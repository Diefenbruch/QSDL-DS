#ifndef _DSATOMCOMPONENT_H_
#define _DSATOMCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSAtomList.h"

/************************************************************************
 * Classname: DSAtomComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen QSDL-Atome
 *            definiert werden koennen.
 ************************************************************************/

class DSAtomComponent
{
  public:
    DSAtomComponent(class DSObject * = NULL);
   ~DSAtomComponent(void);

    DSAtomKeyList  *GetAtomList(void) const;
    class DSAtom   *GetAtom(DSString *) const;
    class DSAtom   *GetAtom(DSString&) const;
    class DSAtom   *GetAtom(const char *) const;
    class DSAtom   *GetFirstAtom(void) const;
    class DSAtom   *GetNextAtom(void) const;

    DSResult        SetAtomList(DSAtomKeyList *);
    DSResult        InsertAtom(class DSAtom *);

  protected:
    DSObject       *GetComponentParent(void) const;  // Vaterobject
    DSResult        SetComponentParent(const DSObject*);

  private:
    DSAtomKeyList  *atom_definition_list;
    class DSObject *parent;
};

#endif
