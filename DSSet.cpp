/****************************************************************************
 *                 Modul: $RCSfile: DSSet.cpp,v $
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
 *             GetTime(): Liefert die Zeit 
 *             SetTimerRef(): Speichert den uebergebenen Timerzeiger
 *             SetTime(): Setzt die entsprechende Zeit
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

#include "DSSet.h"
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

DSSet::DSSet(DSObject         *father,
             DSString         *label_name, 
             DSTimerRef        t_ref,
             DSExpressionList *i_list,
             DSExpression     *time_exp) :
  DSAction(father, DS_SET, label_name),
  DSActualParamComponent(NULL, i_list), 
  timer_ref(t_ref), 
  time(time_exp)
{
  DSActualParamComponent::SetComponentParent(this);

  if (time)
  {
    if (time->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      time->SetParent(this);
    }
  }
}

DSSet::DSSet(DSObject         *father,
             DSString         &label_name, 
             DSTimerRef        t_ref,
             DSExpressionList *i_list,
             DSExpression     *time_exp) :
  DSAction(father, DS_SET, &label_name),
  DSActualParamComponent(NULL, i_list), 
  timer_ref(t_ref), 
  time(time_exp)
{
  DSActualParamComponent::SetComponentParent(this);

  if (time)
  {
    if (time->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      time->SetParent(this);
    }
  }
}

DSSet::DSSet(DSObject         *father,
             const char       *label_name, 
             DSTimerRef        t_ref,
             DSExpressionList *i_list,
             DSExpression     *time_exp) :
  DSAction(father, DS_SET, label_name),
  DSActualParamComponent(NULL, i_list), 
  timer_ref(t_ref), 
  time(time_exp)
{
  DSActualParamComponent::SetComponentParent(this);

  if (time)
  {
    if (time->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      time->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSet::~DSSet(void)
{
  if (time) delete time;
}

/****************************************************************************
 * GetTimerRef(): Liefert Zeiger auf den zu setzenden Timer
 *                 Ergebnis: Zeiger auf einen Timer
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSTimerRef DSSet::GetTimerRef(void) const
{
  return timer_ref;
}

/****************************************************************************
 * GetTime():  Liefert Zeiger auf den Zeitwert zurueck
 *             Ergebnis: Zeiger auf einen String
 *             Seiteneffekte: keine
 ****************************************************************************/

DSExpression* DSSet::GetTime(void) const
{
  return time;
}

/****************************************************************************
 * SetTimerRef(): Speichert den uebergebenen Zeiger
 *                -> timer : Zeiger auf einen Timer
 *                Ergebnis: DS_OK
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSet::SetTimerRef(DSTimerRef timer)
{
  timer_ref = timer;
  return DS_OK;
}

/****************************************************************************
 * SetTime(): Setzt die Zeit, an welcher der Timer ablaeuft
 *            -> time_exp: Zeiger auf eine Time-Expression
 *            Ergebnis: DS_OK
 *            Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSet::SetTime(DSExpression* time_exp)
{
  if (time == time_exp) return DS_OK;

  if (time) delete time;
  time = time_exp;

  if (time != NULL)
  {
    if (time->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      time->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSSet::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSet *new_set;

  if (fill_this == NULL)
  {
    new_set = (DSSet *)New(father);
    assert(new_set);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_set = (DSSet *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_set);

  if (GetActualParamList())
  {
    new_set->SetActualParamList(GetActualParamList()->Clone((DSObject *)new_set));
  }

  if (GetTimerRef())
  {
    new_set->SetTimerRef(GetTimerRef());  // do not clone!
  }

  if (GetTime())
  {
    new_set->SetTime((DSExpression *)GetTime()->Clone((DSObject *)new_set));
  }

  return new_set;
}

DSResult DSSet::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (timer_ref) timer_ref->Write(writer, what);
  Run(writer, DS_ACTUALPARAM, what);
  if (time) time->Write(writer, what);

  return DS_OK;
}

DSResult DSSet::Run(DSWriter *writer, DSType object_type,
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
