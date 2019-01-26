/****************************************************************************
 *                 Modul: $RCSfile: DSAtom.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Sorte, des Namens und des Propositionialisierungswertes einer 
 *          Atomn (BASIC, STRUCTURE ...)
 *
 * Funktionen: GetProposition(): Liefert Zeiger auf die Proposition
 *             SetProposition(): Aendert die Proposition
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

#include "DSAtom.h"
#include "DSSystem.h"
#include "DSExpression.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Atomn
 ****************************************************************************/

/****************************************************************************
 * Globale Atomn
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSAtom::DSAtom(DSObject     *father,
               DSString     *n, 
               DSExpression *prop):
  DSNamedObject(DS_ATOM, n, father),
  proposition(prop)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertAtom(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  if (proposition)
  {
    if (proposition->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      proposition->SetParent(this);
    }
  }
}

DSAtom::DSAtom(DSObject     *father,
               DSString&     n, 
               DSExpression *prop) :
  DSNamedObject(DS_ATOM, n, father),
  proposition(prop)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertAtom(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  if (proposition)
  {
    if (proposition->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      proposition->SetParent(this);
    }
  }
}

DSAtom::DSAtom(DSObject     *father,
               const char   *n, 
               DSExpression *prop) :
  DSNamedObject(DS_ATOM, n, father),
  proposition(prop)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertAtom(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  if (proposition)
  {
    if (proposition->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      proposition->SetParent(this);
    }
  }
}


/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSAtom::~DSAtom(void)
{
  if (proposition) delete proposition;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSAtom::New(DSObject *father) const
{
  return new DSAtom(father);
}

/****************************************************************************
 * GetProposition(): Liefert den Propositionialwert zurueck
 *            Ergebnis: Zeiger auf DSExpression
 *            Seiteneffekte: keine
 ****************************************************************************/

DSExpression *DSAtom::GetProposition(void) const
{
  return proposition;
}

/****************************************************************************
 * SetProposition(): Speichert den uebergebenen Wert
 *            -> ini: Stringzeiger
 *            Ergebnis: TRUE
 *            Seiteneffekte: keine
 ****************************************************************************/

DSResult DSAtom::SetProposition(DSExpression *prop)
{
  if (proposition == prop) return DS_OK;

  if (proposition) delete proposition;
  proposition = prop;

  if (proposition != NULL)
  {
    if (proposition->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      proposition->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSAtom::Clone(DSObject *father, DSObject *fill_this) const
{
  DSAtom *new_atom;

  if (fill_this == NULL)
  {
    new_atom = (DSAtom *)New(father);
    assert(new_atom);
  }
  else
  {
    assert(fill_this->GetType() == DS_ATOM);
    new_atom = (DSAtom *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_atom);

  if (GetProposition())
  {
    new_atom->SetProposition((DSExpression *)GetProposition()->Clone((DSObject *)new_atom));
  }

  return new_atom;
}

DSResult DSAtom::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}
