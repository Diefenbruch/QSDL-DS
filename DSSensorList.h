#ifndef _DSSENSORLIST_H_
#define _DSSENSORLIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSSensor;
class DSString;

typedef DSList<DSSensor> DSSensorList;
typedef DSKeyList<DSSensor, DSString> DSSensorKeyList;

#endif  // _DSSENSORLIST_H_
