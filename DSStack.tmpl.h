/******************************************************************************
 *  Modul: $RCSfile: DSStack.tmpl.h,v $
 *
 *  $Author: md $
 *  $Date: 1998/01/13 12:48:22 $
 *  $Revision: 1.1 $
 *
 *  Aufgabe:
 *    Dieser Modul stellt Klassen fuer die Handhabung von Stacks
 *    bereit. 
 *
 *  Klassen:
 ******************************************************************************/

#ifndef _DS_STACK_TMPL_H_
#define _DS_STACK_TMPL_H_

#include "DSBaseList.h"

/******************************************************************************
   Method:     DSStack::DSStack
   Purpose:    Konstruktor.
               Die internen Felder werden mit NULL initialisiert.
   In:         None.
   Out:        None.
   Sideffects: None.
 ******************************************************************************/

template<class T> DSStack<T>::DSStack(void):
  DSRefList<T>()                        /* Konstruktor der Basisklasse
                                           aufrufen. */
{
}

/******************************************************************************
   Method:     DSStack::~DSStack
   Purpose:    Destruktor.
               Alle Listenelemente werden geloescht.
   In:         None.
   Out:        None.
   Sideffects: Der Speicher fuer die Listenelemente wird freigegeben.
 ******************************************************************************/

template<class T> DSStack<T>::~DSStack(void)
{
}

template<class T> DSResult DSStack<T>::Push(T *new_elem)
{
  this->Prepend(new_elem);
  return DS_OK;
}

template<class T> DSResult DSStack<T>::Push(T &new_elem)
{
  this->Prepend(new_elem);
  return DS_OK;
}

template <class T> T* DSStack<T>::Pop(void)
{
  T *data;

  if (this->MoveFirst() != DS_OK)
  {
    return NULL;
  }

  data = this->GetCurrentData();
  assert(data);

  // nur das Listenelement nicht der Inhalt
  // wird geloescht:
  assert(this->DeleteElement() == DS_OK);

  return data;
}

template <class T> T* DSStack<T>::Top(void)
{
  T *data;

  if (this->MoveFirst() != DS_OK)
  {
    return NULL;
  }

  data = this->GetCurrentData();
  assert(data);

  return data;
}

#endif
