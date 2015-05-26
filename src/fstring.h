// fstring.h
// class FString

#ifndef _FSTRING_H
#define _FSTRING_H

#include <sys/types.h>

#include <stdint.h>

#include <cassert>
#include <cerrno>  // for read errno
#include <climits>
#include <cstdarg> // need for va_list, va_start and va_end
#include <cstdio>  // need for vsprintf
#include <cstring>
#include <cwchar>
#include <cwctype>

#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <vector>


#define FWDBUFFER 15
#define INPBUFFER 200
#define CHAR_SIZE (sizeof(wchar_t))  // bytes per character
#define bad_alloc_str ("not enough memory to alloc a new string")

typedef unsigned char  uChar;
typedef unsigned int   uInt;
typedef unsigned long  uLong;
typedef unsigned char  uInt8;
typedef unsigned short uInt16;
typedef unsigned int   uInt32;
typedef u_int64_t      uInt64;

typedef signed int   sInt;
typedef signed long  sLong;
typedef signed char  sInt8;
typedef signed short sInt16;
typedef signed int   sInt32;
typedef int64_t      sInt64;


//----------------------------------------------------------------------
// class FString
//----------------------------------------------------------------------

class FString
{
 public:
   typedef const wchar_t* iterator;

 private:
   wchar_t*      string;
   uInt          length;
   uInt          bufsize;
   mutable char* c_string;

 private:
   inline void initLength (uInt);
   inline void _replace (const wchar_t*);
   inline void _insert (uInt, uInt, const wchar_t*);
   inline void _remove (uInt, uInt);
   inline char* wc_to_c_str (const wchar_t* s) const;
   inline wchar_t* c_to_wc_str (const char* s) const;
   inline wchar_t* extractToken (wchar_t**, const wchar_t*, const wchar_t*);

 public:
   FString ();                    // constructor
   FString (int);                 // constructor
   FString (uInt);                // constructor
   FString (int, wchar_t);        // constructor
   FString (uInt, wchar_t);       // constructor
   FString (int, char);           // constructor
   FString (uInt, char);          // constructor
   FString (const FString&);      // constructor
   FString (const std::wstring&); // constructor
   FString (const wchar_t*);      // constructor
   FString (const std::string&);  // constructor
   FString (const char*);         // constructor
   FString (const wchar_t);       // constructor
   FString (const char);          // constructor
   virtual ~FString ();  // destructor

   bool isNull() const;
   bool isEmpty() const;
   uInt getLength() const;
   uInt getUTF8length() const;

   iterator begin() const;
   iterator end() const;
   wchar_t front() const;
   wchar_t back() const;

   FString& sprintf (const wchar_t*, ...);
   FString& sprintf (const char*, ...)
   #if defined(__clang__)
     __attribute__((__format__ (__printf__, 2, 3)))
   #elif defined(__GNUC__)
     __attribute__ ((format (printf, 2, 3)))
   #endif
            ;
   FString clear();

   const wchar_t* wc_str() const;
   const char* c_str() const;
   const std::string toString() const;

   FString  toLower()  const;
   FString  toUpper()  const;

   sInt16   toShort()  const;
   uInt16   toUShort() const;
   int      toInt()    const;
   uInt     toUInt()   const;
   long     toLong()   const;
   uLong    toULong()  const;

   FString  ltrim() const;
   FString  rtrim() const;
   FString  trim()  const;

   FString  left(uInt) const;
   FString  right(uInt) const;
   FString  mid(uInt, uInt) const;

   std::vector<FString> split(const FString&);

   FString& setString (const wchar_t*);
   FString& setString (const char*);

   FString& setNumber (sInt16);
   FString& setNumber (uInt16);
   FString& setNumber (int);
   FString& setNumber (uInt);
   FString& setNumber (long);
   FString& setNumber (uLong);

   FString& setFormatedNumber (sInt16, char separator='.');
   FString& setFormatedNumber (uInt16, char separator='.');
   FString& setFormatedNumber (int,    char separator='.');
   FString& setFormatedNumber (uInt,   char separator='.');
   FString& setFormatedNumber (long,   char separator='.');
   FString& setFormatedNumber (uLong,  char separator='.');

   friend std::ostream&  operator << (std::ostream& outstr, const FString& s);
   friend std::istream&  operator >> (std::istream& instr, FString& s);
   friend std::wostream& operator << (std::wostream& outstr, const FString& s);
   friend std::wistream& operator >> (std::wistream& instr, FString& s);

   FString& operator = (const FString&);
   FString& operator = (const std::wstring&);
   const FString& operator = (const wchar_t*);
   FString& operator = (const std::string&);
   const FString& operator = (const char*);
   const FString& operator = (const wchar_t);
   const FString& operator = (const char);

   const FString& operator += (const FString&);
   const FString& operator += (const std::wstring&);
   const FString& operator += (const wchar_t*);
   const FString& operator += (const std::string&);
   const FString& operator += (const char*);
   const FString& operator += (const wchar_t);
   const FString& operator += (const char);

   const FString operator + (const FString&);
   const FString operator + (const std::wstring&);
   const FString operator + (const wchar_t*);
   const FString operator + (const std::string&);
   const FString operator + (const char*);
   const FString operator + (const wchar_t);
   const FString operator + (const char);

   friend const FString operator + (const FString&, const FString&);
   friend const FString operator + (const std::wstring&, const FString&);
   friend const FString operator + (const wchar_t*, const FString&);
   friend const FString operator + (const std::string&, const FString&);
   friend const FString operator + (const char*, const FString&);
   friend const FString operator + (const wchar_t, const FString&);
   friend const FString operator + (const char, const FString&);

