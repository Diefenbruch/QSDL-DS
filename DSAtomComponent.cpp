/****************************************************************************
 *                 Modul: $RCSfile: DSAtomComponent.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.2 $
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Bloecke
 *            definiert werden koennen.
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

#include <stdio.h>

#include "DSAtomComponent.h"
#include "DSAtom.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Atomn
 ****************************************************************************/

/****************************************************************************
 * Globale Atomn
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSAtomComponent::DSAtomComponent(DSObject *father) :
  parent(father)
{
  atom_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSAtomComponent::~DSAtomComponent(void)
{
  if (atom_definition_list) delete atom_definition_list;
}

DSAtomKeyList* DSAtomComponent::GetAtomList(void) const
{
  return atom_definition_list;
}

DSAtom *DSAtomComponent::GetAtom(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (atom_definition_list == NULL)
  {
    return NULL;
  }

  if (atom_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return atom_definition_list->GetCurrentData();
}

DSAtom *DSAtomComponent::GetAtom(DSString& n) const
{
  return GetAtom(&n);
}

DSAtom *DSAtomComponent::GetAtom(const char *n) const
{
  DSAtom *atom;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  atom = GetAtom(str);
  delete str;

  return atom;
}

DSAtom *DSAtomComponent::GetFirstAtom(void) const
{
  if (atom_definition_list == NULL)
  {
    return NULL;
  }

  if (atom_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return atom_definition_list->GetCurrentData();
}

DSAtom *DSAtomComponent::GetNextAtom(void) const
{
  if (atom_definition_list == NULL)
  {
    return NULL;
  }

  if (atom_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return atom_definition_list->GetCurrentData();
}

DSResult DSAtomComponent::SetAtomList(DSAtomKeyList *list)
{
  if (atom_definition_list == list) return DS_OK;

  if (atom_definition_list) delete atom_definition_list;
  atom_definition_list = list;
  return DS_OK;
}

DSResult DSAtomComponent::InsertAtom(DSAtom* atom)
{
  assert(atom != NULL);
  assert(atom->GetName() != NULL);

  if (atom_definition_list == NULL)
  {
    atom_definition_list = new DSAtomKeyList;
    assert(atom_definition_list != NULL);
  }

  if (atom->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    atom->SetParent(this->parent);
  }

  return atom_definition_list->Append(atom, new DSString(*atom->GetName()));
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSAtomComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSAtomComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
