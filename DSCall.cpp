/****************************************************************************
 *                 Modul: $RCSfile: DSCall.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.3 $
 * 
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          des Parameters (Statenamens), der in Verbindung mit einem 
 *          Nextstate-Befehl angegeben ist
 *
 * Funktionen: GetProcedureRef(): liefert Zeiger auf die aufzurufende Proc
 *             GetParameterList(): liefert die Aufruf-Parameterliste
 *             SetProcedureRef(): speichert Proc-Zeiger
 *             SetParameterList(): speichert Parameterliste
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

#include "DSCall.h"
#include "DSProcedure.h"
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

DSCall::DSCall (DSObject *father,
                DSString *label_name, 
                DSProcedureRef proc,
                DSActualParamList *act_par_list) :
  DSAction(father, DS_CALL, label_name),
  DSActualParamComponent(NULL, act_par_list),
  procedure_ref(proc)
{
  DSActualParamComponent::SetComponentParent(this);
}

DSCall::DSCall (DSObject *father,
                DSString& label_name, 
                DSProcedureRef proc,
                DSActualParamList *act_par_list) :
  DSAction (father, DS_CALL, &label_name),
  DSActualParamComponent(NULL, act_par_list),
  procedure_ref(proc)
{
  DSActualParamComponent::SetComponentParent(this);
}

DSCall::DSCall (DSObject *father,
                const char *label_name, 
                DSProcedureRef proc,
                DSActualParamList *act_par_list) :
  DSAction (father, DS_CALL, label_name),
  DSActualParamComponent(NULL, act_par_list),
  procedure_ref(proc)
{
  DSActualParamComponent::SetComponentParent(this);
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSCall::~DSCall(void)             
{ 
}                                            

/****************************************************************************
 * GetProcedureRef(): Liefert den Zeiger auf die aufgerufene Prozedur zurueck
 *                    Ergebnis: Zeiger auf eine Prozedur
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSProcedureRef DSCall::GetProcedureRef(void) const
{
  return procedure_ref;
}

/****************************************************************************
 * SetProcedureRef(): Speichert den uebergebenen Zeiger
 *                    -> proc_ref: Zeiger auf eine Prozedur
 *                    Ergebnis: DS_OK
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSResult DSCall::SetProcedureRef(DSProcedureRef proc_ref)
{
  procedure_ref = proc_ref;
  return DS_OK;
}

DSObject *DSCall::Clone(DSObject *father, DSObject *fill_this) const
{
  DSCall *new_call;

  if (fill_this == NULL)
  {
    new_call = (DSCall *)New(father);
    assert(new_call);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    assert(((DSAction *)fill_this)->GetTag() == DS_CALL);
    new_call = (DSCall *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_call);
 
  if (GetActualParamList())
  {
    new_call->SetActualParamList(GetActualParamList()->Clone((DSObject *)new_call));
  }

  new_call->SetProcedureRef(GetProcedureRef());

  return new_call;
}

DSResult DSCall::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (procedure_ref) procedure_ref->Write(writer, what);
  Run(writer, DS_ACTUALPARAM, what);

  return DS_OK;
}

DSResult DSCall::Run(DSWriter *writer, DSType object_type,
                     DSCardinal what) const
{
  DSResult       result;
  DSActualParam *actual_param;

  switch(object_type)
  {
    case DS_ACTUALPARAM:
      for (actual_param = GetFirstActualParam();
           actual_param;
           actual_param = GetNextActualParam())
      {
        result = actual_param->Write(writer, what);
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
