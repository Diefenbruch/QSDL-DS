/******************************************************************************
 *  Modul: $RCSfile: DSKeyList.tmpl.h,v $
 *
 *  $Author: md $
 *  $Date: 1998/01/13 12:48:22 $
 *  $Revision: 1.2 $
 *
 *  Aufgabe:
 *    Dieser Modul stellt Klassen fuer die Handhabung von Listen
 *    bereit. Listen werden in zwei Grundformen angeboten:
 *    Listen mit Schluessel, die durchsucht werden koennen, und
 *    Listen ohne Schluessel, die nicht durchsucht werden koennen.
 *
 *  Klassen:
 ******************************************************************************/

#ifndef _DS_KEYLIST_TMPL_H_
#define _DS_KEYLIST_TMPL_H_

/******************************************************************************
   Method:     DSKeyList::DSKeyList
   Purpose:    Konstruktor.
               Die internen Felder werden mit NULL initialisiert.
   In:         None.
   Out:        None.
   Sideffects: None.
 ******************************************************************************/

template<class T, class K>
DSKeyList<T, K>::DSKeyList(void)
{
}

/******************************************************************************
   Method:     DSKeyList::~DSKeyList
   Purpose:    Destruktor.
               Alle Listenelemente werden geloescht.
   In:         None.
   Out:        None.
   Sideffects: Der Speicher fuer die Listenelemente wird freigegeben.
 ******************************************************************************/

template<class T, class K>
DSKeyList<T, K>::~DSKeyList(void)
{
}

/******************************************************************************
   Method:     DSList::InsertAfter(T*, K*)
   Purpose:    Neues Element hinter dem momentanen Element einfuegen. Das neue
               Element ist danach das momentane Element.
               Leere Elemente duerfen eingefuegt werden.
   In:         Zeiger auf Daten vom Typ T*,
               Zeiger auf Schluessel vom Typ K*
   Out:        DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: Es wird Speicher fuer das neue Listenelement alloziert.
 ******************************************************************************/

template <class T, class K>
DSResult DSKeyList<T, K>::InsertAfter(T *new_data_ptr,
                                      K *new_key_ptr)
{
  assert((void *)new_data_ptr != (void *)new_key_ptr);
  return this->xInsertAfter(new DSKeyListElem<T, K>(new_data_ptr,
                                              new_key_ptr));
                                                 /* Neues Element erzeugen
                                                    und einfuegen lassen.
                                                    Nur diese Zeile ist
                                                    typabhaengig, der Rest
                                                    bleibt immer gleich. */
}

template <class T, class K>
DSResult DSKeyList<T, K>::InsertAfter(T& new_data_ptr,
                                      K& new_key_ptr)
{
  assert((void *)&new_data_ptr != (void *)&new_key_ptr);
  return this->xInsertAfter(new DSKeyListElem<T, K>(&new_data_ptr,
                                              &new_key_ptr));
                                                 /* Neues Element erzeugen
                                                    und einfuegen lassen.
                                                    Nur diese Zeile ist
                                                    typabhaengig, der Rest
                                                    bleibt immer gleich. */
}

/******************************************************************************
   Method:     DSList::InsertBefore(T*, K*)
   Purpose:    Neues Element vor dem momentanen Element einfuegen. Das neue
               Element ist danach das momentane Element.
   In:         Zeiger auf Datensatz vom Typ T*,
               Zeiger auf Schluessel vom Typ K*.
   Out:        DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: Es wird Speicher fuer das neue Listenelement alloziert.
 ******************************************************************************/
 
template <class T, class K>
DSResult DSKeyList<T, K>::InsertBefore(T *new_data_ptr,
                                       K *new_key_ptr)
{
  assert((void *)new_data_ptr != (void *)new_key_ptr);
  return this->xInsertBefore(new DSKeyListElem<T, K>(new_data_ptr, new_key_ptr));
}

template <class T, class K> DSResult DSKeyList<T, K>::
  InsertBefore(T& new_data_ptr,
               K& new_key_ptr)
{
  assert((void *)&new_data_ptr != (void *)&new_key_ptr);
  return this->xInsertBefore(new DSKeyListElem<T, K>(&new_data_ptr, &new_key_ptr));
}


/******************************************************************************
   Method:     DSList::Append(T*, K*)
   Purpose:    Neues Element nach dem letzten Element einfuegen. Das neue
               Element ist danach das momentane Element.
   In:         Zeiger auf Datensatz vom Typ T*,
               Zeigr auf Schluessel vom Typ K*.
   Out:        DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: Es wird Speicher fuer den Datenteil alloziert.
 ******************************************************************************/

