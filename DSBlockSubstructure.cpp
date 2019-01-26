/****************************************************************************
 *                 Modul: $RCSfile: DSBlockSubstructure.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/27 16:31:48 $
 * $Revision: 1.4 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer ein SDL-BlockSubstructure bereit.
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

#include "DSBlockSubstructure.h"
#include "DSBlock.h"
#include "DSProcedure.h"
#include "DSSort.h"
#include "DSOperandConstant.h"
#include "DSSynonym.h"
#include "DSExpression.h"
#include "DSString.h"
#include "DSChannel.h"
#include "DSPipe.h"
#include "DSSignal.h"
#include "DSSignalslist.h"
#include "DSMachineService.h"
#include "DSSensor.h"
#include "DSChannel2ChannelConnection.h" // for CC
#include "DSPipe2PipeBinding.h" // for CC

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

DSBlockSubstructure::DSBlockSubstructure(DSObject *father,
                                         DSString *n) :
  DSNamedObject(DS_BLOCKSUBSTRUCTURE, n, father)
/*  DSBlockComponent(this),
  DSChannelComponent(this),
  DSChannel2ChannelConnectionComponent(this),
  DSSortComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSProcedureComponent(this),
  DSMachineServiceComponent(this),
  DSPipeComponent(this),
  DSPipe2PipeBindingComponent(this),
  DSSensorComponent(this) */
{
  DSBlock *block;
  
  DSBlockComponent::SetComponentParent(this);
  DSChannelComponent::SetComponentParent(this);
  DSChannel2ChannelConnectionComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSMachineServiceComponent::SetComponentParent(this);
  DSPipeComponent::SetComponentParent(this);
  DSPipe2PipeBindingComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    assert(father->GetType() == DS_BLOCK);
    
    block = (DSBlock *)father;
    
    block->SetBlockSubstructure(this);
  }
}

DSBlockSubstructure::DSBlockSubstructure(DSObject *father,
                                         DSString& n) :
  DSNamedObject(DS_BLOCKSUBSTRUCTURE, n, father)
/*  DSBlockComponent(this),
  DSChannelComponent(this),
  DSChannel2ChannelConnectionComponent(this),
  DSSortComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSProcedureComponent(this),
  DSMachineServiceComponent(this),
  DSPipeComponent(this),
  DSPipe2PipeBindingComponent(this),
  DSSensorComponent(this) */
{
  DSBlock *block;
  
  DSBlockComponent::SetComponentParent(this);
  DSChannelComponent::SetComponentParent(this);
  DSChannel2ChannelConnectionComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSMachineServiceComponent::SetComponentParent(this);
  DSPipeComponent::SetComponentParent(this);
  DSPipe2PipeBindingComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    assert(father->GetType() == DS_BLOCK);
    
    block = (DSBlock *)father;
    
    block->SetBlockSubstructure(this);
  }
}

DSBlockSubstructure::DSBlockSubstructure(DSObject *father,
                                         const char *n) :
  DSNamedObject(DS_BLOCKSUBSTRUCTURE, n, father)
/*  DSBlockComponent(this),
  DSChannelComponent(this),
  DSChannel2ChannelConnectionComponent(this),
  DSSortComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSProcedureComponent(this),
  DSMachineServiceComponent(this),
  DSPipeComponent(this),
  DSPipe2PipeBindingComponent(this),
  DSSensorComponent(this) */
{
  DSBlock *block;
  
  DSBlockComponent::SetComponentParent(this);
  DSChannelComponent::SetComponentParent(this);
  DSChannel2ChannelConnectionComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSMachineServiceComponent::SetComponentParent(this);
  DSPipeComponent::SetComponentParent(this);
  DSPipe2PipeBindingComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);

  if (father)
  {
    assert(father->GetType() == DS_BLOCK);
    
    block = (DSBlock *)father;
    
    block->SetBlockSubstructure(this);
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSBlockSubstructure::~DSBlockSubstructure(void)
{
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSBlockSubstructure::New(DSObject *father) const
{
  (void)father;

  return new DSBlockSubstructure;
}


DSBoolean DSBlockSubstructure::HasAction(DSActionTag action_type,
                                         DSBoolean recursive) const
{
  DSBlock *block;

  if (recursive && GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      if (block->HasAction(action_type, recursive))
      {
        GetBlockList()->RestorePosition();
    
        return DS_TRUE;
      }
    }
    GetBlockList()->RestorePosition();
  }
  
  return DS_FALSE;
}


DSBoolean DSBlockSubstructure::HasDelayedOutputs(DSBoolean recursive) const
{
  DSBlock *block;

  if (recursive && GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      if (block->HasDelayedOutputs(recursive))
      {
        GetBlockList()->RestorePosition();
    
        return DS_TRUE;
      }
    }

    GetBlockList()->RestorePosition();
  }
  
  return DS_FALSE;
}


