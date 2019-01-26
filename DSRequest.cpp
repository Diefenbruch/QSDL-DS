/****************************************************************************
 *                 Modul: $RCSfile: DSRequest.cpp,v $
 *
 * $Author: md $
 * $Date: 1998/01/13 12:48:22 $
 * $Revision: 1.3 $
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          der Parameter, die in Verbindung mit einem QSDL-Request-Befehl
 *          angegeben sind
 *
 * Funktionen:
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

#include "DSRequest.h"
#include "DSProcess.h" // wegen GetMachineServiceDestination()
#include "DSBlock.h" // wegen GetMachineServiceDestination()
#include "DSPipe.h" // wegen GetMachineServiceDestination()
#include "DSLink.h" // wegen GetMachineServiceDestination()
#include "DSPipe2LinkBinding.h" // wegen GetMachineServiceDestination()
#include "DSMachine.h"
#include "DSExpression.h"

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

DSRequest::DSRequest(DSObject            *father,
                     DSString            *label_name, 
                     DSMachineServiceRef req_service,
                     DSExpression        *amount,
                     DSExpression        *prio,
                     DSLinkRefList      *via_links,
                     DSPipeRefList      *via_pipes) :
  DSAction(father, DS_REQUEST, label_name),
  DSLinkRefComponent(via_links),
  DSPipeRefComponent(via_pipes),
  service_ref(req_service),
  service_amount(amount),
  priority(prio)
{
  machine_ref = NULL;

  if (service_amount)
  {
    if (service_amount->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      service_amount->SetParent(this);
    }
  }
  if (priority)
  {
    if (priority->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      priority->SetParent(this);
    }
  }
}

DSRequest::DSRequest(DSObject            *father,
                     DSString&            label_name, 
                     DSMachineServiceRef req_service,
                     DSExpression        *amount,
                     DSExpression        *prio,
                     DSLinkRefList      *via_links,
                     DSPipeRefList      *via_pipes) :
  DSAction(father, DS_REQUEST, &label_name),
  DSLinkRefComponent(via_links),
  DSPipeRefComponent(via_pipes),
  service_ref(req_service),
  service_amount(amount),
  priority(prio)
{
  machine_ref = NULL;

  if (service_amount)
  {
    if (service_amount->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      service_amount->SetParent(this);
    }
  }
  if (priority)
  {
    if (priority->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      priority->SetParent(this);
    }
  }
}

DSRequest::DSRequest(DSObject            *father,
                     const char          *label_name, 
                     DSMachineServiceRef req_service,
                     DSExpression        *amount,
                     DSExpression        *prio,
                     DSLinkRefList      *via_links,
                     DSPipeRefList      *via_pipes) :
  DSAction(father, DS_REQUEST, label_name),
  DSLinkRefComponent(via_links),
  DSPipeRefComponent(via_pipes),
  service_ref(req_service),
  service_amount(amount),
  priority(prio)
{
  machine_ref = NULL;

  if (service_amount)
  {
    if (service_amount->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      service_amount->SetParent(this);
    }
  }
  if (priority)
  {
    if (priority->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      priority->SetParent(this);
    }
  }
}

// Konstruktoren fuer FROM-Syntax:

DSRequest::DSRequest(DSObject            *father,
                     DSString            *label_name, 
                     DSMachineServiceRef req_service,
                     DSExpression        *amount,
                     DSExpression        *prio,
                     DSMachineRef         mach):
  DSAction(father, DS_REQUEST, label_name),
  service_ref(req_service),
  service_amount(amount),
  priority(prio),
  machine_ref(mach)
{
  if (service_amount)
  {
    if (service_amount->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      service_amount->SetParent(this);
    }
  }
  if (priority)
  {
    if (priority->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      priority->SetParent(this);
    }
  }
}

DSRequest::DSRequest(DSObject            *father,
                     DSString&            label_name, 
                     DSMachineServiceRef req_service,
                     DSExpression        *amount,
                     DSExpression        *prio,
                     DSMachineRef         mach):
  DSAction(father, DS_REQUEST, &label_name),
  service_ref(req_service),
  service_amount(amount),
  priority(prio),
  machine_ref(mach)
{
  if (service_amount)
  {
    if (service_amount->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      service_amount->SetParent(this);
    }
  }
  if (priority)
  {
    if (priority->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      priority->SetParent(this);
    }
  }
}

DSRequest::DSRequest(DSObject            *father,
                     const char          *label_name, 
                     DSMachineServiceRef req_service,
                     DSExpression        *amount,
                     DSExpression        *prio,
                     DSMachineRef         mach):
  DSAction(father, DS_REQUEST, label_name),
  service_ref(req_service),
  service_amount(amount),
  priority(prio),
  machine_ref(mach)
{
  if (service_amount)
  {
    if (service_amount->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      service_amount->SetParent(this);
    }
  }
  if (priority)
  {
    if (priority->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      priority->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSRequest::~DSRequest(void)
{
  if (service_amount) delete service_amount;
  if (priority) delete priority;
}

/****************************************************************************
 * GetMachineServiceRef(): Liefert Zeiger auf den Diensttyp
 *                         Ergebnis: Zeiger auf einen Diensttyp
 *                         Seiteneffekte: keine
 ****************************************************************************/

