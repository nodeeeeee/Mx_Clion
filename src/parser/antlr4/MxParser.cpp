
// Generated from Mx.g4 by ANTLR 4.13.1


#include "../../include/parser/MxListener.h"
#include "../../include/parser/MxVisitor.h"

#include "MxParser.h"


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
      "formatString", "update", "funcCall", "arrayConst", "initArray", "initObject", 
      "type"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "'f\"'", "'\"'", "'class'", "'for'", "'while'", 
      "'if'", "'else'", "'int'", "'bool'", "'string'", "'void'", "'main'", 
      "'return'", "'continue'", "'break'", "'new'", "'null'", "", "'this'", 
      "", "", "'$'", "", "", "", "'='", "'+'", "'-'", "'*'", "'/'", "'('", 
      "')'", "'{'", "'}'", "'['", "']'", "'++'", "'--'", "'%'", "'>>'", 
      "'<<'", "'>'", "'<'", "'>='", "'<='", "'=='", "'!='", "'&'", "'^'", 
      "'|'", "'&&'", "'||'", "'\\u003F'", "';'", "':'", "'.'", "','", "'~'", 
      "'!'"
    },
    std::vector<std::string>{
      "", "LITERAL", "SL_COMMENT", "ML_COMMENT", "DOCS_COMMENT", "FORMAT_STRING_ELEMENT", 
      "STRING", "FORMAT_STRING_STARTER", "QUOTATION", "CLASS", "FOR", "WHILE", 
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
  	4,1,65,399,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
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
  	1,12,1,12,3,12,210,8,12,1,12,1,12,3,12,214,8,12,1,12,1,12,1,12,1,13,1,
  	13,1,13,1,13,1,13,1,14,1,14,1,14,3,14,227,8,14,1,15,1,15,1,16,1,16,1,
  	17,1,17,1,17,3,17,236,8,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,17,1,17,3,17,252,8,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,3,17,296,8,17,1,17,1,17,1,
  	17,5,17,301,8,17,10,17,12,17,304,9,17,1,18,1,18,1,18,1,18,1,18,1,18,5,
  	18,312,8,18,10,18,12,18,315,9,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,
  	19,3,19,325,8,19,1,20,1,20,1,20,1,20,1,20,5,20,332,8,20,10,20,12,20,335,
  	9,20,3,20,337,8,20,1,20,1,20,1,21,1,21,1,21,1,21,5,21,345,8,21,10,21,
  	12,21,348,9,21,3,21,350,8,21,1,21,1,21,1,21,1,21,1,21,5,21,357,8,21,10,
  	21,12,21,360,9,21,1,21,1,21,3,21,364,8,21,1,22,1,22,1,22,1,22,3,22,370,
  	8,22,1,22,4,22,373,8,22,11,22,12,22,374,1,23,1,23,1,23,1,23,3,23,381,
  	8,23,1,24,1,24,1,24,1,24,1,24,1,24,3,24,389,8,24,1,24,1,24,1,24,5,24,
  	394,8,24,10,24,12,24,397,9,24,1,24,1,195,2,34,48,25,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,0,7,1,0,43,44,1,0,
  	64,65,1,0,33,34,2,0,35,36,45,45,1,0,46,47,1,0,48,51,1,0,52,53,456,0,59,
  	1,0,0,0,2,77,1,0,0,0,4,85,1,0,0,0,6,90,1,0,0,0,8,115,1,0,0,0,10,117,1,
  	0,0,0,12,134,1,0,0,0,14,153,1,0,0,0,16,158,1,0,0,0,18,176,1,0,0,0,20,
  	187,1,0,0,0,22,191,1,0,0,0,24,200,1,0,0,0,26,218,1,0,0,0,28,223,1,0,0,
  	0,30,228,1,0,0,0,32,230,1,0,0,0,34,251,1,0,0,0,36,305,1,0,0,0,38,324,
  	1,0,0,0,40,326,1,0,0,0,42,363,1,0,0,0,44,365,1,0,0,0,46,376,1,0,0,0,48,
  	388,1,0,0,0,50,51,3,16,8,0,51,52,5,60,0,0,52,58,1,0,0,0,53,54,3,10,5,
  	0,54,55,5,60,0,0,55,58,1,0,0,0,56,58,3,12,6,0,57,50,1,0,0,0,57,53,1,0,
  	0,0,57,56,1,0,0,0,58,61,1,0,0,0,59,57,1,0,0,0,59,60,1,0,0,0,60,62,1,0,
  	0,0,61,59,1,0,0,0,62,72,3,2,1,0,63,64,3,16,8,0,64,65,5,60,0,0,65,71,1,
  	0,0,0,66,67,3,10,5,0,67,68,5,60,0,0,68,71,1,0,0,0,69,71,3,12,6,0,70,63,
  	1,0,0,0,70,66,1,0,0,0,70,69,1,0,0,0,71,74,1,0,0,0,72,70,1,0,0,0,72,73,
  	1,0,0,0,73,75,1,0,0,0,74,72,1,0,0,0,75,76,5,0,0,1,76,1,1,0,0,0,77,78,
  	5,14,0,0,78,79,5,18,0,0,79,80,5,37,0,0,80,81,5,38,0,0,81,82,3,22,11,0,
  	82,3,1,0,0,0,83,86,3,8,4,0,84,86,3,6,3,0,85,83,1,0,0,0,85,84,1,0,0,0,
  	86,5,1,0,0,0,87,91,3,12,6,0,88,91,3,14,7,0,89,91,3,16,8,0,90,87,1,0,0,
  	0,90,88,1,0,0,0,90,89,1,0,0,0,91,7,1,0,0,0,92,93,3,34,17,0,93,94,5,60,
  	0,0,94,116,1,0,0,0,95,96,3,10,5,0,96,97,5,60,0,0,97,116,1,0,0,0,98,116,
  	3,18,9,0,99,100,3,20,10,0,100,101,5,60,0,0,101,116,1,0,0,0,102,116,3,
  	22,11,0,103,116,3,24,12,0,104,116,3,26,13,0,105,106,3,28,14,0,106,107,
  	5,60,0,0,107,116,1,0,0,0,108,109,3,30,15,0,109,110,5,60,0,0,110,116,1,
  	0,0,0,111,112,3,32,16,0,112,113,5,60,0,0,113,116,1,0,0,0,114,116,5,60,
  	0,0,115,92,1,0,0,0,115,95,1,0,0,0,115,98,1,0,0,0,115,99,1,0,0,0,115,102,
  	1,0,0,0,115,103,1,0,0,0,115,104,1,0,0,0,115,105,1,0,0,0,115,108,1,0,0,
  	0,115,111,1,0,0,0,115,114,1,0,0,0,116,9,1,0,0,0,117,118,3,48,24,0,118,
  	121,5,27,0,0,119,120,5,32,0,0,120,122,3,34,17,0,121,119,1,0,0,0,121,122,
  	1,0,0,0,122,131,1,0,0,0,123,124,5,63,0,0,124,127,5,27,0,0,125,126,5,32,
  	0,0,126,128,3,34,17,0,127,125,1,0,0,0,127,128,1,0,0,0,128,130,1,0,0,0,
  	129,123,1,0,0,0,130,133,1,0,0,0,131,129,1,0,0,0,131,132,1,0,0,0,132,11,
  	1,0,0,0,133,131,1,0,0,0,134,135,3,48,24,0,135,136,5,27,0,0,136,148,5,
  	37,0,0,137,138,3,48,24,0,138,145,5,27,0,0,139,140,5,63,0,0,140,141,3,
  	48,24,0,141,142,5,27,0,0,142,144,1,0,0,0,143,139,1,0,0,0,144,147,1,0,
  	0,0,145,143,1,0,0,0,145,146,1,0,0,0,146,149,1,0,0,0,147,145,1,0,0,0,148,
  	137,1,0,0,0,148,149,1,0,0,0,149,150,1,0,0,0,150,151,5,38,0,0,151,152,
  	3,22,11,0,152,13,1,0,0,0,153,154,5,27,0,0,154,155,5,37,0,0,155,156,5,
  	38,0,0,156,157,3,22,11,0,157,15,1,0,0,0,158,159,5,9,0,0,159,160,5,27,
  	0,0,160,171,5,39,0,0,161,162,3,10,5,0,162,163,5,60,0,0,163,170,1,0,0,
  	0,164,170,3,12,6,0,165,170,3,14,7,0,166,167,3,16,8,0,167,168,5,60,0,0,
  	168,170,1,0,0,0,169,161,1,0,0,0,169,164,1,0,0,0,169,165,1,0,0,0,169,166,
  	1,0,0,0,170,173,1,0,0,0,171,169,1,0,0,0,171,172,1,0,0,0,172,174,1,0,0,
  	0,173,171,1,0,0,0,174,175,5,40,0,0,175,17,1,0,0,0,176,177,5,12,0,0,177,
  	179,5,37,0,0,178,180,3,34,17,0,179,178,1,0,0,0,179,180,1,0,0,0,180,181,
  	1,0,0,0,181,182,5,38,0,0,182,185,3,8,4,0,183,184,5,13,0,0,184,186,3,8,
  	4,0,185,183,1,0,0,0,185,186,1,0,0,0,186,19,1,0,0,0,187,188,3,34,17,0,
  	188,189,5,32,0,0,189,190,3,34,17,0,190,21,1,0,0,0,191,195,5,39,0,0,192,
  	194,3,4,2,0,193,192,1,0,0,0,194,197,1,0,0,0,195,196,1,0,0,0,195,193,1,
  	0,0,0,196,198,1,0,0,0,197,195,1,0,0,0,198,199,5,40,0,0,199,23,1,0,0,0,
  	200,201,5,10,0,0,201,205,5,37,0,0,202,206,3,10,5,0,203,206,3,20,10,0,
  	204,206,3,34,17,0,205,202,1,0,0,0,205,203,1,0,0,0,205,204,1,0,0,0,205,
  	206,1,0,0,0,206,207,1,0,0,0,207,209,5,60,0,0,208,210,3,34,17,0,209,208,
  	1,0,0,0,209,210,1,0,0,0,210,211,1,0,0,0,211,213,5,60,0,0,212,214,3,38,
  	19,0,213,212,1,0,0,0,213,214,1,0,0,0,214,215,1,0,0,0,215,216,5,38,0,0,
  	216,217,3,8,4,0,217,25,1,0,0,0,218,219,5,11,0,0,219,220,5,37,0,0,220,
  	221,3,34,17,0,221,222,5,38,0,0,222,27,1,0,0,0,223,226,5,19,0,0,224,227,
  	3,34,17,0,225,227,3,40,20,0,226,224,1,0,0,0,226,225,1,0,0,0,226,227,1,
  	0,0,0,227,29,1,0,0,0,228,229,5,20,0,0,229,31,1,0,0,0,230,231,5,21,0,0,
  	231,33,1,0,0,0,232,233,6,17,-1,0,233,235,5,37,0,0,234,236,3,34,17,0,235,
  	234,1,0,0,0,235,236,1,0,0,0,236,237,1,0,0,0,237,252,5,38,0,0,238,252,
  	3,42,21,0,239,252,3,40,20,0,240,241,7,0,0,0,241,252,3,34,17,19,242,243,
  	7,1,0,0,243,252,3,34,17,18,244,245,7,2,0,0,245,252,3,34,17,16,246,252,
  	3,44,22,0,247,252,3,46,23,0,248,252,3,36,18,0,249,252,5,25,0,0,250,252,
  	5,1,0,0,251,232,1,0,0,0,251,238,1,0,0,0,251,239,1,0,0,0,251,240,1,0,0,
  	0,251,242,1,0,0,0,251,244,1,0,0,0,251,246,1,0,0,0,251,247,1,0,0,0,251,
  	248,1,0,0,0,251,249,1,0,0,0,251,250,1,0,0,0,252,302,1,0,0,0,253,254,10,
  	21,0,0,254,255,5,62,0,0,255,301,3,34,17,22,256,257,10,17,0,0,257,258,
  	7,3,0,0,258,301,3,34,17,18,259,260,10,15,0,0,260,261,7,2,0,0,261,301,
  	3,34,17,16,262,263,10,14,0,0,263,264,7,4,0,0,264,301,3,34,17,15,265,266,
  	10,13,0,0,266,267,7,5,0,0,267,301,3,34,17,14,268,269,10,12,0,0,269,270,
  	7,6,0,0,270,301,3,34,17,13,271,272,10,11,0,0,272,273,5,54,0,0,273,301,
  	3,34,17,12,274,275,10,10,0,0,275,276,5,55,0,0,276,301,3,34,17,11,277,
  	278,10,9,0,0,278,279,5,56,0,0,279,301,3,34,17,10,280,281,10,8,0,0,281,
  	282,5,57,0,0,282,301,3,34,17,9,283,284,10,7,0,0,284,285,5,58,0,0,285,
  	301,3,34,17,8,286,287,10,6,0,0,287,288,5,59,0,0,288,289,3,34,17,0,289,
  	290,5,61,0,0,290,291,3,34,17,7,291,301,1,0,0,0,292,293,10,24,0,0,293,
  	295,5,41,0,0,294,296,3,34,17,0,295,294,1,0,0,0,295,296,1,0,0,0,296,297,
  	1,0,0,0,297,301,5,42,0,0,298,299,10,20,0,0,299,301,7,0,0,0,300,253,1,
  	0,0,0,300,256,1,0,0,0,300,259,1,0,0,0,300,262,1,0,0,0,300,265,1,0,0,0,
  	300,268,1,0,0,0,300,271,1,0,0,0,300,274,1,0,0,0,300,277,1,0,0,0,300,280,
  	1,0,0,0,300,283,1,0,0,0,300,286,1,0,0,0,300,292,1,0,0,0,300,298,1,0,0,
  	0,301,304,1,0,0,0,302,300,1,0,0,0,302,303,1,0,0,0,303,35,1,0,0,0,304,
  	302,1,0,0,0,305,313,5,7,0,0,306,312,5,5,0,0,307,308,5,28,0,0,308,309,
  	3,34,17,0,309,310,5,28,0,0,310,312,1,0,0,0,311,306,1,0,0,0,311,307,1,
  	0,0,0,312,315,1,0,0,0,313,311,1,0,0,0,313,314,1,0,0,0,314,316,1,0,0,0,
  	315,313,1,0,0,0,316,317,5,8,0,0,317,37,1,0,0,0,318,319,7,0,0,0,319,325,
  	5,27,0,0,320,321,5,27,0,0,321,325,7,0,0,0,322,325,3,20,10,0,323,325,3,
  	34,17,0,324,318,1,0,0,0,324,320,1,0,0,0,324,322,1,0,0,0,324,323,1,0,0,
  	0,325,39,1,0,0,0,326,327,5,27,0,0,327,336,5,37,0,0,328,333,3,34,17,0,
  	329,330,5,63,0,0,330,332,3,34,17,0,331,329,1,0,0,0,332,335,1,0,0,0,333,
  	331,1,0,0,0,333,334,1,0,0,0,334,337,1,0,0,0,335,333,1,0,0,0,336,328,1,
  	0,0,0,336,337,1,0,0,0,337,338,1,0,0,0,338,339,5,38,0,0,339,41,1,0,0,0,
  	340,349,5,39,0,0,341,346,5,1,0,0,342,343,5,63,0,0,343,345,5,1,0,0,344,
  	342,1,0,0,0,345,348,1,0,0,0,346,344,1,0,0,0,346,347,1,0,0,0,347,350,1,
  	0,0,0,348,346,1,0,0,0,349,341,1,0,0,0,349,350,1,0,0,0,350,351,1,0,0,0,
  	351,364,5,40,0,0,352,353,5,39,0,0,353,358,3,42,21,0,354,355,5,63,0,0,
  	355,357,3,42,21,0,356,354,1,0,0,0,357,360,1,0,0,0,358,356,1,0,0,0,358,
  	359,1,0,0,0,359,361,1,0,0,0,360,358,1,0,0,0,361,362,5,40,0,0,362,364,
  	1,0,0,0,363,340,1,0,0,0,363,352,1,0,0,0,364,43,1,0,0,0,365,366,5,22,0,
  	0,366,372,3,48,24,0,367,369,5,41,0,0,368,370,3,34,17,0,369,368,1,0,0,
  	0,369,370,1,0,0,0,370,371,1,0,0,0,371,373,5,42,0,0,372,367,1,0,0,0,373,
  	374,1,0,0,0,374,372,1,0,0,0,374,375,1,0,0,0,375,45,1,0,0,0,376,377,5,
  	22,0,0,377,380,3,48,24,0,378,379,5,37,0,0,379,381,5,38,0,0,380,378,1,
  	0,0,0,380,381,1,0,0,0,381,47,1,0,0,0,382,383,6,24,-1,0,383,389,5,14,0,
  	0,384,389,5,15,0,0,385,389,5,16,0,0,386,389,5,17,0,0,387,389,5,27,0,0,
  	388,382,1,0,0,0,388,384,1,0,0,0,388,385,1,0,0,0,388,386,1,0,0,0,388,387,
  	1,0,0,0,389,395,1,0,0,0,390,391,10,1,0,0,391,392,5,41,0,0,392,394,5,42,
  	0,0,393,390,1,0,0,0,394,397,1,0,0,0,395,393,1,0,0,0,395,396,1,0,0,0,396,
  	49,1,0,0,0,397,395,1,0,0,0,40,57,59,70,72,85,90,115,121,127,131,145,148,
  	169,171,179,185,195,205,209,213,226,235,251,295,300,302,311,313,324,333,
  	336,346,349,358,363,369,374,380,388,395
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
      ((1ULL << _la) & 134464000) != 0)) {
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

MxParser::ExprContext* MxParser::RegularStatContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}

