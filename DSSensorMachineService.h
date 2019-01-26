#ifndef DS_SENSORMACHINESERVICE_H_
#define DS_SENSORMACHINESERVICE_H_

#include "DSSensor.h"
#include "DSRef.h"
#include "DSMachineServiceRefComponent.h"

/************************************************************************
 * Classname: DSSensorMachineService
 * Purpose:   Definition eines Sensors fuer MachineServices
 ************************************************************************/

class DSSensorMachineService : public DSSensor,
                               public DSMachineServiceRefComponent
{
  public:
                 DSSensorMachineService (DSObject*,
                                         DSSensorType = DS_SENSOR_ILLEGAL,
                                         DSString* = NULL,
                                         DSMachineServiceRefList * = NULL,
                                         DSExpression * = NULL); // Intervall
                 DSSensorMachineService (DSObject*,
                                         DSSensorType,
                                         DSString&,
                                         DSMachineServiceRefList * = NULL,
                                         DSExpression * = NULL); // Intervall
                 DSSensorMachineService (DSObject*,
                                         DSSensorType,
                                         const char *,
                                         DSMachineServiceRefList * = NULL,
                                         DSExpression * = NULL); // Intervall
                ~DSSensorMachineService(void);

    DSObject    *New(DSObject * = NULL) const;
    DSObject    *Clone(DSObject * = NULL,
                       DSObject * = NULL) const;
};

typedef DSList<DSSensorMachineService> DSSensorMachineServiceList;

#endif
