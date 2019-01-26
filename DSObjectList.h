#ifndef _DSOBJECTLIST_H_
#define _DSOBJECTLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSObject;
class DSString;

typedef DSList<DSObject> DSObjectList;
typedef DSKeyList<DSObject, DSString> DSObjectKeyList;

#endif  // _DSOBJECTLIST_H_
