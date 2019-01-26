#ifndef _DSDECISION_H_
#define _DSDECISION_H_

#include "DSBasicTypes.h"
#include "DSAction.h"
#include "DSRangeList.h"
#include "DSTransitionList.h"
  
/******************************************************************************
 * Klasse DSDecision
 * Zweck: Datenstruktur zur Speicherung der Parameter fuer eine DECISION-
 *        Instruktion.
 * Z100:  Seite 67
 ******************************************************************************/

class DSDecision : public DSAction
{
  public:
    DSDecision(DSObject*,                // Vaterobjekt
               DSString* =     NULL,     // optionales Label
               class DSExpression* = NULL,     // Question (<question>)
               DSRangeList* = NULL,      // Answer (<answer>)
               DSTransitionList* = NULL, // Transitionsliste
               class DSTransition* = NULL);    // Else-Part (<else part>)
    DSDecision(DSObject*,
               DSString&,
               class DSExpression* = NULL,     // Question (<question>)
               DSRangeList* = NULL,      // Answer (<answer>)
               DSTransitionList* = NULL, // Transitionsliste
               class DSTransition* = NULL);    // Else-Part (<else part>)
    DSDecision(DSObject*,
               const char *,
               class DSExpression* = NULL,     // Question (<question>)
               DSRangeList* = NULL,      // Answer (<answer>)
               DSTransitionList* = NULL, // Transitionsliste
               class DSTransition* = NULL);    // Else-Part (<else part>)
   ~DSDecision(void);

    class DSExpression *GetQuestion(void) const;
    DSRangeList        *GetAnswerList(void) const;
    class DSRange      *GetFirstAnswer(void) const;
    class DSRange      *GetNextAnswer(void) const;
    DSTransitionList   *GetTransitionList(void) const;
    class DSTransition *GetFirstTransition(void) const;
    class DSTransition *GetNextTransition(void) const;
    class DSTransition *GetElseTransition(void) const;

    DSResult            SetQuestion(class DSExpression*);
    DSResult            SetTransitionList(DSTransitionList*);
    DSResult            InsertTransition(class DSTransition*);
    DSResult            SetAnswerList(DSRangeList*);
    DSResult            InsertAnswer(class DSRange*);
    DSResult            SetElseTransition(class DSTransition*);

    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult  Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    class DSExpression *question;
    DSRangeList        *answer_list;
    DSTransitionList   *transition_list;
    class DSTransition *else_transition;
};
 
#endif // ifndef
