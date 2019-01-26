#ifndef _DSNAMESORT_H_
#define _DSNAMESORT_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSRef.h"

/************************************************************************
 * Classname: DSNameSort
 * Purpose:   Zuordnung von Variablennamen zu Datentypen. Wird von
 *            DSStruct verwendet.
 ************************************************************************/
 
class DSNameSort : public DSNamedObject
{
  public:
    DSNameSort(DSObject* = NULL,
               DSString* = NULL,
               DSSortRef = NULL);
    DSNameSort(DSObject*,
               DSString&,
               DSSortRef = NULL);
    DSNameSort(DSObject*,
               const char *,
               DSSortRef = NULL);
    ~DSNameSort(void);

    DSObject *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSSortRef GetSortRef(void) const;

    DSResult  SetSortRef(DSSortRef = NULL);

    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                                   // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSSortRef sort_ref;      
};

#endif
