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
static volatile uint32_t lapCount = 0;
void EventDataCallback(iCommsMessage_t *msg) {
    DebugPrint("EventDataCallback! %d", msg->standardMessageID);

    if (msg->dataLength == CANMessageLookUpTable[EVENT_DATA_ID].numberOfBytes) {
        EventCode code = msg->data[1];
        flag_status_t status = msg->data[0];

        DebugPrint("EventDataCallback, received code %d with status %d", code, status);
        switch (code) {
            case NEW_LAP:
                if (status > lapCount) {
                    lapCount = status;
                    ResetTimer(aggregatorWrapper, 0);
                }
            default:
                break;
        }
    } else {
        DebugPrint("msg.dataLength does not match lookup table. %d != %d", msg->dataLength, CANMessageLookUpTable[ERROR_DATA_ID].numberOfBytes);
    }
}
void MotorRPMDataCallback(iCommsMessage_t *msg) {
    DebugPrint("Received motor RPM");
    int32_t rpm = readMsg(msg);
    DebugPrint("RPM %d", rpm);
    SetRPMSpeed(aggregatorWrapper, rpm * -1);
}
void CurrentVoltageDataCallback(iCommsMessage_t *msg) {
    DebugPrint("Received current and voltage");
    uint16_pair_t battery = readMsgPairUInt16Bit(msg);
    DebugPrint("Current %d", battery.a);
    SetBatteryCurrent(aggregatorWrapper, battery.a);
    DebugPrint("Voltage %d", battery.b);
    SetBatteryVoltage(aggregatorWrapper, battery.b);
}
void MotorTemperatureDataCallback(iCommsMessage_t *msg) {
    DebugPrint("Received motor temperature");
    temperature_t temp = readMsg(msg);
    DebugPrint("Temperature %d", temp);
    SetMotorTemperature(aggregatorWrapper, temp);
}
void PressureTemperatureDataCallback(iCommsMessage_t *msg){}
void LightsDataCallback(iCommsMessage_t *msg){}
