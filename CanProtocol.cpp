#include "CanProtocol.hpp"

canFrame_t CanProtocol::createFrame(enum canFrameID_e ID, ...) {
    va_list args;
    va_start(args, ID);
    canFrame_t canData;
    canData.ID = ID;
    switch (ID) {
        case CAN_PLIERS_ID:
            canData.len = CAN_PLIERS_LEN;
            canData.data.pliersData = {
                .plierID = (uint8_t)va_arg(args, int),
                .state   = (uint8_t)va_arg(args, int),
            };
            break;
        case CAN_SLIDERS_ID: {
            canData.len = CAN_SLIDERS_LEN;
            uint8_t sliderID = va_arg(args, int);
            uint16_t position = va_arg(args, int);
            canData.data.slidersData = {
                .position = position,
                .sliderID = sliderID,
            };
            break;
        }
        case CAN_FLAG_ID:
            canData.len = CAN_FLAG_LEN;
            canData.data.flagData = {
                .state = (uint8_t)va_arg(args, int),
            };
            break;
        case CAN_ARMS_ID:
            canData.len = CAN_ARMS_LEN;
            canData.data.armData = {
                .armID = (uint8_t)va_arg(args, int),
                .state = (uint8_t)va_arg(args, int),
            };
            break;
        case CAN_READ_COLOR_ID:
            canData.len = CAN_READ_COLOR_LEN;
            canData.data.readColorData = {
                .sensorID = (uint8_t)va_arg(args, int),
            };
            break;
        case CAN_COLOR_ID:
            canData.len = CAN_COLOR_LEN;
            canData.data.colorData = {
                .red = (uint8_t)va_arg(args, int),
                .green = (uint8_t)va_arg(args, int),
                .blue = (uint8_t)va_arg(args, int),
            };
            break;
        case CAN_ACTION_IN_PROGRESS_ID:
            canData.len = CAN_ACTION_IN_PROGRESS_LEN;
            break;
        case CAN_ACTION_DONE_ID:
            canData.len = CAN_ACTION_DONE_LEN;
            break;
        case CAN_DISPLAY_POINTS_ID:
            canData.len = CAN_DISPLAY_POINTS_LEN;
            canData.data.displayPointsData = {
                .points = (uint16_t)va_arg(args, int),
            };
            break;
        case CAN_SET_POSE_ID:
            canData.len = CAN_SET_POSE_LEN;
            canData.data.poseData = {
                .x = (int16_t)va_arg(args, int),
                .y = (int16_t)va_arg(args, int),
                    .angle = (float)va_arg(args, double),
            };
            break;
        case CAN_CURRENT_POSE_ID:
            canData.len = CAN_CURRENT_POSE_LEN;
            canData.data.poseData = {
                    .x = (int16_t)va_arg(args, int),
                    .y = (int16_t)va_arg(args, int),
                    .angle = (float)va_arg(args, double),
            };
            break;
    }

    va_end(args);
    return canData;
}

canFrame_t CanProtocol::decodeFrame(CANRxFrame frame){
    canFrame_t  canData;
    switch(frame.SID) {
        case CAN_PLIERS_ID             : {
            canData.ID = CAN_PLIERS_ID;
            canData.data.pliersData.plierID = frame.data8[0];
            canData.data.pliersData.state   = frame.data8[1];
            break;
        }
        case CAN_SLIDERS_ID            : {
            canData.ID = CAN_SLIDERS_ID;
            canData.data.slidersData.position = frame.data16[0];
            canData.data.slidersData.sliderID = frame.data8[2];
            break;
        }
        case CAN_FLAG_ID               : {
            canData.ID =CAN_FLAG_ID;
            canData.data.flagData.state = frame.data8[0];
            break;
        }
        case CAN_ARMS_ID               : {
            canData.ID =CAN_ARMS_ID;
            canData.data.armData.armID = frame.data8[0];
            canData.data.armData.state = frame.data8[1];
            break;
        }
        case CAN_READ_COLOR_ID         : {
            canData.ID = CAN_READ_COLOR_ID;
            canData.data.readColorData.sensorID = frame.data8[0];
            break;
        }
        case CAN_COLOR_ID              : {
            canData.ID = CAN_COLOR_ID;
            canData.data.colorData.red   = frame.data8[0];
            canData.data.colorData.green = frame.data8[1];
            canData.data.colorData.blue  = frame.data8[2];
            break;
        }
        case CAN_ACTION_IN_PROGRESS_ID : {
            canData.ID = CAN_ACTION_IN_PROGRESS_ID;
            break;
        }
        case CAN_ACTION_DONE_ID        : {
            canData.ID = CAN_ACTION_DONE_ID;
            break;
        }
        case CAN_DISPLAY_POINTS_ID     : {
            canData.ID = CAN_DISPLAY_POINTS_ID;
            canData.data.displayPointsData.points = frame.data16[0];
            break;
        }
        case CAN_SET_POSE_ID           : {
            canData.ID = CAN_SET_POSE_ID;
            canData.data.poseData.x = frame.data16[0];
            canData.data.poseData.y = frame.data16[1];
            uint32_t encodedAngle = frame.data32[1];
            canData.data.poseData.angle = *reinterpret_cast<float*>(&encodedAngle);
            break;
        }
        case CAN_CURRENT_POSE_ID       : {
            canData.ID = CAN_CURRENT_POSE_ID;
            canData.data.poseData.x = frame.data16[0];
            canData.data.poseData.y = frame.data16[1];
            uint32_t encodedAngle = frame.data32[1];
            canData.data.poseData.angle = *reinterpret_cast<float*>(&encodedAngle);
            break;
        }
        default:
            break;
    }
    return canData;
}
