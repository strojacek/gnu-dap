
// Generated from Dap.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"




class  DapLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, ABEND = 10, END = 11, LENGTH = 12, QKUPCASE = 13, 
    SYSEVALF = 14, ABORT = 15, EVAL = 16, LET = 17, QSCAN = 18, SYSEXEC = 19, 
    ACT = 20, FILE = 21, LIST = 22, QSUBSTR = 23, SYSFUNC = 24, ACTIVATE = 25, 
    GLOBAL = 26, LISTM = 27, QSYSFUNC = 28, SYSGET = 29, BQUOTE = 30, GO = 31, 
    LOCAL = 32, QUOTE = 33, SYSRPUT = 34, BY = 35, GOTO = 36, MACRO = 37, 
    QUPCASE = 38, THEN = 39, CLEAR = 40, IF = 41, MEND = 42, RESOLVE = 43, 
    TO = 44, CLOSE = 45, INC = 46, PAUSE = 47, RETURN = 48, TSO = 49, CMS = 50, 
    INCLUDE = 51, NRSTR = 52, RUN = 53, UNQUOTE = 54, COMANDR = 55, INDEX = 56, 
    ON = 57, SAVE = 58, UNSTR = 59, COPY = 60, INFILE = 61, OPEN = 62, SCAN = 63, 
    UNTIL = 64, DEACT = 65, INPUT = 66, PUT = 67, STOP = 68, UPCASE = 69, 
    DEL = 70, KCMPRES = 71, NRBQUOTE = 72, STR = 73, WHILE = 74, DELETE = 75, 
    KINDEX = 76, NRQUOTE = 77, SYSCALL = 78, WINDOW = 79, DISPLAY = 80, 
    KLEFT = 81, METASYM = 82, SUBSTR = 83, DMIDSPLY = 84, KLENGTH = 85, 
    QKCMPRES = 86, SUPERQ = 87, DMISPLIT = 88, KSCAN = 89, QKLEFT = 90, 
    SYMDEL = 91, DO = 92, KSUBSTR = 93, QKSCAN = 94, SYMEXIST = 95, EDIT = 96, 
    KTRIM = 97, QKSUBSTR = 98, SYMGLOBL = 99, ELSE = 100, KUPCASE = 101, 
    QKTRIM = 102, SYMLOCAL = 103, Tk_NULL = 104, CANCEL = 105, NOLIST = 106, 
    ARRAY = 107, ARRAY_NUMERIC_ELEMENTS = 108, ARRAY_CHARACTER_ELEMENTS = 109, 
    ARRAY_ALL_ELEMENTS = 110, GROUPFORMAT = 111, NOTSORTED = 112, DESCENDING = 113, 
    CALL = 114, DEBUG = 115, NESTING = 116, STACK = 117, READ = 118, PW = 119, 
    SOURCE = 120, VIEW = 121, PGM = 122, ENCRYPT = 123, NOSAVE = 124, DATALINES = 125, 
    CARDS = 126, LINES = 127, DATALINES4 = 128, CARDS4 = 129, LINES4 = 130, 
    END_DATALINES4 = 131, ALTER = 132, DISK = 133, DUMMY = 134, GTERM = 135, 
    PIPE = 136, PLOTTER = 137, PRINTER = 138, TAPE = 139, TEMP = 140, TERMINAL = 141, 
    UPRINTER = 142, DSD = 143, EXPANDTABS = 144, NOEXPANDTABS = 145, FLOWOVER = 146, 
    MISSOVER = 147, PAD = 148, NOPAD = 149, SCANOVER = 150, SHAREBUFFERS = 151, 
    STOPOVER = 152, TRUNCOVER = 153, V_INFILE_ = 154, INPUT_ODS = 155, DATE = 156, 
    DATETIME = 157, DDMMYY = 158, INFORMAT_COMMA = 159, INFORMAT_CHAR = 160, 
    DROP = 161, PROC = 162, ANOVA = 163, MEANS = 164, REG = 165, CORR = 166, 
    SGPLOT = 167, PRINT = 168, DATA = 169, Informat = 170, DOLLAR = 171, 
    EQ = 172, NE = 173, GT = 174, LT = 175, GE = 176, LE = 177, IN = 178, 
    EQC = 179, NEC = 180, GTC = 181, LTC = 182, GEC = 183, LEC = 184, INColon = 185, 
    AND = 186, OR = 187, NOT = 188, MIN = 189, MAX = 190, DateLiteral = 191, 
    TimeLiteral = 192, DateTimeLiteral = 193, BitLiteral = 194, NameLiteral = 195, 
    HexLiteral = 196, STRINGLITERAL = 197, INT = 198, FloatingPointLiteral = 199, 
    Identifier = 200, DOT = 201, AT = 202, EQUAL = 203, COMMA = 204, LBracket = 205, 
    RBracket = 206, WS = 207, COMMENT = 208, LINE_COMMENT = 209, SEMICOLON = 210, 
    OF = 211, MissingValueLiteral = 212, COLON = 213, PERCENT = 214, ADD = 215, 
    SUB = 216, MUL = 217, DIV = 218, VERLINE = 219, EXCLAMATION = 220, LParentheses = 221, 
    RParentheses = 222, LBraces = 223, RBraces = 224, LSqBracket = 225, 
    RSqBracket = 226
  };

  explicit DapLexer(antlr4::CharStream *input);

  ~DapLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

