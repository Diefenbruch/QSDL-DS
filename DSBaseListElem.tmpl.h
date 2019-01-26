#ifndef _DS_BASELISTELEM_TMPL_H_
#define _DS_BASELISTELEM_TMPL_H_

/******************************************************************************
   Method:     DSBaseListElem::DSBaseListElem
   Purpose:    Konstruktor.
               Die internen Felder werden mit den Vorgabewerten belegt.
   In:         Zeiger auf Datensatz vom Typ T*,
               Zeiger auf Nachfolgerelement vom Typ DSBaseListElem<T>*,
               Zeiger auf Vorgaengerelement vom Typ DSBaseListElem<T>*.
   Out:        None.
   Sideffects: None.
 ******************************************************************************/
 
template <class T>
DSBaseListElem<T>::DSBaseListElem(T *                 init_data,
                                  DSBaseListElem<T> * init_next_ptr,
                                  DSBaseListElem<T> * init_prev_ptr) :
  next_element_ptr(init_next_ptr),
  previous_element_ptr(init_prev_ptr),
  data(init_data)
{
  // data = NULL is possible in some cases!
}

/******************************************************************************
   Method:     DSBaseListElem::~DSBaseListElem
   Purpose:    Destruktor.
   In:         None.
   Out:        None.
   Sideffects: Dealloziert Speicher fuer data.
 ******************************************************************************/
 
template <class T>
DSBaseListElem<T>::~DSBaseListElem(void)
{
}

#endif
