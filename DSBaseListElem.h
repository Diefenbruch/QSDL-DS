/******************************************************************************
 *  Modul: $RCSfile: DSBaseListElem.h,v $
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
 *    DSBaseListElement<T>
 ******************************************************************************/

#ifndef _DS_BASELISTELEM_H_
#define _DS_BASELISTELEM_H_

/******************************************************************************
   Konstanten
 ******************************************************************************/

/******************************************************************************
   Include-Dateien
 ******************************************************************************/

#include "DSBasicTypes.h"

/******************************************************************************
   Klasse DSBaseListElem
   Zweck: Elementklasse fuer schluessellose Listen.
 ******************************************************************************/

template <class T> class DSBaseListElem
{
  public:
    DSBaseListElem(T* = NULL,                     // Leere Elemente erlaubt.
                   DSBaseListElem<T>* = NULL,
                   DSBaseListElem<T>* = NULL);
    virtual ~DSBaseListElem(void);
    
    DSBaseListElem<T> * next_element_ptr;
    DSBaseListElem<T> * previous_element_ptr;
    T *                 data;
};

#ifndef __GNUC__
  #include "DSBaseListElem.tmpl.h"  // necessary for CC compiler
#endif

#endif
