#ifndef _DS_LIST_TMPL_H_
#define _DS_LIST_TMPL_H_

#include "DSObject.h"

/******************************************************************************
   Method:     DSList::DSList
   Purpose:    Konstruktor.
               Die internen Felder werden mit NULL initialisiert.
   In:         None.
   Out:        None.
   Sideffects: None.
 ******************************************************************************/
 
template<class T> DSList<T>::DSList(void)
{
}

/******************************************************************************
   Method:     DSList::~DSList
   Purpose:    Destruktor. Alle Listenelemente werden geloescht.
   In:         None.
   Out:        None.
   Sideffects: Der Speicher fuer die Elemente wird dealloziert. Referenzen auf
               Listenelemente sind nacher ungueltig.
 ******************************************************************************/
 
template <class T> DSList<T>::~DSList(void)
{ 
}

template <class T>
DSBaseListElem<T> *DSList<T>::NewElem(T *new_data) const
{
  return new DSListElem<T>(new_data);
}


/******************************************************************************
   Method:     DSList::Clone(DSObject *)
   Purpose:    Erzeugt identische Kopie dieser Liste.
   In:         Parent Object for Elements.
   Out:        Zeiger auf die Kopie.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSList<T> *DSList<T>::Clone(DSObject *father) const
{
  DSList<T> *orig_list = (DSList<T> *)this;
  DSList<T> *new_list;
  DSResult   status;
  T         *clone_elem;

  new_list = new DSList<T>;
  assert(new_list);

  status = orig_list->MoveFirst();               // An Listenanfang.
  
  while (status == DS_OK)                        // Nicht Listenende...
  {
    clone_elem = (T *)orig_list->GetCurrentData()->Clone(); // father NICHT
                                                 // uebergeben!!!
    assert(clone_elem);

    if (father)
    {
      ((DSObject *)clone_elem)->SetParent(father);
    }
    new_list->Append(clone_elem);
    status = orig_list->MoveNext();
  }

  return new_list;
}

/******************************************************************************
   Method:     DSList::Split(void)
   Purpose:    Teilt die Liste in zwei Teile. Erstes Element der zweiten
               Liste wird das aktuelle Element der Ausgangsliste.
   In:         None.
   Out:        Zeiger auf Restliste.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSList<T> *DSList<T>::Split(void)
{
  DSList<T> *new_list;
  DSResult   status;
  DSCardinal counter;

  new_list = new DSList<T>;
  assert(new_list);

  if (!this->current_element_ptr)
  {
    return new_list;  // empty list results in 2 empty lists!
  }

  new_list->first_element_ptr = this->current_element_ptr;
  new_list->last_element_ptr = this->last_element_ptr;
  new_list->current_element_ptr = this->current_element_ptr;

  if (this->current_element_ptr->previous_element_ptr)
  {
    this->current_element_ptr->previous_element_ptr->next_element_ptr = NULL;
    this->last_element_ptr = this->current_element_ptr->previous_element_ptr;
    this->current_element_ptr->previous_element_ptr = NULL;
  }
  else // cut all! (orig list becomes empty!)
  {
    this->first_element_ptr = NULL;
    this->last_element_ptr = NULL;
    this->current_element_ptr = NULL;
  }

  // Recalculation of number_of_elements:
  counter = 0;
  for (status = new_list->MoveFirst();
       status == DS_OK;
       status = new_list->MoveNext())
  {
    counter++;
  }
  new_list->number_of_elements = counter;

  this->number_of_elements = this->number_of_elements - counter;

  return new_list;
}

#endif
