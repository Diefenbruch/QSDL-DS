#ifndef _DSSTRUCT_H_
#define _DSSTRUCT_H_

#include "DSBasicTypes.h"
#include "DSSortExtended.h"
#include "DSNameSortList.h"

/************************************************************************
 * Classname: DSStruct
 * Purpose:   Definition einer SDL-Struktur
 * Z100:      Seite 137
 ************************************************************************/

class DSStruct : public DSSortExtended
{
  public:
    DSStruct(DSObject*,
             DSString * = NULL,
             DSNameSortKeyList* = NULL);
    DSStruct(DSObject*,
             DSString& ,
             DSNameSortKeyList* = NULL);
    DSStruct(DSObject*,
             const char *,
             DSNameSortKeyList* = NULL);
    ~DSStruct(void);

    DSNameSortKeyList *GetFieldList(void) const;
    DSNameSort        *GetFirstField(void) const;
    DSNameSort        *GetNextField(void) const;
    DSNameSort        *GetField(DSString*) const;
    DSNameSort        *GetField(DSString&) const;
    DSNameSort        *GetField(const char *) const;

    DSResult           SetFieldList(DSNameSortKeyList*);
    DSResult           InsertField(DSNameSort*);

    DSObject          *Clone(DSObject * = NULL,
                             DSObject * = NULL) const;      // erzeugt eine identische
                                               // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult   Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult   Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSNameSortKeyList *field_list;
};

#endif
