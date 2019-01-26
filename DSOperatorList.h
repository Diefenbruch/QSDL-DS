#ifndef _DSOPERATORLIST_H_
#define _DSOPERATORLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSOperator;
class DSString;

typedef DSList<DSOperator> DSOperatorList;
typedef DSKeyList<DSOperator, DSString> DSOperatorKeyList;

#endif  // _DSOPERATORLIST_H_
