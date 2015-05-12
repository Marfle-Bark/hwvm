#include <stdio.h>
#include <stdbool.h>

#define rp (registers[RP])
#define ip (registers[IP])
#define sp (registers[SP])

//program instructions
typedef enum {
  PSH,  //PSH X: Push X onto the stack.
  ADD,  //ADD: Pop two numbers off of the stack, add them, put result in RP.
  POP,  //POP: Pop top number off the stack into RP.
  PEEK, //PEEK: Peek top number off the stack into RP.
  SET,  //SET X Y: Set register X to non-register value Y.
  HLT   //HLT: Program over.
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
  PSH, 5,
  PSH, 6,
  ADD,
  PEEK,
  SET, A, 5,
  SET, RP, B,
  POP,
  HLT
};

bool running = true;  //"is the VM running?"

int stack[256]; //256-int stack

char* getInstruction(int instr) {
  switch(instr) {
    case PSH:
      return "PSH";
    case ADD:
      return "ADD";
    case POP:
      return "POP";
    case PEEK:
      return "PEEK";
    case SET:
      return "SET";
    case HLT:
      return "HLT";
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

//get instruction at instruction pointer
int fetch() { return program[ip]; }

//evaluate instruction
void eval(int instr) {
  
  printf("*Evaluating instruction %s...\n", getInstruction(instr));

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
      registers[rp] = stack[sp--];
      break;
    }

    case PEEK: {
      printf("**Peeked %i\n", stack[sp-1]);
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
    eval(fetch());
    ip++;
    cycles++;
  }

  printf("\n\n***Closing HWVM...\n");
  printf("***VM ran for %i cycles.\n", cycles);
  dumpRegisters();
  dumpStack();

  return 0;
}
