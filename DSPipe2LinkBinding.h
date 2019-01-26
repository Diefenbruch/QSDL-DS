#ifndef _DSPIPE2LINKBINDING_H_
#define _DSPIPE2LINKBINDING_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSLinkRefComponent.h"
#include "DSPipeRefComponent.h"

/************************************************************************
 * Classname:  DSPipe2LinkBinding
 * Purpose:    Speicherung der Verbindung zwischen einer QSDL-Pipe und
 *             mehreren Links (Umsetzung des QSDL-bind)
 ************************************************************************/

class DSPipe2LinkBinding : public DSObject,
                           public DSPipeRefComponent,
                           public DSLinkRefComponent
{
  public:
    DSPipe2LinkBinding(DSObject*      = NULL,
                       DSPipeRefList* = NULL,
                       DSLinkRefList* = NULL);
    virtual ~DSPipe2LinkBinding(void);       

    DSObject      *New(DSObject * = NULL) const;  // virtueller Konstruktor

    /***********************************************/
    /* Die folgenden zwei Funktionen stellen fest, */
    /* ob eine Pipe bzw. ein Link in der Ver-      */
    /* bindung vorkommt:                           */
    /***********************************************/

    DSBoolean      IsPipeBound(DSPipeRef) const;
    DSBoolean      IsLinkBound(DSLinkRef) const;

    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
};

#endif
