#ifndef _DSGENERATOR_H_
#define _DSGENERATOR_H_

#include "DSBasicTypes.h"
#include "DSSortExtended.h"
#include "DSSortRefComponent.h"

/************************************************************************
 * Classname: DSGenerator
 * Purpose:   Definition eines SDL-Generators (entspricht C++ Template)
 * Z100:      Seite 
 ************************************************************************/

class DSGenerator : public DSSortExtended,
                    public DSSortRefComponent
{
  public:
    DSGenerator(DSObject*,                       /* Vaterobjekt               */
                DSString* = NULL,                /* Name des DSSort           */
                DSString* = NULL,                /* Name des DSGenerator      */
                DSSortRefList* = NULL,           /* Typen                     */
                class DSOperandLiteral* = NULL); /* Emptystring               */
    DSGenerator(DSObject*,                       /* Vaterobjekt               */
                DSString&,                       /* Name des DSSort           */
                DSString&,                       /* Name des DSGenerator      */
                DSSortRefList* = NULL,           /* Typen                     */
                class DSOperandLiteral* = NULL); /* Emptystring               */
    DSGenerator(DSObject*,                       /* Vaterobjekt               */
                const char*,                     /* Name des DSSort           */
                const char* = NULL,              /* Name des DSGenerator      */
                DSSortRefList* = NULL,           /* Typen                     */
                class DSOperandLiteral* = NULL); /* Emptystring               */
    ~DSGenerator(void);
    
    DSString         *GetGeneratorName(void) const;  // nicht 'GetName()' nennen!
    DSOperandLiteral *GetLiteral(void) const;
    
    DSResult          SetGeneratorName(DSString*);  // nicht 'SetName()' nennen!
    DSResult          SetGeneratorName(DSString&);
    DSResult          SetGeneratorName(const char *);
    DSResult          SetLiteral(DSOperandLiteral *);
        
    DSObject         *Clone(DSObject * = NULL,
                            DSObject * = NULL) const;
                                              // erzeugt eine identische
                                              // Kopie dieses Objekts

    /***********************************************************/
    /* Die folgenden zwei Funktionen dienen zum systematischen */
    /* Durchlaufen und Verarbeiten der Datenstruktur:          */
    /***********************************************************/
    virtual DSResult Write(DSWriter *, DSCardinal = 0) const;
    virtual DSResult Run(DSWriter*, DSType, DSCardinal = 0) const;

  private:
    DSString         *generator_name;  // nicht 'name' nennen!
    class DSOperandLiteral *literal;      // fuer String-Generator notwendig
};


#endif
