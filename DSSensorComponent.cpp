/****************************************************************************
 *                 Modul: $RCSfile: DSSensorComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe: Basisklasse fuer alle SDL-Strukturen in denen SDL-Sensoren
 *          definiert werden koennen.
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

#include "DSSensorComponent.h"
#include "DSSensor.h"
#include "DSString.h"

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

DSSensorComponent::DSSensorComponent(DSObject *father) :
  parent(father)
{
  sensor_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSensorComponent::~DSSensorComponent(void)
{
  if (sensor_definition_list) delete sensor_definition_list;
}

DSSensorKeyList* DSSensorComponent::GetSensorList (void) const
{
  return sensor_definition_list;
}

DSSensor *DSSensorComponent::GetSensor (DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (sensor_definition_list == NULL)
  {
    return NULL;
  }

  if (sensor_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return sensor_definition_list->GetCurrentData();
}

DSSensor *DSSensorComponent::GetSensor (DSString& n) const
{
  return GetSensor (&n);
}

DSSensor *DSSensorComponent::GetSensor (const char * n) const
{
  DSSensor *signal;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  signal = GetSensor (str);
  delete str;

  return signal;
}

DSSensor *DSSensorComponent::GetFirstSensor (void) const
{
  if (sensor_definition_list == NULL)
  {
    return NULL;
  }

  if (sensor_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return sensor_definition_list->GetCurrentData();
}

DSSensor *DSSensorComponent::GetNextSensor (void) const
{
  if (sensor_definition_list == NULL)
  {
    return NULL;
  }

  if (sensor_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return sensor_definition_list->GetCurrentData();
}

DSResult DSSensorComponent::SetSensorList(DSSensorKeyList *list)
{
  if (sensor_definition_list == list) return DS_OK;

  if (sensor_definition_list != NULL)
  {
    delete sensor_definition_list;
  }
  sensor_definition_list = list;
  return DS_OK;
}

DSResult DSSensorComponent::InsertSensor (DSSensor* sensor)
{
  assert(sensor != NULL);
  assert(sensor->GetName() != NULL);

  if (sensor_definition_list == NULL)
  {
    sensor_definition_list = new DSSensorKeyList;
    assert(sensor_definition_list != NULL);
  }
  if (sensor->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    sensor->SetParent(DSSensorComponent::parent);
  }
  return sensor_definition_list->Append(sensor,
                                        new DSString(*sensor->GetName()));
}


/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSSensorComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSSensorComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
