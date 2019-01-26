#ifndef _DSOPERANDOPERATOR_H_
#define _DSOPERANDOPERATOR_H_

#include "DSBasicTypes.h"
#include "DSOperand.h"
#include "DSActualParamComponent.h"

/************************************************************************
 * Classname: DSOperandOperator
 * Purpose:   Speicherung eines SDL-ADT-Operator-Aufrufs aus einer Expression
 * Z100:
 ************************************************************************/

class DSOperandOperator : public DSOperand,
                          public DSActualParamComponent
{
  public:
    DSOperandOperator(DSObject* = NULL,
                      DSOperatorRef = NULL,       // Operator
                      DSActualParamList* = NULL); // aktuelle Parameter
    ~DSOperandOperator(void);

    DSOperatorRef      GetOperatorRef(void) const;

    DSResult           SetOperatorRef(DSOperatorRef);

    DSObject          *New(DSObject * = NULL) const; // virtueller Konstruktor
    DSObject          *Clone(DSObject * = NULL,
                             DSObject * = NULL) const;
                                               // erzeugt eine identische
                                               // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult   Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult   Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSOperatorRef      operator_ref;
};

#endif
