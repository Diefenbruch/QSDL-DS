#ifndef _DSMACHINECOMPONENT_H_
#define _DSMACHINECOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSMachineList.h"

/************************************************************************
 * Classname: DSMachineComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen QSDL-Maschinen
 *            definiert werden koennen.
 ************************************************************************/

class DSMachineComponent
{
  public:
    DSMachineComponent(class DSObject * = NULL);
   ~DSMachineComponent(void);

    DSMachineKeyList *GetMachineList(void) const;
    class DSMachine  *GetMachine(class DSString*) const;
    class DSMachine  *GetMachine(class DSString&) const;
    class DSMachine  *GetMachine(const char *) const;
    class DSMachine  *GetFirstMachine(void) const;
    class DSMachine  *GetNextMachine(void) const;

    DSResult          SetMachineList(DSMachineKeyList*);
    DSResult          InsertMachine(class DSMachine*);

  protected:
    DSObject         *GetComponentParent(void) const;  // Vaterobject
    DSResult          SetComponentParent(const DSObject*);

  private:
    DSMachineKeyList *machine_definition_list;
    class DSObject   *parent;
};

#endif
