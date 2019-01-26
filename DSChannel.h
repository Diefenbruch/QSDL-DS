#ifndef _DSCHANNEL_H_
#define _DSCHANNEL_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSRef.h"
#include "DSSignalItemList.h"

/************************************************************************
 * Classname: DSChannel
 * Purpose:   Definition eines Kanals
 * Z100:      Seite 42
 ************************************************************************/

class DSChannel : public DSNamedObject
{
  public:
    DSChannel(DSObject* = NULL,     // 1. Parameter: Vater-Objekt
              DSString* = NULL,     // 2. Parameter: Name
              DSBoolean = DS_TRUE,  // 3. Parameter: Delay (ja/nein)
              DSBlockRef = NULL,    // 4. Parameter: 1. Block
              DSBlockRef = NULL);   // 5. Parameter: 2. Block
    DSChannel(DSObject*,
              DSString&,
              DSBoolean = DS_TRUE,
              DSBlockRef = NULL,    // 4. Parameter: 1. Block
              DSBlockRef = NULL);   // 5. Parameter: 2. Block
    DSChannel(DSObject*,
              const char *,
              DSBoolean = DS_TRUE,
              DSBlockRef = NULL,    // 4. Parameter: 1. Block
              DSBlockRef = NULL);   // 5. Parameter: 2. Block
    virtual ~DSChannel(void);

    DSObject         *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSBlockRef        GetBlock1Ref(void) const;
    DSBlockRef        GetBlock2Ref(void) const;
    DSSignalItemList *GetSignalList12(void) const;
    DSSignalItemList *GetSignalList21(void) const;
    DSBoolean         GetHasDelay(void) const;

    DSResult          SetBlock1Ref(DSBlockRef);
    DSResult          SetBlock2Ref(DSBlockRef);
    DSResult          SetSignalList12(DSSignalItemList*);
    DSResult          SetSignalList21(DSSignalItemList*);
    DSResult          SetHasDelay(DSBoolean);

    DSObject *Clone(DSObject * = NULL,
                    DSObject * = NULL) const; // erzeugt eine identische
                                              // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSBlockRef        block1_ref;
    DSBlockRef        block2_ref;
    DSSignalItemList *b1_b2_signal_list;
    DSSignalItemList *b2_b1_signal_list;
    DSBoolean         has_delay;
};

#endif
