#ifndef _DSSTATE_H_
#define _DSSTATE_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSStringList.h"
#include "DSInputList.h"
#include "DSSaveList.h"

/************************************************************************
 * Classname: DSState
 * Purpose:   Speichert einen SDL-Zustand
 * Z100:      Seite 52, Seite 103 (Asterisk State)
 ************************************************************************/

class DSState : public DSObject
{
  public:
    DSState(DSObject* = NULL,           // 1. Parameter: Vaterobjekt
            DSStringKeyList* = NULL,    // 2. Parameter: Namen des Zustands
            DSBoolean = DS_FALSE);      // 3. Parameter: Zwischenzustand ?
    DSState(DSObject*,                  // 1. Parameter: Vaterobjekt
            DSString*,                  // 2. Parameter: 1. Name des Zustands
            DSBoolean = DS_FALSE);      // 3. Parameter: Zwischenzustand ?
    DSState(DSObject*,                  // 1. Parameter: Vaterobjekt
            DSString&,                  // 2. Parameter: 1. Name des Zustands
            DSBoolean = DS_FALSE);      // 3. Parameter: Zwischenzustand ?
    DSState(DSObject*,                  // 1. Parameter: Vaterobjekt
            const char *,               // 2. Parameter: 1. Name des Zustands
            DSBoolean = DS_FALSE);      // 3. Parameter: Zwischenzustand ?
    virtual ~DSState(void);

    DSObject         *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSBoolean         GetIsAsterisk(void) const;
    DSStringKeyList  *GetNameList(void) const;
    DSString         *GetFirstName(void) const;
    DSString         *GetNextName(void) const;
    DSInputList      *GetInputList(void) const;
    class DSInput    *GetFirstInput(void) const;
    class DSInput    *GetNextInput(void) const;
    DSSaveList       *GetSaveList(void) const;
    class DSSave     *GetFirstSave(void) const;
    class DSSave     *GetNextSave(void) const;

    class DSExpression *GetAwakeTime(void) const;

    // die Linearisierung der Decisions erzeugt verschiedene
    // 'Hilfszustaende'. um diese von den 'normalen' Zustaenden
    // abzugrenzen, bekommen sie ein 'intermediate'-Flag:
    DSBoolean         GetIsIntermediate(void) const;

    // die folgende Funktion 'merged' 2 Zustaende zusammen:
    DSResult          Append(DSState *);

    DSBoolean         HasAction(DSActionTag) const;
    DSBoolean         HasDelayedOutputs(void) const;

    DSBoolean         HasInputAsterisk(void) const;
    DSBoolean         HasInputData(void) const;
    DSBoolean         HasInputSignalData(void) const;
    DSBoolean         HasInputTimerSignalData(void) const;
    DSCardinal        HasEnablingConditions(void) const;
    DSCardinal        HasContinuousSignals(void) const;

    DSCardinal        NumOfActions(DSActionTag) const;  // wichtig fuer Validation

    DSResult          SetIsAsterisk(DSBoolean);
    DSResult          SetNameList(DSStringKeyList*);
    DSResult          InsertName(DSString*);
    DSResult          InsertName(DSString&);
    DSResult          InsertName(const char *);
    DSResult          SetInputList(DSInputList*);
    DSResult          InsertInput(class DSInput*);
    DSResult          SetSaveList(DSSaveList*);
    DSResult          InsertSave(class DSSave*);

    DSResult          SetAwakeTime(class DSExpression*);

    /**************************************************/
    /* Die folgende Funktion berechnet die moeglichen */
    /* Eingaben (Signale oder Timer) des Zustands und */
    /* liefert sie in zwei Listen zurueck (werden     */
    /* allokiert falls Null-Pointer uebergeben werden)*/
    /**************************************************/
    DSResult          GetInputSet(DSSignalRefList *,
                                  DSTimerRefList *) const;

    DSSaveType        GetSaveType(void) const;
    DSResult          GetSpontanousTransitionList(DSTransitionRefList *) const;

    /*************************************************************/
    /* 'Nextstate -' aufloesen:                                  */
    /*************************************************************/
    DSResult          DissolveNextStateDash(void);

    /*************************************************************/
    /* Decision-Konstrukte aufloesen:                            */
    /*************************************************************/
    DSResult          DissolveDecisions(DSBoolean = DS_TRUE); // true = alle
                                                              // false = nur decision any

    DSObject         *Clone(DSObject * = NULL,
                            DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult  Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSBoolean         is_asterisk; // wenn TRUE
    DSStringKeyList  *name_list;   // dann ist name_list die Ausnahmeliste!
    DSInputList      *input_list;
    DSSaveList       *save_list;
    DSExpression     *awake_time;
    DSBoolean         intermediate; // Zwischenzustand der durch Linearisierung
                                    // von decisions entstanden ist?
};

#endif
