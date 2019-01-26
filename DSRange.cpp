/****************************************************************************
 *                 Modul: $RCSfile: DSRange.cpp,v $
 *
 * $Author: hirche $
 * $Date: 1997/08/29 13:33:16 $
 * $Revision: 1.1 $
 *
 * Aufgabe: Dieser Modul ermoeglicht die Abspeicherung bzw. Ruecklieferung
 *          des Wertebereichs eines Datentyps
 *
 * Funktionen: GetName(): Gibt einen Zeiger den Namen zurueck
 *             SetName(): Speichert den Typnamen
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

#include "DSRange.h"
#include "DSSyntype.h"  // wegen parent
#include "DSDecision.h"  // wegen parent
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

DSRange::DSRange(DSObject       *father,
                 DSExpression   *lower,
                 DSExpression   *upper,
                 DSRangeOperator range_op) :
  DSObject(DS_RANGE, father),
  lower_bound(lower),
  upper_bound(upper),
  range_operator(range_op)
{
  if (lower_bound && upper_bound)
  {
    assert(lower_bound != upper_bound);
  }
  
  if (father)
  {
    switch (father->GetType())
    {
      case DS_SORT:
        ((DSSyntype*)father)->InsertRange(this);
        break;
      case DS_ACTION:
        ((DSDecision*)father)->InsertAnswer(this);
        break;
      default:
        assert(DS_FALSE);
        break;
      }
  }
  if (upper_bound)
  {
    if (upper_bound->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      upper_bound->SetParent(this);
    }
  }
  if (lower_bound)
  {
    if (lower_bound->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      lower_bound->SetParent(this);
    }
  }
}

DSRange::DSRange(DSObject       *father,
                 DSExpression&   lower,
                 DSExpression&   upper,
                 DSRangeOperator range_op) :
  DSObject(DS_RANGE, father),
  lower_bound(&lower),
  upper_bound(&upper),
  range_operator(range_op)
{
  if (lower_bound && upper_bound)
  {
    assert(lower_bound != upper_bound);
  }

  if (father)
  {
    switch (father->GetType())
    {
      case DS_SORT:
        ((DSSyntype*)father)->InsertRange(this);
        break;
      case DS_ACTION:
        ((DSDecision*)father)->InsertAnswer(this);
        break;
      default:
        assert(DS_FALSE);
        break;
    }
  }
  if (upper_bound)
  {
    if (upper_bound->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      upper_bound->SetParent(this);
    }
  }
  if (lower_bound)
  {
    if (lower_bound->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      lower_bound->SetParent(this);
    }
  }
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSRange::~DSRange(void)
{
  if (lower_bound) delete lower_bound;                        
  if (upper_bound) delete upper_bound;
}

/****************************************************************************
 * Virtueller Konstruktor
 ****************************************************************************/

DSObject *DSRange::New(DSObject *father) const
{
  return new DSRange(father);
}

/****************************************************************************
 * GetUpperBound(): Liefert den Zeiger auf die untere Wertegrenze zurueck
 *                  Ergebnis: Zeiger auf einen DSExpression
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSExpression *DSRange::GetUpperBound(void) const
{
  return upper_bound;
}

/****************************************************************************
 * GetLowerBound(): Liefert den Zeiger auf die untere Wertegrenze zurueck
 *                  Ergebnis: Zeiger auf einen DSExpression
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSExpression *DSRange::GetLowerBound(void) const
{
  return lower_bound;
}

/****************************************************************************
 * GetRangeOperator(): Liefert den den Operatortyp eines offenen Wertebereichs
 *                     Ergebnis: Operatortyp (vgl. DSBasicTypes.h)
 *                     Seiteneffekte: keine
 ****************************************************************************/

DSRangeOperator DSRange::GetRangeOperator(void) const
{
  return range_operator;
}

/****************************************************************************
 * SetUpperBound(): Speichert den uebergebenen Zeiger
 *                 -> upper: Zeiger auf einen DSExpression
 *                 Ergebnis: DS_OK
 *                 Seiteneffekte: keine
 ****************************************************************************/

DSResult DSRange::SetUpperBound(DSExpression *upper)
{
  if (upper_bound == upper) return DS_OK;

  if (upper_bound) delete upper_bound;
  upper_bound = upper;

  if (upper_bound != NULL)
  {
    if (upper_bound->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      upper_bound->SetParent(this);
    }
  }

  if (lower_bound && upper_bound)
  {
    assert(lower_bound != upper_bound);
  }

  return DS_OK;
}

/****************************************************************************
 * SetLowerBound(): Speichert den uebergebenen Zeiger
 *                  -> lower: Zeiger auf einen DSExpression
 *                  Ergebnis: DS_OK
 *                  Seiteneffekte: keine
 ****************************************************************************/

DSResult DSRange::SetLowerBound(DSExpression *lower)
{
  if (lower_bound == lower) return DS_OK;

  if (lower_bound) delete lower_bound;
  lower_bound = lower;

  if (lower_bound != NULL)
  {
    if (lower_bound->GetParent() == NULL) // Vater noch nicht gesetzt ?
    {
      lower_bound->SetParent(this);
    }
  }

  if (lower_bound && upper_bound)
  {
    assert(lower_bound != upper_bound);
  }

  return DS_OK;
}

/****************************************************************************
 * SetRangeOperator(): Speichert den Operatortyp eines offenen Wertebereichs
 *                     -> range_op: Operatortyp
 *                     Ergebnis: DS_OK
 *                     Seiteneffekte: keine
 ****************************************************************************/

DSResult DSRange::SetRangeOperator(DSRangeOperator range_op)
{
  range_operator = range_op;
  return DS_OK;
}

DSObject *DSRange::Clone(DSObject *father, DSObject *fill_this) const
{
  DSRange *new_range;

  if (fill_this == NULL)
  {
    new_range = (DSRange *)New(father);
    assert(new_range);
  }
  else
  {
    assert(fill_this->GetType() == DS_RANGE);
    new_range = (DSRange *)fill_this;
  }

  if (GetUpperBound()) // immer erst UpperBound clonen!
  {
    GetUpperBound()->Clone((DSObject *)new_range);
  }

  if (GetLowerBound())
  {
    GetLowerBound()->Clone((DSObject *)new_range);
  }

  new_range->SetRangeOperator(GetRangeOperator());

  return new_range;
}

DSResult DSRange::Write(DSWriter *writer, DSCardinal what) const
{
  assert(writer);

  if (lower_bound) lower_bound->Write(writer, what);
  if (upper_bound) upper_bound->Write(writer, what);

  return DS_OK;
}
