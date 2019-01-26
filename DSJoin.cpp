/****************************************************************************
 *                 Modul: $RCSfile: DSJoin.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          des Parameters (Sprungaddresse), der in Verbindung mit einem
 *          JOIN-Befehl angegeben ist
 *
 * Funktionen: GetConnectorRef(): Gibt einen Zeiger auf einen String zurueck
 *             SetConnectorRef(): Speichert die Sprungaddresse
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

#include "DSJoin.h"
#include "DSString.h"

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

DSJoin::DSJoin(DSObject *father,
               DSString* connector,
               DSString *label_name) :
  DSAction (father, DS_JOIN, label_name),
  connector_ref(connector)
{
}

DSJoin::DSJoin(DSObject *father,
               DSString& connector,
               DSString& label_name) :
  DSAction(father, DS_JOIN, &label_name),
  connector_ref(&connector)
{
}

DSJoin::DSJoin(DSObject *father,
               const char* connector,
               const char *label_name) :
  DSAction(father, DS_JOIN, label_name)
{
  connector_ref = new DSString(connector);
  assert(connector_ref);
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSJoin::~DSJoin(void)
{
  if (connector_ref) delete connector_ref;    /* ruft Destruktor der       */
}                                             /* Stringklasse auf          */

/****************************************************************************
 * GetConnectorRef(): Liefert den Zeiger auf die Sprungaddresse zurueck
 *                    Ergebnis: Zeiger auf einen String
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSString* DSJoin::GetConnectorRef(void) const
{
  return connector_ref;
}

/****************************************************************************
 * SetConnectorRef(): Speichert den uebergebenen Zeiger
 *                    -> conn_ref: Zeiger auf einen String
 *                    Ergebnis: DS_OK
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSResult DSJoin::SetConnectorRef(DSString* conn_ref)
{
  connector_ref = conn_ref;
  return DS_OK;
}

DSObject *DSJoin::Clone(DSObject *father, DSObject *fill_this) const
{
  DSJoin *new_join;

  if (fill_this == NULL)
  {
    new_join = (DSJoin *)New(father);
    assert(new_join);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_join = (DSJoin *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_join);

  if (GetConnectorRef())
  {
    new_join->SetConnectorRef((DSString *)GetConnectorRef()->Clone((DSObject *)new_join));
  }

  return new_join;
}

DSResult DSJoin::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (connector_ref) connector_ref->Write(writer, what);

  return DS_OK;
}
