#pragma once

// hijackfuns.h
// 6/3/2015 jichi

#include <windows.h>

namespace Hijack {

#define DEF_FUN(_fun, _return, ...) \
  typedef _return (WINAPI *_fun##_fun_t)(__VA_ARGS__); \
  extern _fun##_fun_t old##_fun; \
  _return WINAPI new##_fun(__VA_ARGS__);

  DEF_FUN(CreateFontIndirectA, HFONT, const LOGFONTA *lplf)
  DEF_FUN(CreateFontIndirectW, HFONT, const LOGFONTW *lplf)

  DEF_FUN(CreateFontA, HFONT, int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet, DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality, DWORD fdwPitchAndFamily, LPCSTR lpszFace)
  DEF_FUN(CreateFontW, HFONT, int nHeight, int nWidth, int nEscapement, int nOrientation, int fnWeight, DWORD fdwItalic, DWORD fdwUnderline, DWORD fdwStrikeOut, DWORD fdwCharSet, DWORD fdwOutputPrecision, DWORD fdwClipPrecision, DWORD fdwQuality, DWORD fdwPitchAndFamily, LPCWSTR lpszFace)

  DEF_FUN(GetGlyphOutlineA, DWORD, HDC hdc, UINT uChar, UINT uFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpvBuffer, const MAT2 *lpmat2)
  DEF_FUN(GetGlyphOutlineW, DWORD, HDC hdc, UINT uChar, UINT uFormat, LPGLYPHMETRICS lpgm, DWORD cbBuffer, LPVOID lpvBuffer, const MAT2 *lpmat2)

  DEF_FUN(GetTextExtentPoint32A, BOOL, HDC hdc, LPCSTR lpString, int cchString, LPSIZE lpSize)
  DEF_FUN(GetTextExtentPoint32W, BOOL, HDC hdc, LPCWSTR lpString, int cchString, LPSIZE lpSize)

  DEF_FUN(GetTextExtentExPointA, BOOL, HDC hdc, LPCSTR lpszStr, int cchString, int nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize)
  DEF_FUN(GetTextExtentExPointW, BOOL, HDC hdc, LPCWSTR lpszStr, int cchString, int nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize)

  DEF_FUN(GetCharABCWidthsA, BOOL, HDC hdc, UINT uFirstChar, UINT uLastChar,  LPABC lpabc)
  DEF_FUN(GetCharABCWidthsW, BOOL, HDC hdc, UINT uFirstChar, UINT uLastChar,  LPABC lpabc)

  DEF_FUN(TextOutA, BOOL, HDC hdc, int nXStart, int nYStart, LPCSTR lpString, int cchString)
  DEF_FUN(TextOutW, BOOL, HDC hdc, int nXStart, int nYStart, LPCWSTR lpString, int cchString)

  DEF_FUN(ExtTextOutA, BOOL, HDC hdc, int X, int Y, UINT fuOptions, const RECT *lprc, LPCSTR lpString, UINT cbCount, const INT *lpDx)
  DEF_FUN(ExtTextOutW, BOOL, HDC hdc, int X, int Y, UINT fuOptions, const RECT *lprc, LPCWSTR lpString, UINT cbCount, const INT *lpDx)

  //DEF_FUN(TabbedTextOutA, LONG, HDC hDC, int X, int Y, LPCSTR lpString, int nCount, int nTabPositions, const LPINT lpnTabStopPositions, int nTabOrigin)
  //DEF_FUN(TabbedTextOutW, LONG, HDC hDC, int X, int Y, LPCWSTR lpString, int nCount, int nTabPositions, const LPINT lpnTabStopPositions, int nTabOrigin)

#undef DEF_FUN

// Global variables

} // namespace Hijack

// EOF