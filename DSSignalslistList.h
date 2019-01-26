#ifndef _DSSIGNALLISTLIST_H_
#define _DSSIGNALLISTLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSSignalslist;
class DSString;

typedef DSList<DSSignalslist> DSSignalslistList;
typedef DSKeyList<DSSignalslist, DSString> DSSignalslistKeyList;

#endif  // _DSSIGNALLISTLIST_H_
