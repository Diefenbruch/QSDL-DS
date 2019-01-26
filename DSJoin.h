#ifndef _DSJOIN_H_
#define _DSJOIN_H_

#include "DSBasicTypes.h"
#include "DSAction.h"

/*****************************************************************************
 * Klasse DSJoin
 * Zweck: Datenstruktur zur Speicherung der Parameter fuer eine JOIN-
 *        Instruktion.
 * Z100:  Seite 59
 *****************************************************************************/

class DSJoin : public DSAction
{
  public:
    DSJoin(DSObject*,                    // Vaterobjekt
           DSString* = NULL,             // Connector
           DSString* = NULL);            // Label
    DSJoin(DSObject*,                    // Vaterobjekt
           DSString&,
           DSString&);
    DSJoin(DSObject*,                    // Vaterobjekt
           const char *,
           const char *);
   ~DSJoin(void);

    DSString *GetConnectorRef(void) const;

    DSResult  SetConnectorRef(DSString *);

    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSString *connector_ref;
};

#endif // ifndef
