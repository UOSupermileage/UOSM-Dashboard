#include "ApplicationTypes.h"

#include "CANMessageLookUpModule.h"
#include "InternalCommsModule.h"
#include "CANDriver.h"
#include "DataAggregatorWrapper.h"

static DataAggregatorWrapper* aggregatorWrapper;

void CAN_SetAggregator(DataAggregatorWrapper* wrapper) {
    aggregatorWrapper = wrapper;
}

static bool CAN_Enabled() {
    return aggregatorWrapper != NULL;
}

void CAN_Dummy_RPM(velocity_t v) {
    // Invert motor RPM to display in human-readable manor
    SetMotorRPM(aggregatorWrapper, v);
}

void MotorRPMDataCallback(iCommsMessage_t* msg) {
    if (!CAN_Enabled()) {
        return;
    }

    velocity_t rpm = readMsg(msg);
    DebugPrint("CAN rpm received: %d", rpm);
    SetMotorRPM(aggregatorWrapper, rpm * -1);
    LogCanMessage(aggregatorWrapper, MOTOR_RPM_DATA_ID, rpm, CAN_DECIMAL);
}

void ThrottleDataCallback(iCommsMessage_t* msg) {
    if (!CAN_Enabled()) {
        return;
    }

    percentage_t throttle = readMsg(msg);
    DebugPrint("CAN throttle received: %d", throttle);
    SetThrottlePosition(aggregatorWrapper, throttle);
    LogCanMessage(aggregatorWrapper, THROTTLE_DATA_ID, throttle, CAN_DECIMAL);
}

void ErrorDataCallback(iCommsMessage_t* msg) {
    if (msg->dataLength == CANMessageLookUpTable[ERROR_DATA_ID].numberOfBytes) {
        ErrorCode code = msg->data[1];
        flag_status_t status = msg->data[0];
        LogCanMessagePairValue(aggregatorWrapper, ERROR_DATA_ID, code, status, CAN_DECIMAL);
    } else {
        DebugPrint("Received corrupted error CAN message.");
    }
}

void SpeedDataCallback(iCommsMessage_t* msg) {
    speed_t speed = readMsg(msg);
    LogCanMessage(aggregatorWrapper, SPEED_DATA_ID, speed, CAN_DECIMAL);
}

void EventDataCallback(iCommsMessage_t* msg) {
    if (msg->dataLength == CANMessageLookUpTable[EVENT_DATA_ID].numberOfBytes) {
        EventCode code = (EventCode) msg->data[1];
        flag_status_t status = (flag_status_t) msg->data[0];
        LogCanMessagePairValue(aggregatorWrapper, EVENT_DATA_ID, code, status, CAN_DECIMAL);
    } else {
        DebugPrint("Received corrupted event CAN message.");
    }
}

void CurrentVoltageDataCallback(iCommsMessage_t* msg) {
    uint16_pair_t pair = readMsgPairUInt16Bit(msg);
    SetBatteryVoltage(aggregatorWrapper, pair.b);
    LogCanMessagePairValue(aggregatorWrapper, CURRENT_VOLTAGE_DATA_ID, pair.a, pair.b, CAN_DECIMAL);
}
