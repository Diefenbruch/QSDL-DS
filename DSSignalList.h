#ifndef _DSSIGNAL_LIST_H_
#define _DSSIGNAL_LIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSSignal;
class DSString;

typedef DSList<DSSignal> DSSignalList;
typedef DSKeyList<DSSignal, DSString> DSSignalKeyList;

#endif  // _DSSIGNAL_LIST_H_
