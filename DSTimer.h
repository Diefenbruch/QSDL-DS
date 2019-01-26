#ifndef _DSTIMER_H_
#define _DSTIMER_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSSortRefComponent.h"

/************************************************************************
 * Classname: DSTimer
 * Purpose:   Speichert die Deklaration eines Timers
 * Z100:      Seite 69
 ************************************************************************/

class DSTimer : public DSNamedObject,
                public DSSortRefComponent
{
  public:
    DSTimer(DSObject*,
            class DSString* = NULL,
            DSSortRefList* = NULL);
    DSTimer(DSObject*,
            class DSString&,
            DSSortRefList* = NULL);
    DSTimer(DSObject*,
            const char*,
            DSSortRefList* = NULL);
    virtual ~DSTimer(void);

    DSObject *Clone(DSObject * = NULL,
                    DSObject * = NULL) const; // erzeugt eine identische
                                              // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
};

#endif

