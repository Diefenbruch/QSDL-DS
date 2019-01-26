/******************************************************************************
 *  Modul: $RCSfile: DSList.h,v $
 *
 *  $Author: md $
 *  $Date: 1998/01/14 06:07:11 $
 *  $Revision: 1.6 $
 *
 *  Aufgabe:
 *    Dieser Modul stellt Klassen fuer die Handhabung von Listen
 *    bereit. Listen werden in zwei Grundformen angeboten:
 *    Listen mit Schluessel, die durchsucht werden koennen, und
 *    Listen ohne Schluessel, die nicht durchsucht werden koennen.
 *    Dieser Modul stellt schluessellose Listen, die nicht durchsucht werden
 *    koennen, bereit.
 *
 *  Klassen:
 *    DSList<T>
 ******************************************************************************/

#ifndef _DSLIST_H_
#define _DSLIST_H_

#include "DSBaseList.h"
#include "DSListElem.h"

/******************************************************************************
   Klasse DSList
   Zweck: Listenklasse fuer schluessellose Listen.
 ******************************************************************************/

template <class T> class DSList : public DSBaseList<T>                  
{
   public:
     DSList(void);
    ~DSList(void);

     DSBaseListElem<T> * NewElem(T *) const;
     DSList<T> *         Clone(DSObject *) const;
                                                 /* erzeugt eine identische
                                                    Kopie dieser Liste. */
     DSList<T> *         Split(void);            /* Trennt die Liste an der
                                                   aktuellen Position; Kopfteil
                                                   bleibt der urspruenglichen
                                                   Liste zugeordnet, Endteil
                                                   wird als neue Liste zurueck-
                                                   geliefert */
};

#ifndef __GNUC__
  #include "DSList.tmpl.h"  // necessary for CC compiler
#endif

#endif
