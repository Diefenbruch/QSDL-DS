#ifndef _DSSORTEXTENDED_H_
#define _DSSORTEXTENDED_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSSort.h"
#include "DSStringList.h"
#include "DSOperatorList.h"

/************************************************************************
 * Classname: DSSortExtended
 * Purpose:   Definition eines SDL-Datentypes mit erweiterten Informationen.
 *            Wird fuer DSGenerator und DSStruct benoetigt. Im Moment werden
 *            als Zusatzinformationen nur die Literale und Operatoren gespeichert.
 *            (keine Axiome)
 * Z100:      Seite 
 ************************************************************************/

class DSSortExtended : public DSSort
{
  public:
    DSSortExtended(DSObject* = NULL,                /* Vaterobjekt            */
                   DSString* = NULL,                /* Name des DSSort        */
                   DSSortTag = DS_SORT_EXTENDED,
                   DSStringList* = NULL,            /* Literale               */
                   DSOperatorKeyList* = NULL,       /* Operatorenliste        */
                   DSBoolean = DS_FALSE,            /* vordefinierter Typ?    */
                   DSBoolean = DS_FALSE);           /* komplexer Typ?         */
    DSSortExtended(DSObject*,                       /* Vaterobjekt            */
                   DSString&,                       /* Name des DSSort        */
                   DSSortTag = DS_SORT_EXTENDED,
                   DSStringList* = NULL,            /* Literale               */
                   DSOperatorKeyList* = NULL,       /* Operatorenliste        */
                   DSBoolean = DS_FALSE,            /* vordefinierter Typ?    */
                   DSBoolean = DS_FALSE);           /* komplexer Typ?         */
    DSSortExtended(DSObject*,                       /* Vaterobjekt            */
                   const char*,                     /* Name des DSSort        */
                   DSSortTag = DS_SORT_EXTENDED,
                   DSStringList* = NULL,            /* Literale               */
                   DSOperatorKeyList* = NULL,       /* Operatorenliste        */
                   DSBoolean = DS_FALSE,            /* vordefinierter Typ?    */
                   DSBoolean = DS_FALSE);           /* komplexer Typ?         */
    virtual ~DSSortExtended(void);
    
    DSObject  *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSStringList      *GetLiteralList(void) const;
    DSString          *GetFirstLiteral(void) const;
    DSString          *GetNextLiteral(void) const;
    DSOperatorKeyList *GetOperatorList(void) const;
    DSOperator        *GetFirstOperator(void) const;
    DSOperator        *GetNextOperator(void) const;
    DSOperator        *GetOperator(DSString*) const;
    DSOperator        *GetOperator(DSString&) const;
    DSOperator        *GetOperator(const char *) const;

    DSResult           SetLiteralList(DSStringList*);
    DSResult           InsertLiteral(DSString*);
    DSResult           InsertLiteral(DSString&);
    DSResult           InsertLiteral(const char *);
    DSResult           SetOperatorList(DSOperatorKeyList*);
    DSResult           InsertOperator(DSOperator*);
        
    DSObject          *Clone(DSObject * = NULL,
                             DSObject * = NULL) const; // erzeugt eine identische
                                                       // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult   Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult   Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSStringList      *literal_list;
    DSOperatorKeyList *operator_list;
};

#endif
