#ifndef _DSOPERANDEXPRESSION_H_
#define _DSOPERANDEXPRESSION_H_

#include "DSBasicTypes.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSOperandExpression
 * Purpose:   Definiton einer SDL-Ausdrucksoperanden (zur rekursiven
 *            Definition eines Ausdrucks)
 * Z100:
 ************************************************************************/

class DSOperandExpression : public DSOperand
{
  public:
    DSOperandExpression(DSObject* = NULL,
                        class DSExpression* = NULL);
    ~DSOperandExpression(void);
    
    class DSExpression *GetExpression(void) const;

    DSResult            SetExpression(class DSExpression *);

    DSObject *New(DSObject * = NULL) const;
    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    class DSExpression *expression;
};

#endif
