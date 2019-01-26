#ifndef _DSLINKLIST_H_
#define _DSLINKLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSLink;
class DSString;

typedef DSList<DSLink> DSLinkList;
typedef DSKeyList<DSLink, DSString> DSLinkKeyList;

#endif  // _DSLINKLIST_H_
