#ifndef _DSSIGNALROUTE_H_
#define _DSSIGNALROUTE_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSRef.h"
#include "DSSignalItemList.h"

/************************************************************************
 * Classname: DSSignalRoute
 * Purpose:   Speichert eine SDL-Signalroute
 * Z100:      Seite 44
 ************************************************************************/

class DSSignalRoute : public DSNamedObject
{
  public:
    DSSignalRoute(DSObject* = NULL,
                  class DSString* = NULL,
                  DSProcessRef = NULL,
                  DSProcessRef = NULL);
    DSSignalRoute(DSObject*,
                  class DSString&,
                  DSProcessRef = NULL,
                  DSProcessRef = NULL);
    DSSignalRoute(DSObject*,
                  const char *,
                  DSProcessRef = NULL,
                  DSProcessRef = NULL);
    virtual ~DSSignalRoute(void);

    DSObject         *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSProcessRef      GetProcess1Ref(void) const;
    DSProcessRef      GetProcess2Ref(void) const;
    DSSignalItemList *GetSignalList12(void) const;
    DSSignalItemList *GetSignalList21(void) const;

    DSResult          SetProcess1Ref(DSProcessRef);
    DSResult          SetProcess2Ref(DSProcessRef);
    DSResult          SetSignalList12(DSSignalItemList*);
    DSResult          SetSignalList21(DSSignalItemList*);

    DSObject         *Clone(DSObject * = NULL,
                            DSObject * = NULL) const; // erzeugt eine identische
                                                      // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSProcessRef      process1_ref;
    DSProcessRef      process2_ref;
    DSSignalItemList *p1_p2_signal_list;
    DSSignalItemList *p2_p1_signal_list;
};

#endif
