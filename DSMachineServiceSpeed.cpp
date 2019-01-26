/****************************************************************************
 *                 Modul: $RCSfile: DSMachineServiceSpeed.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines QSDL-Maschinendienstes mit seiner spezifischen
 *          Geschwindigkeit
 *
 * Funktionen: GetServiceName(): Name des Dienstes
 *             GetSpeed(): Ausfuehrungsgeschwindigkeit
 *             SetServiceName(): setzt den Dienstnamen
 *             SetSpeed(): setzt die Geschwindigkeit
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

#include "DSMachineServiceSpeed.h"
#include "DSMachine.h" // wegen parent
#include "DSExpression.h"
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

DSMachineServiceSpeed::DSMachineServiceSpeed(DSObject            *father,
                                               DSMachineServiceRef service,
                                               DSExpression        *spd) :
  DSObject(DS_MACHINESERVICESPEED, father),
  service_ref(service),
  speed(spd)
{
  if (father)
  {
    ((DSMachine*)father)->InsertMachineServiceSpeed(this);
  }
  if (speed)
  {
    if (speed->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      speed->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSMachineServiceSpeed::~DSMachineServiceSpeed(void)
{
  if (speed) delete speed;
}

/****************************************************************************
 * GetMachineService(): liefert Zeiger auf Namen des Dienstes
 *                      Ergebnis: Zeiger auf DSString
 *                      Seiteneffekte: keine
 ****************************************************************************/

DSMachineServiceRef DSMachineServiceSpeed::GetMachineServiceRef(void) const
{
  return service_ref;
}

/****************************************************************************
 * GetSpeed(): liefert die Geschwindigkeit, mit welcher die Maschine
 *             den Dienst erbringen kann
 *             Ergebnis: Geschwindigkeit (DSSpeed)
 *             Seiteneffekte: keine
 ****************************************************************************/

DSExpression *DSMachineServiceSpeed::GetSpeed(void) const
{
  return speed;
}

/****************************************************************************
 * SetMachineServiceRef(): speichert den Namen des Dienstes
 *                         -> service: Dienst
 *                         Ergebnis: DS_OK
 *                         Seiteneffekte: keine
 ****************************************************************************/

DSResult DSMachineServiceSpeed::SetMachineServiceRef(DSMachineServiceRef service)
{
  service_ref = service;
  return DS_OK;
}

/****************************************************************************
 * SetSpeed(): speichert die Geschwindigkeit mit der die Maschine
 *             den Dienst erbringen kann
 *             -> spd: Geschwindigkeit
 *             Ergebnis: DS_OK
 *             Seiteneffekte: keine
 ****************************************************************************/

DSResult DSMachineServiceSpeed::SetSpeed(DSExpression *spd)
{
  if (speed == spd) return DS_OK;

  if (speed) delete speed;
  speed = spd;

  if (speed != NULL)
  {
    if (speed->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      speed->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSMachineServiceSpeed::Clone(DSObject *father, DSObject *fill_this) const
{
  DSMachineServiceSpeed *new_machine_service_speed;

  if (fill_this == NULL)
  {
    new_machine_service_speed = (DSMachineServiceSpeed *)New(father);
    assert(new_machine_service_speed);
  }
  else
  {
    assert(fill_this->GetType() == DS_MACHINESERVICESPEED);
    new_machine_service_speed = (DSMachineServiceSpeed *)fill_this;
  }

  if (GetSpeed())
  {
    new_machine_service_speed->SetSpeed((DSExpression *)GetSpeed()->Clone((DSObject *)new_machine_service_speed));
  }

  new_machine_service_speed->SetMachineServiceRef(GetMachineServiceRef());

  return new_machine_service_speed;
}

DSResult DSMachineServiceSpeed::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (service_ref) service_ref->Write(writer, what);
  if (speed) speed->Write(writer, what);

  return DS_OK;
}
