#ifndef _DSPROCEDURELIST_H_
#define _DSPROCEDURELIST_H_

#include "DSList.h"
#include "DSKeyList.h"

class DSProcedure;
class DSString;

typedef DSList<DSProcedure> DSProcedureList;
typedef DSKeyList<DSProcedure, DSString> DSProcedureKeyList;

#endif  // _DSPROCEDURELIST_H_
