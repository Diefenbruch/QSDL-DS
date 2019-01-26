/****************************************************************************
 *                 Modul: $RCSfile: DSSystem.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/27 16:31:48 $
 * $Revision: 1.6 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer ein SDL-System bereit.
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

#include "DSRef.h"
#include "DSSystem.h"
#include "DSBlock.h"
#include "DSChannel.h"
#include "DSSortExtended.h"
#include "DSGenerator.h"
#include "DSSyntype.h"
#include "DSNextState.h"
#include "DSProcess.h"
#include "DSProcedure.h"
#include "DSState.h"
#include "DSInput.h"
#include "DSInputSignal.h"
#include "DSTransition.h"
#include "DSSignalRoute.h"
#include "DSChannel2RouteConnection.h"
#include "DSOperator.h"
#include "DSPipe.h"
#include "DSSignal.h"
#include "DSSignalslist.h"
#include "DSSensor.h"
#include "DSString.h"
#include "DSAtom.h"
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

DSSystem::DSSystem(DSString *n) :
  DSNamedObject(DS_SYSTEM, n)
/*  DSBlockComponent(this),
  DSChannelComponent(this),
  DSSortComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSProcedureComponent(this),
  DSMachineServiceComponent(this),
  DSPipeComponent(this),
  DSSensorComponent(this),
  DSAtomComponent(this) */
{
  env_block = NULL;

  DSBlockComponent::SetComponentParent(this);
  DSChannelComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSMachineServiceComponent::SetComponentParent(this);
  DSPipeComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);
  DSAtomComponent::SetComponentParent(this);
}

DSSystem::DSSystem(DSString& n) :
  DSNamedObject(DS_SYSTEM, n)
/*  DSBlockComponent(this),
  DSChannelComponent(this),
  DSSortComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSProcedureComponent(this),
  DSMachineServiceComponent(this),
  DSPipeComponent(this),
  DSSensorComponent(this),
  DSAtomComponent(this) */
{
  env_block = NULL;

  DSBlockComponent::SetComponentParent(this);
  DSChannelComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSMachineServiceComponent::SetComponentParent(this);
  DSPipeComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);
  DSAtomComponent::SetComponentParent(this);
}

DSSystem::DSSystem(const char *n) :
  DSNamedObject(DS_SYSTEM, n)
