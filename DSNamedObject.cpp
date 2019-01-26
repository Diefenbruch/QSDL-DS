/****************************************************************************
 *                 Modul: $RCSfile: DSNamedObject.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/10/22 16:09:53 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul implementiert die Basisklasse aller anderen
 *          Klassen der Datenstruktur
 *
 * Funktionen: GetName(): Liefert den Namen
 *             SetName(): Setzt den Namen
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

#include "DSNamedObject.h"
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

DSNamedObject::DSNamedObject(DSType object_type,
                             DSString *n,
                             DSObject *father):
  DSObject(object_type, father),
  name(n)
{
  if (name)
  {
    if (name->GetParent() == NULL)
    {
      name->SetParent(this);
    }
  }
}

DSNamedObject::DSNamedObject(DSType object_type,
                             DSString &n,
                             DSObject *father):
  DSObject(object_type, father),
  name(&n)
{
  if (name)
  {
    if (name->GetParent() == NULL)
    {
      name->SetParent(this);
    }
  }
}

DSNamedObject::DSNamedObject(DSType object_type,
                             const char *n,
                             DSObject *father):
  DSObject(object_type, father)
{
  if (n)
  {
    name = new DSString(this, n);
    assert(name);
  }
  else
  {
    name = NULL;
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSNamedObject::~DSNamedObject(void)
{
  if (name) delete name;
}

/****************************************************************************
 * GetName(): Liefert den Zeiger auf den Namen zurueck
 *            Ergebnis: Zeiger auf einen String
 *            Seiteneffekte: keine
 ****************************************************************************/

DSString* DSNamedObject::GetName(void) const
{
  return name;
}

/****************************************************************************
 * GetIdentifier(): Liefert kompletten Identifizierer, wird vom Codegenerator
 *                  fuer einige Klassen redefiniert.
 *                  Ergebnis: Zeiger auf einen String
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSString & DSNamedObject::GetIdentifier(void) const
{
  assert(GetName());
  
  return *GetName();
}

/****************************************************************************
 * SetName(): Speichert den uebergebenen Zeiger
 *            -> list_name: Zeiger auf einen String
 *            Ergebnis: DS_OK
 *            Seiteneffekte: keine
 ****************************************************************************/

DSResult DSNamedObject::SetName(DSString *new_name)
{
  if (name == new_name) return DS_OK;

  if (name) delete name;
  name = new_name;

  if (name)
  {
    if (name->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      name->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSNamedObject::SetName(DSString &new_name)
{
  if (name == &new_name) return DS_OK;

  if (name) delete name;
  name = &new_name;

  if (name->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    name->SetParent(this);
  }
  return DS_OK;
}

DSResult DSNamedObject::SetName(const char *new_name)
{
  if (name) delete name;
  name = new DSString(this, new_name);
  assert(name);

  return DS_OK;
}

DSObject *DSNamedObject::Clone(DSObject *father, DSObject *fill_this) const
{
  DSNamedObject *new_named_object;

  if (fill_this == NULL)
  {
    new_named_object = (DSNamedObject *)New(father);
    assert(new_named_object);
  }
  else
  {
    new_named_object = (DSNamedObject *)fill_this;
  }

  new_named_object->SetName(GetName()->GetString());

  return new_named_object;
}
