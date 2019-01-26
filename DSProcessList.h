#ifndef _DSPROCESSLIST_H_
#define _DSPROCESSLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSProcess;
class DSString;

typedef DSList<DSProcess> DSProcessList;
typedef DSKeyList<DSProcess, DSString> DSProcessKeyList;

#endif  // _DSPROCESSLIST_H_
