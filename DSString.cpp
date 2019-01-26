/****************************************************************************
 *                 Modul: $RCSfile: DSString.cpp,v $
 *
 * $Author: md $
 * $Date: 1997/10/30 15:13:40 $
 * $Revision: 1.4 $
 *
 * Aufgabe: Dieses Modul ermoeglicht die Erzeugung sowie Loeschung von Strings 
 *          und alle ueblichen ops, welche auf Strings angewendet werden 
 *          koennen
 *
 * Funktionen:  Length(void) const;  
 *              operator= (const DSString);
 *              operator+= (const DSString);
 *              operator==(const DSString);
 *              operator!= (const DSString);
 *              operator<<(ostream&s, const DSString);
 *              operator[]()
 *              Substring(int, int);
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

#include "DSString.h"
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#ifdef DEBUG
#include <dmalloc.h>
#endif

/****************************************************************************
 * Externe Variablen
 ****************************************************************************/

/****************************************************************************
 * Globale Variablen
 ****************************************************************************/

char DSString::tmp[TMP_LENGTH];

/****************************************************************************
 * Konstruktoren
 ****************************************************************************/

DSString::DSString(void) :
  DSObject(DS_STRING, NULL)
{
  s = NULL;
  size = 0;
}

DSString::DSString(size_t length, char init) :
  DSObject(DS_STRING, NULL)
{
  if (length == 0)
  {
    s = NULL;
    size = 0;
    return;
  }
  size = length + 1;
  s = new char[size];
  assert(s);
  memset(s, (int)init, length);
  s[length] = '\0';
}

DSString::DSString(const char *string) :
  DSObject(DS_STRING, NULL)
{
  if (string == NULL)
  {
    s = NULL;
    size = 0;
    return;
  }
  size = strlen(string) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, string);
}

DSString::DSString(const DSString& orig) :
  DSObject(DS_STRING, NULL)
{
  if (orig.Size() == 0 || !orig.GetString())
  {
    s = NULL;
    size = 0;
    return;
  }
  size = strlen(orig.GetString()) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, orig.GetString());
}

DSString::DSString(DSInteger integer) :
  DSObject(DS_STRING, NULL)
{
  sprintf(tmp, "%ld", integer);

  size = strlen(tmp) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, tmp);
}

DSString::DSString(DSCardinal cardinal) :
  DSObject(DS_STRING, NULL)
{
  sprintf(tmp, "%u", cardinal);

  size = strlen(tmp) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, tmp);
}

DSString::DSString(DSDouble dbl) :
  DSObject(DS_STRING, NULL)
{
  sprintf(tmp, "%f", dbl);

  size = strlen(tmp) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, tmp);
}

DSString::DSString(DSObject *father, size_t length, char init) :
  DSObject(DS_STRING, father)
{
  if (length == 0)
  {
    s = NULL;
    size = 0;
    return;
  }

  size = length + 1;
  s = new char[size];
  assert(s);
  memset(s, (int)init, length);
  s[length] = '\0';
}

DSString::DSString(DSObject *father, const char *string) :
  DSObject(DS_STRING, father)
{
  if (string == NULL)
  {
    s = NULL;
    size = 0;
    return;
  }
  size = strlen(string) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, string);
}

DSString::DSString(DSObject *father, const DSString& orig) :
  DSObject(DS_STRING, father)
{
  if (orig.Size() == 0 || !orig.GetString())
  {
    s = NULL;
    size = 0;
    return;
  }
  size = strlen(orig.GetString()) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, orig.GetString());
}

DSString::DSString(DSObject *father, DSInteger integer) :
  DSObject(DS_STRING, father)
{
  sprintf(tmp, "%ld", integer);

  size = strlen(tmp) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, tmp);
}

DSString::DSString(DSObject *father, DSCardinal cardinal) :
  DSObject(DS_STRING, father)
{
  sprintf(tmp, "%u", cardinal);

  size = strlen(tmp) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, tmp);
}

DSString::DSString(DSObject *father, DSDouble dbl) :
  DSObject(DS_STRING, father)
{
  sprintf(tmp, "%f", dbl);

  size = strlen(tmp) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, tmp);
}

/****************************************************************************
 * Destruktor
 ****************************************************************************/

DSString::~DSString(void)
{   
  if (s) delete[] s;                                            
}

DSObject *DSString::New(DSObject *father) const
{
  return new DSString(father);
}

