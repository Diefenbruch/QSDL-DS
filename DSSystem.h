#ifndef _DSSYSTEM_H_
#define _DSSYSTEM_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSBlockComponent.h"
#include "DSChannelComponent.h"
#include "DSSortComponent.h"
#include "DSSignalComponent.h"
#include "DSSignalslistComponent.h"
#include "DSProcedureComponent.h"
#include "DSMachineServiceComponent.h"
#include "DSPipeComponent.h"
#include "DSSensorComponent.h"
#include "DSAtomComponent.h"

/************************************************************************
 * Classname: DSSystem
 * Purpose:   Gesamtsystem einer SDL-Spezifikation
 * Z100:      Seite 28
 ************************************************************************/

class DSSystem : public DSNamedObject,
                 public DSBlockComponent,
                 public DSChannelComponent,
                 public DSSortComponent,
                 public DSSignalComponent,
                 public DSSignalslistComponent,
                 public DSProcedureComponent,
                 public DSMachineServiceComponent,
                 public DSPipeComponent,
                 public DSSensorComponent,
                 public DSAtomComponent
{
  public:
    DSSystem(DSString* = NULL);
    DSSystem(DSString&);
    DSSystem(const char *);
    virtual ~DSSystem(void);

    DSObject                *New(DSObject * = NULL) const;  // virtueller Konstruktor

    virtual DSResult         InitializeBasicSorts(void);
                                                     // legt die Sorten "Real",
                                                     // "Boolean", etc. an
    virtual DSResult         InitializeQSDLSorts(void); 
                                                     // legt die Sorten "discipline",
                                                     // "exponential", etc. an
    DSBoolean                IsOpen(void) const;     // stellt fest, ob
                                                     // es sich um ein offenes
                                                     // System handelt (mit
                                                     // Kanaelen ans Environment
    virtual DSResult         Close(class DSStream &,
                                   DSBoolean);       // schliesst offenes System
                                                     // Param: Verbose-Flag

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


  protected:
    class DSBlock           *env_block;
};

#endif
