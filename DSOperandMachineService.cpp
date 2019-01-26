/****************************************************************************
 *                 Modul: $RCSfile: DSOperandMachineService.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung eines MachineServicenoperanden
 *
 * Funktionen: GetMachineServiceRef(): liefert Zeiger auf die MachineService
 *             SetMachineServiceRef(): setzt den Zeiger auf die MachineService
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

#include "DSOperandMachineService.h"
#include "DSMachineService.h"
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

DSOperandMachineService::DSOperandMachineService(DSObject *father,
                                                 DSMachineServiceRef ms_ref) :
  DSOperand(father, DS_OPN_MACHINE_SERVICE),
  machine_service_ref(ms_ref)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandMachineService::~DSOperandMachineService(void)
{
}

DSObject *DSOperandMachineService::New(DSObject *father) const
{
  return new DSOperandMachineService(father);
}

/****************************************************************************
 * GetMachineServiceRef(): liefert Zeiger auf die MachineService
 *                         Ergebnis: Zeiger auf DSMachineService
 *                         Seiteneffekte: keine
 ****************************************************************************/

DSMachineServiceRef DSOperandMachineService::GetMachineServiceRef(void) const
{
  return machine_service_ref;
}

/****************************************************************************
 * SetMachineServiceRef(): setzt Zeiger auf den uebergebenen Dienst
 *                         ->elem: Zeiger auf DSMachineService
 *                         Ergebnis: DS_OK
 *                         Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandMachineService::SetMachineServiceRef(DSMachineServiceRef ms_ref)
{
  machine_service_ref = ms_ref;
  return DS_OK;
}

DSObject *DSOperandMachineService::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandMachineService *new_operand_machine_service;

  if (fill_this == NULL)
  {
    new_operand_machine_service = (DSOperandMachineService *)New(father); // virtueller Konstruktor
    assert(new_operand_machine_service);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_machine_service = (DSOperandMachineService *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_machine_service);

  new_operand_machine_service->SetMachineServiceRef(GetMachineServiceRef());

  return new_operand_machine_service;
}

DSResult DSOperandMachineService::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);
  (void)what;

  return DS_OK;
}
