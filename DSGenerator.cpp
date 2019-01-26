/****************************************************************************
 *                 Modul: $RCSfile: DSGenerator.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/11/25 15:09:22 $
 * $Revision: 1.3 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines SDL-Generator-Konstruktes <generator transformation>
 *
 * Funktionen: GetIndexSortRef(): liefert Zeiger auf Indexart (char,..)
 *             GetElemSortRef():  liefert Zeiger auf Elementsorte (char,..)
 *             SetIndexSortRef(): speichert Indexart
 *             SetElemSortRef():  speichert Elementsorte
 *             Save(): Abspeicherung in eine Datei
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

#include "DSGenerator.h"
#include "DSString.h"
#include "DSOperandLiteral.h"

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

DSGenerator::DSGenerator(DSObject *father,
                         DSString *sort_name,
                         DSString *gen_name,
                         DSSortRefList *sorts,
                         DSOperandLiteral *emptystring) :
  DSSortExtended(father, sort_name, DS_SORT_GENERATOR, NULL, NULL, DS_FALSE, DS_TRUE),
  DSSortRefComponent(sorts),
  generator_name(gen_name),
  literal(emptystring)
{
}

DSGenerator::DSGenerator(DSObject *father,
                         DSString& sort_name,
                         DSString& gen_name,
                         DSSortRefList *sorts,
                         DSOperandLiteral *emptystring) :
  DSSortExtended(father, &sort_name, DS_SORT_GENERATOR, NULL, NULL, DS_FALSE, DS_TRUE),
  DSSortRefComponent(sorts),
  generator_name(&gen_name),
  literal(emptystring)
{
}

DSGenerator::DSGenerator(DSObject *father,
                         const char *sort_name,
                         const char *gen_name,
                         DSSortRefList *sorts,
                         DSOperandLiteral *emptystring) :
  DSSortExtended(father, sort_name, DS_SORT_GENERATOR, NULL, NULL, DS_FALSE, DS_TRUE),
  DSSortRefComponent(sorts),
  literal(emptystring)
{
  if (gen_name)
  {
    generator_name = new DSString(gen_name);
    assert(generator_name);
  }
  else
  {
    generator_name = NULL;
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSGenerator::~DSGenerator(void)
{
  if (generator_name) delete generator_name;
}

DSString* DSGenerator::GetGeneratorName(void) const
{
  return generator_name;
}

DSOperandLiteral* DSGenerator::GetLiteral(void) const
{
  return literal;
}

DSResult DSGenerator::SetGeneratorName(DSString *new_name)
{
  if (generator_name == new_name) return DS_OK;

  if (generator_name) delete generator_name;
  generator_name = new_name;

  if (generator_name != NULL)
  {
    if (generator_name->GetParent() == NULL)
    {
      generator_name->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSGenerator::SetGeneratorName(DSString &new_name)
{
  if (generator_name == &new_name) return DS_OK;

  if (generator_name) delete generator_name;
  generator_name = &new_name;

  if (generator_name != NULL)
  {
    if (generator_name->GetParent() == NULL)
    {
      generator_name->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSGenerator::SetGeneratorName(const char *new_name)
{
  if (generator_name) delete generator_name;
  generator_name = new DSString(new_name);
  assert(generator_name);
  return DS_OK;
}


DSResult DSGenerator::SetLiteral(DSOperandLiteral *new_literal)
{
  if (literal == new_literal) return DS_OK;

  if (literal) delete literal;
  literal = new_literal;

  if (literal != NULL)
  {
    if (literal->GetParent() == NULL)
    {
      literal->SetParent(this);
    }
  }

  return DS_OK;
}


DSObject *DSGenerator::Clone(DSObject *father, DSObject *fill_this) const
{
  DSGenerator *new_generator;

  if (fill_this == NULL)
  {
    new_generator = (DSGenerator *)New(father);
    assert(new_generator);
  }
  else
  {
    assert(fill_this->GetType() == DS_SORT);
    new_generator = (DSGenerator *)fill_this;
  }

  // Basisklasse clonen:
  DSSortExtended::Clone(father, new_generator);
  
  if (GetSortRefList())
  {
    new_generator->SetSortRefList((DSSortRefList *)GetSortRefList()->Clone((DSObject *)new_generator));
  }
  
  if (GetGeneratorName())
  {
    new_generator->SetGeneratorName((DSString *)GetGeneratorName()->Clone((DSObject *)new_generator));
  }

  return new_generator;
}

DSResult DSGenerator::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (generator_name) generator_name->Write(writer, what);

  Run(writer, DS_SORT, what);

  return DS_OK;
}

DSResult DSGenerator::Run(DSWriter *writer, DSType object_type,
                          DSCardinal what) const
{
  DSResult        result;
  DSSortRef       sort;

  switch(object_type)
  {
    case DS_SORT:
      for (sort = GetFirstSortRef();
           sort;
           sort = GetNextSortRef())
      {
        result = sort->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    default:
      assert(DS_FALSE);
      break;
  }

  return DS_OK;
}
