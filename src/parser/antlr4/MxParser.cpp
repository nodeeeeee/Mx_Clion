
// Generated from Mx.g4 by ANTLR 4.13.1


#include "../../include/parser/MxListener.h"
#include "../../include/parser/MxVisitor.h"

#include "parser/MxParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MxParserStaticData final {
  MxParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MxParserStaticData(const MxParserStaticData&) = delete;
  MxParserStaticData(MxParserStaticData&&) = delete;
  MxParserStaticData& operator=(const MxParserStaticData&) = delete;
  MxParserStaticData& operator=(MxParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag mxParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
MxParserStaticData *mxParserStaticData = nullptr;

void mxParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (mxParserStaticData != nullptr) {
    return;
  }
#else
  assert(mxParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MxParserStaticData>(
    std::vector<std::string>{
      "prog", "mainFunc", "stat", "specialStat", "regularStat", "varDef", 
      "funcDef", "classFuncDef", "classDef", "ifStat", "assignStat", "block", 
      "forStat", "whileStat", "returnStat", "continue", "break", "expr", 
      "formatString", "funcCall", "arrayConst", "initArray", "initObject", 
      "type", "literal"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "'f\"'", "", "'class'", "'for'", "'while'", 
      "'if'", "'else'", "'int'", "'bool'", "'string'", "'void'", "'main'", 
      "'return'", "'continue'", "'break'", "'new'", "'null'", "", "'this'", 
      "", "", "'$'", "", "", "", "'='", "'+'", "'-'", "'*'", "'/'", "'('", 
      "')'", "'{'", "'}'", "'['", "']'", "'++'", "'--'", "'%'", "'>>'", 
      "'<<'", "'>'", "'<'", "'>='", "'<='", "'=='", "'!='", "'&'", "'^'", 
      "'|'", "'&&'", "'||'", "'\\u003F'", "';'", "':'", "'.'", "','", "'~'", 
      "'!'"
    },
    std::vector<std::string>{
      "", "SL_COMMENT", "ML_COMMENT", "DOCS_COMMENT", "FORMAT_STRING_ELEMENT", 
      "QUOTATION", "FORMAT_STRING_STARTER", "STRING", "CLASS", "FOR", "WHILE", 
      "IF", "ELSE", "INT", "BOOLEAN", "STR", "VOID", "MAIN", "RETURN", "CONTINUE", 
      "BREAK", "NEW", "NULL", "BOOL", "THIS", "WS", "ID", "DOLLAR", "INTEGER", 
      "LETTER", "NUMBER", "EQUAL", "ADD", "SUB", "MUL", "DIV", "LEFT_PARENTHESIS", 
      "RIGHT_PARENTHESIS", "LEFT_CURLY_BRACKET", "RIGHT_CURLY_BRACKET", 
      "LEFT_SQUARE_BRACKET", "RIGHT_SQUARE_BRACKET", "PLUS_PLUS", "MINUS_MINUS", 
      "MOD", "SRL", "SLL", "BT", "LT", "BEQ", "LEQ", "ET", "NET", "AND", 
      "XOR", "OR", "AND_AND", "OR_OR", "QUESTION", "SEMI_COLON", "COLON", 
      "DOT", "COMMA", "WAVE", "EXCLAIMER"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,64,417,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,1,0,1,0,1,0,1,0,1,0,1,0,1,0,5,0,58,8,
  	0,10,0,12,0,61,9,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,5,0,71,8,0,10,0,12,
  	0,74,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,3,2,86,8,2,1,3,1,3,1,
  	3,3,3,91,8,3,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,
  	1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,3,4,116,8,4,1,5,1,5,1,5,1,5,3,5,122,
  	8,5,1,5,1,5,1,5,1,5,3,5,128,8,5,5,5,130,8,5,10,5,12,5,133,9,5,1,6,1,6,
  	1,6,1,6,1,6,1,6,1,6,1,6,1,6,5,6,144,8,6,10,6,12,6,147,9,6,3,6,149,8,6,
  	1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,5,8,170,8,8,10,8,12,8,173,9,8,1,8,1,8,1,9,1,9,1,9,3,9,180,8,9,1,
  	9,1,9,1,9,1,9,3,9,186,8,9,1,10,1,10,1,10,1,10,1,11,1,11,5,11,194,8,11,
  	10,11,12,11,197,9,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,3,12,206,8,12,
  	1,12,1,12,3,12,210,8,12,1,12,1,12,1,12,3,12,215,8,12,1,12,1,12,1,12,1,
  	13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,3,14,229,8,14,1,15,1,15,1,
  	16,1,16,1,17,1,17,1,17,3,17,238,8,17,1,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,3,17,255,8,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,3,17,302,8,17,1,17,1,17,5,17,306,8,17,10,17,12,17,309,9,17,1,18,1,
  	18,1,18,1,18,3,18,315,8,18,1,18,5,18,318,8,18,10,18,12,18,321,9,18,1,
  	18,1,18,1,19,1,19,1,19,1,19,1,19,5,19,330,8,19,10,19,12,19,333,9,19,3,
  	19,335,8,19,1,19,1,19,1,20,1,20,1,20,1,20,5,20,343,8,20,10,20,12,20,346,
  	9,20,3,20,348,8,20,1,20,1,20,1,20,1,20,1,20,5,20,355,8,20,10,20,12,20,
  	358,9,20,1,20,1,20,3,20,362,8,20,1,21,1,21,1,21,1,21,1,21,1,21,4,21,370,
  	8,21,11,21,12,21,371,1,21,1,21,5,21,376,8,21,10,21,12,21,379,9,21,1,21,
  	1,21,1,21,1,21,4,21,385,8,21,11,21,12,21,386,1,21,1,21,3,21,391,8,21,
  	1,22,1,22,1,22,1,22,3,22,397,8,22,1,23,1,23,1,23,1,23,1,23,1,23,3,23,
  	405,8,23,1,23,1,23,1,23,5,23,410,8,23,10,23,12,23,413,9,23,1,24,1,24,
  	1,24,1,195,2,34,46,25,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,
  	36,38,40,42,44,46,48,0,8,1,0,42,43,1,0,63,64,1,0,32,33,2,0,34,35,44,44,
  	1,0,45,46,1,0,47,50,1,0,51,52,3,0,7,7,22,23,28,28,476,0,59,1,0,0,0,2,
  	77,1,0,0,0,4,85,1,0,0,0,6,90,1,0,0,0,8,115,1,0,0,0,10,117,1,0,0,0,12,
  	134,1,0,0,0,14,153,1,0,0,0,16,158,1,0,0,0,18,176,1,0,0,0,20,187,1,0,0,
  	0,22,191,1,0,0,0,24,200,1,0,0,0,26,219,1,0,0,0,28,225,1,0,0,0,30,230,
  	1,0,0,0,32,232,1,0,0,0,34,254,1,0,0,0,36,310,1,0,0,0,38,324,1,0,0,0,40,
  	361,1,0,0,0,42,390,1,0,0,0,44,392,1,0,0,0,46,404,1,0,0,0,48,414,1,0,0,
  	0,50,51,3,16,8,0,51,52,5,59,0,0,52,58,1,0,0,0,53,54,3,10,5,0,54,55,5,
  	59,0,0,55,58,1,0,0,0,56,58,3,12,6,0,57,50,1,0,0,0,57,53,1,0,0,0,57,56,
  	1,0,0,0,58,61,1,0,0,0,59,57,1,0,0,0,59,60,1,0,0,0,60,62,1,0,0,0,61,59,
  	1,0,0,0,62,72,3,2,1,0,63,64,3,16,8,0,64,65,5,59,0,0,65,71,1,0,0,0,66,
  	67,3,10,5,0,67,68,5,59,0,0,68,71,1,0,0,0,69,71,3,12,6,0,70,63,1,0,0,0,
  	70,66,1,0,0,0,70,69,1,0,0,0,71,74,1,0,0,0,72,70,1,0,0,0,72,73,1,0,0,0,
  	73,75,1,0,0,0,74,72,1,0,0,0,75,76,5,0,0,1,76,1,1,0,0,0,77,78,5,13,0,0,
  	78,79,5,17,0,0,79,80,5,36,0,0,80,81,5,37,0,0,81,82,3,22,11,0,82,3,1,0,
  	0,0,83,86,3,8,4,0,84,86,3,6,3,0,85,83,1,0,0,0,85,84,1,0,0,0,86,5,1,0,
  	0,0,87,91,3,12,6,0,88,91,3,14,7,0,89,91,3,16,8,0,90,87,1,0,0,0,90,88,
  	1,0,0,0,90,89,1,0,0,0,91,7,1,0,0,0,92,93,3,34,17,0,93,94,5,59,0,0,94,
  	116,1,0,0,0,95,96,3,10,5,0,96,97,5,59,0,0,97,116,1,0,0,0,98,116,3,18,
  	9,0,99,100,3,20,10,0,100,101,5,59,0,0,101,116,1,0,0,0,102,116,3,22,11,
  	0,103,116,3,24,12,0,104,116,3,26,13,0,105,106,3,28,14,0,106,107,5,59,
  	0,0,107,116,1,0,0,0,108,109,3,30,15,0,109,110,5,59,0,0,110,116,1,0,0,
  	0,111,112,3,32,16,0,112,113,5,59,0,0,113,116,1,0,0,0,114,116,5,59,0,0,
  	115,92,1,0,0,0,115,95,1,0,0,0,115,98,1,0,0,0,115,99,1,0,0,0,115,102,1,
  	0,0,0,115,103,1,0,0,0,115,104,1,0,0,0,115,105,1,0,0,0,115,108,1,0,0,0,
  	115,111,1,0,0,0,115,114,1,0,0,0,116,9,1,0,0,0,117,118,3,46,23,0,118,121,
  	5,26,0,0,119,120,5,31,0,0,120,122,3,34,17,0,121,119,1,0,0,0,121,122,1,
  	0,0,0,122,131,1,0,0,0,123,124,5,62,0,0,124,127,5,26,0,0,125,126,5,31,
  	0,0,126,128,3,34,17,0,127,125,1,0,0,0,127,128,1,0,0,0,128,130,1,0,0,0,
  	129,123,1,0,0,0,130,133,1,0,0,0,131,129,1,0,0,0,131,132,1,0,0,0,132,11,
  	1,0,0,0,133,131,1,0,0,0,134,135,3,46,23,0,135,136,5,26,0,0,136,148,5,
  	36,0,0,137,138,3,46,23,0,138,145,5,26,0,0,139,140,5,62,0,0,140,141,3,
  	46,23,0,141,142,5,26,0,0,142,144,1,0,0,0,143,139,1,0,0,0,144,147,1,0,
  	0,0,145,143,1,0,0,0,145,146,1,0,0,0,146,149,1,0,0,0,147,145,1,0,0,0,148,
  	137,1,0,0,0,148,149,1,0,0,0,149,150,1,0,0,0,150,151,5,37,0,0,151,152,
  	3,22,11,0,152,13,1,0,0,0,153,154,5,26,0,0,154,155,5,36,0,0,155,156,5,
  	37,0,0,156,157,3,22,11,0,157,15,1,0,0,0,158,159,5,8,0,0,159,160,5,26,
  	0,0,160,171,5,38,0,0,161,162,3,10,5,0,162,163,5,59,0,0,163,170,1,0,0,
  	0,164,170,3,12,6,0,165,170,3,14,7,0,166,167,3,16,8,0,167,168,5,59,0,0,
  	168,170,1,0,0,0,169,161,1,0,0,0,169,164,1,0,0,0,169,165,1,0,0,0,169,166,
  	1,0,0,0,170,173,1,0,0,0,171,169,1,0,0,0,171,172,1,0,0,0,172,174,1,0,0,
  	0,173,171,1,0,0,0,174,175,5,39,0,0,175,17,1,0,0,0,176,177,5,11,0,0,177,
  	179,5,36,0,0,178,180,3,34,17,0,179,178,1,0,0,0,179,180,1,0,0,0,180,181,
  	1,0,0,0,181,182,5,37,0,0,182,185,3,8,4,0,183,184,5,12,0,0,184,186,3,8,
  	4,0,185,183,1,0,0,0,185,186,1,0,0,0,186,19,1,0,0,0,187,188,3,34,17,0,
  	188,189,5,31,0,0,189,190,3,34,17,0,190,21,1,0,0,0,191,195,5,38,0,0,192,
  	194,3,4,2,0,193,192,1,0,0,0,194,197,1,0,0,0,195,196,1,0,0,0,195,193,1,
  	0,0,0,196,198,1,0,0,0,197,195,1,0,0,0,198,199,5,39,0,0,199,23,1,0,0,0,
  	200,201,5,9,0,0,201,205,5,36,0,0,202,206,3,10,5,0,203,206,3,20,10,0,204,
  	206,3,34,17,0,205,202,1,0,0,0,205,203,1,0,0,0,205,204,1,0,0,0,205,206,
  	1,0,0,0,206,207,1,0,0,0,207,209,5,59,0,0,208,210,3,34,17,0,209,208,1,
  	0,0,0,209,210,1,0,0,0,210,211,1,0,0,0,211,214,5,59,0,0,212,215,3,20,10,
  	0,213,215,3,34,17,0,214,212,1,0,0,0,214,213,1,0,0,0,214,215,1,0,0,0,215,
  	216,1,0,0,0,216,217,5,37,0,0,217,218,3,8,4,0,218,25,1,0,0,0,219,220,5,
  	10,0,0,220,221,5,36,0,0,221,222,3,34,17,0,222,223,5,37,0,0,223,224,3,
  	8,4,0,224,27,1,0,0,0,225,228,5,18,0,0,226,229,3,34,17,0,227,229,3,38,
  	19,0,228,226,1,0,0,0,228,227,1,0,0,0,228,229,1,0,0,0,229,29,1,0,0,0,230,
  	231,5,19,0,0,231,31,1,0,0,0,232,233,5,20,0,0,233,33,1,0,0,0,234,235,6,
  	17,-1,0,235,237,5,36,0,0,236,238,3,34,17,0,237,236,1,0,0,0,237,238,1,
  	0,0,0,238,239,1,0,0,0,239,255,5,37,0,0,240,255,3,40,20,0,241,255,3,38,
  	19,0,242,243,7,0,0,0,243,255,3,34,17,20,244,245,7,1,0,0,245,255,3,34,
  	17,19,246,247,7,2,0,0,247,255,3,34,17,17,248,255,3,42,21,0,249,255,3,
  	44,22,0,250,255,3,36,18,0,251,255,5,24,0,0,252,255,3,48,24,0,253,255,
  	5,26,0,0,254,234,1,0,0,0,254,240,1,0,0,0,254,241,1,0,0,0,254,242,1,0,
  	0,0,254,244,1,0,0,0,254,246,1,0,0,0,254,248,1,0,0,0,254,249,1,0,0,0,254,
  	250,1,0,0,0,254,251,1,0,0,0,254,252,1,0,0,0,254,253,1,0,0,0,255,307,1,
  	0,0,0,256,257,10,18,0,0,257,258,7,3,0,0,258,306,3,34,17,19,259,260,10,
  	16,0,0,260,261,7,2,0,0,261,306,3,34,17,17,262,263,10,15,0,0,263,264,7,
  	4,0,0,264,306,3,34,17,16,265,266,10,14,0,0,266,267,7,5,0,0,267,306,3,
  	34,17,15,268,269,10,13,0,0,269,270,7,6,0,0,270,306,3,34,17,14,271,272,
  	10,12,0,0,272,273,5,53,0,0,273,306,3,34,17,13,274,275,10,11,0,0,275,276,
  	5,54,0,0,276,306,3,34,17,12,277,278,10,10,0,0,278,279,5,55,0,0,279,306,
  	3,34,17,11,280,281,10,9,0,0,281,282,5,56,0,0,282,306,3,34,17,10,283,284,
  	10,8,0,0,284,285,5,57,0,0,285,306,3,34,17,9,286,287,10,7,0,0,287,288,
  	5,58,0,0,288,289,3,34,17,0,289,290,5,60,0,0,290,291,3,34,17,7,291,306,
  	1,0,0,0,292,293,10,25,0,0,293,294,5,40,0,0,294,295,3,34,17,0,295,296,
  	5,41,0,0,296,306,1,0,0,0,297,298,10,22,0,0,298,301,5,61,0,0,299,302,5,
  	26,0,0,300,302,3,38,19,0,301,299,1,0,0,0,301,300,1,0,0,0,302,306,1,0,
  	0,0,303,304,10,21,0,0,304,306,7,0,0,0,305,256,1,0,0,0,305,259,1,0,0,0,
  	305,262,1,0,0,0,305,265,1,0,0,0,305,268,1,0,0,0,305,271,1,0,0,0,305,274,
  	1,0,0,0,305,277,1,0,0,0,305,280,1,0,0,0,305,283,1,0,0,0,305,286,1,0,0,
  	0,305,292,1,0,0,0,305,297,1,0,0,0,305,303,1,0,0,0,306,309,1,0,0,0,307,
  	305,1,0,0,0,307,308,1,0,0,0,308,35,1,0,0,0,309,307,1,0,0,0,310,319,5,
  	6,0,0,311,318,5,4,0,0,312,314,5,27,0,0,313,315,3,34,17,0,314,313,1,0,
  	0,0,314,315,1,0,0,0,315,316,1,0,0,0,316,318,5,27,0,0,317,311,1,0,0,0,
  	317,312,1,0,0,0,318,321,1,0,0,0,319,317,1,0,0,0,319,320,1,0,0,0,320,322,
  	1,0,0,0,321,319,1,0,0,0,322,323,5,5,0,0,323,37,1,0,0,0,324,325,5,26,0,
  	0,325,334,5,36,0,0,326,331,3,34,17,0,327,328,5,62,0,0,328,330,3,34,17,
  	0,329,327,1,0,0,0,330,333,1,0,0,0,331,329,1,0,0,0,331,332,1,0,0,0,332,
  	335,1,0,0,0,333,331,1,0,0,0,334,326,1,0,0,0,334,335,1,0,0,0,335,336,1,
  	0,0,0,336,337,5,37,0,0,337,39,1,0,0,0,338,347,5,38,0,0,339,344,3,48,24,
  	0,340,341,5,62,0,0,341,343,3,48,24,0,342,340,1,0,0,0,343,346,1,0,0,0,
  	344,342,1,0,0,0,344,345,1,0,0,0,345,348,1,0,0,0,346,344,1,0,0,0,347,339,
  	1,0,0,0,347,348,1,0,0,0,348,349,1,0,0,0,349,362,5,39,0,0,350,351,5,38,
  	0,0,351,356,3,40,20,0,352,353,5,62,0,0,353,355,3,40,20,0,354,352,1,0,
  	0,0,355,358,1,0,0,0,356,354,1,0,0,0,356,357,1,0,0,0,357,359,1,0,0,0,358,
  	356,1,0,0,0,359,360,5,39,0,0,360,362,1,0,0,0,361,338,1,0,0,0,361,350,
  	1,0,0,0,362,41,1,0,0,0,363,364,5,21,0,0,364,369,3,46,23,0,365,366,5,40,
  	0,0,366,367,3,34,17,0,367,368,5,41,0,0,368,370,1,0,0,0,369,365,1,0,0,
  	0,370,371,1,0,0,0,371,369,1,0,0,0,371,372,1,0,0,0,372,377,1,0,0,0,373,
  	374,5,40,0,0,374,376,5,41,0,0,375,373,1,0,0,0,376,379,1,0,0,0,377,375,
  	1,0,0,0,377,378,1,0,0,0,378,391,1,0,0,0,379,377,1,0,0,0,380,381,5,21,
  	0,0,381,384,3,46,23,0,382,383,5,40,0,0,383,385,5,41,0,0,384,382,1,0,0,
  	0,385,386,1,0,0,0,386,384,1,0,0,0,386,387,1,0,0,0,387,388,1,0,0,0,388,
  	389,3,40,20,0,389,391,1,0,0,0,390,363,1,0,0,0,390,380,1,0,0,0,391,43,
  	1,0,0,0,392,393,5,21,0,0,393,396,3,46,23,0,394,395,5,36,0,0,395,397,5,
  	37,0,0,396,394,1,0,0,0,396,397,1,0,0,0,397,45,1,0,0,0,398,399,6,23,-1,
  	0,399,405,5,13,0,0,400,405,5,14,0,0,401,405,5,15,0,0,402,405,5,16,0,0,
  	403,405,5,26,0,0,404,398,1,0,0,0,404,400,1,0,0,0,404,401,1,0,0,0,404,
  	402,1,0,0,0,404,403,1,0,0,0,405,411,1,0,0,0,406,407,10,1,0,0,407,408,
  	5,40,0,0,408,410,5,41,0,0,409,406,1,0,0,0,410,413,1,0,0,0,411,409,1,0,
  	0,0,411,412,1,0,0,0,412,47,1,0,0,0,413,411,1,0,0,0,414,415,7,7,0,0,415,
  	49,1,0,0,0,42,57,59,70,72,85,90,115,121,127,131,145,148,169,171,179,185,
  	195,205,209,214,228,237,254,301,305,307,314,317,319,331,334,344,347,356,
  	361,371,377,386,390,396,404,411
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  mxParserStaticData = staticData.release();
}

}

MxParser::MxParser(TokenStream *input) : MxParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MxParser::MxParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MxParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *mxParserStaticData->atn, mxParserStaticData->decisionToDFA, mxParserStaticData->sharedContextCache, options);
}

