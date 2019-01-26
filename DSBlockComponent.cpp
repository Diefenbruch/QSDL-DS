/****************************************************************************
 *                 Modul: $RCSfile: DSBlockComponent.cpp,v $
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

#include "DSBlockComponent.h"
#include "DSBlock.h"
#include "DSString.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Blockn
 ****************************************************************************/

/****************************************************************************
 * Globale Blockn
 ****************************************************************************/
 
/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSBlockComponent::DSBlockComponent(DSObject *father) :
  parent(father)
{
  block_definition_list = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSBlockComponent::~DSBlockComponent(void)
{
  if (block_definition_list) delete block_definition_list;
}

DSBlockKeyList* DSBlockComponent::GetBlockList(void) const
{
  return block_definition_list;
}

DSBlock *DSBlockComponent::GetBlock(DSString* n) const
{
  if (n == NULL)
  {
    return NULL;
  }

  if (block_definition_list == NULL)
  {
    return NULL;
  }

  if (block_definition_list->GotoKeyElement(n) != DS_OK)
  {
    return NULL;
  }
  return block_definition_list->GetCurrentData();
}

DSBlock *DSBlockComponent::GetBlock(DSString& n) const
{
  return GetBlock(&n);
}

DSBlock *DSBlockComponent::GetBlock(const char *n) const
{
  DSBlock *block;
  DSString *str;

  assert(n);
  str = new DSString(n);
  assert(str);
  block = GetBlock(str);
  delete str;

  return block;
}

DSBlock *DSBlockComponent::GetFirstBlock(void) const
{
  if (block_definition_list == NULL)
  {
    return NULL;
  }

  if (block_definition_list->MoveFirst() != DS_OK)
  {
    return NULL;
  }
  return block_definition_list->GetCurrentData();
}

DSBlock *DSBlockComponent::GetNextBlock(void) const
{
  if (block_definition_list == NULL)
  {
    return NULL;
  }

  if (block_definition_list->MoveNext() != DS_OK)
  {
    return NULL;
  }
  return block_definition_list->GetCurrentData();
}

DSResult DSBlockComponent::SetBlockList(DSBlockKeyList *list)
{
  if (block_definition_list == list) return DS_OK;

  if (block_definition_list) delete block_definition_list;
  block_definition_list = list;
  return DS_OK;
}

DSResult DSBlockComponent::InsertBlock(DSBlock* block, DSBoolean tail)
{
  assert(block != NULL);
  assert(block->GetName() != NULL);

  if (block_definition_list == NULL)
  {
    block_definition_list = new DSBlockKeyList;
    assert(block_definition_list != NULL);
  }

  if (block->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    block->SetParent(this->parent);
  }

  if (tail)
  {
    return block_definition_list->Append(block, new DSString(*block->GetName()));
  }
  else
  {
    return block_definition_list->Prepend(block, new DSString(*block->GetName()));
  }
}

/****************************************************************************
 * GetParent(): Liefert das Vaterobjekt des Objekts
 *              Ergebnis: Zeiger auf DSObject
 *              Seiteneffekte: keine
 ****************************************************************************/

DSObject* DSBlockComponent::GetComponentParent(void) const
{
  return parent;
}

DSResult DSBlockComponent::SetComponentParent(const DSObject *par)
{
  parent = (DSObject *)par;
  return DS_OK;
}
