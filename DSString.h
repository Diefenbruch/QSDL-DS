#ifndef _DSSTRING_H_
#define _DSSTRING_H_

#include <iostream>
#include "DSStream.h"
#include "DSBasicTypes.h"
#include "DSObject.h"

#define TMP_LENGTH 512

/*****************************************************************************
 * Klasse DSString.h
 * eigene Implementierung o.g. Funktionen.
 *****************************************************************************/

class DSString : public DSObject
{
  public:
    DSString(void);
    DSString(size_t, char);             // Konstruktoren ohne Vaterobjekt
    DSString(const char *);             // fuer den allgemeinen Gebrauch
    DSString(const DSString&);
    DSString(DSInteger);                // konvertiert Integer->String
    DSString(DSCardinal);               // konvertiert Cardinal->String
    DSString(DSDouble);                 // konvertiert Double->String

    DSString(DSObject*, size_t,         // Konstruktoren mit Vaterobjekt
             char);                     // fuer den Gerauch innerhalb der DS
    DSString(DSObject*, const char * = NULL);
    DSString(DSObject*, const DSString&);
    DSString(DSObject*, DSInteger);     // konvertiert Integer->String
    DSString(DSObject*, DSCardinal);    // konvertiert Cardinal->String
    DSString(DSObject*, DSDouble);      // konvertiert Double->String
    virtual ~DSString(void);

    DSObject *New(DSObject * = NULL) const;

    size_t            Length(void) const;
    size_t            Size(void) const;
    DSString*         SubString(unsigned int) const;
    DSString&         operator= (const DSString&);
    DSString&         operator= (const char *);
    DSString&         operator+= (const DSString&);
    DSString&         operator+= (const char *);
    DSString&         operator+= (const char);
    DSBoolean         operator== (const DSString&) const;
    DSBoolean         operator== (const char *) const;
    DSBoolean         operator!= (const DSString&) const ;
    DSBoolean         operator!= (const char *) const;
    char&             operator[] (unsigned int) const;
    // definition of operator+ is outside the class!!!
    // (see below)
    
    DSResult          Format(const char *, ...);

//    friend ostream&   operator<<(ostream& s, DSString *);
//    friend ostream&   operator<<(ostream& s, DSString&);
    friend DSStream&  operator<<(DSStream& s, DSString *);
    friend DSStream&  operator<<(DSStream& s, DSString&);
    const char*       GetString(void) const;
    void              ToUpper(unsigned int = 0); // maximale Anzahl von Zeichen
    void              ToLower(unsigned int = 0); // 0 = Alle
    DSBoolean         IsNumeric(void) const;
    DSBoolean         IsNatural(void) const;

// the following DSString -> const char * operator
// breaks the operator[] ! why?    
//    inline operator   const char *(void) const {return s;};
                                              // NOTE: "const char *"
                                              // is the name of the
                                              // operator!!
	   	
    DSObject *Clone(DSObject * = NULL,
                    DSObject * = NULL) const; // erzeugt eine identische
                                              // Kopie dieses Objekts
    /****************************************************/
    /* Die folgende Funktion dient zum systematischen   */
    /* Durchlaufen und Verarbeiten der Datenstruktur:   */
    /****************************************************/
    virtual DSResult  Write(DSWriter *, DSCardinal = 0) const;

  private:
    char           *s;
    size_t          size;   // belegter Speicherplatz
                            // muss nicht mit Laenge des
                            // Strings uebereinstimmen!
    static char     tmp[TMP_LENGTH];
};

/****************************************************************************
 * operator+: Konkateniert zwei Strings
 *            Ergebnis: DSString&
 *            Seiteneffekte: keine
 ****************************************************************************/

inline DSString operator+ (const DSString& left, const DSString& right) 
{
  DSString result(left);
  
  result += right;
  
  return result;
}


inline DSString operator+ (const char * left, const DSString& right) 
{
  DSString result(left);
  
  result += right;
  
  return result;
}


inline DSString operator+ (const DSString& left, const char * right) 
{
  DSString result(left);
  
  result += right;
  
  return result;
}


inline DSString operator+ (const char left, const DSString& right) 
{
  DSString result(1, left);
  
  result += right;
  
  return result;
}


inline DSString operator+ (const DSString& left, const char right) 
{
  DSString result(left);
  
  result += right;
  
  return result;
}


#endif