DSMachineServiceRef DSRequest::GetMachineServiceRef(void) const
{
  return service_ref;
}

/****************************************************************************
 * GetMachineRef(): Liefert Zeiger auf die Maschine (bei FROM-Syntax)
 *                  Ergebnis: Zeiger auf eine Maschine
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSMachineRef DSRequest::GetMachineRef(void) const
{
  return machine_ref;
}

/****************************************************************************
 * GetMachineServiceAmount(): Liefert den Bedienwunsch des Requests
 *                            Ergebnis: Zeiger auf einen Ausdruck
 *                            Seiteneffekte: keine
 ****************************************************************************/

DSExpression *DSRequest::GetMachineServiceAmount(void) const
{
  return service_amount;
}

/****************************************************************************
 * GetPriority(): Liefert den Prioritaet des Requests
 *                Ergebnis: Prioritaet
 *                Seiteneffekte: keine
 ****************************************************************************/

DSExpression *DSRequest::GetPriority(void) const
{
  return priority;
}

DSBoolean DSRequest::IsPipeAllowed(DSPipeRef search_pipe) const
{
  DSPipeRef pipe;

  if (GetPipeRefList() == NULL)          // keine Routingeinschraenkung?
  {
    return DS_TRUE;
  }

  for (pipe = GetFirstPipeRef();
       pipe != NULL;
       pipe = GetNextPipeRef())
  {
    if (pipe == search_pipe)
    {
      return DS_TRUE;
    }
  }
  return DS_FALSE;
}

DSBoolean DSRequest::IsLinkAllowed(DSLinkRef search_link) const
{
  DSLinkRef link;

  if (GetLinkRefList() == NULL)          // keine Routingeinschraenkung?
  {
    return DS_TRUE;
  }

  for (link = GetFirstLinkRef();
       link != NULL;
       link = GetNextLinkRef())
  {
    if (link == search_link)
    {
      return DS_TRUE;
    }
  }
  return DS_FALSE;
}

/****************************************************************************
 * GetMachineServiceDestination(): Liefert die Maschine, welche den Request
 *                                 ausfuehrt.
 *                                 Ergebnis: Zeiger auf die Maschinenliste
 *                                           Liste weil Routing eventuell
 *                                           nicht eindeutig
 *                                 Seiteneffekte: keine
 ****************************************************************************/

