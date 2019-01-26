#ifndef _DSMACHINESERVICEREFCOMPONENT_H_
#define _DSMACHINESERVICEREFCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSList.h"
#include "DSRef.h"

/************************************************************************
 * Classname: DSMachineServiceRefComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen QSDL-Dienstverweise
 *            definiert werden koennen.
 ************************************************************************/

class DSMachineServiceRefComponent
{
  public:
    DSMachineServiceRefComponent(DSMachineServiceRefList * = NULL);
   ~DSMachineServiceRefComponent(void);

    DSMachineServiceRefList *GetMachineServiceRefList(void) const;
    DSMachineServiceRef      GetFirstMachineServiceRef(void) const;
    DSMachineServiceRef      GetNextMachineServiceRef(void) const;

    DSResult                 SetMachineServiceRefList(DSMachineServiceRefList*);
    DSResult                 InsertMachineServiceRef(DSMachineServiceRef);

  private:
    DSMachineServiceRefList *machine_service_ref_list;     
};

#endif
