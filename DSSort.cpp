/****************************************************************************
 *                 Modul: $RCSfile: DSSort.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/10/22 16:09:53 $
 * $Revision: 1.2 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          von Namen und Typ eines Datentyps
 *
 * Funktionen: GetTag() : Gibt den Typ zurueck
 *             GetRange(): liefert den Wertebereich einer Sorte
 *             SetTag() : Speichert den Typ
 *             SetRange(): Setzt den Wertebereich einer Sorte
 *             Save(): Abspeicherung der Infos in einer Datei
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

#include "DSSort.h"
#include "DSSystem.h"  // wegen parent
#include "DSBlock.h"  // wegen parent
#include "DSBlockSubstructure.h"  // wegen parent
#include "DSProcess.h"  // wegen parent
#include "DSProcedure.h"  // wegen parent
#include "DSExpression.h"
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

DSSort::DSSort(DSObject     *father,
               DSString     *n,
               DSSortTag     t,
               DSBoolean     pre,
               DSBoolean     comp,
               DSExpression *def) :
  DSNamedObject(DS_SORT, n, father),
  tag(t),
  predefined(pre),
  complex(comp),
  default_init(def)
{
  neutral_element = NULL;

  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSort(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSort(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSort(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSort(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertSort(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSSort::DSSort(DSObject  *father,
               DSString  &n,
               DSSortTag  t,
               DSBoolean  pre,
               DSBoolean  comp,
               DSExpression *def) :
  DSNamedObject(DS_SORT, n, father),
  tag(t),
  predefined(pre),
  complex(comp),
  default_init(def)
{
  neutral_element = NULL;

  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSort(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSort(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSort(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSort(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertSort(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
}

DSSort::DSSort(DSObject   *father,
               const char *n,
               DSSortTag   t,
               DSBoolean   pre,
               DSBoolean   comp,
               DSExpression *def) :
  DSNamedObject(DS_SORT, n, father),
  tag(t),
  predefined(pre),
  complex(comp),
  default_init(def)
{
  neutral_element = NULL;
  
  if (father)
  {
    switch(father->GetType())
    {
      case DS_SYSTEM:
        ((DSSystem*)father)->InsertSort(this);
        break;
      case DS_BLOCK:
        ((DSBlock*)father)->InsertSort(this);
        break;
      case DS_BLOCKSUBSTRUCTURE:
        ((DSBlockSubstructure*)father)->InsertSort(this);
        break;
      case DS_PROCESS:
        ((DSProcess*)father)->InsertSort(this);
        break;
      case DS_PROCEDURE:
        ((DSProcedure*)father)->InsertSort(this);
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

DSSort::~DSSort(void)
{
  if (default_init) delete default_init;
  if (neutral_element) delete neutral_element;                      
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSSort::New(DSObject *father) const
{
  return new DSSort(father);
}

/****************************************************************************
 * GetTag(): Liefert den Zeiger auf den Typ zurueck
 *            Ergebnis: Zeiger auf einen Enum-Wert
 *            Seiteneffekte: keine
 ****************************************************************************/

DSSortTag DSSort::GetTag(void) const
{
  return tag;
}

/****************************************************************************
 * GetIsPredefined(): Liefert boolesches Flag ob es sich um einen vor-
 *                    definierten Datentyp handelt.
 *                    Ergebnis: Zeiger auf einen Enum-Wert
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSBoolean DSSort::GetIsPredefined(void) const
{
  return predefined;
}

/****************************************************************************
 * GetIsComplex(): Liefert boolesches Flag ob es sich um einen komplexen
 *                 d.h. zusammengesetzten Datentyp handelt.
 *                 Ergebnis: Zeiger auf einen Enum-Wert
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSBoolean DSSort::GetIsComplex(void) const
{
  return complex;
}

/****************************************************************************
 * GetDefaultInitialization(): Liefert den Default-Wert des Datentyps
 *                             Ergebnis: Zeiger auf einen Ausdruck
 *                             Seiteneffekte: keine
 ****************************************************************************/

