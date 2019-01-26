/****************************************************************************
 *                 Modul: $RCSfile: DSOutput.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.3 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Parameter, die in Verbindung mit einem
 *          OUTPUT-Befehl angegeben sind
 *
 * Funktionen: GetSignalRef(): Gibt eine Referenz auf das Signal zurueck
 *             GetProcessID(): Liefert Zielprozess (TO)
 *             SetSignal(): Speichert den uebergebenen Zeiger
 *             SetProcessID(): s. o.
 *             SetChannelList(): s. o.
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

#include "DSOutput.h"
#include "DSProcess.h" // wegen GetSignalDestination()
#include "DSBlock.h" // wegen GetSignalDestination()
#include "DSChannel2RouteConnection.h" // wegen GetSignalDestination()
#include "DSChannel.h"
#include "DSExpression.h"
#include "DSSignal.h"

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

DSOutput::DSOutput(DSObject          *father,
                   DSString          *label_name, 
                   DSSignalRef        signal, 
                   DSActualParamList *p_list) :
  DSAction(father, DS_OUTPUT, label_name),
  DSActualParamComponent(NULL, p_list),
  signal_ref(signal)
{
  DSActualParamComponent::SetComponentParent(this);

  to_pid = NULL;
  delay = NULL;
}

DSOutput::DSOutput(DSObject          *father,
                   DSString&          label_name, 
                   DSSignalRef        signal, 
                   DSActualParamList *p_list) :
  DSAction(father, DS_OUTPUT, &label_name),
  DSActualParamComponent(NULL, p_list),
  signal_ref(signal)
{
  DSActualParamComponent::SetComponentParent(this);

  to_pid = NULL;
  delay = NULL;
}

DSOutput::DSOutput(DSObject          *father,
                   const char        *label_name, 
                   DSSignalRef        signal, 
                   DSActualParamList *p_list) :
  DSAction(father, DS_OUTPUT, label_name),
  DSActualParamComponent(NULL, p_list),
  signal_ref(signal)
{
  DSActualParamComponent::SetComponentParent(this);

  to_pid = NULL;
  delay = NULL;
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSOutput::~DSOutput(void)
{
  if (to_pid) delete to_pid;
  if (delay) delete delay;
}

/****************************************************************************
 * GetSignalRef(): Liefert das Signal des OUTPUT-Befehls zurueck
 *                 Ergebnis: Zeiger auf ein Signal
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSSignalRef DSOutput::GetSignalRef(void) const
{
  return signal_ref;
}

/****************************************************************************
 * GetProcessID(): Liefert den Zielprozess des OUTPUT-Befehls zurueck
 *                 Ergebnis: PID-Ausdruck
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSExpression* DSOutput::GetProcessID(void) const
{
  return to_pid;
}

DSExpression* DSOutput::GetDelay(void) const
{
  return delay;
}

DSBoolean DSOutput::IsChannelAllowed(DSChannelRef search_channel) const
{
  DSChannelRef channel;

  if (GetChannelRefList() == NULL)          // keine Routingeinschraenkung?
  {
    return DS_TRUE;
	}

  for (channel = GetFirstChannelRef();
       channel != NULL;
       channel = GetNextChannelRef())
  {
    if (channel == search_channel)
    {
      return DS_TRUE;
		}
	}
  return DS_FALSE;
}

DSBoolean DSOutput::IsSignalRouteAllowed(DSSignalRouteRef search_route) const
{
  DSSignalRouteRef route;

  if (GetSignalRouteRefList() == NULL)          // keine Routingeinschraenkung?
  {
    return DS_TRUE;
	}

  for (route = GetFirstSignalRouteRef();
       route != NULL;
       route = GetNextSignalRouteRef())
  {
    if (route == search_route)
    {
      return DS_TRUE;
		}
	}
  return DS_FALSE;
}

/****************************************************************************
 * GetSignalDestination(): Liefert den Prozesstyp, zu dem der Output
 *                         geroutet wird.
 *                         Ergebnis: Zeiger auf den Zielprozesstyp (DSProcess)
 *                         Seiteneffekte: keine
 ****************************************************************************/

