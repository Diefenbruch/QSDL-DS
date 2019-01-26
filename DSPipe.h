#ifndef _DSPIPE_H_
#define _DSPIPE_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSRef.h"
#include "DSMachineService.h"

/************************************************************************
 * Classname: DSPipe
 * Purpose:   Definition eines Kanals
 ************************************************************************/

class DSPipe : public DSNamedObject
{
  public:
    DSPipe(DSObject* = NULL,
           DSString* = NULL,
           DSBlockRef = NULL,
           DSBlockRef = NULL);
    DSPipe(DSObject*,
           DSString&,
           DSBlockRef = NULL,
           DSBlockRef = NULL);
    DSPipe(DSObject*,
           const char *,
           DSBlockRef = NULL,
           DSBlockRef = NULL);
    virtual ~DSPipe(void);

    DSObject                *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSBlockRef               GetBlock1Ref(void) const;
    DSBlockRef               GetBlock2Ref(void) const;
    DSMachineServiceRefList *GetMachineServiceRefList12(void) const;
    DSMachineServiceRef      GetFirstMachineServiceRef12(void) const;
    DSMachineServiceRef      GetNextMachineServiceRef12(void) const;
    DSMachineServiceRefList *GetMachineServiceRefList21(void) const;
    DSMachineServiceRef      GetFirstMachineServiceRef21(void) const;
    DSMachineServiceRef      GetNextMachineServiceRef21(void) const;

    DSBoolean                IsMachineServiceRefInList12(DSMachineServiceRef) const;
    DSBoolean                IsMachineServiceRefInList21(DSMachineServiceRef) const;

    DSResult                 SetBlock1Ref(DSBlockRef);
    DSResult                 SetBlock2Ref(DSBlockRef);
    DSResult                 SetMachineServiceRefList12(DSMachineServiceRefList*);
    DSResult                 InsertMachineServiceRef12(DSMachineServiceRef);
    DSResult                 SetMachineServiceRefList21(DSMachineServiceRefList*);
    DSResult                 InsertMachineServiceRef21(DSMachineServiceRef);

    DSObject                *Clone(DSObject * = NULL,
                                   DSObject * = NULL) const; // erzeugt eine identische
                                                             // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult         Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult         Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSBlockRef               block1_ref;
    DSBlockRef               block2_ref;
    DSMachineServiceRefList *b1_b2_machineservice_ref_list;
    DSMachineServiceRefList *b2_b1_machineservice_ref_list; 
};

#endif
