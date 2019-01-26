#ifndef _DSSIGNALROUTELIST_H_
#define _DSSIGNALROUTELIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSSignalRoute;
class DSString;

typedef DSList<DSSignalRoute> DSSignalRouteList;
typedef DSKeyList<DSSignalRoute, DSString> DSSignalRouteKeyList;

#endif  // _DSSIGNALROUTELIST_H_
