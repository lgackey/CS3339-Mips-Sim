# ================================
# MIPS Full Instruction Test File
# ================================

main:

# --- Basic arithmetic ---
#ADDI $a, $0, 10       # this should throw an error as $a is not a proper register
NOP
ADDI $2, $0, 20
ADD  $3, $1, $2       # 10 + 20 = 30
SUB  $4, $2, $1       # 20 - 10 = 10
MUL  $5, $1, $2       # 10 * 20 = 200

# --- Logic operations ---
AND  $6, $1, $2
OR   $7, $1, $2

# --- Shift tests ---
ADDI $8,  $0, 5
ADDI $9,  $0, 15
SLL  $10, $8, 2       # 5 << 2 = 20
SRL  $11, $9, 1       # 15 >> 1 = 7

# --- More ALU mixing ---
ADD  $12, $3,  $4
SUB  $13, $5,  $6
MUL  $14, $7,  $8
AND  $15, $9,  $10
OR   $16, $11, $12

# --- Load/Store ---
ADDI $17, $0, 100
SW   $17, 0($0)
LW   $18, 0($0)

# ================================
# Branch tests (control hazards)
# ================================

# If $1 == 10, branch should be taken
BEQ $1, $1, branch_taken
ADDI $19, $0, 999     # SHOULD NOT EXECUTE

branch_taken:
ADDI $19, $0, 42      # Should become 42

# ================================
# Jump test and NOP test
# ================================
ADDI $21, $0, 5
J jump_target
ADDI $21, $0, 999     # Should be skipped

jump_target:
NOP
ADDI $21, $21, 10     # 5 + 10 = 15

# ================================
# Memory addressing tests
# ================================
#ADDI $22, $0, 200
#ADDI $23, $0, 4
#SW   $22, 4($23)
#LW   $24, 4($23)

# ================================
# Small pipeline hazard test
# (Load-use hazard)
# ================================
ADDI $25, $0, 50
SW   $25, 8($0)
LW   $26, 8($0)
ADD  $27, $26, $1     # Dependent on LW

# ================================
# End of program
# ================================