MxParser::~MxParser() {
  delete _interpreter;
}

const atn::ATN& MxParser::getATN() const {
  return *mxParserStaticData->atn;
}

std::string MxParser::getGrammarFileName() const {
  return "Mx.g4";
}

const std::vector<std::string>& MxParser::getRuleNames() const {
  return mxParserStaticData->ruleNames;
}

const dfa::Vocabulary& MxParser::getVocabulary() const {
  return mxParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MxParser::getSerializedATN() const {
  return mxParserStaticData->serializedATN;
}


//----------------- ProgContext ------------------------------------------------------------------

MxParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MxParser::MainFuncContext* MxParser::ProgContext::mainFunc() {
  return getRuleContext<MxParser::MainFuncContext>(0);
}

tree::TerminalNode* MxParser::ProgContext::EOF() {
  return getToken(MxParser::EOF, 0);
}

std::vector<MxParser::ClassDefContext *> MxParser::ProgContext::classDef() {
  return getRuleContexts<MxParser::ClassDefContext>();
}

MxParser::ClassDefContext* MxParser::ProgContext::classDef(size_t i) {
  return getRuleContext<MxParser::ClassDefContext>(i);
}

std::vector<tree::TerminalNode *> MxParser::ProgContext::SEMI_COLON() {
  return getTokens(MxParser::SEMI_COLON);
}

tree::TerminalNode* MxParser::ProgContext::SEMI_COLON(size_t i) {
  return getToken(MxParser::SEMI_COLON, i);
}

std::vector<MxParser::VarDefContext *> MxParser::ProgContext::varDef() {
  return getRuleContexts<MxParser::VarDefContext>();
}

MxParser::VarDefContext* MxParser::ProgContext::varDef(size_t i) {
  return getRuleContext<MxParser::VarDefContext>(i);
}

std::vector<MxParser::FuncDefContext *> MxParser::ProgContext::funcDef() {
  return getRuleContexts<MxParser::FuncDefContext>();
}

MxParser::FuncDefContext* MxParser::ProgContext::funcDef(size_t i) {
  return getRuleContext<MxParser::FuncDefContext>(i);
}


size_t MxParser::ProgContext::getRuleIndex() const {
  return MxParser::RuleProg;
}

void MxParser::ProgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProg(this);
}

