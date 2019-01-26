#ifndef _DS_LISTELEM_TMPL_H_
#define _DS_LISTELEM_TMPL_H_

/******************************************************************************
   Method:     DSListElem::DSListElem
   Purpose:    Konstruktor.
               Die internen Felder werden mit den Vorgabewerten belegt.
   In:         Zeiger auf Datensatz vom Typ T*,
               Zeiger auf Nachfolgerelement vom Typ DSListElem<T>*,
               Zeiger auf Vorgaengerelement vom Typ DSListElem<T>*.
   Out:        None.
   Sideffects: None.
 ******************************************************************************/
 
template <class T>
DSListElem<T>::DSListElem(T             *init_data,
                          DSListElem<T> *init_next_ptr,
                          DSListElem<T> *init_prev_ptr) :
  DSBaseListElem<T>(init_data,
                    init_next_ptr,
                    init_prev_ptr)
{
}

/******************************************************************************
   Method:     DSListElem::~DSListElem
   Purpose:    Destruktor.
   In:         None.
   Out:        None.
   Sideffects: Dealloziert Speicher fuer data.
 ******************************************************************************/
 
template <class T>
DSListElem<T>::~DSListElem(void)
{
  if (this->data)
  {
    delete this->data;
    this->data = NULL;
  }
}

#endif
