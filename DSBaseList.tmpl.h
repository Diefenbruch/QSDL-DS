#ifndef _DS_BASELIST_TMPL_H_
#define _DS_BASELIST_TMPL_H_

/******************************************************************************
   Method:     DSBaseList::DSBaseList
   Purpose:    Konstruktor.
               Die internen Felder werden mit NULL initialisiert.
   In:         None.
   Out:        None.
   Sideffects: None.
 ******************************************************************************/
 
template<class T> DSBaseList<T>::DSBaseList(void) :
  first_element_ptr(NULL),
  last_element_ptr(NULL),
  current_element_ptr(NULL),
  save_element_ptr(NULL),
  number_of_elements(0)
{
}

/******************************************************************************
   Method:     DSBaseList::~DSBaseList
   Purpose:    Destruktor. Alle Listenelemente werden geloescht.
   In:         None.
   Out:        None.
   Sideffects: Der Speicher fuer die Elemente wird dealloziert. Referenzen auf
               Listenelemente sind nacher ungueltig.
 ******************************************************************************/
 
template <class T> DSBaseList<T>::~DSBaseList(void)
{ 
  if (number_of_elements > 0)                    // Liste nicht leer.
  {
    for (/* empty */;
         number_of_elements > 1;                 /* Sonderfall: Nur ein
                                                    Element in der Liste. */
         number_of_elements--)
    {
      assert(last_element_ptr);
      current_element_ptr = last_element_ptr->previous_element_ptr;
                                                 /* Auf vorletztes Element
                                                    setzen. */
      delete last_element_ptr;                   // Letztes Element loeschen.
      last_element_ptr = current_element_ptr;    /* current_element_ptr
                                                    zeigt jetzt auf letztes
                                                    Element. */
    }
  
    delete last_element_ptr;                     /* An diesem Punkt ist genau
                                                    ein Element in der Liste. */
    number_of_elements--;                        // Zaehler aktualisieren.
    assert(number_of_elements == 0);             /* Wenn nicht Null, dann
                                                    liegt ein Programm-
                                                    fehler vor, und assert
                                                    beendet das Programm. */
  }
}

/******************************************************************************
   Method:     DSBaseList::InsertAfter(T*)
   Purpose:    Neues Element hinter dem momentanen Element einfuegen. Das neue
               Element ist danach das momentane Element.
               Leere Elemente duerfen eingefuegt werden.
   In:         Zeiger auf Daten vom Typ T*.
   Out:        DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: Es wird Speicher fuer das neue Listenelement alloziert.
 ******************************************************************************/

template <class T>
DSResult DSBaseList<T>::InsertAfter(T* new_data_ptr)
{
  return xInsertAfter(NewElem(new_data_ptr));
                                                 /* Neues Element erzeugen
                                                    und einfuegen lassen.
                                                    Nur diese Zeile ist
                                                    typabhaengig, der Rest
                                                    bleibt immer gleich. */
}

#ifndef _MSC_VER

template <class T>
DSResult DSBaseList<T>::InsertAfter(T& new_data_ptr)
{
  return xInsertAfter(NewElem(&new_data_ptr));
                                                 /* Neues Element erzeugen
                                                    und einfuegen lassen.
                                                    Nur diese Zeile ist
                                                    typabhaengig, der Rest
                                                    bleibt immer gleich. */
}

#endif

/******************************************************************************
   Method:     DSBaseList::xInsertAfter(DSBaseListElem<T>*)
   Purpose:    Neues Element hinter dem momentanen Element einfuegen. Das neue
               Element ist danach das momentane Element.
   In:         Zeiger auf Listenelement vom Typ *DSBaseListElem<T>.
   Out:        boolescher Wert DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/
 
template <class T>
DSResult DSBaseList<T>::xInsertAfter(DSBaseListElem<T>* new_element_ptr)
{  
  assert(current_element_ptr != NULL);           /* Wenn NULL, dann gibt es
                                                    kein momentanes Element.
                                                    Der Aufruf von InsertBefore
                                                    ist dann ein Fehler. */
  if (current_element_ptr == last_element_ptr)   // Einfach anfuegen.
  {
    return xAppend(new_element_ptr);
  }
  else
  {
    assert (new_element_ptr != NULL);            // NULL-Zeiger uebergeben?
    current_element_ptr->next_element_ptr->previous_element_ptr = new_element_ptr;
    new_element_ptr->next_element_ptr = current_element_ptr->next_element_ptr;
    new_element_ptr->previous_element_ptr = current_element_ptr;
    current_element_ptr->next_element_ptr = new_element_ptr;
    current_element_ptr = new_element_ptr;
    number_of_elements++;
    return DS_OK;
  }
}