void MxParser::ProgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProg(this);
}


std::any MxParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ProgContext* MxParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, MxParser::RuleProg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(59);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(57);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
        case 1: {
          setState(50);
          classDef();
          setState(51);
          match(MxParser::SEMI_COLON);
          break;
        }

        case 2: {
          setState(53);
          varDef();
          setState(54);
          match(MxParser::SEMI_COLON);
          break;
        }

        case 3: {
          setState(56);
          funcDef();
          break;
        }

        default:
          break;
        } 
      }
      setState(61);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
    setState(62);
    mainFunc();
    setState(72);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67232000) != 0)) {
      setState(70);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(63);
        classDef();
        setState(64);
        match(MxParser::SEMI_COLON);
        break;
      }

      case 2: {
        setState(66);
        varDef();
        setState(67);
        match(MxParser::SEMI_COLON);
        break;
      }

      case 3: {
        setState(69);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(74);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(75);
    match(MxParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MainFuncContext ------------------------------------------------------------------

MxParser::MainFuncContext::MainFuncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::MainFuncContext::INT() {
  return getToken(MxParser::INT, 0);
}

tree::TerminalNode* MxParser::MainFuncContext::MAIN() {
  return getToken(MxParser::MAIN, 0);
}

tree::TerminalNode* MxParser::MainFuncContext::LEFT_PARENTHESIS() {
  return getToken(MxParser::LEFT_PARENTHESIS, 0);
}

tree::TerminalNode* MxParser::MainFuncContext::RIGHT_PARENTHESIS() {
  return getToken(MxParser::RIGHT_PARENTHESIS, 0);
}

MxParser::BlockContext* MxParser::MainFuncContext::block() {
  return getRuleContext<MxParser::BlockContext>(0);
}


size_t MxParser::MainFuncContext::getRuleIndex() const {
  return MxParser::RuleMainFunc;
}

void MxParser::MainFuncContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMainFunc(this);
}

void MxParser::MainFuncContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMainFunc(this);
}


std::any MxParser::MainFuncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitMainFunc(this);
  else
    return visitor->visitChildren(this);
}

MxParser::MainFuncContext* MxParser::mainFunc() {
  MainFuncContext *_localctx = _tracker.createInstance<MainFuncContext>(_ctx, getState());
  enterRule(_localctx, 2, MxParser::RuleMainFunc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    match(MxParser::INT);
    setState(78);
    match(MxParser::MAIN);
    setState(79);
    match(MxParser::LEFT_PARENTHESIS);
    setState(80);
    match(MxParser::RIGHT_PARENTHESIS);
    setState(81);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatContext ------------------------------------------------------------------

MxParser::StatContext::StatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MxParser::RegularStatContext* MxParser::StatContext::regularStat() {
  return getRuleContext<MxParser::RegularStatContext>(0);
}

MxParser::SpecialStatContext* MxParser::StatContext::specialStat() {
  return getRuleContext<MxParser::SpecialStatContext>(0);
}


size_t MxParser::StatContext::getRuleIndex() const {
  return MxParser::RuleStat;
}

void MxParser::StatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStat(this);
}

void MxParser::StatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStat(this);
}


std::any MxParser::StatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitStat(this);
  else
    return visitor->visitChildren(this);
}

MxParser::StatContext* MxParser::stat() {
  StatContext *_localctx = _tracker.createInstance<StatContext>(_ctx, getState());
  enterRule(_localctx, 4, MxParser::RuleStat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(85);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(83);
      regularStat();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(84);
      specialStat();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SpecialStatContext ------------------------------------------------------------------

MxParser::SpecialStatContext::SpecialStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MxParser::FuncDefContext* MxParser::SpecialStatContext::funcDef() {
  return getRuleContext<MxParser::FuncDefContext>(0);
}

MxParser::ClassFuncDefContext* MxParser::SpecialStatContext::classFuncDef() {
  return getRuleContext<MxParser::ClassFuncDefContext>(0);
}

MxParser::ClassDefContext* MxParser::SpecialStatContext::classDef() {
  return getRuleContext<MxParser::ClassDefContext>(0);
}


size_t MxParser::SpecialStatContext::getRuleIndex() const {
  return MxParser::RuleSpecialStat;
}

void MxParser::SpecialStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSpecialStat(this);
}

void MxParser::SpecialStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSpecialStat(this);
}


std::any MxParser::SpecialStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitSpecialStat(this);
  else
    return visitor->visitChildren(this);
}

MxParser::SpecialStatContext* MxParser::specialStat() {
  SpecialStatContext *_localctx = _tracker.createInstance<SpecialStatContext>(_ctx, getState());
  enterRule(_localctx, 6, MxParser::RuleSpecialStat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(90);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(87);
      funcDef();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(88);
      classFuncDef();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(89);
      classDef();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RegularStatContext ------------------------------------------------------------------

MxParser::RegularStatContext::RegularStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MxParser::RegularStatContext::getRuleIndex() const {
  return MxParser::RuleRegularStat;
}

void MxParser::RegularStatContext::copyFrom(RegularStatContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IfstatContext ------------------------------------------------------------------

MxParser::IfStatContext* MxParser::IfstatContext::ifStat() {
  return getRuleContext<MxParser::IfStatContext>(0);
}

MxParser::IfstatContext::IfstatContext(RegularStatContext *ctx) { copyFrom(ctx); }

void MxParser::IfstatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfstat(this);
}
void MxParser::IfstatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfstat(this);
}

std::any MxParser::IfstatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitIfstat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprstatContext ------------------------------------------------------------------

MxParser::ExprContext* MxParser::ExprstatContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::ExprstatContext::SEMI_COLON() {
  return getToken(MxParser::SEMI_COLON, 0);
}

MxParser::ExprstatContext::ExprstatContext(RegularStatContext *ctx) { copyFrom(ctx); }

void MxParser::ExprstatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprstat(this);
}
void MxParser::ExprstatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprstat(this);
}

std::any MxParser::ExprstatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitExprstat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnstatContext ------------------------------------------------------------------

MxParser::ReturnStatContext* MxParser::ReturnstatContext::returnStat() {
  return getRuleContext<MxParser::ReturnStatContext>(0);
}

tree::TerminalNode* MxParser::ReturnstatContext::SEMI_COLON() {
  return getToken(MxParser::SEMI_COLON, 0);
}

MxParser::ReturnstatContext::ReturnstatContext(RegularStatContext *ctx) { copyFrom(ctx); }

void MxParser::ReturnstatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnstat(this);
}
void MxParser::ReturnstatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnstat(this);
}

std::any MxParser::ReturnstatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitReturnstat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NullstatContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::NullstatContext::SEMI_COLON() {
  return getToken(MxParser::SEMI_COLON, 0);
}

MxParser::NullstatContext::NullstatContext(RegularStatContext *ctx) { copyFrom(ctx); }

void MxParser::NullstatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNullstat(this);
}
void MxParser::NullstatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNullstat(this);
}

std::any MxParser::NullstatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitNullstat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VardefstatContext ------------------------------------------------------------------

MxParser::VarDefContext* MxParser::VardefstatContext::varDef() {
  return getRuleContext<MxParser::VarDefContext>(0);
}

tree::TerminalNode* MxParser::VardefstatContext::SEMI_COLON() {
  return getToken(MxParser::SEMI_COLON, 0);
}

MxParser::VardefstatContext::VardefstatContext(RegularStatContext *ctx) { copyFrom(ctx); }

