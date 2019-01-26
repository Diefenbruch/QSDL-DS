#ifndef _DSPROCESSACCESS_H_
#define _DSPROCESSACCESS_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSObject.h"

/************************************************************************
 * Classname: DSProcessAccess
 * Purpose:   Speicherung eines Prozesszugriffs
 * Z100:
 ************************************************************************/

class DSProcessAccess : public DSObject
{
  public:
    DSProcessAccess(DSObject* = NULL,          // Vaterobjekt
                    DSProcessRef = NULL,       // Referenz auf Prozess
                    DSExpression* = NULL,      // Identifizierungsnummer
                    class DSVariableAccess* = NULL); // Variablenzugriff
    DSProcessAccess(DSObject*,                 // Vaterobjekt
                    DSProcessRef,              // Referenz auf Prozess
                    DSExpression*,             // Identifizierungsnummer
                    DSSensorRef);              // Referenz auf Sensor
    virtual ~DSProcessAccess(void);

    DSProcessRef        GetProcessRef(void) const;
    class DSVariableAccess *  GetVariableAccess(void) const;
    DSSensorRef         GetSensorRef(void) const;
    class DSExpression *GetProcessID(void) const;

    DSResult            SetProcessRef(DSProcessRef);
    DSResult            SetVariableAccess(DSVariableAccess*);
    DSResult            SetSensorRef(DSSensorRef);
    DSResult            SetProcessID(class DSExpression*);

    DSObject           *New(DSObject * = NULL) const;
    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const;
                                                     // erzeugt eine identische
                                                     // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult    Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult    Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSProcessRef        process_ref;
    class DSExpression *pid;
    class DSVariableAccess *variable_access;
    DSSensorRef         sensor_ref;
};

#endif
