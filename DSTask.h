#ifndef _DSTASK_H_
#define _DSTASK_H_

#include "DSBasicTypes.h"
#include "DSAction.h"

/******************************************************************************
 * Klasse DSTask
 * Zweck: Datenstruktur zur Speicherung der Parameter fuer eine TASK-
 *        Instruktion.
 * Z100:  Seite 62
 ******************************************************************************/

class DSTask : public DSAction
{
  public:
    DSTask(DSObject* = NULL,       // Konstruktoren fuer Variablenzuweisung
           DSString* = NULL,
           class DSVariableAccess* = NULL,
           DSExpression* = NULL);
    DSTask(DSObject*,
           DSString&,
           class DSVariableAccess* = NULL,
           DSExpression* = NULL);
    DSTask(DSObject*,
           const char *,
           class DSVariableAccess* = NULL,
           DSExpression* = NULL);

    DSTask(DSObject*,              // Konstruktoren fuer 'informal text'
           DSString*,
           DSString*);
    DSTask(DSObject*,
           DSString&,
           DSString&);
    DSTask(DSObject*,
           const char*,
           const char*);

   ~DSTask(void);

    class DSVariableAccess *GetVariableAccess(void) const;
    class DSExpression     *GetExpression(void) const;
    DSString               *GetInformalText(void) const;

    DSResult          SetVariableAccess(class DSVariableAccess*);
    DSResult          SetExpression(class DSExpression*);
    DSResult          SetInformalText(DSString*);
    DSResult          SetInformalText(DSString&);
    DSResult          SetInformalText(const char*);

    DSObject *Clone(DSObject * = NULL, DSObject * = NULL) const;      // erzeugt eine identische
                                              // Kopie dieses Objekts

    /**************************************************/
    /* Die folgende Funktion dient zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur: */
    /**************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;

  private:
    class DSVariableAccess *variable_access;
    class DSExpression     *expression;
    DSString               *informal_text;
};

#endif  // ifndef
