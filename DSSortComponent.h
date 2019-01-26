#ifndef _DSSORTCOMPONENT_H_
#define _DSSORTCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSSortList.h"
#include "DSRef.h"

/************************************************************************
 * Classname: DSSortComponent
 * Purpose:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Datentypen
 *            definiert werden koennen.
 * Z100:
 ************************************************************************/

class DSSortComponent
{
  protected:
    DSSortComponent(class DSObject * = NULL);

  public:
   ~DSSortComponent(void);

    DSSortKeyList       *GetSortList(void) const;
    class DSSort        *GetSort(class DSString*) const;
    class DSSort        *GetSort(class DSString&) const;
    class DSSort        *GetSort(const char *) const;
    class DSSort        *GetFirstSort(void) const;
    class DSSort        *GetNextSort(void) const;
    class DSSort        *GetLiteralSort(class DSString*) const;
    class DSSort        *GetLiteralSort(class DSString&) const;
    class DSSort        *GetLiteralSort(const char *) const;
    class DSSort        *GetOperatorSort(class DSString*,
                                         DSSortRefList * = NULL) const;
    class DSSort        *GetOperatorSort(class DSString&,
                                         DSSortRefList * = NULL) const;
    class DSSort        *GetOperatorSort(const char *,
                                         DSSortRefList * = NULL) const;

    DSResult             SetSortList(DSSortKeyList*);
    DSResult             InsertSort(class DSSort*);

  protected:
    DSObject            *GetComponentParent(void) const;  // Vaterobject
    DSResult             SetComponentParent(const DSObject*);

  private:
    DSSortKeyList       *sort_definition_list;
    class DSObject      *parent;
};

#endif
