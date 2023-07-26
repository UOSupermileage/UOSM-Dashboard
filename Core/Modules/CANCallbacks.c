#include "ApplicationTypes.h"

#include "CANMessageLookUpModule.h"
#include "DataAggregationModule.h"
#include "InternalCommsModule.h"
#include "CANDriver.h"

void MotorRPMDataCallback(iCommsMessage_t* msg) {
    velocity_t rpm = readMsg(msg);
    DebugPrint("CAN rpm received: %d", rpm);
    SystemSetMotorRPM(rpm);
}

void VoltageDataCallback(iCommsMessage_t* msg) {
	uint32_t voltage = readMsg(msg);
	DebugPrint("CAN voltage received: %d", voltage);
	SystemSetBatteryVoltage(voltage);
}
