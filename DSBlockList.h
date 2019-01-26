#ifndef _DSBLOCKLIST_H_
#define _DSBLOCKLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSBlock;
class DSString;

typedef DSList<DSBlock> DSBlockList;
typedef DSKeyList<DSBlock, DSString> DSBlockKeyList;

#endif  // _DSBLOCKLIST_H_
