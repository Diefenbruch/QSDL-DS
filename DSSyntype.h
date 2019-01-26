#ifndef _DSSYNTYPE_H_
#define _DSSYNTYPE_H_

#include "DSBasicTypes.h"
#include "DSSort.h"
#include "DSRangeList.h"
#include "DSRef.h"

/************************************************************************
 * Classname: DSSyntype
 * Purpose:   Definition eines SDL-Syntype
 * Z100:      Seite 132
 ************************************************************************/

class DSSyntype : public DSSort
{
  public:
    DSSyntype(DSObject*,            // Vaterobjekt, wird an DSSort weiter-
              DSString* = NULL,     // gegeben
              DSSortRef = NULL,
              DSRangeList*  = NULL);                
    DSSyntype(DSObject*,
              DSString&,
              DSSortRef = NULL,
              DSRangeList*  = NULL);               
    DSSyntype(DSObject*,
              const char *,
              DSSortRef = NULL,
              DSRangeList*  = NULL);           /* zwecks Initialisierung des */
    ~DSSyntype(void);                          /* Wertebereichs (DSRange)    */
    
    DSSortRef    GetParentSortRef(void) const;
    DSRangeList *GetRangeList(void) const;
    DSRange     *GetFirstRange(void) const;
    DSRange     *GetNextRange(void) const;

    DSResult     SetParentSortRef(DSSortRef);
    DSResult     SetRangeList(DSRangeList*);
    DSResult     InsertRange(DSRange*);
    
    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSRangeList *range_list;
    DSSortRef    parent_sort_ref;
};

#endif
