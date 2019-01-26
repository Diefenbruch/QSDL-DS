#ifndef _DSVARIABLECOMPONENT_H_
#define _DSVARIABLECOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSVariableList.h"

/************************************************************************
 * Classname: DSVariableComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Variablen
 *            deklariert werden koennen.
 ************************************************************************/

class DSVariableComponent
{
  protected:
    DSVariableComponent(class DSObject * = NULL);

  public:
   ~DSVariableComponent(void);

    DSVariableKeyList *GetVariableList(void) const;
    class DSVariable  *GetVariable(DSString*) const;
    class DSVariable  *GetVariable(DSString&) const;
    class DSVariable  *GetVariable(const char *) const;
    class DSVariable  *GetFirstVariable(void) const;
    class DSVariable  *GetNextVariable(void) const;

    DSResult           SetVariableList(DSVariableKeyList*);
    DSResult           InsertVariable(class DSVariable*);

    DSBoolean          HasNonConstantVariables(void) const;
    
  protected:
    DSObject          *GetComponentParent(void) const;  // Vaterobject
    DSResult           SetComponentParent(const DSObject*);

  private:
    DSVariableKeyList *variable_definition_list;
    class DSObject    *parent;
};

#endif
