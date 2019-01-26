#ifndef _DSUPDATE_H_
#define _DSUPDATE_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSAction.h"

/******************************************************************************
 *  Klasse DSUpdate
 *  Zweck: Datenstruktur zur Speicherung der Parameter fuer eine QSDL-UPDATE-
 *         Aktion (Updaten eines Sensors).
 *  Z100:  -
 ******************************************************************************/

class DSUpdate : public DSAction
{
  public:
    DSUpdate(DSObject* = NULL,           // Vater-Objekt
             DSString* = NULL,           // Label
             DSSensorRef = NULL,         // Sensor
             class DSExpression* = NULL,       // Sample
             class DSExpression* = NULL);      // Value (only for frequency sensors)
    DSUpdate(DSObject*,
             DSString&, 
             DSSensorRef = NULL,            
             class DSExpression* = NULL,         
             class DSExpression* = NULL);      // Value (only for frequency sensors)
    DSUpdate(DSObject*,
             const char * = NULL, 
             DSSensorRef = NULL,               
             class DSExpression* = NULL,
             class DSExpression* = NULL);      // Value (only for frequency sensors)
    ~DSUpdate(void);

    DSSensorRef         GetSensorRef(void) const;
    class DSExpression *GetSample(void) const;
    class DSExpression *GetValue(void) const;

    DSResult            SetSensorRef(DSSensorRef);
    DSResult            SetSample(DSExpression*);
    DSResult            SetValue(DSExpression*);
     
    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const; // erzeugt eine identische
                 				                          // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult  Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSSensorRef         sensor_ref;
    class DSExpression *sample;
    class DSExpression *value;
};

#endif  // ifndef
