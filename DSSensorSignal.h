#ifndef DS_SENSORSIGNAL_H_
#define DS_SENSORSIGNAL_H_

#include "DSSensor.h"
#include "DSRef.h"
#include "DSSignalRefComponent.h"

/************************************************************************
 * Classname: DSSensorSignal
 * Purpose:   Definition eines Sensors fuer Requests
 ************************************************************************/

class DSSensorSignal : public DSSensor,
                       public DSSignalRefComponent
{
  public:
                DSSensorSignal (DSObject* = NULL,
                                DSSensorType = DS_SENSOR_ILLEGAL,
                                DSString* = NULL,
                                DSSignalRefList * = NULL,
                                DSExpression * = NULL);  // Intervall
                DSSensorSignal (DSObject*,
                                DSSensorType,
                                DSString&,
                                DSSignalRefList * = NULL,
                                DSExpression * = NULL);  // Intervall);
                DSSensorSignal (DSObject*,
                                DSSensorType,
                                const char *,
                                DSSignalRefList * = NULL,
                                DSExpression * = NULL);  // Intervall);
               ~DSSensorSignal (void);

    DSObject   *New(DSObject * = NULL) const;
    DSObject   *Clone(DSObject * = NULL,
                      DSObject * = NULL) const;      // erzeugt identische
                                                     // Kopie dieses Objekts
};


#endif
