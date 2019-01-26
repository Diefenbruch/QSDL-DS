/****************************************************************************
 *                 Modul: $RCSfile: DSVariableAccessElem.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines SDL-Variablenzugriffs.
 *
 * Funktionen: 
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

#include <iostream>

#include "DSVariableAccessElem.h"
#include "DSVariableAccess.h"      // wegen parent

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

DSVariableAccessElem::DSVariableAccessElem(DSObject           *father,
                                           DSVariableAccessTag t) :
  DSObject(DS_VARIABLEACCESSELEM, father),
  tag(t) 
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_VARIABLEACCESS:
        ((DSVariableAccess*)father)->InsertElem(this);
        break;
      default:
        std::cerr << "Illegal parent for variable access elem." << std::endl;
        assert(DS_FALSE);
        break;
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSVariableAccessElem::~DSVariableAccessElem(void)
{
}

/****************************************************************************
 * GetTag(): Liefert Art des Zugriffselements (index oder feld)
 *           Ergebnis: ein Enum-Wert aus DSVariableAccessTag (s. DSBasicTypes.h)
 *           Seiteneffekte: keine
 ****************************************************************************/

DSVariableAccessTag DSVariableAccessElem::GetTag(void) const
{
  return tag;
}

/****************************************************************************
 * SetTag(): Speichert den uebergebenen Typ
 *           -> tag_type: Enum-Typ
 *           Ergebnis: TRUE
 *           Seiteneffekte: keine
 ****************************************************************************/

DSResult DSVariableAccessElem::SetTag(DSVariableAccessTag tag_type)
{
  tag = tag_type;
  return DS_OK;
}

DSObject *DSVariableAccessElem::Clone(DSObject *father,
                                      DSObject *fill_this) const
{
  DSVariableAccessElem *new_variable_access_elem;

  if (fill_this == NULL)
  {
    new_variable_access_elem = (DSVariableAccessElem *)New(father);
    assert(new_variable_access_elem);
  }
  else
  {
    assert(fill_this->GetType() == DS_VARIABLEACCESSELEM);
    new_variable_access_elem = (DSVariableAccessElem *)fill_this;
  }

  new_variable_access_elem->SetTag(GetTag());

  return new_variable_access_elem;
}

DSResult DSVariableAccessElem::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}
