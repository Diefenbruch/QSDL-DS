/****************************************************************************
 *                 Modul: $RCSfile: DSVariable.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Sorte, des Namens und des Initialisierungswertes einer 
 *          Variablen (BASIC, STRUCTURE ...)
 *
 * Funktionen: GetSortRef(): Liefert Zeiger auf die Sorte
 *             GetInit(): Liefert Zeiger auf Initialwert
 *             SetSortRef(): Speichert Sortentyp
 *             SetInit(): Aendert den Initialisierungswert
 *             Save(): Abspeicherung der Infos in einer Datei
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

#include "DSVariable.h"
#include "DSProcess.h"    // wegen parent
#include "DSProcedure.h"    // wegen parent
#include "DSExpression.h"
#include "DSSort.h"
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

DSVariable::DSVariable(DSObject     *father,
                       DSString     *n, 
                       DSSortRef     s, 
                       DSExpression *i,
                       DSBoolean     reveal,
                       DSBoolean     exprt,
                       DSString     *exprt_as) :
  DSNamedObject(DS_VARIABLE, n, father),
  sort_ref(s), 
  init(i),
  revealed(reveal),
  exported(exprt),
  exported_as(exprt_as)
{
  inout = DS_FALSE;
  history = DS_FALSE;

  if (father)
  {
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertVariable(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertVariable(this);
        break;
      default:
        std::cerr << "Illegal parent for variable.\n";
        assert(DS_FALSE);
        break;
    }
  }
  if (init)
  {
    if (init->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      init->SetParent(this);
    }
  }
  if (exported_as)
  {
    if (exported_as->GetParent() == NULL)
    {
      exported_as->SetParent(this);
    }
  }
}

DSVariable::DSVariable(DSObject     *father,
                       DSString&     n, 
                       DSSortRef     s, 
                       DSExpression *i,
                       DSBoolean     reveal,
                       DSBoolean     exprt,
                       DSString&     exprt_as) :
  DSNamedObject(DS_VARIABLE, n, father),
  sort_ref(s), 
  init(i),
  revealed(reveal),
  exported(exprt),
  exported_as(&exprt_as)
{
  inout = DS_FALSE;
  history = DS_FALSE;

  if (father)
  {
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertVariable(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertVariable(this);
        break;
      default:
        std::cerr << "Illegal parent for variable.\n";
        assert(DS_FALSE);
        break;
    }
  }
  if (init)
  {
    if (init->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      init->SetParent(this);
    }
  }
  if (exported_as)
  {
    if (exported_as->GetParent() == NULL)
    {
      exported_as->SetParent(this);
    }
  }
}

DSVariable::DSVariable(DSObject     *father,
                       const char   *n, 
                       DSSortRef     s, 
                       DSExpression *i,
                       DSBoolean     reveal,
                       DSBoolean     exprt,
                       const char   *exprt_as) :
  DSNamedObject(DS_VARIABLE, n, father),
  sort_ref(s), 
  init(i),
  revealed(reveal),
  exported(exprt)
{
  inout = DS_FALSE;
  history = DS_FALSE;

  if (exprt_as)
  {
    exported_as = new DSString(this, exprt_as);
    assert(exported_as);
  }
  else
  {
    exported_as = NULL;
  }

  if (father)
  {
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertVariable(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertVariable(this);
        break;
      default:
        std::cerr << "Illegal parent for variable.\n";
        assert(DS_FALSE);
        break;
    }
  }
  if (init)
  {
    if (init->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      init->SetParent(this);
    }
  }
}

DSVariable::DSVariable(DSObject     *father,
                       DSString     *n, 
                       DSSortRef     s,
                       DSBoolean     io) :
  DSNamedObject(DS_FORMALPARAM, n, father),
  sort_ref(s), 
  inout(io)
{
  init = NULL;
  revealed = DS_FALSE;
  exported = DS_FALSE;
  exported_as = NULL;
  history = DS_FALSE;

  if (father)
  {
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertFormalParam(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertFormalParam(this);
        break;
      default:
        std::cerr << "Illegal parent for formal param.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

DSVariable::DSVariable(DSObject     *father,
                       DSString&     n, 
                       DSSortRef     s, 
                       DSBoolean     io) :
  DSNamedObject(DS_FORMALPARAM, n, father),
  sort_ref(s),
  inout(io)
{
  init = NULL;
  revealed = DS_FALSE;
  exported = DS_FALSE;
  exported_as = NULL;
  history = DS_FALSE;

  if (father)
  {
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertFormalParam(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertFormalParam(this);
        break;
      default:
        std::cerr << "Illegal parent for formal param.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

DSVariable::DSVariable(DSObject     *father,
                       const char   *n, 
                       DSSortRef     s, 
                       DSBoolean     io) :
  DSNamedObject(DS_FORMALPARAM, n, father),
  sort_ref(s),
  inout(io)
{
  init = NULL;
  revealed = DS_FALSE;
  exported = DS_FALSE;
  exported_as = NULL;
  history = DS_FALSE;

  if (father)
  {
    switch(father->GetType())
    {
      case DS_PROCESS:
        ((DSProcess*)father)->InsertFormalParam(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertFormalParam(this);
        break;
      default:
        std::cerr << "Illegal parent for formal param.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSVariable::~DSVariable(void)
{
  if (init) delete init;
  if (exported_as) delete exported_as;
}

/****************************************************************************
 * GetSortRef(): Liefert die Sorte zurueck, die in dem referenzierten Objekt
 *               der Klasse DSSort gespeichert ist
 *               Ergebnis: ein Enum-Wert
 *               Seiteneffekte: keine
 ****************************************************************************/

