#ifndef _DSOPERANDLITERAL_H_
#define _DSOPERANDLITERAL_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSOperandLiteral
 * Purpose:   Definiton eines SDL-Literalzugriffs
 * Z100:      
 ************************************************************************/

class DSOperandLiteral : public DSOperand
{
  public:
    DSOperandLiteral(DSObject* = NULL,      // Vaterobjekt, wird an DSOperand
                                            // weitergegeben
                     DSString* = NULL,      // Literalname
                     DSSortRef = NULL);     // Lietralsorte (DSSortExtended)
    DSOperandLiteral(DSObject*,             // Vaterobjekt, wird an DSOperand
                                            // weitergegeben
                     DSString&,
                     DSSortRef = NULL);     // Lietralsorte (DSSortExtended)
    DSOperandLiteral(DSObject*,             // Vaterobjekt, wird an DSOperand
                                            // weitergegeben
                     const char *,
                     DSSortRef = NULL);     // Lietralsorte (DSSortExtended)
   ~DSOperandLiteral(void);
    
    DSSortRef GetSortRef(void) const;
    DSString *GetName(void) const;

    DSResult  SetName(DSString*);
    DSResult  SetName(DSString&);
    DSResult  SetName(const char *);
    DSResult  SetSortRef(DSSortRef);

    DSObject *New(DSObject * = NULL) const;
    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSString *name;
    DSSortRef sort_ref;
};

#endif
