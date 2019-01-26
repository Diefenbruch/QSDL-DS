/****************************************************************************
 *                 Modul: $RCSfile: DSOperandSynonym.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung eines Synonymnoperanden
 *
 * Funktionen: GetSynonymRef(): liefert Zeiger auf die Synonym
 *             SetSynonymRef(): setzt den Zeiger auf die Synonym
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

#include "DSOperandSynonym.h"
#include "DSSynonym.h"
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

DSOperandSynonym::DSOperandSynonym(DSObject *father,
                                   DSSynonymRef syn_ref) :
  DSOperand(father, DS_OPN_SYNONYM),
  synonym_ref(syn_ref)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandSynonym::~DSOperandSynonym(void)
{
}

DSObject *DSOperandSynonym::New(DSObject *father) const
{
  return new DSOperandSynonym(father);
}

/****************************************************************************
 * GetSynonymRef(): liefert Zeiger auf die Synonym
 *                   Ergebnis: Zeiger auf DSSynonym
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSSynonymRef DSOperandSynonym::GetSynonymRef(void) const
{
  return synonym_ref;
}

/****************************************************************************
 * SetSynonymRef(): setzt Zeiger auf die Synonym
 *                   ->elem: Zeiger auf DSSynonym
 *                   Ergebnis: DS_OK
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandSynonym::SetSynonymRef(DSSynonymRef syn_ref)
{
  synonym_ref = syn_ref;
  return DS_OK;
}

DSObject *DSOperandSynonym::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandSynonym *new_operand_synonym;

  if (fill_this == NULL)
  {
    new_operand_synonym = (DSOperandSynonym *)New(father); // virtueller Konstruktor
    assert(new_operand_synonym);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_synonym = (DSOperandSynonym *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_synonym);

  new_operand_synonym->SetSynonymRef(GetSynonymRef());

  return new_operand_synonym;
}

DSResult DSOperandSynonym::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (synonym_ref) synonym_ref->Write(writer, what);

  return DS_OK;
}
