/****************************************************************************
 *                 Modul: $RCSfile: DSVariableAccessIndex.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines Indexzugriffs als Teil eines SDL-Variablenzugriffs.
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

#include "DSVariableAccessIndex.h"
#include "DSExpression.h"

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

DSVariableAccessIndex::DSVariableAccessIndex(DSObject     *father,
                                             DSExpression *ind) :
  DSVariableAccessElem(father, DS_ACCESS_INDEX),
  array_index(ind)
{
  if (array_index)
  {
    if (array_index->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      array_index->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSVariableAccessIndex::~DSVariableAccessIndex(void)
{
  if (array_index) delete array_index;
}

DSObject *DSVariableAccessIndex::New(DSObject *father) const
{
  return new DSVariableAccessIndex(father);
}

DSExpression *DSVariableAccessIndex::GetIndex(void) const
{
  return array_index;
}

DSResult DSVariableAccessIndex::SetIndex(DSExpression *ind)
{
  if (array_index == ind) return DS_OK;

  if (array_index) delete array_index;
  array_index = ind;

  if (array_index != NULL)
  {
    if (array_index->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      array_index->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSVariableAccessIndex::Clone(DSObject *father, DSObject *fill_this) const
{
  DSVariableAccessIndex *new_access_index;

  if (fill_this == NULL)
  {
    new_access_index = (DSVariableAccessIndex *)New(father); // virtueller Konstruktor
    assert(new_access_index);
  }
  else
  {
    assert(fill_this->GetType() == DS_VARIABLEACCESSELEM);
    new_access_index = (DSVariableAccessIndex *)fill_this;
  }

  // Basisklassen clonen:
  DSVariableAccessElem::Clone(father, new_access_index);

  new_access_index->SetIndex((DSExpression *)GetIndex()->Clone((DSObject *)new_access_index));

  return new_access_index;
}

DSResult DSVariableAccessIndex::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (array_index) array_index->Write(writer, what);

  return DS_OK;
}
