#ifndef _DSVARIABLEACCESS_H_
#define _DSVARIABLEACCESS_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSObject.h"
#include "DSVariableAccessElemList.h"

/************************************************************************
 * Classname: DSVariableAccess
 * Purpose:   Speicherung eines Variablenzugriff
 * Z100:      Seite 159
 ************************************************************************/

class DSVariableAccess : public DSObject
{
  public:
    DSVariableAccess(DSObject* = NULL,          // Vaterobjekt
                     DSVariableRef = NULL,      // Referenz auf Deklaration
                     DSVariableAccessElemList* = NULL);
                                                // Zugriffselemente (Indizes
                                                // und/oder Felder
    virtual ~DSVariableAccess(void);

    DSVariableRef               GetVariableRef(void) const;
    DSVariableAccessElemList   *GetElemList(void) const;
    class DSVariableAccessElem *GetFirstElem(void) const;
    class DSVariableAccessElem *GetNextElem(void) const;

    DSResult                  SetVariableRef(DSVariableRef);
    DSResult                  SetElemList(DSVariableAccessElemList*);
    DSResult                  InsertElem(class DSVariableAccessElem*);

    DSObject                 *New(DSObject * = NULL) const;
    DSObject                 *Clone(DSObject * = NULL,
                                    DSObject * = NULL) const;
                                                     // erzeugt eine identische
                                                     // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult          Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult          Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSVariableRef             variable_ref;
    DSVariableAccessElemList *elem_list;
};

#endif
