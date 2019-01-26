/****************************************************************************
 *                 Modul: $RCSfile: DSTask.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $

 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Parameter, die in Verbindung mit einem Task-Befehl
 *          angegeben sind
 *
 * Funktionen: GetVariableAccess(): Gibt den Variablenzugriff links
 *                                  der Zuweisung zurueck
 *             GetExpression() : Liefert den Zeiger auf die Anweisung
 *             SetVariableAccess(): Speichert den uebergebenen Variablenzeiger
 *             SetExpression() : Speichert den uebergebenen Zeiger
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

#include "DSTask.h"
#include "DSExpression.h"
#include "DSString.h"
#include "DSVariableAccess.h"

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

DSTask::DSTask(DSObject         *father,
               DSString         *label_name, 
               DSVariableAccess *access, 
               DSExpression     *expr) :
  DSAction (father, DS_TASK, label_name),
  variable_access(access), 
  expression(expr)
{
  informal_text = NULL;
  if (expression)
  {
    if (expression->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      expression->SetParent(this);
    }
  }
}

DSTask::DSTask(DSObject         *father,
               DSString&         label_name, 
               DSVariableAccess *access, 
               DSExpression     *expr) :
  DSAction (father, DS_TASK, &label_name),
  variable_access(access), 
  expression(expr)
{
  informal_text = NULL;
  if (expression)
  {
    if (expression->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      expression->SetParent(this);
    }
  }
}

DSTask::DSTask(DSObject         *father,
               const char       *label_name, 
               DSVariableAccess *access, 
               DSExpression     *expr) :
  DSAction (father, DS_TASK, label_name),
  variable_access(access), 
  expression(expr)
{
  informal_text = NULL;
  if (expression)
  {
    if (expression->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      expression->SetParent(this);
    }
  }
}

DSTask::DSTask(DSObject *father,
               DSString     *label_name,
               DSString     *text) :
  DSAction (father, DS_TASK, label_name),
  informal_text(text)
{
  variable_access = NULL; 
  expression = NULL;
}

DSTask::DSTask(DSObject *father,
               DSString& label_name,
               DSString& text) :
  DSAction (father, DS_TASK, &label_name),
  informal_text(&text)
{
  variable_access = NULL; 
  expression = NULL;
}

DSTask::DSTask(DSObject     *father,
               const char   *label_name, 
               const char   *text) : 
  DSAction (father, DS_TASK, label_name)
{
  informal_text = new DSString(text);
  assert(informal_text);
  variable_access = NULL; 
  expression = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSTask::~DSTask(void)
{
  if (expression) delete expression;
  if (informal_text) delete informal_text;
  if (variable_access) delete variable_access;
}

/****************************************************************************
 * GetInformalText(): Liefert Zeiger auf den informellen Text des Tasks
 *                    Ergebnis: Zeiger auf einen String
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSString* DSTask::GetInformalText(void) const
{
  return informal_text;
}

/****************************************************************************
 * GetVariableAccess():  Liefert Zeiger auf die Ergebnisvariable
 *                    Ergebnis: Zeiger auf eine Variable
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSVariableAccess* DSTask::GetVariableAccess(void) const
{
  return variable_access;
}

/****************************************************************************
 * GetExpression(): Liefert Zeiger auf die Expression zurueck
 *                  Ergebnis: Zeiger auf einen Ausdruck (DSExpression)
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSExpression* DSTask::GetExpression(void) const
{
  return expression;
}

/****************************************************************************
 * SetInformalText(): Speichert den uebergebenen Zeiger
 *                    -> text : Zeiger auf einen String
 *                    Ergebnis: DS_OK
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSResult DSTask::SetInformalText(DSString *text)
{
  if (informal_text == text) return DS_OK;

  if (informal_text) delete informal_text;
  informal_text = text;

  if (informal_text != NULL)
  {
    if (informal_text->GetParent() == NULL)
    {
      informal_text->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSTask::SetInformalText(DSString &text)
{
  if (informal_text == &text) return DS_OK;

  if (informal_text) delete informal_text;
  informal_text = &text;

  if (informal_text->GetParent() == NULL)
  {
    informal_text->SetParent(this);
  }

  return DS_OK;
}

DSResult DSTask::SetInformalText(const char *text)
{
  if (informal_text) delete informal_text;
  informal_text = new DSString(this, text);
  assert(informal_text);

  return DS_OK;
}

/****************************************************************************
 * SetVariableAccess(): Speichert die linke Seite einer Zuweisung.
 *                      -> access : Zeiger auf eine Variablenzugriff
 *                      Ergebnis: DS_OK
 *                      Seiteneffekte: keine
 ****************************************************************************/

DSResult DSTask::SetVariableAccess(DSVariableAccess *access)
{
  if (variable_access == access) return DS_OK;

  if (variable_access) delete variable_access;
  variable_access = access;

  if (variable_access != NULL)
  {
    if (variable_access->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      variable_access->SetParent(this);
    }
  }

  return DS_OK;
}

/****************************************************************************
 * SetExpression(): Speichert den uebergebenen Zeiger
 *                  -> exp: Zeiger auf eine Expression
 *                  Ergebnis: DS_OK
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSResult DSTask::SetExpression(DSExpression* exp)
{
  if (exp == expression) return DS_OK;

  if (expression) delete expression;
  expression = exp;

  if (expression != NULL)
  {
    if (expression->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      expression->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSTask::Clone(DSObject *father, DSObject *fill_this) const
{
  DSTask *new_task;

  if (fill_this == NULL)
  {
    new_task = (DSTask *)New(father);
    assert(new_task);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_task = (DSTask *)fill_this;
  }

  // Basisklassen clonen:
  DSAction::Clone(father, new_task);

  if (GetVariableAccess())
  {
    new_task->SetVariableAccess((DSVariableAccess *)GetVariableAccess()->Clone((DSObject *)new_task));
  }

  if (GetExpression())
  {
    new_task->SetExpression((DSExpression *)GetExpression()->Clone((DSObject *)new_task));
  }

  if (GetInformalText())
  {
    new_task->SetInformalText((DSString *)GetInformalText()->Clone((DSObject *)new_task));
  }

  return new_task;
}

DSResult DSTask::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (variable_access) variable_access->Write(writer, what);
  if (expression) expression->Write(writer, what);
  if (informal_text) informal_text->Write(writer, what);

  return DS_OK;
}
