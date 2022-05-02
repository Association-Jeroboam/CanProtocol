#include "CanRxThread.hpp"
#include "CanProtocol.hpp"
#include "BuildConf.hpp"
#include "Logging.hpp"
#include "Heartbeat_1_0.h"

CanRxThread::CanRxThread(CanardInstance* instance):m_listenersCount(0), m_subCnt(0), m_instance(instance){}

void CanRxThread::main() {
    Logging::println("[CAN RX] Thread start");
    setName("Can Rx");

    while (!shouldTerminate()){
        CANRxFrame rxFrame;

        canReceiveTimeout(&CAN_DRIVER, CAN_ANY_MAILBOX, &rxFrame, TIME_INFINITE);
        const CanardMicrosecond timestamp = 0;
        CanardFrame frame = {
            .extended_can_id = rxFrame.ext.EID,
            .payload_size = rxFrame.DLC,
            .payload = rxFrame.data8,
        };

        CanardRxTransfer transfer;
        CanardRxSubscription * sub;
        int32_t ret = canardRxAccept(m_instance, timestamp, &frame, 0, &transfer, &sub);
        if(ret == 1) {
            //success
            notifyListeners(sub, &transfer);
            m_instance->memory_free(m_instance, transfer.payload);

        } else if (ret == 0) {
            // rejected or transfer not completed
        }else {
            //error
            Logging::println("frame error %li", ret);
        }
    }
}

bool CanRxThread::registerListener(CanListener *listener, uint8_t * idx) {
    if(m_listenersCount >= CAN_RX_MAX_LISTENERS) {
        return false;
    }
    for(listenerCount_t i = 0; i < m_listenersCount; i++) {
        if(listener == m_listeners[i]){
            *idx = i;
            return true;
        }
    }
    m_listeners[m_listenersCount] = listener;
    *idx = m_listenersCount;
    m_listenersCount++;
    return true;
}

bool CanRxThread::subscribe(CanListener *listener,
                            CanardTransferKind transfer_kind,
                            CanardPortID port_id,
                            size_t extent){

    if(m_subCnt >= CAN_RX_MAX_SUBSCRIPTION) return false;
    uint8_t listenerIdx;
    if( !registerListener(listener, &listenerIdx) ) return false;

    int32_t subRet = canardRxSubscribe(m_instance,
                                       transfer_kind,
                                       port_id,
                                       extent,
                                       CANARD_DEFAULT_TRANSFER_ID_TIMEOUT_USEC,
                                       &m_sub[m_subCnt]);
    if(subRet == 1) {
        // subscription created

    } else if(subRet == 0) {
        // Subscription already existing
        //TODO
    }
    m_listenerSubCnt[listenerIdx]+=1;
    m_subLUT[listenerIdx][m_listenerSubCnt[listenerIdx] - 1] = &m_sub[m_subCnt];

    bool res = subRet >= 0;
    if(res) {
        m_subCnt++;
    }
    return res;
}

void CanRxThread::notifyListeners(CanardRxSubscription * sub, CanardRxTransfer* transfer) {
    for (uint8_t listenerIdx = 0; listenerIdx < m_listenersCount; listenerIdx++) {
        CanListener * listener = m_listeners[listenerIdx];
        for (uint8_t subIdx = 0; subIdx < m_listenerSubCnt[listenerIdx]; subIdx++) {
            if(m_subLUT[listenerIdx][subIdx] == sub) {
                listener->processCanMsg(transfer);
            }
        }
    }
}
