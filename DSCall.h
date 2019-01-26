#ifndef _DSCALL_H_
#define _DSCALL_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSAction.h"
#include "DSActualParamComponent.h"

/******************************************************************************
 * Klasse: DSCall
 * Zweck:  Datenstruktur zur Speicherung der Parameter fuer eine CALL-
 *         Instruktion.
 * Z100:   Seite 64
 ******************************************************************************/

class DSCall : public DSAction,
               public DSActualParamComponent
{
  public:
    DSCall(DSObject*,
           DSString*          = NULL,                   // Label
           DSProcedureRef     = NULL,
           DSActualParamList* = NULL);
    DSCall(DSObject*,
           DSString&,                    
           DSProcedureRef     = NULL,
           DSActualParamList* = NULL);
    DSCall(DSObject*,
           const char *,                    
           DSProcedureRef     = NULL,
           DSActualParamList* = NULL);
   ~DSCall(void);

    DSProcedureRef     GetProcedureRef(void) const;

    DSResult           SetProcedureRef(DSProcedureRef);

    DSObject  *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                               // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult   Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult   Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSProcedureRef     procedure_ref;
};
 
#endif // ifndef
