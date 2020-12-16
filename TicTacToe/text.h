#pragma once

struct TextBox
{
	TextBox() : Y(0), X(0) {}
	TextBox(uint8_t Y, uint8_t X) : Y(Y), X(X) {}

	void show(const char* const) const;
	void clear() const;

protected:
	uint8_t Y, X;
};

struct WarnBox : TextBox
{
	WarnBox(uint8_t Y, uint8_t X) : TextBox(Y, X) {}

	void show(const char* const) const;
};