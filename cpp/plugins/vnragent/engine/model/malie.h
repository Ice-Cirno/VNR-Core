#pragma once

// malie.h
// 8/8/2015 jichi

#include "engine/enginemodel.h"

class MalieEngine : public EngineModel
{
  SK_EXTEND_CLASS(MalieEngine, EngineModel)
  static bool attach();
  //static QString rubyCreate(const QString &rb, const QString &rt);
  //static QString rubyRemove(const QString &text);
public:
  MalieEngine()
  {
    name = "EmbedMalieEngine";
    encoding = Utf16Encoding;
    //enableDynamicFont = true;
    //newLineString = "\n";
    matchFiles << "Malie*"; // Malie.ini or Malie.exe or MalieCfg.exe
    attachFunction = &Self::attach;
  }
};

// EOF
