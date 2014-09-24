# coding: utf8
# 8/10/2014

if __name__ == '__main__':
  import sys
  sys.path.append('..')

# Interface

class MachineTokenizer(object):
  def tokenize(self, text): pass # unicode -> list  cascaded lists of tokens

class MachineParser(object):
  def parse(self, tokens): pass # list -> tree

class MachineTransformer(object):
  def transform(self, tree): pass # tree -> tree

class MachineTranslator(object):
  def translate(self, text): pass # unicode -> unicode

# Japanese tokenizer

import lex
# The same as lex.py
TOKEN_TYPE_NULL = ''
TOKEN_TYPE_KANJI = 'kanji'
TOKEN_TYPE_RUBY = 'ruby'
TOKEN_TYPE_PUNCT = 'punct'
TOKEN_TYPE_LATIN = 'latin'

TOKEN_PUNCT_NULL = 0
TOKEN_PUNCT_STOP = 1 << 1 # period
TOKEN_PUNCT_PAUSE = 1 << 2 # comma

# Three-dot is a stop, two-dot is a pause
_PAUSE_PUNCT = u"、‥『』"
_STOP_PUNCT = u"。？！「」♡…"
def token_punct_flags(text):
  ret = 0
  if text in _PAUSE_PUNCT:
    ret |= TOKEN_PUNCT_PAUSE
  elif text in _STOP_PUNCT:
    ret |= TOKEN_PUNCT_STOP
  return ret

class Token(object):
  def __init__(self, text, type=TOKEN_TYPE_NULL, flags=0, feature=''):
    self.text = text # unicode
    self.feature = feature # unicode
    self.type = type # int
    self.flags = flags

class JapaneseToken(Token):
  def __init__(self, text, **kwargs):
    type = lex.text_type(text)
    flags = 0
    if type == TOKEN_TYPE_PUNCT:
      flags = token_punct_flags(text)
    super(JapaneseToken, self).__init__(text=text, type=type, flags=flags, **kwargs)

class ChineseToken(Token):
  def __init__(self, text):
    super(ChineseToken, self).__init__(text=text)

class CaboChaTokenizer(MachineTokenizer):
  def __init__(self):
    super(CaboChaTokenizer, self).__init__()
    self.encoding = 'utf8' # cabocha dictionary encoding

    import CaboCha
    self.parser = CaboCha.Parser()

  def tokenize(self, text):
    """@reimp
    @param  text  unicode
    @return  [[JapaneseToken], int link]  group with the same link should be put in the same phrase
    """
    ret = []
    encoding = self.encoding
    tree = self.parser.parse(text.encode(encoding))

    newgroup = False
    link = 0
    group = []
    for i in xrange(tree.token_size()):
      token = tree.token(i)

      surface = token.surface.decode(encoding, errors='ignore')
      feature = token.feature.decode(encoding, errors='ignore')

      if not i and token.chunk: # first element
        link = token.chunk.link

      if newgroup and token.chunk:
        ret.append((group, link))
        group = [JapaneseToken(text=surface, feature=feature)]
        link = token.chunk.link
        newgroup = False
      else:
        group.append(JapaneseToken(text=surface, feature=feature))
      newgroup = True

    if group:
      ret.append((group, link))
    return ret

# Japanese parser

#AST_PHRASE_NULL = "null"
#AST_PHRASE_NOUN = "noun"
#AST_PHRASE_VERB = "verb"
#AST_PHRASE_ADJ = "adj" # adjective
#AST_PHRASE_ADV = "adv" # adverb
#AST_PHRASE_SUB = "sub" # suject
#AST_PHRASE_OBJ = "obj" # object
#AST_PHRASE_PRED = "pred" # predicate

AST_CLASS_NULL = "null"
AST_CLASS_NODE = "node"
AST_CLASS_CONTAINER = "container"
AST_CLASS_PARAGRAPH = "paragraph"
AST_CLASS_SENTENCE = "sentence"
AST_CLASS_CLAUSE = "clause"
AST_CLASS_PHRASE = "phrase"
AST_CLASS_WORD = "word"

