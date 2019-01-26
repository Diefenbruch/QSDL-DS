/******************************************************************************
 *  Modul: $RCSfile: DSBaseList.h,v $
 *
 *  $Author: md $
 *  $Date: 1998/02/10 07:19:32 $
 *  $Revision: 1.2 $
 *
 *  Aufgabe:
 *    Dieser Modul stellt die Basis-Klasse fuer die Handhabung von Listen
 *    bereit. Listen werden in zwei Grundformen angeboten:
 *    Listen mit Schluessel, die durchsucht werden koennen, und
 *    Listen ohne Schluessel, die nicht durchsucht werden koennen.
 *    Dieser Modul stellt schluessellose Listen, die nicht durchsucht werden
 *    koennen, bereit.
 *
 *  Klassen:
 *    DSBaseList<T>
 ******************************************************************************/

#ifndef _DS_BASELIST_H_
#define _DS_BASELIST_H_

/******************************************************************************
   Konstanten
 ******************************************************************************/

/******************************************************************************
   Include-Dateien
 ******************************************************************************/

#include "DSBaseListElem.h"

/******************************************************************************
   Externe Variablen
 ******************************************************************************/

/******************************************************************************
   Globale Variablen
 ******************************************************************************/

/******************************************************************************
   Klassendefinitionen
 ******************************************************************************/

class DSObject;

/******************************************************************************
   Klasse DSBaseList
   Zweck: Basis-Listenklasse fuer schluessellose Listen.
 ******************************************************************************/

