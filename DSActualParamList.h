#ifndef _DSACTUALPARAMLIST_H_
#define _DSACTUALPARAMLIST_H_

#include "DSList.h"
#include "DSKeyList.h"
#include "DSActualParam.h"

class DSString;

typedef DSList<DSActualParam> DSActualParamList;
typedef DSKeyList<DSActualParam, DSString> DSActualParamKeyList;

#endif  // _DSACTUALPARAMLIST_H_
