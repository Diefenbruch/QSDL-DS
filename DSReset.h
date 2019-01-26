#ifndef _DSRESET_H_
#define _DSRESET_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSAction.h"
#include "DSActualParamComponent.h"
#include "DSExpressionList.h"
 
/*****************************************************************************
 * Klasse DSReset
 * Zweck: Datenstruktur zur Speicherung der Parameter fuer eine SDL-RESET-
 *        Instruktion.
 * Z100:  Seite 70
 *****************************************************************************/

class DSReset : public DSAction,
                public DSActualParamComponent
{
  public:
    DSReset(DSObject*,
            DSString*         = NULL,     // Label
            DSTimerRef        = NULL,     // Timer-Objekt
            DSExpressionList* = NULL);    // Indizes
    DSReset(DSObject*,
            DSString&,
            DSTimerRef        = NULL,
            DSExpressionList* = NULL);
    DSReset(DSObject*,
            const char *,
            DSTimerRef        = NULL,
            DSExpressionList* = NULL);
    ~DSReset(void);

    DSTimerRef        GetTimerRef(void) const;

    DSResult          SetTimerRef(DSTimerRef);
     
    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult  Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSTimerRef        timer_ref;
};

#endif  // ifndef
