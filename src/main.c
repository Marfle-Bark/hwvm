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

//"is the VM running?"
bool running = true;

//instruction pointer
int ip = 0;

//get instruction at instruction pointer
int fetch() { return test[ip]; }

//increment instruction pointer
void step() { ++ip; }

//decrement instruction pointer
void back() { --ip; }

//jump ip to position in code
void jump(int position) { ip = position; }

//evaluate instruction
void eval(int instr) {
  printf("Evaluating %i\n", instr);
  switch(instr) {
    case PSH:
      step();
      break;
    case ADD:
      break;
    case POP:
      break;
    case SET:
      break;
    case HLT:
      running = false;
      break;
  }
}

int main() {
  printf("Launching HWVM...\n");
  
  while (running) {
    eval(fetch());
    step();
  }

  return 0;
}
