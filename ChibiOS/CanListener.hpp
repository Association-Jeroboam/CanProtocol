#pragma once
#include "CanProtocol.hpp"

class CanListener {
public:
    virtual void processFrame(canFrame_t frame) = 0;
};
