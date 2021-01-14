#ifndef VIRTM_H
#define VIRTM_H

class virtm
{
public:
  int *code_mem = NULL; // code memory
  int *data_mem = NULL; // data memory
  int *stack = NULL; // stack
  int *global = NULL;
  int data_size = 0;

  int i_index; // instruction index
  int s_index; // stack index
  int f_index; // frame index

  virtm () {};
  void virtm_init (int*, int, int);
  void cpu ();
  void dump_mem ();
};

#endif
