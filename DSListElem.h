/******************************************************************************
 *  Modul: $RCSfile: DSListElem.h,v $
 *
 *  $Author: md $
 *  $Date: 1998/01/13 12:48:22 $
 *  $Revision: 1.3 $
 *
 *  Aufgabe:
 *    Dieser Modul stellt die Elementklasse fuer schluessellose Listen
 *    zur Verfuegung.
 *
 *  Klassen:
 *    DSListElem<T>
 ******************************************************************************/

#ifndef _DSLISTELEM_H_
#define _DSLISTELEM_H_

/******************************************************************************
   Include-Dateien
 ******************************************************************************/

#include "DSBaseListElem.h"

/******************************************************************************
   Klasse DSListElem
   Zweck: Elementklasse fuer schluessellose Listen.
 ******************************************************************************/

template <class T> class DSListElem : public DSBaseListElem<T>
{
  public:
    DSListElem(T* = NULL,                // Leere Elemente erlaubt.
               DSListElem<T>* = NULL,
               DSListElem<T>* = NULL);
   ~DSListElem(void);
};

#ifndef __GNUC__
  #include "DSListElem.tmpl.h"  // necessary for CC compiler
#endif

#endif