DSProcessRefList *DSOutput::GetSignalDestination(void) const
{
  DSProcessRefList     *destinations = NULL;
  DSProcessRef          process;
  DSBlockRef            block;
  DSBlockRef            destination_block = NULL;
  DSBlockRefList       *block_list;
  DSSignalItemList     *signal_item_list;
  DSSignalRouteRef      route;
  DSSignalRouteRefList *route_list;
  DSChannelRef          channel;
  DSChannelRefList     *channel_list;
  DSChannelRefList     *block_channel_list;
  DSChannel2RouteConnection *connection;
  DSResult              status, status2;

  process = GetThisProcess();
  assert(process);

  block = (DSBlock*)(process->GetParent());   // DS_BLOCK

  if (!block) return NULL;
  assert(block->GetType() == DS_BLOCK);

  route_list = new DSSignalRouteRefList;     // alle geeigneten Routen
                                             // werden in route_list
                                             // gespeichert
  assert(route_list != NULL);

  /***********************************************************/
  /* Alle Signalrouten des Vaterblocks durchsuchen, ob der   */
  /* Sendeprozess als ein Endpunkt vorkommt:                 */
  /***********************************************************/
  for (route = block->GetFirstSignalRoute();
       route != NULL;
       route = block->GetNextSignalRoute())
  {
    /*************************************************/
    /* Signalliste  fuer die richte Richtung suchen: */
    /*************************************************/
    if (route->GetProcess1Ref() == process)
    {
      signal_item_list = route->GetSignalList12();
      if (signal_item_list == NULL)
      {
        // Signalroute ist unidirektional und fuehrt in
        // die falsche Richtung!
        continue;
      }
    }
    else if (route->GetProcess2Ref() == process)
    {
      signal_item_list = route->GetSignalList21();
      if (signal_item_list == NULL)
      {
        // Signalroute ist unidirektional und fuehrt in
        // die falsche Richtung!
        continue;
      }
    }
    else
    {
      continue;    // aktuelle Route ist nicht mit Sendeprozess verbunden!
    }

    /*************************************************/
    /* Pruefen, ob die Signalroutenauswahl durch via */
    /* erlaubt wurde und das Output-Signal in der    */
    /* Signalliste der Signalroute vorkommt:         */
    /*************************************************/
    if (IsSignalRouteAllowed(route) &&
        signal_item_list->IsSignalRefInList(signal_ref))
    {
      assert (route_list->Append(route) == DS_OK);
    } // if
  } // for (Suchen der passenden Signalrouten)

  if (route_list->IsEmpty())          // keine passenden Routen
  {                                   // gefunden?
    delete route_list;
//    cout << "Can't find useable signalroute for sending process '"
//         << process->GetName() << "' !" << endl;
    return NULL;
  }

  destinations = new DSProcessRefList;
  assert(destinations != NULL);

  /*********************************************************/
  /* Jetzt erst mal die Prozesse als Empfaenger raussuchen */
  /* die im gleichen Block wie der Sender liegen:          */
  /*********************************************************/
  for (status = route_list->MoveFirst();
       status == DS_OK;
       status = route_list->MoveNext())
  {
    route = route_list->GetCurrentData();
    assert(route != NULL);
    if (route->GetProcess1Ref() == process &&
        route->GetProcess2Ref() != NULL)        // NULL = ENV !
    {
      assert(destinations->Append(route->GetProcess2Ref()) == DS_OK);
      route_list->DeleteElement();
      if (route_list->IsEmpty())
      {
        break;
      }
    }
    else if (route->GetProcess2Ref() == process &&
             route->GetProcess1Ref() != NULL)
    {
      assert(destinations->Append(route->GetProcess1Ref()) == DS_OK);
      route_list->DeleteElement();
    }
  }

  /***************************************************************/
  /* Sind keine Signalrouten uebriggeblieben, die ans ENV gehen? */
  /***************************************************************/
  if (route_list->IsEmpty())
  {
     delete route_list;
     if (destinations->IsEmpty())
     {
//       cout << "Can't find useable receiving process in sending block '"
//            << block->GetName() << "'" << endl;
       delete destinations;
       return NULL;
     }
     return destinations;
  }

  /***********************************************/
  /* Es gibt Empfaenger ausserhalb des Blockes!! */
  /***********************************************/
  channel_list = new DSChannelRefList;   // alle geeigneten Kanaele
                                         // werden in channel_list gespeichert
  assert(channel_list != NULL);

  /*********************************************************/
  /* Alle Channel2RouteConnections des Blocks durchsuchen, */
  /* ob eine der Signalrouten ans ENV in ihnen vorkommt:   */
  /*********************************************************/
  for (connection = block->GetFirstChannel2RouteConnection();
       connection != NULL;
       connection = block->GetNextChannel2RouteConnection())
  {
    for (status = route_list->MoveFirst();
         status == DS_OK;
         status = route_list->MoveNext())
    {
      route = route_list->GetCurrentData();
      assert(route != NULL);
      /*******************************************************/
      /* Feststellen ob in aktueller Connection die aktuelle */
      /* Signalroute vorkommt:                               */
      /*******************************************************/
      if (connection->IsSignalRouteConnected(route))
      {
        /*********************************************************/
        /* alle Kanaele der Verbindung auf Eignung ueberpruefen: */
        /*********************************************************/
        for (channel = connection->GetFirstChannelRef();
             channel != NULL;
             channel = connection->GetNextChannelRef())
        {
          /********************************************************/
          /* Sicherstellen, dass Kanaele nicht ueber verschiedene */
          /* Connections mehrfach eingefuegt werden:              */
          /********************************************************/
/*          if (channel_list->IsInList(channel) == DS_TRUE)
          {
            continue;
          }*/
          /*************************************************/
          /* Signalliste  fuer die richte Richtung suchen: */
          /*************************************************/
          if (channel->GetBlock1Ref() == block)
          {
            signal_item_list = channel->GetSignalList12();
            if (signal_item_list == NULL)
            {
              // Kanal ist unidirektional und fuehrt in
              // die falsche Richtung!
              continue;
            }
          }
          else  // Block2Ref ist Sendeblock!
          {
            assert(channel->GetBlock2Ref() == block);
            signal_item_list = channel->GetSignalList21();
            if (signal_item_list == NULL)
            {
              // Kanal ist unidirektional und fuehrt in
              // die falsche Richtung!
              continue;
            }
          }

          /******************************************/
          /* Pruefen, ob die Kanalauswahl durch via */
          /* erlaubt wurde und das Output-Signal in */
          /* der Signalliste des Knals vorkommt:    */
          /******************************************/
          if (IsChannelAllowed(channel) &&
              signal_item_list->IsSignalRefInList(signal_ref))
          {
            assert (channel_list->Append(channel) == DS_OK);
          } // if channel gueltig und kann Singal uebertragen
        }  // for  (alle angebundenen Kanaele)
      }  // if (Signalroute kommt in Verbindung vor)
    }  // for (alle Signalrouten durchlaufen)
  }  // for (alle Verbindungen durchlaufen)

  if (route_list)
  {
    delete route_list;
    route_list = NULL;
	}

  if (channel_list->IsEmpty())        // keine passenden Kanaele
  {                                   // gefunden?
    delete channel_list;
    if (destinations->IsEmpty())
    {
//      cout << "Can't find useable channels for sending block '"
//           << block->GetName() << "' !" << endl;
      delete destinations;
      return NULL;
    }
    return destinations;
  }

  /***********************************/
  /* alle Empfangsbloecke bestimmen: */
  /***********************************/
  block_list = new DSBlockRefList;   // alle geeigneten Bloecke
                                     // werden in block_list gespeichert
  assert(block_list != NULL);

  block_channel_list = new DSChannelRefList;
                                     // speichert ueber welchen Kanal die
                                     // Bloecke erreicht werden
  assert(block_channel_list != NULL);

  /**************************************/
  /* Alle passenden Kanaele durchlaufen */
  /* und die zugehoerigen Zielbloecke   */
  /* ermitteln:                         */
  /**************************************/
  for (status = channel_list->MoveFirst();
       status == DS_OK;
       status = channel_list->MoveNext())
  {
    channel = channel_list->GetCurrentData();
    assert(channel != NULL);
    /*************************************************/
    /* Signalliste  fuer die richte Richtung suchen: */
    /*************************************************/
    if (channel->GetBlock1Ref() == block)
    {
      destination_block = channel->GetBlock2Ref();
    }
    else if (channel->GetBlock2Ref() == block)
    {
      destination_block = channel->GetBlock1Ref();
    }
    // Wenn destination_block = Null dann ist
    // es ein Kanal ans Environment!!
    assert (block_list->Append(destination_block) == DS_OK);
    assert (block_channel_list->Append(channel) == DS_OK);
  } // for (Suchen der passenden Zielbloecke)

  if (channel_list)
  {
    delete channel_list;
    channel_list = NULL;
	}

  if (block_list->IsEmpty())        // keine passenden Zielbloecke
  {                                 // gefunden?
    delete block_list;
    delete block_channel_list;
    if (destinations->IsEmpty())
    {
//      cout << "Can't find useable receiving block !" << endl;
      delete destinations;
      return NULL;
    }
    return destinations;
  }

  route_list = new DSSignalRouteRefList;     // alle geeigneten Routen
                                             // werden in route_list
                                             // gespeichert
  assert(route_list != NULL);

  /******************************************************************/
  /* Alle Zielbloecke durchlaufen und passende Signalrouten suchen: */
  /******************************************************************/

  for (status = block_list->MoveFirst(),
       status2 = block_channel_list->MoveFirst();
       status == DS_OK && status2 == DS_OK;
       status = block_list->MoveNext(),
       status2 = block_channel_list->MoveNext())
  {
    destination_block = block_list->GetCurrentData();
    if (destination_block == NULL) // Signal an die Systemumgebung?
    {
      continue;
    }
    channel = block_channel_list->GetCurrentData();
    assert(channel != NULL);

    for (connection = destination_block->GetFirstChannel2RouteConnection();
         connection != NULL;
         connection = destination_block->GetNextChannel2RouteConnection())
    {
      /*********************************************************/
      /* Feststellen, ob die Connection den Uebertragungskanal */
      /* des Output-Signals enthaelt:                          */
      /*********************************************************/
      if (connection->IsChannelConnected(channel))
      {
        break; // for-Schleife abbrechen, da Uebertragungskanal
               // nur einmal vorkommen kann!
      }
    }

    if (connection == NULL)  // keine Verbindung fuer aktuellen Kanal
                             // gefunden? (dann ist diese connection
                             // uninteressant!)
    {
      continue;
    }

    /********************************************************/
    /* Alle Signalrouten der Connection auf Eignung testen: */
    /********************************************************/
    for (route = connection->GetFirstSignalRouteRef();
         route  != NULL;
         route = connection->GetNextSignalRouteRef())
    {
      /*************************************************/
      /* Signalliste  fuer die richte Richtung suchen: */
      /*************************************************/
      if (route->GetProcess1Ref() == NULL)    // NULL = ENV!!
      {
        signal_item_list = route->GetSignalList12();
        if (signal_item_list == NULL)
        {
          // Signalroute ist unidirektional und fuehrt in
          // die falsche Richtung!
          continue;
        }
      }
      else
      {
        assert(route->GetProcess2Ref() == NULL);
        signal_item_list = route->GetSignalList21();
        if (signal_item_list == NULL)
        {
          // Signalroute ist unidirektional und fuehrt in
          // die falsche Richtung!
          continue;
        }
      }

      /*************************************************/
      /* Pruefen, ob die Signalroutenauswahl durch via */
      /* erlaubt wurde und das Output-Signal in der    */
      /* Signalliste der Signalroute vorkommt:         */
      /*************************************************/
      if ( /* IsSignalRouteAllowed(route) && */
          signal_item_list->IsSignalRefInList(signal_ref))
      {
        assert (route_list->Append(route) == DS_OK);
      } // if Signalroute erlaubt und Signal uebertragbar
    } // for (Suchen der passenden Signalrouten)
  }  // for (Durchlauf der Zielbloecke)

  if (route_list->IsEmpty())          // keine passenden Routen im
  {                                   // Zielblock gefunden?
    delete route_list;
    if (destinations->IsEmpty())
    {
//      cout << "Can't find receiving process in destination block ! " << endl;
      delete destinations;
      return NULL;
    }
    return destinations;
  }

  /*********************************************************/
  /* Zu guter letzt die Prozesse als Empfaenger raussuchen */
  /* die in den Zielbloecken liegen:                       */
  /*********************************************************/
  for (status = route_list->MoveFirst();
       status == DS_OK;
       status = route_list->MoveNext())
  {
    route = route_list->GetCurrentData();
    assert(route != NULL);

    if (route->GetProcess1Ref() == NULL)   // NULL = env !
    {
      assert(destinations->Append(route->GetProcess2Ref()) == DS_OK);
    }
    else if (route->GetProcess2Ref() == NULL)  // NULL = env
    {
      assert(destinations->Append(route->GetProcess1Ref()) == DS_OK);
    }
  }

  if (block_list) delete block_list;
  if (block_channel_list) delete block_channel_list;
  if (route_list) delete route_list;

  return destinations;
}

