/****************************************************************************
 *                 Modul: $RCSfile: DSObject.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/27 16:31:48 $
 * $Revision: 1.3 $
 *
 * Aufgabe: Dieser Modul implementiert die Basisklasse aller anderen
 *          Klassen der Datenstruktur
 *
 * Funktionen: GetType(): Liefert den Objecttypen
 *             GetParent(): Liefert Zeiger auf das Vaterobjekt
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

#include "DSObject.h"
#ifdef DEBUG
#include <dmalloc.h>
#endif

#include "DSSystem.h" // wegen scope-Fkt.
#include "DSBlock.h" // wegen scope-Fkt.
#include "DSBlockSubstructure.h" // wegen scope-Fkt.
#include "DSProcess.h" // wegen scope-Fkt.
#include "DSProcedure.h" // wegen scope-Fkt.
#include "DSMachine.h" // wegen scope-Fkt.
#include "DSSortExtended.h"
#include "DSSignalslistComponent.h"
#include "DSString.h"

/****************************************************************************
 * Externe Variablen
 ****************************************************************************/

/****************************************************************************
 * Globale Variablen
 ****************************************************************************/

/****************************************************************************
 * Initialisierung statischer Elemente
 ****************************************************************************/

DSCardinal DSObject::run_id = 0;

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSObject::DSObject(DSType object_type,
                   DSObject *father):
  type(object_type),
  parent(father)
{
  id = run_id;
  run_id++;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSObject::~DSObject(void)
{
}

/****************************************************************************
 * GetType(): Liefert den Objecttypen
 *            Ergebnis: Objecttype (DSType in DSBasicTypes.h)
 *            Seiteneffekte: keine
 ****************************************************************************/

DSType DSObject::GetType(void) const
{
  return type;
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSObject::GetParent(void) const
{
  return parent;
}

DSResult DSObject::SetParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}

DSSortRef DSObject::GetSortRefByName(DSString *name) const
{
  DSObjectRef object = this;
  DSSortRef sort_ref = NULL;

  assert(name);

  /*************************************************/
  /* Umgebung (Scope) suchen, in welcher die Sorte */
  /* definiert ist:                                */
  /*************************************************/
  while(object != NULL &&
        sort_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_PROCEDURE:
        sort_ref = ((DSProcedure*)object)->GetSort(name);
        break;
      case DS_PROCESS:
        sort_ref = ((DSProcess*)object)->GetSort(name);
        break;
      case DS_BLOCK:
        sort_ref = ((DSBlock*)object)->GetSort(name);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        sort_ref = ((DSBlockSubstructure*)object)->GetSort(name);
        break;
      case DS_SYSTEM:
        sort_ref = ((DSSystem*)object)->GetSort(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return sort_ref;
}

DSSortRef DSObject::GetSortRefByName(const char *name) const
{
  DSString *string;
  DSSortRef sort_ref;

  string = new DSString(name);
  assert(string);

  sort_ref = GetSortRefByName(string);

  delete string;

  return sort_ref;
}

DSSortRef DSObject::GetSortRefByLiteralName(DSString *name) const
{
  DSObjectRef object = this;
  DSSortRef sort_ref = NULL;

  assert(name);

  /***************************************************/
  /* Umgebung (Scope) suchen, in welcher das Literal */
  /* definiert ist:                                  */
  /***************************************************/
  while(object != NULL &&
        sort_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_PROCEDURE:
        sort_ref = ((DSProcedure*)object)->GetLiteralSort(name);
        break;
      case DS_PROCESS:
        sort_ref = ((DSProcess*)object)->GetLiteralSort(name);
        break;
      case DS_BLOCK:
        sort_ref = ((DSBlock*)object)->GetLiteralSort(name);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        sort_ref = ((DSBlockSubstructure*)object)->GetLiteralSort(name);
        break;
      case DS_SYSTEM:
        sort_ref = ((DSSystem*)object)->GetLiteralSort(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return sort_ref;
}

DSSortRef DSObject::GetSortRefByLiteralName(const char *name) const
{
  DSString *string;
  DSSortRef sort_ref;

  string = new DSString(name);
  assert(string);

  sort_ref = GetSortRefByLiteralName(string);

  delete string;

  return sort_ref;
}

// Annahme: Operatoren in unterschiedlichen Sorten koennen den
//          gleichen Namen haben, unterscheiden sich dann aber
//          in den Typen ihrer Parameter.
//          Operatoren einer Sorte haben alle unterschiedliche
//          Namen.
DSOperatorRef
DSObject::GetOperatorRefByNameAndParamSorts(DSString *name,
                                            DSSortRefList *param_sort_list) const
{
  DSObjectRef       object       = this;
  DSOperatorRef     operator_ref = NULL;
  DSSortExtendedRef sort_ref     = NULL;

  assert(name);

  /****************************************************/
  /* Umgebung (Scope) suchen, in welcher der Operator */
  /* definiert ist:                                   */
  /****************************************************/
  while(object != NULL &&
        operator_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_PROCEDURE:
        sort_ref = (DSSortExtended*)((DSProcedure*)object)->GetOperatorSort(name,
                                                                            param_sort_list);
        if (sort_ref) operator_ref = sort_ref->GetOperator(name);
        break;
      case DS_PROCESS:
        sort_ref = (DSSortExtended*)((DSProcess*)object)->GetOperatorSort(name,
                                                                          param_sort_list);
        if (sort_ref) operator_ref = sort_ref->GetOperator(name);
        break;
      case DS_BLOCK:
        sort_ref = (DSSortExtended*)((DSBlock*)object)->GetOperatorSort(name,
                                                                        param_sort_list);
        if (sort_ref) operator_ref = sort_ref->GetOperator(name);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        sort_ref = (DSSortExtended*)((DSBlockSubstructure*)object)->GetOperatorSort(name,
                                                                                    param_sort_list);
        if (sort_ref) operator_ref = sort_ref->GetOperator(name);
        break;
      case DS_SYSTEM:
        sort_ref = (DSSortExtended*)((DSSystem*)object)->GetOperatorSort(name,
                                                                         param_sort_list);
        if (sort_ref) operator_ref = sort_ref->GetOperator(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return operator_ref;
}

DSOperatorRef
DSObject::GetOperatorRefByNameAndParamSorts(const char *name,
                                            DSSortRefList *param_sort_list) const
{
  DSString *string;
  DSOperatorRef operator_ref;

  string = new DSString(name);
  assert(string);

  operator_ref = GetOperatorRefByNameAndParamSorts(string, param_sort_list);

  delete string;

  return operator_ref;
}

DSOperatorRef DSObject::GetOperatorRefByName(DSString *name) const
{
  return GetOperatorRefByNameAndParamSorts(name, NULL);
}

DSOperatorRef DSObject::GetOperatorRefByName(const char *name) const
{
  return GetOperatorRefByNameAndParamSorts(name, NULL);
}

DSVariableRef DSObject::GetVariableRefByName(DSString *name) const
{
  DSObjectRef   object       = this;
  DSVariableRef variable_ref = NULL;

  assert(name);

  /****************************************************/
  /* Umgebung (Scope) suchen, in welcher die Variable */
  /* definiert ist:                                   */
  /****************************************************/
  while(object != NULL &&
        variable_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_PROCEDURE:
        variable_ref = ((DSProcedure*)object)->GetVariable(name);
        if (variable_ref == NULL)
        {
          variable_ref = ((DSProcedure*)object)->GetFormalParam(name);
        }
        break;
      case DS_PROCESS:
        variable_ref = ((DSProcess*)object)->GetVariable(name);
        if (variable_ref == NULL)
        {
          variable_ref = ((DSProcess*)object)->GetFormalParam(name);
        }
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return variable_ref;
}

DSVariableRef DSObject::GetVariableRefByName(const char *name) const
{
  DSString     *string;
  DSVariableRef variable_ref;

  string = new DSString(name);
  assert(string);

  variable_ref = GetVariableRefByName(string);

  delete string;

  return variable_ref;
}

DSSignalRef DSObject::GetSignalRefByName(DSString *name) const
{
  DSObjectRef object     = this;
  DSSignalRef signal_ref = NULL;

  assert(name);

  /****************************************************/
  /* Umgebung (Scope) suchen, in welcher das Signal   */
  /* definiert ist:                                   */
  /****************************************************/
  while(object != NULL &&
        signal_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_PROCESS:
        signal_ref = ((DSProcess*)object)->GetSignal(name);
        break;
      case DS_BLOCK:
        signal_ref = ((DSBlock*)object)->GetSignal(name);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        signal_ref = ((DSBlockSubstructure*)object)->GetSignal(name);
        break;
      case DS_SYSTEM:
        signal_ref = ((DSSystem*)object)->GetSignal(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return signal_ref;
}

DSSignalRef DSObject::GetSignalRefByName(const char *name) const
{
  DSString   *string;
  DSSignalRef signal_ref;

  string = new DSString(name);
  assert(string);

  signal_ref = GetSignalRefByName(string);

  delete string;

  return signal_ref;
}

DSTimerRef DSObject::GetTimerRefByName(DSString *name) const
{
  DSObjectRef object     = this;
  DSTimerRef  signal_ref = NULL;

  assert(name);

  /**************************************************/
  /* Umgebung (Scope) suchen, in welcher der Timer  */
  /* definiert ist:                                 */
  /**************************************************/
  while(object != NULL &&
        signal_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_PROCESS:
        signal_ref = ((DSProcess*)object)->GetTimer(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return signal_ref;
}

DSTimerRef DSObject::GetTimerRefByName(const char *name) const
{
  DSString  *string;
  DSTimerRef timer_ref;

  string = new DSString(name);
  assert(string);

  timer_ref = GetTimerRefByName(string);

  delete string;

  return timer_ref;
}

DSSignalslistRef DSObject::GetSignallistRefByName(DSString *name) const
{
  DSObjectRef     object         = this;
  DSSignalslistRef signallist_ref = NULL;

  assert(name);

  /*******************************************************/
  /* Umgebung (Scope) suchen, in welcher die Signalliste */
  /* definiert ist:                                      */
  /*******************************************************/
  while(object != NULL &&
        signallist_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_PROCESS:
        signallist_ref = ((DSProcess *)object)->DSSignalslistComponent::GetSignallist(*name);
        break;
      case DS_BLOCK:
        signallist_ref = ((DSBlock*)object)->DSSignalslistComponent::GetSignallist(name);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        signallist_ref = ((DSBlockSubstructure*)object)->DSSignalslistComponent::GetSignallist(name);
        break;
      case DS_SYSTEM:
        signallist_ref = ((DSSystem*)object)->DSSignalslistComponent::GetSignallist(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return signallist_ref;
}

DSSignalslistRef DSObject::GetSignallistRefByName(const char *name) const
{
  DSString       *string;
  DSSignalslistRef signallist_ref;

  string = new DSString(name);
  assert(string);

  signallist_ref = GetSignallistRefByName(string);

  delete string;

  return signallist_ref;
}

DSProcessRef DSObject::GetProcessRefByName(DSString *name) const
{
  DSObjectRef  object      = this;
  DSProcessRef process_ref = NULL;

  assert(name);

  /***************************************************/
  /* Umgebung (Scope) suchen, in welcher der Prozess */
  /* definiert ist:                                  */
  /***************************************************/
  while(object != NULL &&
        process_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_BLOCK:
        process_ref = ((DSBlock*)object)->GetProcess(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return process_ref;
}

DSProcessRef DSObject::GetProcessRefByName(const char *name) const
{
  DSString    *string;
  DSProcessRef process_ref;

  string = new DSString(name);
  assert(string);

  process_ref = GetProcessRefByName(string);

  delete string;

  return process_ref;
}

DSProcedureRef DSObject::GetProcedureRefByName(DSString *name) const
{
  DSObjectRef    object        = this;
  DSProcedureRef procedure_ref = NULL;

  assert(name);

  /****************************************************/
  /* Umgebung (Scope) suchen, in welcher die Prozedur */
  /* definiert ist:                                   */
  /****************************************************/
  while(object != NULL &&
        procedure_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_SYSTEM:
        procedure_ref = ((DSSystem*)object)->GetProcedure(name);
        break;
      case DS_BLOCK:
        procedure_ref = ((DSBlock*)object)->GetProcedure(name);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        procedure_ref = ((DSBlockSubstructure*)object)->GetProcedure(name);
        break;
      case DS_PROCESS:
        procedure_ref = ((DSProcess*)object)->GetProcedure(name);
        break;
      case DS_PROCEDURE:
        procedure_ref = ((DSProcedure*)object)->GetProcedure(name);
        if (procedure_ref == NULL)
        {
          if (((DSProcedure*)object)->GetName() == // rekursiver Aufruf?
              name)
          {
            procedure_ref = (DSProcedure*)this;
					}
				}
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return procedure_ref;
}

DSProcedureRef DSObject::GetProcedureRefByName(const char *name) const
{
  DSString      *string;
  DSProcedureRef procedure_ref;

  string = new DSString(name);
  assert(string);

  procedure_ref = GetProcedureRefByName(string);

  delete string;

  return procedure_ref;
}

DSBlockRef DSObject::GetBlockRefByName(DSString *name) const
{
  DSObjectRef object    = this;
  DSBlockRef  block_ref = NULL;

  assert(name);

  /*************************************************/
  /* Umgebung (Scope) suchen, in welcher der Block */
  /* definiert ist:                                */
  /*************************************************/
  while(object != NULL &&
        block_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_SYSTEM:
        block_ref = ((DSSystem*)object)->GetBlock(name);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        block_ref = ((DSBlockSubstructure*)object)->GetBlock(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return block_ref;
}

DSBlockRef DSObject::GetBlockRefByName(const char *name) const
{
  DSString  *string;
  DSBlockRef block_ref;

  string = new DSString(name);
  assert(string);

  block_ref = GetBlockRefByName(string);

  delete string;

  return block_ref;
}

DSStateRef DSObject::GetStateRefByName(DSString *name) const
{
  DSObjectRef object    = this;
  DSStateRef  state_ref = NULL;

  assert(name);

  /*************************************************/
  /* Umgebung (Scope) suchen, in welcher der State */
  /* definiert ist:                                */
  /*************************************************/
  while(object != NULL &&
        state_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_PROCESS:
        state_ref = ((DSProcess*)object)->GetState(name);
        break;
      case DS_PROCEDURE:
        state_ref = ((DSProcedure*)object)->GetState(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return state_ref;
}

DSStateRef DSObject::GetStateRefByName(const char *name) const
{
  DSString *string;
  DSStateRef state_ref;

  string = new DSString(name);
  assert(string);

  state_ref = GetStateRefByName(string);

  delete string;

  return state_ref;
}

DSChannelRef DSObject::GetChannelRefByName(DSString *name) const
{
  DSObjectRef  object      = this;
  DSChannelRef channel_ref = NULL;

  assert(name);

  /*************************************************/
  /* Umgebung (Scope) suchen, in welcher der Kanal */
  /* definiert ist:                                */
  /*************************************************/
  while(object != NULL &&
        channel_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_SYSTEM:
        channel_ref = ((DSSystem*)object)->GetChannel(name);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        channel_ref = ((DSBlockSubstructure*)object)->GetChannel(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return channel_ref;
}

DSChannelRef DSObject::GetChannelRefByName(const char *name) const
{
  DSString    *string;
  DSChannelRef channel_ref;

  string = new DSString(name);
  assert(string);

  channel_ref = GetChannelRefByName(string);

  delete string;

  return channel_ref;
}

DSSignalRouteRef DSObject::GetSignalRouteRefByName(DSString *name) const
{
  DSObjectRef      object          = this;
  DSSignalRouteRef signalroute_ref = NULL;

  assert(name);

  /*******************************************************/
  /* Umgebung (Scope) suchen, in welcher die Signalroute */
  /* definiert ist:                                      */
  /*******************************************************/
  while(object != NULL &&
        signalroute_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_BLOCK:
        signalroute_ref = ((DSBlock*)object)->GetSignalRoute(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return signalroute_ref;
}

DSSignalRouteRef DSObject::GetSignalRouteRefByName(const char *name) const
{
  DSString        *string;
  DSSignalRouteRef signalroute_ref;

  string = new DSString(name);
  assert(string);

  signalroute_ref = GetSignalRouteRefByName(string);

  delete string;

  return signalroute_ref;
}

DSSystemRef DSObject::GetThisSystem(void) const
{
  DSObjectRef  object      = this;
  DSSystemRef system_ref = NULL;

  /*************************************************/
  /* Umgebung (Scope) suchen, in welcher das System */
  /* definiert ist:                                */
  /*************************************************/
  while(object != NULL &&
        system_ref == NULL)
  {
    if (object->GetType() == DS_SYSTEM)
    {
      system_ref = (DSSystem*)object;
      break;
    }
    object = object->GetParent();
  } // while
  return system_ref;
}

DSBlockRef DSObject::GetThisBlock(void) const
{
  DSObjectRef  object      = this;
  DSBlockRef   block_ref = NULL;

  /*************************************************/
  /* Umgebung (Scope) suchen, in welcher der Block */
  /* definiert ist:                                */
  /*************************************************/
  while(object != NULL &&
        block_ref == NULL)
  {
    if (object->GetType() == DS_BLOCK)
    {
      block_ref = (DSBlock *)object;
      break;
    }
    object = object->GetParent();
  } // while
  return block_ref;
}

DSProcessRef DSObject::GetThisProcess(void) const
{
  DSObjectRef  object      = this;
  DSProcessRef process_ref = NULL;

  /*************************************************/
  /* Umgebung (Scope) suchen, in welcher der Process */
  /* definiert ist:                                */
  /*************************************************/
  while(object != NULL &&
        process_ref == NULL)
  {
    if (object->GetType() == DS_PROCESS)
    {
      process_ref = (DSProcess*)object;
      break;
    }
    object = object->GetParent();
  } // while
  return process_ref;
}

DSProcedureRef DSObject::GetThisProcedure(void) const
{
  DSObjectRef    object        = this;
  DSProcedureRef procedure_ref = NULL;

  /*************************************************/
  /* Umgebung (Scope) suchen, in welcher der Process */
  /* definiert ist:                                */
  /*************************************************/
  while(object != NULL &&
        procedure_ref == NULL)
  {
    if (object->GetType() == DS_PROCEDURE)
    {
      procedure_ref = (DSProcedure *)object;
      break;
    }
    object = object->GetParent();
  } // while
  return procedure_ref;
}

DSStateRef DSObject::GetThisState(void) const
{
  DSObjectRef object    = this;
  DSStateRef  state_ref = NULL;

  /*************************************************/
  /* Umgebung (Scope) suchen, in welcher der State */
  /* definiert ist:                                */
  /*************************************************/
  while(object != NULL &&
        state_ref == NULL)
  {
    if (object->GetType() == DS_STATE)
    {
      state_ref = (DSState*)object;
      break;
    }
    object = object->GetParent();
  } // while
  return state_ref;
}

DSAtomRef DSObject::GetThisAtom(void) const
{
  DSObjectRef object    = this;
  DSAtomRef  atom_ref = NULL;

  /*************************************************/
  /* Umgebung (Scope) suchen, in welcher das Atom  */
  /* definiert ist:                                */
  /*************************************************/
  while(object != NULL &&
        atom_ref == NULL)
  {
    if (object->GetType() == DS_ATOM)
    {
      atom_ref = (DSAtom*)object;
      break;
    }
    object = object->GetParent();
  } // while
  return atom_ref;
}

DSMachineServiceRef DSObject::GetMachineServiceRefByName(DSString *name) const
{
  DSObjectRef          object             = this;
  DSMachineServiceRef machineservice_ref = NULL;

  assert(name);

  /****************************************************/
  /* Umgebung (Scope) suchen, in welcher der Dienst   */
  /* definiert ist:                                   */
  /****************************************************/
  while(object != NULL &&
        machineservice_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_BLOCK:
        machineservice_ref = ((DSBlock*)object)->GetMachineService(name);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        machineservice_ref = ((DSBlockSubstructure*)object)->GetMachineService(name);
        break;
      case DS_SYSTEM:
        machineservice_ref = ((DSSystem*)object)->GetMachineService(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return machineservice_ref;
}

DSMachineServiceRef DSObject::GetMachineServiceRefByName(const char *name) const
{
  DSString           *string;
  DSMachineServiceRef machineservice_ref;

  string = new DSString(name);
  assert(string);

  machineservice_ref = GetMachineServiceRefByName(string);

  delete string;

  return machineservice_ref;
}

DSPipeRef DSObject::GetPipeRefByName(DSString *name) const
{
  DSObjectRef object   = this;
  DSPipeRef   pipe_ref = NULL;

  assert(name);

  /*************************************************/
  /* Umgebung (Scope) suchen, in welcher die Pipe  */
  /* definiert ist:                                */
  /*************************************************/
  while(object != NULL &&
        pipe_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_SYSTEM:
        pipe_ref = ((DSSystem*)object)->GetPipe(name);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        pipe_ref = ((DSBlockSubstructure*)object)->GetPipe(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return pipe_ref;
}

DSPipeRef DSObject::GetPipeRefByName(const char *name) const
{
  DSString *string;
  DSPipeRef pipe_ref;

  string = new DSString(name);
  assert(string);

  pipe_ref = GetPipeRefByName(string);

  delete string;

  return pipe_ref;
}

DSLinkRef DSObject::GetLinkRefByName(DSString *name) const
{
  DSObjectRef object   = this;
  DSLinkRef   link_ref = NULL;

  assert(name);

  /************************************************/
  /* Umgebung (Scope) suchen, in welcher der Link */
  /* definiert ist:                               */
  /************************************************/
  while(object != NULL &&
        link_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_BLOCK:
        link_ref = ((DSBlock*)object)->GetLink(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return link_ref;
}

DSLinkRef DSObject::GetLinkRefByName(const char *name) const
{
  DSString *string;
  DSLinkRef link_ref;

  string = new DSString(name);
  assert(string);

  link_ref = GetLinkRefByName(string);

  delete string;

  return link_ref;
}

DSMachineRef DSObject::GetMachineRefByName(DSString *name) const
{
  DSObjectRef   object      = this;
  DSMachineRef machine_ref = NULL;

  assert(name);

  /****************************************************/
  /* Umgebung (Scope) suchen, in welcher die Maschine */
  /* definiert ist:                                   */
  /****************************************************/
  while(object != NULL &&
        machine_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_BLOCK:
        machine_ref = ((DSBlock*)object)->GetMachine(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return machine_ref;
}

DSMachineRef DSObject::GetMachineRefByName(const char *name) const
{
  DSString    *string;
  DSMachineRef machine_ref;

  string = new DSString(name);
  assert(string);

  machine_ref = GetMachineRefByName(string);

  delete string;

  return machine_ref;
}

DSSensorRef DSObject::GetSensorRefByName(DSString *name) const
{
  DSObjectRef object     = this;
  DSSensorRef sensor_ref = NULL;

  assert(name);

  /****************************************************/
  /* Umgebung (Scope) suchen, in welcher der Sensor   */
  /* definiert ist:                                   */
  /****************************************************/
  while(object != NULL &&
        sensor_ref == NULL)
  {
    switch(object->GetType())
    {
      case DS_SYSTEM:
        sensor_ref = ((DSSystem*)object)->GetSensor(name);
        break;
      case DS_BLOCK:
        sensor_ref = ((DSBlock*)object)->GetSensor(name);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        sensor_ref = ((DSBlockSubstructure*)object)->GetSensor(name);
        break;
      case DS_PROCESS:
        sensor_ref = ((DSProcess*)object)->GetSensor(name);
        break;
      case DS_MACHINE:
        sensor_ref = ((DSMachine*)object)->GetSensor(name);
        break;
      default:
        break;
    } // switch
    object = object->GetParent();
  } // while
  return sensor_ref;
}

DSSensorRef DSObject::GetSensorRefByName(const char *name) const
{
  DSString   *string;
  DSSensorRef sensor_ref;

  string = new DSString(name);
  assert(string);

  sensor_ref = GetSensorRefByName(string);

  delete string;

  return sensor_ref;
}
