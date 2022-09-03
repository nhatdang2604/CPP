//push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

//eq
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
D=M
M=0
@EQ_YES.0
D;JEQ
@EQ_DONE.0
0;JMP
(EQ_YES.0)
@SP
A=M-1
M=-1
@EQ_DONE.0
0;JMP
(EQ_DONE.0)

//push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1

//eq
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
D=M
M=0
@EQ_YES.1
D;JEQ
@EQ_DONE.1
0;JMP
(EQ_YES.1)
@SP
A=M-1
M=-1
@EQ_DONE.1
0;JMP
(EQ_DONE.1)

//push constant 16
@16
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 17
@17
D=A
@SP
A=M
M=D
@SP
M=M+1

//eq
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
D=M
M=0
@EQ_YES.2
D;JEQ
@EQ_DONE.2
0;JMP
(EQ_YES.2)
@SP
A=M-1
M=-1
@EQ_DONE.2
0;JMP
(EQ_DONE.2)

//push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

//lt
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
D=M
M=0
@LT_YES.3
D;JLT
@LT_DONE.3
0;JMP
(LT_YES.3)
@SP
A=M-1
M=-1
@LT_DONE.3
0;JMP
(LT_DONE.3)

//push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 892
@892
D=A
@SP
A=M
M=D
@SP
M=M+1

//lt
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
D=M
M=0
@LT_YES.4
D;JLT
@LT_DONE.4
0;JMP
(LT_YES.4)
@SP
A=M-1
M=-1
@LT_DONE.4
0;JMP
(LT_DONE.4)

//push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 891
@891
D=A
@SP
A=M
M=D
@SP
M=M+1

//lt
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
D=M
M=0
@LT_YES.5
D;JLT
@LT_DONE.5
0;JMP
(LT_YES.5)
@SP
A=M-1
M=-1
@LT_DONE.5
0;JMP
(LT_DONE.5)

//push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

//gt
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
D=M
M=0
@GT_YES.6
D;JGT
@GT_DONE.6
0;JMP
(GT_YES.6)
@SP
A=M-1
M=-1
@GT_DONE.6
0;JMP
(GT_DONE.6)

//push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 32767
@32767
D=A
@SP
A=M
M=D
@SP
M=M+1

//gt
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
D=M
M=0
@GT_YES.7
D;JGT
@GT_DONE.7
0;JMP
(GT_YES.7)
@SP
A=M-1
M=-1
@GT_DONE.7
0;JMP
(GT_DONE.7)

//push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 32766
@32766
D=A
@SP
A=M
M=D
@SP
M=M+1

//gt
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D
D=M
M=0
@GT_YES.8
D;JGT
@GT_DONE.8
0;JMP
(GT_YES.8)
@SP
A=M-1
M=-1
@GT_DONE.8
0;JMP
(GT_DONE.8)

//push constant 57
@57
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 31
@31
D=A
@SP
A=M
M=D
@SP
M=M+1

//push constant 53
@53
D=A
@SP
A=M
M=D
@SP
M=M+1

//add
@SP
M=M-1
A=M
D=M
A=A-1
M=M+D

//push constant 112
@112
D=A
@SP
A=M
M=D
@SP
M=M+1

//sub
@SP
M=M-1
A=M
D=M
A=A-1
M=M-D

//neg
@SP
A=M-1
M=-M

//and
@SP
M=M-1
A=M
D=M
A=A-1
M=M&D

//push constant 82
@82
D=A
@SP
A=M
M=D
@SP
M=M+1

//or
@SP
M=M-1
A=M
D=M
A=A-1
M=M|D

//not
@SP
A=M-1
M=!M

(END)
@END
0;JMP
