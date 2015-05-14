# coding: utf8
# getfont.py
# Get the Hanazono Font.
# 5/7/2015 jichi

if __name__ == '__main__':
  import initrc
  initrc.chcwd()
  initrc.initenv()

  import os
  title = os.path.basename(__file__)
  initrc.settitle(title)

import os
from sakurakit.skdebug import dprint, dwarn
from sakurakit.skprof import SkProfiler

FONTS = {
  'hanazono': {
    'size': 26963516,
    'name': 'Hanazono',
    'path': 'Hanazono',
    'hp': 'http://fonts.jp/hanazono',
    'dl': "http://jaist.dl.sourceforge.jp/hanazono-font/62072/hanazono-20141012.zip",
  },
}

import initdefs
FONT_DIR = initdefs.CACHE_FONT_RELPATH
TMP_DIR = initdefs.TMP_RELPATH

# Tasks

def init(): # raise
  for it in TMP_DIR, FONT_DIR:
    if not os.path.exists(it):
      os.makedirs(it)

def extract(family): # str -> bool
  dprint("enter: family = %s" % family)

  srcpath = TMP_DIR + '/font-%s.zip' % family
  tmppath = TMP_DIR + '/font-%s' % family
  targetpath = FONT_DIR + '/' + FONTS[family]['path']

  import shutil
  from sakurakit import skfileio
  with SkProfiler("extract"):
    ok = skfileio.extractzip(srcpath, tmppath)
  if ok:
    if os.path.exists(targetpath):
      shutil.rmtree(targetpath)
    os.renames(tmppath, targetpath)
  if os.path.exists(tmppath):
    shutil.rmtree(tmppath)
  skfileio.removefile(srcpath)

  dprint("leave: ok = %s" % ok)
  return ok

def get(family): # str -> bool
  url = FONTS[family]['dl']
  path = TMP_DIR + '/font-%s.zip' % family

  dprint("enter: family = %s, url = %s" % (family, url))

  #from sakurakit import skfileio
  #if os.path.exists(path) and skfileio.filesize(path) == size:
  #  dprint("leave: already downloaded")
  #  return True

  ok = False
  from sakurakit import skfileio, sknetio
  with SkProfiler("fetch"):
    if sknetio.getfile(url, path, flush=False): # flush=false to use more memory to reduce disk access
      ok = skfileio.filesize(path) == FONTS[family]['size']
  if not ok and os.path.exists(path):
    skfileio.removefile(path)
  dprint("leave: ok = %s" % ok)
  return ok

def lock(family): # str
  name = "font.%s.lock" % family
  import initrc
  if initrc.lock(name):
    return True
  else:
    dwarn("multiple instances")
    return False

def run(family): # str -> bool
  if family not in FONTS:
    dwarn("unknown font: %s" % family)
    return False
  return lock(family) and get(family) and extract(family)

# Main process

def usage():
  print 'usage:', '|'.join(FONTS.iterkeys())

def msg(family): # str ->
  font = FONTS[family]
  import messages
  messages.info(
    name=font['name'],
    location="Caches/Fonts/" + font['path'],
    size=font['size'],
    urls=[font['hp']],
  )

def main(argv):
  """
  @param  argv  [unicode]
  @return  int
  """
  dprint("enter")
  ok = False
  if not argv or len(argv) == 1 and argv[0] in ('-h', '--help'):
    usage()
  elif len(argv) != 1:
    dwarn("invalid number of parameters")
    usage()
  else:
    family, = argv
    try:
      msg(family)
      init()
      ok = run(family)
      if ok:
        from sakurakit import skos
        path = os.path.join(FONT_DIR, FONTS[family]['path'])
        skos.open_location(os.path.abspath(path))
    except Exception, e:
      dwarn(e)
  ret = 0 if ok else 1
  dprint("leave: ret = %s" % ret)
  return ret

if __name__ == '__main__':
  import sys
  ret = main(sys.argv[1:])
  sys.exit(ret)

# EOF