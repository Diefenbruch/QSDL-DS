#ifndef _DSOPERANDMACHINESERVICE_H_
#define _DSOPERANDMACHINESERVICE_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSOperandMachineService
 * Purpose:   Definiton eines QSDL-MachineService-Operanden (wird fuer Zugriffs-
 *            methoden auf Sensoren benoetigt)
 * Z100:      -
 ************************************************************************/

class DSOperandMachineService : public DSOperand
{
  public:
    DSOperandMachineService(DSObject*    = NULL,
                            DSMachineServiceRef = NULL);
    ~DSOperandMachineService(void);
    
    DSMachineServiceRef GetMachineServiceRef() const;

    DSResult            SetMachineServiceRef(DSMachineServiceRef);

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
    DSMachineServiceRef machine_service_ref;
};

#endif
