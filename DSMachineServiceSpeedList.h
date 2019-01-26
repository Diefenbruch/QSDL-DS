#ifndef _DSMACHINESERVICESPEEDLIST_H_
#define _DSMACHINESERVICESPEEDLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSMachineServiceSpeed;
class DSString;

typedef DSList<DSMachineServiceSpeed> DSMachineServiceSpeedList;
typedef DSKeyList<DSMachineServiceSpeed, DSString> DSMachineServiceSpeedKeyList;

#endif  // _DSMACHINESERVICESPEEDLIST_H_
