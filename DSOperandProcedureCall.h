#ifndef _DSOPERANDPROCEDURE_CALL_H_
#define _DSOPERANDPROCEDURE_CALL_H_

#include "DSBasicTypes.h"
#include "DSOperand.h"

/************************************************************************
 * Classname: DSOperandProcedureCall
 * Purpose:   Definiton eines wertliefernden SDL-Proceduraufrufs in
 *            einem Ausdruck
 * Z100:
 ************************************************************************/

class DSOperandProcedureCall : public DSOperand
{
  public:
    DSOperandProcedureCall(DSObject* = NULL,
                           class DSCall* = NULL);
    virtual ~DSOperandProcedureCall(void);
    
    class DSCall     *GetProcedureCall() const;

    DSResult          SetProcedureCall(class DSCall *);
        
    DSObject *New(DSObject * = NULL) const;
    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /****************************************************/
    /* Die folgende Funktionen dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    class DSCall  *call;
};

#endif
