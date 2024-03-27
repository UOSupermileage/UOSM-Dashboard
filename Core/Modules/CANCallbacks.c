#include "ApplicationTypes.h"

#include "InternalCommsModule.h"
#include "DataAggregatorWrapper.h"

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