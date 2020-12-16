#include "terminal_control.h"
#include "text.h"

void TextBox::show(const char* const text) const
{
	GOTO_R(Y, X);
	std::cout << CLEAR_LN() << text;
}

void TextBox::clear() const
{
	GOTO_R(Y, X);
	std::cout << CLEAR_LN();
}

void WarnBox::show(const char* const text) const
{
	GOTO_R(Y, X);
	std::cout << CLEAR_LN() << FG_RED() << text << CLEAR_FORMAT();
}