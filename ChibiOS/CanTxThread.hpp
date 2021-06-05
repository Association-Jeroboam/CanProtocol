#pragma once

#include "ch.hpp"
#include "hal.h"
#include "CanProtocol.hpp"

constexpr uint16_t CAN_TX_WA = 0x100;
constexpr uint16_t TX_QUEUE_LEN  = 10;
constexpr uint16_t MSG_DATA_SIZE = sizeof(canFrame_t);

class CanTxThread : public chibios_rt::BaseStaticThread<CAN_TX_WA>{

public :

    CanTxThread();

    bool send(canFrame_t frame);

private:

    void main() override;

    CANTxFrame buildFrame(canFrame_t frameData);

    objects_fifo_t pendingMessagesQueue;
    CANTxFrame     dataBuffer[TX_QUEUE_LEN];
    msg_t          msgBuffer[TX_QUEUE_LEN];

};
