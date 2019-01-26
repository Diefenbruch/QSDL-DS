#ifndef _DSASSERT_H_
#define _DSASSERT_H_

#include "DSBasicTypes.h"
#include "DSAction.h"
 
/*****************************************************************************
 * Klasse DSAssert
 * Zweck: Datenstruktur zur Speicherung der Parameter fuer eine QSDL-ASSERT-
 *        Instruktion (Testen von benutzerdefinierten Anforderungen).
 * Z100:  -
 *****************************************************************************/

class DSAssert : public DSAction
{
  public:
    DSAssert(DSObject *,
             DSString * = NULL,        // Label
             DSExpression * = NULL);   // Anforderung
    DSAssert(DSObject *,
             DSString&,
             DSExpression * = NULL);
    DSAssert(DSObject *,
             const char *,
             DSExpression * = NULL);
    ~DSAssert(void);

    DSExpression *GetExpression(void) const;

    DSResult      SetExpression(DSExpression *);
     
    DSObject     *Clone(DSObject * = NULL,
                        DSObject * = NULL) const; // erzeugt eine identische
                                                 // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult  Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSExpression   *expression;
};

#endif  // ifndef
