/****************************************************************************
 *                 Modul: $RCSfile: DSChannel.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/12/19 13:10:25 $
 * $Revision: 1.3 $
 * Aufgabe: Dieser Modul stellt Datenstruktur fuer ein SDL-Kanal bereit.
 *
 * Funktionen: GetBlock1Ref()    liefert eine Referenz auf den ersten Block
 *             GetBlock2Ref()    liefert eine Referenz auf den ersten Block
 *             GetSignalList12() liefert Signalliste von Block1 -> Block2
 *             GetSignalList21() liefert Signalliste von Block2 -> Block1
 *             SetBlock1Ref()    setzt die Refenrenz auf den ersten Block
 *             SetBlock2Ref()    setzt die Refenrenz auf den ersten Block
 *             SetSignalList12() setzt Signalliste von Block1 -> Block2
 *             SetSignalList21() setzt Signalliste von Block2 -> Block1
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
 
#include "DSChannel.h"
#include "DSSystem.h"   // wegen parent
#include "DSBlockSubstructure.h"  // wegen parent
#include "DSBlock.h"
#include "DSString.h"

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

DSChannel::DSChannel(DSObject *father,
                     DSString *n,
                     DSBoolean delay,
                     DSBlockRef b1_ref,
                     DSBlockRef b2_ref) :
  DSNamedObject(DS_CHANNEL, n, father),
  block1_ref(b1_ref),
  block2_ref(b2_ref),
  has_delay(delay)
{
  b1_b2_signal_list = NULL;
  b2_b1_signal_list = NULL;

  if (father)
  {
    if (!GetName())
    {
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertChannel(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertChannel(this);
        break;
      default:
        std::cerr << "Illegal parent for channel.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

DSChannel::DSChannel(DSObject *father,
                     DSString& n,
                     DSBoolean delay,
                     DSBlockRef b1_ref,
                     DSBlockRef b2_ref) :
  DSNamedObject(DS_CHANNEL, n, father),
  block1_ref(b1_ref),
  block2_ref(b2_ref),
  has_delay(delay)
{
  b1_b2_signal_list = NULL;
  b2_b1_signal_list = NULL;

  if (father)
  {
    if (!GetName())
    {
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertChannel(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertChannel(this);
        break;
      default:
        std::cerr << "Illegal parent for channel.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

DSChannel::DSChannel(DSObject *father,
                     const char *n,
                     DSBoolean delay,
                     DSBlockRef b1_ref,
                     DSBlockRef b2_ref) :
  DSNamedObject(DS_CHANNEL, n, father),
  block1_ref(b1_ref),
  block2_ref(b2_ref),
  has_delay(delay)
{
  b1_b2_signal_list = NULL;
  b2_b1_signal_list = NULL;

  if (father)
  {
    if (!GetName())
    {
      assert(DS_FALSE);
      return;
    }
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertChannel(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertChannel(this);
        break;
      default:
        std::cerr << "Illegal parent for channel.\n";
        assert(DS_FALSE);
        break;
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSChannel::~DSChannel(void)
{
  if (b1_b2_signal_list) delete b1_b2_signal_list;
  if (b2_b1_signal_list) delete b2_b1_signal_list;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSChannel::New(DSObject *father) const
{
  return new DSChannel(father);
}

DSBlockRef DSChannel::GetBlock1Ref(void) const
{
  return block1_ref;
}

DSBlockRef DSChannel::GetBlock2Ref(void) const
{
  return block2_ref;
}

DSSignalItemList* DSChannel::GetSignalList12(void) const
{
  return b1_b2_signal_list;
}

DSSignalItemList* DSChannel::GetSignalList21(void) const
{
  return b2_b1_signal_list;
}

DSBoolean DSChannel::GetHasDelay(void) const
{
  return has_delay;
}

DSResult DSChannel::SetBlock1Ref(DSBlockRef ref)
{
  block1_ref = ref;
  return DS_OK;
}

DSResult DSChannel::SetBlock2Ref(DSBlockRef ref)
{
  block2_ref = ref;
  return DS_OK;
}

DSResult DSChannel::SetSignalList12(DSSignalItemList *list)
{
  if (b1_b2_signal_list == list) return DS_OK;

  if (b1_b2_signal_list != NULL)
  {
    delete b1_b2_signal_list;
  }
  b1_b2_signal_list = list;
  return DS_OK;
}

DSResult DSChannel::SetSignalList21(DSSignalItemList *list)
{
  if (b2_b1_signal_list == list) return DS_OK;

  if (b2_b1_signal_list != NULL)
  {
    delete b2_b1_signal_list;
  }
  b2_b1_signal_list = list;
  return DS_OK;
}

DSResult DSChannel::SetHasDelay(DSBoolean delay)
{
  has_delay = delay;
  return DS_OK;
}

DSObject *DSChannel::Clone(DSObject *father, DSObject *fill_this) const
{
  DSChannel *new_channel;

  if (fill_this == NULL)
  {
    new_channel = (DSChannel *)New(father);
    assert(new_channel);
  }
  else
  {
    assert(fill_this->GetType() == DS_CHANNEL);
    new_channel = (DSChannel *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_channel);

  new_channel->SetBlock1Ref(GetBlock1Ref());
  new_channel->SetBlock2Ref(GetBlock2Ref());

  if (GetSignalList12())
  {
    new_channel->SetSignalList12((DSSignalItemList *)GetSignalList12()->Clone((DSObject *)new_channel));
  }

  if (GetSignalList21())
  {
    new_channel->SetSignalList21((DSSignalItemList *)GetSignalList21()->Clone((DSObject *)new_channel));
  }

  new_channel->SetHasDelay(GetHasDelay());

  return new_channel;
}

DSResult DSChannel::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (GetName()) GetName()->Write(writer, what);
  if (block1_ref) block1_ref->Write(writer, what);
  if (block2_ref) block2_ref->Write(writer, what);
  if (b1_b2_signal_list) b1_b2_signal_list->Write(writer, what);
  if (b2_b1_signal_list) b2_b1_signal_list->Write(writer, what);

  return DS_OK;
}
