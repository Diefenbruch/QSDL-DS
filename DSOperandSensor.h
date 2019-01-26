#ifndef _DSOPERANDSENSOR_H_
#define _DSOPERANDSENSOR_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSOperandSensor
 * Purpose:   Definiton eines QSDL-Sensor-Operanden (wird fuer Zugriffs-
 *            methoden auf den Sensor benoetigt)
 * Z100:      -
 ************************************************************************/

class DSOperandSensor : public DSOperand
{
  public:
    DSOperandSensor(DSObject*    = NULL,
                     DSSensorRef = NULL);
    ~DSOperandSensor(void);
    
    DSSensorRef      GetSensorRef() const;

    DSResult          SetSensorRef(DSSensorRef);

    DSObject *New(DSObject * = NULL) const;
    DSObject *Clone(DSObject * = NULL,
                    DSObject * = NULL) const; // erzeugt eine identische
                                              // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSSensorRef sensor_ref;
};

#endif
