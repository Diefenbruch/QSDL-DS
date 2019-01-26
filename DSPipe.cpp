/****************************************************************************
 *                 Modul: $RCSfile: DSPipe.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/12/19 13:10:25 $
 * $Revision: 1.3 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer eine QSDL-Pipe bereit.
 *
 * Funktionen: GetBlock1Ref()            liefert eine Referenz auf den ersten
 *                                       Block
 *             GetBlock2Ref()            liefert eine Referenz auf den zweiten
 *                                       Block
 *             GetMachineServiceList12() liefert MachineServiceliste von
 *                                       Block1 -> Block2
 *             GetMachineServiceList21() liefert MachineServiceliste von
 *                                       Block2 -> Block1
 *             SetBlock1Ref()            setzt die Refenrenz auf den ersten
 *                                       Block
 *             SetBlock2Ref()            setzt die Refenrenz auf den ersten
 *                                       Block
 *             SetMachineServiceList12() setzt MachineService-Liste von
 *                                       Block1 -> Block2
 *             SetMachineServiceList21() setzt MachineService-Liste von
 *                                       Block2 -> Block1
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
 
#include "DSPipe.h"
#include "DSSystem.h"  // wegen parent
#include "DSBlockSubstructure.h" // wegen parent
#include "DSBlock.h"

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

DSPipe::DSPipe(DSObject *father,
               DSString *n,
               DSBlockRef b1_ref,
               DSBlockRef b2_ref) :
  DSNamedObject(DS_PIPE, n, father),
  block1_ref(b1_ref),
  block2_ref(b2_ref)
{
  b1_b2_machineservice_ref_list = NULL;
  b2_b1_machineservice_ref_list = NULL;
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertPipe(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertPipe(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSPipe::DSPipe(DSObject *father,
               DSString& n,
               DSBlockRef b1_ref,
               DSBlockRef b2_ref) :
  DSNamedObject(DS_PIPE, n, father),
  block1_ref(b1_ref),
  block2_ref(b2_ref)
{
  b1_b2_machineservice_ref_list = NULL;
  b2_b1_machineservice_ref_list = NULL;
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertPipe(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertPipe(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSPipe::DSPipe(DSObject *father,
               const char *n,
               DSBlockRef b1_ref,
               DSBlockRef b2_ref) :
  DSNamedObject(DS_PIPE, n, father),
  block1_ref(b1_ref),
  block2_ref(b2_ref)
{
  b1_b2_machineservice_ref_list = NULL;
  b2_b1_machineservice_ref_list = NULL;
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertPipe(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertPipe(this);
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

DSPipe::~DSPipe(void)
{
  if (b1_b2_machineservice_ref_list) delete b1_b2_machineservice_ref_list;
  if (b2_b1_machineservice_ref_list) delete b2_b1_machineservice_ref_list;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSPipe::New(DSObject *father) const
{
  return new DSPipe(father);
}

DSBlockRef DSPipe::GetBlock1Ref(void) const
{
  return block1_ref;
}

DSBlockRef DSPipe::GetBlock2Ref(void) const
{
  return block2_ref;
}

DSMachineServiceRefList* DSPipe::GetMachineServiceRefList12(void) const
{
  return b1_b2_machineservice_ref_list;
}

DSMachineServiceRef DSPipe::GetFirstMachineServiceRef12(void) const
{
  if (b1_b2_machineservice_ref_list == NULL)
  {
    return NULL;
  }

  if (b1_b2_machineservice_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return b1_b2_machineservice_ref_list->GetCurrentData();
}

DSMachineServiceRef DSPipe::GetNextMachineServiceRef12(void) const
{
  if (b1_b2_machineservice_ref_list == NULL)
  {
    return NULL;
  }

  if (b1_b2_machineservice_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return b1_b2_machineservice_ref_list->GetCurrentData();
}

DSMachineServiceRefList* DSPipe::GetMachineServiceRefList21(void) const
{
  return b2_b1_machineservice_ref_list;
}

DSMachineServiceRef DSPipe::GetFirstMachineServiceRef21(void) const
{
  if (b2_b1_machineservice_ref_list == NULL)
  {
    return NULL;
  }

  if (b2_b1_machineservice_ref_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return b2_b1_machineservice_ref_list->GetCurrentData();
}

DSMachineServiceRef DSPipe::GetNextMachineServiceRef21(void) const
{
  if (b2_b1_machineservice_ref_list == NULL)
  {
    return NULL;
  }

  if (b2_b1_machineservice_ref_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return b2_b1_machineservice_ref_list->GetCurrentData();
}

DSBoolean DSPipe::IsMachineServiceRefInList12(DSMachineServiceRef ms_ref) const
{
  DSMachineServiceRef act_ref;

  for (act_ref = GetFirstMachineServiceRef12();
       act_ref != NULL;
       act_ref = GetNextMachineServiceRef12())
  {
    if (act_ref == ms_ref) return DS_TRUE;
  }
  return DS_FALSE;
}

DSBoolean DSPipe::IsMachineServiceRefInList21(DSMachineServiceRef ms_ref) const
{
  DSMachineServiceRef act_ref;

  for (act_ref = GetFirstMachineServiceRef21();
       act_ref != NULL;
       act_ref = GetNextMachineServiceRef21())
  {
    if (act_ref == ms_ref) return DS_TRUE;
  }
  return DS_FALSE;
}

DSResult DSPipe::SetBlock1Ref(DSBlockRef ref)
{
  block1_ref = ref;
  return DS_OK;
}

DSResult DSPipe::SetBlock2Ref(DSBlockRef ref)
{
  block2_ref = ref;
  return DS_OK;
}

DSResult DSPipe::SetMachineServiceRefList12(DSMachineServiceRefList *list)
{
  if (b1_b2_machineservice_ref_list == list) return DS_OK;

  if (b1_b2_machineservice_ref_list) delete b1_b2_machineservice_ref_list;
  b1_b2_machineservice_ref_list = list;
  return DS_OK;
}

DSResult DSPipe::
         InsertMachineServiceRef12(DSMachineServiceRef machineservice_ref)
{
  if (b1_b2_machineservice_ref_list == NULL)
  {
    b1_b2_machineservice_ref_list = new DSMachineServiceRefList;
    assert(b1_b2_machineservice_ref_list != NULL);
  }
  return b1_b2_machineservice_ref_list->Append(machineservice_ref);
}

DSResult DSPipe::SetMachineServiceRefList21(DSMachineServiceRefList *list)
{
  if (b2_b1_machineservice_ref_list == list) return DS_OK;

  if (b2_b1_machineservice_ref_list) delete b2_b1_machineservice_ref_list;
  b2_b1_machineservice_ref_list = list;
  return DS_OK;
}

DSResult DSPipe::
         InsertMachineServiceRef21(DSMachineServiceRef machineservice_ref)
{
  if (b2_b1_machineservice_ref_list == NULL)
  {
    b2_b1_machineservice_ref_list = new DSMachineServiceRefList;
    assert(b2_b1_machineservice_ref_list != NULL);
  }
  return b2_b1_machineservice_ref_list->Append(machineservice_ref);
}

DSObject *DSPipe::Clone(DSObject *father, DSObject *fill_this) const
{
  DSPipe *new_pipe;

  if (fill_this == NULL)
  {
    new_pipe = (DSPipe *)New(father);
    assert(new_pipe);
  }
  else
  {
    assert(fill_this->GetType() == DS_PIPE);
    new_pipe = (DSPipe *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_pipe);

  new_pipe->SetBlock1Ref(GetBlock1Ref());
  new_pipe->SetBlock2Ref(GetBlock2Ref());

  if (GetMachineServiceRefList12())
  {
    new_pipe->SetMachineServiceRefList12((DSMachineServiceRefList *)GetMachineServiceRefList12()->Clone((DSObject *)new_pipe));
  }

  if (GetMachineServiceRefList21())
  {
    new_pipe->SetMachineServiceRefList21((DSMachineServiceRefList *)GetMachineServiceRefList21()->Clone((DSObject *)new_pipe));
  }

  return new_pipe;
}

DSResult DSPipe::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSPipe::Run(DSWriter *writer, DSType object_type,
                     DSCardinal what) const
{
  DSResult            result;
  DSMachineServiceRef machineservice;

  switch(object_type)
  {
    case DS_MACHINESERVICE:
      for (machineservice = GetFirstMachineServiceRef12();
           machineservice;
           machineservice = GetNextMachineServiceRef12())
      {
        result = machineservice->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      for (machineservice = GetFirstMachineServiceRef21();
           machineservice;
           machineservice = GetNextMachineServiceRef21())
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
