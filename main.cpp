#include <iostream>
#include "virtm.h"
#include "bytecode.h"

int main (int argc, char **argv)
{

  static int test[] =
  {
    ICONST, 99, // 0
    GSTORE, 0, // 2
    GLOAD, 0, // 4
    PRINT, // 5
    HALT // 7
  }; // test bytecodes


  static int loop[] =
  {
// .GLOBALS 2; N, I
// N = 10						ADDRESS
    ICONST, 10,				// 0
    GSTORE, 0,				// 2
// I = 0
    ICONST, 0,				// 4
    GSTORE, 1,				// 6
// WHILE I<N:
// START (8):
    GLOAD, 1,				// 8
    GLOAD, 0,				// 10
    ILT,					// 12
    BRF, 24,				// 13
//     I = I + 1
    GLOAD, 1,				// 15
    ICONST, 1,				// 17
    IADD,					// 19
    GSTORE, 1,				// 20
    BR, 8,					// 22
// DONE (24):
//PRINT "LOOPED "+N+" TIMES."
    HALT					// 24
  };

  int factorial_index = 1;
  int factorial_address = 0;

  static int factorial[] =
  {
    // IF N < 2 RETURN 1
    LOAD, -3,     // 0
    ICONST, 2,    // 2
    ILT,          // 4
    BRF, 10,      // 5
    ICONST, 1,    // 7
    RET,          // 9
    // RETURN N* FACTORIAL(N-1)
    LOAD, -3,     // 10
    LOAD, -3,     // 12
    ICONST, 1,    // 14
    ISUB,         // 16
    CALL, 0, 1,   // 17
    IMUL,         // 20
    RET,          // 21
    // PRINT FACTORIAL(10)
    ICONST, 5,    // 22
    CALL, 0, 1,   // 24
    PRINT,        // 27
    HALT          // 28
  };

  virtm vm;
  vm.virtm_init (test, 0, 1);
  vm.cpu ();
  vm.dump_mem ();
  vm.virtm_init (loop, 0, 3);
  vm.cpu ();
  vm.dump_mem ();
  vm.virtm_init (factorial, 0, 1);
  vm.cpu ();
  vm.dump_mem ();
}
