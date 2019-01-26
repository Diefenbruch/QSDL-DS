/****************************************************************************
 *                 Modul: $RCSfile: DSOperandProcedureCall.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung eines ProcedureCallnoperanden
 *
 * Funktionen: GetProcedureCall(): liefert Zeiger auf den Proceduraufruf
 *             SetProcedureCall(): setzt den Zeiger auf den Proceduraufruf
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

#include "DSOperandProcedureCall.h"
#include "DSCall.h"

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

DSOperandProcedureCall::DSOperandProcedureCall(DSObject *father,
                                               DSCall *procedure_call) :
  DSOperand(father, DS_OPN_PROCEDURE_CALL),
  call(procedure_call)
{
  if (procedure_call)
  {
    if (procedure_call->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      procedure_call->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandProcedureCall::~DSOperandProcedureCall(void)
{
  if (call) delete call;
}

DSObject *DSOperandProcedureCall::New(DSObject *father) const
{
  return new DSOperandProcedureCall(father);
}

/****************************************************************************
 * GetProcedureCall(): liefert Zeiger auf den Proceduraufruf
 *                     Ergebnis: Zeiger auf DSCall
 *                     Seiteneffekte: keine
 ****************************************************************************/

DSCall *DSOperandProcedureCall::GetProcedureCall(void) const
{
  return call;
}

/****************************************************************************
 * SetProcedureCall(): setzt Zeiger auf den Proceduraufruf
 *                     ->procedure_call: Zeiger auf DSCall
 *                     Ergebnis: DS_OK
 *                     Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandProcedureCall::SetProcedureCall(DSCall *procedure_call)
{
  if (call == procedure_call) return DS_OK;

  if (call) delete call;
  call = procedure_call;

  if (call != NULL)
  {
    if (call->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      call->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSOperandProcedureCall::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandProcedureCall *new_operand_call;

  if (fill_this == NULL)
  {
    new_operand_call = (DSOperandProcedureCall *)New(father); // virtueller Konstruktor
    assert(new_operand_call);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_call = (DSOperandProcedureCall *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_call);

  if (GetProcedureCall())
  {
    new_operand_call->SetProcedureCall((DSCall *)GetProcedureCall()->Clone((DSObject *)new_operand_call));
  }

  return new_operand_call;
}

DSResult DSOperandProcedureCall::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (call) call->Write(writer, what);

  return DS_OK;
}
