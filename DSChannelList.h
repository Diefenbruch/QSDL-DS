#ifndef _DSCHANNELLIST_H_
#define _DSCHANNELLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSChannel;
class DSString;

typedef DSList<DSChannel> DSChannelList;
typedef DSKeyList<DSChannel, DSString> DSChannelKeyList;

#endif  // _DSCHANNELLIST_H_
