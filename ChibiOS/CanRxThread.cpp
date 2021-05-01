#include "CanRxThread.hpp"
#include "CanProtocol.hpp"
#include "BuildConf.hpp"
#include "Logging.hpp"

CanRxThread::CanRxThread():m_listenersCount(0) {}

void CanRxThread::main() {
    Logging::println("[CAN RX] Thread start");
    setName("Can Rx");

    while (!shouldTerminate()){
        CANRxFrame rxFrame;

        canReceiveTimeout(&CAN_DRIVER, CAN_ANY_MAILBOX, &rxFrame, TIME_INFINITE);

        dispatchFrame(rxFrame);

    }
}

void CanRxThread::registerListener(CanListener *listener) {
    if(m_listenersCount < CAN_RX_MAX_LISTENERS) {
        m_listeners[m_listenersCount] = listener;
        m_listenersCount++;
    }
}

void CanRxThread::dispatchFrame(CANRxFrame frame){

    canFrame_t canData = CanProtocol::decodeFrame(frame);
    for (listenerCount_t i = 0; i < m_listenersCount; i++) {
        m_listeners[i]->processFrame(canData);
    }
}
