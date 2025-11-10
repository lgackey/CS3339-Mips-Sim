# CS3339-Mips-Sim
Repository for MIPS x86 Simulator.

Final Project for CS 3339 @ TXST

## Team Members
- Joshua Egwaikhide
- Daniel Kuchar
- Logan Magaha
- Aarush Nepali

## Description
This project is designed to interpret and simulate MIPS x86 instructions through a pipelined MIPS processor.

### Supported Instructions:

| Opcode | Description                |
|--------|----------------------------|
| ADD    | signed integer addition    |
| ADDI   | add immediate              |
| SUB    | signed integer subtraction |
| MUL    | integer multiplication     |
| AND    | bitwise and operation      |
| OR     | bitwise or operaton        |
| SLL    | shift left logical         |
| SRL    | shift right logical        |
| LW     | load word                  |
| SW     | store word                 |
| BEQ    | branch if equal to         |
| J      | jump                       |
| NOP    | no op                      |

## Compilation Instructions
A pre-compiled binary is not available. To compile, use the included makefile.
```
make mips_sim
./mips_sim
```

