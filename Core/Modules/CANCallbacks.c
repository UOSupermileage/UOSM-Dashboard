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

void MotorRPMDataCallback(iCommsMessage_t* msg) {
    if (!CAN_Enabled()) {
        return;
    }

    velocity_t rpm = readMsg(msg);
    DebugPrint("CAN rpm received: %d", rpm);
    SetMotorRPM(aggregatorWrapper, rpm);
}

void VoltageDataCallback(iCommsMessage_t* msg) {
    if (!CAN_Enabled()) {
        return;
    }

    uint32_t voltage = readMsg(msg);
    DebugPrint("CAN voltage received: %d", voltage);
    SetBatteryVoltage(aggregatorWrapper, voltage);
}
