/****************************************************************************
 *                 Modul: $RCSfile: DSSignalRoute.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer ein SDL-Signalroute bereit.
 *
 * Funktionen: GetName()         liefert den Signalroutennamen
 *             GetProcess1Ref()  liefert eine Referenz auf den ersten Process
 *             GetProcess2Ref()  liefert eine Referenz auf den ersten Process
 *             GetSignalList12() liefert Signalliste von Process1 -> Process2
 *             GetSignalList21() liefert Signalliste von Process2 -> Process1
 *             SetName()         setzt den Signalroutennamen
 *             SetProcess1Ref()  setzt die Refenrenz auf den ersten Process
 *             SetProcess2Ref()  setzt die Refenrenz auf den ersten Process
 *             SetSignalList12() setzt Signalliste von Process1 -> Process2
 *             SetSignalList21() setzt Signalliste von Process2 -> Process1
 ****************************************************************************/

#ifdef USE_PRAGMA
#pragma interface
#endif

/****************************************************************************
 * Konstanten
 ****************************************************************************/
 
/****************************************************************************
 * Include-Anweisungen
 ****************************************************************************/
 
#include "DSSignalRoute.h"
#include "DSBlock.h"        // wegen parent
#include "DSProcess.h"

#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Variablen
 ****************************************************************************/
 
/****************************************************************************
 * Globale Variablen
 ****************************************************************************/

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSSignalRoute::DSSignalRoute(DSObject *father,
                             DSString *n,
                             DSProcessRef p1,
                             DSProcessRef p2) :
  DSNamedObject(DS_SIGNALROUTE, n, father),
  process1_ref(p1),
  process2_ref(p2)
{
  p1_p2_signal_list = NULL;
  p2_p1_signal_list = NULL;

  if (father)
  {
    if (!GetName())
    {
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSignalRoute(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSSignalRoute::DSSignalRoute(DSObject *father,
                             DSString& n,
                             DSProcessRef p1,
                             DSProcessRef p2) :
  DSNamedObject(DS_SIGNALROUTE, n, father),
  process1_ref(p1),
  process2_ref(p2)
{
  p1_p2_signal_list = NULL;
  p2_p1_signal_list = NULL;

  if (father)
  {
    if (!GetName())
    {
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSignalRoute(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSSignalRoute::DSSignalRoute(DSObject *father,
                             const char *n,
                             DSProcessRef p1,
                             DSProcessRef p2) :
  DSNamedObject(DS_SIGNALROUTE, n, father),
  process1_ref(p1),
  process2_ref(p2)
{
  p1_p2_signal_list = NULL;
  p2_p1_signal_list = NULL;
  if (father)
  {
    if (!GetName())
    {
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSignalRoute(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSSignalRoute::~DSSignalRoute(void)
{
  if (p1_p2_signal_list) delete p1_p2_signal_list;
  if (p2_p1_signal_list) delete p2_p1_signal_list;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSSignalRoute::New(DSObject *father) const
{
  return new DSSignalRoute(father);
}

DSProcessRef DSSignalRoute::GetProcess1Ref(void) const
{
  return process1_ref;
}

DSProcessRef DSSignalRoute::GetProcess2Ref(void) const
{
  return process2_ref;
}

DSSignalItemList* DSSignalRoute::GetSignalList12(void) const
{
  return p1_p2_signal_list;
}

DSSignalItemList* DSSignalRoute::GetSignalList21(void) const
{
  return p2_p1_signal_list;
}

DSResult DSSignalRoute::SetProcess1Ref(DSProcessRef ref)
{
  process1_ref = ref;
  return DS_OK;
}

DSResult DSSignalRoute::SetProcess2Ref(DSProcessRef ref)
{
  process2_ref = ref;
  return DS_OK;
}

DSResult DSSignalRoute::SetSignalList12(DSSignalItemList *list)
{
  if (p1_p2_signal_list == list) return DS_OK;

  if (p1_p2_signal_list != NULL)
  {
    delete p1_p2_signal_list;
  }
  p1_p2_signal_list = list;
  return DS_OK;
}

DSResult DSSignalRoute::SetSignalList21(DSSignalItemList *list)
{
  if (p2_p1_signal_list == list)

  if (p2_p1_signal_list != NULL)
  {
    delete p2_p1_signal_list;
  }
  p2_p1_signal_list = list;
  return DS_OK;
}

DSObject *DSSignalRoute::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSignalRoute *new_signalroute;

  if (fill_this == NULL)
  {
    new_signalroute = (DSSignalRoute *)New(father);
    assert(new_signalroute);
  }
  else
  {
    assert(fill_this->GetType() == DS_SIGNALROUTE);
    new_signalroute = (DSSignalRoute *)fill_this;
    assert(new_signalroute);
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_signalroute);

  new_signalroute->SetProcess1Ref(GetProcess1Ref());
  new_signalroute->SetProcess2Ref(GetProcess2Ref());

  if (GetSignalList12())
  {
    new_signalroute->SetSignalList12((DSSignalItemList *)GetSignalList12()->Clone((DSObject *)new_signalroute));
  }

  if (GetSignalList21())
  {
    new_signalroute->SetSignalList21((DSSignalItemList *)GetSignalList21()->Clone((DSObject *)new_signalroute));
  }

  return new_signalroute;
}

DSResult DSSignalRoute::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}
