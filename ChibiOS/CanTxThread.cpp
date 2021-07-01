#include "CanTxThread.hpp"
#include "CanProtocol.hpp"
#include "Logging.hpp"
#include "hal.h"
#include "BuildConf.hpp"
#include "cstring"

constexpr uint32_t TIMEOUT_MS = 500;
constexpr uint32_t THREAD_SLEEP_US = 30;

CanTxThread::CanTxThread() {
    chFifoObjectInit(&pendingMessagesQueue, MSG_DATA_SIZE, TX_QUEUE_LEN,  dataBuffer, msgBuffer);
}

void CanTxThread::main() {
	Logging::println("[CAN TX] Thread start");
    setName("Can Tx");

    while (!shouldTerminate()) {
        canFrame_t * data;
        chFifoReceiveObjectTimeout(&pendingMessagesQueue, (void **)&data, TIME_INFINITE);
        CANTxFrame frame = buildFrame(*data);
        chFifoReturnObject(&pendingMessagesQueue, data);
        msg_t msg = canTransmitTimeout(&CAN_DRIVER, CAN_ANY_MAILBOX, &frame, TIME_MS2I(TIMEOUT_MS));

        if(msg != MSG_OK){
            Logging::println("[CAN TX] fail %lu", msg);
        }
        chThdSleep(TIME_US2I(THREAD_SLEEP_US));
    }
}

bool CanTxThread::send(canFrame_t frame){
    bool ret = false;
    canFrame_t *txFrame = (canFrame_t *) chFifoTakeObjectTimeout(&pendingMessagesQueue, TIME_IMMEDIATE);
    if(txFrame == NULL) {
        Logging::println("[CAN TX] Queue full!");
    } else {
        ret = true;
        *txFrame = frame;
        chFifoSendObject(&pendingMessagesQueue, txFrame);
    }
    return ret;
}

CANTxFrame CanTxThread::buildFrame(canFrame_t frameData) {
    CANTxFrame  canFrame;
    canFrame.std.SID = frameData.ID;
    canFrame.DLC = frameData.len;
    memcpy(&canFrame.data8, &frameData.data, frameData.len);
    return canFrame;
}
