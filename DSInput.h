#ifndef _DSINPUT_H_
#define _DSINPUT_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSInputSignalList.h"
#include "DSInputTimerSignalList.h"

/************************************************************************
 * Classname: DSInput
 * Purpose:   Speichert ein SDL-Input-Konstrukt
 * Z100:      Seite 53, Seite 56 (spontaneous transition),
 *            Seite 104 (asterisk), Seite 105 (priority),
 *            Seite 106 (continuous signal), Seite 108 (enabling condition)
 ************************************************************************/

class DSInput : public DSObject
{
  public:
    DSInput(DSObject* = NULL,          // 1. Parameter: Vaterobjekt
            DSBoolean = DS_FALSE,      // 2. Parameter: Prioritaets-Input (j/n)
            DSBoolean = DS_FALSE,      // 3. Parameter: Asterisk-Input (j/n)
            DSBoolean = DS_FALSE,      // 4. Parameter: Spontanous-Input (j/n)
            DSInputSignalList* = NULL, // 5. Parameter: Signalliste
            DSInputTimerSignalList* = NULL, // 6. Parameter: Timer-Liste
            class DSExpression* = NULL,  // 7. Parameter: Enabling-Condition
            class DSTransition* = NULL); // 8. Parameter: Transition
    virtual ~DSInput(void);

    DSObject       *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSBoolean               GetHasPriority(void) const;
    DSBoolean               GetIsAsterisk(void) const;
    DSBoolean               GetIsSpontanous(void) const;
    DSInputSignalList      *GetInputSignalList(void) const;
    DSInputSignal          *GetFirstInputSignal(void) const;
    DSInputSignal          *GetNextInputSignal(void) const;
    DSInputTimerSignalList *GetInputTimerSignalList(void) const;
    DSInputTimerSignal     *GetFirstInputTimerSignal(void) const;
    DSInputTimerSignal     *GetNextInputTimerSignal(void) const;
    DSExpression           *GetEnablingCondition(void) const;
    class DSTransition     *GetTransition(void) const;
    class DSExpression     *GetProbability(void) const;
    DSString               *GetPriority(void) const;

    DSResult                SetHasPriority(DSBoolean);
    DSResult                SetIsAsterisk(DSBoolean);
    DSResult                SetIsSpontanous(DSBoolean);
    DSResult                SetInputSignalList(DSInputSignalList*);
    DSResult                InsertInputSignal(DSInputSignal*);
    DSResult                SetInputTimerSignalList(DSInputTimerSignalList*);
    DSResult                InsertInputTimerSignal(DSInputTimerSignal*);
    DSResult                SetEnablingCondition(class DSExpression*);
    DSResult                SetTransition(class DSTransition*);
    DSResult                SetPriority(DSString*);
    DSResult                SetPriority(DSString&);
    DSResult                SetPriority(const char *);

    DSObject               *Clone(DSObject * = NULL,
                                  DSObject * = NULL) const; // erzeugt eine identische
                                                            // Kopie dieses Objekts
    DSBoolean               HasInputData(void) const;
    DSBoolean               HasInputSignalData(void) const;
    DSBoolean               HasInputTimerSignalData(void) const;

    /****************************************************/
    /* Die folgende Funktionen berechnen die moeglichen */
    /* Eingaben (Signale oder Timer) des Inputs und     */
    /* liefert sie in zwei Listen zurueck (werden       */
    /* allokiert falls Null-Pointer uebergeben werden)  */
    /****************************************************/
    DSResult                GetSignalSet(DSSignalRefList *) const;
    DSResult                GetTimerSet(DSTimerRefList *) const;
    DSResult                GetAsteriskSet(DSSignalRefList *,
                                           DSTimerRefList *) const;

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult        Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult        Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSBoolean               has_priority;       // nur fuer priority input
                                                // nicht fuer continuous signal!
    DSBoolean               is_asterisk;        // <- wenn TRUE oder
    DSBoolean               is_spontanous;      // <- wenn TRUE dann muessen
    DSInputSignalList      *signal_list;        // signal_list und timer_list 
    DSInputTimerSignalList *timer_list;         // leer sein!
    class DSExpression     *enabling_condition; // Wenn zuseatzlich signal_list
                                                // und timer_list leer sind
                                                // dann handelt es sich
                                                // um ein Continuous Signal
                                                // ansonsten ist es eine
                                                // Enabling Condition
    class DSTransition     *transition;
    DSString               *priority;           // Prioritaet (nur fuer
                                                // continuous signal wichtig)
                                                // hat nichts mit has_priority
                                                // zu tun
};

#endif
