/************************************************************************
 * Classname: DSSensorProcess
 * Purpose:   Definition eines Sensors
 ************************************************************************/

#include "DSSensorProcess.h"

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSensorProcess::DSSensorProcess (DSObject* father,
                                  DSSensorType sType,
                                  DSString* sName,
                                  DSProcessRefList *p_list,
                                  DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  DSProcessRefComponent(p_list)
{
  // do nothing.
}

DSSensorProcess::DSSensorProcess (DSObject* father,
                                  DSSensorType sType,
                                  DSString& sName,
                                  DSProcessRefList *p_list,
                                  DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  DSProcessRefComponent(p_list)
{
  // do nothing.
}

DSSensorProcess::DSSensorProcess (DSObject* father,
                                  DSSensorType sType,
                                  const char * sName,
                                  DSProcessRefList *p_list,
                                  DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  DSProcessRefComponent(p_list)
{
  // do nothing.
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSensorProcess::~DSSensorProcess (void)
{
  // do nothing.
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject* DSSensorProcess::New (DSObject* father) const
{
  return new DSSensorProcess(father);
}

DSObject *DSSensorProcess::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSensorProcess *new_sensor_process;

  if (fill_this == NULL)
  {
    new_sensor_process = (DSSensorProcess *)New(father);
    assert(new_sensor_process);
  }
  else
  {
    assert(fill_this->GetType() == DS_SENSOR);
    new_sensor_process = (DSSensorProcess *)fill_this;
  }

  // Basisklassen clonen:
  DSSensor::Clone(father, new_sensor_process);
 
  if (GetProcessRefList())  
  {
    new_sensor_process->SetProcessRefList((DSProcessRefList *)GetProcessRefList()->Clone((DSObject *)new_sensor_process));
  }
  
  return new_sensor_process;
}