/****************************************************************************
 * SetSignalRef(): Speichert den uebergebenen Zeiger
 *                 -> sig: Zeiger auf ein Signal
 *                 Ergebnis: DS_OK
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOutput::SetSignalRef(DSSignalRef sig)
{
  signal_ref = sig;
  return DS_OK;
}

/****************************************************************************
 * SetProcessID(): Speichert die uebergebene PID
 *              -> proc_id: Zeiger auf einen String, der den Namen des Ziel-
 *                          Prozesses enthaelt. Das Routing erfolgt ggf. zur
 *                          Laufzeit durch Suche in der Schluesselliste der
 *                          Prozesse, falls kein VIA-Konstrukt im OUTPUT
 *                          enthalten ist
 *              Ergebnis: DS_OK
 *              Seiteneffekte: keine
 ****************************************************************************/

DSResult DSOutput::SetProcessID(DSExpression *p_id)
{
  if (to_pid == p_id) return DS_OK;

  if (to_pid) delete to_pid;
  to_pid = p_id;

  if (to_pid != NULL)
  {
    if (to_pid->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      to_pid->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSOutput::SetDelay(DSExpression *p_delay)
{
  if (delay == p_delay) return DS_OK;

  if (delay) delete delay;
  delay = p_delay;

  if (delay != NULL)
  {
    if (delay->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      delay->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSOutput::Clone(DSObject *father, DSObject *fill_this) const
{
  DSOutput *new_output;

  if (fill_this == NULL)
  {
    new_output = (DSOutput *)New(father);
    assert(new_output);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_output = (DSOutput *)fill_this;
  }

  // Basisklasse clonen:
  DSAction::Clone(father, new_output);

  if (GetActualParamList())
  {
    new_output->SetActualParamList(GetActualParamList()->Clone((DSObject *)new_output));
  }
  
  if (GetSignalRouteRefList())
  {
    new_output->SetSignalRouteRefList((DSSignalRouteRefList *)GetSignalRouteRefList()->Clone((DSObject *)new_output));
  }
  
  if (GetChannelRefList())
  {
    new_output->SetChannelRefList((DSChannelRefList *)GetChannelRefList()->Clone((DSObject *)new_output));
  }
  
  if (GetSignalRef())
  {
    new_output->SetSignalRef(GetSignalRef());  // do not clone!
  }

  if (GetProcessID())
  {
    new_output->SetProcessID((DSExpression *)GetProcessID()->Clone((DSObject *)new_output));
  }

  if (GetDelay())
  {
    new_output->SetDelay((DSExpression *)GetDelay()->Clone((DSObject *)new_output));
  }

  return new_output;
}

DSResult DSOutput::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (signal_ref) signal_ref->Write(writer, what);
  Run(writer, DS_ACTUALPARAM, what);
  if (to_pid) to_pid->Write(writer, what);
  Run(writer, DS_SIGNALROUTE, what);
  Run(writer, DS_CHANNEL, what);

  return DS_OK;
}

DSResult DSOutput::Run(DSWriter *writer, DSType object_type,
                       DSCardinal what) const
{
  DSResult         result;
  DSActualParam   *actual_param;
  DSChannelRef     channel;
  DSSignalRouteRef signal_route;

  switch(object_type)
  {
    case DS_ACTUALPARAM:
      for (actual_param = GetFirstActualParam();
           actual_param;
           actual_param = GetNextActualParam())
      {
        result = actual_param->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_CHANNEL:
      for (channel = GetFirstChannelRef();
           channel;
           channel = GetNextChannelRef())
      {
        result = channel->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_SIGNALROUTE:
      for (signal_route = GetFirstSignalRouteRef();
           signal_route;
           signal_route = GetNextSignalRouteRef())
      {
        result = signal_route->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    default:
      assert(DS_FALSE);
      break;
  }

  return DS_OK;
}
