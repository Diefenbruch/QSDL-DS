/****************************************************************************
 *                 Modul: $RCSfile: DSInputSignal.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.3 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Variablen in Verbindung mit einem INPUT-Befehl
 *
 * Funktionen: GetSignalRef(): Gibt einen Zeiger auf ein Signal zurueck
 *             SetSignalRef(): Speichert Signaladdresse
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

#include "DSInputSignal.h"
#include "DSInput.h" // wegen parent
#include "DSSignal.h"
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

DSInputSignal::DSInputSignal(DSObject             *father,
                             DSSignalRef           sig_ref,
                             DSVariableAccessList *access_list) :
  DSObject(DS_INPUTSIGNAL, father),
  DSVariableAccessComponent(NULL, access_list),
  signal_ref(sig_ref)
{
  DSVariableAccessComponent::SetComponentParent(this);

  if (father)
  {
    switch(father->GetType())
    {
      case DS_INPUT:
        ((DSInput*)father)->InsertInputSignal(this);
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

DSInputSignal::~DSInputSignal(void)
{
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSInputSignal::New(DSObject *father) const
{
  return new DSInputSignal(father);
}

/****************************************************************************
 * GetSignalRef(): Liefert den Zeiger auf das Signal zurueck
 *                 Ergebnis: Zeiger auf ein Signal
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSSignalRef DSInputSignal::GetSignalRef(void) const
{
  return signal_ref;
}

/****************************************************************************
 * SetSignalRef(): Speichert den uebergebenen Zeiger
 *                -> sig_ref: Zeiger auf einen DSString
 *                Ergebnis: TRUE
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSInputSignal::SetSignalRef(DSSignalRef sig_ref)
{
  signal_ref = sig_ref;
  return DS_OK;
}

DSObject *DSInputSignal::Clone(DSObject *father, DSObject *fill_this) const
{
  DSInputSignal *new_input_signal;

  if (fill_this == NULL)
  {
    new_input_signal = (DSInputSignal *)New(father);
    assert(new_input_signal);
  }
  else
  {
    assert(fill_this->GetType() == DS_INPUTSIGNAL);
    new_input_signal = (DSInputSignal *)fill_this;
  }

  if (GetVariableAccessList())
  {
    new_input_signal->SetVariableAccessList(GetVariableAccessList()->Clone((DSObject *)new_input_signal));
  }
  
  new_input_signal->SetSignalRef(GetSignalRef());

  return new_input_signal;
}

DSResult DSInputSignal::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (signal_ref) signal_ref->Write(writer, what);
  Run(writer, DS_VARIABLEACCESS, what);

  return DS_OK;
}

DSResult DSInputSignal::Run(DSWriter *writer, DSType object_type,
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
