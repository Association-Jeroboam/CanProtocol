#pragma once

enum CanProtocolPortID {
    ROBOT_CURRENT_STATE_ID        = 1,
    ROBOT_POSE_GOAL_ID            = 2,
    ROBOT_TWIST_GOAL_ID           = 3,
    ROBOT_SET_CURRENT_POSE_ID     = 4,

    MOTION_SET_PID_ID             = 5,
    MOTION_SET_ADAPTATIVE_PID_ID  = 6,
    MOTION_SET_MOTION_CONFIG_ID   = 7,
    MOTION_PID_STATE_ID           = 8,
    MOTION_RESET_ID               = 9,

    EMERGENCY_STATE_ID            = 10,

    ACTION_SERVO_SET_ANGLE_ID     = 11,
    ACTION_SERVO_SET_CONFIG_ID    = 12,
    ACTION_SERVO_SET_COLOR_ID     = 13,
    ACTION_SLIDER_SET_POSITION_ID = 14,
    ACTION_SLIDER_SET_CONFIG_ID   = 15,
    ACTION_PUMP_SET_STATUS_ID     = 16,
    ACTION_PUMP_STATUS_ID         = 17,
    ACTION_VALVE_SET_STATUS_ID    = 18,
    ACTION_VALVE_STATUS_ID        = 19,

};

enum CanProtocolNodeID {
    CAN_PROTOCOL_EMBEDDED_COMPUTER_ID = 42, // the answer
    CAN_PROTOCOL_MOTION_BOARD_ID      = 11, // the legs
    CAN_PROTOCOL_ACTION_BOARD_ID      = 31, // 11 + 31 = 42 !!
};

enum CanProtocolServoID {
    CAN_PROTOCOL_SERVO_ARM_LEFT_A,
    CAN_PROTOCOL_SERVO_ARM_LEFT_B,
    CAN_PROTOCOL_SERVO_ARM_LEFT_C,
    CAN_PROTOCOL_SERVO_ARM_LEFT_D,
    CAN_PROTOCOL_SERVO_ARM_LEFT_E,
    CAN_PROTOCOL_SERVO_ARM_RIGHT_A,
    CAN_PROTOCOL_SERVO_ARM_RIGHT_B,
    CAN_PROTOCOL_SERVO_ARM_RIGHT_C,
    CAN_PROTOCOL_SERVO_ARM_RIGHT_D,
    CAN_PROTOCOL_SERVO_ARM_RIGHT_E,
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
