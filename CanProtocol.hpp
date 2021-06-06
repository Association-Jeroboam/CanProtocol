#pragma once
#include "ch.hpp"
#include "hal.h"

enum canFrameID_e {
    CAN_PLIERS_ID             = 0x11,
    CAN_SLIDERS_ID            = 0x12,
    CAN_FLAG_ID               = 0x13,
    CAN_ARMS_ID               = 0x14,
    CAN_READ_COLOR_ID         = 0x15,
    CAN_COLOR_ID              = 0x16,
    CAN_PLIERS_BLOCK_ID       = 0x17,
    CAN_ACTION_IN_PROGRESS_ID = 0x1E,
    CAN_ACTION_DONE_ID        = 0x1F,
    CAN_DISPLAY_POINTS_ID     = 0x20,
    CAN_SET_POSE_ID           = 0x40,
    CAN_CURRENT_POSE_ID       = 0x80,
};

enum canFrameLen_e : uint8_t {
    CAN_PLIERS_LEN             = 2,
    CAN_SLIDERS_LEN            = 3,
    CAN_FLAG_LEN               = 1,
    CAN_ARMS_LEN               = 2,
    CAN_READ_COLOR_LEN         = 1,
    CAN_COLOR_LEN              = 3,
    CAN_PLIERS_BLOCK_LEN       = 1,
    CAN_ACTION_IN_PROGRESS_LEN = 0,
    CAN_ACTION_DONE_LEN        = 0,
    CAN_DISPLAY_POINTS_LEN     = 2,
    CAN_SET_POSE_LEN           = 8,
    CAN_CURRENT_POSE_LEN       = 8,
};

enum pliersID : uint8_t {
	PLIERS_FRONT_FAR_LEFT = 0,
	PLIERS_FRONT_LEFT,
	PLIERS_FRONT_RIGHT,
	PLIERS_FRONT_FAR_RIGHT,
	PLIERS_REAR_FAR_RIGHT,
	PLIERS_REAR_RIGHT,
	PLIERS_REAR_MIDDLE,
	PLIERS_REAR_LEFT,
	PLIERS_REAR_FAR_LEFT,
};

enum sliderID {
    SLIDER_ELEVATOR,
    SLIDER_TRANSLATION,
};

enum pliersState : uint8_t {
	PLIERS_OPEN,
	PLIERS_CLOSE,
};

struct pliersData {
	enum pliersID plierID;
	enum pliersState state;
};

struct slidersData {
    uint16_t position;
    enum sliderID sliderID;
};

struct flagData {
    uint8_t state;
};

struct armData {
    uint8_t armID;
    uint8_t state;
};

struct readColorData {
    uint8_t sensorID;
};

struct colorData {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct pliersBlockData {
    uint8_t state;
};

struct displayPointsData {
    uint16_t points;
};

struct poseData {
    int16_t x;
    int16_t y;
    float    angle;
};

typedef struct {
    enum canFrameID_e ID;
    uint8_t len;
    union {
        struct pliersData        pliersData;
        struct slidersData       slidersData;
        struct flagData          flagData;
        struct armData           armData;
        struct readColorData     readColorData;
        struct colorData         colorData;
        struct pliersBlockData   pliersBlockData;
        struct displayPointsData displayPointsData;
        struct poseData          poseData;
    } data;
} __attribute__((packed)) canFrame_t;

namespace CanProtocol {
    canFrame_t createFrame(enum canFrameID_e ID, ...);
    canFrame_t decodeFrame(CANRxFrame frame);
}