void MxParser::VardefstatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVardefstat(this);
}
void MxParser::VardefstatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVardefstat(this);
}

std::any MxParser::VardefstatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitVardefstat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinuestatContext ------------------------------------------------------------------

MxParser::ContinueContext* MxParser::ContinuestatContext::continue_() {
  return getRuleContext<MxParser::ContinueContext>(0);
}

tree::TerminalNode* MxParser::ContinuestatContext::SEMI_COLON() {
  return getToken(MxParser::SEMI_COLON, 0);
}

MxParser::ContinuestatContext::ContinuestatContext(RegularStatContext *ctx) { copyFrom(ctx); }

void MxParser::ContinuestatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinuestat(this);
}
void MxParser::ContinuestatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinuestat(this);
}

std::any MxParser::ContinuestatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitContinuestat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignstatContext ------------------------------------------------------------------

MxParser::AssignStatContext* MxParser::AssignstatContext::assignStat() {
  return getRuleContext<MxParser::AssignStatContext>(0);
}

tree::TerminalNode* MxParser::AssignstatContext::SEMI_COLON() {
  return getToken(MxParser::SEMI_COLON, 0);
}

MxParser::AssignstatContext::AssignstatContext(RegularStatContext *ctx) { copyFrom(ctx); }

void MxParser::AssignstatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignstat(this);
}
void MxParser::AssignstatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignstat(this);
}

std::any MxParser::AssignstatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitAssignstat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhilestatContext ------------------------------------------------------------------

MxParser::WhileStatContext* MxParser::WhilestatContext::whileStat() {
  return getRuleContext<MxParser::WhileStatContext>(0);
}

MxParser::WhilestatContext::WhilestatContext(RegularStatContext *ctx) { copyFrom(ctx); }

void MxParser::WhilestatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhilestat(this);
}
void MxParser::WhilestatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhilestat(this);
}

std::any MxParser::WhilestatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitWhilestat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakstatContext ------------------------------------------------------------------

MxParser::BreakContext* MxParser::BreakstatContext::break_() {
  return getRuleContext<MxParser::BreakContext>(0);
}

tree::TerminalNode* MxParser::BreakstatContext::SEMI_COLON() {
  return getToken(MxParser::SEMI_COLON, 0);
}

MxParser::BreakstatContext::BreakstatContext(RegularStatContext *ctx) { copyFrom(ctx); }

void MxParser::BreakstatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakstat(this);
}
void MxParser::BreakstatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakstat(this);
}

std::any MxParser::BreakstatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitBreakstat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockstatContext ------------------------------------------------------------------

MxParser::BlockContext* MxParser::BlockstatContext::block() {
  return getRuleContext<MxParser::BlockContext>(0);
}

MxParser::BlockstatContext::BlockstatContext(RegularStatContext *ctx) { copyFrom(ctx); }

void MxParser::BlockstatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockstat(this);
}
void MxParser::BlockstatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockstat(this);
}

std::any MxParser::BlockstatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitBlockstat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ForstatContext ------------------------------------------------------------------

MxParser::ForStatContext* MxParser::ForstatContext::forStat() {
  return getRuleContext<MxParser::ForStatContext>(0);
}

MxParser::ForstatContext::ForstatContext(RegularStatContext *ctx) { copyFrom(ctx); }

void MxParser::ForstatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForstat(this);
}
void MxParser::ForstatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForstat(this);
}

std::any MxParser::ForstatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitForstat(this);
  else
    return visitor->visitChildren(this);
}
MxParser::RegularStatContext* MxParser::regularStat() {
  RegularStatContext *_localctx = _tracker.createInstance<RegularStatContext>(_ctx, getState());
  enterRule(_localctx, 8, MxParser::RuleRegularStat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(115);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MxParser::ExprstatContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(92);
      expr(0);
      setState(93);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MxParser::VardefstatContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(95);
      varDef();
      setState(96);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MxParser::IfstatContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(98);
      ifStat();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<MxParser::AssignstatContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(99);
      assignStat();
      setState(100);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<MxParser::BlockstatContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(102);
      block();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<MxParser::ForstatContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(103);
      forStat();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<MxParser::WhilestatContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(104);
      whileStat();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<MxParser::ReturnstatContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(105);
      returnStat();
      setState(106);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<MxParser::ContinuestatContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(108);
      continue_();
      setState(109);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<MxParser::BreakstatContext>(_localctx);
      enterOuterAlt(_localctx, 10);
      setState(111);
      break_();
      setState(112);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<MxParser::NullstatContext>(_localctx);
      enterOuterAlt(_localctx, 11);
      setState(114);
      match(MxParser::SEMI_COLON);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

MxParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MxParser::TypeContext* MxParser::VarDefContext::type() {
  return getRuleContext<MxParser::TypeContext>(0);
}

std::vector<tree::TerminalNode *> MxParser::VarDefContext::ID() {
  return getTokens(MxParser::ID);
}

tree::TerminalNode* MxParser::VarDefContext::ID(size_t i) {
  return getToken(MxParser::ID, i);
}

std::vector<tree::TerminalNode *> MxParser::VarDefContext::EQUAL() {
  return getTokens(MxParser::EQUAL);
}

tree::TerminalNode* MxParser::VarDefContext::EQUAL(size_t i) {
  return getToken(MxParser::EQUAL, i);
}

std::vector<MxParser::ExprContext *> MxParser::VarDefContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::VarDefContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MxParser::VarDefContext::COMMA() {
  return getTokens(MxParser::COMMA);
}

tree::TerminalNode* MxParser::VarDefContext::COMMA(size_t i) {
  return getToken(MxParser::COMMA, i);
}


size_t MxParser::VarDefContext::getRuleIndex() const {
  return MxParser::RuleVarDef;
}

void MxParser::VarDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDef(this);
}

void MxParser::VarDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDef(this);
}


std::any MxParser::VarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitVarDef(this);
  else
    return visitor->visitChildren(this);
}

MxParser::VarDefContext* MxParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 10, MxParser::RuleVarDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    type(0);
    setState(118);
    match(MxParser::ID);
    setState(121);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MxParser::EQUAL) {
      setState(119);
      match(MxParser::EQUAL);
      setState(120);
      expr(0);
    }
    setState(131);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MxParser::COMMA) {
      setState(123);
      match(MxParser::COMMA);
      setState(124);
      match(MxParser::ID);
      setState(127);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MxParser::EQUAL) {
        setState(125);
        match(MxParser::EQUAL);
        setState(126);
        expr(0);
      }
      setState(133);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

MxParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MxParser::TypeContext *> MxParser::FuncDefContext::type() {
  return getRuleContexts<MxParser::TypeContext>();
}

MxParser::TypeContext* MxParser::FuncDefContext::type(size_t i) {
  return getRuleContext<MxParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> MxParser::FuncDefContext::ID() {
  return getTokens(MxParser::ID);
}

tree::TerminalNode* MxParser::FuncDefContext::ID(size_t i) {
  return getToken(MxParser::ID, i);
}

tree::TerminalNode* MxParser::FuncDefContext::LEFT_PARENTHESIS() {
  return getToken(MxParser::LEFT_PARENTHESIS, 0);
}

tree::TerminalNode* MxParser::FuncDefContext::RIGHT_PARENTHESIS() {
  return getToken(MxParser::RIGHT_PARENTHESIS, 0);
}

MxParser::BlockContext* MxParser::FuncDefContext::block() {
  return getRuleContext<MxParser::BlockContext>(0);
}

std::vector<tree::TerminalNode *> MxParser::FuncDefContext::COMMA() {
  return getTokens(MxParser::COMMA);
}

tree::TerminalNode* MxParser::FuncDefContext::COMMA(size_t i) {
  return getToken(MxParser::COMMA, i);
}


size_t MxParser::FuncDefContext::getRuleIndex() const {
  return MxParser::RuleFuncDef;
}

void MxParser::FuncDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDef(this);
}

void MxParser::FuncDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDef(this);
}


std::any MxParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

MxParser::FuncDefContext* MxParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 12, MxParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(134);
    type(0);
    setState(135);
    match(MxParser::ID);
    setState(136);
    match(MxParser::LEFT_PARENTHESIS);
    setState(148);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67231744) != 0)) {
      setState(137);
      type(0);
      setState(138);
      match(MxParser::ID);
      setState(145);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MxParser::COMMA) {
        setState(139);
        match(MxParser::COMMA);
        setState(140);
        type(0);
        setState(141);
        match(MxParser::ID);
        setState(147);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(150);
    match(MxParser::RIGHT_PARENTHESIS);
    setState(151);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassFuncDefContext ------------------------------------------------------------------

MxParser::ClassFuncDefContext::ClassFuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::ClassFuncDefContext::ID() {
  return getToken(MxParser::ID, 0);
}

tree::TerminalNode* MxParser::ClassFuncDefContext::LEFT_PARENTHESIS() {
  return getToken(MxParser::LEFT_PARENTHESIS, 0);
}

tree::TerminalNode* MxParser::ClassFuncDefContext::RIGHT_PARENTHESIS() {
  return getToken(MxParser::RIGHT_PARENTHESIS, 0);
}

MxParser::BlockContext* MxParser::ClassFuncDefContext::block() {
  return getRuleContext<MxParser::BlockContext>(0);
}


size_t MxParser::ClassFuncDefContext::getRuleIndex() const {
  return MxParser::RuleClassFuncDef;
}

void MxParser::ClassFuncDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassFuncDef(this);
}

void MxParser::ClassFuncDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassFuncDef(this);
}