   wchar_t& operator [] (uInt);
   const FString  operator () (uInt, uInt);

   bool operator <  (const FString&) const;
   bool operator <= (const FString&) const;
   bool operator == (const FString&) const;
   bool operator != (const FString&) const;
   bool operator >= (const FString&) const;
   bool operator >  (const FString&) const;

   operator const char* () const { return c_str(); }

   const FString& insert (const FString&, uInt);
   const FString& insert (const wchar_t*, uInt);
   const FString& insert (const char*, uInt);

   FString replace (const FString&, const FString&);
   FString replace (const FString&, const std::wstring&);
   FString replace (const FString&, const wchar_t*);
   FString replace (const FString&, const std::string&);
   FString replace (const FString&, const char*);
   FString replace (const FString&, const wchar_t);
   FString replace (const FString&, const char);
   FString replace (const std::wstring&, const FString&);
   FString replace (const std::wstring&, const std::wstring&);
   FString replace (const std::wstring&, const wchar_t*);
   FString replace (const std::wstring&, const std::string&);
   FString replace (const std::wstring&, const char*);
   FString replace (const std::wstring&, const wchar_t);
   FString replace (const std::wstring&, const char);
   FString replace (const std::string&, const FString&);
   FString replace (const std::string&, const std::wstring&);
   FString replace (const std::string&, const wchar_t*);
   FString replace (const std::string&, const std::string&);
   FString replace (const std::string&, const char*);
   FString replace (const std::string&, const wchar_t);
   FString replace (const std::string&, const char);
   FString replace (const wchar_t*, const FString&);
   FString replace (const wchar_t*, const std::wstring&);
   FString replace (const wchar_t*, const wchar_t*);
   FString replace (const wchar_t*, const std::string&);
   FString replace (const wchar_t*, const char*);
   FString replace (const wchar_t*, const wchar_t);
   FString replace (const wchar_t*, const char);
   FString replace (const char*, const FString&);
   FString replace (const char*, const std::wstring&);
   FString replace (const char*, const wchar_t*);
   FString replace (const char*, const std::string&);
   FString replace (const char*, const char*);
   FString replace (const char*, const wchar_t);
   FString replace (const char*, const char);
   FString replace (const wchar_t, const FString&);
   FString replace (const wchar_t, const std::wstring&);
   FString replace (const wchar_t, const wchar_t*);
   FString replace (const wchar_t, const std::string&);
   FString replace (const wchar_t, const char*);
   FString replace (const wchar_t, const wchar_t);
   FString replace (const wchar_t, const char);
   FString replace (const char, const FString&);
   FString replace (const char, const std::wstring&);
   FString replace (const char, const wchar_t*);
   FString replace (const char, const std::string&);
   FString replace (const char, const char*);
   FString replace (const char, const wchar_t);
   FString replace (const char, const char);

   FString replaceControlCodes() const;
   FString expandTabs (uInt tabsize=8) const;
   FString removeDel() const;
   FString removeBackspaces() const;

   const FString& overwrite (const FString&, uInt);
   const FString& overwrite (const wchar_t*, uInt);
   const FString& overwrite (const wchar_t, uInt);

   const FString& remove (uInt, uInt);
   bool includes (const FString&);
   bool includes (const wchar_t*);
   bool includes (const char*);
};


// FString inline functions
//----------------------------------------------------------------------
inline bool FString::isNull() const
{ return ( ! this->string ); }

//----------------------------------------------------------------------
inline bool FString::isEmpty() const
{ return (! this->string ) || (! *this->string); }

//----------------------------------------------------------------------
inline uInt FString::getLength() const
{ return length; }

//----------------------------------------------------------------------
inline FString::iterator FString::begin() const
{ return string; }

//----------------------------------------------------------------------
inline FString::iterator FString::end() const
{ return string + length; }

//----------------------------------------------------------------------
inline wchar_t FString::front() const
{
  assert( ! isEmpty() );
  return string[0];
}

//----------------------------------------------------------------------
inline wchar_t FString::back() const
{
  assert( ! isEmpty() );
  return string[length-1];
}

//----------------------------------------------------------------------
inline sInt16 FString::toShort() const
{ return sInt16( toLong() ); }

//----------------------------------------------------------------------
inline uInt16 FString::toUShort() const
{ return uInt16( toULong() ); }

//----------------------------------------------------------------------
inline int FString::toInt() const
{ return int( toLong() ); }

//----------------------------------------------------------------------
inline uInt FString::toUInt() const
{ return uInt( toULong() ); }

//----------------------------------------------------------------------
inline FString& FString::setNumber (sInt16 num)
{ return setNumber (long(num)); }

//----------------------------------------------------------------------
inline FString& FString::setNumber (uInt16 num)
{ return setNumber (uLong(num)); }

//----------------------------------------------------------------------
inline FString& FString::setNumber (int num)
{ return setNumber (long(num)); }

//----------------------------------------------------------------------
inline FString& FString::setNumber (uInt num)
{ return setNumber (uLong(num)); }

//----------------------------------------------------------------------
inline FString& FString::setFormatedNumber (sInt16 num, char separator)
{ return setFormatedNumber (long(num), separator); }

//----------------------------------------------------------------------
inline FString& FString::setFormatedNumber (uInt16 num, char separator)
{ return setFormatedNumber (uLong(num), separator); }

//----------------------------------------------------------------------
inline FString& FString::setFormatedNumber (int num, char separator)
{ return setFormatedNumber (long(num), separator); }

//----------------------------------------------------------------------
inline FString& FString::setFormatedNumber (uInt num, char separator)
{ return setFormatedNumber (uLong(num), separator); }


#endif  // _FSTRING_H