/****************************************************************************
 *                 Modul: $RCSfile: DSBlock.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/27 16:31:48 $
 * $Revision: 1.5 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer einen SDL-Block bereit.
 *
 * Funktionen: 
 *
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

#include "DSRef.h"
#include "DSBlock.h"
#include "DSSystem.h"  // wegen parent
#include "DSBlockSubstructure.h"  // wegen parent
#include "DSProcess.h"
#include "DSProcedure.h"  // wegen write
#include "DSChannel2RouteConnection.h"
#include "DSPipe2LinkBinding.h"
#include "DSMachine.h"
#include "DSSort.h"
#include "DSSensor.h"
#include "DSSignalslist.h"
#include "DSSignal.h"
#include "DSString.h"
#include "DSSynonym.h"
#include "DSOperandConstant.h"
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

DSBlock::DSBlock(DSObject *father,
                 DSString *n) :
  DSNamedObject(DS_BLOCK, n, father)
/*  DSSortComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSSignalRouteComponent(this),
  DSProcessComponent(this),
  DSProcedureComponent(this),
  DSMachineComponent(this),
  DSMachineServiceComponent(this),
  DSLinkComponent(this),
  DSChannel2RouteConnectionComponent(this),
  DSPipe2LinkBindingComponent(this),
  DSSensorComponent(this) */
{
  block_substructure = NULL;
  
  DSSortComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSSignalRouteComponent::SetComponentParent(this);
  DSProcessComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSMachineComponent::SetComponentParent(this);
  DSMachineServiceComponent::SetComponentParent(this);
  DSLinkComponent::SetComponentParent(this);
  DSChannel2RouteConnectionComponent::SetComponentParent(this);
  DSPipe2LinkBindingComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    if (!GetName())
    {
      std::cerr << "Block has a parent but no name!\n";
      return;
    }
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertBlock(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertBlock(this);
        break;
      default:
        std::cerr << "Illegal parent for block.\n";
        exit(DS_FATAL_ERROR);
        break;
    }
  }
}

DSBlock::DSBlock(DSObject *father,
                 DSString& n) :
  DSNamedObject(DS_BLOCK, n, father)
/*  DSSortComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSSignalRouteComponent(this),
  DSProcessComponent(this),
  DSProcedureComponent(this),
  DSMachineComponent(this),
  DSMachineServiceComponent(this),
  DSLinkComponent(this),
  DSChannel2RouteConnectionComponent(this),
  DSPipe2LinkBindingComponent(this),
  DSSensorComponent(this) */
{
  block_substructure = NULL;
  
  DSSortComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSSignalRouteComponent::SetComponentParent(this);
  DSProcessComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSMachineComponent::SetComponentParent(this);
  DSMachineServiceComponent::SetComponentParent(this);
  DSLinkComponent::SetComponentParent(this);
  DSChannel2RouteConnectionComponent::SetComponentParent(this);
  DSPipe2LinkBindingComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    if (!GetName())
    {
      return;
    }
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertBlock(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertBlock(this);
        break;
      default:
        std::cerr << "Illegal parent for block.\n";
        exit(DS_FATAL_ERROR);
        break;
    }
  }
}

DSBlock::DSBlock(DSObject *father,
                 const char *n) :
  DSNamedObject(DS_BLOCK, n, father)
