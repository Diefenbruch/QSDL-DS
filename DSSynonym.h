#ifndef _DSSYNONYM_H_
#define _DSSYNONYM_H_

#include "DSBasicTypes.h"
#include "DSSort.h"
#include "DSRef.h"

/************************************************************************
 * Classname: DSSynonym
 * Purpose:   Definition von SDL-Synonymen
 * Z100:      Seite 144
 ************************************************************************/

class DSSynonym : public DSSort
{
  public:
    DSSynonym(DSObject*,                            // Vater-Objekt
              DSString* = NULL,                     // Name,
              class DSExpression* = NULL,           // Default-Wert,
              DSSortRef = NULL);                    // Sorte
    DSSynonym(DSObject*,                            // Vater-Objekt
              DSString&,                            // Name,
              class DSExpression* = NULL,           // Default-Wert,
              DSSortRef = NULL);                    // Sorte
    DSSynonym(DSObject*,                            // Vater-Objekt
              const char *,                         // Name,
              class DSExpression* = NULL,           // Default-Wert,
              DSSortRef = NULL);                    // Sorte
   ~DSSynonym(void);
  
    class DSExpression *GetValue(void) const;
    DSSortRef           GetSortRef(void) const;

    DSResult            SetValue(class DSExpression *);
    DSResult            SetSortRef(DSSortRef);
  
    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const; // erzeugt eine identische
                                                    // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    class DSExpression *default_value;
    DSSortRef           sort;
};

#endif