tree::TerminalNode* MxParser::RegularStatContext::SEMI_COLON() {
  return getToken(MxParser::SEMI_COLON, 0);
}

MxParser::VarDefContext* MxParser::RegularStatContext::varDef() {
  return getRuleContext<MxParser::VarDefContext>(0);
}

MxParser::IfStatContext* MxParser::RegularStatContext::ifStat() {
  return getRuleContext<MxParser::IfStatContext>(0);
}

MxParser::AssignStatContext* MxParser::RegularStatContext::assignStat() {
  return getRuleContext<MxParser::AssignStatContext>(0);
}

MxParser::BlockContext* MxParser::RegularStatContext::block() {
  return getRuleContext<MxParser::BlockContext>(0);
}

MxParser::ForStatContext* MxParser::RegularStatContext::forStat() {
  return getRuleContext<MxParser::ForStatContext>(0);
}

MxParser::WhileStatContext* MxParser::RegularStatContext::whileStat() {
  return getRuleContext<MxParser::WhileStatContext>(0);
}

MxParser::ReturnStatContext* MxParser::RegularStatContext::returnStat() {
  return getRuleContext<MxParser::ReturnStatContext>(0);
}

MxParser::ContinueContext* MxParser::RegularStatContext::continue_() {
  return getRuleContext<MxParser::ContinueContext>(0);
}

