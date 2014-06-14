# coding: utf8
# cabochaparse.py
# 6/13/2014 jichi
#
# See: cabocha/src/tree.cpp
#   void write_tree(const Tree &tree, StringBuffer *os, int output_layer, int charset)
#    const size_t size = tree.token_size();
#    for (size_t i = 0; i < size;) {
#      size_t cid = i;
#      chunks.resize(chunks.size() + 1);
#      std::string surface;
#      for (; i < size; ++i) {
#        const Token *token = tree.token(i);
#        if (in && token->ne &&
#            (token->ne[0] == 'B' || token->ne[0] == 'O')) {
#          surface += "</";
#          surface += ne;
#          surface += ">";
#          in = false;
#        }
#
#        if (i != cid && token->chunk) {
#          break;
#        }
#
#        if (token->ne && token->ne[0] == 'B') {
#          ne = std::string(token->ne + 2);
#          surface += "<";
#          surface += ne;
#          surface += ">";
#          in = true;
#        }
#       surface += std::string(token->surface);

if __name__ == '__main__': # DEBUG
  import sys
  sys.path.append("..")

#import re
import CaboCha
import MeCab
from sakurakit import skos, skstr
from cconv import cconv
from jptraits import jpchars
from mecabjlp import mecabdef, mecabfmt

if skos.WIN:
  from msime import msime
  HAS_MSIME = msime.ja_valid() # cached
else:
  HAS_MSIME = False

DEBUG = True
#DEBUG = False

## Parser ##

def parse(text, parser=None, type=False, fmt=mecabfmt.DEFAULT, reading=False, feature=False, lougo=False, ruby=mecabdef.RB_HIRA, readingTypes=(mecabdef.TYPE_VERB, mecabdef.TYPE_NOUN)):
  """
  @param  text  unicode
  @param  parser  CaboCha.Parser
  @param  fmt  mecabfmt
  @param* type  bool  whether return type
  @param* reading  bool   whether return yomigana
  @param* feature  bool   whether return feature
  @param* ruby  unicode
  @param* readingTypes  (int type) or [int type]
  @param* lougo  bool
  @yield  (unicode surface, int type, unicode yomigana or None, unicode feature or None)
  """
  if not parser:
    import cabocharc
    parser = cabocharc.parser()
  if reading:
    wordtrans = _wordtrans if ruby == mecabdef.RB_TR else None
    katatrans = (cconv.kata2hira if ruby == mecabdef.RB_HIRA else
                 cconv.kata2hangul if ruby == mecabdef.RB_HANGUL else
                 cconv.kata2thai if ruby == mecabdef.RB_THAI else
                 cconv.kata2kanji if ruby == mecabdef.RB_KANJI else
                 cconv.kata2romaji if ruby in (mecabdef.RB_ROMAJI, mecabdef.RB_TR) else
                 None)
    if ruby in (mecabdef.RB_ROMAJI, mecabdef.RB_HANGUL, mecabdef.RB_THAI, mecabdef.RB_KANJI):
      readingTypes = None
  encoding = mecabdef.DICT_ENCODING
  feature2katana = fmt.getkata

  tree = parser.parse(text.encode(encoding))
  size = tree.token_size()
  newgroup = True
  group_id = 0
  if DEBUG:
     group_surface = ''
  for i in range(tree.token_size()):
    token = tree.token(i)
    surface = token.surface.decode(encoding, errors='ignore')

    if newgroup and token.chunk:
      group_id += 1
      if DEBUG:
        print "group surface %s:" % group_id, group_surface
      group_surface = ''
      newgroup = False
    if DEBUG:
      group_surface += surface
    newgroup = True

    if len(surface) == 1 and surface in jpchars.set_punc:
      char_type = mecabdef.TYPE_PUNCT
    else:
      char_type = mecabdef.TYPE_VERB # TODO, the type of the character is missing!

    if reading:
      yomigana = None
      #if node.char_type in (mecabdef.TYPE_VERB, mecabdef.TYPE_NOUN, mecabdef.TYPE_KATAGANA, mecabdef.TYPE_MODIFIER):
      f = None
      if feature:
        f = token.feature.decode(encoding, errors='ignore')
      if not readingTypes or char_type in readingTypes or char_type == mecabdef.TYPE_KATAGANA and wordtrans: # always translate katagana
        if wordtrans:
          if not yomigana:
            yomigana = wordtrans(surface)
        if not yomigana and not lougo:
          if not feature:
            f = token.feature.decode(encoding, errors='ignore')
          katagana = feature2katana(f)
          if katagana:
            furigana = None
            if katagana == '*':
              # Use MSIME as fallback
              unknownYomi = True
              if HAS_MSIME and len(surface) < msime.IME_MAX_SIZE:
                if ruby == mecabdef.RB_HIRA:
                  yomigana = msime.to_yomi_hira(surface)
                else:
                  yomigana = msime.to_yomi_kata(surface)
                  if yomigana:
                    if ruby == mecabdef.RB_HIRA:
                      pass
                    elif ruby == mecabdef.RB_ROMAJI:
                      yomigana = cconv.wide2thin(cconv.kata2romaji(yomigana))
                      if yomigana == surface:
                        yomigana = None
                        unknownYomi = False
                    elif ruby == mecabdef.RB_HANGUL:
                      yomigana = cconv.kata2hangul(yomigana)
                    elif ruby == mecabdef.RB_KANJI:
                      yomigana = cconv.kata2kanji(yomigana)
              if not yomigana and unknownYomi and readingTypes:
                yomigana = '?'
            else:
              #katagana = _repairkatagana(katagana)
              yomigana = katatrans(katagana) if katatrans else katagana
              if yomigana == surface:
                yomigana = None
      if not type and not feature:
        yield surface, yomigana
      elif type and not feature:
        yield surface, char_type, yomigana
      elif not type and feature:
        yield surface, yomigana, f
      else: # render all
        yield surface, char_type, yomigana, f
    elif not type and not feature:
      yield surface
    elif type and not feature: # and type
      yield surface, char_type
    elif not type and feature:
      f = token.feature.decode(encoding, errors='ignore')
      yield surface, f
    elif type and feature:
      f = token.feature.decode(encoding, errors='ignore')
      yield surface, char_type, f
    #else:
    #  assert False, "unreachable"