template <class T, class K>
DSResult DSKeyList<T, K>::Append(T *new_data_ptr,
                                 K *new_key_ptr)
{
  assert((void *)new_data_ptr != (void *)new_key_ptr);
  return this->xAppend(new DSKeyListElem<T, K>(new_data_ptr, new_key_ptr));
}

template <class T, class K>
DSResult DSKeyList<T, K>::Append(T& new_data_ptr,
                                 K& new_key_ptr)
{
  assert((void *)&new_data_ptr != (void *)&new_key_ptr);
  return this->xAppend(new DSKeyListElem<T, K>(&new_data_ptr, &new_key_ptr));
}


/******************************************************************************
   Method:     DSKeyList::Prepend(T*)
   Purpose:    Neues Element vor dem ersten Element einfuegen. Das neue
               Element ist danach das momentane Element.
   In:         Zeiger auf Datensatz vom Typ T*.
   Out:        DS_TRUE, falls OK, sonst DS_FALSE.
   Sideffects: Es wird Speicher fuer den Datenteil alloziert.
 ******************************************************************************/

template <class T, class K>
DSResult DSKeyList<T, K>::Prepend(T *new_data_ptr,
                                  K *new_key_ptr)
{
  assert((void *)new_data_ptr != (void *)new_key_ptr);
  return this->xPrepend(new DSKeyListElem<T, K>(new_data_ptr, new_key_ptr));
}

template <class T, class K>
DSResult DSKeyList<T, K>::Prepend(T& new_data_ptr,
                                  K& new_key_ptr)
{
  assert((void *)&new_data_ptr != (void *)&new_key_ptr);
  return this->xPrepend(new DSKeyListElem<T, K>(&new_data_ptr, &new_key_ptr));
}

/******************************************************************************
   Method:     DSKeyList::IsKeyInList
   Purpose:    Prueft, ob die Liste ein Element enthaelt, dessen Schluesselwert
               mit *search_key identisch ist. Der Listenzustand wird nicht
               veraendert.
   In:         Zeiger auf Schluesselwert vom Typ K*.
   Out:        DSResult TRUE, wenn gefunden, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T, class K>
DSBoolean DSKeyList<T, K>::IsKeyInList(K *search_key)
{
  DSResult status;
  K *act_key;
  DSKeyListElem<T, K> *temporary_ptr;

  assert(search_key);

  if (this->number_of_elements == 0)                    // Liste ist leer.
  {
    return DS_FALSE;
  }
  
  temporary_ptr = (DSKeyListElem<T, K> *)this->current_element_ptr;            
                                                  // Momentanes Element
                                                  // zwischenspeichern.
  status = this->MoveFirst();                           // An Listenanfang.
  if (status != DS_OK)
  {
    return DS_FALSE;
  }

  act_key = ((DSKeyListElem<T, K> *)this->current_element_ptr)->key;
  if (*act_key == *search_key)
                                                  // Schon gefunden?
  {
    this->current_element_ptr = temporary_ptr;          // Urspruengl.
                                                  // momentanes Element
                                                  // wiederherstellen.
    return DS_TRUE;                               // Ergebnis zurueckgeben.
  }
  
  while (!this->AtEndOfList())                          // Noch beim letzten Ele-
  {                                               // ment?
    status = this->MoveNext();                          // Zum naechsten.
    if (status != DS_OK)
    {
      return DS_FALSE;
    }
    act_key = ((DSKeyListElem<T, K> *)this->current_element_ptr)->key;
    if (*act_key == *search_key)
                                                  // gefunden?
    {
      this->current_element_ptr = temporary_ptr;        // Urspruengl.
                                                  // momentanes Element
                                                  // wiederherstellen.
      return DS_TRUE;                             // Zurueck.
    }
  }
  
  this->current_element_ptr = temporary_ptr;            // Urspruengl.
                                                  // momentanes Element
                                                  // wiederherstellen.
  return DS_FALSE;                                // Nicht gefunden.
}

template <class T, class K>
DSBoolean DSKeyList<T, K>::IsKeyInList(K& search_key)
{
  return IsKeyInList(&search_key);
}

/******************************************************************************
   Method:     DSKeyList::GotoKeyElement
   Purpose:    Prueft, ob die Liste ein Element enthaelt, dessen Schluesselwert
               mit *search_key identisch ist. Wenn ja, ist das momentane Element
               das gesuchte Element. Ist das Element nicht in der Liste
               enthalten, terminiert die Funktion mit assert. Fuer den
               Schluesseltyp K musz der Operator == ueberladen worden sein!!!
   In:         Zeiger auf Schluesselwert vom Typ K*.
   Out:        DSResult TRUE, wenn gefunden, sonst DS_FALSE.
   Sideffects: None.
 ******************************************************************************/

