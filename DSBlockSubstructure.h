#ifndef _DSBLOCKSUBSTRUCTURE_H_
#define _DSBLOCKSUBSTRUCTURE_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSBlockComponent.h"
#include "DSChannelComponent.h"
#include "DSChannel2ChannelConnectionComponent.h"
#include "DSPipe2PipeBindingComponent.h"
#include "DSSortComponent.h"
#include "DSSignalComponent.h"
#include "DSSignalslistComponent.h"
#include "DSProcedureComponent.h"
#include "DSMachineServiceComponent.h"
#include "DSPipeComponent.h"
#include "DSSensorComponent.h"

/************************************************************************
 * Classname: DSBlockSubstructure
 * Purpose:   Gesamtsystem einer SDL-Spezifikation
 * Z100:      Seite 28
 ************************************************************************/

class DSBlockSubstructure : public DSNamedObject,
                            public DSBlockComponent,
                            public DSChannelComponent,
                            public DSChannel2ChannelConnectionComponent,
                            public DSSortComponent,
                            public DSSignalComponent,
                            public DSSignalslistComponent,
                            public DSProcedureComponent,
                            public DSMachineServiceComponent,
                            public DSPipeComponent,
                            public DSPipe2PipeBindingComponent,
                            public DSSensorComponent
{
  public:
    DSBlockSubstructure(DSObject* = NULL,
                        DSString * = NULL);
    DSBlockSubstructure(DSObject*,
                        DSString&);
    DSBlockSubstructure(DSObject*,
                        const char *);
    virtual ~DSBlockSubstructure(void);

    DSObject                *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSObject                *Clone(DSObject * = NULL,
                                   DSObject * = NULL) const;
                                                     // erzeugt eine identische
                                                     // Kopie dieses Objekts

    DSBoolean                HasAction(DSActionTag, DSBoolean) const;
    DSBoolean                HasDelayedOutputs(DSBoolean) const;

    DSBoolean                HasAsteriskStates(DSBoolean) const;
    DSBoolean                HasTimer(DSBoolean) const;
    DSBoolean                HasSensors(DSBoolean) const;

    DSBoolean                HasComplexProcedures(DSBoolean) const;
    DSBoolean                HasExternalSynonyms(DSBoolean) const;

    DSCardinal               GetNumOfProcesses(void) const;

    void                     CheckForComplexProcedures(DSBoolean);

    /*************************************************************/
    /* 'State *' durch neue Referenzlisten in DSState aufloesen: */
    /*************************************************************/
    DSResult                 DissolveAsteriskStates(void);

    /*************************************************************/
    /* 'Nextstate -' aufloesen:                                  */
    /*************************************************************/
    DSResult                 DissolveNextStateDash(void);

    /*************************************************************/
    /* Decision-Konstrukte aufloesen:                            */
    /*************************************************************/
    DSResult                 DissolveDecisions(DSBoolean = DS_TRUE);
                                                     // true = alle
                                                     // false = nur decision any

    /*************************************************************/
    /* Liste aller externen Synonyme:                            */
    /*************************************************************/

    DSResult                 GetExternalSynonyms(DSSynonymRefList *) const;
    
    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult         Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult         Run(DSWriter*, DSType, DSCardinal = 0) const;

};

#endif
