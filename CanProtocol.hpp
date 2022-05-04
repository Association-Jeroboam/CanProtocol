#pragma once
#include "ch.hpp"
#include "hal.h"

enum CanProtocolPortID {
    ROBOT_CURRENT_STATE_ID = 0,
    ROBOT_POSE_GOAL_ID,
    ROBOT_TWIST_GOAL_ID,

    MOTION_SET_MOTOR_PID_ID,
    MOTION_SET_PARAMS_ID,
    MOTION_RESET_ID,

    EMERGENCY_STATE_ID,

    ACTION_SERVO_SET_ANGLE_ID,
    ACTION_SERVO_SET_CONFIG_ID,
    ACTION_PUMP_SET_STATUS_ID,
    ACTION_PUMP_STATUS_ID,

};

enum CanProtocolNodeID {
    EMBEDDED_COMPUTER_ID = 42, // the answer
    MOTION_BOARD_ID      = 11, // the legs
    ACTION_BOARD_ID      = 31, // 11 + 31 = 42 !!
};