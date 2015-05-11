#include <stdio.h>
#include <stdbool.h>

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

bool running = true;  //"is the VM running?"

int ip = 0;     //instruction pointer
int sp = -1;    //stack pointer
int stack[256]; //256-int stack

//get instruction at instruction pointer
int fetch() { return test[ip]; }

//evaluate instruction
void eval(int instr) {
  printf("*Evaluating %i\n", instr);
  switch(instr) {
    case PSH:
      ip++;
      sp++;
      stack[sp] = test[ip];
      printf("**Pushed %i\n", stack[sp]);
      break;
    case ADD:
      break;
    case POP:
      break;
    case SET:
      break;
    case HLT:
      running = false;
      printf("***Halting.");
      break;
  }
}

int main() {
  printf("***Launching HWVM...\n");
  
  while (running) {
    eval(fetch());
    ip++;
  }

  return 0;
}
