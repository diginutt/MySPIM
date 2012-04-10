#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
	unsigned Z;
	switch(ALUControl) {
	case 0x0:
		Z = A + B;
		break;
	case 0x1:
		Z = A - B;
		break;
	case 0x2:
		if (A < B)
			Z = 0x1;
		else
			Z = 0x0;
		break;
	case 0x3:
		if (A < B)
			Z = 0x1;
		else
			Z = 0x0;
		break;
	case 0x4:
		Z = A & B;
		break;
	case 0x5:
		Z = A | B;
		break;
	case 0x6:
		B = B << 16;
		break;
	case 0x7:
		// Add code to decode R-type instructions based on the funct value
		Z = ~A;
		break;
	}
	*ALUresult = Z;
	if (Z == 0x0)
		*Zero = 0x1;
	else
		*Zero = 0x0;
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	return 0;
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	//Set up bit masks to decode the instruction into the various parts
	unsigned opMask = 0x7e000000; // instruction [31-26]
	unsigned r1Mask = 0x1f000000; // instruction [25-21]
	unsigned r2Mask = 0x000f8000; // instruction [20-16]
	unsigned r3Mask = 0x00007c00; // instruction [15-11]
	unsigned functMask = 0x0000003f; // instruction [5-0]
	unsigned offsetMask = 0x0000ffff; // instruction [15-0]
	unsigned jsecMask = 0x01ffffff; // instruction [25-0]

	//Bit mask the instruction into the various parts
	*op = instruction & opMask;
	*r1 = instruction & r1Mask;
	*r2 = instruction & r2Mask;
	*r3 = instruction & r3Mask;
	*funct = instruction & functMask;
	*offset = instruction & offsetMask;
	*jsec = instruction & jsecMask;
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	switch(op) {
	case 0x0:  // add, sub, and, or, slt, sltu
		//These are all R type instructions
		*controls->MemRead = 0x0;
		*controls->MemWrite = 0x0;
		*controls->RegWrite = 0x0;
		*controls->RegDst = 0x1;
		*controls->Jump = 0x0;
		*controls->Branch = 0x0;
		*controls->MemtoReg = 0x0;
		*controls->ALUSrc = 0x0;
		*controls->ALUOp = 0x7;
		break;
	case 0x8: // addi
		// I type instruction
		*controls->MemRead = 0x0;
		*controls->MemWrite = 0x0;
		*controls->RegWrite = 0x0;
		*controls->RegDst = 0x0;
		*controls->Jump = 0x0;
		*controls->Branch = 0x0;
		*controls->MemtoReg = 0x0;
		*controls->ALUSrc = 0x1;
		*controls->ALUOp = 0x0;
		break;
	case 0x23: // lw
		// I type instruction
		*controls->MemRead = 0x1;
		*controls->MemWrite = 0x0;
		*controls->RegWrite = 0x1;
		*controls->RegDst = 0x0;
		*controls->Jump = 0x0;
		*controls->Branch = 0x0;
		*controls->MemtoReg = 0x1;
		*controls->ALUSrc = 0x1;
		*controls->ALUOp = 0x0;
		break;
	case 0x2b: // sw
		// I type instruction
		*controls->MemRead = 0x0;
		*controls->MemWrite = 0x1;
		*controls->RegWrite = 0x0;
		*controls->RegDst = 0x0;
		*controls->Jump = 0x0;
		*controls->Branch = 0x0;
		*controls->MemtoReg = 0x0;
		*controls->ALUSrc = 0x1;
		*controls->ALUOp = 0x0;
		break;
	case 0xf:  // lui
		// I type instruction
		*controls->MemRead = 0x1;
		*controls->MemWrite = 0x0;
		*controls->RegWrite = 0x1;
		*controls->RegDst = 0x0;
		*controls->Jump = 0x0;
		*controls->Branch = 0x0;
		*controls->MemtoReg = 0x0;
		*controls->ALUSrc = 0x1;
		*controls->ALUOp = 0x6;
		break;
	case 0x4:  // beq
		// I type instruction
		*controls->MemRead = 0x0;
		*controls->MemWrite = 0x0;
		*controls->RegWrite = 0x0;
		*controls->RegDst = 0x0;
		*controls->Jump = 0x0;
		*controls->Branch = 0x1;
		*controls->MemtoReg = 0x0;
		*controls->ALUSrc = 0x1;
		*controls->ALUOp = 0x0;
		break;
	case 0xa:  // slti
		// I type instruction
		*controls->MemRead = 0x0;
		*controls->MemWrite = 0x0;
		*controls->RegWrite = 0x0;
		*controls->RegDst = 0x0;
		*controls->Jump = 0x0;
		*controls->Branch = 0x1;
		*controls->MemtoReg = 0x0;
		*controls->ALUSrc = 0x1;
		*controls->ALUOp = 0x0;
		break;
	case 0xb:  // sltu
		// I type instruction
		*controls->MemRead = 0x0;
		*controls->MemWrite = 0x0;
		*controls->RegWrite = 0x0;
		*controls->RegDst = 0x0;
		*controls->Jump = 0x0;
		*controls->Branch = 0x1;
		*controls->MemtoReg = 0x0;
		*controls->ALUSrc = 0x1;
		*controls->ALUOp = 0x0;
		break;
	case 0x2:  // j
		// J type instruction
		*controls->MemRead = 0x0;
		*controls->MemWrite = 0x0;
		*controls->RegWrite = 0x0;
		*controls->RegDst = 0x0;
		*controls->Jump = 0x1;
		*controls->Branch = 0x0;
		*controls->MemtoReg = 0x0;
		*controls->ALUSrc = 0x0;
		*controls->ALUOp = 0x0;
		break;
	default:
		return 1;
	}
	return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
	return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

