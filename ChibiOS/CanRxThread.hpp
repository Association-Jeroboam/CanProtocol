#pragma once

#include "ch.hpp"
#include "hal.h"
#include "CanListener.hpp"
#include "canard.h"

struct CanardSubscribeMetadata {
    CanardTransferKind transfer_kind;
    CanardPortID port_id;
    size_t extent;
};

typedef uint8_t listenerCount_t;

constexpr uint16_t CAN_RX_WA = 0x100;
constexpr listenerCount_t  CAN_RX_MAX_LISTENERS = 8;
constexpr uint8_t          CAN_RX_MAX_SUBSCRIPTION = 16;

class CanRxThread : public chibios_rt::BaseStaticThread<CAN_RX_WA> {
public:
    CanRxThread();

    inline void setCanardInstance(CanardInstance* instance) { this->m_instance = instance;};

    bool subscribe(CanListener *listener, CanardRxSubscription* subscription, CanardSubscribeMetadata metadata);

private:
    void main() override;
    CanListener *   m_listeners[CAN_RX_MAX_LISTENERS];
    listenerCount_t m_listenersCount;
    CanardInstance * m_instance;
    CanardRxSubscription* m_sub[CAN_RX_MAX_SUBSCRIPTION];
    uint8_t m_subCnt;

    bool registerListener(CanListener * listener);
};

