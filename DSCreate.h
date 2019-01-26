#ifndef _DSCREATE_H_
#define _DSCREATE_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSAction.h"
#include "DSActualParamComponent.h"

/******************************************************************************
 * Klasse: DSCreate
 * Zweck:  Datenstruktur zur Speicherung der Parameter fuer eine CREATE-
 *         Instruktion.
 * Z100:   Seite 62
 ******************************************************************************/

class DSCreate : public DSAction,
                 public DSActualParamComponent
{
  public:
    DSCreate(DSObject*,
             DSString*          = NULL,          // Label
             DSProcessRef       = NULL,
             DSActualParamList* = NULL);         
    DSCreate(DSObject*,
             DSString&,        
             DSProcessRef       = NULL,
             DSActualParamList* = NULL);     
    DSCreate(DSObject*,
             const char *       = NULL,        
             DSProcessRef       = NULL,
             DSActualParamList* = NULL);      
    ~DSCreate(void);
     
    DSProcessRef       GetProcessRef(void) const;

    DSResult           SetProcessRef(DSProcessRef);
     
    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult   Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult   Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSProcessRef       process_ref;
};

#endif  // ifndef
