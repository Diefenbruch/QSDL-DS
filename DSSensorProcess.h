#ifndef DS_SENSORPROCESS_H_
#define DS_SENSORPROCESS_H_

#include "DSSensor.h"
#include "DSRef.h"
#include "DSProcessRefComponent.h"

/************************************************************************
 * Classname: DSSensorProcess
 * Purpose:   Definition eines Sensors fuer Prozesse
 ************************************************************************/

class DSSensorProcess : public DSSensor,
                        public DSProcessRefComponent
{
  public:
                DSSensorProcess (DSObject* = NULL,
                                 DSSensorType = DS_SENSOR_ILLEGAL,
                                 DSString* = NULL,
                                 DSProcessRefList* = NULL,
                                 DSExpression * = NULL); // Intervall
                DSSensorProcess (DSObject*,
                                 DSSensorType,
                                 DSString&,
                                 DSProcessRefList * = NULL,
                                 DSExpression * = NULL); // Intervall
                DSSensorProcess (DSObject*,
                                 DSSensorType,
                                 const char *,
                                 DSProcessRefList * = NULL,
                                 DSExpression * = NULL); // Intervall
               ~DSSensorProcess (void);

    DSObject    *New(DSObject * = NULL) const;
    DSObject    *Clone(DSObject * = NULL,
                       DSObject * = NULL) const;
};

#endif
