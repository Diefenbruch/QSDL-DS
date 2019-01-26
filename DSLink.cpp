/****************************************************************************
 *                 Modul: $RCSfile: DSLink.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/12/19 13:10:25 $
 * $Revision: 1.2 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer ein QSDL-Link bereit.
 *
 * Funktionen: GetName()               liefert den Linknamen
 *             GetProcessRef()         liefert eine Referenz auf den Process
 *             GetMachineRef()         liefert eine Referenz auf die Maschine
 *             GetMachineServiceList() liefert MachineService-Liste des Links
 *             SetName()               setzt den Linknamen
 *             SetProcessRef()         setzt die Refenrenz auf den Process
 *             SetMachineRef()         setzt die Refenrenz auf die Maschine
 *             SetMachineServiceList() setzt MachineService-Liste des Links
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
 
#include "DSLink.h"
#include "DSBlock.h"  // wegen parent
#include "DSMachineService.h"
#include "DSProcess.h"
#include "DSMachine.h"

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

DSLink::DSLink(DSObject *father,
               DSString *n,
               DSProcessRef p_ref,
               DSMachineRef m_ref) :
  DSNamedObject(DS_LINK, n, father),
  process_ref(p_ref),
  machine_ref(m_ref)
{
  machineservice_ref_list = NULL;
  if (father)
  {
    ((DSBlock*)father)->InsertLink(this);
  }
}

DSLink::DSLink(DSObject *father,
               DSString& n,
               DSProcessRef p_ref,
               DSMachineRef m_ref) :
  DSNamedObject(DS_LINK, n, father),
  process_ref(p_ref),
  machine_ref(m_ref)
{
  machineservice_ref_list = NULL;
  if (father)
  {
    ((DSBlock*)father)->InsertLink(this);
  }
}

DSLink::DSLink(DSObject *father,
               const char *n,
               DSProcessRef p_ref,
               DSMachineRef m_ref) :
  DSNamedObject(DS_LINK, n, father),
  process_ref(p_ref),
  machine_ref(m_ref)
{
  machineservice_ref_list = NULL;
  if (father)
  {
    ((DSBlock*)father)->InsertLink(this);
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSLink::~DSLink(void)
{
  if (machineservice_ref_list) delete machineservice_ref_list;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSLink::New(DSObject *father) const
{
  return new DSLink(father);
}

DSProcessRef DSLink::GetProcessRef(void) const
{
  return process_ref;
}

DSMachineRef DSLink::GetMachineRef(void) const
{
  return machine_ref;
}

DSMachineServiceRefList* DSLink::GetMachineServiceRefList(void) const
{
  return machineservice_ref_list;
}

DSMachineServiceRef DSLink::GetFirstMachineServiceRef(void) const
{
  if (machineservice_ref_list == NULL)
  {
    return NULL;
  }

  if (machineservice_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return machineservice_ref_list->GetCurrentData();
}

DSMachineServiceRef DSLink::GetNextMachineServiceRef(void) const
{
  if (machineservice_ref_list == NULL)
  {
    return NULL;
  }

  if (machineservice_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return machineservice_ref_list->GetCurrentData();
}

DSBoolean DSLink::IsMachineServiceRefInList(DSMachineServiceRef) const
{
  return DS_TRUE;
}

DSResult DSLink::SetProcessRef(DSProcessRef ref)
{
  process_ref = ref;
  return DS_OK;
}

DSResult DSLink::SetMachineRef(DSMachineRef ref)
{
  machine_ref = ref;
  return DS_OK;
}

DSResult DSLink::SetMachineServiceRefList(DSMachineServiceRefList *list)
{
  if (machineservice_ref_list == list) return DS_OK;

  if (machineservice_ref_list != NULL)
  {
    delete machineservice_ref_list;
  }
  machineservice_ref_list = list;
  return DS_OK;
}

DSResult DSLink::InsertMachineServiceRef(DSMachineServiceRef machineservice_ref)
{
  assert(machineservice_ref != NULL);
  if (machineservice_ref_list == NULL)
  {
    machineservice_ref_list = new DSMachineServiceRefList;
    assert(machineservice_ref_list != NULL);
  }
  return machineservice_ref_list->Append(machineservice_ref);
}

DSObject *DSLink::Clone(DSObject *father, DSObject *fill_this) const
{
  DSLink *new_link;

  if (fill_this == NULL)
  {
    new_link = (DSLink *)New(father);
    assert(new_link);
  }
  else
  {
    assert(fill_this->GetType() == DS_LINK);
    new_link = (DSLink *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_link);

  new_link->SetProcessRef(GetProcessRef());
  new_link->SetMachineRef(GetMachineRef());

  if (GetMachineServiceRefList())
  {
    new_link->SetMachineServiceRefList((DSMachineServiceRefList *)GetMachineServiceRefList()->Clone((DSObject *)new_link));
  }

  return new_link;
}

DSResult DSLink::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSLink::Run(DSWriter *writer, DSType object_type,
                     DSCardinal what) const
{
  DSResult            result;
  DSMachineServiceRef machineservice;

  switch(object_type)
  {
    case DS_MACHINESERVICE:
      for (machineservice = GetFirstMachineServiceRef();
           machineservice;
           machineservice = GetNextMachineServiceRef())
      {
        result = machineservice->Write(writer, what);
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
