#ifndef _DSOBJECT_H_
#define _DSOBJECT_H_

#include "DSBasicTypes.h"
#include "DSRef.h"
#include "DSWriter.h"

/************************************************************************
 * Classname: DSObject
 * Purpose:   Basisklasse fuer alle anderen Datenstruktur-Klassen
 ************************************************************************/

class DSObject
{
  protected:                // damit kein Object vom Type DSObject
    DSObject(DSType,        // erzeugt werden kann
             DSObject* = NULL);

  public:
    virtual ~DSObject(void);

    DSType              GetType(void) const;

    DSObject           *GetParent(void) const;  // Vaterobject
    DSResult            SetParent(const DSObject*);

    /***************************************/
    /* Die folgenden Funktionen werden zum */
    /* Umsetzen von Namen in Referenzen    */
    /* benoetigt:                          */
    /***************************************/
    DSSortRef           GetSortRefByName(DSString *) const;
    DSSortRef           GetSortRefByName(const char *) const;
    DSSortRef           GetSortRefByLiteralName(DSString *) const;
    DSSortRef           GetSortRefByLiteralName(const char *) const;
    DSOperatorRef       GetOperatorRefByName(DSString *) const;
    DSOperatorRef       GetOperatorRefByName(const char *) const;
    DSOperatorRef       GetOperatorRefByNameAndParamSorts(DSString *,
                                                          DSSortRefList * = NULL) const;
    DSOperatorRef       GetOperatorRefByNameAndParamSorts(const char *,
                                                          DSSortRefList * = NULL) const;
    DSVariableRef       GetVariableRefByName(DSString *) const;
    DSVariableRef       GetVariableRefByName(const char *) const;
    DSSignalRef         GetSignalRefByName(DSString *) const;
    DSSignalRef         GetSignalRefByName(const char *) const;
    DSSignalslistRef     GetSignallistRefByName(DSString *) const;
    DSSignalslistRef     GetSignallistRefByName(const char *) const;
    DSBlockRef          GetBlockRefByName(DSString *) const;
    DSBlockRef          GetBlockRefByName(const char *) const;
    DSChannelRef        GetChannelRefByName(DSString *) const;
    DSChannelRef        GetChannelRefByName(const char *) const;
    DSProcessRef        GetProcessRefByName(DSString *) const;
    DSProcessRef        GetProcessRefByName(const char *) const;
    DSSignalRouteRef    GetSignalRouteRefByName(DSString *) const;
    DSSignalRouteRef    GetSignalRouteRefByName(const char *) const;
    DSProcedureRef      GetProcedureRefByName(DSString *) const;
    DSProcedureRef      GetProcedureRefByName(const char *) const;
    DSTimerRef          GetTimerRefByName(DSString *) const;
    DSTimerRef          GetTimerRefByName(const char *) const;
    DSStateRef          GetStateRefByName(DSString *) const;
    DSStateRef          GetStateRefByName(const char *) const;
    DSMachineServiceRef GetMachineServiceRefByName(DSString *) const;
    DSMachineServiceRef GetMachineServiceRefByName(const char *) const;
    DSMachineRef        GetMachineRefByName(DSString *) const;
    DSMachineRef        GetMachineRefByName(const char *) const;
    DSPipeRef           GetPipeRefByName(DSString *) const;
    DSPipeRef           GetPipeRefByName(const char *) const;
    DSLinkRef           GetLinkRefByName(DSString *) const;
    DSLinkRef           GetLinkRefByName(const char *) const;
    DSSensorRef         GetSensorRefByName(DSString *) const;
    DSSensorRef         GetSensorRefByName(const char *) const;
    
    /************************************************/
    /* Funktion liefert das System zu Objekten die  */
    /* hierarchisch unterhalb des Systemobjekts     */
    /* liegen:                                      */
    /************************************************/
    DSSystemRef         GetThisSystem(void) const;

    /************************************************/
    /* Funktion liefert den Block zu Objekten die   */
    /* hierarchisch unterhalb des Blockobjekts      */
    /* liegen:                                      */
    /************************************************/
    DSBlockRef          GetThisBlock(void) const;

    /************************************************/
    /* Funktion liefert den Prozess zu Objekten die */
    /* hierarchisch unterhalb des Prozessobjekts    */
    /* liegen (z.B. fuer Output und Create):        */
    /************************************************/
    DSProcessRef        GetThisProcess(void) const;

    /*************************************************/
    /* Funktion liefert die Prozedur zu Objekten die */
    /* hierarchisch unterhalb des Prozedurobjekts    */
    /* liegen (z.B. fuer Variablenzugriff):          */
    /*************************************************/
    DSProcedureRef      GetThisProcedure(void) const;

    /************************************************/
    /* Funktion liefert den Zustand zu Objekten die */
    /* hierarchisch unterhalb des State-Objekts     */
    /* liegen (z.B. fuer Nextstate):                */
    /************************************************/
    DSStateRef          GetThisState(void) const;

    /************************************************/
    /* Funktion liefert das Atom zu Objekten die    */
    /* hierarchisch unterhalb des Atom-Objekts      */
    /* liegen (z.B. fuer Synoynme wichtig):         */
    /************************************************/
    DSAtomRef          GetThisAtom(void) const;

    /*************************************************/
    /* Virtuelle Clone-Funktion, dient dem Kopieren  */
    /* beliebiger DS-Objekte. Muss von jeder abge-   */
    /* leiteten Klasse redefiniert werden.           */
    /* Als Parameter kann optional ein zu fuellendes */
    /* Objekt angegeben werden (ansonsten wird das   */
    /* Clone-Objekt dynamisch mit New() (s.u.) allo- */
    /* kiert.                                        */
    /*************************************************/
    virtual DSObject   *Clone(DSObject * = NULL, DSObject * = NULL) const = 0;
    
    virtual DSResult    Write(class DSWriter *, DSCardinal = 0) const = 0;
    
    /*************************************************/
    /* Virtueller Konstruktor, dient dem Anlegen     */
    /* beliebiger DS-Objekte. Muss von jeder abge-   */
    /* leiteten Klasse von der Instanzen gebildet    */
    /* werden koennen redefiniert werden.            */
    /*************************************************/
    virtual DSObject   *New(DSObject * = NULL) const = 0;

  private:
    DSType              type;
    DSObject           *parent;
    DSCardinal          id;
    static DSCardinal   run_id;
};

#endif
