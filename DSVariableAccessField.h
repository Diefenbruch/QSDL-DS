#ifndef _DSVARIABLEACCESSFIELD_H_
#define _DSVARIABLEACCESSFIELD_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSVariableAccessElem.h"

/************************************************************************
 * Classname: DSVariableAccessField
 * Purpose:   Speicherung eines Feldzugriffs als Teil eines Variablenzugriff
 * Z100:
 ************************************************************************/

class DSVariableAccessField : public DSVariableAccessElem
{
  public:
    DSVariableAccessField(DSObject* = NULL,      // Vaterobjekt
                          DSNameSortRef = NULL); // Feldzugriff
    ~DSVariableAccessField(void);

    DSNameSortRef GetField(void) const;

    DSResult      SetField(DSNameSortRef);

    DSObject *New(DSObject * = NULL) const;         // virtueller Konstruktor
    DSObject *Clone(DSObject * = NULL,
                    DSObject * = NULL) const;       // erzeugt eine identische
                                                    // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSNameSortRef field_ref;
};

typedef DSList<DSVariableAccessField>  DSVariableAccessFieldList;

#endif