MxParser::BreakContext* MxParser::RegularStatContext::break_() {
  return getRuleContext<MxParser::BreakContext>(0);
}


size_t MxParser::RegularStatContext::getRuleIndex() const {
  return MxParser::RuleRegularStat;
}

void MxParser::RegularStatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRegularStat(this);
}

void MxParser::RegularStatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRegularStat(this);
}


std::any MxParser::RegularStatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitRegularStat(this);
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
      enterOuterAlt(_localctx, 1);
      setState(92);
      expr(0);
      setState(93);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(95);
      varDef();
      setState(96);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(98);
      ifStat();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(99);
      assignStat();
      setState(100);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(102);
      block();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(103);
      forStat();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(104);
      whileStat();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(105);
      returnStat();
      setState(106);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(108);
      continue_();
      setState(109);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(111);
      break_();
      setState(112);
      match(MxParser::SEMI_COLON);
      break;
    }

    case 11: {
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
      ((1ULL << _la) & 134463488) != 0)) {
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
      ((1ULL << _la) & 134464000) != 0)) {
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
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 27101415604354) != 0) || _la == MxParser::WAVE

    || _la == MxParser::EXCLAIMER) {
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

MxParser::AssignStatContext* MxParser::ForStatContext::assignStat() {
  return getRuleContext<MxParser::AssignStatContext>(0);
}

std::vector<MxParser::ExprContext *> MxParser::ForStatContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::ForStatContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

MxParser::UpdateContext* MxParser::ForStatContext::update() {
  return getRuleContext<MxParser::UpdateContext>(0);
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
      varDef();
      break;
    }

    case 2: {
      setState(203);
      assignStat();
      break;
    }

    case 3: {
      setState(204);
      expr(0);
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
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 27101415604354) != 0) || _la == MxParser::WAVE

    || _la == MxParser::EXCLAIMER) {
      setState(208);
      antlrcpp::downCast<ForStatContext *>(_localctx)->forCondExpr = expr(0);
    }
    setState(211);
    match(MxParser::SEMI_COLON);
    setState(213);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 27101415604354) != 0) || _la == MxParser::WAVE

    || _la == MxParser::EXCLAIMER) {
      setState(212);
      antlrcpp::downCast<ForStatContext *>(_localctx)->forUpdateExpr = update();
    }
    setState(215);
    match(MxParser::RIGHT_PARENTHESIS);
    setState(216);
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
    setState(218);
    match(MxParser::WHILE);
    setState(219);
    match(MxParser::LEFT_PARENTHESIS);
    setState(220);
    antlrcpp::downCast<WhileStatContext *>(_localctx)->whileCondExpr = expr(0);
    setState(221);
    match(MxParser::RIGHT_PARENTHESIS);
   
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
    setState(223);
    match(MxParser::RETURN);
    setState(226);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      setState(224);
      expr(0);
      break;
    }

    case 2: {
      setState(225);
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
    setState(228);
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
    setState(230);
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

std::vector<MxParser::ExprContext *> MxParser::DotExprContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::DotExprContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
}