DSMachineRefList *DSRequest::GetMachineServiceDestination(void) const
{
  DSMachineRefList   *destinations = NULL;
  DSProcessRef         process_ref;
  DSBlock            *block;
  DSBlockRef          destination_block = NULL;
  DSBlockRefList     *block_list;
  DSLinkRef           link;
  DSLinkRefList      *link_list;
  DSPipeRef           pipe;
  DSPipeRefList      *pipe_list;
  DSPipeRefList      *block_pipe_list;
  DSPipe2LinkBinding *binding;
  DSResult             status, status2;

  process_ref = GetThisProcess();
  assert(process_ref);

  block = (DSBlock*)(process_ref->GetParent());   // DS_BLOCK

  if (!block) return NULL;
  assert(block->GetType() == DS_BLOCK);

  link_list = new DSLinkRefList;      // alle geeigneten Links
                                      // werden in link_list
                                      // gespeichert
  assert(link_list != NULL);

  /****************************************************/
  /* Alle Links des Blocks durchsuchen, ob der Sende- */
  /* prozess als ein Endpunkt vorkommt:               */
  /****************************************************/
  for (link = block->GetFirstLink();
       link != NULL;
       link = block->GetNextLink())
  {
    if (link->GetProcessRef() != process_ref)
    {
      continue;    // aktuelle Link ist nicht mit Sendeprozess verbunden!
    }

    /********************************************/
    /* Pruefen, ob die Linksauswahl durch via   */
    /* erlaubt wurde und der Request-Dienst in der */
    /* Dienstliste des Links vorkommt:          */
    /********************************************/
    if (IsLinkAllowed(link) &&
        link->IsMachineServiceRefInList(service_ref))
    {
      assert (link_list->Append(link) == DS_OK);
    } // if
  } // for (Suchen der passenden Links)

  if (link_list->IsEmpty())          // keine passenden Links
  {                                   // gefunden?
    delete link_list;
    return NULL;
  }

  destinations = new DSMachineRefList;
  assert(destinations != NULL);

  /**********************************************************/
  /* Jetzt erst mal die Maschinen als Empfaenger raussuchen */
  /* die im gleichen Block wie der Dienstnehmer liegen:     */
  /**********************************************************/
  for (status = link_list->MoveFirst();
       status == DS_OK;
       status = link_list->MoveNext())
  {
    link = link_list->GetCurrentData();
    assert(link != NULL);
    if (link->GetMachineRef() != NULL)        // NULL = ENV !
    {
      assert(destinations->Append(link->GetMachineRef()) == DS_OK);
      link_list->DeleteElement();
    }
  }

  /********************************************************/
  /* Sind keine Links uebriggeblieben, die ans ENV gehen? */
  /********************************************************/
  if (link_list->IsEmpty())
  {
    delete link_list;
    return destinations;
  }

  /******************************************************/
  /* Es gibt Empfangsmaschinen ausserhalb des Blockes!! */
  /******************************************************/
  pipe_list = new DSPipeRefList;         // alle geeigneten Kanaele
                                         // werden in pipe_list gespeichert
  assert(pipe_list != NULL);

  /*****************************************************/
  /* Alle Pipe2LinkBindings des Blocks durchsuchen, */
  /* ob eine der Links ans ENV in ihnen vorkommt:      */
  /*****************************************************/
  for (binding = block->GetFirstPipe2LinkBinding();
       binding != NULL;
       binding = block->GetNextPipe2LinkBinding())
  {
    for (status = link_list->MoveFirst();
         status == DS_OK;
         status = link_list->MoveNext())
    {
      link = link_list->GetCurrentData();
      assert(link != NULL);
      /*******************************************************/
      /* Feststellen ob in aktueller Binding der aktuelle */
      /* Link vorkommt:                                      */
      /*******************************************************/
      if (binding->IsLinkBound(link))
      {
        /*******************************************************/
        /* alle Pipes der Verbindung auf Eignung ueberpruefen: */
        /*******************************************************/
        for (pipe = binding->GetFirstPipeRef();
             pipe != NULL;
             pipe = binding->GetNextPipeRef())
        {
          /******************************************************/
          /* Sicherstellen, dass Pipes nicht ueber verschiedene */
          /* Bindings mehrfach eingefuegt werden:            */
          /******************************************************/
/*          if (pipe_list->IsInList(pipe) == DS_TRUE)
          {
            continue;
          }*/
          /*********************************************/
          /* Pruefen, ob die Pipeauswahl durch via     */
          /* erlaubt wurde und die Request-Anforderung */
          /* in der Dienstliste der Pipe vorkommt:     */
          /*********************************************/
          if (IsPipeAllowed(pipe) &&
              (((pipe->GetBlock1Ref() == block &&
                pipe->IsMachineServiceRefInList12(service_ref)) ||
               ((pipe->GetBlock2Ref() == block &&
                pipe->IsMachineServiceRefInList21(service_ref)))))
             )
          {
            assert (pipe_list->Append(pipe) == DS_OK);
          } // if pipe gueltig und kann Singal uebertragen
        }  // for  (alle angebundenen Kanaele)
      }  // if (Link kommt in Verbindung vor)
    }  // for (alle Links durchlaufen)
  }  // for (alle Verbindungen durchlaufen)

  if (link_list)
  {
    delete link_list;
    link_list = NULL;
  }

  if (pipe_list->IsEmpty())           // keine passenden Pipes
  {                                   // gefunden?
    delete pipe_list;
    return destinations;
  }

  /***********************************/
  /* alle Empfangsbloecke bestimmen: */
  /***********************************/
  block_list = new DSBlockRefList;   // alle geeigneten Bloecke
                                     // werden in block_list gespeichert
  assert(block_list != NULL);

  block_pipe_list = new DSPipeRefList;
                                     // speichert ueber welche Pipe die
                                     // Bloecke erreicht werden
  assert(block_pipe_list != NULL);

  /************************************/
  /* Alle passenden Pipes durchlaufen */
  /* und die zugehoerigen Zielbloecke */
  /* ermitteln:                       */
  /************************************/
  for (status = pipe_list->MoveFirst();
       status == DS_OK;
       status = pipe_list->MoveNext())
  {
    pipe = pipe_list->GetCurrentData();
    assert(pipe != NULL);
    /*************************************************/
    /* Dienstliste  fuer die richte Richtung suchen: */
    /*************************************************/
    if (pipe->GetBlock1Ref() == block)
    {
      destination_block = pipe->GetBlock2Ref();
    }
    else if (pipe->GetBlock2Ref() == block)
    {
      destination_block = pipe->GetBlock1Ref();
    }
    assert (block_list->Append(destination_block) == DS_OK);
    assert (block_pipe_list->Append(pipe) == DS_OK);
  } // for (Suchen der passenden Zielbloecke)

  if (pipe_list)
  {
    delete pipe_list;
    pipe_list = NULL;
  }

  if (block_list->IsEmpty())        // keine passenden Zielbloecke
  {                                 // gefunden?
    delete block_list;
    delete block_pipe_list;
    return destinations;
  }

  link_list = new DSLinkRefList;     // alle geeigneten Links
                                     // werden in link_list
                                     // gespeichert
  assert(link_list != NULL);

  /***********************************************************/
  /* Alle Zielbloecke durchlaufen und passende Links suchen: */
  /***********************************************************/
  for (status = block_list->MoveFirst(),
       status2 = block_pipe_list->MoveFirst();
       status == DS_OK && status2 == DS_OK;
       status = block_list->MoveNext(),
       status2 = block_pipe_list->MoveNext())
  {
    destination_block = block_list->GetCurrentData();
    assert(destination_block != NULL);
    pipe = block_pipe_list->GetCurrentData();
    assert(pipe != NULL);

    for (binding = destination_block->GetFirstPipe2LinkBinding();
         binding != NULL;
         binding = destination_block->GetNextPipe2LinkBinding())
    {
      /*********************************************************/
      /* Feststellen, ob die Binding die Uebertragungspipe     */
      /* des Request-Dienstes enthaelt:                        */
      /*********************************************************/
      if (binding->IsPipeBound(pipe))
      {
        break; // for-Schleife abbrechen, da Uebertragungskanal
               // nur einmal vorkommen kann!
      }
    }

    if (binding == NULL)  // keine Verbindung fuer aktuellen Kanal
                          // gefunden? (dann ist diese binding
                          // uninteressant!)
    {
      continue;
    }

    /**********************************************/
    /* Alle Links der Binding auf Eignung testen: */
    /**********************************************/
    for (link = binding->GetFirstLinkRef();
         link  != NULL;
         link = binding->GetNextLinkRef())
    {
      /********************************************/
      /* Pruefen, ob die Linksauswahl durch via   */
      /* erlaubt wurde und das Request-Signal in der */
      /* Dienstliste des Links vorkommt:          */
      /********************************************/
      if (IsLinkAllowed(link) &&
          link->IsMachineServiceRefInList(service_ref))
      {
        assert (link_list->Append(link) == DS_OK);
      } // if Signallink erlaubt und Signal uebertragbar
    } // for (Suchen der passenden Links)
  }  // for (Durchlauf der Zielbloecke)

  if (link_list->IsEmpty())          // keine passenden Links im
  {                                   // Zielblock gefunden?
    delete link_list;
    return destinations;
  }

  /**********************************************************/
  /* Zu guter letzt die Maschinen als Empfaenger raussuchen */
  /* die in den Zielbloecken liegen:                        */
  /**********************************************************/
  for (status = link_list->MoveFirst();
       status == DS_OK;
       status = link_list->MoveNext())
  {
    link = link_list->GetCurrentData();
    assert(link != NULL);

    assert(destinations->Append(link->GetMachineRef()) == DS_OK);
  }

  if (block_list) delete block_list;
  if (block_pipe_list) delete block_pipe_list;
  if (link_list) delete link_list;

  return destinations;
}

