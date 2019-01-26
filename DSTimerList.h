#ifndef _DSTIMERLIST_H_
#define _DSTIMERLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSTimer;
class DSString;

typedef DSList<DSTimer> DSTimerList;
typedef DSKeyList<DSTimer, DSString> DSTimerKeyList;

#endif  // _DSTIMERLIST_H_