/******************************************************************************
   Method:     DSBaseList::InsertBefore(T*)
   Purpose:    Neues Element vor dem momentanen Element einfuegen. Das neue
               Element ist danach das momentane Element.
   In:         Zeiger auf Datensatz vom Typ T*.
   Out:        DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: Es wird Speicher fuer das neue Listenelement alloziert.
 ******************************************************************************/
 
template <class T>
DSResult DSBaseList<T>::InsertBefore(T* new_data_ptr)
{
  return xInsertBefore(NewElem(new_data_ptr));
}

#ifndef _MSC_VER

template <class T>
DSResult DSBaseList<T>::InsertBefore(T& new_data_ptr)
{
  return xInsertBefore(NewElem(&new_data_ptr));
}

#endif

/******************************************************************************
   Method:     DSBaseList::xInsertBefore(DSBaseListElem<T>*)
   Purpose:    Neues Element vor dem momentanen Element einfuegen. Das neue
               Element ist danach das momentane Element.
   In:         Zeiger auf Listenelement vom Typ DSBaseListElem<T>.
   Out:        DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/
 
template <class T>
DSResult DSBaseList<T>::xInsertBefore(DSBaseListElem<T> *new_element_ptr)
{
  assert(current_element_ptr != NULL);           // Wenn NULL, dann gibt es
                                                 // kein momentanes Element.
                                                 // Der Aufruf von InsertBefore
                                                 // ist dann ein Fehler.
  if (current_element_ptr == first_element_ptr)
  {
    return xPrepend(new_element_ptr);
  }
  else
  {
    assert (new_element_ptr != NULL);            // NULL-Zeiger uebergeben?
    current_element_ptr->previous_element_ptr->next_element_ptr
      = new_element_ptr;
    new_element_ptr->previous_element_ptr
      = current_element_ptr->previous_element_ptr;
    current_element_ptr->previous_element_ptr = new_element_ptr;
    new_element_ptr->next_element_ptr = current_element_ptr;
    current_element_ptr = new_element_ptr;
    
    number_of_elements++;
    return DS_OK;
  }
}

/******************************************************************************
   Method:     DSBaseList::Append(T*)
   Purpose:    Neues Element nach dem letzten Element einfuegen. Das neue
               Element ist danach das momentane Element.
   In:         Zeiger auf Datensatz vom Typ T*.
   Out:        DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: Es wird Speicher fuer den Datenteil alloziert.
 ******************************************************************************/

template <class T>
DSResult DSBaseList<T>::Append(T *new_data_ptr)
{
  return xAppend(NewElem(new_data_ptr));
}

#ifndef _MSC_VER

template <class T> DSResult DSBaseList<T>::Append(T& new_data_ptr)
{
  return xAppend(NewElem(&new_data_ptr));
}

#endif

/******************************************************************************
   Method:     DSBaseList::xAppend(DSBaseListElem<T>*)
   Purpose:    Neues Element nach dem letzten Element einfuegen. Das neue
               Element ist danach das momentane Element.
   In:         Zeiger auf Listenelement vom Typ DSBaseListElem<T>*.
   Out:        DS_OK, falls OK, sonst DS_ERROR.
   Sideffects: None.
 ******************************************************************************/
 
template <class T>
DSResult DSBaseList<T>::xAppend(DSBaseListElem<T>* new_element_ptr)
{
  assert(new_element_ptr != NULL);               // NULL-pointer uebergeben?
  if (number_of_elements == 0)                   // Liste leer.
  {
    first_element_ptr   =
    last_element_ptr    =
    current_element_ptr = new_element_ptr;       /* Alle drei Zeiger zeigen
                                                    auf das neue Element. */
  }
  else
  {
    last_element_ptr->next_element_ptr = new_element_ptr;
    new_element_ptr->previous_element_ptr = last_element_ptr;
    last_element_ptr = new_element_ptr;
  }
  number_of_elements++;
  return DS_OK;
}

/******************************************************************************
   Method:     DSBaseList::Prepend(T*)
   Purpose:    Neues Element vor dem ersten Element einfuegen. Das neue
               Element ist danach das momentane Element.
   In:         Zeiger auf Datensatz vom Typ T*.
   Out:        DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: Es wird Speicher fuer den Datenteil alloziert.
 ******************************************************************************/

