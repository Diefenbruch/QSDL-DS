#ifndef _DSOPERATOR_H_
#define _DSOPERATOR_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSSortRefComponent.h"

/************************************************************************
 * Classname: DSOperator
 * Purpose:   Definition eines SDL-Datentypoperators.
 * Z100:      Seite 120
 ************************************************************************/

class DSOperator : public DSNamedObject,
                   public DSSortRefComponent  // Parametersorten
{
  public:
    DSOperator(DSObject* = NULL,                /* Vaterobjekt               */
               DSString* = NULL,                /* Name des Operators        */
               DSSortRefList* = NULL,           /* Parametertypen            */
               DSSortRef = NULL);               /* Ergebnistyp               */
    DSOperator(DSObject*,                       /* Vaterobjekt               */
               DSString&,                       /* Name des Operators        */
               DSSortRefList* = NULL,           /* Parametertypen            */
               DSSortRef = NULL);               /* Ergebnistyp               */
    DSOperator(DSObject*,                       /* Vaterobjekt               */
               const char *,                    /* Name des Operators        */
               DSSortRefList* = NULL,           /* Parametertypen            */
               DSSortRef = NULL);               /* Ergebnistyp               */
    virtual ~DSOperator(void);
    
    DSObject *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSSortRef         GetResultSortRef(void) const;

    DSResult          SetResultSortRef(DSSortRef);
        
    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSSortRef      result_sort_ref;
};

#endif
