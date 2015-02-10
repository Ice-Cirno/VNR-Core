# coding: utf8
# bingdef.py
# 11/2/2014 jichi

LANG_LOCALES = {
  'zht': 'zh-CHT',
  'zhs': 'zh-CHS',
}
def lang2locale(lang):
  """
  @param  lang  unicode
  @return  unicode
  """
  return LANG_LOCALES.get(lang) or lang

def mt_lang_test(to, fr, online=False): return True # str, str -> bool # all languages are supported
def tts_lang_test(lang): return True # str -> bool # all languages are supported

# EOF
