#ifndef DS_SENSORSTATE_H_
#define DS_SENSORSTATE_H_

#include "DSSensor.h"
#include "DSRef.h"

/************************************************************************
 * Classname: DSSensorState
 * Purpose:   Definition eines Sensors mit State-Parameter
 ************************************************************************/

class DSSensorState : public DSSensor
{
  public:
                DSSensorState (DSObject* = NULL,
                               DSSensorType = DS_SENSOR_ILLEGAL,
                               DSString* = NULL,
                               DSStateRef = NULL,
                               DSExpression * = NULL);   // Intervall
                DSSensorState (DSObject*,
                               DSSensorType,
                               DSString&,
                               DSStateRef = NULL,
                               DSExpression * = NULL);   // Intervall
                DSSensorState (DSObject*,
                               DSSensorType,
                               const char *,
                               DSStateRef = NULL,
                               DSExpression * = NULL);   // Intervall
               ~DSSensorState (void);

    DSStateRef  GetStateRef (void) const;
    DSResult    SetStateRef (DSStateRef state);

    DSObject   *New(DSObject * = NULL) const;
    DSObject   *Clone(DSObject * = NULL,
                      DSObject * = NULL) const;
    
  private:
    DSStateRef state_ref;
};


#endif