template <class T>
DSResult DSBaseList<T>::Prepend(T *new_data_ptr)
{
  return xPrepend(NewElem(new_data_ptr));
}

#ifndef _MSC_VER

template <class T> DSResult DSBaseList<T>::Prepend(T& new_data_ptr)
{
  return xPrepend(NewElem(&new_data_ptr));
}

#endif

/******************************************************************************
   Method:     DSBaseList::xPrepend(DSBaseListElem<T>* new_element_ptr)
   Purpose:    Neues Element vor dem ersten Element einfuegen. Das neue
               Element ist danach das momentane Element.
   In:         Zeiger auf Listenelement vom Typ DSBaseListElem<T>*.
   Out:        DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSResult DSBaseList<T>::xPrepend(DSBaseListElem<T>* new_element_ptr)
{
  assert (new_element_ptr != NULL);          // NULL-pointer uebergeben?
  if (number_of_elements == 0)
  {
    first_element_ptr   =
    last_element_ptr    =
    current_element_ptr = new_element_ptr;   
  }
  else
  {
    first_element_ptr->previous_element_ptr = new_element_ptr;
    new_element_ptr->next_element_ptr = first_element_ptr;
    first_element_ptr = new_element_ptr;
  }
  number_of_elements++;
  return DS_OK;
}

/******************************************************************************
   Method:     DSBaseList::GotoElement
   Purpose:    Prueft, ob die Liste ein Element enthaelt, dessen Adresse
               mit *search_elem identisch ist. Wenn ja, ist das momentane Element
               das gesuchte Element. Ist das Element nicht in der Liste
               enthalten, terminiert die Funktion mit assert.
   In:         Zeiger auf Adresse eines Elements vom Typ T*.
   Out:        DS_TRUE, wenn gefunden, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSResult DSBaseList<T>::GotoElement(T *search_elem)
{
  DSResult status;

  assert(search_elem != NULL);                   // Schluessel leer?

  if (number_of_elements == 0)                   // Liste leer?
  {
    return DS_ERROR;                             // dann sofort raus...
  }

  assert(current_element_ptr != NULL);           // List kann nich leer sein

  status = MoveFirst();                          // An Listenanfang.
  
  while (status == DS_OK)                        // Nicht Listenende...
  {
    if (current_element_ptr->data == search_elem) // gefunden?
    {
      return DS_OK;
    }
    status = MoveNext();
  }
  return DS_ERROR;
}

#ifndef _MSC_VER

template <class T>
DSResult DSBaseList<T>::GotoElement(T& search_elem)
{
  return GotoElement(&search_elem);
}

#endif

/******************************************************************************
   Method:     DSBaseList::IsInList
   Purpose:    Prueft, ob die Liste ein Element enthaelt, dessen Adresse
               mit *search_elem identisch ist. Der Listenzustand wird nicht
               veraendert.
   In:         Zeiger auf Element vom Typ T*.
   Out:        DSResult TRUE, wenn gefunden, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSBoolean DSBaseList<T>::IsInList(T *search_elem)
{
  DSResult       status;
  DSBaseListElem<T> *temporary_ptr;

  temporary_ptr = current_element_ptr;            // Momentanes Element
                                                  // zwischenspeichern.
  status = GotoElement(search_elem);

  current_element_ptr = temporary_ptr;            // Urspruengl.
                                                  // momentanes Element
                                                  // wiederherstellen.
  if (status == DS_OK)
  {
    return DS_TRUE;
  }
  return DS_FALSE;
}

#ifndef _MSC_VER

template <class T> DSBoolean DSBaseList<T>::IsInList(T& search_elem)
{
  return IsInList(&search_elem);
}

#endif

/******************************************************************************
   Method:     DSBaseList::DeleteElement(void)
   Purpose:    Momentanes Element loeschen. Ist das momentane Element
               undefiniert, wird der Loeschversuch mit assert abgefangen.
   In:         None.
   Out:        boolescher Wert DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: Der Speicher fuer den Datenteil wird dealloziert. Nach dem
               Loeschen wird der Nachfolger des geloeschten Elements momentanes
               Element. Wird das letzte Element geloescht, ist das momentane
               Element undefiniert.
 ******************************************************************************/