std::any MxParser::ClassFuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitClassFuncDef(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ClassFuncDefContext* MxParser::classFuncDef() {
  ClassFuncDefContext *_localctx = _tracker.createInstance<ClassFuncDefContext>(_ctx, getState());
  enterRule(_localctx, 14, MxParser::RuleClassFuncDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    match(MxParser::ID);
    setState(154);
    match(MxParser::LEFT_PARENTHESIS);
    setState(155);
    match(MxParser::RIGHT_PARENTHESIS);
    setState(156);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClassDefContext ------------------------------------------------------------------

MxParser::ClassDefContext::ClassDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::ClassDefContext::CLASS() {
  return getToken(MxParser::CLASS, 0);
}

tree::TerminalNode* MxParser::ClassDefContext::ID() {
  return getToken(MxParser::ID, 0);
}

tree::TerminalNode* MxParser::ClassDefContext::LEFT_CURLY_BRACKET() {
  return getToken(MxParser::LEFT_CURLY_BRACKET, 0);
}

tree::TerminalNode* MxParser::ClassDefContext::RIGHT_CURLY_BRACKET() {
  return getToken(MxParser::RIGHT_CURLY_BRACKET, 0);
}

std::vector<MxParser::VarDefContext *> MxParser::ClassDefContext::varDef() {
  return getRuleContexts<MxParser::VarDefContext>();
}

MxParser::VarDefContext* MxParser::ClassDefContext::varDef(size_t i) {
  return getRuleContext<MxParser::VarDefContext>(i);
}

std::vector<tree::TerminalNode *> MxParser::ClassDefContext::SEMI_COLON() {
  return getTokens(MxParser::SEMI_COLON);
}

tree::TerminalNode* MxParser::ClassDefContext::SEMI_COLON(size_t i) {
  return getToken(MxParser::SEMI_COLON, i);
}

std::vector<MxParser::FuncDefContext *> MxParser::ClassDefContext::funcDef() {
  return getRuleContexts<MxParser::FuncDefContext>();
}

MxParser::FuncDefContext* MxParser::ClassDefContext::funcDef(size_t i) {
  return getRuleContext<MxParser::FuncDefContext>(i);
}

std::vector<MxParser::ClassFuncDefContext *> MxParser::ClassDefContext::classFuncDef() {
  return getRuleContexts<MxParser::ClassFuncDefContext>();
}

MxParser::ClassFuncDefContext* MxParser::ClassDefContext::classFuncDef(size_t i) {
  return getRuleContext<MxParser::ClassFuncDefContext>(i);
}

std::vector<MxParser::ClassDefContext *> MxParser::ClassDefContext::classDef() {
  return getRuleContexts<MxParser::ClassDefContext>();
}

MxParser::ClassDefContext* MxParser::ClassDefContext::classDef(size_t i) {
  return getRuleContext<MxParser::ClassDefContext>(i);
}


size_t MxParser::ClassDefContext::getRuleIndex() const {
  return MxParser::RuleClassDef;
}

void MxParser::ClassDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassDef(this);
}

void MxParser::ClassDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassDef(this);
}


std::any MxParser::ClassDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitClassDef(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ClassDefContext* MxParser::classDef() {
  ClassDefContext *_localctx = _tracker.createInstance<ClassDefContext>(_ctx, getState());
  enterRule(_localctx, 16, MxParser::RuleClassDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(158);
    match(MxParser::CLASS);
    setState(159);
    match(MxParser::ID);
    setState(160);
    match(MxParser::LEFT_CURLY_BRACKET);
    setState(171);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67232000) != 0)) {
      setState(169);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
      case 1: {
        setState(161);
        varDef();
        setState(162);
        match(MxParser::SEMI_COLON);
        break;
      }

      case 2: {
        setState(164);
        funcDef();
        break;
      }

      case 3: {
        setState(165);
        classFuncDef();
        break;
      }

      case 4: {
        setState(166);
        classDef();
        setState(167);
        match(MxParser::SEMI_COLON);
        break;
      }

      default:
        break;
      }
      setState(173);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(174);
    match(MxParser::RIGHT_CURLY_BRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatContext ------------------------------------------------------------------

MxParser::IfStatContext::IfStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::IfStatContext::IF() {
  return getToken(MxParser::IF, 0);
}

tree::TerminalNode* MxParser::IfStatContext::LEFT_PARENTHESIS() {
  return getToken(MxParser::LEFT_PARENTHESIS, 0);
}

tree::TerminalNode* MxParser::IfStatContext::RIGHT_PARENTHESIS() {
  return getToken(MxParser::RIGHT_PARENTHESIS, 0);
}

std::vector<MxParser::RegularStatContext *> MxParser::IfStatContext::regularStat() {
  return getRuleContexts<MxParser::RegularStatContext>();
}

MxParser::RegularStatContext* MxParser::IfStatContext::regularStat(size_t i) {
  return getRuleContext<MxParser::RegularStatContext>(i);
}

tree::TerminalNode* MxParser::IfStatContext::ELSE() {
  return getToken(MxParser::ELSE, 0);
}

MxParser::ExprContext* MxParser::IfStatContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}


size_t MxParser::IfStatContext::getRuleIndex() const {
  return MxParser::RuleIfStat;
}

void MxParser::IfStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStat(this);
}

void MxParser::IfStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStat(this);
}


std::any MxParser::IfStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitIfStat(this);
  else
    return visitor->visitChildren(this);
}

MxParser::IfStatContext* MxParser::ifStat() {
  IfStatContext *_localctx = _tracker.createInstance<IfStatContext>(_ctx, getState());
  enterRule(_localctx, 18, MxParser::RuleIfStat);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    match(MxParser::IF);
    setState(177);
    match(MxParser::LEFT_PARENTHESIS);
    setState(179);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 6) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 6)) & 432345775961767939) != 0)) {
      setState(178);
      antlrcpp::downCast<IfStatContext *>(_localctx)->ifExpr = expr(0);
    }
    setState(181);
    match(MxParser::RIGHT_PARENTHESIS);
    setState(182);
    regularStat();
    setState(185);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(183);
      match(MxParser::ELSE);
      setState(184);
      regularStat();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignStatContext ------------------------------------------------------------------

MxParser::AssignStatContext::AssignStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MxParser::ExprContext *> MxParser::AssignStatContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::AssignStatContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

tree::TerminalNode* MxParser::AssignStatContext::EQUAL() {
  return getToken(MxParser::EQUAL, 0);
}


size_t MxParser::AssignStatContext::getRuleIndex() const {
  return MxParser::RuleAssignStat;
}

void MxParser::AssignStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignStat(this);
}

void MxParser::AssignStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignStat(this);
}


std::any MxParser::AssignStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitAssignStat(this);
  else
    return visitor->visitChildren(this);
}

MxParser::AssignStatContext* MxParser::assignStat() {
  AssignStatContext *_localctx = _tracker.createInstance<AssignStatContext>(_ctx, getState());
  enterRule(_localctx, 20, MxParser::RuleAssignStat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    expr(0);
    setState(188);
    match(MxParser::EQUAL);
    setState(189);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

MxParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::BlockContext::LEFT_CURLY_BRACKET() {
  return getToken(MxParser::LEFT_CURLY_BRACKET, 0);
}

tree::TerminalNode* MxParser::BlockContext::RIGHT_CURLY_BRACKET() {
  return getToken(MxParser::RIGHT_CURLY_BRACKET, 0);
}

std::vector<MxParser::StatContext *> MxParser::BlockContext::stat() {
  return getRuleContexts<MxParser::StatContext>();
}

MxParser::StatContext* MxParser::BlockContext::stat(size_t i) {
  return getRuleContext<MxParser::StatContext>(i);
}


size_t MxParser::BlockContext::getRuleIndex() const {
  return MxParser::RuleBlock;
}

void MxParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void MxParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any MxParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

MxParser::BlockContext* MxParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 22, MxParser::RuleBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(191);
    match(MxParser::LEFT_CURLY_BRACKET);
    setState(195);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(192);
        stat(); 
      }
      setState(197);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
    setState(198);
    match(MxParser::RIGHT_CURLY_BRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStatContext ------------------------------------------------------------------

MxParser::ForStatContext::ForStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::ForStatContext::FOR() {
  return getToken(MxParser::FOR, 0);
}

tree::TerminalNode* MxParser::ForStatContext::LEFT_PARENTHESIS() {
  return getToken(MxParser::LEFT_PARENTHESIS, 0);
}

std::vector<tree::TerminalNode *> MxParser::ForStatContext::SEMI_COLON() {
  return getTokens(MxParser::SEMI_COLON);
}

tree::TerminalNode* MxParser::ForStatContext::SEMI_COLON(size_t i) {
  return getToken(MxParser::SEMI_COLON, i);
}

tree::TerminalNode* MxParser::ForStatContext::RIGHT_PARENTHESIS() {
  return getToken(MxParser::RIGHT_PARENTHESIS, 0);
}

MxParser::RegularStatContext* MxParser::ForStatContext::regularStat() {
  return getRuleContext<MxParser::RegularStatContext>(0);
}

MxParser::VarDefContext* MxParser::ForStatContext::varDef() {
  return getRuleContext<MxParser::VarDefContext>(0);
}

std::vector<MxParser::AssignStatContext *> MxParser::ForStatContext::assignStat() {
  return getRuleContexts<MxParser::AssignStatContext>();
}

MxParser::AssignStatContext* MxParser::ForStatContext::assignStat(size_t i) {
  return getRuleContext<MxParser::AssignStatContext>(i);
}

std::vector<MxParser::ExprContext *> MxParser::ForStatContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::ForStatContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}


size_t MxParser::ForStatContext::getRuleIndex() const {
  return MxParser::RuleForStat;
}

void MxParser::ForStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStat(this);
}

void MxParser::ForStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStat(this);
}


std::any MxParser::ForStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitForStat(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ForStatContext* MxParser::forStat() {
  ForStatContext *_localctx = _tracker.createInstance<ForStatContext>(_ctx, getState());
  enterRule(_localctx, 24, MxParser::RuleForStat);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(200);
    match(MxParser::FOR);
    setState(201);
    match(MxParser::LEFT_PARENTHESIS);
    setState(205);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      setState(202);
      antlrcpp::downCast<ForStatContext *>(_localctx)->initialVarDef = varDef();
      break;
    }

    case 2: {
      setState(203);
      antlrcpp::downCast<ForStatContext *>(_localctx)->initialAssignStat = assignStat();
      break;
    }

    case 3: {
      setState(204);
      antlrcpp::downCast<ForStatContext *>(_localctx)->initialExpr = expr(0);
      break;
    }

    default:
      break;
    }
    setState(207);
    match(MxParser::SEMI_COLON);
    setState(209);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 6) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 6)) & 432345775961767939) != 0)) {
      setState(208);
      antlrcpp::downCast<ForStatContext *>(_localctx)->forCondExpr = expr(0);
    }
    setState(211);
    match(MxParser::SEMI_COLON);
    setState(214);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(212);
      antlrcpp::downCast<ForStatContext *>(_localctx)->updateAssignStat = assignStat();
      break;
    }

    case 2: {
      setState(213);
      antlrcpp::downCast<ForStatContext *>(_localctx)->updateExpr = expr(0);
      break;
    }

    default:
      break;
    }
    setState(216);
    match(MxParser::RIGHT_PARENTHESIS);
    setState(217);
    regularStat();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatContext ------------------------------------------------------------------

