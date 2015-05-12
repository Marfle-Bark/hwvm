#include <stdio.h>
#include <stdbool.h>

#define ip (registers[IP])
#define sp (registers[SP])

//program instructions
typedef enum {
  PSH,  //PSH X: Push X onto the stack.
  ADD,  //ADD: Pop top two numbers off of the stack, add them, push result.
  POP,  //POP: Pop and print top number off the stack.
  SET,  //SET X Y: Set register X to value Y.
  HLT   //HLT: Program over.
} InstructionSet;

typedef enum {
  A, B, C, D, E, F, IP, SP,
  NUM_OF_REGISTERS
} Registers;

int registers[NUM_OF_REGISTERS];

const int program[] = {
  PSH, 5,
  PSH, 6,
  ADD,
  POP,
  SET, A, 5,
  HLT
};

bool running = true;  //"is the VM running?"

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

char* getReg(int reg) {
  switch(reg) {
    case 0:
      return "A";
      break;
    case 1:
      return "B";
      break;
    case 2:
      return "C";
      break;
    case 3:
      return "D";
      break;
    case 4:
      return "E";
      break;
    case 5:
      return "F";
      break;
    case 6:
      return "IP";
      break;
    case 7:
      return "SP";
      break;
    default:
      return "ERROR";
      break;
  }
}

//get instruction at instruction pointer
int fetch() { return program[ip]; }

//evaluate instruction
void eval(int instr) {
  
  printInstruction(instr);

  switch(instr) {

    case PSH: {
      stack[++sp] = program[++ip];
      printf("**Pushed %i\n", stack[sp]);
      break;
    }

    case ADD: {
      int a = stack[sp--];
      int b = stack[sp--];
      stack[++sp] = a + b;
      printf("**Added %i and %i to get %c.\n", a, b, stack[sp]);
      break;
    }

    case POP: {
      int val = stack[sp--];
      printf("**Popped %i\n", val);
      break;
    }

    case SET: {
      int reg = program[++ip];
      int val = program[++ip];
      registers[reg] = val;
      printf("**Loaded %i into register %s.\n", val, getReg(reg));
      break;
    }

    case HLT: {
      running = false;
      printf("**Halting.\n");
      break;
    }

  }
}

void init() {
  printf("**Initializing pointers...\n");
  ip = 0;
  sp = -1;
}

int main() {
  printf("\n\n***Launching HWVM...\n\n\n");
  init();
  
  int cycle = 0;

  while (running) {
    eval(fetch());
    ip++;
    cycle++;
  }

  printf("\n\n***Closing HWVM...\n\n\n");
  printf("\n***VM ran for %i cycles.\n", cycle);

  return 0;
}
