#pragma once
#include "CanProtocol.hpp"
#include "canard.h"

class CanListener {
public:
    virtual void processCanMsg(CanardRxTransfer * transfer) = 0;
};