MxParser::WhileStatContext::WhileStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::WhileStatContext::WHILE() {
  return getToken(MxParser::WHILE, 0);
}

tree::TerminalNode* MxParser::WhileStatContext::LEFT_PARENTHESIS() {
  return getToken(MxParser::LEFT_PARENTHESIS, 0);
}

tree::TerminalNode* MxParser::WhileStatContext::RIGHT_PARENTHESIS() {
  return getToken(MxParser::RIGHT_PARENTHESIS, 0);
}

MxParser::RegularStatContext* MxParser::WhileStatContext::regularStat() {
  return getRuleContext<MxParser::RegularStatContext>(0);
}

MxParser::ExprContext* MxParser::WhileStatContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}


size_t MxParser::WhileStatContext::getRuleIndex() const {
  return MxParser::RuleWhileStat;
}

void MxParser::WhileStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhileStat(this);
}

void MxParser::WhileStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhileStat(this);
}


std::any MxParser::WhileStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitWhileStat(this);
  else
    return visitor->visitChildren(this);
}

MxParser::WhileStatContext* MxParser::whileStat() {
  WhileStatContext *_localctx = _tracker.createInstance<WhileStatContext>(_ctx, getState());
  enterRule(_localctx, 26, MxParser::RuleWhileStat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    match(MxParser::WHILE);
    setState(220);
    match(MxParser::LEFT_PARENTHESIS);
    setState(221);
    antlrcpp::downCast<WhileStatContext *>(_localctx)->whileCondExpr = expr(0);
    setState(222);
    match(MxParser::RIGHT_PARENTHESIS);
    setState(223);
    regularStat();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatContext ------------------------------------------------------------------

MxParser::ReturnStatContext::ReturnStatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::ReturnStatContext::RETURN() {
  return getToken(MxParser::RETURN, 0);
}

MxParser::ExprContext* MxParser::ReturnStatContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

MxParser::FuncCallContext* MxParser::ReturnStatContext::funcCall() {
  return getRuleContext<MxParser::FuncCallContext>(0);
}


size_t MxParser::ReturnStatContext::getRuleIndex() const {
  return MxParser::RuleReturnStat;
}

void MxParser::ReturnStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStat(this);
}

void MxParser::ReturnStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStat(this);
}


std::any MxParser::ReturnStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitReturnStat(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ReturnStatContext* MxParser::returnStat() {
  ReturnStatContext *_localctx = _tracker.createInstance<ReturnStatContext>(_ctx, getState());
  enterRule(_localctx, 28, MxParser::RuleReturnStat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(225);
    match(MxParser::RETURN);
    setState(228);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      setState(226);
      expr(0);
      break;
    }

    case 2: {
      setState(227);
      funcCall();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueContext ------------------------------------------------------------------

MxParser::ContinueContext::ContinueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::ContinueContext::CONTINUE() {
  return getToken(MxParser::CONTINUE, 0);
}


size_t MxParser::ContinueContext::getRuleIndex() const {
  return MxParser::RuleContinue;
}

void MxParser::ContinueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinue(this);
}

void MxParser::ContinueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinue(this);
}


std::any MxParser::ContinueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitContinue(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ContinueContext* MxParser::continue_() {
  ContinueContext *_localctx = _tracker.createInstance<ContinueContext>(_ctx, getState());
  enterRule(_localctx, 30, MxParser::RuleContinue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(230);
    match(MxParser::CONTINUE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakContext ------------------------------------------------------------------

MxParser::BreakContext::BreakContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::BreakContext::BREAK() {
  return getToken(MxParser::BREAK, 0);
}


size_t MxParser::BreakContext::getRuleIndex() const {
  return MxParser::RuleBreak;
}

void MxParser::BreakContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreak(this);
}

void MxParser::BreakContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreak(this);
}


std::any MxParser::BreakContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitBreak(this);
  else
    return visitor->visitChildren(this);
}

MxParser::BreakContext* MxParser::break_() {
  BreakContext *_localctx = _tracker.createInstance<BreakContext>(_ctx, getState());
  enterRule(_localctx, 32, MxParser::RuleBreak);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(232);
    match(MxParser::BREAK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

MxParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MxParser::ExprContext::getRuleIndex() const {
  return MxParser::RuleExpr;
}

void MxParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- InitObjectExprContext ------------------------------------------------------------------

MxParser::InitObjectContext* MxParser::InitObjectExprContext::initObject() {
  return getRuleContext<MxParser::InitObjectContext>(0);
}

MxParser::InitObjectExprContext::InitObjectExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::InitObjectExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitObjectExpr(this);
}
void MxParser::InitObjectExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitObjectExpr(this);
}

std::any MxParser::InitObjectExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitInitObjectExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ThisExprContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::ThisExprContext::THIS() {
  return getToken(MxParser::THIS, 0);
}

MxParser::ThisExprContext::ThisExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::ThisExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterThisExpr(this);
}
void MxParser::ThisExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitThisExpr(this);
}

std::any MxParser::ThisExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitThisExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DotExprContext ------------------------------------------------------------------

MxParser::ExprContext* MxParser::DotExprContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::DotExprContext::DOT() {
  return getToken(MxParser::DOT, 0);
}

tree::TerminalNode* MxParser::DotExprContext::ID() {
  return getToken(MxParser::ID, 0);
}

MxParser::FuncCallContext* MxParser::DotExprContext::funcCall() {
  return getRuleContext<MxParser::FuncCallContext>(0);
}

MxParser::DotExprContext::DotExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::DotExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDotExpr(this);
}
void MxParser::DotExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDotExpr(this);
}

std::any MxParser::DotExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitDotExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayExprContext ------------------------------------------------------------------

MxParser::ArrayConstContext* MxParser::ArrayExprContext::arrayConst() {
  return getRuleContext<MxParser::ArrayConstContext>(0);
}

MxParser::ArrayExprContext::ArrayExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::ArrayExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayExpr(this);
}
void MxParser::ArrayExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayExpr(this);
}

std::any MxParser::ArrayExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitArrayExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryExprContext ------------------------------------------------------------------

std::vector<MxParser::ExprContext *> MxParser::BinaryExprContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::BinaryExprContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

