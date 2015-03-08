#ifndef TRDDECODERULE_H
#define TRDDECODERULE_H

// trdecoderule.h
// 9/20/2014 jichi

#include "trcodec/trrule.h"
#include "sakurakit/skglobal.h"
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <cstdint>

#ifdef __clang__
# pragma clang diagnostic ignored "-Wlogical-op-parentheses"
#endif // __clang__

class TranslationDecodeRule : private TranslationRule
{
  SK_EXTEND_CLASS(TranslationDecodeRule, TranslationRule)

  std::wstring token,
               target,
               source;
  boost::wregex *source_re; // cached compiled regex
  int source_symbol_count;
  mutable bool valid; // whether the object is valid

public:
  TranslationDecodeRule()
    : source_re(nullptr)
    , source_symbol_count(0)
    , valid(false)
  {}

  ~TranslationDecodeRule()
  { if (source_re) delete source_re; }

  bool match_category(int v) const { return !v || !category || v & category; }

  void init(const TranslationRule &param);
  bool is_valid() const { return valid; }
  bool is_symbolic() const { return source_symbol_count; }

  // Replacement
private:
  void init_source(); // may throw regular expression exception
  void init_target();
  void cache_target() const;

  void string_replace(std::wstring &ret) const;
  void regex_replace(std::wstring &ret) const;

  bool string_exists(const std::wstring &t) const // inline to make this function faster
  { return is_icase() ? boost::algorithm::icontains(t, source) : boost::algorithm::contains(t, source); }

  bool regex_exists(const std::wstring &t) const;

  bool exists(const std::wstring &text) const
  { return is_regex() ? regex_exists(text) : string_exists(text); }

public:
  bool replace(std::wstring &ret) const
  {
    if (exists(ret)) {
      if (is_regex())
        regex_replace(ret);
      else
        string_replace(ret);
      return true;
    }
    return false;
  }
};

#endif // TRDECODERULE_H
