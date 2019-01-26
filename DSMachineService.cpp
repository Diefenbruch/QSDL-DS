/****************************************************************************
 *                 Modul: $RCSfile: DSMachineService.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/10/22 16:09:53 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Variablen in Verbindung mit einer MachineServicedefinition
 *
 * Funktionen: GetName(): Gibt einen Zeiger auf den Dienstnamen zurueck
 *             GetSortList(): Liefert Zeiger auf Liste zurueck
 *             SetName(): Speichert MachineServicenamen
 *             SetSortList(): Speichert die Sortenliste des Deinstes
 *             Save(): Abspeicherung der Infos in einer Datei
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

#include "DSMachineService.h"
#include "DSSystem.h"  // wegen parent
#include "DSBlock.h"  // wegen parent
#include "DSBlockSubstructure.h"  // wegen parent
#include "DSSort.h"

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

DSMachineService::DSMachineService(DSObject      *father,
                                   DSString      *n, 
                                   DSSortRefList *sort_list) :
  DSNamedObject(DS_MACHINESERVICE, n, father),
  DSSortRefComponent(sort_list)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertMachineService(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertMachineService(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertMachineService(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSMachineService::DSMachineService(DSObject      *father,
                                   DSString      &n, 
                                   DSSortRefList *sort_list) :
  DSNamedObject(DS_MACHINESERVICE, n, father),
  DSSortRefComponent(sort_list)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertMachineService(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertMachineService(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertMachineService(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSMachineService::DSMachineService(DSObject      *father,
                                   const char    *n, 
                                   DSSortRefList *sort_list) :
  DSNamedObject(DS_MACHINESERVICE, n, father),
  DSSortRefComponent(sort_list)
{
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertMachineService(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertMachineService(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertMachineService(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSMachineService::~DSMachineService(void)
{
}

DSObject *DSMachineService::Clone(DSObject *father, DSObject *fill_this) const
{
  DSMachineService *new_machine_service;

  if (fill_this == NULL)
  {
    new_machine_service = (DSMachineService *)New(father);
    assert(new_machine_service);
  }
  else
  {
    assert(fill_this->GetType() == DS_MACHINESERVICE);
    new_machine_service = (DSMachineService *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_machine_service);

  if (GetSortRefList())
  {
    new_machine_service->SetSortRefList((DSSortRefList *)GetSortRefList()->Clone((DSObject *)new_machine_service));
  }
  
  return new_machine_service;
}

DSResult DSMachineService::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSMachineService::Run(DSWriter *writer, DSType object_type,
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
