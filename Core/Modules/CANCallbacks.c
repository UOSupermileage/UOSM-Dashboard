#include "ApplicationTypes.h"

#include "InternalCommsModule.h"
#include "DataAggregatorWrapper.h"
#include "CANDriver.h"

static DataAggregatorWrapper* aggregatorWrapper;

void CAN_SetAggregator(DataAggregatorWrapper* wrapper) {
    aggregatorWrapper = wrapper;
}

void EfficiencyDataCallback(iCommsMessage_t* msg) {
    lap_efficiencies_t e;
    DebugPrint("Received efficiencies");
    IComms_ReadEfficiencyMessage(msg, &e);
    DebugPrint("Lap Efficiency: %d %d %d %d", e.lap_0, e.lap_1, e.lap_2, e.lap_3);

    SetEfficiency(aggregatorWrapper, &e);
}

void ThrottleDataCallback(iCommsMessage_t *msg){}
void ErrorDataCallback(iCommsMessage_t *msg){}
void SpeedDataCallback(iCommsMessage_t *msg){
    DebugPrint("Received speed");
    speed_t speed = readMsg(msg);
    DebugPrint("Speed %d", speed);
    SetSpeed(aggregatorWrapper, speed);
}
void EventDataCallback(iCommsMessage_t *msg){}
void MotorRPMDataCallback(iCommsMessage_t *msg) {
    DebugPrint("Received motor RPM");
    int32_t rpm = readMsg(msg);
    DebugPrint("RPM %d", rpm);
    SetRPMSpeed(aggregatorWrapper, rpm);
}
void CurrentVoltageDataCallback(iCommsMessage_t *msg) {
    DebugPrint("Received current and voltage");
    voltage_t voltage = readMsg(msg);
    DebugPrint("Voltage %d", voltage);
    SetBatteryVoltage(aggregatorWrapper, voltage);
}
void PressureTemperatureDataCallback(iCommsMessage_t *msg){}
void LightsDataCallback(iCommsMessage_t *msg){}
