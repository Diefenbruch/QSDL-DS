/************************************************************************
 * Classname: DSSensor
 * Purpose:   Definition eines Sensors
 ************************************************************************/

#include "DSSensor.h"
#include "DSSystem.h"  // wegen parent
#include "DSBlock.h"  // wegen parent
#include "DSBlockSubstructure.h"  // wegen parent
#include "DSProcess.h" // wegen parent
#include "DSMachine.h" // wegen parent
#include "DSExpression.h"

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSensor::DSSensor (DSObject* father,
                    DSSensorType sType,
                    DSString* sName,
                    DSExpression *int_exp) :
  DSNamedObject (DS_SENSOR, sName, father),
  sensorType (sType),
  interval(int_exp)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSensor(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSensor(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSensor(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSensor(this);
        break;
      case DS_MACHINE:
        ((DSMachine*)father)->InsertSensor(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  SetSortRef();
}

DSSensor::DSSensor (DSObject* father,
                    DSSensorType sType,
                    DSString& sName,
                    DSExpression *int_exp) :
  DSNamedObject (DS_SENSOR, sName, father),
  sensorType (sType),
  interval(int_exp)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSensor(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSensor(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSensor(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSensor(this);
        break;
      case DS_MACHINE:
        ((DSMachine*)father)->InsertSensor(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  SetSortRef();
}

DSSensor::DSSensor (DSObject* father,
                    DSSensorType sType,
                    const char * sName,
                    DSExpression *int_exp):
  DSNamedObject (DS_SENSOR, sName, father),
  sensorType (sType),
  interval(int_exp)
{
  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSensor(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSensor(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSensor(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSensor(this);
        break;
      case DS_MACHINE:
        ((DSMachine*)father)->InsertSensor(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  SetSortRef();
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSensor::~DSSensor(void)
{
  if (interval)
    delete interval;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject* DSSensor::New (DSObject* father) const
{
  return new DSSensor(father);
}

DSExpression *DSSensor::GetInterval(void) const
{
  return interval;
}

DSResult DSSensor::SetInterval(DSExpression *int_exp)
{
  if (interval == int_exp) return DS_OK;

  if (interval) delete interval;
  interval = int_exp;

  if (interval != NULL)
  {
    if (interval->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      interval->SetParent(this);
    }
  }

  return DS_OK;
}

DSSortRef DSSensor::GetSortRef(void) const
{
  return sort_ref;
}

DSResult DSSensor::SetSortRef(DSSortRef sort)
{
  if (sort) 
  {
    sort_ref = sort;
    return DS_OK;
  }
  
  switch(sensorType)
  {
    //
    // Counter-Sensoren:
    //
    case DS_SENSOR_COUNTER:
    case DS_SENSOR_PCS_COUNT_SIGNAL_RECEIVE:
    case DS_SENSOR_PCS_COUNT_SIGNAL_DROP:
    case DS_SENSOR_PCS_COUNT_SIGNAL_CONSUME:
    case DS_SENSOR_PCS_COUNT_SIGNAL_SAVE:
    case DS_SENSOR_PCS_COUNT_SIGNAL_LOSE:
    case DS_SENSOR_PCS_COUNT_SIGNAL_SEND:
    case DS_SENSOR_PCS_COUNT_REQUEST:
    case DS_SENSOR_PCS_COUNT_STATE:
    case DS_SENSOR_PCS_COUNT_TRANSITION:
    case DS_SENSOR_MACH_THROUGHPUT:
    case DS_SENSOR_SYS_COUNT_SIGNAL:
    case DS_SENSOR_SYS_COUNT_REQUEST:
    case DS_SENSOR_SYS_COUNT_PROCESS_CREATE:
    case DS_SENSOR_SYS_COUNT_PROCESS_STOP:
      sort_ref = GetSortRefByName(DS_SORT_NAME_COUNTER);
      assert(sort_ref);
      break;
      
    //
    // Frequency-Sensoren:
    //
    case DS_SENSOR_FREQUENCY:
    case DS_SENSOR_PCS_FREQ_SIGNAL_RECEIVE:
    case DS_SENSOR_PCS_FREQ_SIGNAL_DROP:
    case DS_SENSOR_PCS_FREQ_SIGNAL_CONSUME:
    case DS_SENSOR_PCS_FREQ_SIGNAL_SAVE:
    case DS_SENSOR_PCS_FREQ_SIGNAL_LOSE:
    case DS_SENSOR_PCS_FREQ_SIGNAL_SEND:
    case DS_SENSOR_PCS_FREQ_REQUEST:
    case DS_SENSOR_PCS_FREQ_STATE:
    case DS_SENSOR_PCS_FREQ_TRANSITION:
    case DS_SENSOR_MACH_FREQ_REQUEST:
    case DS_SENSOR_SYS_FREQ_SIGNAL:
    case DS_SENSOR_SYS_FREQ_REQUEST:
    case DS_SENSOR_SYS_FREQ_PROCESS_CREATE:
    case DS_SENSOR_SYS_FREQ_PROCESS_STOP:
    case DS_SENSOR_PCS_QUEUE_CONTENT:
    case DS_SENSOR_MACH_QUEUE_CONTENT:
      sort_ref = GetSortRefByName(DS_SORT_NAME_FREQUENCY);
      assert(sort_ref);
      break;

    //
    // Tally-Sensoren:
    //
    case DS_SENSOR_TALLY:
    case DS_SENSOR_PCS_QUEUE_LENGTH:
    case DS_SENSOR_PCS_WAITTIME_SIGNAL:
    case DS_SENSOR_PCS_WAITTIME_STATE:
    case DS_SENSOR_PCS_RESPONSETIME_REQUEST:
    case DS_SENSOR_PCS_TRANSMISSIONTIME_SIGNAL:
    case DS_SENSOR_MACH_COUNT_REQUEST:
    case DS_SENSOR_MACH_QUEUE_LENGTH:
    case DS_SENSOR_MACH_UTILIZATION:
    case DS_SENSOR_MACH_WAITTIME_REQUEST:
    case DS_SENSOR_MACH_SERVICETIME_REQUEST:
    case DS_SENSOR_SYS_LIFETIME_PROCESS:
      sort_ref = GetSortRefByName(DS_SORT_NAME_TALLY);
      assert(sort_ref);
      break;

    default:
      assert(DS_FALSE);
      return DS_ERROR;
   }
   
   return DS_OK;
}


DSObject *DSSensor::Clone (DSObject* father, DSObject* fill_this) const
{
  DSSensor *new_sensor;

  if (fill_this == NULL)
  {
    new_sensor = (DSSensor *)New(father);
    assert(new_sensor);
  }
  else
  {
    assert(fill_this->GetType() == DS_SENSOR);
    new_sensor = (DSSensor *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_sensor);

  new_sensor->SetType(GetType());

  return new_sensor;
}


DSResult DSSensor::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  (void)what;
  
  return DS_OK;
}