DSExpression *DSSort::GetDefaultInitialization(void) const
{
  return default_init;
}

/****************************************************************************
 * GetNeutralElement(): Liefert den Zeiger auf das neutrale Element der
 *                      Sorte zurueck
 *                      Ergebnis: Zeiger auf einen DSString
 *                      Seiteneffekte: keine
 ****************************************************************************/

DSString *DSSort::GetNeutralElement(void) const
{
  return neutral_element;
}

/****************************************************************************
 * SetTag(): Speichert den uebergebenen Typ
 *            -> tag_type: Enum-Typ
 *            Ergebnis: TRUE
 *            Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSort::SetTag(DSSortTag tag_type)
{
  tag = tag_type;
  return DS_OK;
}

/****************************************************************************
 * SetIsPredefined(): Speichert ob der Datentyp vordefiniert ist.
 *                    -> flag: Boolesches Flag
 *                    Ergebnis: DS_OK
 *                    Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSort::SetIsPredefined(DSBoolean flag)
{
  predefined = flag;
  return DS_OK;
}

/****************************************************************************
 * SetIsComplex(): Speichert ob der Datentyp komplex (zusammengesetzt) ist.
 *                 -> flag: Boolesches Flag
 *                 Ergebnis: DS_OK
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSort::SetIsComplex(DSBoolean flag)
{
  complex = flag;
  return DS_OK;
}

/****************************************************************************
 * SetDefaultInitialization(): Speichert den Initialwert des Datentyps
 *                             -> init: Zeiger auf Ausdruck
 *                             Ergebnis: DS_OK
 *                             Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSort::SetDefaultInitialization(DSExpression *init)
{
  if (default_init == init) return DS_OK;

  if (default_init) delete default_init;
  default_init = init;

  if (default_init != NULL)
  {
    if (default_init->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      default_init->SetParent(this);
    }
  }

  return DS_OK;
}

/****************************************************************************
 * SetNeutralElement(): Setzt das neutrale Element der Sorte
 *                      -> neutral: Zeiger auf einen DSString
 *                      Ergebnis: DS_OK
 *                      Seiteneffekte: keine
 ****************************************************************************/

DSResult DSSort::SetNeutralElement(DSString *neutral)
{
  if (neutral_element == neutral) return DS_OK;

  if (neutral_element) delete neutral_element;
  neutral_element = neutral;

  if (neutral_element != NULL)
  {
    if (neutral_element->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      neutral_element->SetParent(this);
    }
  }

  return DS_OK;
}

DSResult DSSort::SetNeutralElement(DSString &neutral)
{
  if (neutral_element == &neutral) return DS_OK;

  if (neutral_element) delete neutral_element;
  neutral_element = &neutral;

  if (neutral_element->GetParent() == NULL) // Vater noch nicht gesetzt ?
  {
    neutral_element->SetParent(this);
  }

  return DS_OK;
}

DSResult DSSort::SetNeutralElement(const char *neutral)
{
  if (neutral_element) delete neutral_element;
  neutral_element = new DSString(this, neutral);
  assert(neutral_element);
  return DS_OK;
}

DSObject *DSSort::Clone(DSObject *father, DSObject *fill_this) const
{
  DSSort *new_sort;

  if (fill_this == NULL)
  {
    new_sort = (DSSort *)New(father);
    assert(new_sort);
  }
  else
  {
    assert(fill_this->GetType() == DS_SORT);
    new_sort = (DSSort *)fill_this;
  }

  // Basisklassen clonen:
  DSNamedObject::Clone(father, new_sort);

  new_sort->SetTag(GetTag());
  new_sort->SetIsPredefined(GetIsPredefined());

  if (GetDefaultInitialization())
  {
    new_sort->SetDefaultInitialization((DSExpression *)GetDefaultInitialization()->Clone((DSObject *)new_sort));
  }

  if (GetNeutralElement())
  {
    new_sort->SetNeutralElement((DSString *)GetNeutralElement()->Clone((DSObject *)new_sort));
  }

  return new_sort;
}

DSResult DSSort::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}