DSSortRef DSVariable::GetSortRef(void) const
{
  return sort_ref;
}

/****************************************************************************
 * GetInit(): Liefert den Initialwert zurueck
 *            Ergebnis: Zeiger auf DSExpression
 *            Seiteneffekte: keine
 ****************************************************************************/

DSExpression *DSVariable::GetInit(void) const
{
  return init;
}

DSBoolean DSVariable::GetRevealed(void) const
{
  return revealed;
}

DSBoolean DSVariable::GetExported(void) const
{
  return exported;
}

DSString *DSVariable::GetExportedAs(void) const
{
  return exported_as;
}

DSBoolean DSVariable::GetIsInOut(void) const
{
  return inout;
}

DSBoolean DSVariable::GetIsHistory(void) const
{
  return history;
}

/****************************************************************************
 * SetSortRef(): Speichert den uebergebenen Wert
 *               -> sort: Wert vom Typ Enum
 *               Ergebnis: TRUE
 *               Seiteneffekte: keine
 ****************************************************************************/

DSResult DSVariable::SetSortRef(DSSortRef sort)
{
  sort_ref = sort;
  return DS_OK;
}

/****************************************************************************
 * SetInit(): Speichert den uebergebenen Wert
 *            -> ini: Stringzeiger
 *            Ergebnis: TRUE
 *            Seiteneffekte: keine
 ****************************************************************************/

DSResult DSVariable::SetInit(DSExpression *ini)
{
  if (init == ini) return DS_OK;

  if (init) delete init;
  init = ini;

  if (init != NULL)
  {
    if (init->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      init->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSVariable::SetRevealed(DSBoolean flag)
{
  revealed = flag;
  return DS_OK;
}

DSResult DSVariable::SetExported(DSBoolean flag)
{
  exported = flag;
  return DS_OK;
}

DSResult DSVariable::SetExportedAs(DSString *n)
{
  if (exported_as == n) return DS_OK;

  if (exported_as) delete exported_as;
  exported_as = n;

	if (exported_as != NULL)
  {
    if (exported_as->GetParent() == NULL)
    {
      exported_as->SetParent(this);
    }
  }
	
  return DS_OK;
}

DSResult DSVariable::SetExportedAs(DSString &n)
{
  if (exported_as == &n) return DS_OK;

  if (exported_as) delete exported_as;
  exported_as = &n;

  if (exported_as->GetParent() == NULL)
  {
    exported_as->SetParent(this);
  }

	return DS_OK;
}

DSResult DSVariable::SetExportedAs(const char *n)
{
  if (exported_as) delete exported_as;
  exported_as = new DSString(this, n);
  assert(exported_as);

  return DS_OK;
}

DSResult DSVariable::SetIsInOut(DSBoolean flag)
{
  inout = flag;
  return DS_OK;
}

DSResult DSVariable::SetIsHistory(DSBoolean flag)
{
  history = flag;
  return DS_OK;
}

DSObject *DSVariable::Clone(DSObject *father, DSObject *fill_this) const
{
  DSVariable *new_variable;

  if (fill_this == NULL)
  {
    new_variable = (DSVariable *)New(father);
    assert(new_variable);
  }
  else
  {
    assert(fill_this->GetType() == DS_VARIABLE);
    new_variable = (DSVariable *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_variable);

  new_variable->SetSortRef(GetSortRef());

  if (GetInit())
  {
    new_variable->SetInit((DSExpression *)GetInit()->Clone((DSObject *)new_variable));
  }

  new_variable->SetRevealed(GetRevealed());
  new_variable->SetExported(GetExported());

  if (GetExportedAs())
  {
    new_variable->SetExportedAs((DSString *)GetExportedAs()->Clone((DSObject *)new_variable));
  }

  new_variable->SetIsInOut(GetIsInOut());

  return new_variable;
}

DSResult DSVariable::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (GetName()) GetName()->Write(writer, what);
  if (sort_ref) sort_ref->Write(writer, what);
  if (init) init->Write(writer, what);
  if (exported_as) exported_as->Write(writer, what);

  return DS_OK;
}