/*  DSBlockComponent(this),
  DSChannelComponent(this),
  DSSortComponent(this),
  DSSignalComponent(this),
  DSSignalslistComponent(this),
  DSProcedureComponent(this),
  DSMachineServiceComponent(this),
  DSPipeComponent(this),
  DSSensorComponent(this),
  DSAtomComponent(this) */
{
  env_block = NULL;

  DSBlockComponent::SetComponentParent(this);
  DSChannelComponent::SetComponentParent(this);
  DSSortComponent::SetComponentParent(this);
  DSSignalComponent::SetComponentParent(this);
  DSSignalslistComponent::SetComponentParent(this);
  DSProcedureComponent::SetComponentParent(this);
  DSMachineServiceComponent::SetComponentParent(this);
  DSPipeComponent::SetComponentParent(this);
  DSSensorComponent::SetComponentParent(this);
  DSAtomComponent::SetComponentParent(this);
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSystem::~DSSystem(void)
{
  if (env_block) delete env_block;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSSystem::New(DSObject *father) const
{
  (void)father;

  return new DSSystem;
}

DSBoolean DSSystem::IsOpen(void) const
{
  DSChannel *channel;

  for (channel = this->GetFirstChannel();
       channel;
       channel = this->GetNextChannel())
  {
    if (channel->GetBlock1Ref() == NULL ||
        channel->GetBlock2Ref() == NULL) // Kanal ans Environment?
    {
      return DS_TRUE;
    }
  }
  return DS_FALSE;
}

DSResult DSSystem::Close(DSStream &dsCout, DSBoolean verbose)
{
  DSChannel2RouteConnection *c2rc;
  DSSignalRoute    *env_signal_route;
  DSChannel        *channel;
  DSSignalItemList *signal_item_list_from_env, *signal_item_list_to_env;
  DSProcess        *env_process;
  DSState          *state = NULL;
  DSInput          *input;
  DSTransition     *start_transition, *passive_transition, *active_transition;
  DSNextState      *nextstate;
  DSString         *process_name;
  DSString         *signalroute_name;
  DSSignalRefList  *signal_ref_list;
  DSSignalRef       signal_ref;
  DSInputSignal    *input_signal;
  DSResult          status;

  for (channel = this->GetFirstChannel();
       channel;
       channel = this->GetNextChannel())
  {
    if (channel->GetBlock1Ref() == NULL) // Kanal vom Environment?
    {
      assert(channel->GetBlock2Ref() != NULL);

      // Env-Block anlegen falls dies noch nicht geschehen ist:
      if (env_block == NULL)
      {
        if (verbose)
        {
          dsCout << "  Creating Environment Block '" << DS_NAME_ENV_BLOCK <<
                  "'...\n";
        }

        env_block = new DSBlock(NULL, DS_NAME_ENV_BLOCK);
        assert(env_block);
        InsertBlock(env_block, DS_FALSE); // vorne anfuegen!
      }

      // Kanal umrouten:
      channel->SetBlock1Ref(env_block);

      // Signallisten merken:
      signal_item_list_from_env = channel->GetSignalList12();
      signal_item_list_to_env = channel->GetSignalList21();
    }
    else if (channel->GetBlock2Ref() == NULL)
    {
      assert(channel->GetBlock1Ref() != NULL);

      // Env-Block anlegen falls dies noch nicht geschehen ist:
      if (env_block == NULL)
      {
        if (verbose)
        {
          dsCout << "  Creating Environment Block '" << DS_NAME_ENV_BLOCK <<
                  "'...\n";
        }

        env_block = new DSBlock(NULL, DS_NAME_ENV_BLOCK);
        assert(env_block);
        InsertBlock(env_block, DS_FALSE); // vorne anfuegen!
      }

      // Kanal umrouten:
      channel->SetBlock2Ref(env_block);

      // Signallisten merken:
      signal_item_list_from_env = channel->GetSignalList21();
      signal_item_list_to_env = channel->GetSignalList12();
    }
    else
    {
      continue;
    }

    if (signal_item_list_from_env && signal_item_list_to_env)
    {
      if (verbose)
      {
        dsCout << "  Found bidirectional Channel from/to Environment: '"
             << channel->GetName()->GetString() << "'\n";
      }
    }
    else if (signal_item_list_from_env)
    {
      if (verbose)
      {
        dsCout << "  Found unidirectional Channel from Environment: '"
             << channel->GetName()->GetString() << "'\n";
      }
    }
    else if (signal_item_list_to_env)
    {
      if (verbose)
      {
        dsCout << "  Found unidirectional Channel to Environment: '"
             << channel->GetName()->GetString() << "'\n";
      }
    }
    else
    {
      continue;
    }

    // Environment Process anlegen:
    process_name = new DSString;
    process_name->Format("%s_%d",
                         DS_NAME_ENV_PROCESS,
                         env_block->GetProcessList() ?
                         env_block->GetProcessList()->NumberOfElements() + 1 :
                         1);
    if (verbose)
    {
      dsCout << "  Creating Environment Process '" << *process_name << "'...\n";
    }
    env_process = new DSProcess(env_block, *process_name);
    assert(env_process);

    // aktives + passives Environment  ?
    if (signal_item_list_to_env && signal_item_list_from_env)
    {
      state = new DSState(env_process, DS_NAME_ENV_STATE);
      assert(state);

      // Fuer alle Signale die der Prozess bekommen kann Inputs erzeugen:
      signal_ref_list = new DSSignalRefList;
      assert(signal_ref_list);
      signal_item_list_to_env->GetSignals(signal_ref_list);
      
      for (status = signal_ref_list->MoveFirst();
           status == DS_OK;
           status = signal_ref_list->MoveNext())
      {
        signal_ref = signal_ref_list->GetCurrentData();
        assert(signal_ref);

        input = new DSInput(state);
        assert(input);
      
        input_signal = new DSInputSignal(input, signal_ref);
        assert(input_signal);

        // Leere Transition erzeugen:
        passive_transition = new DSTransition(input);
        assert(passive_transition);
      }
      delete signal_ref_list;
      
      input = new DSInput(state, DS_FALSE, DS_FALSE, DS_TRUE);  // 'input none' erzeugen!
      active_transition = new DSTransition(input);
      assert(active_transition);
    }
    // rein passives Environment ?
    else if (signal_item_list_to_env)
    {
      state = new DSState(env_process, DS_NAME_ENV_STATE_PASSIVE);
      assert(state);

      // Fuer alle Signale die der Prozess bekommen kann Inputs erzeugen:
      signal_ref_list = new DSSignalRefList;
      assert(signal_ref_list);
      signal_item_list_to_env->GetSignals(signal_ref_list);
      
      for (status = signal_ref_list->MoveFirst();
           status == DS_OK;
           status = signal_ref_list->MoveNext())
      {
        signal_ref = signal_ref_list->GetCurrentData();
        assert(signal_ref);

        input = new DSInput(state);
        assert(input);
      
        input_signal = new DSInputSignal(input, signal_ref);
        assert(input_signal);

        // Leere Transition erzeugen:
        passive_transition = new DSTransition(input);
        assert(passive_transition);
      }
      delete signal_ref_list;
    }
    // rein aktives Environment (dann input none generieren!) ?
    else if (signal_item_list_from_env)
    {
      state = new DSState(env_process, DS_NAME_ENV_STATE_ACTIVE);
      assert(state);

      input = new DSInput(state, DS_FALSE, DS_FALSE, DS_TRUE);  // 'input none' erzeugen!
      active_transition = new DSTransition(input);
      assert(active_transition);
    }

    start_transition = new DSTransition(env_process);
    assert(start_transition);
    nextstate = new DSNextState(start_transition, (DSString*)NULL, state);
    assert(nextstate);

    if (verbose)
    {
      dsCout << "  Creating Signalroute to connect Environment Process '"
           << *process_name << "'...\n";
    }

    signalroute_name = new DSString;
    signalroute_name->Format("%s_%d",
                             DS_NAME_ENV_SIGNAL_ROUTE,
                             env_block->GetProcessList() ?
                             env_block->GetProcessList()->NumberOfElements() + 1 :
                             1);
    env_signal_route = new DSSignalRoute(env_block, *signalroute_name,
                                         NULL, env_process);
    assert(env_signal_route);
    assert(env_signal_route->SetSignalList12(signal_item_list_to_env));
    assert(env_signal_route->SetSignalList21(signal_item_list_from_env));
    c2rc = new DSChannel2RouteConnection(env_block);
    assert(c2rc);
    assert(c2rc->InsertChannelRef(channel) == DS_OK);
    assert(c2rc->InsertSignalRouteRef(env_signal_route) == DS_OK);
  }
  return DS_OK;
}

DSResult DSSystem::InitializeBasicSorts(void)
{
  DSSort         *sort;
  DSSortExtended *sort_extended;
  DSGenerator    *sort_generator;
  DSOperator     *op;
  DSSortRefList  *input_sort_ref_list;
  DSSortRef       input_sort;
  DSSortRef       output_sort_ref;

  ////////////////////////
  // Boolean:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_BOOLEAN);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->InsertLiteral(DS_SORT_LITERAL_NAME_FALSE);
  sort_extended->InsertLiteral(DS_SORT_LITERAL_NAME_TRUE);
  sort_extended->SetNeutralElement(DS_SORT_NEUTRAL_BOOLEAN);

  ////////////////////////
  // Real:
  ////////////////////////
  sort = new DSSort(this, DS_SORT_NAME_REAL);
  sort->SetIsPredefined(DS_TRUE);
  sort->SetNeutralElement(DS_SORT_NEUTRAL_REAL);

  ////////////////////////
  // Integer:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_INTEGER);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetNeutralElement(DS_SORT_NEUTRAL_INTEGER);

  // Float-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_FLOAT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Fix-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_FIX,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Natural:
  ////////////////////////

  sort_extended = new DSSortExtended(this, DS_SORT_NAME_NATURAL);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetNeutralElement(DS_SORT_NEUTRAL_NATURAL);

  // Float-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_NATURAL);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_FLOAT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Fix-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NATURAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_FIX,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Character:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_CHARACTER);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetNeutralElement(DS_SORT_NEUTRAL_CHAR);

  // Num-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARACTER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_NUM,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Chr-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_CHARACTER);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_CHR,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Charstring:
  ////////////////////////
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);
  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARACTER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);
  
  sort_generator = new DSGenerator(this, DS_SORT_NAME_CHARSTRING,
                                   DS_GENERATOR_NAME_STRING,
                                   input_sort_ref_list);
  sort_generator->SetIsPredefined(DS_TRUE);
  sort_generator->SetIsComplex(DS_TRUE);
  sort_generator->InsertLiteral(DS_SORT_LITERAL_NAME_EMPTYSTRING);
  sort_generator->InsertLiteral(DS_SORT_LITERAL_NAME_EMPTYSTRING2);
  sort_generator->SetNeutralElement(DS_SORT_NEUTRAL_CHARSTRING);

  // MkString-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARACTER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  op = new DSOperator(sort_generator,
                      DS_SORT_OPERATOR_NAME_MKSTRING,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Length-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  op = new DSOperator(sort_generator,
                      DS_SORT_OPERATOR_NAME_LENGTH,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // First-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_CHARACTER);
  op = new DSOperator(sort_generator,
                      DS_SORT_OPERATOR_NAME_FIRST,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Last-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_CHARACTER);
  op = new DSOperator(sort_generator,
                      DS_SORT_OPERATOR_NAME_LAST,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // "//"-Funktion: (Stringverkettung)
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  op = new DSOperator(sort_generator,
                      DS_SORT_OPERATOR_NAME_CONCAT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Extract!-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_CHARACTER);
  op = new DSOperator(sort_generator,
                      DS_SORT_OPERATOR_NAME_EXTRACT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Modify!-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARACTER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  op = new DSOperator(sort_generator,
                      DS_SORT_OPERATOR_NAME_MODIFY,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Substring-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  op = new DSOperator(sort_generator,
                      DS_SORT_OPERATOR_NAME_SUBSTRING,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Duration:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_DURATION);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetNeutralElement(DS_SORT_NEUTRAL_DURATION);

  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_DURATION);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_DURATION,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Time:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_TIME);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetNeutralElement(DS_SORT_NEUTRAL_TIME);

  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_DURATION);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_TIME);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_TIME,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // PID:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_PID);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->InsertLiteral(DS_SORT_LITERAL_NAME_NULL);
  sort_extended->SetNeutralElement(DS_SORT_NEUTRAL_PID);

  ////////////////////////
  // Byte:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_BYTE);
  sort_extended->SetIsPredefined(DS_TRUE);

  // BAND-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_BAND,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // BOR-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_BOR,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // BXOR-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_BXOR,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // BNOT-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_BNOT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // BSHL-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_BSHL,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // BSHR-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_BSHR,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // BPLUS-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_BPLUS,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // BSUB-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_BSUB,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // BMUL-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_BMUL,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // BDIV-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_BDIV,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // BMOD-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_BMOD,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // I2B-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_I2B,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // B2I-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_B2I,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // B2C-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_CHARACTER);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_B2C,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // C2B-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARACTER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BYTE);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_C2B,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  return DS_OK;
}

