#ifndef _DSVARIABLEACCESSINDEX_H_
#define _DSVARIABLEACCESSINDEX_H_

#include "DSBasicTypes.h"
#include "DSVariableAccessElem.h"

/************************************************************************
 * Classname: DSVariableAccessIndex
 * Purpose:   Speicherung eines Indexzugriffs als Teil eines Variablenzugriff
 * Z100:
 ************************************************************************/

class DSVariableAccessIndex : public DSVariableAccessElem
{
  public:
    DSVariableAccessIndex(DSObject* = NULL,      // Vaterobjekt
                          DSExpression* = NULL); // Index
    ~DSVariableAccessIndex(void);

    class DSExpression *GetIndex(void) const;
    DSResult            SetIndex(class DSExpression*);

    DSObject           *New(DSObject * = NULL) const;
    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const; // erzeugt eine identische
                                                        // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    class DSExpression *array_index;
};

#endif
