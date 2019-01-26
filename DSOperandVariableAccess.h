#ifndef _DSOPERANDVARIABLEACCESS_H_
#define _DSOPERANDVARIABLEACCESS_H_

#include "DSBasicTypes.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSOperandVariableAccess
 * Purpose:   Definiton einer SDL-Variablenoperanden
 * Z100:
 ************************************************************************/

class DSOperandVariableAccess : public DSOperand
{
  public:
    DSOperandVariableAccess(DSObject* = NULL,
                            class DSVariableAccess* = NULL);
    ~DSOperandVariableAccess(void);
    
    class DSVariableAccess *GetVariableAccess(void) const;

    DSResult                SetVariableAccess(DSVariableAccess*);
        
    DSObject *New(DSObject * = NULL) const;
    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    class DSVariableAccess *variable_access;
};

#endif
