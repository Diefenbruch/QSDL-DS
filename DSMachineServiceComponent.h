#ifndef _DSMACHINESERVICECOMPONENT_H_
#define _DSMACHINESERVICECOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSMachineServiceList.h"

/************************************************************************
 * Classname: DSMachineServiceComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen QSDL-Dienste
 *            definiert werden koennen.
 ************************************************************************/

class DSMachineServiceComponent
{
  public:
    DSMachineServiceComponent(class DSObject * = NULL);
   ~DSMachineServiceComponent(void);

    DSMachineServiceKeyList *GetMachineServiceList(void) const;
    class DSMachineService  *GetMachineService(class DSString*) const;
    class DSMachineService  *GetMachineService(class DSString&) const;
    class DSMachineService  *GetMachineService(const char *) const;
    class DSMachineService  *GetFirstMachineService(void) const;
    class DSMachineService  *GetNextMachineService(void) const;

    DSResult                 SetMachineServiceList(DSMachineServiceKeyList*);
    DSResult                 InsertMachineService(class DSMachineService*);

  protected:
    DSObject                *GetComponentParent(void) const;  // Vaterobject
    DSResult                 SetComponentParent(const DSObject*);

  private:
    DSMachineServiceKeyList *machineservice_definition_list;
    class DSObject          *parent;
};

#endif
