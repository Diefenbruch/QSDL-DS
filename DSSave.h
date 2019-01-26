#ifndef _DSSAVE_H_
#define _DSSAVE_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSSignalItemList.h"

/************************************************************************
 * Classname: DSSave
 * Purpose:   Speichert ein SDL-Save-Konstrukt
 * Z100:      Seite 55
 ************************************************************************/

class DSSave : public DSObject
{
  public:
    DSSave(DSObject* = NULL,           // 1. Parameter: Vaterobjekt
           DSBoolean = DS_FALSE,       // 2. Parameter: Asterisk-Save (j/n)
           DSSignalItemList * = NULL); // 2. Parameter: Signalliste
    virtual ~DSSave(void);

    DSObject         *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSBoolean         GetIsAsterisk(void) const;
    DSSignalItemList *GetSignalList(void) const;

    DSResult          SetIsAsterisk(DSBoolean);
    DSResult          SetSignalList(DSSignalItemList*);

    DSObject         *Clone(DSObject * = NULL,
                            DSObject * = NULL) const; 
                                              // erzeugt eine identische
                                              // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSBoolean         is_asterisk;  // <- wenn TRUE, dann ist signal_list
    DSSignalItemList *signal_list;  //    Ausnahmeliste
};

#endif
