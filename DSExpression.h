#ifndef _DSEXPRESSION_H_
#define _DSEXPRESSION_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSObject.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSExpression
 * Purpose:   Speichert eine SDL-Expression
 * Z100:      Seite 150
 ************************************************************************/

class DSExpression : public DSObject
{
  public:
    DSExpression(DSObject* = NULL,           // Vaterobjekt
                 class DSOperand* = NULL,
                 DSExpressionOperator = DS_OPT_NONE,
                 class DSOperand* = NULL,
                 DSSortRef  = NULL);
    DSExpression(DSExpression&);             // copy constructor

    virtual ~DSExpression(void);

    DSObject            *New(DSObject * = NULL) const;
    class DSOperand     *GetOperand1(void) const;
    class DSOperand     *GetOperand2(void) const;
    DSExpressionOperator GetOperator(void) const;
    DSSortRef            GetSortRef(void) const;

    DSBoolean            IsConstant(void) const;
    DSBoolean            IsZero(void) const;
    DSResult             SetOperand1(class DSOperand*);
    DSResult             SetOperand2(class DSOperand*);
    DSResult             SetOperator(DSExpressionOperator);
    DSResult             SetSortRef(DSSortRef);

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
    class DSOperand     *operand1;
    DSExpressionOperator op;        // in DSBasicTypes.h
    class DSOperand     *operand2;
    DSSortRef            sort_ref;
};

#endif
