#ifndef _DSLINKCOMPONENT_H_
#define _DSLINKCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSLinkList.h"

/************************************************************************
 * Classname: DSLinkComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen QSDL-Links
 *            definiert werden koennen.
 ************************************************************************/

class DSLinkComponent
{
  public:
    DSLinkComponent(class DSObject * = NULL);
   ~DSLinkComponent(void);

    DSLinkKeyList  *GetLinkList(void) const;
    class DSLink   *GetLink(class DSString*) const;
    class DSLink   *GetLink(class DSString&) const;
    class DSLink   *GetLink(const char *) const;
    class DSLink   *GetFirstLink(void) const;
    class DSLink   *GetNextLink(void) const;

    DSResult        SetLinkList(DSLinkKeyList*);
    DSResult        InsertLink(class DSLink*);

  protected:
    DSObject       *GetComponentParent(void) const;  // Vaterobject
    DSResult        SetComponentParent(const DSObject*);

  private:
    DSLinkKeyList  *link_definition_list;
    class DSObject *parent;
};

#endif
