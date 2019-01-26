#ifndef _DSOPERANDCONSTANT_H_
#define _DSOPERANDCONSTANT_H_

#include "DSBasicTypes.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSOperandConstant
 * Purpose:   Definiton einer SDL-Konstanten (textuell oder numerisch)
 * Z100:      
 ************************************************************************/

class DSOperandConstant : public DSOperand
{
  public:
    DSOperandConstant(DSObject* = NULL,      // Vaterobjekt, wird an DSOperand
                                             // weitergegeben
                      DSString* = NULL,      // Konstante
                      DSBoolean = DS_TRUE);  // numerisch (ja/nein)
    DSOperandConstant(DSObject*,             // Vaterobjekt, wird an DSOperand
                                             // weitergegeben
                      DSString&,
                      DSBoolean = DS_TRUE);
    DSOperandConstant(DSObject*,             // Vaterobjekt, wird an DSOperand
                                             // weitergegeben
                      const char *,
                      DSBoolean = DS_TRUE);
   ~DSOperandConstant(void);
    
    DSString *GetConstant(void) const;
    DSBoolean GetIsNumeric(void) const;

    DSResult  SetConstant(DSString*);
    DSResult  SetConstant(DSString&);
    DSResult  SetConstant(const char *);
    DSResult  SetIsNumeric(DSBoolean);

    DSObject *New(DSObject * = NULL) const;
    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;     // erzeugt eine identische
                                             // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSString *constant;
    DSBoolean numeric;
};

#endif
