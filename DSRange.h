#ifndef _DSRANGE_H_
#define _DSRANGE_H_

#include "DSBasicTypes.h"
#include "DSObject.h"

/************************************************************************
 * Classname: DSRange
 * Purpose:   Definition eines SDL-Wertebereichs. SDL unterscheidet offene
 *            und geschlossene Wertebereiche.
 * Z100:      Seite 136
 ************************************************************************/

class DSRange : public DSObject
{
  public:
    DSRange(DSObject*     = NULL,  // Vaterobjekt
            class DSExpression* = NULL,  // untere Grenze
            class DSExpression* = NULL,  // obere Grenze
            DSRangeOperator = DS_RANGE_OPT_NONE); // Operator fuer 'open range'
    DSRange(DSObject*,
            class DSExpression&,
            class DSExpression&,
            DSRangeOperator = DS_RANGE_OPT_NONE); // Operator fuer 'open range'
   ~DSRange(void);

    DSObject           *New(DSObject * = NULL) const;  // virtueller Konstruktor

    class DSExpression *GetLowerBound(void) const;
    class DSExpression *GetUpperBound(void) const;
    DSRangeOperator     GetRangeOperator(void) const;

    DSResult            SetLowerBound(class DSExpression*);
    DSResult            SetUpperBound(class DSExpression*);
    DSResult            SetRangeOperator(DSRangeOperator);

    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    class DSExpression *lower_bound;    // ist bei 'open range' = NULL !
    class DSExpression *upper_bound;    // ist immer gesetzt!
    DSRangeOperator    range_operator; // ist bei 'closed range' =
                                    // DS_RANGE_OPT_NONE
};

#endif
