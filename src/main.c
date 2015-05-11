#include <stdio.h>

//program instructions
typedef enum {
  PSH,  //PSH X: Push X onto the stack.
  ADD,  //ADD: Pop top two numbers off of the stack, add them, push result.
  POP,  //POP: Pop and print top number off the stack.
  SET,  //SET X Y: Set register X to value Y.
  HLT   //HLT: Program over.
} InstructionSet;

const int test[] = {
  PSH, 5,
  PSH, 6,
  ADD,
  POP,
  HLT
};

//instruction pointer
int ip = 0;
//get instruction at instruction pointer
int fetch() { return test[ip]; }
//increment instruction pointer
void step() { ++ip; }

int main() {
  printf("Launching HWVM...\n");
  
  int instr = fetch();
  printf("%i\n", instr);

  step();
  instr = fetch();
  printf("%i\n", instr);

  return 0;
}