tree::TerminalNode* MxParser::DotExprContext::DOT() {
  return getToken(MxParser::DOT, 0);
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

tree::TerminalNode* MxParser::LiteralExprContext::LITERAL() {
  return getToken(MxParser::LITERAL, 0);
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
    setState(251);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(233);
      match(MxParser::LEFT_PARENTHESIS);
      setState(235);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 27101415604354) != 0) || _la == MxParser::WAVE

      || _la == MxParser::EXCLAIMER) {
        setState(234);
        expr(0);
      }
      setState(237);
      match(MxParser::RIGHT_PARENTHESIS);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ArrayExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(238);
      arrayConst();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<FuncCallExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(239);
      funcCall();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(240);
      _la = _input->LA(1);
      if (!(_la == MxParser::PLUS_PLUS

      || _la == MxParser::MINUS_MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(241);
      expr(19);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(242);
      _la = _input->LA(1);
      if (!(_la == MxParser::WAVE

      || _la == MxParser::EXCLAIMER)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(243);
      expr(18);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<UnaryExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(244);
      _la = _input->LA(1);
      if (!(_la == MxParser::ADD

      || _la == MxParser::SUB)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(245);
      expr(16);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<InitArrayExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(246);
      initArray();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<InitObjectExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(247);
      initObject();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<FormatStringExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(248);
      formatString();
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<ThisExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(249);
      match(MxParser::THIS);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<LiteralExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(250);
      match(MxParser::LITERAL);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(302);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(300);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<DotExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(253);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(254);
          match(MxParser::DOT);
          setState(255);
          expr(22);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(256);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(257);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 35287451303936) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(258);
          expr(18);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(259);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
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
          expr(16);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(262);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
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
          expr(15);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(265);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(266);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 4222124650659840) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(267);
          expr(14);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(268);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
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
          expr(13);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(271);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(272);
          match(MxParser::AND);
          setState(273);
          expr(12);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(274);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(275);
          match(MxParser::XOR);
          setState(276);
          expr(11);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(277);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(278);
          match(MxParser::OR);
          setState(279);
          expr(10);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(280);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(281);
          match(MxParser::AND_AND);
          setState(282);
          expr(9);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<BinaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(283);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(284);
          match(MxParser::OR_OR);
          setState(285);
          expr(8);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<TernaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(286);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
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

        case 13: {
          auto newContext = _tracker.createInstance<IndexExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(292);

          if (!(precpred(_ctx, 24))) throw FailedPredicateException(this, "precpred(_ctx, 24)");
          setState(293);
          match(MxParser::LEFT_SQUARE_BRACKET);
          setState(295);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 27101415604354) != 0) || _la == MxParser::WAVE

          || _la == MxParser::EXCLAIMER) {
            setState(294);
            expr(0);
          }
          setState(297);
          match(MxParser::RIGHT_SQUARE_BRACKET);
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<UnaryExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(298);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(299);
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
      setState(304);
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
    setState(305);
    match(MxParser::FORMAT_STRING_STARTER);
    setState(313);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MxParser::FORMAT_STRING_ELEMENT

    || _la == MxParser::DOLLAR) {
      setState(311);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case MxParser::FORMAT_STRING_ELEMENT: {
          setState(306);
          match(MxParser::FORMAT_STRING_ELEMENT);
          break;
        }

        case MxParser::DOLLAR: {
          setState(307);
          match(MxParser::DOLLAR);
          setState(308);
          expr(0);
          setState(309);
          match(MxParser::DOLLAR);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(315);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(316);
    match(MxParser::QUOTATION);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UpdateContext ------------------------------------------------------------------

MxParser::UpdateContext::UpdateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MxParser::UpdateContext::ID() {
  return getToken(MxParser::ID, 0);
}

tree::TerminalNode* MxParser::UpdateContext::PLUS_PLUS() {
  return getToken(MxParser::PLUS_PLUS, 0);
}

tree::TerminalNode* MxParser::UpdateContext::MINUS_MINUS() {
  return getToken(MxParser::MINUS_MINUS, 0);
}

MxParser::AssignStatContext* MxParser::UpdateContext::assignStat() {
  return getRuleContext<MxParser::AssignStatContext>(0);
}

MxParser::ExprContext* MxParser::UpdateContext::expr() {
  return getRuleContext<MxParser::ExprContext>(0);
}


size_t MxParser::UpdateContext::getRuleIndex() const {
  return MxParser::RuleUpdate;
}

void MxParser::UpdateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUpdate(this);
}

void MxParser::UpdateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MxListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUpdate(this);
}


