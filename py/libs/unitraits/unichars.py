# coding: utf8
# unichars.py
# 6/16/2014 jichi

# Orders of hiragana and katagana
ORD_HIRA_FIRST = 12353
ORD_HIRA_LAST = 12438
DIST_HIRA_KATA = 96
ORD_KATA_FIRST = ORD_HIRA_FIRST + DIST_HIRA_KATA
ORD_KATA_LAST = ORD_HIRA_LAST + DIST_HIRA_KATA

# Orders of wide and thin characters
ORD_THIN_FIRST = 33
ORD_THIN_LAST = 126
DIST_THIN_WIDE = 65248
ORD_WIDE_FIRST = ORD_THIN_FIRST + DIST_THIN_WIDE
ORD_WIDE_LAST = ORD_THIN_LAST + DIST_THIN_WIDE

ORD_KANJI_FIRST = 19968
ORD_KANJI_LAST = 40869

ORD_DIGIT_FIRST = ord('0')
ORD_DIGIT_LAST = ord('9')

ORD_IALPHA_FIRST = ord('a')
ORD_IALPHA_LAST = ord('z')
ORD_UALPHA_FIRST = ord('A')
ORD_UALPHA_LAST = ord('Z')

#ORD_NUM_FIRST = ord('0') # 48
#ORD_NUM_LAST = ord('9') # 57

s_ascii_punct = ',.\'"?!~'

def ordany(text, start, stop):
  """
  @param  text  unicode
  @param  start  int
  @param  stop  int
  @return  bool
  """
  for c in text:
    u8 = ord(c)
    if u8 >= start and u8 <= stop:
      return True
  return False

def ordall(text, start, stop):
  """
  @param  text  unicode
  @param  start  int
  @param  stop  int
  @return  bool
  """
  for c in text:
    u8 = ord(c)
    if u8 < start or u8 > stop:
      return False
  return True

def isascii(s):
  """
  @param  s  unicode
  @return  bool
  """
  if len(s) == 1:
    return ord(s) < 128
  else:
    return all(ord(c) < 128 for c in s)

def isspace(ch):
  """
  @param  s  unicode
  @return  bool
  """
  return ch in u" \u3000\t\n"

def isalpha(ch):
  """
  @param  s  unicode
  @return  bool
  """
  if len(ch) == 1:
    ch = ord(ch)
    return ORD_IALPHA_FIRST <= ch and ch <= ORD_IALPHA_LAST or ORD_UALPHA_FIRST <= ch and ch <= ORD_UALPHA_LAST
  return False

# EOF