class ASTNode(object): # abstract
  classType = AST_CLASS_NODE
  def __init__(self):
    self.parent = None # ASTNode  parent
    self.previous = None # ASTNode  sibling
    self.next = None # ASTNode  sibling

  def unparse(self): assert False; return "" # unicode

class ASTNull(ASTNode): # abstract
  classType = AST_CLASS_NULL
  def __init__(self):
    super(ASTNull, self).__init__()

  def unparse(self):
    """@reimp"""
    return ""

class ASTContainer(ASTNode): # abstract
  classType = AST_CLASS_CONTAINER
  def __init__(self, children=[]):
    super(ASTContainer, self).__init__()
    self.children = children # [ASTNode]
    for i,it in enumerate(children):
      it.parent = self
      if i > 0:
        it.previous = children[i-1]
      if i < len(children) - 1:
        it.next = children[i+1]

  def unparse(self):
    """@reimp"""
    return "".join((it.unparse()for it in self.children))

  def removeLastChild(self):
    l = self.children
    if l:
      last = l.pop()
      if l:
        l[-1].next = None


class ASTParagraph(ASTContainer): # container of sentences
  classType = AST_CLASS_PARAGRAPH
  def __init__(self, *args, **kwargs):
    super(ASTParagraph, self).__init__(*args, **kwargs)

class ASTSentence(ASTContainer): # container of phrases
  classType = AST_CLASS_SENTENCE
  def __init__(self, children=[], hasPunct=False):
    super(ASTSentence, self).__init__(children=children)
    self.hasPunct = hasPunct # bool

class ASTClause(ASTContainer): # container of phrases
  classType = AST_CLASS_CLAUSE
  def __init__(self, children=[], hasPunct=False):
    super(ASTClause, self).__init__(children=children)
    self.hasPunct = hasPunct # bool

class ASTPhrase(ASTContainer): # container of [phrase or word]
  classType = AST_CLASS_PHRASE
  def __init__(self, *args, **kwargs):
    super(ASTPhrase, self).__init__(*args, **kwargs)

class ASTWord(ASTNode):
  classType = AST_CLASS_WORD
  def __init__(self, token=None):
    super(ASTWord, self).__init__()
    self.token = token # Token

  def unparse(self):
    """@reimp"""
    return self.token.text if self.token else ''

class JapaneseParser(MachineParser):
  def __init__(self):
    super(JapaneseParser, self).__init__()

  def _reduceLinkedPhrases(self, linkedphrases):
    """
    @param  linkedphrases  [phrase, int link]
    @return  [phrase]
    """
    if not linkedphrases:
      return []
    if len(linkedphrases) == 1:
      return [linkedphrases[0][0]]

    lastphrase, lastlink = linkedphrases.pop()

    splitindex = None
    for i,(phrase,link) in enumerate(linkedphrases):
      if link >= lastlink:
        splitindex = i

    if splitindex is None:
      l = self._reduceLinkedPhrases(linkedphrases)
      if not l:
        l = [lastphrase]
      elif len(l) == 1:
        l = [l[0], lastphrase]
      else:
        l = [ASTPhrase(children=l), lastphrase]

    else:
      left = linkedphrases[:splitindex+1]
      left = self._reduceLinkedPhrases(left)
      if len(left) == 1:
        left = left[0]
      elif left:
        left = ASTPhrase(children=left)

      right = linkedphrases[splitindex+1:]
      right = self._reduceLinkedPhrases(right)
      if len(right) == 1:
        right = right[0]
      elif right:
        right = ASTPhrase(children=right)

      l = []
      if left:
        l.append(left)
      if right:
        l.append(right)
      l.append(lastphrase)
    return [ASTPhrase(children=l)]

  def parse(self, tokens):
    """@reimp
    @param  tokens  [[Token]]
    @return  ASTNode
    """
    paragraph_sentences = []
    sentence_clauses = []

    linked_phrases = [] # [phrase, int link]

    for index,(group,link) in enumerate(tokens):
      words = [ASTWord(token=token) for token in group]
      phrase = ASTPhrase(children=words)

      if link == -1:
        link = index
      linked_phrases.append((phrase, link))

      last = group[-1]
      if last.type == TOKEN_TYPE_PUNCT:
        phrases = self._reduceLinkedPhrases(linked_phrases)
        linked_phrases = []
        clause = ASTClause(children=phrases, hasPunct=True)
        sentence_clauses.append(clause)
        if last.flags & TOKEN_PUNCT_STOP:
          sentence = ASTSentence(children=sentence_clauses, hasPunct=True)
          paragraph_sentences.append(sentence)
          paragraph_sentences = []

    if linked_phrases:
      phrases = self._reduceLinkedPhrases(linked_phrases)
      clause = ASTClause(children=phrases, hasPunct=False)
      sentence_clauses.append(clause)

    if sentence_clauses:
      sentence = ASTSentence(children=sentence_clauses, hasPunct=False)
      paragraph_sentences.append(sentence)

    ret = ASTParagraph(children=paragraph_sentences)
    return ret

