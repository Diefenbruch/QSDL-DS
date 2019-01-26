#ifndef _DSNAMESORTLIST_H_
#define _DSNAMESORTLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSNameSort;
class DSString;

typedef DSList<DSNameSort> DSNameSortList;
typedef DSKeyList<DSNameSort, DSString> DSNameSortKeyList;

#endif  // _DSNAMESORTLIST_H_
