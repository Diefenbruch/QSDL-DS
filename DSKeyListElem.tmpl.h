/******************************************************************************
 *  Modul: $RCSfile: DSKeyListElem.tmpl.h,v $
 *
 *  $Author: md $
 *  $Date: 1998/01/13 12:48:22 $
 *  $Revision: 1.1 $
 *
 *  Aufgabe:
 *    Dieser Modul stellt Klassen fuer die Handhabung von Listen
 *    bereit. Listen werden in zwei Grundformen angeboten:
 *    Listen mit Schluessel, die durchsucht werden koennen, und
 *    Listen ohne Schluessel, die nicht durchsucht werden koennen.
 *    In diesem Modul wird die Elementklasse fuer geordnete, durchsuchbare
 *    Listen definiert.
 *
 *  Klassen:
 *    DSKeyListElem  Elementklasse fuer nach Schluessel durchsuchbare Listen.
 ******************************************************************************/

#ifndef _DS_KEYLISTELEM_TMPL_H_
#define _DS_KEYLISTELEM_TMPL_H_

/******************************************************************************
   Method:     DSKeyListElem::DSKeyListElem
   Purpose:    Konstruktor.
               Die internen Felder werden mit den Vorgabewerten belegt.
   In:         Zeiger auf Datensatz vom Typ T*,
               Zeiger auf Schluesselwert vom Typ K*,
               Zeiger auf Nachfolgerelement vom Typ DSKeyListElem<T, K>*,
               Zeiger auf Vorgaengerelement vom Typ DSKeyListElem<T, K>*.
   Out:        None.
   Sideffects: None.
 ******************************************************************************/
 
template <class T, class K> DSKeyListElem<T, K>::
  DSKeyListElem(T                   *init_data,   // darf nicht NULL sein!
                K                   *init_key,  // darf nicht NULL sein!
                DSKeyListElem<T, K> *init_next_ptr,
                DSKeyListElem<T, K> *init_prev_ptr):
  DSListElem<T>(init_data,
                init_next_ptr,
                init_prev_ptr),
  key(init_key)
{
  assert(key != NULL);                      // Leerer Schluessel?
  assert((void *)init_data != (void *)key);
}


/******************************************************************************
   Method:     DSKeyListElem::~DSKeyListElem
   Purpose:    Destruktor.
   In:         None.
   Out:        None.
   Sideffects: Dealloziert Speicher fuer den Schluessel.
 ******************************************************************************/
 
template <class T, class K> DSKeyListElem<T, K>::~DSKeyListElem(void)
{
  assert(key);
  delete key;
  key = NULL;
}

#endif
