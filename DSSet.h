#ifndef _DSSET_H_
#define _DSSET_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSAction.h"
#include "DSActualParamComponent.h"
#include "DSExpressionList.h"

/******************************************************************************
 *  Klasse DSSet
 *  Zweck: Datenstruktur zur Speicherung der Parameter fuer eine SDL-SET-
 *         Instruktion.
 *  Z100:  Seite 70
 ******************************************************************************/

class DSSet : public DSAction,
              public DSActualParamComponent // Timer-Parameter
{
  public:
    DSSet(DSObject* = NULL,
          DSString* = NULL,           // Label
          DSTimerRef = NULL,              
          DSExpressionList* = NULL,   // Indizes
          class DSExpression* = NULL);      // Zeit
    DSSet(DSObject*,
          DSString&, 
          DSTimerRef = NULL,            
          DSExpressionList* = NULL,  
          class DSExpression* = NULL);         
    DSSet(DSObject*,
          const char * = NULL, 
          DSTimerRef = NULL,               
          DSExpressionList * = NULL,   
          class DSExpression* = NULL);
    ~DSSet(void);

    DSTimerRef          GetTimerRef(void) const;
    class DSExpression *GetTime(void) const;

    DSResult            SetTimerRef(DSTimerRef);
    DSResult            SetTime(DSExpression*);
     
    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult    Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult    Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSTimerRef          timer_ref;
    class DSExpression *time;
};

#endif  // ifndef
