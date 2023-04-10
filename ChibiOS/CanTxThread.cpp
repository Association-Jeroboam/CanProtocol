#include "ch.hpp"
#include "chmemheaps.h"
#include "CanTxThread.hpp"
#include "CanProtocol.hpp"
#include "Logging.hpp"
#include "hal.h"
#include "BuildConf.hpp"
#include "cstring"
#include "Cyphal/libcanard/libcanard/canard.h"

constexpr uint32_t TIMEOUT_MS      = 500;
constexpr uint32_t THREAD_SLEEP_US = 30;
constexpr uint32_t MSG_SEND_EVT    = 1;
constexpr uint32_t MAX_FRAME_SIZE  = CANARD_MTU_CAN_CLASSIC;

CanTxThread::CanTxThread(CanardInstance* instance):m_listener(),
                                                   m_source(),
                                                   instance(instance),
                                                   m_mutex(){
    instance = nullptr;
}

void CanTxThread::main() {
    Logging::println("[CAN TX] Thread start");
    setName("Can Tx");
    queue = canardTxInit(100, MAX_FRAME_SIZE);

    m_source.registerMask(&m_listener, MSG_SEND_EVT);

    while (!shouldTerminate()) {

        eventmask_t event = waitOneEvent(MSG_SEND_EVT);

        if(event & MSG_SEND_EVT) {
            const CanardTxQueueItem* item = canardTxPeek(&queue);

            while(item != NULL) {
                m_mutex.lock();
                CanardTxQueueItem* extractedItem = canardTxPop(&queue, item);
                m_mutex.unlock();
                uint32_t           size          = item->frame.payload_size;

                do {
                    CANTxFrame frame;
                    frame.ext.EID = item->frame.extended_can_id;
                    frame.ext.XTD = 1;

                    if (size >= MAX_FRAME_SIZE) {
                        frame.DLC = MAX_FRAME_SIZE;
                        size -= MAX_FRAME_SIZE;
                    } else {
                        frame.DLC = size;
                        size      = 0;
                    }
                    memcpy(&frame.data8, item->frame.payload, frame.DLC);
                    msg_t msg = canTransmitTimeout(&CAN_DRIVER, CAN_ANY_MAILBOX, &frame, TIME_MS2I(TIMEOUT_MS));
                    if (msg != MSG_OK) {
                        chSysLock();
                        canStop(&CAN_DRIVER);
                        canStart(&CAN_DRIVER, &canConfig);
                        chSysUnlock();
                        Logging::println("[CAN TX] fail %lu", msg);
                    }
                } while (size > 0);

                instance->memory_free(instance, extractedItem);
                item = canardTxPeek(&queue);
            }

        }
        chThdYield();
    }
}

bool CanTxThread::send(const CanardTransferMetadata* const metadata,
                       const size_t                        payload_size,
                       const void* const                   payload){
    bool success;
    m_mutex.lock();
    int32_t res = canardTxPush(&queue, instance, chVTGetSystemTime(), metadata, payload_size, payload);
    m_mutex.unlock();
    success = (0 <= res);
    if(success) {
        m_source.broadcastFlags(MSG_SEND_EVT);
    } else {
        Logging::println("[CAN TX] send fail with error %li", res);
    }
    return success;
}
