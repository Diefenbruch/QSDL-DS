#ifndef _DSBLOCK_H_
#define _DSBLOCK_H_

#include "DSBasicTypes.h"

#include "DSNamedObject.h"
#include "DSSortComponent.h"
#include "DSSignalComponent.h"
#include "DSSignalslistComponent.h"
#include "DSSignalRouteComponent.h"
#include "DSProcessComponent.h"
#include "DSProcedureComponent.h"
#include "DSMachineComponent.h"
#include "DSMachineServiceComponent.h"
#include "DSLinkComponent.h"
#include "DSChannel2RouteConnectionComponent.h"
#include "DSPipe2LinkBindingComponent.h"
#include "DSSensorComponent.h"
#include "DSBlockSubstructure.h"

/************************************************************************
 * Classname: DSBlock
 * Purpose:   Definiton eines SDL-Blockes
 * Z100:      Seite 30
 ************************************************************************/

class DSBlock : public DSNamedObject,
                public DSSortComponent,
                public DSSignalComponent,
                public DSSignalslistComponent,
                public DSSignalRouteComponent,
                public DSProcessComponent,
                public DSProcedureComponent,
                public DSMachineComponent,
                public DSMachineServiceComponent,
                public DSLinkComponent,
                public DSChannel2RouteConnectionComponent,
                public DSPipe2LinkBindingComponent,
                public DSSensorComponent
{
  public:
    DSBlock(DSObject* = NULL,
            DSString* = NULL);
    DSBlock(DSObject*,
            DSString&);
    DSBlock(DSObject*,
            const char *);
    virtual ~DSBlock(void);

    DSObject                      *New(DSObject * = NULL) const; 
                                                     // virtueller Konstruktor

    DSObject                      *Clone(DSObject * = NULL,
                                         DSObject * = NULL) const; // erzeugt eine identische
                                                                   // Kopie dieses Objekts

    DSBoolean                      HasAction(DSActionTag, DSBoolean) const;
    DSBoolean                      HasDelayedOutputs(DSBoolean) const;
    
    DSBoolean                      HasAsteriskStates(DSBoolean) const;

    DSBoolean                      HasComplexProcedures(DSBoolean) const;
    DSBoolean                      HasSensors(DSBoolean) const;
    DSBoolean                      HasExternalSynonyms(DSBoolean) const;

    DSBlockSubstructure *          GetBlockSubstructure(void) const;
    DSResult                       SetBlockSubstructure(DSBlockSubstructure *);

    DSCardinal                     GetNumOfProcesses(void) const;

    void                           CheckForComplexProcedures(DSBoolean);

    /*************************************************************/
    /* 'State *' durch neue Referenzlisten in DSState aufloesen: */
    /*************************************************************/
    DSResult                       DissolveAsteriskStates(void);

    /*************************************************************/
    /* 'Nextstate -' aufloesen:                                  */
    /*************************************************************/
    DSResult                       DissolveNextStateDash(void);

    /*************************************************************/
    /* Decision-Konstrukte aufloesen:                            */
    /*************************************************************/
    DSResult                       DissolveDecisions(DSBoolean = DS_TRUE);
                                                      // true = alle
                                                      // false = nur decision any

    /*************************************************************/
    /* Liste aller externen Synonyme:                            */
    /*************************************************************/

    DSResult                       GetExternalSynonyms(DSSynonymRefList *) const;
    
    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult               Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult               Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSBlockSubstructure *          block_substructure;
};

#endif
