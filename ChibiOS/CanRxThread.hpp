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

constexpr uint16_t CAN_RX_WA = 0x400;
constexpr listenerCount_t  CAN_RX_MAX_LISTENERS = 8;
constexpr uint8_t          CAN_RX_MAX_SUBSCRIPTION = 16;

class CanRxThread : public chibios_rt::BaseStaticThread<CAN_RX_WA> {
public:
    CanRxThread(CanardInstance* instance);

    bool subscribe(CanListener *listener,
                   CanardTransferKind transfer_kind,
                   CanardPortID port_id,
                   size_t extent);

private:
    void main() override;
    CanListener *   m_listeners[CAN_RX_MAX_LISTENERS];
    uint8_t         m_listenerSubCnt[CAN_RX_MAX_LISTENERS];
    CanardRxSubscription * m_subLUT[CAN_RX_MAX_LISTENERS][CAN_RX_MAX_SUBSCRIPTION];
    listenerCount_t m_listenersCount;
    CanardInstance * m_instance;
    CanardRxSubscription m_sub[CAN_RX_MAX_SUBSCRIPTION];
    uint8_t m_subCnt;

    bool registerListener(CanListener *listener, uint8_t * idx);

    void notifyListeners(CanardRxSubscription * sub, CanardRxTransfer* transfer);
};

