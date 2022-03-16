#include <stdio.h>

void printBits(unsigned num, unsigned size)
{
    if (size>0) printBits(num >> 1, --size);
    printf("%i ", num & 0x01);
}

void main()
{
   unsigned a = 123; //111 1011
   unsigned b = 87;  //101 0111 

   printf("\nBitwise AND (\"&\") "); 
   printBits(a & b,sizeof(unsigned)*8);
   printf("\nBitwise OR (\"|\") ");
   printBits( a | b,sizeof(unsigned)*8);
   printf("\nBitwise XOR (\"^\") ");
   printBits( a ^ b,sizeof(unsigned)*8);
   printf("\nBitwise Complement (\"~\") ");
   printBits(~a,sizeof(unsigned)*8);
   printf("\nBitwise Left Shift (\"<<\") ");
   printBits(a << 4,sizeof(unsigned)*8);
   printf("\nBitwise Right Shift (\">>\") ");
   printBits(a >> 4,sizeof(unsigned)*8);
}