/*  DSSortComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSSignalRouteComponent(this),
  DSProcessComponent(this),
  DSProcedureComponent(this),
  DSMachineComponent(this),
  DSMachineServiceComponent(this),
  DSLinkComponent(this),
  DSChannel2RouteConnectionComponent(this),
  DSPipe2LinkBindingComponent(this),
  DSSensorComponent(this) */
{
  block_substructure = NULL;
  
  DSSortComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSSignalRouteComponent::SetComponentParent(this);
  DSProcessComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSMachineComponent::SetComponentParent(this);
  DSMachineServiceComponent::SetComponentParent(this);
  DSLinkComponent::SetComponentParent(this);
  DSChannel2RouteConnectionComponent::SetComponentParent(this);
  DSPipe2LinkBindingComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    if (!GetName())
    {
      return;
    }
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertBlock(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertBlock(this);
        break;
      default:
        std::cerr << "Illegal parent for block.\n";
        exit(DS_FATAL_ERROR);
        break;
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSBlock::~DSBlock(void)
{
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSBlock::New(DSObject *father) const
{
  return new DSBlock(father);
}

DSBoolean DSBlock::HasAction(DSActionTag action_type,
                             DSBoolean recursive) const
{
  DSProcess   *process;
  DSProcedure *procedure;

  if (recursive && block_substructure)
  {
    if (block_substructure->HasAction(action_type, recursive))
      return DS_TRUE;
  }
  
  if (recursive && GetProcessList())
  {
    GetProcessList()->StorePosition();
  
    for (process = GetFirstProcess();
         process;
         process = GetNextProcess())
    {
      if (process->HasAction(action_type, recursive))
      {
        GetProcessList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetProcessList()->RestorePosition();
  }

  if (recursive && GetProcedureList())
  {
    GetProcedureList()->StorePosition();
  
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->HasAction(action_type, recursive))
      {
        GetProcedureList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSBlock::HasDelayedOutputs(DSBoolean recursive) const
{
  DSProcess   *process;
  DSProcedure *procedure;

  if (recursive && block_substructure)
  {
    if (block_substructure->HasDelayedOutputs(recursive))
      return DS_TRUE;
  }
  
  if (recursive && GetProcessList())
  {
    GetProcessList()->StorePosition();
  
    for (process = GetFirstProcess();
         process;
         process = GetNextProcess())
    {
      if (process->HasDelayedOutputs(recursive))
      {
        GetProcessList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetProcessList()->RestorePosition();
  }

  if (recursive && GetProcedureList())
  {
    GetProcedureList()->StorePosition();
  
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->HasDelayedOutputs(recursive))
      {
        GetProcedureList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSBlock::HasAsteriskStates(DSBoolean recursive) const
{
  DSProcess   *process;
  DSProcedure *procedure;

  if (recursive && block_substructure)
  {
    if (block_substructure->HasAsteriskStates(recursive))
      return DS_TRUE;
  }
  
  if (recursive && GetProcessList())
  {
    GetProcessList()->StorePosition();
  
    for (process = GetFirstProcess();
         process;
         process = GetNextProcess())
    {
      if (process->HasAsteriskStates(recursive))
      {
        GetProcessList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetProcessList()->RestorePosition();
  }

  if (recursive && GetProcedureList())
  {
    GetProcedureList()->StorePosition();
  
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->HasAsteriskStates(recursive))
      {
        GetProcedureList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSBlock::HasComplexProcedures(DSBoolean recursive) const
{
  DSProcess   *process;
  DSProcedure *procedure;

  if (recursive && block_substructure)
  {
    if (block_substructure->HasComplexProcedures(recursive))
      return DS_TRUE;
  }
  
  if (recursive && GetProcessList())
  {
    GetProcessList()->StorePosition();
  
    for (process = GetFirstProcess();
         process;
         process = GetNextProcess())
    {
      if (process->HasComplexProcedures(recursive))
      {
        GetProcessList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetProcessList()->RestorePosition();
  }

  if (GetProcedureList())
  {
    GetProcedureList()->StorePosition();
  
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      if (procedure->GetIsComplex())
      {
        GetProcedureList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetProcedureList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSBlock::HasSensors(DSBoolean recursive) const
{
  DSProcess *process;

  if (GetSensorList())
  {
    return DS_TRUE;
  }
  
  if (recursive && block_substructure)
  {
    if (block_substructure->HasSensors(recursive))
      return DS_TRUE;
  }
  
  if (recursive && GetProcessList())
  {
    GetProcessList()->StorePosition();
  
    for (process = GetFirstProcess();
         process;
         process = GetNextProcess())
    {
      if (process->HasSensors(recursive))
      {
        GetProcessList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetProcessList()->RestorePosition();
  }
  return DS_FALSE;
}


DSBoolean DSBlock::HasExternalSynonyms(DSBoolean recursive) const
{
  DSSort *sort;
  DSSynonym *synonym;
  DSProcess *process;
  DSExpression *expression;
  DSOperandConstant *operand;
  
  if (GetSortList())
  {
    GetSortList()->StorePosition();
    
    for (sort = GetFirstSort();
         sort;
         sort = GetNextSort())
    {
      if (sort->GetTag() == DS_SORT_SYNONYM)
      {
        synonym = (DSSynonym *)sort;
        
        expression = synonym->GetValue();
        assert(expression);
        
        if (expression->IsConstant())
        {
          operand = (DSOperandConstant *)expression->GetOperand1();
          assert(operand->GetConstant());
          
          if (*operand->GetConstant() == DS_NAME_EXTERNAL)
          {
            GetSortList()->RestorePosition();
            return DS_TRUE;
          }
        }
      }
    }

    GetSortList()->RestorePosition();
  }

  if (recursive && block_substructure)
  {
    if (block_substructure->HasExternalSynonyms(recursive))
      return DS_TRUE;
  }
  
  if (recursive && GetProcessList())
  {
    GetProcessList()->StorePosition();
    
    for (process = GetFirstProcess();
         process;
         process = GetNextProcess())
    {
      if (process->HasExternalSynonyms(recursive))
      {
        GetProcessList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetProcessList()->RestorePosition();    
  }
  
  return DS_FALSE;
}

DSBlockSubstructure * DSBlock::GetBlockSubstructure(void) const
{
  return block_substructure;
}

DSResult DSBlock::SetBlockSubstructure(DSBlockSubstructure *new_sub)
{
  if (new_sub == block_substructure)
    return DS_OK;
    
  if (block_substructure)
    delete block_substructure;
    
  block_substructure = new_sub;
  
  if (block_substructure)
    block_substructure->SetParent(this);

  return DS_OK;
}

DSCardinal DSBlock::GetNumOfProcesses(void) const
{
  if (!GetProcessList())
    return 0;

  return GetProcessList()->NumberOfElements();
}

void DSBlock::CheckForComplexProcedures(DSBoolean recursive)
{
  DSProcess   *process;
  DSProcedure *procedure;

  if (recursive && block_substructure)
  {
    block_substructure->CheckForComplexProcedures(recursive);
  }
  
  if (recursive && GetProcessList())
  {
    GetProcessList()->StorePosition();
    
    for (process = GetFirstProcess();
         process;
         process = GetNextProcess())
    {
      process->CheckForComplexProcedures(recursive);
    }
    
    GetProcessList()->RestorePosition();
  }

  if (GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      procedure->CheckForComplexProcedures(recursive);
    }
    
    GetProcedureList()->RestorePosition();
  }
}

DSResult DSBlock::DissolveAsteriskStates(void)
{
  DSProcess *process;
  DSResult result;

  if (block_substructure)
  {
    result = block_substructure->DissolveAsteriskStates();
    if (result != DS_OK) return result;
  }
  
  for (process = GetFirstProcess();
       process;
       process = GetNextProcess())
  {
    result = process->DissolveAsteriskStates();
    if (result != DS_OK) return result;
  }
  return DS_OK;
}

DSResult DSBlock::DissolveNextStateDash(void)
{
  DSProcess *process;
  DSResult result;

  if (block_substructure)
  {
    result = block_substructure->DissolveNextStateDash();
    if (result != DS_OK) return result;
  }
  
  for (process = GetFirstProcess();
       process;
       process = GetNextProcess())
  {
    result = process->DissolveNextStateDash();
    if (result != DS_OK) return result;
  }
  return DS_OK;
}

DSResult DSBlock::DissolveDecisions(DSBoolean all)
{
  DSProcess *process;
  DSResult result;

  if (block_substructure)
  {
    result = block_substructure->DissolveDecisions(all);
    if (result != DS_OK) return result;
  }
  
  for (process = GetFirstProcess();
       process;
       process = GetNextProcess())
  {
    result = process->DissolveDecisions(all);
    if (result != DS_OK) return result;
  }
  return DS_OK;
}

DSObject *DSBlock::Clone(DSObject *father, DSObject *fill_this) const
{
  DSBlock *new_block;

  if (fill_this == NULL)
  {
    new_block = (DSBlock *)New(father);
    assert(new_block);
  }
  else
  {
    assert(fill_this->GetType() == DS_BLOCK);
    new_block = (DSBlock *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_block);

  if (block_substructure)
  {
    new_block->SetBlockSubstructure((DSBlockSubstructure *)GetBlockSubstructure()->Clone((DSObject *)new_block));
  }

  if (GetSortList())
  {
    new_block->SetSortList((DSSortKeyList *)GetSortList()->Clone((DSObject *)new_block));
  }

  if (DSSignalComponent::GetSignalList())
  {
    new_block->SetSignalList((DSSignalKeyList *)DSSignalComponent::GetSignalList()->Clone((DSObject *)new_block));
  }

  if (GetSignallistList())
  {
    new_block->SetSignallistList((DSSignalslistKeyList *)GetSignallistList()->Clone((DSObject *)new_block));
  }

  if (GetSignalRouteList())
  {
    new_block->SetSignalRouteList((DSSignalRouteKeyList *)GetSignalRouteList()->Clone((DSObject *)new_block));
  }

  if (GetProcessList())
  {
    new_block->SetProcessList((DSProcessKeyList *)GetProcessList()->Clone((DSObject *)new_block));
  }

  if (GetProcedureList())
  {
    new_block->SetProcedureList((DSProcedureKeyList *)GetProcedureList()->Clone((DSObject *)new_block));
  }

  if (GetMachineList())
  {
    new_block->SetMachineList((DSMachineKeyList *)GetMachineList()->Clone((DSObject *)new_block));
  }

  if (GetMachineServiceList())
  {
    new_block->SetMachineServiceList((DSMachineServiceKeyList *)GetMachineServiceList()->Clone((DSObject *)new_block));
  }

  if (GetLinkList())
  {
    new_block->SetLinkList((DSLinkKeyList *)GetLinkList()->Clone((DSObject *)new_block));
  }

  return new_block;
}


DSResult DSBlock::GetExternalSynonyms(DSSynonymRefList *result_list) const
{
  DSSort *sort;
  DSSynonym *synonym;
  DSProcess *process;
  DSResult result;
  DSExpression *expression;
  DSOperandConstant *operand;
  
  assert(result_list);
      
  if (block_substructure)
  {
    result = block_substructure->GetExternalSynonyms(result_list);
    if (result != DS_OK) return result;
  }
  
  if (GetSortList())
  {
    GetSortList()->StorePosition();
    
    for (sort = GetFirstSort();
         sort;
         sort = GetNextSort())
    {
      if (sort->GetTag() == DS_SORT_SYNONYM)
      {
        synonym = (DSSynonym *)sort;
        
        expression = synonym->GetValue();
        assert(expression);
        
        if (expression->IsConstant())
        {
          operand = (DSOperandConstant *)expression->GetOperand1();
          assert(operand->GetConstant());
          
          if (*operand->GetConstant() == DS_NAME_EXTERNAL)
          {
            result_list->Append(synonym);
          }
        }
      }
    }

    GetSortList()->RestorePosition();
  }

  if (GetProcessList())
  {
    GetProcessList()->StorePosition();
    
    for (process = GetFirstProcess();
         process;
         process = GetNextProcess())
    {
      result = process->GetExternalSynonyms(result_list);
      if (result != DS_OK)
      {
        GetProcessList()->RestorePosition();
        return result;
      }
    }

    GetProcessList()->RestorePosition();    
  }
  
  return DS_OK;
}


DSResult DSBlock::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (GetName()) GetName()->Write(writer, what);
  Run(writer, DS_CHANNEL2ROUTECONNECTION, what);
  Run(writer, DS_PIPE2LINKBINDING, what);
  Run(writer, DS_SORT, what);
  Run(writer, DS_PROCESS, what);
  Run(writer, DS_PROCEDURE, what);
  Run(writer, DS_MACHINE, what);
  Run(writer, DS_SIGNAL, what);
  Run(writer, DS_SIGNALLIST, what);
  Run(writer, DS_MACHINESERVICE, what);
  Run(writer, DS_SIGNALROUTE, what);
  Run(writer, DS_LINK, what);

  return DS_OK;
}

DSResult DSBlock::Run(DSWriter *writer,
                      DSType object_type,
                      DSCardinal what) const
{
  DSResult                     result;
  DSChannel2RouteConnectionRef channel_to_route_connection;
  DSPipe2LinkBindingRef pipe_to_link_binding;
  DSProcessRef                 process;
  DSProcedureRef               procedure;
  DSMachineRef                 machine;
  DSSortRef                    sort;
  DSSignalRef                  signal;
  DSSignalslistRef              signallist;
  DSSignalRouteRef             signalroute;
  DSLinkRef                    link;
  DSMachineServiceRef          machineservice;
  DSSensorRef                  sensor;

  assert(writer);

  switch(object_type)
  {
    case DS_CHANNEL2ROUTECONNECTION:
      for (channel_to_route_connection = GetFirstChannel2RouteConnection();
           channel_to_route_connection;
           channel_to_route_connection = GetNextChannel2RouteConnection())
      {
        result = channel_to_route_connection->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_PIPE2LINKBINDING:
      for (pipe_to_link_binding = GetFirstPipe2LinkBinding();
           pipe_to_link_binding;
           pipe_to_link_binding = GetNextPipe2LinkBinding())
      {
        result = pipe_to_link_binding->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_PROCESS:
      for (process = GetFirstProcess();
           process;
           process = GetNextProcess())
      {
        result = process->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_PROCEDURE:
      for (procedure = GetFirstProcedure();
           procedure;
           procedure = GetNextProcedure())
      {
        result = procedure->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_MACHINE:
      for (machine = GetFirstMachine();
           machine;
           machine = GetNextMachine())
      {
        result = machine->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_SORT:
      for (sort = GetFirstSort();
           sort;
           sort = GetNextSort())
      {
        result = sort->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_SIGNAL:
      for (signal = GetFirstSignal();
           signal;
           signal = GetNextSignal())
      {
        result = signal->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_SIGNALLIST:
      for (signallist = GetFirstSignallist();
           signallist;
           signallist = GetNextSignallist())
      {
        result = signallist->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_MACHINESERVICE:
      for (machineservice = GetFirstMachineService();
           machineservice;
           machineservice = GetNextMachineService())
      {
        result = machineservice->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_SIGNALROUTE:
      for (signalroute = GetFirstSignalRoute();
           signalroute;
           signalroute = GetNextSignalRoute())
      {
        result = signalroute->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_LINK:
      for (link = GetFirstLink();
           link;
           link = GetNextLink())
      {
        result = link->Write(writer, what);
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
