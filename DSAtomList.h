#ifndef _DSATOMLIST_H_
#define _DSATOMLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSAtom;
class DSString;

typedef DSList<DSAtom> DSAtomList;
typedef DSKeyList<DSAtom, DSString> DSAtomKeyList;

#endif  // _DSATOMLIST_H_
