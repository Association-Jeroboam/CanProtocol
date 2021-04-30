#include "CanRxThread.hpp"
#include "CanProtocol.hpp"
#include "BuildConf.hpp"
#include "Logging.hpp"
#include "PliersManager.hpp"

void CanRxThread::main() {
    Logging::println("[CAN RX] Thread start");
    setName("Can Rx");

    while (!shouldTerminate()){
        CANRxFrame rxFrame;

        canReceiveTimeout(&CAN_DRIVER, CAN_ANY_MAILBOX, &rxFrame, TIME_INFINITE);

        processFrame(rxFrame);

    }
}

void CanRxThread::processFrame(CANRxFrame frame){
    canFrame_t canData = CanProtocol::decodeFrame(frame);
    switch(canData.ID) {
        case CAN_PLIERS_ID             : {
            PliersManager::instance()->sendOrder(canData.data.pliersData);
            break;
        }
        case CAN_SLIDERS_ID            : {
            // notify sliders thread
            Logging::println("[CAN RX] Sliders : ID %u, pos %u",
                             canData.data.slidersData.sliderID,
                             canData.data.slidersData.position);
            break;
        }
        case CAN_FLAG_ID               : {
            Logging::println("[CAN RX] Flag : state %u",
                             canData.data.flagData.state);
            break;
        }
        case CAN_ARMS_ID               : {
            Logging::println("[CAN RX] Arm : ID %u state %u",
                             canData.data.armData.armID,
                             canData.data.armData.state);
            break;
        }
        case CAN_READ_COLOR_ID         : {
            Logging::println("[CAN RX] Read color : ID %u",
                             canData.data.readColorData.sensorID);
            break;
        }
        case CAN_COLOR_ID              : {
            Logging::println("[CAN RX] Color: R %u G %u B %u",
                             canData.data.colorData.red,
                             canData.data.colorData.green,
                             canData.data.colorData.blue);
            break;
        }
        case CAN_ACTION_IN_PROGRESS_ID : {
            Logging::println("[CAN RX] Action in progress");
            break;
        }
        case CAN_ACTION_DONE_ID        : {
            Logging::println("[CAN RX] Action done");
            break;
        }
        case CAN_DISPLAY_POINTS_ID     : {
            Logging::println("[CAN RX] Points: %u", canData.data.displayPointsData.points);
            break;
        }
        case CAN_SET_POSE_ID           : {
            Logging::println("[CAN RX] Set pose : X %i Y %i angle %f",
                             canData.data.poseData.x,
                             canData.data.poseData.y,
                             canData.data.poseData.angle);
            break;
        }
        case CAN_CURRENT_POSE_ID       : {
            Logging::println("[CAN RX] Current Pose : X %i Y %i angle %f",
                             canData.data.poseData.x,
                             canData.data.poseData.y,
                             canData.data.poseData.angle);
            break;
        }
        default:
            Logging::println("[CAN RX] Unknown ID %lX", frame.SID);
            break;
    }
}
