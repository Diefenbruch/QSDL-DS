#ifndef _DSCHANNELCOMPONENT_H_
#define _DSCHANNELCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSChannelList.h"

/************************************************************************
 * Classname: DSChannelComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Kanaele
 *            definiert werden koennen.
 ************************************************************************/

class DSChannelComponent
{
  public:
    DSChannelComponent(class DSObject * = NULL); // parent
   ~DSChannelComponent(void);

    DSChannelKeyList *GetChannelList(void) const;
    class DSChannel  *GetChannel(class DSString*) const;
    class DSChannel  *GetChannel(class DSString&) const;
    class DSChannel  *GetChannel(const char *) const;
    class DSChannel  *GetFirstChannel(void) const;
    class DSChannel  *GetNextChannel(void) const;

    DSResult          SetChannelList(DSChannelKeyList*);
    DSResult          InsertChannel(DSChannel*);

  protected:
    DSObject         *GetComponentParent(void) const;  // Vaterobject
    DSResult          SetComponentParent(const DSObject*);

  private:
    DSChannelKeyList *channel_definition_list;
    class DSObject   *parent;
};

#endif
