#ifndef _DSSIGNALITEMLIST_H_
#define _DSSIGNALITEMLIST_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSRef.h"

/************************************************************************
 * Classname: DSSignalItemList
 * Purpose:   Hilfsklasse fuer Kanal- und Signalroutendefinition, ent-
 *            haelt die drei Konstrukte welche in einer Signalliste
 *            vorkommen koennen:
 *            1. Einzelne Signale
 *            2. Signallisten
 *            3. Timersignale
 * Z100:      Seite 49 (<signal list item>)
 ************************************************************************/

class DSSignalItemList : public DSObject
{
  public:
    DSSignalItemList(DSObject* = NULL,
                     DSSignalRefList* = NULL,
                     DSSignalslistRefList* = NULL,
                     DSTimerRefList* = NULL);
    virtual ~DSSignalItemList(void);

    DSObject            *New(DSObject * = NULL) const; // virtueller Konstruktor

    DSSignalRefList     *GetSignalRefList(void) const;
    DSSignalRef          GetFirstSignalRef(void) const;
    DSSignalRef          GetNextSignalRef(void) const;
    DSSignalslistRefList *GetSignallistRefList(void) const;
    DSSignalslistRef      GetFirstSignallistRef(void) const;
    DSSignalslistRef      GetNextSignallistRef(void) const;
    DSTimerRefList      *GetTimerRefList(void) const;
    DSTimerRef           GetFirstTimerRef(void) const;
    DSTimerRef           GetNextTimerRef(void) const;

    DSObject            *Clone(DSObject * = NULL,
                               DSObject * = NULL) const;      // erzeugt eine identische
                                                 // Kopie dieses Objekts
    /*********************************************/
    /* Die folgenden drei Funktionen suchen ein  */
    /* Signal in der SignalItemList zu einem ge- */
    /* gebenen Signalnamen. Dabei werden auch    */
    /* Untersignallisten durchsucht!             */
    /*********************************************/
    DSSignalRef          GetSignalRef(DSString *) const;
    DSSignalRef          GetSignalRef(DSString &) const;
    DSSignalRef          GetSignalRef(const char *) const;

    /***************************************************/
    /* Die folgenden zwei Funktionen liefern einer     */
    /* linearisierte Liste der Signale bzw. der Timer: */
    /***************************************************/
    DSResult             GetSignals(DSSignalRefList *) const;
    DSResult             GetTimers(DSTimerRefList *) const;

    /**************************************/
    /* Die folgende Funktion stellt fest, */
    /* ob sich ein Signal bereits in der  */
    /* SignalItemList befindet. Dabei     */
    /* werden auch Untersignallisten be-  */
    /* ruecksichtigt!                     */
    /**************************************/
    DSBoolean            IsSignalRefInList(DSSignalRef) const;

    DSResult             SetSignalRefList(DSSignalRefList*);
    DSResult             InsertSignalRef(DSSignalRef);
    DSResult             SetSignallistRefList(DSSignalslistRefList*);
    DSResult             InsertSignallistRef(DSSignalslistRef);
    DSResult             SetTimerRefList(DSTimerRefList*);
    DSResult             InsertTimerRef(DSTimerRef);

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult     Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult     Run(DSWriter*, DSType, DSCardinal = 0) const;

  protected:
    DSSignalRef FindSignal(DSSignalItemListRef,
                           DSString *) const;
  private:
    DSSignalRefList     *signal_ref_list;
    DSSignalslistRefList *signallist_ref_list;
    DSTimerRefList      *timer_ref_list;
};

#endif
