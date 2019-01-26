#ifndef _DSRETURN_H_
#define _DSRETURN_H_

#include "DSBasicTypes.h"
#include "DSAction.h"

/*****************************************************************************
 * Klasse DSReturn
 * Zweck: Datenstruktur zur Speicherung der Parameter fuer eine RETURN-
 *        Instruktion von Prozeduren.
 * Z100:  Seite 61
 *****************************************************************************/

class DSReturn : public DSAction
{
  public:
    DSReturn(DSObject*,                    // Vaterobjekt
             class DSExpression* = NULL,   // Rueckgabewert
             class DSString* = NULL);      // Label
    DSReturn(DSObject*,                    // Vaterobjekt
             class DSExpression*,          // Rueckgabewert
             class DSString&);
    DSReturn(DSObject*,                    // Vaterobjekt
             class DSExpression*,          // Rueckgabewert
             const char *);
   ~DSReturn(void);

    class DSExpression *GetResult(void) const;

    DSResult            SetResult(class DSExpression *);

    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const; // erzeugt eine identische
                                              // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    class DSExpression *proc_result;  // fuer 'value returning procedures'
};

#endif // ifndef
