#ifndef _DSSTREAM_H_
#define _DSSTREAM_H_

#include <iostream>

typedef std::ostream& (*my_omanip)(std::ostream&);

class DSStream: public std::ostream
{
  public:
    DSStream(std::ostream &the_stream) : dsStream(the_stream) {}
    virtual ~DSStream(void) {}

    DSStream& operator<<(char c) { Display(c); return *this;}
    DSStream& operator<<(unsigned char c) { Display(c); return *this;}
    DSStream& operator<<(signed char c) { Display(c); return *this;}
    DSStream& operator<<(const char *s) { Display(s); return *this;}
    DSStream& operator<<(const unsigned char *s) { Display(s); return *this;}
    DSStream& operator<<(const signed char *s) { Display(s); return *this;}
    DSStream& operator<<(const void *p) { Display(p); return *this;}
    DSStream& operator<<(int n) { Display(n); return *this;}
    DSStream& operator<<(unsigned int n) { Display(n); return *this;}
    DSStream& operator<<(long n) { Display(n); return *this;}
    DSStream& operator<<(unsigned long n) { Display(n); return *this;}
    DSStream& operator<<(short n) { Display(n); return *this;}
    DSStream& operator<<(unsigned short n) { Display(n); return *this;}
    DSStream& operator<<(double n) { Display(n); return *this;}
    DSStream& operator<<(float n) { Display(n); return *this;}
    DSStream& operator<<(long double n) { Display(n); return *this;}
    DSStream& operator<<(my_omanip func) { Display(func); return *this;}

  protected:
    virtual void Display(char c) { dsStream << c;}
    virtual void Display(unsigned char c) { dsStream << c;}
    virtual void Display(signed char c) { dsStream << c;}
    virtual void Display(const char *s) { dsStream << s;}
    virtual void Display(const unsigned char *s) { dsStream << s;}
    virtual void Display(const signed char *s) { dsStream << s;}
    virtual void Display(const void *p) { dsStream << p;}
    virtual void Display(int n) { dsStream << n;}
    virtual void Display(unsigned int n) { dsStream << n;}
    virtual void Display(long n) { dsStream << n;}
    virtual void Display(unsigned long n) { dsStream << n;}
    virtual void Display(short n) { dsStream << n;}
    virtual void Display(unsigned short n) { dsStream << n;}
    virtual void Display(double n) { dsStream << n;}
    virtual void Display(float n) { dsStream << n;}
    virtual void Display(long double n) { dsStream << n;}
    virtual void Display(my_omanip func) { dsStream << func;}

  private:
    std::ostream &dsStream;
};

#endif

