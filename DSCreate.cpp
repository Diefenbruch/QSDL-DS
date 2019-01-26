/****************************************************************************
 *                 Modul: $RCSfile: DSCreate.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Parameter (Prozessnamens), der in Verbindung mit einem
 *          Create-Befehl angegeben ist
 *
 * Funktionen: GetProcessRef(): Gibt eine Referenz auf den entsprechenden
 *                              Prozess zurueck
 *             GetParamList() : Liefert den Zeiger auf die Parameterliste
 *             SetProcessRef(): Speichert den uebergebenen Prozesszeiger
 *             SetParamList() : Speichert den uebergebenen Zeiger
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

#include "DSCreate.h"
#include "DSProcess.h"
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

DSCreate :: DSCreate(DSObject *father,
                     DSString *label_name, 
                     DSProcessRef proc, 
                     DSActualParamList *p_list) :
  DSAction(father, DS_CREATE, label_name),
  DSActualParamComponent(NULL, p_list),
  process_ref(proc)
{
  DSActualParamComponent::SetComponentParent(this);
}

DSCreate :: DSCreate(DSObject *father,
                     DSString& label_name, 
                     DSProcessRef proc, 
                     DSActualParamList *p_list) :
  DSAction(father, DS_CREATE, &label_name),
  DSActualParamComponent(NULL, p_list),
  process_ref(proc)
{
  DSActualParamComponent::SetComponentParent(this);
}

DSCreate :: DSCreate(DSObject *father,
                     const char *label_name, 
                     DSProcessRef proc, 
                     DSActualParamList *p_list) :
  DSAction(father, DS_CREATE, label_name),
  DSActualParamComponent(NULL, p_list),
  process_ref(proc)
{
  DSActualParamComponent::SetComponentParent(this);
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSCreate::~DSCreate(void)
{
}

/****************************************************************************
 * GetProcessRef(): Liefert Zeiger auf den erzeugten Prozess des
 *                 CREATE-Befehls zurueck
 *                 Ergebnis: Zeiger auf einen Prozess
 *                 Seiteneffekte: keine
 ****************************************************************************/
 
DSProcessRef DSCreate::GetProcessRef(void) const
{
  return process_ref;
}

/****************************************************************************
 * SetProcessRef(): Speichert den uebergebenen Zeiger
 *                  -> proc : Zeiger auf ein Signal
 *                  Ergebnis: DS_OK
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSResult DSCreate::SetProcessRef(DSProcessRef proc)
{
  process_ref = proc;
  return DS_OK;
}

DSObject *DSCreate::Clone(DSObject *father, DSObject *fill_this) const
{
  DSCreate *new_create;

  if (fill_this == NULL)
  {
    new_create = (DSCreate *)New(father);
    assert(new_create);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_create = (DSCreate *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_create);

  if (GetActualParamList())
  {
    new_create->SetActualParamList(GetActualParamList()->Clone((DSObject *)new_create));
  }

  new_create->SetProcessRef(GetProcessRef());

  return new_create;
}

DSResult DSCreate::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (process_ref) process_ref->Write(writer, what);
  Run(writer, DS_ACTUALPARAM, what);

  return DS_OK;
}

DSResult DSCreate::Run(DSWriter *writer, DSType object_type,
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
