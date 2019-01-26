#ifndef _DSOPERANDSYNONYM_H_
#define _DSOPERANDSYNONYM_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSOperandSynonym
 * Purpose:   Definiton eines SDL-Synonyms
 * Z100:
 ************************************************************************/

class DSOperandSynonym : public DSOperand
{
  public:
    DSOperandSynonym(DSObject*    = NULL,
                     DSSynonymRef = NULL);
    ~DSOperandSynonym(void);
    
    DSSynonymRef      GetSynonymRef() const;

    DSResult          SetSynonymRef(DSSynonymRef);

    DSObject *New(DSObject * = NULL) const;
    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSSynonymRef synonym_ref;
};

#endif
