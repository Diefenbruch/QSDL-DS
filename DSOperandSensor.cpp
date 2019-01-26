/****************************************************************************
 *                 Modul: $RCSfile: DSOperandSensor.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung eines Sensornoperanden
 *
 * Funktionen: GetSensorRef(): liefert Zeiger auf die Sensor
 *             SetSensorRef(): setzt den Zeiger auf die Sensor
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

#include "DSOperandSensor.h"
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

DSOperandSensor::DSOperandSensor(DSObject *father,
                                   DSSensorRef syn_ref) :
  DSOperand(father, DS_OPN_SENSOR),
  sensor_ref(syn_ref)
{
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOperandSensor::~DSOperandSensor(void)
{
}

DSObject *DSOperandSensor::New(DSObject *father) const
{
  return new DSOperandSensor(father);
}

/****************************************************************************
 * GetSensorRef(): liefert Zeiger auf die Sensor
 *                   Ergebnis: Zeiger auf DSSensor
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSSensorRef DSOperandSensor::GetSensorRef(void) const
{
  return sensor_ref;
}

/****************************************************************************
 * SetSensorRef(): setzt Zeiger auf die Sensor
 *                   ->elem: Zeiger auf DSSensor
 *                   Ergebnis: DS_OK
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOperandSensor::SetSensorRef(DSSensorRef sen_ref)
{
  sensor_ref = sen_ref;
  return DS_OK;
}

DSObject *DSOperandSensor::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOperandSensor *new_operand_sensor;

  if (fill_this == NULL)
  {
    new_operand_sensor = (DSOperandSensor *)New(father); // virtueller Konstruktor
    assert(new_operand_sensor);
  }
  else
  {
    assert(fill_this->GetType() == DS_OPERAND);
    new_operand_sensor = (DSOperandSensor *)fill_this;
  }

  // Basisklassen clonen:
  DSOperand::Clone(father, new_operand_sensor);

  new_operand_sensor->SetSensorRef(GetSensorRef());

  return new_operand_sensor;
}

DSResult DSOperandSensor::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);
  (void)what;

  return DS_OK;
}
