/****************************************************************************
 *                 Modul: $RCSfile: DSNextState.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          des Parameters (Statenamens), der in Verbindung mit einem 
 *          Nextstate-Befehl angegeben ist
 *
 * Funktionen: GetNextStateRef(): Gibt eine Referenz auf den entsprechenden
 *                                Folgezustand zurueck
 *             SetNextStateRef(): Speichert den uebergebenen Folgezustand
 *             Save(): Abspeichern in eine Datei
 ****************************************************************************/

#ifdef USE_PRAGMA
#pragma interface
#endif

/****************************************************************************
 * Konstanten
 ****************************************************************************/
 
/****************************************************************************
 * Include-Anweisungen
 ****************************************************************************/
 
#include "DSNextState.h"
#include "DSState.h"
#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Variablen
 ****************************************************************************/
 
/****************************************************************************
 * Globale Variablen
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSNextState::DSNextState(DSObject *father,
                         DSString *label_name,
                         DSStateRef state) : 
  DSAction(father, DS_NEXTSTATE, label_name),
  next_state_ref(state)
{
}

DSNextState::DSNextState(DSObject *father,
                         DSString& label_name,
                         DSStateRef state) : 
  DSAction(father, DS_NEXTSTATE, &label_name),
  next_state_ref(state)
{
}

DSNextState::DSNextState(DSObject *father,
                         const char *label_name,
                         DSStateRef state) : 
  DSAction(father, DS_NEXTSTATE, label_name),
  next_state_ref(state)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSNextState::~DSNextState(void)    /* enthaelt nur einen Zeiger  */
{                                              /* also kein Speicherplatz    */                                
}                                              /* freizugeben                */

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSNextState::New(DSObject *father) const
{
  return new DSNextState(father);
}

/****************************************************************************
 * GetNextStateRef(): Liefert den aktuellen Zeiger auf den Folgezustand
 *                    des NextState-Befehls zurueck
 *                    -> next_state_ref: Zeiger auf einen State
 *                    Seiteneffekte: keine
 ****************************************************************************/
 
DSStateRef DSNextState::GetNextStateRef(void) const
{
  return next_state_ref;
}

/****************************************************************************
 * SetNextStateRef(): Speichert den uebergebenen Zeiger
 *                    <- next_state_ref: Zeiger auf einen State
 *                    Ergebnis: DS_OK, falls der uebergebene Zeiger ungleich
 *                              NULL, DS_ERROR sonst
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSResult DSNextState::SetNextStateRef(DSStateRef state)
{
  return (((next_state_ref = state) != NULL) ? DS_OK : DS_ERROR);
}

DSObject *DSNextState::Clone(DSObject *father, DSObject *fill_this) const
{
  DSNextState *new_nextstate;

  if (fill_this == NULL)
  {
    new_nextstate = (DSNextState *)New(father);
    assert(new_nextstate);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_nextstate = (DSNextState *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_nextstate);

  new_nextstate->SetNextStateRef(GetNextStateRef());

  return new_nextstate;
}

DSResult DSNextState::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (next_state_ref) next_state_ref->Write(writer, what);

  return DS_OK;
}
