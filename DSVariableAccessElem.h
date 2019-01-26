#ifndef _DSVARIABLEACCESSELEM_H_
#define _DSVARIABLEACCESSELEM_H_

#include "DSBasicTypes.h"
#include "DSObject.h"

/************************************************************************
 * Classname: DSVariableAccessElem
 * Purpose:   Speicherung eines Elementes von einem Variablenzugriff
 *            Basisklasse fuer DSVariableAccessField und DSVariableAccessIndex.
 * Z100:
 ************************************************************************/

class DSVariableAccessElem : public DSObject
{
  public:
    virtual            ~DSVariableAccessElem(void);

    DSVariableAccessTag GetTag(void) const;
    DSResult            SetTag(DSVariableAccessTag);

    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const;
                                                     // erzeugt eine identische
                                                     // Kopie dieses Objekts
                                                     // (muss hier nur fuer
                                                     // CGAction deklariert werden)
    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  protected:
    DSVariableAccessElem(DSObject* = NULL,          // Vaterobjekt
                         DSVariableAccessTag = DS_ACCESS_FIELD);
                                                    // Typ (Index oder Feld)

  private:
    DSVariableAccessTag tag;
};

#endif
