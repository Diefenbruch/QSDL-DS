#ifndef _DSSIGNAL_H_
#define _DSSIGNAL_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSSortRefComponent.h"

/************************************************************************
 * Classname: DSSignal
 * Purpose:   Definition eines Signals (Name + Typen)
 * Z100:      Seite 48
 ************************************************************************/

class DSSignal : public DSNamedObject,
                 public DSSortRefComponent
{
  public:
    DSSignal(DSObject*,
             DSString* = NULL,
             DSSortRefList* = NULL);
    DSSignal(DSObject*,
             DSString&,
             DSSortRefList* = NULL);
    DSSignal(DSObject*,
             const char * = NULL,
             DSSortRefList* = NULL);
    virtual ~DSSignal(void);

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
