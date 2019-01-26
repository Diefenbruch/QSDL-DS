#ifndef _DSCHANNELREFCOMPONENT_H_
#define _DSCHANNELREFCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSList.h"
#include "DSRef.h"
 
/*******************************************************************************
 * Klasse DSChannelRefComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen die Kanalreferenzen
 *            enthalten.
 ******************************************************************************/

class DSChannelRefComponent
{
  public:
    DSChannelRefComponent(DSChannelRefList * = NULL);
   ~DSChannelRefComponent(void);

    DSChannelRefList *GetChannelRefList(void) const;
    DSChannelRef      GetFirstChannelRef(void) const;
    DSChannelRef      GetNextChannelRef(void) const;

    DSResult          SetChannelRefList(DSChannelRefList*);
    DSResult          InsertChannelRef(DSChannelRef);

  private:
    DSChannelRefList *channel_ref_list;
};

#endif  // ifndef
