#ifndef _DSATOM_H_
#define _DSATOM_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSNamedObject.h"

/************************************************************************
 * Classname: DSAtom
 * Purpose:   Speicherung einer Atomdeklaration fuer die Verifikation
 * Z100:      -
 ************************************************************************/

class DSAtom : public DSNamedObject
{
  public:
    DSAtom(DSObject*,                    // Vaterobjekt
           class DSString* = NULL,       // Name des Atoms
           class DSExpression* = NULL);  // Initialisierung
    DSAtom(DSObject*,                    // Vaterobjekt
           class DSString&,              // Name des Atoms
           class DSExpression*);         // Initialisierung
    DSAtom(DSObject*,                    // Vaterobjekt
           const char *,                 // Name des Atoms
           class DSExpression*);         // Initialisierung
    virtual ~DSAtom(void);

    DSObject           *New(DSObject * = NULL) const;  // virtueller Konstruktor

    class DSExpression *GetProposition(void) const;

    DSResult            SetProposition(class DSExpression*);

    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const;
                                              // erzeugt eine identische
                                              // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    class DSExpression *proposition;
};

#endif