DSResult DSSystem::InitializeQSDLSorts(void)
{
  DSSortExtended *sort_extended;
  DSOperator     *op;
  DSSortRefList  *input_sort_ref_list;
  DSSortRef       input_sort;
  DSSortRef       output_sort_ref;

  sort_extended = new DSSortExtended(this, DS_SORT_NAME_DISCIPLINE);
  sort_extended->InsertLiteral(DS_SORT_LITERAL_NAME_PS);
  sort_extended->InsertLiteral(DS_SORT_LITERAL_NAME_IS);
  sort_extended->InsertLiteral(DS_SORT_LITERAL_NAME_FCFS);
  sort_extended->InsertLiteral(DS_SORT_LITERAL_NAME_FCFSPP);
  sort_extended->InsertLiteral(DS_SORT_LITERAL_NAME_FCFSPNP);
  sort_extended->InsertLiteral(DS_SORT_LITERAL_NAME_LCFSPP);
  sort_extended->InsertLiteral(DS_SORT_LITERAL_NAME_RANDOM);

  ////////////////////////
  // Deterministische Verteilung:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_DETERMINISTIC);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);
  // Init-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_DETERMINISTIC); // Vert.-Var.
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_DETERMINISTIC);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_INIT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Sample-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_DETERMINISTIC);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SAMPLE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Empirische-Verteilung:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_EMPIRICAL);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);
  // Init-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_EMPIRICAL); // Vert.-Var.
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_CHARSTRING);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_EMPIRICAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_INIT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Sample-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_EMPIRICAL);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SAMPLE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Erlang-Verteilung:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_ERLANG);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);
  // Init-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_ERLANG); // Vert.-Var.
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL);  // Mittelwert
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL);  // Standardabweichung
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_ERLANG);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_INIT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Sample-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_ERLANG);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SAMPLE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////////////////
  // Negativ-Exponentielle-Verteilung:
  ////////////////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_NEGEXP);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);
  // Init-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_NEGEXP); // Vert.-Var.
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL);    // Mittelwert
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NEGEXP);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_INIT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Sample-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_NEGEXP);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SAMPLE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Normal-Verteilung:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_NORMAL);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);
  // Init-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_NORMAL); // Vert.-Var.
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL);  // Mittelwert
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL);  // Standardabweichung
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NORMAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_INIT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Sample-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_NORMAL);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SAMPLE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Gleich-Verteilung:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_UNIFORM);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);
  // Init-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_UNIFORM); // Vert.-Var.
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL);  // untere Grenze
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL);  // obere Grenze
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_UNIFORM);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_INIT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Sample-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_UNIFORM);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SAMPLE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Bernoulli-Verteilung:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_BERNOULLI);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);
  // Init-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BERNOULLI); // Vert.-Var.
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_REAL); // Wahrscheinlichkeit f. TRUE
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BERNOULLI);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_INIT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Sample-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_BERNOULLI);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_BOOLEAN);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SAMPLE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Poisson-Verteilung:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_POISSON);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);
  // Init-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_POISSON); // Vert.-Var.
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);   // Mittelwert
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_POISSON);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_INIT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Sample-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_POISSON);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SAMPLE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  //////////////////////////////////
  // Gleich-Verteilung (ganzzahlig):
  //////////////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_RANDINT);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);
  // Init-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_RANDINT); // Vert.-Var.
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);  // untere Grenze
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_INTEGER);  // obere Grenze
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_RANDINT);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_INIT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Sample-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_RANDINT);
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_INTEGER);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SAMPLE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Counter-Sensor:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_COUNTER);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);

  // Sum-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_COUNTER); // Vert.-Var.
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NATURAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SUM,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // SumInt-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_COUNTER); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NATURAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SUMINT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // SumTime-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_COUNTER); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SUMTIME,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // SumTimeInt-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_COUNTER); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SUMTIMEINT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Frequency-Sensor:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_FREQUENCY);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);

  // Sum-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_FREQUENCY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NATURAL); // sum of samples
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SUM,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // AbsFreq-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_FREQUENCY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_NATURAL); // Value
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NATURAL); // absolute frequency
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_ABSFREQ,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // RelFreq-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_FREQUENCY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_NATURAL); // Value
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL); // relative frequency
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_RELFREQ,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // LastValue-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_FREQUENCY); // sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NATURAL); // last updated value
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_LASTVALUE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // LastSample-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_FREQUENCY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NATURAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_LASTSAMPLE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // CurrentValue-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_FREQUENCY); // sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NATURAL); // last updated value
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_CURRENTVALUE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  ////////////////////////
  // Tally-Sensor:
  ////////////////////////
  sort_extended = new DSSortExtended(this, DS_SORT_NAME_TALLY);
  sort_extended->SetIsPredefined(DS_TRUE);
  sort_extended->SetIsComplex(DS_TRUE);

  // Num-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NATURAL); // num of samples
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_NUM,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // NumInt-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_NATURAL); // num of samples
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_NUMINT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Minimum-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL); // minimum of samples
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_MINIMUM,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Maximum-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL); // maximum of samples
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_MAXIMUM,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Sum-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL); // sum of samples
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SUM,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // SumInt-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL); // sum of samples
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SUMINT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // SumSquare-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL); // sum of squares of samples
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_SUMSQUARE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Average-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL); // average of samples
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_AVERAGE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // AverageInt-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL); // average of samples
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_AVERAGEINT,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // Variance-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL); // variance of samples
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_VARIANCE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // StdDev-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL); // standard deviation
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_STDDEV,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // VarCoeff-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL); // standard deviation
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_VARCOEFF,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  // LastSample-Funktion:
  input_sort_ref_list = new DSSortRefList;
  assert(input_sort_ref_list);

  input_sort = this->GetSortRefByName(DS_SORT_NAME_TALLY); // Sensor
  assert(input_sort);
  input_sort_ref_list->Append(input_sort);

  output_sort_ref = this->GetSortRefByName(DS_SORT_NAME_REAL);
  op = new DSOperator(sort_extended,
                      DS_SORT_OPERATOR_NAME_LASTSAMPLE,
                      input_sort_ref_list,
                      output_sort_ref);
  assert(op);

  return DS_OK;
}


