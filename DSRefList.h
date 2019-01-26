/******************************************************************************
 *  Modul: $RCSfile: DSRefList.h,v $
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
 *    Dieser Modul stellt schluessellose Listen, die nicht durchsucht werden
 *    koennen, bereit.
 *
 *  Klassen:
 *    DSList<T>
 ******************************************************************************/

#ifndef _DSREFLIST_H_
#define _DSREFLIST_H_

/******************************************************************************
   Include-Dateien
 ******************************************************************************/

#include "DSBaseList.h"
#include "DSRefListElem.h"

/******************************************************************************
   Klasse DSRefList
   Zweck: Listenklasse fuer schluessellose Listen (ohne Freigabe der
          Daten).
 ******************************************************************************/

template <class T> class DSRefList : public DSBaseList<T>
{
   public:
     DSRefList(void);
    ~DSRefList(void);

     DSBaseListElem<T> * NewElem(T *) const;
     DSRefList<T> *      Clone(DSObject *) const;
                                                 /* erzeugt eine identische
                                                    Kopie dieser Liste. */
     DSRefList<T> *      Split(void);            /* Trennt die Liste an der
                                                   aktuellen Position; Kopfteil
                                                   bleibt der urspruenglichen
                                                   Liste zugeordnet, Endteil
                                                   wird als neue Liste zurueck-
                                                   geliefert */
};

#ifndef __GNUC__
  #include "DSRefList.tmpl.h"  // necessary for CC compiler
#endif

#endif
