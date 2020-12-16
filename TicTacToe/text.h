#pragma once

#include <Windows.h>

struct TextBox
{
	TextBox();
	TextBox(uint8_t Y, uint8_t X);

	virtual void show(const char* const) const;
	void clear() const;

private:
	uint8_t Y, X;
};