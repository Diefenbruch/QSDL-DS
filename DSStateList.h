#ifndef _DSSTATELIST_H_
#define _DSSTATELIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSState;
class DSString;

typedef DSList<DSState> DSStateList;
typedef DSKeyList<DSState, DSString> DSStateKeyList;

#endif  // _DSSTATELIST_H_
