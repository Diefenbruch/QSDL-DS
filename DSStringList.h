#ifndef _DSSTRINGLIST_H_
#define _DSSTRINGLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSString;

typedef DSList<DSString> DSStringList;
typedef DSKeyList<DSString, DSString> DSStringKeyList;

#endif  // _DSSTRINGLIST_H_
