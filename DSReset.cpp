/****************************************************************************
 *                 Modul: $RCSfile: DSReset.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.3 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Parameter, die in Verbindung mit einem
 *          RESET-Befehl angegeben sind
 *
 * Funktionen: GetTimerRef(): Gibt eine Referenz auf den entsprechenden
 *                              Timer zurueck
 *             SetTimerRef(): Speichert den uebergebenen Timerzeiger
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

#include "DSReset.h"
#include "DSTimer.h"
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

DSReset::DSReset(DSObject         *father,
                 DSString         *label_name, 
                 DSTimerRef        t_ref, 
                 DSExpressionList *i_list) :
  DSAction(father, DS_RESET, label_name),
  DSActualParamComponent(NULL, i_list),
  timer_ref(t_ref)
{
  DSActualParamComponent::SetComponentParent(this);
}

DSReset::DSReset(DSObject         *father,
                 DSString         &label_name, 
                 DSTimerRef        t_ref, 
                 DSExpressionList *i_list) :
  DSAction(father, DS_RESET, &label_name),
  DSActualParamComponent(NULL, i_list),
  timer_ref(t_ref)
{
  DSActualParamComponent::SetComponentParent(this);
}

DSReset::DSReset(DSObject         *father,
                 const char       *label_name, 
                 DSTimerRef        t_ref, 
                 DSExpressionList *i_list) :
  DSAction(father, DS_RESET, label_name),
  DSActualParamComponent(NULL, i_list),
  timer_ref(t_ref)
{
  DSActualParamComponent::SetComponentParent(this);
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSReset::~DSReset(void)
{
}

/****************************************************************************
 * GetTimerRef(): Liefert Zeiger auf den zurueckzusetzenden Timer
 *                 Ergebnis: Zeiger auf einen Timer
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSTimerRef DSReset::GetTimerRef(void) const
{
  return timer_ref;
}

/****************************************************************************
 * SetTimerRef(): Speichert den uebergebenen Zeiger
 *                -> timer : Zeiger auf einen Timer
 *                Ergebnis: DS_OK
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSReset::SetTimerRef(DSTimerRef timer)
{
  timer_ref = timer;
  return DS_OK;
}

DSObject *DSReset::Clone(DSObject *father, DSObject *fill_this) const
{
  DSReset *new_reset;

  if (fill_this == NULL)
  {
    new_reset = (DSReset *)New(father);
    assert(new_reset);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_reset = (DSReset *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_reset);

  if (GetActualParamList())
  {
    new_reset->SetActualParamList(GetActualParamList()->Clone((DSObject *)new_reset));
  }
  
  new_reset->SetTimerRef(GetTimerRef());

  return new_reset;
}

DSResult DSReset::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (timer_ref) timer_ref->Write(writer, what);
  Run(writer, DS_ACTUALPARAM, what);

  return DS_OK;
}

DSResult DSReset::Run(DSWriter *writer, DSType object_type,
                      DSCardinal what) const
{
  DSResult         result;
  DSActualParamRef actual_param;

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