/****************************************************************************
 * SetService(): Speichert den uebergebenen Zeiger auf einen Dienst
 *               -> exp: Zeiger auf eine Expression
 *               Ergebnis: DS_OK
 *               Seiteneffekte: keine
 ****************************************************************************/

DSResult DSRequest::SetMachineServiceRef(DSMachineServiceRef service)
{
  service_ref = service;
  return DS_OK;
}

/****************************************************************************
 * SetMachineRef(): Speichert den uebergebenen Zeiger auf eine Maschine
 *               -> exp: Zeiger auf eine Expression
 *               Ergebnis: DS_OK
 *               Seiteneffekte: keine
 ****************************************************************************/

DSResult DSRequest::SetMachineRef(DSMachineRef mach)
{
  machine_ref = mach;
  return DS_OK;
}

/****************************************************************************
 * SetMachineServiceAmount(): Speichert den uebergebenen Bedienwunsch
 *                            -> amount: Zeiger auf eine Expression
 *                           Ergebnis: DS_OK
 *                           Seiteneffekte: keine
 ****************************************************************************/

DSResult DSRequest::SetMachineServiceAmount(DSExpression* amount)
{
  if (service_amount == amount) return DS_OK;

  if (service_amount) delete service_amount;
  service_amount = amount;

  if (service_amount != NULL)
  {
    if (service_amount->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      service_amount->SetParent(this);
    }
  }

  return DS_OK;
}

