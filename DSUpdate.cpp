/****************************************************************************
 *                 Modul: $RCSfile: DSUpdate.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/12 11:52:37 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Parameter, die in Verbindung mit einer QSDL-Update-Aktion
 *          angegeben sind
 *
 * Funktionen: GetSensorRef(): Gibt eine Referenz auf den entsprechenden
 *                             Sensor zurueck
 *             GetSample(): Liefert den Update-Sample 
 *             SetSensorRef(): Speichert den uebergebenen Sensorzeiger
 *             SetSample(): Setzt den entsprechenden Sample-Wert
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

#include "DSUpdate.h"
#include "DSSensor.h"
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

DSUpdate::DSUpdate(DSObject     *father,
                   DSString     *label_name, 
                   DSSensorRef   s_ref,
                   DSExpression *sample_exp,
                   DSExpression *value_exp) :
  DSAction(father, DS_UPDATE, label_name),
  sensor_ref(s_ref), 
  sample(sample_exp),
  value(value_exp)
{
  if (sample)
  {
    if (sample->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      sample->SetParent(this);
    }
  }
  if (value)
  {
    if (value->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      value->SetParent(this);
    }
  }
}

DSUpdate::DSUpdate(DSObject     *father,
                   DSString     &label_name, 
                   DSSensorRef   s_ref,
                   DSExpression *sample_exp,
                   DSExpression *value_exp) :
  DSAction(father, DS_SET, &label_name),
  sensor_ref(s_ref), 
  sample(sample_exp),
  value(value_exp)
{
  if (sample)
  {
    if (sample->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      sample->SetParent(this);
    }
  }
  if (value)
  {
    if (value->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      value->SetParent(this);
    }
  }
}

DSUpdate::DSUpdate(DSObject     *father,
                   const char   *label_name, 
                   DSSensorRef   s_ref,
                   DSExpression *sample_exp,
                   DSExpression *value_exp) :
  DSAction(father, DS_SET, label_name),
  sensor_ref(s_ref), 
  sample(sample_exp),
  value(value_exp)
{
  if (sample)
  {
    if (sample->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      sample->SetParent(this);
    }
  }
  if (value)
  {
    if (value->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      value->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSUpdate::~DSUpdate(void)
{
  if (sample) delete sample;
  if (value) delete value;
}

/****************************************************************************
 * GetSensorRef(): Liefert Zeiger auf den zu updatenden Sensor
 *                 Ergebnis: Zeiger auf einen Sensor
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSSensorRef DSUpdate::GetSensorRef(void) const
{
  return sensor_ref;
}

/****************************************************************************
 * GetSample():  Liefert Zeiger auf den Samplewert zurueck
 *               Ergebnis: Zeiger auf einen Ausdruck
 *               Seiteneffekte: keine
 ****************************************************************************/

DSExpression* DSUpdate::GetSample(void) const
{
  return sample;
}

/****************************************************************************
 * GetValue():  Liefert Zeiger auf den Valuewert zurueck (nur fuer Frequency-
 *              sensoren verfuegbar)
 *              Ergebnis: Zeiger auf einen Ausdruck
 *              Seiteneffekte: keine
 ****************************************************************************/

DSExpression* DSUpdate::GetValue(void) const
{
  return value;
}

/****************************************************************************
 * SetSensorRef(): Speichert den uebergebenen Zeiger
 *                 -> ssensor : Zeiger auf einen Sensor
 *                 Ergebnis: DS_OK
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSResult DSUpdate::SetSensorRef(DSSensorRef sensor)
{
  sensor_ref = sensor;
  return DS_OK;
}

/****************************************************************************
 * SetSample(): Setzt den Samplewert
 *              -> sample_exp: Zeiger auf eine Sample-Expression
 *              Ergebnis: DS_OK
 *              Seiteneffekte: keine
 ****************************************************************************/

DSResult DSUpdate::SetSample(DSExpression* sample_exp)
{
  if (sample == sample_exp) return DS_OK;

  if (sample) delete sample;
  sample = sample_exp;

  if (sample != NULL)
  {
    if (sample->GetParent() == NULL) // Vater noch nicht geupdatezt ?
    {
      sample->SetParent(this);
    }
  }

  return DS_OK;
}

/****************************************************************************
 * SetValue(): Setzt den Valuewert
 *              -> sample_exp: Zeiger auf eine Value-Expression
 *              Ergebnis: DS_OK
 *              Seiteneffekte: keine
 ****************************************************************************/

DSResult DSUpdate::SetValue(DSExpression* value_exp)
{
  if (value == value_exp) return DS_OK;

  if (value) delete value;
  value = value_exp;

  if (value != NULL)
  {
    if (value->GetParent() == NULL) // Vater noch nicht geupdatezt ?
    {
      value->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSUpdate::Clone(DSObject *father, DSObject *fill_this) const
{
  DSUpdate *new_update;

  if (fill_this == NULL)
  {
    new_update = (DSUpdate *)New(father);
    assert(new_update);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_update = (DSUpdate *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_update);

  if (GetSensorRef())
  {
    new_update->SetSensorRef(GetSensorRef());  // do not clone!
  }

  if (GetSample())
  {
    new_update->SetSample((DSExpression *)GetSample()->Clone((DSObject *)new_update));
  }

  if (GetValue())
  {
    new_update->SetValue((DSExpression *)GetValue()->Clone((DSObject *)new_update));
  }

  return new_update;
}

DSResult DSUpdate::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  (void)what;

  return DS_OK;
}

DSResult DSUpdate::Run(DSWriter *writer, DSType object_type,
                       DSCardinal what) const
{
  assert(writer);
  
  (void)what;
  (void)object_type;

  return DS_OK;
}
