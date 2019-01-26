#ifndef _DSPIPEREFCOMPONENT_H_
#define _DSPIPEREFCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSPipe.h"
#include "DSList.h"

/******************************************************************************
 * Klasse:  DSPipeRefComponent
 * Aufgabe: Basisklasse fuer alle SDL-Strukturen die Pipereferenzen
 *          enthalten.
 ******************************************************************************/

class DSPipeRefComponent
{
  public:
    DSPipeRefComponent(DSPipeRefList * = NULL);
   ~DSPipeRefComponent(void);

    DSPipeRefList *GetPipeRefList(void) const;
    DSPipeRef      GetFirstPipeRef(void) const;
    DSPipeRef      GetNextPipeRef(void) const;

    DSResult       SetPipeRefList(DSPipeRefList*);
    DSResult       InsertPipeRef(DSPipeRef);

  private:
    DSPipeRefList *pipe_ref_list;
};

#endif
