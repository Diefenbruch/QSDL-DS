#ifndef _DSTIMERCOMPONENT_H_
#define _DSTIMERCOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSTimerList.h"

/************************************************************************
 * Classname: DSTimerComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Timer
 *            definiert werden koennen.
 ************************************************************************/

class DSTimerComponent
{
  protected:
    DSTimerComponent(class DSObject * = NULL);

  public:
   ~DSTimerComponent(void);

    DSTimerKeyList *GetTimerList(void) const;
    class DSTimer  *GetTimer(class DSString*) const;
    class DSTimer  *GetTimer(class DSString&) const;
    class DSTimer  *GetTimer(const char *) const;
    class DSTimer  *GetFirstTimer(void) const;
    class DSTimer  *GetNextTimer(void) const;

    DSResult        SetTimerList(DSTimerKeyList*);
    DSResult        InsertTimer(class DSTimer*);

    DSBoolean       HasTimerParams(void) const;

  protected:
    DSObject       *GetComponentParent(void) const;  // Vaterobject
    DSResult        SetComponentParent(const DSObject*);

  private:
    DSTimerKeyList *timer_definition_list;
    class DSObject *parent;
};

#endif