template <class T> DSResult DSBaseList<T>::DeleteElement(void)
{
  DSBaseListElem<T> *temporary_ptr;
  
  assert(current_element_ptr != NULL);           /* Wenn NULL, dann gibt es
                                                    kein momentanes Element.
                                                    Der Aufruf von DeleteElement
                                                    ist dann ein Fehler. */
  if (number_of_elements == 1)                   // Sonderfall: Nur 1 Element da.
  {
    delete current_element_ptr;
    current_element_ptr =
    first_element_ptr   =
    last_element_ptr    = NULL;
    number_of_elements = 0;
    return DS_OK;
  }

  if (current_element_ptr == first_element_ptr)   // Erstes loeschen.
  {
    current_element_ptr = current_element_ptr->next_element_ptr;
    current_element_ptr->previous_element_ptr = NULL;
    delete first_element_ptr;
    first_element_ptr = current_element_ptr;
    number_of_elements--;
    return DS_OK;
  }

  if (current_element_ptr == last_element_ptr)    // Letztes loeschen.
  {
    last_element_ptr = last_element_ptr->previous_element_ptr;
    last_element_ptr->next_element_ptr = NULL;
    delete current_element_ptr;
    current_element_ptr = last_element_ptr;
    number_of_elements--;
    return DS_OK;
  }
                                                  /* Mehr als ein Element und
                                                     mitten in der Liste. */
  current_element_ptr->next_element_ptr->previous_element_ptr
      = current_element_ptr->previous_element_ptr;
  current_element_ptr->previous_element_ptr->next_element_ptr
      = current_element_ptr->next_element_ptr;
  temporary_ptr= current_element_ptr;
  current_element_ptr = current_element_ptr->next_element_ptr;
  delete temporary_ptr;
  number_of_elements--;
  return DS_OK;
}

/******************************************************************************
   Method:     DSBaseList::RemoveElement(void)
   Purpose:    Momentanes Element entnehmen. Ist das momentane Element
               undefiniert, wird die Entnahme mit assert abgefangen.
   In:         None.
   Out:        Data des momentanen Elements (T *)
   Sideffects: Der Speicher fuer das DSBaseListElem wird dealloziert. Nach dem
               Entnehmen wird der Nachfolger des entnommenen Elements momentanes
               Element. Wird das letzte Element entnommen, ist das momentane
               Element undefiniert.
 ******************************************************************************/

template <class T>
T *DSBaseList<T>::RemoveElement(void)
{
  T             *ret_value;

  assert(current_element_ptr != NULL);           /* Wenn NULL, dann gibt es
                                                    kein momentanes Element.
                                                    Der Aufruf von DeleteElement
                                                    ist dann ein Fehler. */

  ret_value = current_element_ptr->data;
  current_element_ptr->data = NULL;              /* notwendig damit beim an-
                                                    schliessenden Loeschen des
                                                    DSListElems der Datenteil
                                                    nicht zerstoert wird! */
  DeleteElement();                               /* Element entfernen und zer-
                                                    stoeren (aber nicht die Daten!!) */
  return ret_value;
}

/******************************************************************************
   Method:     DSBaseList::NumberOfElements(void)
   Purpose:    Gibt die Anzahl der Elemente in der Liste zurueck.
   In:         None.
   Out:        Anzahl der Elemente vom Typ cardinal.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSCardinal DSBaseList<T>::NumberOfElements(void) const
{
  return number_of_elements;
}

/******************************************************************************
   Method:     DSBaseList::IsEmpty(void)
   Purpose:    Gibt zurueck, ob die Liste leer ist.
   In:         None.
   Out:        DS_TRUE, falls Anzahl der Elemente 0 (zero) ist.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSBoolean DSBaseList<T>::IsEmpty(void) const
{
  return (number_of_elements == 0) ? DS_TRUE : DS_FALSE;
}

/******************************************************************************
   Method:     DSBaseList::NoCurrentElement(void)
   Purpose:    Ergibt DS_TRUE, wenn kein momentanes Element definiert ist.
   In:         None.
   Out:        DSResult DS_TRUE, wenn kein momentanes Element definiert ist,
               sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSBoolean DSBaseList<T>::NoCurrentElement(void) const
{
  return (current_element_ptr == NULL) ? DS_TRUE : DS_FALSE;
}

/******************************************************************************
   Method:     DSBaseList::GetCurrentData(void)
   Purpose:    Zeiger auf Datenteil des momentanen Elements zurueckgeben.
   In:         None.
   Out:        Zeiger auf Datenteil vom Typ T*.
   Sideffects: None.
 ******************************************************************************/