DSBoolean DSBlockSubstructure::HasAsteriskStates(DSBoolean recursive) const
{
  DSBlock *block;

  if (recursive && GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      if (block->HasAsteriskStates(recursive))
      {
        GetBlockList()->RestorePosition();
    
        return DS_TRUE;
      }
    }
    GetBlockList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSBlockSubstructure::HasTimer(DSBoolean recursive) const
{
  DSBlock *block;

  if (recursive && GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      if (block->HasTimer(recursive))
      {
        GetBlockList()->RestorePosition();
    
        return DS_TRUE;
      }
    }
    GetBlockList()->RestorePosition();
  }

  return DS_FALSE;
}

DSBoolean DSBlockSubstructure::HasSensors(DSBoolean recursive) const
{
  DSBlock *block;

  if (GetSensorList())
  {
    return DS_TRUE;
  }
  
  if (recursive && GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      if (block->HasSensors(recursive))
      {
        GetBlockList()->RestorePosition();
    
        return DS_TRUE;
      }
    }
    GetBlockList()->RestorePosition();
  }

  return DS_FALSE;
}


DSBoolean DSBlockSubstructure::HasComplexProcedures(DSBoolean recursive) const
{
  DSProcedure *procedure;
  DSBlock *block;

  if (recursive && GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      if (block->HasComplexProcedures(recursive))
      {
        GetBlockList()->RestorePosition();
    
        return DS_TRUE;
      }
    }
    GetBlockList()->RestorePosition();
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


DSBoolean DSBlockSubstructure::HasExternalSynonyms(DSBoolean recursive) const
{
  DSSort *sort;
  DSSynonym *synonym;
  DSBlock *block;
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

  if (recursive && GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      if (block->HasExternalSynonyms(recursive))
      {
        GetBlockList()->RestorePosition();
        return DS_TRUE;
      }
    }

    GetBlockList()->RestorePosition();    
  }
  
  return DS_FALSE;
}


DSCardinal DSBlockSubstructure::GetNumOfProcesses(void) const
{
  DSBlock *block;
  DSCardinal result = 0;

  if (GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      result += block->GetNumOfProcesses();
    }
    GetBlockList()->RestorePosition();
  }

  return result;
}

DSResult DSBlockSubstructure::DissolveAsteriskStates(void)
{
  DSBlock     *block;
  DSProcedure *procedure;
  DSResult     result;

  if (GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      result = block->DissolveAsteriskStates();
      if (result != DS_OK)
      {
        GetBlockList()->RestorePosition();

        return result;
      }
    }

    GetBlockList()->RestorePosition();
  }

  if (GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      result = procedure->DissolveAsteriskStates();
      if (result != DS_OK)
      {
        GetProcedureList()->RestorePosition();

        return result;
      }
    }
    
    GetProcedureList()->RestorePosition();
  }

  return DS_OK;
}

void DSBlockSubstructure::CheckForComplexProcedures(DSBoolean recursive)
{
  DSBlock     *block;
  DSProcedure *procedure;

  if (GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      block->CheckForComplexProcedures(recursive);
    }
    
    GetBlockList()->RestorePosition();
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

DSResult DSBlockSubstructure::DissolveNextStateDash(void)
{
  DSBlock     *block;
  DSProcedure *procedure;
  DSResult     result;

  if (GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      result = block->DissolveNextStateDash();
      if (result != DS_OK)
      {
        GetBlockList()->RestorePosition();
        return result;
      }
    }

    GetBlockList()->RestorePosition();    
  }

  if (GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      result = procedure->DissolveNextStateDash();
      if (result != DS_OK)
      {
        GetProcedureList()->RestorePosition();
        return result;
      }
    }
    
    GetProcedureList()->RestorePosition();
  }

  return DS_OK;
}

DSResult DSBlockSubstructure::DissolveDecisions(DSBoolean all)
{
  DSBlock *block;
  DSProcedure *procedure;
  DSResult result;

  if (GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      result = block->DissolveDecisions(all);
      if (result != DS_OK)
      {
        GetBlockList()->RestorePosition();
        return result;
      }
    }

    GetBlockList()->RestorePosition();    
  }

  if (GetProcedureList())
  {
    GetProcedureList()->StorePosition();
    
    for (procedure = GetFirstProcedure();
         procedure;
         procedure = GetNextProcedure())
    {
      result = procedure->DissolveDecisions(all);
      if (result != DS_OK)
      {
        GetProcedureList()->RestorePosition();
        return result;
      }
    }
    
    GetProcedureList()->RestorePosition();
  }

  return DS_OK;
}


