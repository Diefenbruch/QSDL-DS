/****************************************************************************
 *                 Modul: $RCSfile: DSClear.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/09 10:59:11 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Parameter, die in Verbindung mit einer QSDL-Clear-Aktion
 *          angegeben sind
 *
 * Funktionen: GetSensorRef(): Gibt eine Referenz auf den entsprechenden
 *                              Sensor zurueck
 *             SetSensorRef(): Speichert den uebergebenen Sensorzeiger
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

#include "DSClear.h"
#include "DSSensor.h"
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

DSClear::DSClear(DSObject    *father,
                 DSString    *label_name, 
                 DSSensorRef  s_ref) :
  DSAction(father, DS_CLEAR, label_name),
  sensor_ref(s_ref)
{
}

DSClear::DSClear(DSObject    *father,
                 DSString    &label_name, 
                 DSSensorRef  s_ref) :
  DSAction(father, DS_CLEAR, &label_name),
  sensor_ref(s_ref)
{
}

DSClear::DSClear(DSObject    *father,
                 const char  *label_name, 
                 DSSensorRef  s_ref) :
  DSAction(father, DS_CLEAR, label_name),
  sensor_ref(s_ref)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSClear::~DSClear(void)
{
}

/****************************************************************************
 * GetSensorRef(): Liefert Zeiger auf den zurueckgesetzten Sensor
 *                 Ergebnis: Zeiger auf einen Sensor
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSSensorRef DSClear::GetSensorRef(void) const
{
  return sensor_ref;
}

/****************************************************************************
 * SetSensorRef(): Speichert den uebergebenen Zeiger
 *                -> sensor : Zeiger auf einen Sensor
 *                Ergebnis: DS_OK
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSClear::SetSensorRef(DSSensorRef sensor)
{
  sensor_ref = sensor;
  return DS_OK;
}

DSObject *DSClear::Clone(DSObject *father, DSObject *fill_this) const
{
  DSClear *new_clear;

  if (fill_this == NULL)
  {
    new_clear = (DSClear *)New(father);
    assert(new_clear);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_clear = (DSClear *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_clear);

  new_clear->SetSensorRef(GetSensorRef());

  return new_clear;
}

DSResult DSClear::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  (void)what;

  return DS_OK;
}

DSResult DSClear::Run(DSWriter *writer, DSType object_type,
                      DSCardinal what) const
{
  assert(writer);
  
  (void)what;
  (void)object_type;

  return DS_OK;
}