std::any MxParser::UpdateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MxVisitor*>(visitor))
    return parserVisitor->visitUpdate(this);
  else
    return visitor->visitChildren(this);
}

MxParser::UpdateContext* MxParser::update() {
  UpdateContext *_localctx = _tracker.createInstance<UpdateContext>(_ctx, getState());
  enterRule(_localctx, 38, MxParser::RuleUpdate);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(324);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(318);
      _la = _input->LA(1);
      if (!(_la == MxParser::PLUS_PLUS

      || _la == MxParser::MINUS_MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(319);
      match(MxParser::ID);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(320);
      match(MxParser::ID);
      setState(321);
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

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(322);
      assignStat();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(323);
      expr(0);
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
  enterRule(_localctx, 40, MxParser::RuleFuncCall);
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
    setState(326);
    match(MxParser::ID);
    setState(327);
    match(MxParser::LEFT_PARENTHESIS);
    setState(336);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 27101415604354) != 0) || _la == MxParser::WAVE

    || _la == MxParser::EXCLAIMER) {
      setState(328);
      expr(0);
      setState(333);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MxParser::COMMA) {
        setState(329);
        match(MxParser::COMMA);
        setState(330);
        expr(0);
        setState(335);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(338);
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

std::vector<tree::TerminalNode *> MxParser::ArrayConstContext::LITERAL() {
  return getTokens(MxParser::LITERAL);
}

tree::TerminalNode* MxParser::ArrayConstContext::LITERAL(size_t i) {
  return getToken(MxParser::LITERAL, i);
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
  enterRule(_localctx, 42, MxParser::RuleArrayConst);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(363);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(340);
      match(MxParser::LEFT_CURLY_BRACKET);
      setState(349);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MxParser::LITERAL) {
        setState(341);
        match(MxParser::LITERAL);
        setState(346);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == MxParser::COMMA) {
          setState(342);
          match(MxParser::COMMA);
          setState(343);
          match(MxParser::LITERAL);
          setState(348);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(351);
      match(MxParser::RIGHT_CURLY_BRACKET);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(352);
      match(MxParser::LEFT_CURLY_BRACKET);
      setState(353);
      arrayConst();
      setState(358);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MxParser::COMMA) {
        setState(354);
        match(MxParser::COMMA);
        setState(355);
        arrayConst();
        setState(360);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(361);
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

std::vector<tree::TerminalNode *> MxParser::InitArrayContext::RIGHT_SQUARE_BRACKET() {
  return getTokens(MxParser::RIGHT_SQUARE_BRACKET);
}

tree::TerminalNode* MxParser::InitArrayContext::RIGHT_SQUARE_BRACKET(size_t i) {
  return getToken(MxParser::RIGHT_SQUARE_BRACKET, i);
}

std::vector<MxParser::ExprContext *> MxParser::InitArrayContext::expr() {
  return getRuleContexts<MxParser::ExprContext>();
}

MxParser::ExprContext* MxParser::InitArrayContext::expr(size_t i) {
  return getRuleContext<MxParser::ExprContext>(i);
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
  enterRule(_localctx, 44, MxParser::RuleInitArray);
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
    setState(365);
    match(MxParser::NEW);
    setState(366);
    type(0);
    setState(372); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(367);
              match(MxParser::LEFT_SQUARE_BRACKET);
              setState(369);
              _errHandler->sync(this);

              _la = _input->LA(1);
              if ((((_la & ~ 0x3fULL) == 0) &&
                ((1ULL << _la) & 27101415604354) != 0) || _la == MxParser::WAVE

              || _la == MxParser::EXCLAIMER) {
                setState(368);
                expr(0);
              }
              setState(371);
              match(MxParser::RIGHT_SQUARE_BRACKET);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(374); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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
  enterRule(_localctx, 46, MxParser::RuleInitObject);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(376);
    match(MxParser::NEW);
    setState(377);
    type(0);
    setState(380);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      setState(378);
      match(MxParser::LEFT_PARENTHESIS);
      setState(379);
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
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, MxParser::RuleType, precedence);

    

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
    setState(388);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MxParser::INT: {
        setState(383);
        match(MxParser::INT);
        break;
      }

      case MxParser::BOOLEAN: {
        setState(384);
        match(MxParser::BOOLEAN);
        break;
      }

      case MxParser::STR: {
        setState(385);
        match(MxParser::STR);
        break;
      }

      case MxParser::VOID: {
        setState(386);
        match(MxParser::VOID);
        break;
      }

      case MxParser::ID: {
        setState(387);
        match(MxParser::ID);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(395);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(390);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(391);
        match(MxParser::LEFT_SQUARE_BRACKET);
        setState(392);
        match(MxParser::RIGHT_SQUARE_BRACKET); 
      }
      setState(397);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
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
    case 24: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool MxParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 21);
    case 1: return precpred(_ctx, 17);
    case 2: return precpred(_ctx, 15);
    case 3: return precpred(_ctx, 14);
    case 4: return precpred(_ctx, 13);
    case 5: return precpred(_ctx, 12);
    case 6: return precpred(_ctx, 11);
    case 7: return precpred(_ctx, 10);
    case 8: return precpred(_ctx, 9);
    case 9: return precpred(_ctx, 8);
    case 10: return precpred(_ctx, 7);
    case 11: return precpred(_ctx, 6);
    case 12: return precpred(_ctx, 24);
    case 13: return precpred(_ctx, 20);

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
