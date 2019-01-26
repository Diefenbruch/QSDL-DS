#ifndef _DSPROCEDURECOMPONENT_H_
#define _DSPROCEDURECOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSProcedureList.h"

/************************************************************************
 * Classname: DSProcedureComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Prozeduren
 *            definiert werden koennen.
 ************************************************************************/

class DSProcedureComponent
{
  protected:
    DSProcedureComponent(class DSObject * = NULL);

  public:
   ~DSProcedureComponent(void);

    DSProcedureKeyList *GetProcedureList(void) const;
    class DSProcedure  *GetProcedure(class DSString*) const;
    class DSProcedure  *GetProcedure(class DSString&) const;
    class DSProcedure  *GetProcedure(const char *) const;
    class DSProcedure  *GetFirstProcedure(void) const;
    class DSProcedure  *GetNextProcedure(void) const;

    DSResult            SetProcedureList(DSProcedureKeyList*);
    DSResult            InsertProcedure(class DSProcedure*);

  protected:
    DSObject           *GetComponentParent(void) const;  // Vaterobject
    DSResult            SetComponentParent(const DSObject*);

  private:
    DSProcedureKeyList *procedure_definition_list;
    class DSObject     *parent;
};

#endif
