#ifndef _DSPIPELIST_H_
#define _DSPIPELIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSPipe;
class DSString;

typedef DSList<DSPipe> DSPipeList;
typedef DSKeyList<DSPipe, DSString> DSPipeKeyList;

#endif  // _DSPIPELIST_H_
