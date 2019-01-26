#ifndef _DSMACHINESERVICE_H_
#define _DSMACHINESERVICE_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSSortRefComponent.h"

/************************************************************************
 * Classname: DSMachineService
 * Purpose:   Definition eines Dienstes (Name + Typen) auf Block- oder
 *            Systemebene
 ************************************************************************/

class DSMachineService : public DSNamedObject,
                         public DSSortRefComponent
{
  public:
    DSMachineService(DSObject*,
                     DSString* = NULL,       // Dienstname
                     DSSortRefList* = NULL); // Dienstparameter (Bedienwunsch
                                             // + Prioritaet)
    DSMachineService(DSObject*,
                     DSString&,
                     DSSortRefList* = NULL);
    DSMachineService(DSObject*,
                     const char * = NULL,
                     DSSortRefList* = NULL);
    virtual ~DSMachineService(void);

    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
};

#endif
