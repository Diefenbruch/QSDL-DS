#ifndef _DSMACHINE_H_
#define _DSMACHINE_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"
#include "DSSensorComponent.h"
#include "DSMachineServiceSpeedList.h"

/************************************************************************
 * Classname: DSMachine
 * Purpose:   Definition eines QSDL-Maschine (Ressourcen)
 ************************************************************************/

class DSMachine : public DSNamedObject,
                  public DSSensorComponent
{
  public:
    DSMachine(DSObject*,
               DSString* = NULL,
               class DSExpression* = NULL,   // Server
               class DSExpression* = NULL);  // Discipline
    DSMachine(DSObject*,
               DSString&,
               class DSExpression* = NULL,   // Server
               class DSExpression* = NULL);  // Discipline
    DSMachine(DSObject*,
               const char *,
               class DSExpression* = NULL,   // Server
               class DSExpression* = NULL);  // Discipline
    virtual ~DSMachine(void);

    DSExpression                *GetNumberOfServers(void) const;
    DSExpression                *GetDiscipline(void) const;
    DSMachineServiceSpeedList   *GetMachineServiceSpeedList(void) const;
    class DSMachineServiceSpeed *GetFirstMachineServiceSpeed(void) const;
    class DSMachineServiceSpeed *GetNextMachineServiceSpeed(void) const;

    DSResult                     SetNumberOfServers(class DSExpression*);
    DSResult                     SetDiscipline(class DSExpression*);
    DSResult                     SetMachineServiceSpeedList(DSMachineServiceSpeedList*);
    DSResult                     InsertMachineServiceSpeed(class DSMachineServiceSpeed*);

    DSObject                    *Clone(DSObject * = NULL,
                                       DSObject * = NULL) const;
                                                     // erzeugt eine identische
                                                     // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult           Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult           Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    class DSExpression        *number_of_servers;
    class DSExpression        *discipline;
    DSMachineServiceSpeedList *service_speed_list;
};

#endif
