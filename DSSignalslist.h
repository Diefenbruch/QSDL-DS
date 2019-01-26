#ifndef _DSSIGNALLIST_H_
#define _DSSIGNALLIST_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"

/************************************************************************
 * Classname: DSSignalslist
 * Purpose:   Definition einer Signalliste, besteht aus Elementen vom
 *            Typ DSSignalItemList
 * Z100:      Seite 48
 ************************************************************************/

class DSSignalslist : public DSNamedObject
{
  public:
    DSSignalslist(DSObject * = NULL,
                 DSString * = NULL,
                 DSSignalItemList * = NULL);
    DSSignalslist(DSObject *,
                 DSString&,
                 DSSignalItemList * = NULL);
    DSSignalslist(DSObject *,
                 const char *,
                 DSSignalItemList* = NULL);
    virtual ~DSSignalslist(void);

    DSObject         *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSSignalItemList *GetSignalItemList(void) const;

    DSResult          SetSignalItemList(DSSignalItemList*);

    DSObject         *Clone(DSObject * = NULL,
                            DSObject * = NULL) const; // erzeugt eine identische
                                                      // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSSignalItemList *signal_item_list;
};

#endif
