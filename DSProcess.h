#ifndef _DSPROCESS_H_
#define _DSPROCESS_H_

#include "DSBasicTypes.h"
#include "DSSignalItemList.h"

#include "DSNamedObject.h"
#include "DSFormalParamComponent.h"
#include "DSSortComponent.h"
#include "DSProcedureComponent.h"
#include "DSSignalComponent.h"
#include "DSSignalslistComponent.h"
#include "DSTimerComponent.h"
#include "DSStateComponent.h"
#include "DSVariableComponent.h"
#include "DSSensorComponent.h"

/************************************************************************
 * Classname: DSProcess
 * Purpose:   Definition eines SDL-Prozesses
 * Z100:      Seite 33
 ************************************************************************/

class DSProcess : public DSNamedObject,
                  public DSFormalParamComponent,
                  public DSSortComponent,
                  public DSProcedureComponent,
                  public DSSignalComponent,
                  public DSSignalslistComponent,
                  public DSTimerComponent,
                  public DSStateComponent,
                  public DSVariableComponent,
                  public DSSensorComponent
{
  public:
    DSProcess(DSObject* = NULL,
              DSString* = NULL,
              DSExpression* = NULL,  // initiale Anzahl von Instanzen
              DSExpression* = NULL,  // maximale Anzahl von Instanzen
              DSExpression* = NULL); // maximale Queue-Laenge
    DSProcess(DSObject*,
              DSString&,
              DSExpression* = NULL,  // initiale Anzahl von Instanzen
              DSExpression* = NULL,  // maximale Anzahl von Instanzen
              DSExpression* = NULL); // maximale Queue-Laenge
    DSProcess(DSObject*,
              const char *,
              DSExpression* = NULL,  // initiale Anzahl von Instanzen
              DSExpression* = NULL,  // maximale Anzahl von Instanzen
              DSExpression* = NULL); // maximale Queue-Laenge
    virtual ~DSProcess(void);

    DSObject *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSExpression     *GetInitInstances(void) const;
    DSExpression     *GetMaxInstances(void) const;
    DSExpression     *GetQueueLength(void) const;

    DSObject         *Clone(DSObject * = NULL,
                            DSObject * = NULL) const; // erzeugt eine identische
                                                      // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion liefert die Menge der    */
    /* gueltigen Eingabesignale des Prozesses; falls  */
    /* Sie nicht direkt spezifiziert ist, wird        */
    /* sie mit Hilfe der verbundenen Signalrouten     */
    /* konstruiert:                                   */
    /**************************************************/
    DSSignalItemList *GetValidSignalSet(void);

    DSResult          SetInitInstances(DSExpression*);
    DSResult          SetMaxInstances(DSExpression*);
    DSResult          SetQueueLength(DSExpression*);
    DSResult          SetValidSignalSet(DSSignalItemList*);

    DSBoolean         HasAction(DSActionTag, DSBoolean) const;
    DSBoolean         HasDelayedOutputs(DSBoolean) const;
    DSBoolean         HasSensors(DSBoolean) const;

    DSBoolean         HasSaves(DSBoolean) const;
    DSBoolean         HasAsteriskStates(DSBoolean) const;
    DSBoolean         HasInputData(DSBoolean) const;
    DSBoolean         HasInputSignalData(DSBoolean) const;
    DSBoolean         HasInputTimerSignalData(DSBoolean) const;

    DSBoolean         HasComplexProcedures(DSBoolean) const;
    DSBoolean         HasExternalSynonyms(DSBoolean) const;

    DSCardinal        NumOfActions(DSActionTag,
                                   DSBoolean) const;  // wichtig fuer Validation

    void              CheckForComplexProcedures(DSBoolean);

    /*************************************************************/
    /* 'State *' durch neue Referenzlisten in DSState aufloesen: */
    /*************************************************************/
    DSResult          DissolveAsteriskStates(void);

    /*************************************************************/
    /* 'Nextstate -' aufloesen:                                  */
    /*************************************************************/
    DSResult          DissolveNextStateDash(void);

    /*************************************************************/
    /* Decision-Konstrukte aufloesen:                            */
    /*************************************************************/
    DSResult          DissolveDecisions(DSBoolean = DS_TRUE); // true = alle
                                                              // false = nur decision any

    /*************************************************************/
    /* Liste aller externen Synonyme:                            */
    /*************************************************************/

    DSResult          GetExternalSynonyms(DSSynonymRefList *) const;
    
    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSExpression     *number_of_init_instances;
    DSExpression     *number_of_max_instances;
    DSSignalItemList *valid_signalset;
    DSExpression     *queue_length;
};

#endif
