#include "dic/code_arm.h"

#include <string.h> // strcat
#include <stdlib.h> // strtoul
#include <stdio.h>




word ZeroExtend (Plgtab imm) {
	
	char imm_str[33] = {0};
	int i;



	for(i = 0; i < imm.size; i++)
		strcat(imm_str, int_to_bin(imm.plages[i].value, imm.plages[i].end - imm.plages[i].start));

	return strtoul(imm_str, NULL, 2);
}



int SignExtend (Plgtab imm) 
{
	uint u_imm=0, b=0;
	int prev_size=0, size=0;



	for (int i = imm.size -1; i >= 0; i--)
	{
		u_imm += imm.plages[i].value << prev_size;

		prev_size = imm.plages[i].end - imm.plages[i].start + 1;

		size += prev_size;
	}



	b = (1 << size) - 1;



	// printf("u_imm = %u\t b = %u\n", u_imm, b);

	if(u_imm > 1 << (size - 1))
		return -(u_imm ^ b);

	else
		return u_imm;
}



void BranchWritePC (vaddr32 adresse) {
	
	adresse = adresse & ~(1u << 0) ;
	PC = adresse;

	}


	
void BXWritePC (vaddr a) {

	BranchwritePC (a);

}


int SInt16 (int x ) {

	int result = 0;
	int i;
	for (i = 0; i<=15; i++) {
		if (x & (1u << i ) ){ 
			result = result + 2^i;
		}
	}
	if (x & (1u << 15) ) {
		result = result - 2^15;
	}
	return result;
}

long SInt32 (long x) {
	
	long result = 0;
	int i;
	for (i = 0; i<=31; i++) {
		if (x & (1u << i ) ){ 
			result = result + 2^i;
		}
	}
	if (x & (1u << 31) ) {
		result = result - 2^32;
	}
	return result;
}


int UInt16 (int x) {
	
	int result = 0;
	int i;
	for (i = 0 ; i<=15 ; i++) { 
		if (x & (1u << i)) {
			result = result + 2^i;
		}
	}
	return result;
}

long UInt32 (long x) {
	
	long result = 0;
	int i;
	for (i = 0 ; i<=31 ; i++) { 
		if (x & (1u << i) ){
			result = result + 2^i;
		}
	}
	return result;
}

unsigned long AddWithCarry (unsigned long registre , unsigned long imm32 , int* carry , int* overflow) {


	unsigned long unsigned_sum;
	long signed_sum;
	long result;
	long mask;
	mask = 0x0000FFFF;
	
	unsigned_sum = UInt32 (registre) + UInt32 (imm32) + UInt16 (*carry);
    	signed_sum   = SInt32 (registre) + SInt32 (imm32) + UInt16 (*carry);
    	result       = unsigned_sum & mask ;  // same value as signed_sum<N-1:0>
    	if (UInt32 (result) == unsigned_sum ) {
		*carry = 0; 
	}
	else {
		*carry = 1;
	}
    	if (SInt32 (result) == signed_sum ) {
		*overflow = 0;
	}	
	else {
		*overflow = 1;
	}
	return result;	


}