if __name__ == '__main__':
  c = CaboCha.Parser()

  #t = u"太郎はこの本を二郎を見た女性に渡した。"
  t = u"「どれだけ必死に働こうとも、所詮、安月給の臨時教師ですけどね」"

  if True:
    for it in parse(t, parser=c, reading=True):
      print it[0], it[1]


  if False:
    sentence = t.encode('utf8')
    print c.parseToString(sentence)

    tree =  c.parse(sentence)

    print tree.toString(CaboCha.FORMAT_TREE)
    #print tree.toString(CaboCha.FORMAT_LATTICE)

    print '#', type(c)
    print dir(c)
    print
    print '#', type(tree)
    print dir(tree)

    print tree.chunk_size()
    print tree.empty()
    print tree.output_layer()
    print tree.posset()
    #print tree.read()
    print tree.sentence()
    print tree.sentence_size()

    # This is the original logic
    size = tree.token_size()
    i = 0
    while i < size:
      cid = i
      surface = ''
      while i < size:
        token = tree.token(i)
        if i != cid and token.chunk:
          break
        surface += token.surface
        i += 1
      print cid, surface

    # This is my logic
    print '-' * 5

    surf = ''
    for i in range(tree.token_size()):
      tok = tree.token(i)
      if surf and tok.chunk:
        print surf
        surf = ''
      surf += tok.surface
    if surf:
      print surf
      surf = ''

    print '-' * 5

    tok = tree.token(0)
    print
    print '#', type(tok)
    print dir(tok)
    print tok.surface
    print tok.feature
    print tok.ne
    print tok.additional_info
    print tok.feature_list_size
    #print tok.feature_list(0)
    #print tok.feature_list(1)

# EOF
