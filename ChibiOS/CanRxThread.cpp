#include "CanRxThread.hpp"
#include "CanProtocol.hpp"
#include "BuildConf.hpp"
#include "Logging.hpp"
#include "Heartbeat_1_0.h"

CanRxThread::CanRxThread():m_listenersCount(0) {}

void CanRxThread::main() {
    Logging::println("[CAN RX] Thread start");
    setName("Can Rx");
    CanardRxSubscription heartbeatSub;
    m_sub[m_subCnt] = &heartbeatSub;
    int32_t subscrption = canardRxSubscribe(m_instance,
                      CanardTransferKindMessage,
                      uavcan_node_Heartbeat_1_0_FIXED_PORT_ID_,
                      uavcan_node_Heartbeat_1_0_EXTENT_BYTES_,
                      CANARD_DEFAULT_TRANSFER_ID_TIMEOUT_USEC,
                      m_sub[m_subCnt++]);

    Logging::println("sbuscription: %li", subscrption);

    while (!shouldTerminate()){
        CANRxFrame rxFrame;

        canReceiveTimeout(&CAN_DRIVER, CAN_ANY_MAILBOX, &rxFrame, TIME_INFINITE);
        Logging::println("CAN Rx rcvd");
        const CanardMicrosecond timestamp = 0;
        const CanardFrame frame = {
            .extended_can_id = rxFrame.ext.EID,
            .payload_size = rxFrame.DLC,
            .payload = rxFrame.data8,
        };

        CanardRxTransfer transfer;
        int32_t ret = canardRxAccept(m_instance, timestamp, &frame, 0, &transfer, m_sub);
        if(ret == 1) {
            //success
            Logging::println("frame accepted");
            Logging::println("frame rcvd:");
            Logging::println("Metadata");
            Logging::println("port_id: %X", transfer.metadata.port_id);
            Logging::println("transfer_id: %X", transfer.metadata.transfer_id);
            Logging::println("remote_node_id: %X", transfer.metadata.remote_node_id);
            Logging::println("Data");
            for(uint8_t i = 0; i < transfer.payload_size; i++){
                Logging::print("%X ", ((uint8_t*)transfer.payload)[i]);
            }

            Logging::println("");

            m_instance->memory_free(m_instance, transfer.payload);

        } else if (ret == 0) {
            //nope
            Logging::println("frame rejected");
        }else {
            //error
            Logging::println("frame error %li", ret);
        }

    }
}

bool CanRxThread::registerListener(CanListener *listener) {
    if(m_listenersCount >= CAN_RX_MAX_LISTENERS) {
        return false;
    }
    for(listenerCount_t i = 0; i < m_listenersCount; i++) {
        if(listener == m_listeners[i]){
            return true;
        }
    }
    m_listeners[m_listenersCount] = listener;
    m_listenersCount++;
    return true;
}

bool CanRxThread::subscribe(CanListener *listener, CanardRxSubscription* subscription, CanardSubscribeMetadata metadata){

    if(m_subCnt >= CAN_RX_MAX_SUBSCRIPTION) return false;

    if( !registerListener(listener) ) return false;

    m_sub[m_subCnt] = subscription;
    int32_t subRet = canardRxSubscribe(m_instance,
                                       metadata.transfer_kind,
                                       metadata.port_id,
                                       metadata.extent,
                                       CANARD_DEFAULT_TRANSFER_ID_TIMEOUT_USEC,
                                       m_sub[m_subCnt]);
    m_subCnt++;

    Logging::println("sbuscription: %li", subRet);
}
