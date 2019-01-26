#ifndef _DSOPERAND_H_
#define _DSOPERAND_H_

#include "DSBasicTypes.h"
#include "DSObject.h"

/************************************************************************
 * Classname: DSOperand
 * Purpose:   Basisklasse fuer alle Operandenklassen
 ************************************************************************/

class DSOperand : public DSObject
{
  public:
    DSOperand(DSObject*,
              DSExpressionOperandTag = DS_OPN_CONSTANT);
    virtual ~DSOperand(void);
    
    DSExpressionOperandTag GetTag(void) const;
    DSResult               SetTag(DSExpressionOperandTag);
    
    DSObject      *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                                   // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSExpressionOperandTag tag;
};

#endif
