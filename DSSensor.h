#ifndef DS_SENSOR_H_
#define DS_SENSOR_H_

#include "DSBasicTypes.h"
#include "DSNamedObject.h"

/************************************************************************
 * Classname: DSSensor
 * Purpose:   Definition eines Sensors
 ************************************************************************/

class DSSensor : public DSNamedObject
{
  public:
                 DSSensor (DSObject* = NULL,
                           DSSensorType = DS_SENSOR_ILLEGAL,
                           DSString* = NULL,
                           DSExpression * = NULL);  // Intervall-Ausdruck
                 DSSensor (DSObject*,
                           DSSensorType,
                           DSString&,
                           DSExpression * = NULL);  // Intervall-Ausdruck
                 DSSensor (DSObject*,
                           DSSensorType,
                           const char *,
                           DSExpression * = NULL);  // Intervall-Ausdruck
                ~DSSensor(void);

    DSSensorType  GetType (void) const { return sensorType; }
    DSResult      SetType (DSSensorType sType) { sensorType = sType;
                                                 return DS_OK; }
    DSExpression *GetInterval(void) const;
    DSResult      SetInterval(DSExpression *);

    DSSortRef     GetSortRef(void) const;        // jeder Sensor hat eine Sorte
    DSResult      SetSortRef(DSSortRef = NULL);  // (Counter, Frequency oder Tally)

    DSObject     *Clone(DSObject * = NULL,
                        DSObject * = NULL) const;
    DSObject     *New(DSObject * = NULL) const;

    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    DSSensorType sensorType;
    DSExpression *interval;  // fuer Tally und Counter-Sensoren
    DSSortRef      sort_ref; // Verweis auf Counter-, Frequency oder
                             // Tally-Sorte (sind vordefiniert, siehe
                             // CGSystem::InitializeQSDLSorts()
};

#endif
