#ifndef _DSMACHINELIST_H_
#define _DSMACHINELIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSMachine;
class DSString;

typedef DSList<DSMachine> DSMachineList;
typedef DSKeyList<DSMachine, DSString> DSMachineKeyList;

#endif  // _DSMACHINELIST_H_
