#ifndef _DS_REFLISTELEM_TMPL_H_
#define _DS_REFLISTELEM_TMPL_H_

/******************************************************************************
   Method:     DSRefListElem::DSRefListElem
   Purpose:    Konstruktor.
               Die internen Felder werden mit den Vorgabewerten belegt.
   In:         Zeiger auf Datensatz vom Typ T*,
               Zeiger auf Nachfolgerelement vom Typ DSListElem<T>*,
               Zeiger auf Vorgaengerelement vom Typ DSListElem<T>*.
   Out:        None.
   Sideffects: None.
 ******************************************************************************/
 
template <class T>
DSRefListElem<T>::DSRefListElem(T                *init_data,
                                DSRefListElem<T> *init_next_ptr,
                                DSRefListElem<T> *init_prev_ptr) :
  DSBaseListElem<T>(init_data,
                    init_next_ptr,
                    init_prev_ptr)
{
}

/******************************************************************************
   Method:     DSRefListElem::~DSRefListElem
   Purpose:    Destruktor.
   In:         None.
   Out:        None.
   Sideffects: Dealloziert Speicher fuer data.
 ******************************************************************************/
 
template <class T>
DSRefListElem<T>::~DSRefListElem(void)
{
}

#endif
