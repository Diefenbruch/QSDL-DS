/****************************************************************************
 *                 Modul: $RCSfile: DSVariableAccess.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines SDL-Variablenzugriffs.
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

#include "DSVariableAccess.h"
#include "DSInputSignal.h"      // wegen parent
#include "DSInputTimerSignal.h" // wegen parent
#include "DSTask.h"             // wegen parent
#include "DSOperandVariableAccess.h"
#include "DSVariableAccessElem.h"

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

DSVariableAccess::DSVariableAccess(DSObject                 *father,
                                   DSVariableRef             var_ref,
                                   DSVariableAccessElemList *elems) :
  DSObject(DS_VARIABLEACCESS, father),
  variable_ref(var_ref), 
  elem_list(elems)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_INPUTSIGNAL:
        ((DSInputSignal*)father)->InsertVariableAccess(this);
        break;
      case DS_INPUTTIMERSIGNAL:
        ((DSInputTimerSignal*)father)->InsertVariableAccess(this);
        break;
      case DS_ACTION:
        if (((DSAction*)father)->GetTag() == DS_TASK)
        {
          ((DSTask*)father)->SetVariableAccess(this);
        }
        else
        {
          assert(DS_FALSE);
          break;
        }
        break;
      case DS_OPERAND:
        if (((DSOperand*)father)->GetTag() == DS_OPN_VARIABLE_ACCESS)
        {
          ((DSOperandVariableAccess *)father)->SetVariableAccess(this);
        }
        else
        {
          assert(DS_FALSE);
          break;
        }
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

DSVariableAccess::~DSVariableAccess(void)
{
  if (elem_list) delete elem_list;
}

DSObject *DSVariableAccess::New(DSObject *father) const
{
  return new DSVariableAccess(father);
}

/****************************************************************************
 * GetVariableRef(): Liefert die Variable zurueck, auf die zugegriffen wird.
 *                   Ergebnis: Referenz auf Variable
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSVariableRef DSVariableAccess::GetVariableRef(void) const
{
  return variable_ref;
}

DSVariableAccessElemList *DSVariableAccess::GetElemList(void) const
{
  return elem_list;
}

DSVariableAccessElem *DSVariableAccess::GetFirstElem(void) const
{
  if (elem_list == NULL)
  {
    return NULL;
  }

  if (elem_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return elem_list->GetCurrentData();
}

DSVariableAccessElem *DSVariableAccess::GetNextElem(void) const
{
  if (elem_list == NULL)
  {
    return NULL;
  }

  if (elem_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return elem_list->GetCurrentData();
}

/****************************************************************************
 * SetVariableRef(): Speichert den uebergebenen Wert
 *                   -> variable: Wert vom DSVariableRef
 *                   Ergebnis: DS_OK
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSVariableAccess::SetVariableRef(DSVariableRef var_ref)
{
  variable_ref = var_ref;
  return DS_OK;
}

DSResult DSVariableAccess::SetElemList(DSVariableAccessElemList *list)
{
  if (elem_list == list) return DS_OK;

  if (elem_list != NULL)
  {
    delete elem_list;
  }
  elem_list = list;
  return DS_OK;
}

DSResult DSVariableAccess::InsertElem(DSVariableAccessElem* elem)
{
  assert(elem);
  if (elem_list == NULL)
  {
    elem_list = new DSVariableAccessElemList;
    assert(elem_list != NULL);
  }
  if (elem->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    elem->SetParent(this);
  }
  return elem_list->Append(elem);
}

DSObject *DSVariableAccess::Clone(DSObject *father, DSObject *fill_this) const
{
  DSVariableAccess *new_variable_access;

  if (fill_this == NULL)
  {
    new_variable_access = (DSVariableAccess *)New(father);  // virtueller Konstruktor
    assert(new_variable_access);
  }
  else
  {
    assert(fill_this->GetType() == DS_VARIABLEACCESS);
    new_variable_access = (DSVariableAccess *)fill_this;
  }

  if (GetElemList())
  {
    new_variable_access->SetElemList(GetElemList()->Clone((DSObject *)new_variable_access));
  }

  new_variable_access->SetVariableRef(GetVariableRef());

  return new_variable_access;
}

DSResult DSVariableAccess::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSVariableAccess::Run(DSWriter *writer, DSType object_type,
                               DSCardinal what) const
{
  DSResult              result;
  DSVariableAccessElem *elem;

  switch(object_type)
  {
    case DS_VARIABLEACCESSELEM:
      for (elem = GetFirstElem();
           elem;
           elem = GetNextElem())
      {
        result = elem->Write(writer, what);
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
