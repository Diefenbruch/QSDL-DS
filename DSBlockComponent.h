#ifndef _DSBLOCKCOMPONENT_H_
#define _DSBLOCKCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSBlockList.h"

/************************************************************************
 * Classname: DSBlockComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Bloecke
 *            definiert werden koennen.
 ************************************************************************/

class DSBlockComponent
{
  public:
    DSBlockComponent(class DSObject * = NULL);
   ~DSBlockComponent(void);

    DSBlockKeyList *GetBlockList(void) const;
    class DSBlock  *GetBlock(DSString *) const;
    class DSBlock  *GetBlock(DSString&) const;
    class DSBlock  *GetBlock(const char *) const;
    class DSBlock  *GetFirstBlock(void) const;
    class DSBlock  *GetNextBlock(void) const;

    DSResult        SetBlockList(DSBlockKeyList *);
    DSResult        InsertBlock(class DSBlock *,
                                DSBoolean = DS_TRUE);

  protected:
    DSObject       *GetComponentParent(void) const;  // Vaterobject
    DSResult        SetComponentParent(const DSObject*);

  private:
    DSBlockKeyList *block_definition_list;
    class DSObject *parent;
};

#endif
