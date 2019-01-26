/************************************************************************
 * Classname: DSSensorMachineService
 * Purpose:   Definition eines Sensors
 ************************************************************************/

#include "DSSensorMachineService.h"

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSensorMachineService::DSSensorMachineService (DSObject* father,
                                                DSSensorType sType,
                                                DSString* sName,
                                                DSMachineServiceRefList *m_list,
                                                DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  DSMachineServiceRefComponent(m_list)
{
  // do nothing.
}

DSSensorMachineService::DSSensorMachineService (DSObject* father,
                                                DSSensorType sType,
                                                DSString& sName,
                                                DSMachineServiceRefList *m_list,
                                                DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  DSMachineServiceRefComponent(m_list)
{
  // do nothing.
}

DSSensorMachineService::DSSensorMachineService (DSObject* father,
                                                DSSensorType sType,
                                                const char * sName,
                                                DSMachineServiceRefList *m_list,
                                                DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  DSMachineServiceRefComponent(m_list)
{
  // do nothing.
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSensorMachineService::~DSSensorMachineService(void)
{
  // do nothing.
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject* DSSensorMachineService::New (DSObject* father) const
{
  return new DSSensorMachineService(father);
}

DSObject *DSSensorMachineService::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSensorMachineService *new_sensor_machine_service;

  if (fill_this == NULL)
  {
    new_sensor_machine_service = (DSSensorMachineService *)New(father);
    assert(new_sensor_machine_service);
  }
  else
  {
    assert(fill_this->GetType() == DS_SENSOR);
    new_sensor_machine_service = (DSSensorMachineService *)fill_this;
  }

  // Basisklassen clonen:
  DSSensor::Clone(father, new_sensor_machine_service);
 
  if (GetMachineServiceRefList())
  {
    new_sensor_machine_service->SetMachineServiceRefList((DSMachineServiceRefList *)GetMachineServiceRefList()->Clone((DSObject *)new_sensor_machine_service));
  }
  
  return new_sensor_machine_service;
}
