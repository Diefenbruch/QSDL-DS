#ifndef _DSVARIABLE_H_
#define _DSVARIABLE_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSNamedObject.h"

/************************************************************************
 * Classname: DSVariable
 * Purpose:   Speicherung einer Variablendeklaration oder von formalen
 *            Parametern
 * Z100:      Seite 49
 ************************************************************************/

class DSVariable : public DSNamedObject
{
  public:
    DSVariable(DSObject*,              // Vaterobjekt
               class DSString* = NULL, // Name der Variablen
               DSSortRef = NULL,       // Datentyp
               DSExpression* = NULL,   // Initialisierung
               DSBoolean = DS_FALSE,   // Revealed (j/n)
               DSBoolean = DS_FALSE,   // Exported (j/n)
               class DSString* = NULL);// Exported as (Name)
    DSVariable(DSObject*,              // Vaterobjekt
               class DSString&,        // Name der Variablen
               DSSortRef,              // Datentyp
               DSExpression*,          // Initialisierung
               DSBoolean,              // Revealed (j/n)
               DSBoolean,              // Exported (j/n)
               class DSString&);       // Exported as (Name)
    DSVariable(DSObject*,              // Vaterobjekt
               const char *,           // Name der Variablen
               DSSortRef,              // Datentyp
               DSExpression*,          // Initialisierung
               DSBoolean,              // Revealed (j/n)
               DSBoolean,              // Exported (j/n)
               const char* = NULL);    // Exported as (Name)
    // spezielle Konstruktoren fuer formale Parameter:
    DSVariable(DSObject*,              // Vaterobjekt
               class DSString*,        // Name des Parameters
               DSSortRef = NULL,       // Datentyp
               DSBoolean = DS_FALSE);  // IN/OUT-Parameter (j/n)
    DSVariable(DSObject*,              // Vaterobjekt
               class DSString&,        // Name des Parameters
               DSSortRef = NULL,       // Datentyp
               DSBoolean = DS_FALSE);  // IN/OUT-Parameter (j/n)
    DSVariable(DSObject*,              // Vaterobjekt
               const char *,           // Name des Parameters
               DSSortRef = NULL,       // Datentyp
               DSBoolean = DS_FALSE);  // IN/OUT-Parameter (j/n)
    virtual ~DSVariable(void);

    DSSortRef       GetSortRef(void) const;
    DSExpression   *GetInit(void) const;
    DSBoolean       GetRevealed(void) const;
    DSBoolean       GetExported(void) const;
    class DSString *GetExportedAs(void) const;
    DSBoolean       GetIsInOut(void) const;
    DSBoolean       GetIsHistory(void) const;

    DSResult        SetSortRef(DSSortRef);
    DSResult        SetInit(class DSExpression*);
    DSResult        SetRevealed(DSBoolean);
    DSResult        SetExported(DSBoolean);
    DSResult        SetExportedAs(class DSString*);
    DSResult        SetExportedAs(class DSString&);
    DSResult        SetExportedAs(const char *);
    DSResult        SetIsInOut(DSBoolean);
    DSResult        SetIsHistory(DSBoolean);

    DSObject *Clone(DSObject * = NULL,
                    DSObject * = NULL) const; // erzeugt eine identische
                                              // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSSortRef           sort_ref;
    class DSExpression *init;
    DSBoolean           revealed;
    DSBoolean           exported;
    class DSString     *exported_as;
    DSBoolean           inout;         // nur fuer DSFormalParam wichtig
    DSBoolean           history;       // nur fuer Validation wichtig
};

#endif
