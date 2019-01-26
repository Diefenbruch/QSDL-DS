#ifndef _DSNAMEDOBJECT_H_
#define _DSNAMEDOBJECT_H_

#include "DSObject.h"

/************************************************************************
 * Classname: DSNamedObject
 * Purpose:   Basisklasse fuer alle anderen Datenstruktur-Klassen mit Namen
 ************************************************************************/

class DSNamedObject : public DSObject
{
  protected:                // damit kein Object vom Type DSNamedObject
                            // erzeugt werden kann
    DSNamedObject(DSType,               // Objekttyp
                  class DSString* = NULL,     // Name
                  DSObject* = NULL);    // parent
    DSNamedObject(DSType,               // Objekttyp
                  class DSString&,      // Name
                  DSObject* = NULL);    // parent
    DSNamedObject(DSType,               // Objekttyp
                  const char * = NULL,  // Name
                  DSObject* = NULL);    // parent

  public:
   ~DSNamedObject(void);

    class DSString *GetName(void) const;
    virtual class DSString & GetIdentifier(void) const;

    DSResult  SetName(class DSString*);
    DSResult  SetName(class DSString&);
    DSResult  SetName(const char *);

    DSObject *Clone(DSObject * = NULL,
                    DSObject * = NULL) const;

  private:
    class DSString *name;
};

#endif
