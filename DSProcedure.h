#ifndef _DSPROCEDURE_H_
#define _DSPROCEDURE_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSFormalParamComponent.h"
#include "DSProcedureComponent.h"
#include "DSSortComponent.h"
#include "DSStateComponent.h"
#include "DSVariableComponent.h"
#include "DSSensorComponent.h"

/************************************************************************
 * Classname:  DSProcedure
 * Purpose:    Definition einer SDL-Prozedur
 * Z100:       Seite 39
 ************************************************************************/

class DSProcedure : public DSNamedObject,
                    public DSFormalParamComponent,
                    public DSSortComponent,
                    public DSProcedureComponent,
                    public DSStateComponent,
                    public DSVariableComponent,
                    public DSSensorComponent
{
  public:
    DSProcedure(DSObject* = NULL,       // 1. Parameter: Vaterobj.
                DSString* = NULL);      // 2. Parameter: Name
    DSProcedure(DSObject*, DSString&);
    DSProcedure(DSObject*, const char * = NULL);
    virtual ~DSProcedure(void);

    DSFormalParamRef GetReturnParamRef(void) const; // Name + Datentyp von Value returning
                                                    // Procedure Call (s. S. 42 Z100)
    DSBoolean        GetIsComplex(void) const;
                                                        
    DSResult         SetReturnParamRef(DSFormalParamRef);
    DSResult         SetIsComplex(DSBoolean);

    DSBoolean        HasAction(DSActionTag, DSBoolean) const;
    DSBoolean        HasDelayedOutputs(DSBoolean) const;

    DSBoolean        HasSaves(DSBoolean) const;
    DSBoolean        HasAsteriskStates(DSBoolean) const;
    DSBoolean        HasInputData(DSBoolean) const;
    DSBoolean        HasInputSignalData(DSBoolean) const;
    DSBoolean        HasInputTimerSignalData(DSBoolean) const;

    DSBoolean        HasComplexProcedures(DSBoolean) const;

    void             CheckForComplexProcedures(DSBoolean);

    DSCardinal       NumOfActions(DSActionTag,
                                  DSBoolean) const;  // wichtig fuer Validation

    /*************************************************************/
    /* 'State *' durch neue Referenzlisten in DSState aufloesen: */
    /*************************************************************/
    DSResult         DissolveAsteriskStates(void);

    /*************************************************************/
    /* 'Nextstate -' aufloesen:                                  */
    /*************************************************************/
    DSResult         DissolveNextStateDash(void);

    /*************************************************************/
    /* Decision-Konstrukte aufloesen:                            */
    /*************************************************************/
    DSResult         DissolveDecisions(DSBoolean = DS_TRUE);
                                                   // true = alle
                                                   // false = nur decision any

    DSObject        *Clone(DSObject * = NULL,
                           DSObject * = NULL) const; // erzeugt eine identische
                                                     // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSFormalParamRef return_param_ref;  // Z100 Seite 42 oben
                                        // wenn != NULL, dann
                                        // handelt es sich um eine
                                        // Wertliefernde Prozedur
                                        // zeigt auf letztes Element
                                        // in param_list!
    DSBoolean        is_complex;        // erfordert diese
                                        // Prozedur ein eigenes Runnable
                                        // im Laufzeitsystem da sie
                                        // Call- oder Request-Aktionen
                                        // oder Zustaende besitzt?
                                        // Dieses Flag wird durch die
                                        // Methode CheckForComplexProcedures()
                                        // bestimmt. 
};

#endif
