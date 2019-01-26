#ifndef _DSNEXTSTATE_H_
#define _DSNEXTSTATE_H_

#include "DSBasicTypes.h"
#include "DSRef.h" 
#include "DSAction.h"
  
/******************************************************************************
 * Klasse DSNextState
 * Zweck: Datenstruktur zur Speicherung der Parameter fuer eine NEXTSTATE-
 *        Instruktion.
 * Z100:  Seite 59
 ******************************************************************************/

class DSNextState : public DSAction
{
  public:
    DSNextState (DSObject* = NULL,      // Vaterobjekt
                 DSString* =     NULL,  // optionales Label
                 DSStateRef =    NULL); // naechster Zustand
    DSNextState (DSObject*,
                 DSString&,
                 DSStateRef =    NULL);
    DSNextState (DSObject*,
                 const char *,
                 DSStateRef =    NULL);
    ~DSNextState(void);

    DSObject *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSStateRef        GetNextStateRef(void) const;

    DSResult          SetNextStateRef(DSStateRef);

    DSObject         *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSStateRef next_state_ref;
};
 
#endif // ifndef