tree::TerminalNode* MxParser::BinaryExprContext::MUL() {
  return getToken(MxParser::MUL, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::DIV() {
  return getToken(MxParser::DIV, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::MOD() {
  return getToken(MxParser::MOD, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::ADD() {
  return getToken(MxParser::ADD, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::SUB() {
  return getToken(MxParser::SUB, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::SRL() {
  return getToken(MxParser::SRL, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::SLL() {
  return getToken(MxParser::SLL, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::BT() {
  return getToken(MxParser::BT, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::LT() {
  return getToken(MxParser::LT, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::BEQ() {
  return getToken(MxParser::BEQ, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::LEQ() {
  return getToken(MxParser::LEQ, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::ET() {
  return getToken(MxParser::ET, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::NET() {
  return getToken(MxParser::NET, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::AND() {
  return getToken(MxParser::AND, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::XOR() {
  return getToken(MxParser::XOR, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::OR() {
  return getToken(MxParser::OR, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::AND_AND() {
  return getToken(MxParser::AND_AND, 0);
}

tree::TerminalNode* MxParser::BinaryExprContext::OR_OR() {
  return getToken(MxParser::OR_OR, 0);
}

MxParser::BinaryExprContext::BinaryExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::BinaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBinaryExpr(this);
}
void MxParser::BinaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBinaryExpr(this);
}

std::any MxParser::BinaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitBinaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncCallExprContext ------------------------------------------------------------------

MxParser::FuncCallContext* MxParser::FuncCallExprContext::funcCall() {
  return getRuleContext<MxParser::FuncCallContext>(0);
}

MxParser::FuncCallExprContext::FuncCallExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::FuncCallExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCallExpr(this);
}
void MxParser::FuncCallExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCallExpr(this);
}

std::any MxParser::FuncCallExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitFuncCallExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::ParenExprContext::LEFT_PARENTHESIS() {
  return getToken(MxParser::LEFT_PARENTHESIS, 0);
}

tree::TerminalNode* MxParser::ParenExprContext::RIGHT_PARENTHESIS() {
  return getToken(MxParser::RIGHT_PARENTHESIS, 0);
}

MxParser::ExprContext* MxParser::ParenExprContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

MxParser::ParenExprContext::ParenExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::ParenExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenExpr(this);
}
void MxParser::ParenExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenExpr(this);
}

std::any MxParser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IndexExprContext ------------------------------------------------------------------

std::vector<MxParser::ExprContext *> MxParser::IndexExprContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::IndexExprContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

tree::TerminalNode* MxParser::IndexExprContext::LEFT_SQUARE_BRACKET() {
  return getToken(MxParser::LEFT_SQUARE_BRACKET, 0);
}

tree::TerminalNode* MxParser::IndexExprContext::RIGHT_SQUARE_BRACKET() {
  return getToken(MxParser::RIGHT_SQUARE_BRACKET, 0);
}

MxParser::IndexExprContext::IndexExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::IndexExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIndexExpr(this);
}
void MxParser::IndexExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIndexExpr(this);
}

std::any MxParser::IndexExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitIndexExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExprContext ------------------------------------------------------------------

MxParser::ExprContext* MxParser::UnaryExprContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::UnaryExprContext::PLUS_PLUS() {
  return getToken(MxParser::PLUS_PLUS, 0);
}

tree::TerminalNode* MxParser::UnaryExprContext::MINUS_MINUS() {
  return getToken(MxParser::MINUS_MINUS, 0);
}

tree::TerminalNode* MxParser::UnaryExprContext::WAVE() {
  return getToken(MxParser::WAVE, 0);
}

tree::TerminalNode* MxParser::UnaryExprContext::EXCLAIMER() {
  return getToken(MxParser::EXCLAIMER, 0);
}

tree::TerminalNode* MxParser::UnaryExprContext::ADD() {
  return getToken(MxParser::ADD, 0);
}

tree::TerminalNode* MxParser::UnaryExprContext::SUB() {
  return getToken(MxParser::SUB, 0);
}

MxParser::UnaryExprContext::UnaryExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::UnaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpr(this);
}
void MxParser::UnaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpr(this);
}

std::any MxParser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TernaryExprContext ------------------------------------------------------------------

std::vector<MxParser::ExprContext *> MxParser::TernaryExprContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::TernaryExprContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

tree::TerminalNode* MxParser::TernaryExprContext::QUESTION() {
  return getToken(MxParser::QUESTION, 0);
}

tree::TerminalNode* MxParser::TernaryExprContext::COLON() {
  return getToken(MxParser::COLON, 0);
}

MxParser::TernaryExprContext::TernaryExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::TernaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTernaryExpr(this);
}
void MxParser::TernaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTernaryExpr(this);
}

std::any MxParser::TernaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitTernaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LiteralExprContext ------------------------------------------------------------------

MxParser::LiteralContext* MxParser::LiteralExprContext::literal() {
  return getRuleContext<MxParser::LiteralContext>(0);
}

MxParser::LiteralExprContext::LiteralExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::LiteralExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralExpr(this);
}
void MxParser::LiteralExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralExpr(this);
}

std::any MxParser::LiteralExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitLiteralExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InitArrayExprContext ------------------------------------------------------------------

MxParser::InitArrayContext* MxParser::InitArrayExprContext::initArray() {
  return getRuleContext<MxParser::InitArrayContext>(0);
}

MxParser::InitArrayExprContext::InitArrayExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::InitArrayExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitArrayExpr(this);
}
void MxParser::InitArrayExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitArrayExpr(this);
}

std::any MxParser::InitArrayExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitInitArrayExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FormatStringExprContext ------------------------------------------------------------------

MxParser::FormatStringContext* MxParser::FormatStringExprContext::formatString() {
  return getRuleContext<MxParser::FormatStringContext>(0);
}

MxParser::FormatStringExprContext::FormatStringExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::FormatStringExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormatStringExpr(this);
}
void MxParser::FormatStringExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormatStringExpr(this);
}

std::any MxParser::FormatStringExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitFormatStringExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdExprContext ------------------------------------------------------------------

tree::TerminalNode* MxParser::IdExprContext::ID() {
  return getToken(MxParser::ID, 0);
}

MxParser::IdExprContext::IdExprContext(ExprContext *ctx) { copyFrom(ctx); }

void MxParser::IdExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdExpr(this);
}
void MxParser::IdExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdExpr(this);
}

std::any MxParser::IdExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitIdExpr(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ExprContext* MxParser::expr() {
   return expr(0);
}

MxParser::ExprContext* MxParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MxParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  MxParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, MxParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(254);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(235);
      match(MxParser::LEFT_PARENTHESIS);
      setState(237);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 6) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 6)) & 432345775961767939) != 0)) {
        setState(236);
        expr(0);
      }
      setState(239);
      match(MxParser::RIGHT_PARENTHESIS);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ArrayExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(240);
      arrayConst();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<FuncCallExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(241);
      funcCall();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(242);
      _la = _input->LA(1);
      if (!(_la == MxParser::PLUS_PLUS

      || _la == MxParser::MINUS_MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(243);
      expr(20);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(244);
      _la = _input->LA(1);
      if (!(_la == MxParser::WAVE

      || _la == MxParser::EXCLAIMER)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(245);
      expr(19);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(246);
      _la = _input->LA(1);
      if (!(_la == MxParser::ADD

      || _la == MxParser::SUB)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(247);
      expr(17);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<InitArrayExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(248);
      initArray();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<InitObjectExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(249);
      initObject();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<FormatStringExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(250);
      formatString();
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<ThisExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(251);
      match(MxParser::THIS);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<LiteralExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(252);
      literal();
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<IdExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(253);
      match(MxParser::ID);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(307);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(305);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(256);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(257);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 17643725651968) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(258);
          expr(19);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(259);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(260);
          _la = _input->LA(1);
          if (!(_la == MxParser::ADD

          || _la == MxParser::SUB)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(261);
          expr(17);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(262);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(263);
          _la = _input->LA(1);
          if (!(_la == MxParser::SRL

          || _la == MxParser::SLL)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(264);
          expr(16);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(265);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(266);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 2111062325329920) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(267);
          expr(15);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(268);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(269);
          _la = _input->LA(1);
          if (!(_la == MxParser::ET

          || _la == MxParser::NET)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(270);
          expr(14);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(271);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(272);
          match(MxParser::AND);
          setState(273);
          expr(13);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(274);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(275);
          match(MxParser::XOR);
          setState(276);
          expr(12);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(277);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(278);
          match(MxParser::OR);
          setState(279);
          expr(11);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(280);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(281);
          match(MxParser::AND_AND);
          setState(282);
          expr(10);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(283);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(284);
          match(MxParser::OR_OR);
          setState(285);
          expr(9);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<TernaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(286);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(287);
          match(MxParser::QUESTION);
          setState(288);
          expr(0);
          setState(289);
          match(MxParser::COLON);
          setState(290);
          expr(7);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<IndexExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(292);

          if (!(precpred(_ctx, 25))) throw FailedPredicateException(this, "precpred(_ctx, 25)");
          setState(293);
          match(MxParser::LEFT_SQUARE_BRACKET);
          setState(294);
          expr(0);
          setState(295);
          match(MxParser::RIGHT_SQUARE_BRACKET);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<DotExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(297);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(298);
          match(MxParser::DOT);
          setState(301);
          _errHandler->sync(this);
          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
          case 1: {
            setState(299);
            match(MxParser::ID);
            break;
          }

          case 2: {
            setState(300);
            funcCall();
            break;
          }

          default:
            break;
          }
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<UnaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(303);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(304);
          _la = _input->LA(1);
          if (!(_la == MxParser::PLUS_PLUS

          || _la == MxParser::MINUS_MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        default:
          break;
        } 
      }
      setState(309);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- FormatStringContext ------------------------------------------------------------------

MxParser::FormatStringContext::FormatStringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::FormatStringContext::FORMAT_STRING_STARTER() {
  return getToken(MxParser::FORMAT_STRING_STARTER, 0);
}

tree::TerminalNode* MxParser::FormatStringContext::QUOTATION() {
  return getToken(MxParser::QUOTATION, 0);
}

std::vector<tree::TerminalNode *> MxParser::FormatStringContext::FORMAT_STRING_ELEMENT() {
  return getTokens(MxParser::FORMAT_STRING_ELEMENT);
}

tree::TerminalNode* MxParser::FormatStringContext::FORMAT_STRING_ELEMENT(size_t i) {
  return getToken(MxParser::FORMAT_STRING_ELEMENT, i);
}

std::vector<tree::TerminalNode *> MxParser::FormatStringContext::DOLLAR() {
  return getTokens(MxParser::DOLLAR);
}

tree::TerminalNode* MxParser::FormatStringContext::DOLLAR(size_t i) {
  return getToken(MxParser::DOLLAR, i);
}

std::vector<MxParser::ExprContext *> MxParser::FormatStringContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::FormatStringContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}


size_t MxParser::FormatStringContext::getRuleIndex() const {
  return MxParser::RuleFormatString;
}

void MxParser::FormatStringContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFormatString(this);
}

void MxParser::FormatStringContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFormatString(this);
}


std::any MxParser::FormatStringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitFormatString(this);
  else
    return visitor->visitChildren(this);
}

MxParser::FormatStringContext* MxParser::formatString() {
  FormatStringContext *_localctx = _tracker.createInstance<FormatStringContext>(_ctx, getState());
  enterRule(_localctx, 36, MxParser::RuleFormatString);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(310);
    match(MxParser::FORMAT_STRING_STARTER);
    setState(319);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MxParser::FORMAT_STRING_ELEMENT

    || _la == MxParser::DOLLAR) {
      setState(317);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case MxParser::FORMAT_STRING_ELEMENT: {
          setState(311);
          match(MxParser::FORMAT_STRING_ELEMENT);
          break;
        }

        case MxParser::DOLLAR: {
          setState(312);
          match(MxParser::DOLLAR);
          setState(314);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (((((_la - 6) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 6)) & 432345775961767939) != 0)) {
            setState(313);
            expr(0);
          }
          setState(316);
          match(MxParser::DOLLAR);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(321);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(322);
    match(MxParser::QUOTATION);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncCallContext ------------------------------------------------------------------

MxParser::FuncCallContext::FuncCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::FuncCallContext::ID() {
  return getToken(MxParser::ID, 0);
}

tree::TerminalNode* MxParser::FuncCallContext::LEFT_PARENTHESIS() {
  return getToken(MxParser::LEFT_PARENTHESIS, 0);
}

tree::TerminalNode* MxParser::FuncCallContext::RIGHT_PARENTHESIS() {
  return getToken(MxParser::RIGHT_PARENTHESIS, 0);
}

std::vector<MxParser::ExprContext *> MxParser::FuncCallContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::FuncCallContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MxParser::FuncCallContext::COMMA() {
  return getTokens(MxParser::COMMA);
}

tree::TerminalNode* MxParser::FuncCallContext::COMMA(size_t i) {
  return getToken(MxParser::COMMA, i);
}


size_t MxParser::FuncCallContext::getRuleIndex() const {
  return MxParser::RuleFuncCall;
}

void MxParser::FuncCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCall(this);
}

void MxParser::FuncCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCall(this);
}


std::any MxParser::FuncCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitFuncCall(this);
  else
    return visitor->visitChildren(this);
}

MxParser::FuncCallContext* MxParser::funcCall() {
  FuncCallContext *_localctx = _tracker.createInstance<FuncCallContext>(_ctx, getState());
  enterRule(_localctx, 38, MxParser::RuleFuncCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(324);
    match(MxParser::ID);
    setState(325);
    match(MxParser::LEFT_PARENTHESIS);
    setState(334);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 6) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 6)) & 432345775961767939) != 0)) {
      setState(326);
      expr(0);
      setState(331);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MxParser::COMMA) {
        setState(327);
        match(MxParser::COMMA);
        setState(328);
        expr(0);
        setState(333);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(336);
    match(MxParser::RIGHT_PARENTHESIS);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayConstContext ------------------------------------------------------------------

MxParser::ArrayConstContext::ArrayConstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::ArrayConstContext::LEFT_CURLY_BRACKET() {
  return getToken(MxParser::LEFT_CURLY_BRACKET, 0);
}

tree::TerminalNode* MxParser::ArrayConstContext::RIGHT_CURLY_BRACKET() {
  return getToken(MxParser::RIGHT_CURLY_BRACKET, 0);
}

std::vector<MxParser::LiteralContext *> MxParser::ArrayConstContext::literal() {
  return getRuleContexts<MxParser::LiteralContext>();
}

MxParser::LiteralContext* MxParser::ArrayConstContext::literal(size_t i) {
  return getRuleContext<MxParser::LiteralContext>(i);
}

std::vector<tree::TerminalNode *> MxParser::ArrayConstContext::COMMA() {
  return getTokens(MxParser::COMMA);
}

tree::TerminalNode* MxParser::ArrayConstContext::COMMA(size_t i) {
  return getToken(MxParser::COMMA, i);
}

std::vector<MxParser::ArrayConstContext *> MxParser::ArrayConstContext::arrayConst() {
  return getRuleContexts<MxParser::ArrayConstContext>();
}

MxParser::ArrayConstContext* MxParser::ArrayConstContext::arrayConst(size_t i) {
  return getRuleContext<MxParser::ArrayConstContext>(i);
}


size_t MxParser::ArrayConstContext::getRuleIndex() const {
  return MxParser::RuleArrayConst;
}

void MxParser::ArrayConstContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayConst(this);
}

void MxParser::ArrayConstContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayConst(this);
}


