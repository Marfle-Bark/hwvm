#include <stdio.h>
#include <stdbool.h>

#define rp (registers[RP])
#define ip (registers[IP])
#define sp (registers[SP])

//program instructions
typedef enum {
  PUSH,  //PUSH X: Push X onto the stack.
  ADD,  //ADD: Pop two numbers off of the stack, add them, put result in RP.
  POP,  //POP: Pop top number off the stack into RP.
  PEEK, //PEEK: Peek top number off the stack into RP.
  SET,  //SET X Y: Set register X to non-register value Y.
  HALT   //HALT: Program over.
} InstructionSet;

typedef enum {
  A, B, C, D, E, F,
  RP, //register pointer
  IP, //instruction pointer
  SP, //stack pointer
  NUM_OF_REGISTERS
} Registers;

int registers[NUM_OF_REGISTERS];

const int program[] = {
  SET, A, 5,
  PUSH, 5,
  PUSH, 6,
  SET, RP, B,
  ADD,
  PUSH, 1,
  PUSH, 2,
  SET, RP, C,
  PEEK,
  POP,
  HALT
};

bool running = true;  //"is the VM running?"

int stack[256]; //256-int stack

char* getInstruction(int instr) {
  switch(instr) {
    case PUSH:
      return "PUSH";
    case ADD:
      return "ADD";
    case POP:
      return "POP";
    case PEEK:
      return "PEEK";
    case SET:
      return "SET";
    case HALT:
      return "HALT";
    default:
      return "ERROR";
    }
}

char* getReg(int reg) {
  switch(reg) {
    case A:
      return "A";
    case B:
      return "B";
    case C:
      return "C";
    case D:
      return "D";
    case E:
      return "E";
    case F:
      return "F";
    case RP:
      return "RP";
    case IP:
      return "IP";
    case SP:
      return "SP";
    default:
      return "ERROR";
  }
}

void dumpRegisters() {
  printf("***Register Values:\n");
  int i;
  for(i = 0; i < NUM_OF_REGISTERS; i++)
    printf("%s: %i\n", getReg(i), registers[i]);
  printf("\n");
}

void dumpStack() {
  printf("***Stack trace:\n");
  while(sp > -1)
    printf("%i: %i\n", sp--, stack[sp]);
  printf("\n");
}

//evaluate instruction
void eval() {
  int instr = program[ip];
  printf("*Evaluating instruction %s...\n", getInstruction(instr));

  switch(instr) {

    case PUSH: {
      stack[++sp] = program[++ip];
      printf("**Pushed %i onto the stack.\n", stack[sp]);
      break;
    }

    case ADD: {
      int a = stack[sp--];
      int b = stack[sp--];
      registers[rp] = a + b;
      printf("**Added %i and %i to get %i.\n", a, b, registers[rp]);
      break;
    }

    case POP: {
      registers[rp] = stack[sp--];
      printf("**Popped %i onto register %s.\n", registers[rp], getReg(rp));
      break;
    }

    case PEEK: {
      registers[rp] = stack[sp];
      printf("**Peeked %i onto register %s.\n", registers[rp], getReg(rp));
      break;
    }

    case SET: {
      int reg = program[++ip];
      int val = program[++ip];
      registers[reg] = val;
      printf("**Loaded %i into register %s.\n", val, getReg(reg));
      break;
    }

    case HALT: {
      running = false;
      printf("**Halting.\n");
      break;
    }

  }
  ip++; //increment IP at end of eval()
}

void init() {
  printf("**Initializing registers...\n");
  registers[A] = 0;
  registers[B] = 0;
  registers[C] = 0;
  registers[D] = 0;
  registers[E] = 0;
  registers[F] = 0;
  rp = A;
  ip = 0;
  sp = -1;
}

int main() {
  printf("\n\n***Launching HWVM...\n\n\n");
  init();
  
  int cycles = 0;

  while (running) {
    eval();
    cycles++;
  }

  printf("\n\n***Closing HWVM...\n");
  printf("***VM ran for %i cycles.\n", cycles);
  dumpRegisters();
  dumpStack();

  return 0;
}
