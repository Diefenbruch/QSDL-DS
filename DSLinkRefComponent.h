#ifndef _DSLINKREFCOMPONENT_H_
#define _DSLINKREFCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSLink.h"
#include "DSList.h"

/******************************************************************************
 * Klasse:  DSLinkRefComponent
 * Aufgabe: Basisklasse fuer alle SDL-Strukturen die Link-Referenzen
 *          enthalten.
 ******************************************************************************/

class DSLinkRefComponent
{
  public:
    DSLinkRefComponent(DSLinkRefList * = NULL);
   ~DSLinkRefComponent(void);

    DSLinkRefList *GetLinkRefList(void) const;
    DSLinkRef      GetFirstLinkRef(void) const;
    DSLinkRef      GetNextLinkRef(void) const;

    DSResult       SetLinkRefList(DSLinkRefList*);
    DSResult       InsertLinkRef(DSLinkRef);

  private:
    DSLinkRefList *link_ref_list;
};

#endif
