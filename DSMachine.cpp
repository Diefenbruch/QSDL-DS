/****************************************************************************
 *                 Modul: $RCSfile: DSMachine.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer ein QSDL-Machine bereit.
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

#include "DSMachine.h"
#include "DSBlock.h"  // wegen parent
#include "DSExpression.h"
#include "DSMachineServiceSpeed.h"
#include "DSSensor.h"

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

DSMachine::DSMachine(DSObject     *father,
                     DSString     *n,
                     DSExpression *server,
                     DSExpression *dcpl) :
  DSNamedObject(DS_MACHINE, n, father),
  number_of_servers(server),
  discipline(dcpl)
{
  service_speed_list = NULL;

  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    switch(father->GetType())
    {
      case DS_BLOCK:
        ((DSBlock*)father)->InsertMachine(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  if (discipline)
  {
    if (discipline->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      discipline->SetParent(this);
    }
  }
  if (number_of_servers)
  {
    if (number_of_servers->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_servers->SetParent(this);
    }
  }
}

DSMachine::DSMachine(DSObject     *father,
                     DSString     &n,
                     DSExpression *server,
                     DSExpression *dcpl) :
  DSNamedObject(DS_MACHINE, n, father),
  number_of_servers(server),
  discipline(dcpl)
{
  service_speed_list = NULL;

  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    switch(father->GetType())
    {
      case DS_BLOCK:
        ((DSBlock*)father)->InsertMachine(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  if (discipline)
  {
    if (discipline->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      discipline->SetParent(this);
    }
  }
  if (number_of_servers)
  {
    if (number_of_servers->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_servers->SetParent(this);
    }
  }
}

DSMachine::DSMachine(DSObject *father,
                     const char *n,
                     DSExpression *server,
                     DSExpression *dcpl) :
  DSNamedObject(DS_MACHINE, n, father),
  number_of_servers(server),
  discipline(dcpl)
{
  service_speed_list = NULL;
  
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    switch(father->GetType())
    {
      case DS_BLOCK:
        ((DSBlock*)father)->InsertMachine(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  if (discipline)
  {
    if (discipline->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      discipline->SetParent(this);
    }
  }
  if (number_of_servers)
  {
    if (number_of_servers->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_servers->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSMachine::~DSMachine(void)
{
  if (service_speed_list) delete service_speed_list;
  if (number_of_servers) delete number_of_servers;
  if (discipline) delete discipline;
}

DSExpression *DSMachine::GetNumberOfServers(void) const
{
  return number_of_servers;
}

DSExpression *DSMachine::GetDiscipline(void) const
{
  return discipline;
}

DSMachineServiceSpeedList* DSMachine::GetMachineServiceSpeedList(void) const
{
  return service_speed_list;
}

DSMachineServiceSpeed *DSMachine::GetFirstMachineServiceSpeed(void) const
{
  if (service_speed_list == NULL)
  {
    return NULL;
  }

  if (service_speed_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return service_speed_list->GetCurrentData();
}

DSMachineServiceSpeed *DSMachine::GetNextMachineServiceSpeed(void) const
{
  if (service_speed_list == NULL)
  {
    return NULL;
  }

  if (service_speed_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return service_speed_list->GetCurrentData();
}

DSResult DSMachine::SetNumberOfServers(DSExpression *server)
{
  if (number_of_servers == server) return DS_OK;

  if (number_of_servers) delete number_of_servers;
  number_of_servers = server;

  if (number_of_servers != NULL)
  {
    if (number_of_servers->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      number_of_servers->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSMachine::SetDiscipline(DSExpression *dcpl)
{
  if (discipline == dcpl) return DS_OK;

  if (discipline) delete discipline;
  discipline = dcpl;

  if (discipline != NULL)
  {
    if (discipline->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      discipline->SetParent(this);
    }
  }
  return DS_OK;
}

DSResult DSMachine::SetMachineServiceSpeedList(DSMachineServiceSpeedList *list)
{
  DSMachineServiceSpeed *speed;
  DSResult status;

  if (service_speed_list == list) return DS_OK;

  if (service_speed_list) delete service_speed_list;
  service_speed_list = list;

  if (service_speed_list)
  {
    for (status = service_speed_list->MoveFirst();
         status == DS_OK;
         status = service_speed_list->MoveNext())
    {
      speed = service_speed_list->GetCurrentData();
      assert(speed);
      if (speed->GetParent() == NULL) // Vater noch nicht gesetzt ?
      {
        speed->SetParent(this);
      }
    }
  }
  return DS_OK;
}

DSResult DSMachine::InsertMachineServiceSpeed(DSMachineServiceSpeed* service_speed)
{
  assert(service_speed);
  if (service_speed_list == NULL)
  {
    service_speed_list = new DSMachineServiceSpeedList;
    assert(service_speed_list != NULL);
  }
  if (service_speed->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    service_speed->SetParent(this);
  }
  return service_speed_list->Append(service_speed);
}

DSObject *DSMachine::Clone(DSObject *father, DSObject *fill_this) const
{
  DSMachine *new_machine;

  if (fill_this == NULL)
  {
    new_machine = (DSMachine *)New(father);
    assert(new_machine);
  }
  else
  {
    assert(fill_this->GetType() == DS_MACHINE);
    new_machine = (DSMachine *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_machine);

  if (GetNumberOfServers())
  {
    new_machine->SetNumberOfServers((DSExpression *)GetNumberOfServers()->Clone((DSObject *)new_machine));
  }

  if (GetDiscipline())
  {
    new_machine->SetDiscipline((DSExpression *)GetDiscipline()->Clone((DSObject *)new_machine));
  }

  if (GetMachineServiceSpeedList())
  {
    new_machine->SetMachineServiceSpeedList(GetMachineServiceSpeedList()->Clone((DSObject *)new_machine));
  }

  return new_machine;
}

DSResult DSMachine::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSMachine::Run(DSWriter *writer, DSType object_type,
                        DSCardinal what) const
{
  DSResult               result;
  DSMachineServiceSpeed *machine_service_speed;
  DSSensorRef         sensor;

  switch(object_type)
  {
    case DS_MACHINESERVICESPEED:
      for (machine_service_speed = GetFirstMachineServiceSpeed();
           machine_service_speed;
           machine_service_speed = GetNextMachineServiceSpeed())
      {
        result = machine_service_speed->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_SENSOR:
      for (sensor = GetFirstSensor();
           sensor;
           sensor = GetNextSensor())
      {
        result = sensor->Write(writer, what);
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

