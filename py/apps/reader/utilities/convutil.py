# coding: utf8
# convutil.py
# 10/18/2014 jichi

from unitraits.uniconv import hira2kata, kata2hira, thin2wide, wide2thin, wide2thin_digit
from jaconv.jaconv import hira2romaji, hira2hangul, hira2thai \
                        , kata2romaji, kata2hangul, kata2thai \
                        , kana2romaji, kana2hangul, kana2thai \
                        , capitalizeromaji
from opencc.opencc import zht2zhs
from ccman import zhs2zht, zht2zhx

def kana2yomi(text, lang):
  """
  @param  text  unicode
  @param  lang  str
  @return  unicode or None
  """
  if lang == 'ko':
    return kana2hangul(text)
  elif lang == 'th':
    return kana2thai(text)
  else:
    return capitalizeromaji(kana2romaji(text))

# EOF