template <class T, class K>
DSResult DSKeyList<T, K>::GotoKeyElement(K *search_key) // const
{
  DSResult status;
  K       *act_key;

  assert(search_key != NULL);                    // Schluessel leer?

  if (this->number_of_elements == 0)                   // Liste leer?
  {
    return DS_ERROR;                             // dann sofort raus...
  }

  assert(this->current_element_ptr != NULL);           // List kann nich leer sein

  status = this->MoveFirst();                          // An Listenanfang.
  
  while (status == DS_OK)                        // Nicht Listenende...
  {
    act_key = ((DSKeyListElem<T, K> *)this->current_element_ptr)->key;

    if (*act_key == *search_key)                 // gefunden?
    {
      return DS_OK;
    }
    status = this->MoveNext();
  }
  return DS_ERROR;
}

template <class T, class K>
DSResult DSKeyList<T, K>::GotoKeyElement(K& search_key) // const
{
  return GotoKeyElement(&search_key);
}

/******************************************************************************
   Method:     DSKeyList::SetCurrentKey(K*)
   Purpose:    Setzt den Schluesselzeiger auf den angegebenen Wert.
   In:         Zeiger auf Schluesselwert vom Typ K*.
   Out:        DS_TRUE, wenn alles o.k., sonst DS_FALSE.
   Sideffects: Der alte Schluesselwert wird dealloziert. (Beachte: in einem
               DSKeyListElem kann dieser Zeiger nie NULL sein!!!).
 ******************************************************************************/

template <class T, class K>
DSResult DSKeyList<T, K>::SetCurrentKey(K *new_key)
{
  assert(this->current_element_ptr != NULL);           // Kein momentanes Element?
  assert(((DSKeyListElem<T, K> *)this->current_element_ptr)->key !=
         NULL);                                  // Schluessel leer???
  delete ((DSKeyListElem<T, K> *)this->current_element_ptr)->key;
                                                 // Alten Schluessel loeschen.
  ((DSKeyListElem<T, K> *)this->current_element_ptr)->key = new_key;
                                                 // Neuen Schluessel setzen.
  return DS_OK;
}

template <class T, class K>
DSResult DSKeyList<T, K>::SetCurrentKey(K& new_key)
{
  return SetCurrentKey(&new_key);
}

/******************************************************************************
   Method:     DSKeyList::GetCurrentKey(K*)
   Purpose:    Ergibt den Schluesselzeiger des momentanen Elements. Gibt es
               kein momentanes Element, wird mit assert abgebrochen.
   In:         Zeiger auf Schluesselwert vom Typ K*.
   Out:        DS_TRUE, wenn alles o.k., sonst DS_FALSE.
   Sideffects: Der alte Schluesselwert wird dealloziert. (Beachte: in einem
               DSKeyListElem kann dieser Zeiger nie NULL sein!!!).
 ******************************************************************************/

template <class T, class K> 
K *DSKeyList<T, K>::GetCurrentKey(void) const
{
  assert(this->current_element_ptr != NULL);           // Kein momentanes Element?
  assert(((DSKeyListElem<T, K> *)this->current_element_ptr)->key != NULL);
                                                 // Schluessel leer???
  return ((DSKeyListElem<T, K> *)this->current_element_ptr)->key;
                                                 // Schluesselzeiger
                                                 // zurueckgeben.
}

/******************************************************************************
   Method:     DSKeyList::Clone(DSObject *)
   Purpose:    Erzeugt identische Kopie dieser Liste.
   In:         Vaterobjekt fuer die neuen Elemente.
   Out:        Zeiger auf die Kopie.
   Sideffects: None.
 ******************************************************************************/

template <class T, class K> DSList<T> *DSKeyList<T, K>::Clone(DSObject *father) const
{
  DSKeyList<T, K> *orig_list = (DSKeyList<T, K> *)this;
  DSKeyList<T, K> *new_list;
  DSResult         status;
  T               *clone_elem;

  new_list = new DSKeyList<T, K>;
  assert(new_list);

  status = orig_list->MoveFirst();               // An Listenanfang.
  
  while (status == DS_OK)                        // Nicht Listenende...
  {
    clone_elem = (T *)this->GetCurrentData()->Clone(); // father NICHT
                                                 // uebergeben!!!
    assert(clone_elem);
    if (father)
    {
      clone_elem->SetParent(father);
    }
    new_list->Append(clone_elem,
                     (K *)this->GetCurrentKey()->Clone(NULL));
    status = orig_list->MoveNext();
  }

  return new_list;
}

#endif
