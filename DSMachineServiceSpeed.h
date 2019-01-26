#ifndef _DSMACHINESERVICESPEED_H_
#define _DSMACHINESERVICESPEED_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSRef.h"

/************************************************************************
 * Classname: DSMachineServiceSpeed
 * Purpose:   Zuordnung von Dienstnamen zu Geschwindigkeiten.
 *            Hilfsklasse fuer DSMachine
 ************************************************************************/
 
class DSMachineServiceSpeed : public DSObject
{
  public:
    DSMachineServiceSpeed(DSObject* = NULL,
                          DSMachineServiceRef = NULL,
                          class DSExpression* = NULL);
    virtual ~DSMachineServiceSpeed(void);

    DSMachineServiceRef  GetMachineServiceRef(void) const;
    class DSExpression  *GetSpeed(void) const;

    DSResult             SetMachineServiceRef(DSMachineServiceRef);
    DSResult             SetSpeed(class DSExpression*);

    DSObject            *Clone(DSObject * = NULL,
                               DSObject * = NULL) const;
                                                 // erzeugt eine identische
                                                 // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult     Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSMachineServiceRef service_ref;
    class DSExpression *speed;
};

#endif
