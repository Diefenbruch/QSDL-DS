#ifndef _DSSORT_H_
#define _DSSORT_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"

/************************************************************************
 * Classname: DSSort
 * Purpose:   Definition eines SDL-Datentyps, Basisklasse fuer DSStruct,...
 * Z100:      Seite 117, Seite 161 (default initialization)
 ************************************************************************/

class DSSort : public DSNamedObject
{
  public:
    DSSort(DSObject* = NULL,               /* Vaterobjekt          */
           class DSString* = NULL,         /* Name                 */
           DSSortTag = DS_SORT_BASIC,      /* Type der Sorte       */
           DSBoolean = DS_FALSE,           /* vordefinierter Typ ? */
           DSBoolean = DS_FALSE,           /* komplexer Typ ?      */
           class DSExpression* = NULL);
    DSSort(DSObject*,                      /* Vaterobjekt          */
           class DSString&,                /* Name                 */
           DSSortTag = DS_SORT_BASIC,      /* Type der Sorte       */
           DSBoolean = DS_FALSE,           /* vordefinierter Typ ? */
           DSBoolean = DS_FALSE,           /* komplexer Typ ?      */
           class DSExpression* = NULL);
    DSSort(DSObject*,                      /* Vaterobjekt          */
           const char *,                   /* Name                 */
           DSSortTag = DS_SORT_BASIC,      /* Type der Sorte       */
           DSBoolean = DS_FALSE,           /* vordefinierter Typ ? */
           DSBoolean = DS_FALSE,           /* komplexer Typ ?      */
           class DSExpression* = NULL);
    ~DSSort(void);

    DSObject           *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSSortTag           GetTag(void) const;
    virtual DSBoolean   GetIsPredefined(void) const;
    virtual DSBoolean   GetIsComplex(void) const;
    class DSExpression *GetDefaultInitialization(void) const;
    class DSString     *GetNeutralElement(void) const;
    
    DSResult            SetTag(DSSortTag);
    DSResult            SetIsPredefined(DSBoolean);
    DSResult            SetIsComplex(DSBoolean);
    DSResult            SetDefaultInitialization(class DSExpression *);
    DSResult            SetNeutralElement(class DSString *);
    DSResult            SetNeutralElement(class DSString &);
    DSResult            SetNeutralElement(const char *);

    DSObject           *Clone(DSObject * = NULL,
                              DSObject * = NULL) const;
                                                // erzeugt eine identische
                                                // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktion dient zum systematischen   */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSSortTag           tag;
    DSBoolean           predefined;      // alle QSDL-Datentypen (auch Randoms)
    DSBoolean           complex;         // komplexer (aggregierter) Datentyp
    class DSExpression *default_init;
    class DSString     *neutral_element; // Neutrales Element des Datentyps,
                                         // z.B. 0 bei Integer
};

#endif
