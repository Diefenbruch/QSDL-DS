#ifndef _DSVARIABLELIST_H_
#define _DSVARIABLELIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSVariable;
class DSString;

typedef DSList<DSVariable> DSVariableList;
typedef DSKeyList<DSVariable, DSString> DSVariableKeyList;

#endif  // _DSVARIABLELIST_H_
