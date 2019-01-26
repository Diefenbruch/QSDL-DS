#ifndef _DSACTUALPARAMCOMPONENT_H_
#define _DSACTUALPARAMCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSActualParamList.h"
 
/*****************************************************************************
 * Klasse:  DSActualParamComponent
 * Aufgabe: Basisklasse fuer alle SDL-Strukturen die aktuelle SDL-
 *          Parameter erwarten.
 ****************************************************************************/

class DSActualParamComponent
{
  public:
    DSActualParamComponent(class DSObject * = NULL,
                           DSActualParamList* = NULL);
   ~DSActualParamComponent(void);

    DSActualParamList   *GetActualParamList(void) const;
    DSActualParam       *GetFirstActualParam(void) const;
    DSActualParam       *GetNextActualParam(void) const;

    DSResult             SetActualParamList(DSActualParamList*);
    DSResult             InsertActualParam(DSActualParam*);

  protected:
    DSObject            *GetComponentParent(void) const;  // Vaterobject
    DSResult             SetComponentParent(const DSObject*);

  private:
    DSActualParamList   *actual_param_list;
    class DSObject      *parent;
};

#endif  // ifndef
