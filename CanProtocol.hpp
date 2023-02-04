#pragma once

enum CanProtocolPortID {
    ROBOT_CURRENT_STATE_ID          = 101,
    ROBOT_POSE_GOAL_ID              = 102,
    ROBOT_TWIST_GOAL_ID             = 103,
    ROBOT_SET_CURRENT_POSE_ID       = 104,
    ROBOT_GOAL_SPEEDS_WHEELS_ID     = 105,
    ROBOT_GOAL_SPEED_LEFT_WHEEL_ID  = 106,
    ROBOT_GOAL_SPEED_RIGHT_WHEEL_ID = 107,
    ROBOT_GOAL_SPEED_ANGULAR_ID     = 108,
    ROBOT_GOAL_SPEED_LINEAR_ID      = 109,
    ROBOT_GOAL_ANGLE_ID             = 110,
    ROBOT_GOAL_DISTANCE_ID          = 111,
    ROBOT_SET_PWM_LEFT_WHEEL_ID     = 112,
    ROBOT_SET_PWM_RIGHT_WHEEL_ID    = 113,
    ROBOT_SET_PWM_WHEELS_ID         = 114,


    MOTION_SET_PID_ID               = 201,
    MOTION_SET_ADAPTATIVE_PID_ID    = 202,
    MOTION_SET_MOTION_CONFIG_ID     = 203,
    MOTION_PID_STATE_ID             = 204,
    MOTION_RESET_ID                 = 205,
    MOTION_ODOM_TICKS_ID            = 206,

    EMERGENCY_STATE_ID              = 301,

    ACTION_SERVO_SET_ANGLE_ID       = 401,
    ACTION_SERVO_SET_CONFIG_ID      = 402,
    ACTION_SERVO_SET_COLOR_ID       = 403,
    ACTION_SLIDER_SET_POSITION_ID   = 404,
    ACTION_SLIDER_SET_CONFIG_ID     = 405,
    ACTION_PUMP_SET_STATUS_ID       = 406,
    ACTION_PUMP_STATUS_ID           = 407,
    ACTION_VALVE_SET_STATUS_ID      = 408,
    ACTION_VALVE_STATUS_ID          = 409,
    ACTION_SERVO_CURRENT_ANGLE_ID   = 410,
    ACTION_SERVO_SET_PLIERS_ID      = 411,
    ACTION_RESISTANCE_MEAS_ID       = 412,
    ACTION_SERVO_REBOOT_ID          = 413,
    ACTION_SERVO_GENERIC_COMMAND_ID = 414,
    ACTION_SERVO_GENERIC_READ_ID    = 415,

    EMERGENCY_STOP_ID               = 501,

};

enum CanProtocolNodeID {
    CAN_PROTOCOL_EMBEDDED_COMPUTER_ID = 42, // the answer
    CAN_PROTOCOL_MOTION_BOARD_ID      = 11, // the legs
    CAN_PROTOCOL_ACTION_BOARD_ID      = 31, // 11 + 31 = 42 !!
};

enum CanProtocolServoID {
    CAN_PROTOCOL_SERVO_ARM_LEFT_A         = 0,
    CAN_PROTOCOL_SERVO_ARM_LEFT_B         = 1,
    CAN_PROTOCOL_SERVO_ARM_LEFT_C         = 2,
    CAN_PROTOCOL_SERVO_ARM_LEFT_D         = 3,
    CAN_PROTOCOL_SERVO_ARM_LEFT_E         = 4,
    CAN_PROTOCOL_SERVO_ARM_RIGHT_A        = 5,
    CAN_PROTOCOL_SERVO_ARM_RIGHT_B        = 6,
    CAN_PROTOCOL_SERVO_ARM_RIGHT_C        = 7,
    CAN_PROTOCOL_SERVO_ARM_RIGHT_D        = 8,
    CAN_PROTOCOL_SERVO_ARM_RIGHT_E        = 9,
    CAN_PROTOCOL_SERVO_RAKE_LEFT_TOP      = 10,
    CAN_PROTOCOL_SERVO_RAKE_LEFT_BOTTOM   = 11,
    CAN_PROTOCOL_SERVO_RAKE_RIGHT_TOP     = 12,
    CAN_PROTOCOL_SERVO_RAKE_RIGHT_BOTTOM  = 13,
    CAN_PROTOCOL_SERVO_PUSH_ARM_LEFT      = 14,
    CAN_PROTOCOL_SERVO_PUSH_ARM_RIGHT     = 15,
    CAN_PROTOCOL_SERVO_MEASURE_FORK       = 16,
    CAN_PROTOCOL_SERVO_PLIERS_INCLINATION = 17,
    CAN_PROTOCOL_SERVO_PLIERS             = 18,
};

enum CanProtocolSliderID {
    CAN_PROTOCOL_SLIDER_LEFT,
    CAN_PROTOCOL_SLIDER_RIGHT,
};

enum CanProtocolPumpID {
    CAN_PROTOCOL_PUMP_LEFT_ID,
    CAN_PROTOCOL_PUMP_RIGHT_ID,
};

enum CanProtocolValveID {
    CAN_PROTOCOL_VALVE_LEFT_ID,
    CAN_PROTOCOL_VALVE_RIGHT_ID,
};

enum CanProtocolPIDID{
    CAN_PROTOCOL_LEFT_SPEED_PID_ID,
    CAN_PROTOCOL_RIGHT_SPEED_PID_ID,
    CAN_PROTOCOL_PID_LAST,
};

enum CanProtocolResponseTag{
    CAN_PROTOCOL_RESPONSE_SUCCESS = 0,
    CAN_PROTOCOL_RESPONSE_ERROR,
};
