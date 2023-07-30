//
// Created by Jeremy Cote on 2023-07-29.
//

#ifndef UOSM_DASHBOARD_CANCALLBACKS_H
#define UOSM_DASHBOARD_CANCALLBACKS_H

#include "DataAggregatorWrapper.h"

/**
 * Set the aggregator used by CAN Callbacks
 * @param wrapper
 */
void CAN_SetAggregator(DataAggregatorWrapper* wrapper);

void CAN_Dummy_RPM(velocity_t v);

#endif //UOSM_DASHBOARD_CANCALLBACKS_H
