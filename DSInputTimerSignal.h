#ifndef _DSINPUTTIMERSIGNAL_H_
#define _DSINPUTTIMERSIGNAL_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSRef.h"
#include "DSVariableAccessComponent.h"

/************************************************************************
 * Classname: DSInputTimerSignal
 * Purpose:   Speichert einen SDL Timer-Stimulus
 * Z100:      Seite 53 <stimulus>
 ************************************************************************/

class DSInputTimerSignal : public DSObject,
                           public DSVariableAccessComponent
{
  public:
    DSInputTimerSignal(DSObject*             = NULL, // Vaterobjekt
                       DSTimerRef            = NULL,
                       DSVariableAccessList* = NULL);
    virtual ~DSInputTimerSignal(void);

    DSTimerRef         GetTimerRef(void) const;

    DSResult           SetTimerRef(DSTimerRef);

    DSObject          *Clone(DSObject * = NULL,
                             DSObject * = NULL) const; 
                                               // erzeugt eine identische
                                               // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult   Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult   Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSTimerRef         timer_ref;
};

#endif
