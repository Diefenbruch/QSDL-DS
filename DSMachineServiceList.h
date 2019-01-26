#ifndef _DSMACHINESERVICELIST_H_
#define _DSMACHINESERVICELIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSMachineService;
class DSString;

typedef DSList<DSMachineService> DSMachineServiceList;
typedef DSKeyList<DSMachineService, DSString> DSMachineServiceKeyList;

#endif  // _DSMACHINESERVICELIST_H_
