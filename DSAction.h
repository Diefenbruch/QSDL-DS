/******************************************************************************
 *
 *
 * Modul: $RCSfile: DSAction.h,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe:
 *    Der Modul stellt die Datenstruktur fuer SDL-Anweisungen breit.
 *
 * Klassen:
 *    DSAction: Containerklasse zur Aufnahme der verschiedenen
 *                       Instruktionstypen.
 *    DSNextState: Klasse fuer die Parameter einer NEXTSTATE-Instruktion.
 *    DSCall:      Klasse fuer die Parameter einer CALL-Instruktion.
 *    DSOutput:    Klasse fuer die Parameter einer OUTPUT-Instruktion.
 *    DSReset:     Klasse fuer die Parameter einer RESET-Instruktion.
 *    DSSet:       Klasse fuer die Parameter einer SET-Instruktion.
 *    DSTask:      Klasse fuer die Parameter einer TASK-Instruktion.
 *    DSCreate:    Klasse fuer die Parameter einer CREATE-Instruktion.
 *    DSJoin:      Klasse fuer die Parameter einer JOIN-Instruktion.
 *
 ******************************************************************************/


/******************************************************************************
 *  Konstanten
 ******************************************************************************/

#ifndef _DSACTION_H_
#define _DSACTION_H_

/******************************************************************************
 *  Include-Dateien
 ******************************************************************************/

#include "DSBasicTypes.h"
#include "DSObject.h"

/******************************************************************************
 *  Klasse DSAction
 *  Zweck: Containerklasse fuer beliebige Instruktionstypen.
 *  Z100:  Seite 58
 ******************************************************************************/

class DSAction : public DSObject
{
  public:
    DSAction(DSObject*,         // Vaterobjekt, hier DSTransition
             DSActionTag,
             class DSString * = NULL);
    DSAction(DSObject*,
             DSActionTag,
             class DSString&);
    DSAction(DSObject*,
             DSActionTag,
             const char*);

    virtual ~DSAction(void);

  public:
    class DSString *GetLabel(void) const;
    DSActionTag     GetTag(void) const;

    DSResult        SetLabel(class DSString *);
    DSResult        SetTag(DSActionTag);

    DSObject       *Clone(DSObject * = NULL,
                          DSObject * = NULL) const;
                                                     // erzeugt eine identische
                                                     // Kopie dieses Objekts
                                                     // (muss hier nur fuer
                                                     // CGAction deklariert werden)

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSActionTag     tag;
    class DSString *label;
};

#endif
