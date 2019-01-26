#ifndef _DSINPUTSIGNAL_H_
#define _DSINPUTSIGNAL_H_

#include "DSBasicTypes.h"
#include "DSObject.h"
#include "DSRef.h"
#include "DSVariableAccessComponent.h"

/************************************************************************
 * Classname: DSInputSignal
 * Purpose:   Speichert einen SDL Signal-Stimulus
 * Z100:      Seite 53 <stimulus>
 ************************************************************************/

class DSInputSignal : public DSObject,
                      public DSVariableAccessComponent
{
  public:
    DSInputSignal(DSObject*             = NULL,   // Vaterobjekt
                  DSSignalRef           = NULL,
                  DSVariableAccessList* = NULL);
    virtual ~DSInputSignal(void);

    DSObject     *New(DSObject * = NULL) const;  // virtueller Konstruktor

    DSSignalRef   GetSignalRef(void) const;

    DSResult      SetSignalRef(DSSignalRef);

    DSObject     *Clone(DSObject * = NULL,
                        DSObject * = NULL) const; // erzeugt eine identische
                                                  // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult      Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult      Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSSignalRef           signal_ref;
};

#endif

