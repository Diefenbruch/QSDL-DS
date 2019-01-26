#ifndef _DSOPERANDPROCESSACCESS_H_
#define _DSOPERANDPROCESSACCESS_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSOperandProcessAccess
 * Purpose:   Definiton eines QSDL-Process-Operanden (wird fuer Zugriffs-
 *            methoden auf Sensoren benoetigt)
 * Z100:      -
 ************************************************************************/

class DSOperandProcessAccess : public DSOperand
{
  public:
    DSOperandProcessAccess(DSObject*    = NULL,
                           class DSProcessAccess * = NULL);
    ~DSOperandProcessAccess(void);
    
    DSProcessAccess * GetProcessAccess() const;
    DSResult          SetProcessAccess(class DSProcessAccess *);

    DSObject         *New(DSObject * = NULL) const;
    DSObject         *Clone(DSObject * = NULL,
                            DSObject * = NULL) const; // erzeugt eine identische
                                                      // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    class DSProcessAccess *process_access;
};

#endif
