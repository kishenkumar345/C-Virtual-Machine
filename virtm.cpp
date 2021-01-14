#include <iostream>
#include "virtm.h"
#include "bytecode.h"

#define TRUE 1
#define FALSE 0

void virtm::virtm_init (int *code, int inst_index, int d_size)
// *code is set of instructions
// inst_index is starting index of instructions array
// data_size is how much memory should be used
{
  code_mem = code;
  i_index = inst_index;
  s_index = -1;
  f_index = -1;
  data_size = d_size;
  data_mem = new int[data_size];
  stack = new int[200];
  global = new int[100];
}

void virtm::cpu ()
{

  int opcode = 0;
  int a = 0, v = 0, address = 0, offset = 0, args = 0, val = 0;

  while (opcode != HALT)
  {
    opcode = code_mem[i_index];

    std::cout << i_index << " " << opcode;
    i_index++;

    switch (opcode)
    {
      case IADD:
      v = stack[s_index];
      s_index--;
      a = stack[s_index];
      s_index--;
      s_index++;
      stack[s_index] = a + v;
      std::cout << " IADD" << std::endl;
      break;

      case ISUB:
      v = stack[s_index];
      s_index--;
      a = stack[s_index];
      s_index--;
      s_index++;
      stack[s_index] = a - v;
      std::cout << " ISUB" << std::endl;
      break;

      case IMUL:
      v = stack[s_index];
      s_index--;
      a = stack[s_index];
      s_index--;
      s_index++;
      stack[s_index] = a * v;
      std::cout << " IMUL" << std::endl;
      break;

      case ILT:
      v = stack[s_index];
      s_index--;
      a = stack[s_index];
      s_index--;
      s_index++;
      if (a < v)
      {
        stack[s_index] = TRUE;
      }
      else
      {
        stack[s_index] = FALSE;
      }
      std::cout << " ILT" << std::endl;
      break;

      case IEQ:
      v = stack[s_index];
      s_index--;
      a = stack[s_index];
      s_index--;
      s_index++;
      if (a == v)
      {
        stack[s_index] = TRUE;
      }
      else
      {
        stack[s_index] = FALSE;
      }
      std::cout << " IEQ" << std::endl;
      break;

      case BR:
      i_index = code_mem[i_index];
      std::cout << " BR" << std::endl;
      break;

      case BRT:
      address = code_mem[i_index];
      i_index++;
      if (stack[s_index--] == TRUE)
      {
        i_index = address;
      }
      std::cout << " BRT" << std::endl;
      break;

      case BRF:
      address = code_mem[i_index];
      i_index++;
      if(stack[s_index--] == FALSE)
      {
        i_index = address;
      }
      std::cout << " BRF" << std::endl;
      break;

      case ICONST:
      v = code_mem[i_index];
      i_index++;
      s_index++; // increase stack set by 1
      stack[s_index] = v; // get instruction out of code memory
      std::cout << " ICONST" << std::endl;
      break;

      case LOAD:
      offset = code_mem[i_index]; // offset is equal to instruction in code memory
      i_index++;
      s_index++;
      stack[s_index] = stack[f_index + offset]; // push into current position of stack, frame index plus the offset, then increment
      std::cout << " LOAD" << std::endl;
      break;

      case GLOAD:
      address = code_mem[i_index]; // get instruction out of code memory
      i_index++; // increase instruction set by 1
      v = global[address]; // make value equal value at address in global memory
      s_index++; // increase stack by 1
      stack[s_index] = v; // push onto stack the global variable
      std::cout << " GLOAD" << std::endl;
      break;

      case STORE:
      offset = code_mem[i_index]; // frame index equals index of local variable on stack
      i_index++;
      stack[f_index + offset] = stack[s_index];
      s_index--;
      std::cout << " STORE" << std::endl;
      break;

      case GSTORE:
      v = stack[s_index]; // get top of stack
      s_index--; // decrease stack by 1
      address = code_mem[i_index]; // get instruction from code memory as address
      i_index++; // increase instruction set by 1
      global[address] = v; // push into global memory at address, the stack value
      std::cout << " GSTORE" << std::endl;
      break;

      case PRINT:
      v = stack[s_index]; // get top of the stack
      s_index--; // decrease stack by 1
      std::cout << "\n" << v; // print the top of the stack
      std::cout << " PRINT" << std::endl;
      break;

      case POP:
      --s_index;
      std::cout << " POP" << std::endl;
      break;

      case HALT:
      return;

      case CALL:
      address = code_mem[i_index]; // get address of function
      i_index++;
      args = code_mem[i_index]; // get number of arguments in function
      i_index++;
      s_index++;
      stack[s_index] = args; // add to stack number of arguments in function
      s_index++;
      stack[s_index] = f_index; // add to stack frame index
      s_index++;
      stack[s_index] = i_index; // add to stack return address
      f_index = s_index; // frame index equals return address
      i_index = address; // instruction index equals to function address.
      std::cout << " CALL" << std::endl;
      break;

      case RET:
      val = stack[s_index];
      s_index--;
      s_index = f_index;
      i_index = stack[s_index];
      s_index--;
      f_index = stack[s_index];
      s_index--;
      args = stack[s_index];
      s_index--;
      s_index = s_index - args;
      s_index++;
      stack[s_index] = val;
      std::cout << " RET" << std::endl;
      break;

      default:
      std::cerr << " Wrong Opcode" << std::endl;
      return;
    }

  }

}

void virtm::dump_mem ()
{
  std::cout << " Data Memory: \n";

  for (int gs = 0; gs < data_size; gs++)
  {
    std::cout << gs << " " << global[gs] << std::endl;
  }

  data_mem = NULL;
  stack = NULL;
  global = NULL;

  delete [] data_mem;
  delete [] stack;
  delete [] global;

  std::cout << "Memory Freed\n" << std::endl;
}
