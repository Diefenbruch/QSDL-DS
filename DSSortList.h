#ifndef _DSSORTLIST_H_
#define _DSSORTLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSSort;
class DSString;

typedef DSList<DSSort> DSSortList;
typedef DSKeyList<DSSort, DSString> DSSortKeyList;

#endif  // _DSSORTLIST_H_
