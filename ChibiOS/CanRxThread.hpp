#pragma once

#include "ch.hpp"
#include "hal.h"
#include "CanListener.hpp"

typedef uint8_t listenerCount_t;

constexpr uint16_t CAN_RX_WA = 0x80;
constexpr listenerCount_t  CAN_RX_MAX_LISTENERS = 8;

class CanRxThread : public chibios_rt::BaseStaticThread<CAN_RX_WA> {
public:
    CanRxThread();
    void registerListener(CanListener * listener);

private:
    void main() override;
    CanListener *   m_listeners[CAN_RX_MAX_LISTENERS];
    listenerCount_t m_listenersCount;
    void dispatchFrame(CANRxFrame frame);
};