template <class T>
T * DSBaseList<T>::GetCurrentData(void) const
{
  assert(current_element_ptr != NULL);           /* Ende, wenn kein momentanes
                                                    Element. */
  return current_element_ptr->data;
}

/******************************************************************************
   Method:     DSBaseList::SetCurrentData(void)
   Purpose:    Zeiger auf Datenteil des momentanen Elements neu setzen.
   In:         Zeiger auf Datensatz vom Typ T*.
   Out:        DS_TRUE, wenn ales ok ist, sonst DS_FALSE.
   Sideffects: Bei Bedarf wird der alte Datenteil dealloziert.
 ******************************************************************************/

template <class T>
DSResult DSBaseList<T>::SetCurrentData(T *new_data_ptr)
{
  assert(current_element_ptr != NULL);           /* Ende, wenn kein momentanes
                                                    Element. */
  if (current_element_ptr->data != NULL)         // Datenteil nicht leer!
  {
    delete current_element_ptr->data;
  }
  current_element_ptr->data = new_data_ptr;
  return DS_OK;
}

#ifndef _MSC_VER

template <class T>
DSResult DSBaseList<T>::SetCurrentData(T& new_data_ptr)
{
  assert(current_element_ptr != NULL);           /* Ende, wenn kein momentanes
                                                    Element. */
  if (current_element_ptr->data != NULL)         // Datenteil nicht leer!
  {
    delete current_element_ptr->data;
  }
  current_element_ptr->data = &new_data_ptr;
  return DS_OK;
}

#endif

/******************************************************************************
   Method:     DSBaseList::MovePrevious(void)
   Purpose:    Aktuelles Element auf voriges Element setzen.
   In:         None.
   Out:        DSResult DS_TRUE, falls erfolgreich, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSResult DSBaseList<T>::MovePrevious(void) // const
{
  if (current_element_ptr == first_element_ptr)
  {
    return DS_ERROR;
  }
                                                 // AtStartOfList?
  assert (number_of_elements != 0);              // Liste leer?
  assert (current_element_ptr != NULL);          // Kein momentanes Element?
  current_element_ptr = current_element_ptr->previous_element_ptr;
  return DS_OK;
}

/******************************************************************************
   Method:     DSBaseList::MoveNext(void)
   Purpose:    Aktuelles Element auf nachfolgendes Element setzen.
   In:         None.
   Out:        DSResult DS_TRUE, falls erfolgreich, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSResult DSBaseList<T>::MoveNext(void) // const
{
  if (current_element_ptr == last_element_ptr)
  {
    return DS_ERROR;
  }
                                                 // AtEndOfList?
  assert(current_element_ptr != NULL);           // Kein momentanes Element?
  current_element_ptr = current_element_ptr->next_element_ptr;
  return DS_OK;
}

/******************************************************************************
   Method:     DSBaseList::MoveFirst(void)
   Purpose:    Aktuelles Element auf erstes Element setzen.
   In:         None.
   Out:        DSResult DS_TRUE, falls erfolgreich, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSResult DSBaseList<T>::MoveFirst(void) // const
{
  if (first_element_ptr == NULL)               // Liste leer?
  {
    return DS_ERROR;
  }
  current_element_ptr = first_element_ptr;
  return DS_OK;
}

/******************************************************************************
   Method:     DSBaseList::MoveLast(void)
   Purpose:    Aktuelles Element auf letztes Element setzen.
   In:         None.
   Out:        DSResult DS_TRUE, falls erfolgreich, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSResult DSBaseList<T>::MoveLast(void) // const
{
  if (number_of_elements == 0)               // Liste leer?
  {
    return DS_ERROR;
  }
  current_element_ptr = last_element_ptr;
  return DS_OK;
}

/******************************************************************************
   Method:     DSBaseList::AtEndOfList(void)
   Purpose:    Test, ob momentanes Element das letzte in der Liste ist.
   In:         None.
   Out:        DSBoolean DS_TRUE, falls ja, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSBoolean DSBaseList<T>::AtEndOfList(void) const
{
  return (current_element_ptr == last_element_ptr) ? DS_TRUE : DS_FALSE;
}

/******************************************************************************
   Method:     DSBaseList::AtStartOfList(void)
   Purpose:    Test, ob momentanes Element das erste in der Liste ist.
   In:         None.
   Out:        DSBoolean DS_TRUE, falls ja, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T>
DSBoolean DSBaseList<T>::AtStartOfList(void) const
{
  return (current_element_ptr == first_element_ptr) ? DS_TRUE : DS_FALSE;
}

#endif
