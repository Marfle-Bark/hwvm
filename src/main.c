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

typedef enum {
  A, B, C, D, E, F,
  NUM_OF_REGISTERS
} Registers;

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

void printInstruction(int instr) {
  printf("*Evaluating instruction ");
  switch(instr) {
    case 0:
      printf("PSH\n");
      break;
    case 1:
      printf("ADD\n");
      break;
    case 2:
      printf("POP\n");
      break;
    case 3:
      printf("SET\n");
      break;
    case 4:
      printf("HLT\n");
      break;
    default:
      printf("ERROR\n");
      break;
    }
}

//get instruction at instruction pointer
int fetch() { return test[ip]; }

//evaluate instruction
void eval(int instr) {
  
  printInstruction(instr);

  switch(instr) {

    case PSH: {
      stack[++sp] = test[++ip];
      printf("**Pushed %i\n", stack[sp]);
      break;
    }

    case ADD: {
      int a = stack[sp--];
      int b = stack[sp--];
      stack[++sp] = a + b;
      printf("**Added %i and %i to get %i.\n", a, b, stack[sp]);
      break;
    }

    case POP: {
      int val = stack[sp--];
      printf("**Popped %i\n", val);
      break;
    }

    case SET: {
      break;
    }

    case HLT: {
      running = false;
      printf("**Halting.\n");
      break;
    }

  }
}

int main() {
  printf("\n\n***Launching HWVM...\n\n\n");
  
  while (running) {
    eval(fetch());
    ip++;
  }

  printf("\n\n***Closing HWVM...\n\n\n");

  return 0;
}