DSResult DSBlockSubstructure::GetExternalSynonyms(DSSynonymRefList *result_list) const
{
  DSSort *sort;
  DSSynonym *synonym;
  DSBlock *block;
  DSResult result;
  DSExpression *expression;
  DSOperandConstant *operand;
  
  assert(result_list);
      
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

  if (GetBlockList())
  {
    GetBlockList()->StorePosition();
    
    for (block = GetFirstBlock();
         block;
         block = GetNextBlock())
    {
      result = block->GetExternalSynonyms(result_list);
      if (result != DS_OK)
      {
        GetBlockList()->RestorePosition();
        return result;
      }
    }

    GetBlockList()->RestorePosition();    
  }
  
  return DS_OK;
}


DSObject *DSBlockSubstructure::Clone(DSObject *father, DSObject *fill_this) const
{
  DSBlockSubstructure *new_block_substructure;

  if (fill_this == NULL)
  {
    new_block_substructure = (DSBlockSubstructure *)New(father);
    assert(new_block_substructure);
  }
  else
  {
    assert(fill_this->GetType() == DS_SYSTEM);
    new_block_substructure = (DSBlockSubstructure *)fill_this;
  }

  // Basisklasse clonen:
  DSNamedObject::Clone(father, new_block_substructure);

  if (GetBlockList())
  {
    new_block_substructure->SetBlockList((DSBlockKeyList *)GetBlockList()->Clone((DSObject *)new_block_substructure));
  }

  if (GetChannelList())
  {
    new_block_substructure->SetChannelList((DSChannelKeyList *)GetChannelList()->Clone((DSObject *)new_block_substructure));
  }

  if (GetChannel2ChannelConnectionList())
  {
    new_block_substructure->SetChannel2ChannelConnectionList((DSChannel2ChannelConnectionList *)GetChannel2ChannelConnectionList()->Clone((DSObject *)new_block_substructure));
  }

  if (GetSortList())
  {
    new_block_substructure->SetSortList((DSSortKeyList *)GetSortList()->Clone((DSObject *)new_block_substructure));
  }

  if (DSSignalComponent::GetSignalList())
  {
    new_block_substructure->SetSignalList((DSSignalKeyList *)DSSignalComponent::GetSignalList()->Clone((DSObject *)new_block_substructure));
  }

  if (GetSignallistList())
  {
    new_block_substructure->SetSignallistList((DSSignalslistKeyList *)GetSignallistList()->Clone((DSObject *)new_block_substructure));
  }

  if (GetProcedureList())
  {
    new_block_substructure->SetProcedureList((DSProcedureKeyList *)GetProcedureList()->Clone((DSObject *)new_block_substructure));
  }

  if (GetMachineServiceList())
  {
    new_block_substructure->SetMachineServiceList((DSMachineServiceKeyList *)GetMachineServiceList()->Clone((DSObject *)new_block_substructure));
  }

  if (GetPipeList())
  {
    new_block_substructure->SetPipeList((DSPipeKeyList *)GetPipeList()->Clone((DSObject *)new_block_substructure));
  }

  if (GetPipe2PipeBindingList())
  {
    new_block_substructure->SetPipe2PipeBindingList((DSPipe2PipeBindingList *)GetPipe2PipeBindingList()->Clone((DSObject *)new_block_substructure));
  }

  if (GetSensorList())
  {
    new_block_substructure->SetSensorList((DSSensorKeyList *)GetSensorList()->Clone((DSObject *)new_block_substructure));
  }

  return new_block_substructure;
}

DSResult DSBlockSubstructure::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (GetName()) GetName()->Write(writer, what);
  Run(writer, DS_BLOCK, what);
  Run(writer, DS_CHANNEL, what);
  Run(writer, DS_PIPE, what);
  Run(writer, DS_PROCEDURE, what);
  Run(writer, DS_SORT, what);
  Run(writer, DS_SIGNAL, what);
  Run(writer, DS_SIGNALLIST, what);
  Run(writer, DS_MACHINESERVICE, what);

  return DS_OK;
}

DSResult DSBlockSubstructure::Run(DSWriter *writer, DSType object_type,
                                  DSCardinal what) const
{
  DSResult        result;
  DSBlockRef      block;
  DSChannelRef    channel;
  DSPipeRef       pipe;
  DSProcedureRef  procedure;
  DSSortRef       sort;
  DSSignalRef     signal;
  DSSignalslistRef signallist;
  DSMachineServiceRef machineservice;
  DSSensorRef     sensor;

  switch(object_type)
  {
    case DS_BLOCK:
      for (block = GetFirstBlock();
           block;
           block = GetNextBlock())
      {
        result = block->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_CHANNEL:
      for (channel = GetFirstChannel();
           channel;
           channel = GetNextChannel())
      {
        result = channel->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_PIPE:
      for (pipe = GetFirstPipe();
           pipe;
           pipe = GetNextPipe())
      {
        result = pipe->Write(writer, what);
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
      std::cerr << "Illegal Run on block substructure '" << GetName() << "'!" << std::endl;
      assert(DS_FALSE);
      break;
  }

  return DS_OK;
}

