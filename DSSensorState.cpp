/************************************************************************
 * Classname: DSSensorState
 * Purpose:   Definition eines Sensors
 ************************************************************************/

#include "DSSensorState.h"

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSensorState::DSSensorState (DSObject* father,
                              DSSensorType sType,
                              DSString* sName,
                              DSStateRef state,
                              DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  state_ref (state)
{
  // do nothing.
}

DSSensorState::DSSensorState (DSObject* father,
                              DSSensorType sType,
                              DSString& sName,
                              DSStateRef state,
                              DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  state_ref (state)
{
  // do nothing.
}

DSSensorState::DSSensorState (DSObject* father,
                              DSSensorType sType,
                              const char * sName,
                              DSStateRef state,
                              DSExpression *int_exp) :
  DSSensor (father, sType, sName, int_exp),
  state_ref (state)
{
  // do nothing.
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSensorState::~DSSensorState (void)
{
  // do nothing.
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject* DSSensorState::New (DSObject* father) const
{
  return new DSSensorState(father);
}

DSObject *DSSensorState::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSensorState *new_sensor_state;

  if (fill_this == NULL)
  {
    new_sensor_state = (DSSensorState *)New(father);
    assert(new_sensor_state);
  }
  else
  {
    assert(fill_this->GetType() == DS_SENSOR);
    new_sensor_state = (DSSensorState *)fill_this;
  }

  // Basisklassen clonen:
  DSSensor::Clone(father, new_sensor_state);
 
  new_sensor_state->SetStateRef(GetStateRef());
  
  return new_sensor_state;
}

DSStateRef DSSensorState::GetStateRef (void) const
{
  return state_ref;
}

DSResult DSSensorState::SetStateRef (DSStateRef state)
{
  state_ref = state;

  return DS_OK;
}
