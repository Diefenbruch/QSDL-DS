#ifndef _DSVARIABLEACCESSCOMPONENT_H_
#define _DSVARIABLEACCESSCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSVariableAccessList.h"

/************************************************************************
 * Classname: DSVariableAccessComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen Variablen-
 *            zugriffe vorkommen.
 ************************************************************************/

class DSVariableAccessComponent
{
  public:
    DSVariableAccessComponent(class DSObject* = NULL,       // Vaterobjekt
                              DSVariableAccessList* = NULL);
   ~DSVariableAccessComponent(void);

    DSVariableAccessList   *GetVariableAccessList(void) const;
    class DSVariableAccess *GetFirstVariableAccess(void) const;
    class DSVariableAccess *GetNextVariableAccess(void) const;

    DSResult                SetVariableAccessList(DSVariableAccessList*);
    DSResult                InsertVariableAccess(class DSVariableAccess*);

  protected:
    DSObject               *GetComponentParent(void) const;  // Vaterobject
    DSResult                SetComponentParent(const DSObject*);

  private:
    DSVariableAccessList *variable_access_list;
    class DSObject       *parent;
};

#endif

