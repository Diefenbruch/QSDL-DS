/******************************************************************************
 *  Modul: $RCSfile: DSKeyList.h,v $
 *
 *  $Author: md $
 *  $Date: 1998/01/13 12:48:22 $
 *  $Revision: 1.3 $
 *
 *  Aufgabe:
 *    Dieser Modul stellt Klassen fuer die Handhabung von Listen
 *    bereit. Listen werden in zwei Grundformen angeboten:
 *    Listen mit Schluessel, die durchsucht werden koennen, und
 *    Listen ohne Schluessel, die nicht durchsucht werden koennen.
 *
 *  Klassen:
 ******************************************************************************/

#ifndef _DSKEYLIST_H_
#define _DSKEYLIST_H_

/******************************************************************************
   Konstanten
 ******************************************************************************/

/******************************************************************************
   Include-Dateien
 ******************************************************************************/

//#include "DSBasicTypes.h"
#include "DSList.h"
#include "DSKeyListElem.h"

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
   Klasse DSKeyList
   Zweck: Listenklasse fuer Listen mit Suchschluessel.
 ******************************************************************************/
 
template <class T, class K> class DSKeyList : public DSList<T>
{
   public:
     DSKeyList(void);
    ~DSKeyList(void);
     
     DSResult  InsertAfter(T&, K&);
     DSResult  InsertAfter(T*, K*);              /* Neues Listen Element hinter
                                                    momentanem Element ein-
                                                    fuegen. Nach dem Einfuegen
                                                    zeigt der Listenzeiger auf
                                                    das neue Element. Doubletten
                                                    sind NICHT erlaubt. */
     DSResult  InsertBefore(T&, K&);
     DSResult  InsertBefore(T*, K*);             /* Neues Listen Element vor
                                                    momentanem Element ein-
                                                    fuegen. Nach dem Einfuegen
                                                    zeigt der Listenzeiger auf
                                                    das neue Element.
                                                    Doubletten sind NICHT
                                                    erlaubt. */
     DSResult  Append(T&, K&);
     DSResult  Append(T*, K*);                   /* Fuegt ein Element am Ende
                                                    der Liste einf.
                                                    Doubletten sind NICHT
                                                    erlaubt. */
     DSResult  Prepend(T&, K&);
     DSResult  Prepend(T*, K*);                  /* Fuegt ein Element am
                                                    Anfang der Liste ein.
                                                    Doubletten sind NICHT
                                                    erlaubt. */
     DSBoolean IsKeyInList(K&);
     DSBoolean IsKeyInList(K*);                  /* DS_TRUE, wenn ein Element
                                                    mit Schluesselwert gleich
                                                    *K gefunden wurde, sonst
                                                    DS_FALSE.
                                                    Der Listenzeiger bleibt
                                                    unveraendert. */
     DSResult  GotoKeyElement(K&);
     DSResult  GotoKeyElement(K*);               /* DS_TRUE, wenn ein Element
                                                    mit dem gesuchten
                                                    Schluesselwert existiert,
                                                    sonst DS_FALSE.
                                                    Falls DS_TRUE, ist das
                                                    gefundene Element das
                                                    momentane Element. */
     DSResult  SetCurrentKey(K&);
     DSResult  SetCurrentKey(K*);                 /* Setzt den Zeiger auf den
                                                    Schluesselwert des
                                                    momentanen Elements neu. */
     K        *GetCurrentKey(void) const;        /* Liefert den Zeiger auf den
                                                    Schluesselwert des
                                                    momentanen Elements. */
     virtual DSList<T> *Clone(DSObject *) const;  /* erzeugt eine identische
                                                    Kopie dieser Liste */
};

#ifndef __GNUC__
  #include "DSKeyList.tmpl.h"  // necessary for CC compiler
#endif

#endif
