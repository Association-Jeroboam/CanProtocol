#pragma once

#include "ch.hpp"
#include "hal.h"

constexpr uint16_t CAN_RX_WA = 0x100;

class CanRxThread : public chibios_rt::BaseStaticThread<CAN_RX_WA>,
                    public chibios_rt::EventSource {

    void main() override;

private:
    void processFrame(CANRxFrame frame);
};

