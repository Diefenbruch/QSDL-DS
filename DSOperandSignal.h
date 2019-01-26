#ifndef _DSOPERANDSIGNAL_H_
#define _DSOPERANDSIGNAL_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSOperandSignal
 * Purpose:   Definiton eines SDL-Signals
 * Z100:
 ************************************************************************/

class DSOperandSignal : public DSOperand
{
  public:
    DSOperandSignal(DSObject*    = NULL,
                     DSSignalRef = NULL);
    ~DSOperandSignal(void);
    
    DSSignalRef      GetSignalRef() const;

    DSResult         SetSignalRef(DSSignalRef);

    DSObject *New(DSObject * = NULL) const;
    DSObject *Clone(DSObject * = NULL,
                    DSObject * = NULL) const;      // erzeugt eine identische
                                                   // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSSignalRef signal_ref;
};

#endif
