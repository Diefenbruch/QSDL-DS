#ifndef _DSOPERANDSTATE_H_
#define _DSOPERANDSTATE_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSOperandState
 * Purpose:   Definiton eines SDL-States
 * Z100:
 ************************************************************************/

class DSOperandState : public DSOperand
{
  public:
    DSOperandState(DSObject*    = NULL,
                   DSStateRef = NULL);
    ~DSOperandState(void);
    
    DSStateRef      GetStateRef() const;

    DSResult        SetStateRef(DSStateRef);

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
    DSStateRef state_ref;
};

#endif
