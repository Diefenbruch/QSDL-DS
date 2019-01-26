/****************************************************************************
 *                 Modul: $RCSfile: DSAction.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul stellt die Datenstruktur fuer den Aufbau des 
 *          Instruktionsbaums bereit. Er speichert selbst Objekte der 
 *          Instruktionstypen STOP und RETURN und dient als Basisklasse
 *          fuer Instruktionstypen mit Parametern
 *
 * Funktionen: GetLabel(): liefert den Typ der Instruktion
 *             SetLabel(): speichert den Namen der Instruktion
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

#include "DSAction.h"
#include "DSTransition.h"  // wegen parent
#include "DSOperand.h"
#include "DSOperandProcedureCall.h"
#include "DSString.h"
#include <iostream>

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

DSAction::DSAction(DSObject   *father,
                   DSActionTag t,
                   DSString   *l) :
  DSObject(DS_ACTION, father),
  tag(t), 
  label(l)
{
  DSOperand *operand;

  if (father)
  {
    switch(father->GetType())
    {
      case DS_TRANSITION:
        ((DSTransition*)father)->InsertAction(this);
        break;
      case DS_OPERAND:
        operand = (DSOperand*)father;
        if (GetTag() != DS_CALL ||
            operand->GetTag() != DS_OPN_PROCEDURE_CALL)
        {
          std::cerr << "Illegal parent for action.\n";
          assert(DS_FALSE);
        }
        ((DSOperandProcedureCall*)operand)->SetProcedureCall((DSCall *)this);
        break;
      default:
        std::cerr << "Illegal parent for action.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

DSAction::DSAction(DSObject   *father,
                   DSActionTag t,
                   DSString&   l) :
  DSObject(DS_ACTION, father),
  tag(t), 
  label(&l)
{
  DSOperand *operand;

  if (father)
  {
    switch(father->GetType())
    {
      case DS_TRANSITION:
        ((DSTransition*)father)->InsertAction(this);
        break;
      case DS_OPERAND:
        operand = (DSOperand*)father;
        if (GetTag() != DS_CALL ||
            operand->GetTag() != DS_OPN_PROCEDURE_CALL)
        {
          std::cerr << "Illegal parent for action.\n";
          assert(DS_FALSE);
        }
        ((DSOperandProcedureCall*)operand)->SetProcedureCall((DSCall *)this);
        break;
      default:
        std::cerr << "Illegal parent for action.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

DSAction::DSAction(DSObject   *father,
                   DSActionTag t,
                   const char *l) :
  DSObject(DS_ACTION, father),
  tag(t)
{
  DSOperand *operand;

  if (l)
  {
    label = new DSString(l);
    assert(label);
  }
  else
  {
    label = NULL;
  }

  if (father)
  {
    switch(father->GetType())
    {
      case DS_TRANSITION:
        ((DSTransition*)father)->InsertAction(this);
        break;
      case DS_OPERAND:
        operand = (DSOperand*)father;
        if (GetTag() != DS_CALL ||
            operand->GetTag() != DS_OPN_PROCEDURE_CALL)
        {
          std::cerr << "Illegal parent for action.\n";
          assert(DS_FALSE);
        }
        ((DSOperandProcedureCall*)operand)->SetProcedureCall((DSCall *)this);
        break;
      default:
        std::cerr << "Illegal parent for action.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSAction::~DSAction(void)
{
  if (label) delete label;
}

/****************************************************************************
 * GetLabel: liefert den Zeiger auf den Namen der Instruktion
 *           Ergebnis: Zeiger auf den Namen
 *           Seiteneffekte: keine
 ****************************************************************************/

DSString* DSAction::GetLabel(void) const
{
  return label;
}

/****************************************************************************
 * GetActionTag: liefert den Typ der Instruction zurueck
 *                        Ergebnis: Aufzaehlungstyp
 *                        Seiteneffekte: keine
 ****************************************************************************/

DSActionTag DSAction::GetTag(void) const
{
  return tag;
}

/****************************************************************************
 * SetLabel: speichert den Zeiger auf den Namen der Instruction
 *           Ergebnis: DS_OK
 *           Seiteneffekte: keine
 ****************************************************************************/
 
DSResult DSAction::SetLabel(DSString *l)
{
  if (label == l) return DS_OK;

  if (label) delete label;
  label = l;

  if (label != NULL)
  {
    if (label->GetParent() == NULL)
    {
      label->SetParent(this);
    }
  }

  return DS_OK;
}

/****************************************************************************
 * SetActionTag: speichert Typ der Instruction
 *                        Ergebnis: DS_OK
 *                        Seiteneffekte: keine
 ****************************************************************************/
 
DSResult DSAction::SetTag(DSActionTag t)
{
  tag = t;
  return DS_OK;
}

DSObject *DSAction::Clone(DSObject *father, DSObject *fill_this) const
{
  DSAction *new_action;

  if (fill_this == NULL)
  {
    new_action = (DSAction *)New(father);
    assert(new_action);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_action = (DSAction *)fill_this;
  }

  if (GetLabel())
  {
    new_action->SetLabel((DSString *)GetLabel()->Clone((DSObject *)new_action));
  }

  return new_action;
}

DSResult DSAction::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (label) label->Write(writer, what);

  return DS_OK;
}
