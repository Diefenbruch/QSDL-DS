#ifndef _DSCLEAR_H_
#define _DSCLEAR_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSAction.h"
 
/*****************************************************************************
 * Klasse DSClear
 * Zweck: Datenstruktur zur Speicherung der Parameter fuer eine QSDL-CLEAR-
 *        Instruktion (Ruecksetzen von QSDL-Sensoren).
 * Z100:  -
 *****************************************************************************/

class DSClear : public DSAction
{
  public:
    DSClear(DSObject*,
            DSString*         = NULL,     // Label
            DSSensorRef       = NULL);    // Sensor-Objekt
    DSClear(DSObject*,
            DSString&,
            DSSensorRef       = NULL);
    DSClear(DSObject*,
            const char *,
            DSSensorRef       = NULL);
    ~DSClear(void);

    DSSensorRef       GetSensorRef(void) const;

    DSResult          SetSensorRef(DSSensorRef);
     
    DSObject *Clone(DSObject * = NULL,
                    DSObject * = NULL) const; // erzeugt eine identische
                                              // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult  Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSSensorRef        sensor_ref;
};

#endif  // ifndef