/****************************************************************************
 * SetPriority(): Speichert die Prioritaet der Dienstanforderung
 *                -> prio: Prioritaet des Requests
 *                Ergebnis: DS_OK
 *                Seiteneffekte: keine
 ****************************************************************************/

DSResult DSRequest::SetPriority(DSExpression *prio)
{
  if (prio == priority) return DS_OK;

  if (priority) delete priority;
  priority = prio;

  if (priority != NULL)
  {
    if (priority->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      priority->SetParent(this);
    }
  }

  return DS_OK;
}

DSObject *DSRequest::Clone(DSObject *father, DSObject *fill_this) const
{
  DSRequest *new_request;

  if (fill_this == NULL)
  {
    new_request = (DSRequest *)New(father);
    assert(new_request);
  }
  else
  {
    assert(fill_this->GetType() == DS_ACTION);
    new_request = (DSRequest *)fill_this;
  }

  // Basisklasse clonen:
  DSAction::Clone(father, new_request);

  if (GetPipeRefList())
  {
    new_request->SetPipeRefList((DSPipeRefList *)GetPipeRefList()->Clone((DSObject *)new_request));
  }
  
  if (GetLinkRefList())
  {
    new_request->SetLinkRefList((DSLinkRefList *)GetLinkRefList()->Clone((DSObject *)new_request));
  }

  if (GetMachineServiceRef())
  {
    new_request->SetMachineServiceRef(GetMachineServiceRef());  // do not clone!
  }

  if (GetMachineServiceAmount())
  {
    new_request->SetMachineServiceAmount((DSExpression *)GetMachineServiceAmount()->Clone((DSObject *)new_request));
  }

  if (GetPriority())
  {
    new_request->SetPriority((DSExpression *)GetPriority()->Clone((DSObject *)new_request));
  }

  return new_request;
}

DSResult DSRequest::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSResult DSRequest::Run(DSWriter *writer, DSType object_type,
                        DSCardinal what) const
{
  DSResult  result;
  DSLinkRef link;
  DSPipeRef pipe;

  switch(object_type)
  {
    case DS_LINK:
      for (link = GetFirstLinkRef();
           link;
           link = GetNextLinkRef())
      {
        result = link->Write(writer, what);
        if (result != DS_OK)
        {
          return DS_ERROR;
        }
      }
      break;

    case DS_PIPE:
      for (pipe = GetFirstPipeRef();
           pipe;
           pipe = GetNextPipeRef())
      {
        result = pipe->Write(writer, what);
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
