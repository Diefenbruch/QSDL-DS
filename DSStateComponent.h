#ifndef _DSSTATECOMPONENT_H_
#define _DSSTATECOMPONENT_H_

#include "DSBasicTypes.h"
#include "DSStateList.h"

/************************************************************************
 * Classname: DSStateComponent
 * Aufgabe:   Basisklasse fuer alle SDL-Strukturen in denen SDL-Zustaende
 *            definiert werden koennen.
 ************************************************************************/

class DSStateComponent
{
  protected:
    DSStateComponent(class DSObject * = NULL);

  public:
   ~DSStateComponent(void);

    class DSTransition *GetStartTransition(void) const;
    DSStateList        *GetStateList(void) const;
    class DSState      *GetState(class DSString*) const;
    class DSState      *GetState(class DSString&) const;
    class DSState      *GetState(const char *) const;
    class DSState      *GetFirstState(void) const;
    class DSState      *GetNextState(void) const;

    DSResult            SetStartTransition(class DSTransition*);
    DSResult            SetStateList(DSStateList*);
    DSResult            InsertState(class DSState*);

    // durch das Aufloesen von Decisions koennen neue
    // 'intermediate states' entstanden sein. Um die
    // eigentliche Anzahl von 'richtigen' Zustaenden
    // zu erhalten kann die folgende Funktion verwendet
    // werden:
    DSCardinal          NumberOfRealStates(void) const;
    
    // die folgenden Methoden fuegen die Informationen
    // welche die 'State *' enthalten den anderen
    // Zustaenden hinzu. Diese enthalten dafuer spezielle
    // Referenzlisten (asterisk_input_list und asterisk_save_list)
    DSResult            DissolveAsteriskStates(void);
    DSResult            DissolveAsteriskState(class DSState *);
    
  protected:
    DSObject           *GetComponentParent(void) const;  // Vaterobject
    DSResult            SetComponentParent(const DSObject*);

  private:
    class DSTransition *start_transition;
    DSStateList        *state_definition_list;
    class DSObject     *parent;
};

#endif
