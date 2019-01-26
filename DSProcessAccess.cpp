/****************************************************************************
 *                 Modul: $RCSfile: DSProcessAccess.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/12 11:52:37 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          eines SDL-Processnzugriffs.
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

#include "DSProcessAccess.h"
#include "DSOperandProcessAccess.h"
#include "DSExpression.h"
#include "DSVariableAccess.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Processn
 ****************************************************************************/

/****************************************************************************
 * Globale Processn
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSProcessAccess::DSProcessAccess(DSObject *father,
                                 DSProcessRef  p_ref,  // Referenz auf Prozess
                                 DSExpression* p_id,   // Identifizierungsnummer
                                 DSVariableAccess *v_access): // Referenz auf Variable
  DSObject(DS_PROCESSACCESS, father),
  process_ref(p_ref),
  pid(p_id),
  variable_access(v_access),
  sensor_ref(NULL)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_OPERAND:
        if (((DSOperand*)father)->GetTag() == DS_OPN_PROCESS_ACCESS)
        {
          ((DSOperandProcessAccess *)father)->SetProcessAccess(this);
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

DSProcessAccess::DSProcessAccess(DSObject *father,
                                 DSProcessRef  p_ref,  // Referenz auf Prozess
                                 DSExpression* p_id,   // Identifizierungsnummer
                                 DSSensorRef   s_ref): // Referenz auf Sensor
  DSObject(DS_PROCESSACCESS, father),
  process_ref(p_ref),
  pid(p_id),
  variable_access(NULL),
  sensor_ref(s_ref)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_OPERAND:
        if (((DSOperand*)father)->GetTag() == DS_OPN_PROCESS_ACCESS)
        {
          ((DSOperandProcessAccess *)father)->SetProcessAccess(this);
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

DSProcessAccess::~DSProcessAccess(void)
{
  if (pid) delete pid;
  if (variable_access) delete variable_access;
}

DSObject *DSProcessAccess::New(DSObject *father) const
{
  return new DSProcessAccess(father);
}

/****************************************************************************
 * GetProcessRef(): Liefert die Process zurueck, auf die zugegriffen wird.
 *                   Ergebnis: Referenz auf Process
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSProcessRef DSProcessAccess::GetProcessRef(void) const
{
  return process_ref;
}

DSVariableAccess * DSProcessAccess::GetVariableAccess(void) const
{
  return variable_access;
}

DSSensorRef DSProcessAccess::GetSensorRef(void) const
{
  return sensor_ref;
}

DSExpression * DSProcessAccess::GetProcessID(void) const
{
  return pid;
}


/****************************************************************************
 * SetProcessRef(): Speichert den uebergebenen Wert
 *                   -> process: Wert vom DSProcessRef
 *                   Ergebnis: DS_OK
 *                   Seiteneffekte: keine
 ****************************************************************************/

DSResult DSProcessAccess::SetProcessRef(DSProcessRef p_ref)
{
  process_ref = p_ref;

  return DS_OK;
}

DSResult DSProcessAccess::SetVariableAccess(DSVariableAccess *v_access)
{
  if (variable_access == v_access) return DS_OK;

  if (variable_access) delete variable_access;
  variable_access = v_access;

  if (variable_access != NULL)
  {
    if (variable_access->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      variable_access->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSProcessAccess::SetSensorRef(DSSensorRef s_ref)
{
  sensor_ref = s_ref;

  return DS_OK;
}

DSResult DSProcessAccess::SetProcessID(DSExpression *p_id)
{
  if (p_id == pid) return DS_OK;

  if (pid) delete pid;
  pid = p_id;

  if (pid != NULL)
  {
    if (pid->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      pid->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSProcessAccess::Clone(DSObject *father, DSObject *fill_this) const
{
  DSProcessAccess *new_process_access;

  if (fill_this == NULL)
  {
    new_process_access = (DSProcessAccess *)New(father);  // virtueller Konstruktor
    assert(new_process_access);
  }
  else
  {
    assert(fill_this->GetType() == DS_PROCESSACCESS);
    new_process_access = (DSProcessAccess *)fill_this;
  }

  new_process_access->SetProcessRef(GetProcessRef());

  if (GetVariableAccess())
  {
    new_process_access->SetVariableAccess((DSVariableAccess *)GetVariableAccess()->Clone((DSObject *)new_process_access));
  }

  new_process_access->SetSensorRef(GetSensorRef());

  return new_process_access;
}

DSResult DSProcessAccess::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSProcessAccess::Run(DSWriter *writer,
                              DSType object_type,
                              DSCardinal what) const
{
  (void)what;
  (void)writer;
  (void)object_type;

  return DS_OK;
}
