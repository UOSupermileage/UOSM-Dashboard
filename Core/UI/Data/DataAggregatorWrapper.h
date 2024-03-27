//
// Created by Jeremy Cote on 2023-07-29.
//

#ifndef UOSM_DASHBOARD_DATAAGGREGATORWRAPPER_H
#define UOSM_DASHBOARD_DATAAGGREGATORWRAPPER_H

#include "ApplicationTypes.h"
#include "DataAggregatorWrapperType.h"
#include "CANMessageLookUpModule.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup core-modules
 * Creates a data aggregator wrapper object and returns a pointer to it.
 * @return A pointer to the data aggregator wrapper object.
*/
DataAggregatorWrapper* DataAggregator_Create();

void SetEfficiency(DataAggregatorWrapper* wrapper, lap_efficiencies_t* efficiencies);

#ifdef  __cplusplus
}
#endif

#endif //UOSM_DASHBOARD_DATAAGGREGATORWRAPPER_H
