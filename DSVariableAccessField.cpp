/****************************************************************************
 *                 Modul: $RCSfile: DSVariableAccessField.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines Feldzugriffs als Teil eines SDL-Variablenzugriffs.
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

#include "DSVariableAccessField.h"
#include "DSNameSort.h"
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

DSVariableAccessField::DSVariableAccessField(DSObject      *father,
                                             DSNameSortRef  field) :
  DSVariableAccessElem(father, DS_ACCESS_FIELD),
  field_ref(field)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSVariableAccessField::~DSVariableAccessField(void)
{
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSVariableAccessField::New(DSObject *father) const
{
  return new DSVariableAccessField(father);
}

DSNameSortRef DSVariableAccessField::GetField(void) const
{
  return field_ref;
}

DSResult DSVariableAccessField::SetField(DSNameSortRef field)
{
  field_ref = field;
  return DS_OK;
}

DSObject *DSVariableAccessField::Clone(DSObject *father, DSObject *fill_this) const
{
  DSVariableAccessField *new_access_field;

  if (fill_this == NULL)
  {
    new_access_field = (DSVariableAccessField *)New(father); // virtueller Konstruktor
    assert(new_access_field);
  }
  else
  {
    assert(fill_this->GetType() == DS_VARIABLEACCESSELEM);
    new_access_field = (DSVariableAccessField *)fill_this;
  }

  // Basisklassen clonen:
  DSVariableAccessElem::Clone(father, new_access_field);

  new_access_field->SetField(GetField());

  return new_access_field;
}

DSResult DSVariableAccessField::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (field_ref) field_ref->Write(writer, what);

  return DS_OK;
}