DSResult DSString::Format(const char *format, ...)  
{
  va_list arg_list;

  assert(format);

  if (s) delete[] s;

  va_start(arg_list, format);
  size = vsprintf(tmp, format, arg_list) + 1;
  va_end(arg_list);

  assert(size > 1 && size < TMP_LENGTH);
  assert(size >= strlen(tmp));

  s = new char[size];
  assert(s);
  strcpy(s, tmp);

  return DS_OK;
}

/****************************************************************************
 * Length(): Liefert die Laenge des Strings zurueck
 *           Ergebnis: size_t
 *           Seiteneffekte: keine
 ****************************************************************************/

size_t DSString::Length(void) const
{
  if (s == NULL) return 0;

  assert(size >= strlen(s));

  return strlen(s);                             
}

/****************************************************************************
 * Size(): Liefert die Groesse des Strings zurueck
 *         Ergebnis: size_t
 *         Seiteneffekte: keine
 ****************************************************************************/

size_t DSString::Size(void) const
{
  return size;                             
}

DSString *DSString::SubString(unsigned int pos) const
{
  DSString *substring;

  assert(pos <= size - 2);
  if (pos >= Length()) return NULL;

  substring = new DSString(&s[pos]);
  assert(substring);

  return substring;
}

/****************************************************************************
 * operator=: Weist einem String den Wert des uebergebenen Strings zu
 *            Ergebnis: DSString&
 *            Seiteneffekte: keine
 ****************************************************************************/

DSString& DSString::operator= (const DSString& orig) 
{
  if (this == &orig) // Zuweisung an sich selbst?
  {
    return *this;
  }
  if (s) delete[] s;
  size = strlen(orig.GetString()) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, orig.GetString());  
  return *this;
}

DSString& DSString::operator= (const char *orig) 
{
  assert(orig);

  if (s) delete[] s;
  size = strlen(orig) + 1;
  s = new char[size];
  assert(s);
  strcpy(s, orig);  
  return *this;
}

/****************************************************************************
 * operator+=: haengt uebergebenen String an das Original an
 *            Ergebnis: DSString&
 *            Seiteneffekte: keine
 ****************************************************************************/

DSString& DSString::operator+= (const DSString& y) 
{
  char *help;
  size_t s_len;

  if (y.Length() == 0)
  {
    return *this;
  }

  if (s)
  {
    s_len = strlen(s);
  }
  else
  {
    s_len = 0;
  }

  // Reicht der Speicher nicht mehr aus?
  if (size < s_len + strlen(y.GetString()) + 1)
  {
    size = s_len + strlen(y.GetString()) + 1;
    help = new char [size];
    assert(help);

    if (s)
    {
      strcpy(help, s);
      strcat(help, y.GetString());
      delete[] s;
    }
    else
    {
      strcpy(help, y.GetString());
    }
    s = help;
  }
  else  // Speicher reicht noch!
  {
    strcat(s, y.GetString());
  }
  return *this;
}

DSString& DSString::operator+= (const char *y) 
{
  char *help;
  size_t s_len;

  if (y == NULL)
  {
    return *this;
  }
  
  if (s)
  {
    s_len = strlen(s);
  }
  else
  {
    s_len = 0;
  }

  // Reicht der Speicher nicht mehr aus?
  if (size < s_len + strlen(y) + 1)
  {
    size = s_len + strlen(y) + 1;
    help = new char [size];
    assert(help);

    if (s)
    {
      strcpy(help, s);
      strcat(help, y);
      delete[] s;
    }
    else
    {
      strcpy(help, y);
    }

    s = help;
  }
  else  // Speicher reicht noch!
  {
    strcat(s, y);
  }

  return *this;
}


DSString& DSString::operator+= (const char y) 
{
  char *help;
  size_t s_len;

  if (s)
  {
    s_len = strlen(s);
  }
  else
  {
    s_len = 0;
  }

  // Reicht der Speicher nicht mehr aus?
  if (size < s_len + 2)
  {
    size = s_len + 2;
    help = new char [size];
    assert(help);

    if (s)
    {
      strcpy(help, s);
      delete[] s;
    }

    help[strlen(help)] = y;
    help[strlen(help) + 1] = '\0';

    s = help;
  }
  else  // Speicher reicht noch!
  {
    s[s_len] = y;
    s[s_len + 1] = '\0';
  }

  return *this;
}


/****************************************************************************
 * operator==: vergleicht zwei Strings miteinander
 *            Ergebnis: DS_TRUE, falls sie gleich sind, DS_FALSE sonst
 *            Seiteneffekte: keine
 ****************************************************************************/

