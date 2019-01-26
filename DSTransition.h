#ifndef _DSTRANSITION_H_
#define _DSTRANSITION_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSActionList.h"

/************************************************************************
 * Classname: DSTransition
 * Purpose:   Speichert eine SDL-Transition
 * Z100:      Seite 57
 ************************************************************************/

class DSTransition : public DSObject
{
  public:
    DSTransition(DSObject* = NULL,                  // Vaterobjekt
                 DSActionList* = NULL);
    virtual ~DSTransition(void);

    DSObject          *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSActionList      *GetActionList(void) const;
    class DSAction    *GetFirstAction(void) const;
    class DSAction    *GetNextAction(void) const;

    DSResult           SetActionList(DSActionList*);
    DSResult           InsertAction(class DSAction*);

    DSObject          *Clone(DSObject * = NULL,    // parent
                             DSObject * = NULL) const;
                                                   // erzeugt eine identische
                                                   // Kopie dieses Objekts
    DSBoolean          HasAction(DSActionTag) const;
    DSBoolean          HasDelayedOutputs(void) const;

    DSCardinal         NumOfActions(DSActionTag) const;  // wichtig fuer Validation

    /*************************************************************/
    /* 'Nextstate -' aufloesen:                                  */
    /*************************************************************/
    DSResult          DissolveNextStateDash(void);

    /*************************************************************/
    /* Decision-Konstrukte aufloesen:                            */
    /*************************************************************/
    DSDecision        *FindDecision(DSBoolean) const;
    virtual DSResult   BuildSpontaneousInput(DSState *, DSState *,
                                             DSTransition *);
    virtual DSResult   BuildContinuousSignal(DSState *, DSState *,
                                             DSTransition *,
                                             DSExpression *, DSRange *);
    virtual DSResult   DissolveDecision(DSDecision *,
                                        DSObject *,
                                        DSString *,
                                        DSCardinal &);
    DSResult           DissolveDecisions(DSCardinal &, DSBoolean = DS_TRUE);

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult   Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult   Run(DSWriter*, DSType, DSCardinal = 0) const;

  protected:
    DSActionList      *action_list;
};

#endif