std::any MxParser::ArrayConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitArrayConst(this);
  else
    return visitor->visitChildren(this);
}

MxParser::ArrayConstContext* MxParser::arrayConst() {
  ArrayConstContext *_localctx = _tracker.createInstance<ArrayConstContext>(_ctx, getState());
  enterRule(_localctx, 40, MxParser::RuleArrayConst);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(361);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(338);
      match(MxParser::LEFT_CURLY_BRACKET);
      setState(347);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 281018496) != 0)) {
        setState(339);
        literal();
        setState(344);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == MxParser::COMMA) {
          setState(340);
          match(MxParser::COMMA);
          setState(341);
          literal();
          setState(346);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(349);
      match(MxParser::RIGHT_CURLY_BRACKET);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(350);
      match(MxParser::LEFT_CURLY_BRACKET);
      setState(351);
      arrayConst();
      setState(356);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MxParser::COMMA) {
        setState(352);
        match(MxParser::COMMA);
        setState(353);
        arrayConst();
        setState(358);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(359);
      match(MxParser::RIGHT_CURLY_BRACKET);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitArrayContext ------------------------------------------------------------------

MxParser::InitArrayContext::InitArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::InitArrayContext::NEW() {
  return getToken(MxParser::NEW, 0);
}

MxParser::TypeContext* MxParser::InitArrayContext::type() {
  return getRuleContext<MxParser::TypeContext>(0);
}

std::vector<tree::TerminalNode *> MxParser::InitArrayContext::LEFT_SQUARE_BRACKET() {
  return getTokens(MxParser::LEFT_SQUARE_BRACKET);
}

tree::TerminalNode* MxParser::InitArrayContext::LEFT_SQUARE_BRACKET(size_t i) {
  return getToken(MxParser::LEFT_SQUARE_BRACKET, i);
}

std::vector<MxParser::ExprContext *> MxParser::InitArrayContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::InitArrayContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MxParser::InitArrayContext::RIGHT_SQUARE_BRACKET() {
  return getTokens(MxParser::RIGHT_SQUARE_BRACKET);
}

tree::TerminalNode* MxParser::InitArrayContext::RIGHT_SQUARE_BRACKET(size_t i) {
  return getToken(MxParser::RIGHT_SQUARE_BRACKET, i);
}

MxParser::ArrayConstContext* MxParser::InitArrayContext::arrayConst() {
  return getRuleContext<MxParser::ArrayConstContext>(0);
}


size_t MxParser::InitArrayContext::getRuleIndex() const {
  return MxParser::RuleInitArray;
}

void MxParser::InitArrayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitArray(this);
}

void MxParser::InitArrayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitArray(this);
}


std::any MxParser::InitArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitInitArray(this);
  else
    return visitor->visitChildren(this);
}

MxParser::InitArrayContext* MxParser::initArray() {
  InitArrayContext *_localctx = _tracker.createInstance<InitArrayContext>(_ctx, getState());
  enterRule(_localctx, 42, MxParser::RuleInitArray);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(390);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(363);
      match(MxParser::NEW);
      setState(364);
      type(0);
      setState(369); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(365);
                match(MxParser::LEFT_SQUARE_BRACKET);
                setState(366);
                expr(0);
                setState(367);
                match(MxParser::RIGHT_SQUARE_BRACKET);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(371); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(377);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(373);
          match(MxParser::LEFT_SQUARE_BRACKET);
          setState(374);
          match(MxParser::RIGHT_SQUARE_BRACKET); 
        }
        setState(379);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(380);
      match(MxParser::NEW);
      setState(381);
      type(0);
      setState(384); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(382);
        match(MxParser::LEFT_SQUARE_BRACKET);
        setState(383);
        match(MxParser::RIGHT_SQUARE_BRACKET);
        setState(386); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == MxParser::LEFT_SQUARE_BRACKET);
      setState(388);
      arrayConst();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitObjectContext ------------------------------------------------------------------

MxParser::InitObjectContext::InitObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::InitObjectContext::NEW() {
  return getToken(MxParser::NEW, 0);
}

MxParser::TypeContext* MxParser::InitObjectContext::type() {
  return getRuleContext<MxParser::TypeContext>(0);
}

tree::TerminalNode* MxParser::InitObjectContext::LEFT_PARENTHESIS() {
  return getToken(MxParser::LEFT_PARENTHESIS, 0);
}

tree::TerminalNode* MxParser::InitObjectContext::RIGHT_PARENTHESIS() {
  return getToken(MxParser::RIGHT_PARENTHESIS, 0);
}


size_t MxParser::InitObjectContext::getRuleIndex() const {
  return MxParser::RuleInitObject;
}

void MxParser::InitObjectContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitObject(this);
}

void MxParser::InitObjectContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitObject(this);
}


std::any MxParser::InitObjectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitInitObject(this);
  else
    return visitor->visitChildren(this);
}

MxParser::InitObjectContext* MxParser::initObject() {
  InitObjectContext *_localctx = _tracker.createInstance<InitObjectContext>(_ctx, getState());
  enterRule(_localctx, 44, MxParser::RuleInitObject);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(392);
    match(MxParser::NEW);
    setState(393);
    type(0);
    setState(396);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      setState(394);
      match(MxParser::LEFT_PARENTHESIS);
      setState(395);
      match(MxParser::RIGHT_PARENTHESIS);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

MxParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::TypeContext::INT() {
  return getToken(MxParser::INT, 0);
}

tree::TerminalNode* MxParser::TypeContext::BOOLEAN() {
  return getToken(MxParser::BOOLEAN, 0);
}

tree::TerminalNode* MxParser::TypeContext::STR() {
  return getToken(MxParser::STR, 0);
}

tree::TerminalNode* MxParser::TypeContext::VOID() {
  return getToken(MxParser::VOID, 0);
}

tree::TerminalNode* MxParser::TypeContext::ID() {
  return getToken(MxParser::ID, 0);
}

MxParser::TypeContext* MxParser::TypeContext::type() {
  return getRuleContext<MxParser::TypeContext>(0);
}

tree::TerminalNode* MxParser::TypeContext::LEFT_SQUARE_BRACKET() {
  return getToken(MxParser::LEFT_SQUARE_BRACKET, 0);
}

tree::TerminalNode* MxParser::TypeContext::RIGHT_SQUARE_BRACKET() {
  return getToken(MxParser::RIGHT_SQUARE_BRACKET, 0);
}


size_t MxParser::TypeContext::getRuleIndex() const {
  return MxParser::RuleType;
}

void MxParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void MxParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}


std::any MxParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}


MxParser::TypeContext* MxParser::type() {
   return type(0);
}

MxParser::TypeContext* MxParser::type(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MxParser::TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, parentState);
  MxParser::TypeContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, MxParser::RuleType, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(404);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MxParser::INT: {
        setState(399);
        match(MxParser::INT);
        break;
      }

      case MxParser::BOOLEAN: {
        setState(400);
        match(MxParser::BOOLEAN);
        break;
      }

      case MxParser::STR: {
        setState(401);
        match(MxParser::STR);
        break;
      }

      case MxParser::VOID: {
        setState(402);
        match(MxParser::VOID);
        break;
      }

      case MxParser::ID: {
        setState(403);
        match(MxParser::ID);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(411);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(406);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(407);
        match(MxParser::LEFT_SQUARE_BRACKET);
        setState(408);
        match(MxParser::RIGHT_SQUARE_BRACKET); 
      }
      setState(413);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

MxParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::LiteralContext::INTEGER() {
  return getToken(MxParser::INTEGER, 0);
}

tree::TerminalNode* MxParser::LiteralContext::STRING() {
  return getToken(MxParser::STRING, 0);
}

tree::TerminalNode* MxParser::LiteralContext::BOOL() {
  return getToken(MxParser::BOOL, 0);
}

tree::TerminalNode* MxParser::LiteralContext::NULL_() {
  return getToken(MxParser::NULL_, 0);
}


size_t MxParser::LiteralContext::getRuleIndex() const {
  return MxParser::RuleLiteral;
}

void MxParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void MxParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


std::any MxParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

MxParser::LiteralContext* MxParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 48, MxParser::RuleLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(414);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281018496) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool MxParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 17: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);
    case 23: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool MxParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 18);
    case 1: return precpred(_ctx, 16);
    case 2: return precpred(_ctx, 15);
    case 3: return precpred(_ctx, 14);
    case 4: return precpred(_ctx, 13);
    case 5: return precpred(_ctx, 12);
    case 6: return precpred(_ctx, 11);
    case 7: return precpred(_ctx, 10);
    case 8: return precpred(_ctx, 9);
    case 9: return precpred(_ctx, 8);
    case 10: return precpred(_ctx, 7);
    case 11: return precpred(_ctx, 25);
    case 12: return precpred(_ctx, 22);
    case 13: return precpred(_ctx, 21);

  default:
    break;
  }
  return true;
}

bool MxParser::typeSempred(TypeContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 14: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void MxParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  mxParserInitialize();
#else
  ::antlr4::internal::call_once(mxParserOnceFlag, mxParserInitialize);
#endif
}