# Japanese-Chinese translator

J2C_PUNCT = {
  u"、": u"，",
}

J2C_WORDS = {
  u"多く": u"许多",
  u"あなた": u"你",
}

class JapaneseChineseTransformer(MachineTransformer):
  def __init__(self, fallbackTranslate=None):
    super(JapaneseChineseTransformer, self).__init__()

    if not fallbackTranslate:
      fallbackTranslate = lambda x:x
    self.fallbackTranslate = fallbackTranslate # unicode text -> unicode text

  def transform(self, tree):
    """@reimp"""
    if not tree:
      return ASTNull()
    ret = self.transformNode(tree)
    self.updateToken(ret)
    return ret

  # Context insensitive transformation

  def updateToken(self, node):
    assert node
    if node.classType == AST_CLASS_WORD:
      token = node.token
      if token.type == TOKEN_TYPE_PUNCT:
        token.text = self.transformPunctuation(token.text)
    else:
      for it in node.children:
        self.updateToken(it)

  def transformPunctuation(self, text):
    return J2C_PUNCT.get(text) or text

  # Context sensitive transformation

  def transformNode(self, node):
    assert node
    if node.classType == AST_CLASS_PARAGRAPH:
      return self.transformParagraph(node)
    else:
      return ASTNull()

  def transformParagraph(self, node):
    cls = ASTParagraph
    assert node and node.classType == cls.classType
    return cls(children=map(self.transformSentence, node.children))

  def transformSentence(self, node):
    cls = ASTSentence
    assert node and node.classType == cls.classType
    return cls(children=map(self.transformClause, node.children), hasPunct=node.hasPunct)

  def transformClause(self, node):
    cls = ASTClause
    assert node and node.classType == cls.classType
    return cls(children=map(self.transformPhrase, node.children), hasPunct=node.hasPunct)

  def transformPhraseOrWord(self, node):
    assert node
    if node.classType == AST_CLASS_PHRASE:
      return self.transformPhrase(node)
    if node.classType == AST_CLASS_WORD:
      return self.transformWord(node)
    assert False

  def transformPhrase(self, node):
    cls = ASTPhrase
    assert node and node.classType == cls.classType
    return cls(children=self.transformPhraseOrWordList(node.children))

  def transformPhraseOrWordList(self, nodes): # [ASTNode]
    if len(nodes) == 1:
      return [self.transformPhraseOrWord(nodes[0])]
    else:
       # Machine translation rules
      last = nodes[-1]
      if last.classType == AST_CLASS_WORD:
        token = last.token
        if token.text == u"の":
          l = self.transformPhraseOrWordList(nodes[:-1])
          l.append(ASTWord(token=ChineseToken(u"的")))
          return l
        elif token.text == u"が":
          l = self.transformPhraseOrWordList(nodes[:-1])
          l.append(ASTWord(token=ChineseToken(u"在")))
          return l
        elif token.text == u"は":
          return self.transformPhraseOrWordList(nodes[:-1])
      elif last.classType == AST_CLASS_PHRASE:
        # TODO: This modification should happen only after the other places has been translated
        phrases = last.children
        lastlast = phrases[-1]
        if lastlast.classType == AST_CLASS_WORD:
          token = lastlast.token
          if token.text == u"で":
            last.removeLastChild()
            l = self.transformPhraseOrWordList(nodes)
            l.insert(0, ASTWord(token=ChineseToken(u"在")))
            return l
      return map(self.transformPhraseOrWord, nodes)

  def transformWord(self, node):
    cls = ASTWord
    assert node and node.classType == cls.classType

    text = node.token.text

    next = node.next
    if text == u"大小" and next and next.classType == AST_CLASS_WORD and next.token.text == u"の":
      text = u"大大小小"

    text = J2C_WORDS.get(text) or text
    return cls(token=ChineseToken(text))

