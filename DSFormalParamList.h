#ifndef _DSFORMALPARAMLIST_H_
#define _DSFORMALPARAMLIST_H_

#include "DSList.h"
#include "DSKeyList.h"
#include "DSFormalParam.h"

class DSString;

typedef DSList<DSFormalParam> DSFormalParamList;
typedef DSKeyList<DSFormalParam, DSString> DSFormalParamKeyList;

#endif  // _DSFORMALPARAMLIST_H_
