/******************************************************************************
 *  Modul: $RCSfile: DSKeyListElem.h,v $
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
 *    In diesem Modul wird die Elementklasse fuer geordnete, durchsuchbare
 *    Listen definiert.
 *
 *  Klassen:
 *    DSKeyListElem  Elementklasse fuer nach Schluessel durchsuchbare Listen.
 ******************************************************************************/

#ifndef _DS_KEYLISTELEM_H_
#define _DS_KEYLISTELEM_H_

/******************************************************************************
   Konstanten
 ******************************************************************************/

/******************************************************************************
   Include-Dateien
 ******************************************************************************/

#include "DSBasicTypes.h"
#include "DSListElem.h"

/******************************************************************************
   Externe Variablen
 ******************************************************************************/

/******************************************************************************
   Globale Variablen
 ******************************************************************************/

/******************************************************************************
   Klassendefinitionen
 ******************************************************************************/

template <class T, class K> class DSKeyList;

/******************************************************************************
 *  Klasse DSKeyListElem
 *  Zweck: Elementklasse fuer Listen mit Suchschluessel.
 ******************************************************************************/
 
template <class T, class K> class DSKeyListElem : DSListElem<T>
{
   public:
     DSKeyListElem(T*,                           // Kein leerer Schluessel!
                   K*,                           // Kein leerer Datenteil!!
                   DSKeyListElem<T, K>* = NULL,
                   DSKeyListElem<T, K>* = NULL);
     ~DSKeyListElem(void);
                                                 
   protected:
     K *key;                                     // Zeiger auf Schluesselwert.

   friend class DSKeyList<T, K>;   
};

#endif