DSBoolean DSString::operator== (const DSString& y) const
{
  assert(s);
  assert(y.GetString());

  return (strcmp(s, y.GetString() ) == 0 ) ? DS_TRUE : DS_FALSE; 
}

DSBoolean DSString::operator== (const char *y) const
{
  assert(s);
  assert(y);

  return (strcmp(s, y) == 0 ) ? DS_TRUE : DS_FALSE; 
}

/****************************************************************************
 * operator!=: vergleicht zwei Strings miteinander
 *            Ergebnis: DS_TRUE, falls sie ungleich sind, DS_FALSE sonst
 *            Seiteneffekte: keine
 ****************************************************************************/

DSBoolean DSString::operator!= (const DSString& y) const
{
  assert(s);
  assert(y.GetString());

  return (strcmp(s, y.GetString() ) != 0 ) ? DS_TRUE : DS_FALSE; 
}

DSBoolean DSString::operator!= (const char *y) const
{
  assert(s);
  assert(y);

  return (strcmp(s, y) != 0 ) ? DS_TRUE : DS_FALSE; 
}

/****************************************************************************
 * operator[]: liefert das char-Element
 *            Ergebnis: DS_TRUE, falls sie ungleich sind, DS_FALSE sonst
 *            Seiteneffekte: keine
 ****************************************************************************/

char& DSString::operator[] (unsigned int i) const
{
  if (i >= size)
  {
    std::cerr << std::endl << std::endl << "DSString::operator[] (unsigned int i = "
         << i << "): Index out of range (size = " << size
         << ", string = '" << s << "'). Exiting..." << std::endl << std::endl;
    assert(i < size);
    exit (-1);
  }
  return s[i];
}

/****************************************************************************
 * operator<<: Ausgabe eines DSString mit cout<<
 *            Ergebnis: ostream&
 *            Seiteneffekte: keine
 ****************************************************************************/

std::ostream& operator<< (std::ostream& out, DSString& y) 
{
  out << y.GetString();
  return out;
}

std::ostream& operator<< (std::ostream& out, DSString * y)
{
  out << y->GetString();
  return out;
}

DSStream& operator<< (DSStream& out, DSString& y) 
{
  out << y.GetString();
  return out;
}

DSStream& operator<< (DSStream& out, DSString * y)
{
  out << y->s;
  return out;
}

/****************************************************************************
 * GetString: liefert den gespeicherten String
 *            Ergebnis: const char*
 *            Seiteneffekte: keine
 ****************************************************************************/

const char* DSString::GetString(void) const
{
  assert(s);
  return s;
}

void DSString::ToUpper(unsigned int max_chars)
{
  int i;
  size_t l = (strlen(s) < max_chars || !max_chars) ? strlen(s) : max_chars;

  for (i = 0;
       i < (int)l;
       i++)
  {
    s[i] = toupper(s[i]);
    if (s[i] == '.')
      s[i] = '_';
  }
}

void DSString::ToLower(unsigned int max_chars)
{
  int i;
  size_t l = (strlen(s) < max_chars || !max_chars) ? strlen(s) : max_chars;

  for (i = 0;
       i < (int)l;
       i++)
  {
    s[i] = tolower(s[i]);
  }
}

DSBoolean DSString::IsNumeric(void) const
{
  int i;
  size_t l = strlen(s);

  for (i = 0;
       i < (int)l;
       i++)
  {
    if (!isdigit(s[i]) && s[i] != '.') // kein glueltiges Zeichen einer Real-Zahl ?
    {
      return DS_FALSE;
    }
  }
  return DS_TRUE;
}

DSBoolean DSString::IsNatural(void) const
{
  int i;
  size_t l = strlen(s);

  for (i = 0;
       i < (int)l;
       i++)
  {
    if (!isdigit(s[i])) // kein glueltiges Zeichen einer Natural-Zahl
    {
      return DS_FALSE;
    }
  }
  return DS_TRUE;
}

DSResult DSString::Write(DSWriter *writer, DSCardinal what) const
{
  (void)what;

  assert(writer);

  return DS_OK;
}

DSObject *DSString::Clone(DSObject *father, DSObject *fill_this) const
{
  DSString *new_string;

  if (fill_this == NULL)
  {
    new_string = new DSString(father, *this);
    assert(new_string);
  }
  else
  {
    assert(fill_this->GetType() == DS_STRING);
    new_string = (DSString *)fill_this;

    if (new_string->s)
    {
      delete new_string->s;
    }
    new_string->size = size;
    new_string->s = new char[size];
    assert(new_string->s);
    strcpy(new_string->s, s);
  }

  return new_string;
}