template <class T> class DSBaseList              /* class T ist d. Typ des
                                                    Datenteils eines Listen-
                                                    Elements. */
{
   public:
     DSBaseList(void);
     virtual ~DSBaseList(void);

#ifndef _MSC_VER
     DSResult      InsertAfter(T&);
#endif
     DSResult      InsertAfter(T*);              /* Neues Listen Element hinter
                                                    momentanem Element ein-
                                                    fuegen. Nach dem Einfuegen
                                                    zeigt der Listenzeiger auf
                                                    das neue Element. Doubletten
                                                    sind erlaubt. */
                                                     
#ifndef _MSC_VER
     DSResult      InsertBefore(T&);
#endif
     DSResult      InsertBefore(T*);             /* Neues Listen Element vor
                                                    momentanem Element ein-
                                                    fuegen. Nach dem Einfuegen
                                                    zeigt der Listenzeiger auf
                                                    das neue Element.
                                                    Doubletten sind erlaubt. */
                                                     
#ifndef _MSC_VER
     DSResult       Append(T&);
#endif
     DSResult       Append(T*);                  /* Fuegt ein Element am Ende
                                                    der Liste einf. */
                                                     
#ifndef _MSC_VER
     DSResult       Prepend(T&);
#endif
     DSResult       Prepend(T*);                 /* Fuegt ein Element am
                                                    Anfang der Liste ein. */
                                                     
#ifndef _MSC_VER
     DSResult       GotoElement(T&);
#endif
     DSResult       GotoElement(T*);             /* DS_OK, wenn ein Element
                                                    mit der gesuchten
                                                    Adresse existiert,
                                                    sonst DS_ERROR.
                                                    Falls DS_OK, ist das
                                                    gefundene Element das
                                                    momentane Element.
                                                    Der Versuch, mit
                                                    GotoElement() ein
                                                    nichtexistierendes Element
                                                    zu referenzieren,
                                                    ist ein Laufzeitfehler. */
     DSBoolean      IsInList(T*);
#ifndef _MSC_VER
     DSBoolean      IsInList(T&);
#endif
                                                 /* DS_TRUE, wenn ein Element
                                                    mit der Adresse gleich
                                                    *T gefunden wurde, sonst
                                                    DS_FALSE.
                                                    Der Listenzeiger bleibt
                                                    unveraendert. */
     DSResult       DeleteElement(void);         /* Aktuelles Element aus der
                                                    Liste loeschen. Wenn das
                                                    Loeschen fehlschlaegt,
                                                    bleibt der Listenzeiger
                                                    unveraendert. Nach
                                                    erfolgreichem Loeschen
                                                    ist das momentane
                                                    Element das auf das
                                                    geloeschte Element
                                                    folgende Element in
                                                    der Liste. Wurde das letzte
                                                    Element in der Liste
                                                    geloescht, ist das
                                                    momentane Element
                                                    undefiniert. */
     T             *RemoveElement(void);         /* Aktuelles Element aus der
                                                    Liste entnehmen. Wenn das
                                                    Entnehmen fehlschlaegt,
                                                    bleibt der Listenzeiger
                                                    unveraendert. Nach
                                                    erfolgreichem Entnehmen
                                                    ist das momentane
                                                    Element das auf das
                                                    entnommene Element
                                                    folgende Element in
                                                    der Liste. Wurde das letzte
                                                    Element in der Liste
                                                    entnommen, ist das
                                                    momentane Element
                                                    undefiniert. */
     DSCardinal     NumberOfElements(void) const;// Anzahl Elemente in Liste.
     DSBoolean      IsEmpty(void) const;         /* DS_TRUE, falls Liste leer,
                                                    sonst DS_FALSE. */
     DSBoolean      NoCurrentElement(void) const;/* DS_TRUE if current_element_ptr
                                                    == NULL, sonst DS_FALSE. */
     T              *GetCurrentData(void) const; /* Gibt Zeiger auf Datenteil
                                                    des momentanen Elements
                                                    zurueck. Wenn kein
                                                    aktuelles Element vorhanden
                                                    ist, wird NULL
                                                    zurueckgegeben. */
#ifndef _MSC_VER
     DSResult       SetCurrentData(T&);
#endif
     DSResult       SetCurrentData(T*);          // Datenzeiger neu setzen.
     DSResult       MoveNext(void);              /* Setzt Listenzeiger auf das
                                                    naechste Element. Falls
                                                    EOList erreicht wird, wird
                                                    DS_ERROR zurueckgegeben und
                                                    GetCurrentData() = DS_ERROR. */
     DSResult       MovePrevious(void);          /* Analog zu MoveNextElement */
     DSResult       MoveFirst(void);             /* Listenzeiger auf erstes
                                                    Element in der Liste setzen.
                                                    Wenn die Liste leer ist,
                                                    wird DS_ERROR zurueckgegeben
                                                    und der Listenzeiger ist
                                                    undefiniert. */
                                              
     DSResult       MoveLast(void);              /* Listenzeiger auf letztes
                                                    Element in der Liste
                                                    setzen.
                                                    Wenn die Liste leer ist,
                                                    wird DS_ERROR zurueckgegeben
                                                    und der Listenzeiger ist
                                                    undefiniert. */
     DSBoolean      AtEndOfList(void) const;     /* DS_TRUE, wenn momentanes
                                                    Element letztes Element
                                                    ist, sonst DS_FALSE. */
     DSBoolean      AtStartOfList(void) const;   /* DS_TRUE, wenn momentanes
                                                    Element erstes Element
                                                    ist, sonst DS_FALSE. */

#ifndef _MSC_VER
     virtual DSBaseListElem<T> * NewElem(T *) const = 0;
#else
     virtual DSBaseListElem<T> * NewElem(T *) const { return NULL; }
#endif
     
     void          StorePosition(void) { save_element_ptr = current_element_ptr; }
     void          RestorePosition(void) { current_element_ptr = save_element_ptr; }

   protected:
     DSResult      xInsertAfter(DSBaseListElem<T>*); /* Eigentliche Einfuege-
                                                    funktion kapselt DSBaseListElem
                                                    nach auszenhin ab. Durch
                                                    diese Konstruktion wird
                                                    erreicht, dasz diese
                                                    Funktion problemlos weiter-
                                                    vererbt werden kann. In
                                                    den abgeleiteten Klassen
                                                    musz dann nur die public-
                                                    Version der Funktion
                                                    ersetzt werden. Diese ist
                                                    SEHR kurz.*/
                                                     
     DSResult      xInsertBefore(DSBaseListElem<T>*);   // s.o.
     DSResult      xAppend(DSBaseListElem<T>*);         // s.o.
     DSResult      xPrepend(DSBaseListElem<T>*);        // s.o.
   
     DSBaseListElem<T> *first_element_ptr;           // Zeiger auf erstes.
     DSBaseListElem<T> *last_element_ptr;            // Zeiger auf letztes.
     DSBaseListElem<T> *current_element_ptr;         // Zeiger auf momentanes.
     DSBaseListElem<T> *save_element_ptr;            // Temporaeres merken der Position.
     DSCardinal     number_of_elements;          // Anzahl der Elemente.
};

#ifndef __GNUC__
  #include "DSBaseList.tmpl.h"  // necessary for CC compiler
#endif

#endif
