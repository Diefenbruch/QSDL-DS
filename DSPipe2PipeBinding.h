#ifndef _DSPIPE2PIPEBINDING_H_
#define _DSPIPE2PIPEBINDING_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSPipeRefComponent.h"
#include "DSPipeComponent.h"

/************************************************************************
 * Classname:  DSPipe2PipeBinding
 * Purpose:    Speicherung der Verbindung zwischen einem Kanal und
 *             mehreren Signalrouten (Umsetzung des SDL-connects)
 * Z100:       
 ************************************************************************/

class DSPipe2PipeBinding : public DSObject
{
  public:
    DSPipe2PipeBinding(DSObject* = NULL,              // Vaterobjekt
                       DSPipeRefComponent * = NULL,   // first list
                       DSPipeRefComponent * = NULL);  // second list
    virtual ~DSPipe2PipeBinding(void);       

    DSObject *            New(DSObject * = NULL) const;  // virtueller Konstruktor

    /***********************************************/
    /* Die folgenden zwei Funktionen stellen fest, */
    /* ob ein Kanal bzw. eine Signalroute in der   */
    /* Verbindung vorkommt:                        */
    /***********************************************/

    DSPipeRefComponent *  GetFirstPipeComponent(void) const;
    DSPipeRefComponent *  GetSecondPipeComponent(void) const;
    DSResult              SetFirstPipeComponent(DSPipeRefComponent *);
    DSResult              SetSecondPipeComponent(DSPipeRefComponent *);
    
    DSBoolean             IsPipeConnectedInFirst(DSPipeRef) const;
    DSBoolean             IsPipeConnectedInSecond(DSPipeRef) const;

    DSObject             *Clone(DSObject * = NULL,
                                DSObject * = NULL) const;
                                                  // erzeugt eine identische
                                                  // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult      Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult      Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSPipeRefComponent *  first_pipe_component;
    DSPipeRefComponent *  second_pipe_component;
};

typedef DSList<DSPipe2PipeBinding>  DSPipe2PipeBindingList;

#endif
