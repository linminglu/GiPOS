#ifndef __STRINGCONVERT_H__
#define __STRINGCONVERT_H__



BOOL CString2MultiByteW( CString srcStr, CHAR* lpMultiByte, int iByteLen );
BOOL CString2MultiByteA( CString srcStr, CHAR* lpMultiByte, int iByteLen );


#ifdef UNICODE
#define CString2MultiByte  CString2MultiByteW
#else
#define CString2MultiByte  CString2MultiByteA
#endif // UNICODE


BOOL CString2WideCharW( CString srcStr, WCHAR* lpWideChar, int iCharLen );
BOOL CString2WideCharA( CString srcStr, WCHAR* lpWideChar, int iCharLen );
#ifdef UNICODE
#define CString2WideChar  CString2WideCharW
#else
#define CString2WideChar  CString2WideCharA
#endif // UNICODE


BOOL MultiByte2CStringW( CHAR* lpMultiByte, int iByteLen, CString &destStr );
BOOL MultiByte2CStringA( CHAR* lpMultiByte, int iByteLen, CString &destStr );

#ifdef UNICODE
#define MultiByte2CString  MultiByte2CStringW
#else
#define MultiByte2CString  MultiByte2CStringA
#endif // UNICODE


BOOL WideChar2CStringW( WCHAR* lpWideChar, int iCharLen, CString &destStr );
BOOL WideChar2CStringA( WCHAR* lpWideChar, int iCharLen, CString &destStr );

#ifdef UNICODE
#define WideChar2CString   WideChar2CStringW
#else
#define WideChar2CString   WideChar2CStringA
#endif // UNICODE


BOOL MultiByte2WideChar( CHAR* lpMultiByte, int iByteLen, WCHAR* lpWideChar, int iCharLen );
BOOL WideChar2MultiByte( WCHAR* lpWideChar, int iCharLen, CHAR* lpMultiByte, int iByteLen );
char* UnicodeToANSI(LPCTSTR str);
WCHAR* ANSI2Unicode(LPCSTR str);
CString URLEncode(CString strIn);


#endif // __STRINGCONVERT_H__
