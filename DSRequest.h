#ifndef _DSREQUEST_H_
#define _DSREQUEST_H_

#include "DSBasicTypes.h"
#include "DSAction.h"
#include "DSLinkRefComponent.h"
#include "DSPipeRefComponent.h"

/******************************************************************************
 * Klasse DSRequest
 * Zweck: Datenstruktur zur Speicherung der Parameter fuer eine QSDL-REQUEST-
 *        Instruktion.
 ******************************************************************************/

class DSRequest : public DSAction,
                  public DSLinkRefComponent, // via Links
                  public DSPipeRefComponent  // via Pipes
{
  public:
    DSRequest(DSObject*,
              DSString* = NULL,            // Label
              DSMachineServiceRef = NULL,  // angeforderter Dienst
              class DSExpression* = NULL,        // Bedienwunsch
              class DSExpression* = NULL,        // Prioritaet
              DSLinkRefList* = NULL,       // VIA-Links
              DSPipeRefList* = NULL);      // VIA-Pipes
    DSRequest(DSObject*,
              DSString&,                   // Label
              DSMachineServiceRef = NULL,  // angeforderter Dienst
              class DSExpression* = NULL,        // Bedienwunsch
              class DSExpression* = NULL,        // Prioritaet
              DSLinkRefList* = NULL,       // VIA-Links
              DSPipeRefList* = NULL);      // VIA-Pipes
    DSRequest(DSObject*,
              const char *,                // Label
              DSMachineServiceRef = NULL,  // angeforderter Dienst
              class DSExpression* = NULL,        // Bedienwunsch
              class DSExpression* = NULL,        // Prioritaet
              DSLinkRefList* = NULL,       // VIA-Links
              DSPipeRefList* = NULL);      // VIA-Pipes

    DSRequest(DSObject*,
              DSString*,                   // Label
              DSMachineServiceRef,         // angeforderter Dienst
              class DSExpression*,               // Bedienwunsch
              class DSExpression*,               // Prioritaet
              DSMachineRef);               // FROM machine
    DSRequest(DSObject*,
              DSString&,                   // Label
              DSMachineServiceRef,         // angeforderter Dienst
              class DSExpression*,               // Bedienwunsch
              class DSExpression*,               // Prioritaet
              DSMachineRef);               // FROM machine
    DSRequest(DSObject*,
              const char *,                // Label
              DSMachineServiceRef,         // angeforderter Dienst
              class DSExpression*,               // Bedienwunsch
              class DSExpression*,               // Prioritaet
              DSMachineRef);               // FROM machine
    ~DSRequest(void);

    DSMachineServiceRef  GetMachineServiceRef(void) const;
    DSExpression        *GetMachineServiceAmount(void) const;
    DSExpression        *GetPriority(void) const;
    DSMachineRef         GetMachineRef(void) const;

    /***********************************************/
    /* Die folgenden zwei Funktionen stellen fest, */
    /* ob eine Pipe bzw. ein Link im Routing er-   */
    /* laubt ist:                                  */
    /***********************************************/

    DSBoolean            IsPipeAllowed(DSPipeRef) const;
    DSBoolean            IsLinkAllowed(DSLinkRef) const;

    /******************************/
    /* Routingfunktion (statisch) */
    /******************************/
    DSMachineRefList    *GetMachineServiceDestination(void) const;

    DSResult             SetMachineServiceRef(DSMachineServiceRef);
    DSResult             SetMachineServiceAmount(DSExpression*);
    DSResult             SetPriority(DSExpression*);
    DSResult             SetMachineRef(DSMachineRef);

    DSObject            *Clone(DSObject * = NULL,
                               DSObject * = NULL) const;  // erzeugt eine identische
                                                          // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult     Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult     Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSMachineServiceRef  service_ref;
    DSExpression        *service_amount;
    DSExpression        *priority;
    DSMachineRef         machine_ref;
};

#endif
