#include <iostream>
#include <string>

void GOTO_R(uint8_t Y, uint8_t X)
{
	printf("\033[%d;%dH", Y, X);
}

void FORWARD_R(uint8_t spaces)
{
	printf("\033[%dC", spaces);
}

void BACKWARD_R(uint8_t spaces)
{
	printf("\033[%dD", spaces);
}