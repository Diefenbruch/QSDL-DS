#ifndef _DSSENSORCOMPONENT_H_
#define _DSSENSORCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSSensorList.h"

/************************************************************************
 * Classname: DSSensorComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen QSDL-Sensoren
 *            definiert werden koennen.
 ************************************************************************/

class DSSensorComponent
{
  protected:
    DSSensorComponent(class DSObject * = NULL);

  public:
   ~DSSensorComponent(void);

    DSSensorKeyList *GetSensorList (void) const;
    class DSSensor  *GetSensor (class DSString*) const;
    class DSSensor  *GetSensor (class DSString&) const;
    class DSSensor  *GetSensor (const char *) const;
    class DSSensor  *GetFirstSensor (void) const;
    class DSSensor  *GetNextSensor (void) const;

    DSResult         SetSensorList (DSSensorKeyList*);
    DSResult         InsertSensor (class DSSensor*);

  protected:
    DSObject        *GetComponentParent(void) const;  // Vaterobject
    DSResult         SetComponentParent(const DSObject*);

  private:
    DSSensorKeyList *sensor_definition_list;
    class DSObject  *parent;
};

#endif
