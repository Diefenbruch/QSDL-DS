#ifndef _DSLINK_H_
#define _DSLINK_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSNamedObject.h"

/************************************************************************
 * Classname: DSLink
 * Purpose:   Speichert einen QSDL-Link
 ************************************************************************/

class DSLink : public DSNamedObject
{
  public:
    DSLink(DSObject* = NULL,
           DSString* = NULL,
           DSProcessRef = NULL,
           DSMachineRef = NULL);
    DSLink(DSObject*,
           DSString&,
           DSProcessRef = NULL,
           DSMachineRef = NULL);
    DSLink(DSObject*,
           const char *,
           DSProcessRef = NULL,
           DSMachineRef = NULL);
    virtual ~DSLink(void);

    DSObject                *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSProcessRef             GetProcessRef(void) const;
    DSMachineRef             GetMachineRef(void) const;
    DSMachineServiceRefList *GetMachineServiceRefList(void) const;
    DSMachineServiceRef      GetFirstMachineServiceRef(void) const;
    DSMachineServiceRef      GetNextMachineServiceRef(void) const;

    DSBoolean                IsMachineServiceRefInList(DSMachineServiceRef) const;
    
    DSResult                 SetProcessRef(DSProcessRef);
    DSResult                 SetMachineRef(DSMachineRef);
    DSResult                 SetMachineServiceRefList(DSMachineServiceRefList*);
    DSResult                 InsertMachineServiceRef(DSMachineServiceRef);

    DSObject                *Clone(DSObject * = NULL,
                                   DSObject * = NULL) const;
                                                     // erzeugt eine identische
                                                     // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult         Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult         Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSProcessRef             process_ref;
    DSMachineRef             machine_ref;
    DSMachineServiceRefList *machineservice_ref_list;
};

#endif