DSBoolean DSSystem::HasAction(DSActionTag action_type,
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


DSBoolean DSSystem::HasDelayedOutputs(DSBoolean recursive) const
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


DSBoolean DSSystem::HasAsteriskStates(DSBoolean recursive) const
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

DSBoolean DSSystem::HasTimer(DSBoolean recursive) const
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

DSBoolean DSSystem::HasSensors(DSBoolean recursive) const
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

DSBoolean DSSystem::HasComplexProcedures(DSBoolean recursive) const
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


DSBoolean DSSystem::HasExternalSynonyms(DSBoolean recursive) const
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


DSCardinal DSSystem::GetNumOfProcesses(void) const
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

DSResult DSSystem::DissolveAsteriskStates(void)
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

void DSSystem::CheckForComplexProcedures(DSBoolean recursive)
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

DSResult DSSystem::DissolveNextStateDash(void)
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

DSResult DSSystem::DissolveDecisions(DSBoolean all)
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


DSResult DSSystem::GetExternalSynonyms(DSSynonymRefList *result_list) const
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


DSObject *DSSystem::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSystem *new_system;

  if (fill_this == NULL)
  {
    new_system = (DSSystem *)New(father);
    assert(new_system);
  }
  else
  {
    assert(fill_this->GetType() == DS_SYSTEM);
    new_system = (DSSystem *)fill_this;
  }

  // Basisklasse clonen:
  DSNamedObject::Clone(father, new_system);

  if (GetBlockList())
  {
    new_system->SetBlockList((DSBlockKeyList *)GetBlockList()->Clone((DSObject *)new_system));
  }

  if (GetChannelList())
  {
    new_system->SetChannelList((DSChannelKeyList *)GetChannelList()->Clone((DSObject *)new_system));
  }

  if (GetSortList())
  {
    new_system->SetSortList((DSSortKeyList *)GetSortList()->Clone((DSObject *)new_system));
  }

  if (DSSignalComponent::GetSignalList())
  {
    new_system->SetSignalList((DSSignalKeyList *)DSSignalComponent::GetSignalList()->Clone((DSObject *)new_system));
  }

  if (GetSignallistList())
  {
    new_system->SetSignallistList((DSSignalslistKeyList *)GetSignallistList()->Clone((DSObject *)new_system));
  }

  if (GetProcedureList())
  {
    new_system->SetProcedureList((DSProcedureKeyList *)GetProcedureList()->Clone((DSObject *)new_system));
  }

  if (GetMachineServiceList())
  {
    new_system->SetMachineServiceList((DSMachineServiceKeyList *)GetMachineServiceList()->Clone((DSObject *)new_system));
  }

  if (GetPipeList())
  {
    new_system->SetPipeList((DSPipeKeyList *)GetPipeList()->Clone((DSObject *)new_system));
  }

  if (GetSensorList())
  {
    new_system->SetSensorList((DSSensorKeyList *)GetSensorList()->Clone((DSObject *)new_system));
  }

  return new_system;
}

DSResult DSSystem::Write(DSWriter *writer, DSCardinal what) const
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

DSResult DSSystem::Run(DSWriter *writer, DSType object_type,
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
  DSAtomRef       atom;

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

    case DS_ATOM:
      for (atom = GetFirstAtom();
           atom;
           atom = GetNextAtom())
      {
        result = atom->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    default:
      std::cerr << "Illegal Run on system '" << GetName() << "'!" << std::endl;
      assert(DS_FALSE);
      break;
  }

  return DS_OK;
}

