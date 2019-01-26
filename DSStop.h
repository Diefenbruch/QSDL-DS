#ifndef _DSSTOP_H_
#define _DSSTOP_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSObject.h"
#include "DSAction.h"

/*****************************************************************************
 * Klasse DSStop
 * Zweck: Datenstruktur zur Speicherung der Parameter fuer eine STOP-
 *        Instruktion von Prozessen.
 * Z100:  Seite 60
 *****************************************************************************/

class DSStop : public DSAction
{
  public:
    DSStop(DSObject*,                    // Vaterobjekt
           DSString* = NULL);            // Label
    DSStop(DSObject*,                    // Vaterobjekt
           DSString&);
    DSStop(DSObject*,                    // Vaterobjekt
           const char *);
   ~DSStop(void);

    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;
};

#endif // ifndef
