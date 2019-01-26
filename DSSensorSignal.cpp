/************************************************************************
 * Classname: DSSensorRequest
 * Purpose:   Definition eines Sensors
 ************************************************************************/

#include "DSSensorSignal.h"

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSensorSignal::DSSensorSignal (DSObject* father,
                                DSSensorType sType,
                                DSString* sName,
                                DSSignalRefList *s_list,
                                DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  DSSignalRefComponent(s_list)
{
  // do nothing.
}

DSSensorSignal::DSSensorSignal (DSObject* father,
                                DSSensorType sType,
                                DSString& sName,
                                DSSignalRefList *s_list,
                                DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  DSSignalRefComponent(s_list)
{
  // do nothing.
}

DSSensorSignal::DSSensorSignal (DSObject* father,
                                DSSensorType sType,
                                const char * sName,
                                DSSignalRefList *s_list,
                                DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  DSSignalRefComponent(s_list)
{
  // do nothing.
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSensorSignal::~DSSensorSignal(void)
{
  // do nothing.
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject* DSSensorSignal::New (DSObject* father) const
{
  return new DSSensorSignal(father);
}

DSObject *DSSensorSignal::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSensorSignal *new_sensor_signal;

  if (fill_this == NULL)
  {
    new_sensor_signal = (DSSensorSignal *)New(father);
    assert(new_sensor_signal);
  }
  else
  {
    assert(fill_this->GetType() == DS_SENSOR);
    new_sensor_signal = (DSSensorSignal *)fill_this;
  }

  // Basisklassen clonen:
  DSSensor::Clone(father, new_sensor_signal);
 
  if (GetSignalRefList())
  {
    new_sensor_signal->SetSignalRefList((DSSignalRefList *)GetSignalRefList()->Clone((DSObject *)new_sensor_signal));
  }
  
  return new_sensor_signal;
}
