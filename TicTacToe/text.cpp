#include "terminal_control.h"
#include "text.h"

TextBox::TextBox() : Y(0), X(0) {}
TextBox::TextBox(uint8_t Y, uint8_t X) : Y(Y), X(X) {}

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