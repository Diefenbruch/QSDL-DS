/****************************************************************************
 *                 Modul: $RCSfile: DSInputTimerSignal.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.3 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Referenz auf den Timer und die Variablenliste in Verbindung
 *          mit einem INPUT-Befehl
 *
 * Funktionen: GetTimerRef(): Gibt einen Zeiger auf einen Timer zurueck
 *             SetTimerRef(): Speichert Timeraddresse
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

#include "DSInputTimerSignal.h"
#include "DSInput.h"  // wegen parent
#include "DSTimer.h"
#include "DSVariableAccess.h"

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

DSInputTimerSignal::DSInputTimerSignal(DSObject          *father,
                                       DSTimerRef         time_ref,
                                       DSVariableAccessList *access_list) :
  DSObject(DS_INPUTTIMERSIGNAL, father),
  DSVariableAccessComponent(NULL, access_list),
  timer_ref(time_ref)
{
  DSVariableAccessComponent::SetComponentParent(this);

  if (father)
  {
    switch(father->GetType())
    {
      case DS_INPUT:
        ((DSInput*)father)->InsertInputTimerSignal(this);
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

DSInputTimerSignal::~DSInputTimerSignal(void)
{
}

/****************************************************************************
 * GetTimerRef(): Liefert den Zeiger auf den Timer zurueck
 *                Ergebnis: Zeiger auf einen Timer
 *                Seiteneffekte: keine
 ****************************************************************************/

DSTimerRef DSInputTimerSignal::GetTimerRef(void) const
{
  return timer_ref;
}

/****************************************************************************
 * SetTimerRef(): Speichert den uebergebenen Zeiger
 *                -> time_ref: Zeiger auf einen String
 *                Ergebnis: TRUE
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSInputTimerSignal::SetTimerRef(DSTimerRef time_ref)
{
  timer_ref = time_ref;
  return DS_OK;
}

DSObject *DSInputTimerSignal::Clone(DSObject *father, DSObject *fill_this) const
{
  DSInputTimerSignal *new_input_timer_signal;

  if (fill_this == NULL)
  {
    new_input_timer_signal = (DSInputTimerSignal *)New(father);
    assert(new_input_timer_signal);
  }
  else
  {
    assert(fill_this->GetType() == DS_INPUTTIMERSIGNAL);
    new_input_timer_signal = (DSInputTimerSignal *)fill_this;
  }

  if (GetVariableAccessList())
  {
    new_input_timer_signal->SetVariableAccessList(GetVariableAccessList()->Clone((DSObject *)new_input_timer_signal));
  }
  
  new_input_timer_signal->SetTimerRef(GetTimerRef());

  return new_input_timer_signal;
}

DSResult DSInputTimerSignal::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (timer_ref) timer_ref->Write(writer, what);
  Run(writer, DS_VARIABLEACCESS, what);

  return DS_OK;
}

DSResult DSInputTimerSignal::Run(DSWriter *writer, DSType object_type,
                                 DSCardinal what) const
{
  DSResult          result;
  DSVariableAccess *variable_access;

  switch(object_type)
  {
    case DS_VARIABLEACCESS:
      for (variable_access = GetFirstVariableAccess();
           variable_access;
           variable_access = GetNextVariableAccess())
      {
        result = variable_access->Write(writer, what);
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
