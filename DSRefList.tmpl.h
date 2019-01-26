#ifndef _DS_REFLIST_TMPL_H_
#define _DS_REFLIST_TMPL_H_

template<class T> DSRefList<T>::DSRefList(void)
{
}

template<class T> DSRefList<T>::~DSRefList(void)
{
}

template <class T>
DSBaseListElem<T> *DSRefList<T>::NewElem(T *new_data) const
{
  return new DSRefListElem<T>(new_data);
}

template <class T>
DSRefList<T> *DSRefList<T>::Clone(DSObject *father) const
{
  DSRefList<T> *orig_list = (DSRefList<T> *)this;
  DSRefList<T> *new_list;
  DSResult      status;

  (void)father;

  new_list = new DSRefList<T>;
  assert(new_list);

  status = orig_list->MoveFirst();               // An Listenanfang.
  
  while (status == DS_OK)                        // Nicht Listenende...
  {
    new_list->Append(this->GetCurrentData());    // hier Data NICHT clonen!
    status = orig_list->MoveNext();
  }

  return new_list;
}

/******************************************************************************
   Method:     DSRefList::Split(void)
   Purpose:    Teilt die Liste in zwei Teile. Erstes Element der zweiten
               Liste wird das aktuelle Element der Ausgangsliste.
   In:         None.
   Out:        Zeiger auf Restliste.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSRefList<T> * DSRefList<T>::Split(void)
{
  DSRefList<T> * new_list;
  DSResult       status;
  DSCardinal     counter;

  new_list = new DSRefList<T>;
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