# Japanese-Chinese translator

class JapaneseChineseTranslator(MachineTranslator):
  def __init__(self):
    super(JapaneseChineseTranslator, self).__init__()

    self.tokenizer = CaboChaTokenizer()
    self.parser = JapaneseParser()
    self.transformer = JapaneseChineseTransformer()

  def translate(self, text):
    """@reimp"""
    tokens = self.tokenizer.tokenize(text)
    tree = self.parser.parse(tokens)
    tree = self.transformer.transform(tree)
    return tree.unparse()

# Alternative machine translator

class GoogleTranslator(MachineTranslator):

  def __init__(self, fr='', to=''):
    self.fr = fr # str  language
    self.to = to # str  language

    from google import googletrans
    self._translate = googletrans.translate

  def translate(self, text): # unicode -> unicode
    """@reimp"""
    return self._translate(text, fr=self.fr, to=self.to) or ''

if __name__ == '__main__':
  # baidu: 未来日本在许多城市，大大小小的犯罪蔓延。警察为主的治安机构功能正在逐渐失去了，晓東市是各种各样的犯罪对策进行的事在国内最高水平的治安，保持着。因此，寻求安全的人们聚积晓东市的物价高涨，其结果是资产家大量居住的街道。在这样的状况，所以资产家的女儿和她们（校长，护卫对象）保护保镖同时培养教育机关存在着。
  #text = u"近未来の日本、多くの都市で大小の犯罪が蔓延。警察を主とした治安機関は機能を失いつつあったが、暁東市は様々な犯罪対策を行なう事で国内でもトップクラスの治安を保っていた。そのため、安全を求める人々が集り暁東市の物価は高騰、その結果資産家が多く住む街となった。そのような状況のため、資産家の令嬢と彼女ら（プリンシパル、護衛対象者）を守るボディーガードを同時に育成する教育機関が存在している。"

  # baidu: 未来日本在许多城市，大大小小的犯罪蔓延。
  # manual: 近未来的日本，大大小小的犯罪在许多城市蔓延。
  #text = u"近未来の日本、多くの都市で大小の犯罪が蔓延。"
  #text = u"警察を主とした治安機関は機能を失いつつあったが、暁東市は様々な犯罪対策を行なう事で国内でもトップクラスの治安を保っていた。"
  #text = u"憎しみは憎しみしか生まない。"
  text = u"あなたは誰ですか？"

  print "-- test tokenizer --"
  _t = CaboChaTokenizer()
  tokens = _t.tokenize(text)
  for i,(group, link) in enumerate(tokens):
    print i, link, ','.join(t.text for t in group)

  print "-- test parser --"

  _p = JapaneseParser()
  tree = _p.parse(tokens)
  print tree.unparse()


  print "-- test translator --"
  _g = GoogleTranslator(fr='ja', to='zhs')

  _t = JapaneseChineseTransformer(fallbackTranslate=_g.translate)

  tree = _t.transform(tree)
  print tree.unparse()

  print "-- test translator --"
  _d = JapaneseChineseTranslator()
  trans = _d.translate(text)
  print trans

# EOF
