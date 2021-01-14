#ifndef BYTECODE
#define BYTECODE

enum bytecode
{
  IADD = 1, // add ints
  ISUB = 2, // subtract ints
  IMUL = 3, // multiply ints
  ILT = 4, // int less than
  IEQ = 5, // int equal
  BR = 6, // branch
  BRT = 7, // branch if true
  BRF = 8, // branch if false
  ICONST = 9, // push constant int
  LOAD = 10, // load from local
  GLOAD = 11, // load from global
  STORE = 12, // store in local
  GSTORE = 13, // store in global
  PRINT = 14, // print stack top
  POP = 15, // pop stack top
  HALT = 16, // halt instruction
  CALL = 17,
  RET = 18 // return value or no value
};

#endif
