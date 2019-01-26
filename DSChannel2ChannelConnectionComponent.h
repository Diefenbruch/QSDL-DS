#ifndef _DSCHANNEL2CHANNELCONNECTIONCOMPONENT_H_
#define _DSCHANNEL2CHANNELCONNECTIONCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSChannel2ChannelConnectionList.h"

/************************************************************************
 * Classname: DSChannel2ChannelConnectionComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Kanaele
 *            verbunden werden koennen.
 ************************************************************************/

class DSChannel2ChannelConnectionComponent
{
  public:
    DSChannel2ChannelConnectionComponent(class DSObject * = NULL); // parent
   ~DSChannel2ChannelConnectionComponent(void);

    DSChannel2ChannelConnectionList   *GetChannel2ChannelConnectionList(void) const;
    class DSChannel2ChannelConnection *GetFirstChannel2ChannelConnection(void) const;
    class DSChannel2ChannelConnection *GetNextChannel2ChannelConnection(void) const;

    DSResult                       SetChannel2ChannelConnectionList
                                    (DSChannel2ChannelConnectionList*);
    DSResult                       InsertChannel2ChannelConnection
                                    (class DSChannel2ChannelConnection*);

  protected:
    DSObject           *GetComponentParent(void) const;  // Vaterobject
    DSResult            SetComponentParent(const DSObject*);

  private:
    DSChannel2ChannelConnectionList *channel2channel_connection_list;
    class DSObject                  *parent;
};

#endif
