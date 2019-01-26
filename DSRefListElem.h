/******************************************************************************
 *  Modul: $RCSfile: DSRefListElem.h,v $
 *
 *  $Author: md $
 *  $Date: 1998/01/13 12:48:22 $
 *  $Revision: 1.1 $
 *
 *  Aufgabe:
 *    Dieser Modul stellt die Elementklasse fuer schluessellose Listen
 *    zur Verfuegung.
 *
 *  Klassen:
 *    DSListElem<T>
 ******************************************************************************/

#ifndef _DS_REFLISTELEM_H_
#define _DS_REFLISTELEM_H_

/******************************************************************************
   Include-Dateien
 ******************************************************************************/

#include "DSBaseListElem.h"

/******************************************************************************
   Klasse DSListElem
   Zweck: Elementklasse fuer schluessellose Listen.
 ******************************************************************************/

template <class T> class DSRefListElem : public DSBaseListElem<T>
{
  public:
    DSRefListElem(T* = NULL,                // Leere Elemente erlaubt.
                  DSRefListElem<T>* = NULL,
                  DSRefListElem<T>* = NULL);
   ~DSRefListElem(void);
};

#ifndef __GNUC__
  #include "DSRefListElem.tmpl.h"  // necessary for CC compiler
#endif

#endif
