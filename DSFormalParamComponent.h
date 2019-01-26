#ifndef _DSFORMALPARAMCOMPONENT_H_
#define _DSFORMALPARAMCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSFormalParamList.h"

/************************************************************************
 * Classname: DSFormalParamComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen die formale SDL-
 *            Parameter erwarten.
 ************************************************************************/

class DSFormalParamComponent
{
  public:
    DSFormalParamComponent(class DSObject * = NULL);
   ~DSFormalParamComponent(void);

    DSFormalParamKeyList *GetFormalParamList(void) const;
    DSFormalParam        *GetFormalParam(class DSString*) const;
    DSFormalParam        *GetFormalParam(class DSString&) const;
    DSFormalParam        *GetFormalParam(const char *) const;
    DSFormalParam        *GetFirstFormalParam(void) const;
    DSFormalParam        *GetNextFormalParam(void) const;

    DSResult              SetFormalParamList(DSFormalParamKeyList*);
    DSResult              InsertFormalParam(DSFormalParam*);

  protected:
    DSObject             *GetComponentParent(void) const;  // Vaterobject
    DSResult              SetComponentParent(const DSObject*);

  private:
    DSFormalParamKeyList *formal_param_list;
    class DSObject       *parent;
};

#endif
