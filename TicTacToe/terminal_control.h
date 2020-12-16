#pragma once

#include <iostream>

#define const_term_expr constexpr const char*

#define COMMAND(code) "\033[" ## #code 
#define GOTO(Y,X) std::cout << COMMAND(Y ## ; ## X ## H)
#define FORWARD(spaces) std::cout << COMMAND(spaces ## C)
#define UP(spaces) std::cout << COMMAND(spaces ## A)
#define BACKWARD(spaces) std::cout << COMMAND(spaces ## D)
#define FORMAT(code) COMMAND(code ## m)

#define CYAN(in) FORMAT(36) in FORMAT(0)
#define RED(in)  FORMAT(31) in FORMAT(0)

void GOTO_R(uint8_t Y, uint8_t X);
void FORWARD_R(uint8_t spaces);
void BACKWARD_R(uint8_t spaces);

const_term_expr CLEAR_FORMAT()
{
	return FORMAT(0);
}

const_term_expr BOLD()
{
	return FORMAT(1);
}

const_term_expr FG_BLACK()
{
	return FORMAT(30);
}

const_term_expr FG_WHITE()
{
	return FORMAT(97);
}

const_term_expr BG_BLACK()
{
	return FORMAT(40);
}

const_term_expr BG_WHITE()
{
	return FORMAT(107);
}

const_term_expr BG_RED()
{
	return FORMAT(41);
}

const_term_expr BG_CYAN()
{
	return FORMAT(46);
}

const_term_expr CLEAR_LN()
{
	return COMMAND(K);
}