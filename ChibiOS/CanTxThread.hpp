#pragma once

#include "ch.hpp"
#include "hal.h"
#include "CanProtocol.hpp"
#include "Cyphal/libcanard/libcanard/canard.h"

constexpr uint16_t CAN_TX_WA = 0x100;

class CanTxThread : public chibios_rt::BaseStaticThread<CAN_TX_WA>{

public :

    CanTxThread(CanardInstance* instance);

    bool send(const CanardTransferMetadata* const metadata,
              const size_t                        payload_size,
              const void* const                   payload);

private:

    void main();

    chibios_rt::EventListener m_listener;
    chibios_rt::EventSource m_source;
    CanardInstance* instance;
    CanardTxQueue  queue;
    chibios_rt::Mutex m_mutex;

};
