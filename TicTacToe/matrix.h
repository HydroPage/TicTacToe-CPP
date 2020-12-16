#pragma once

template<typename T>
struct Matrix
{
	virtual T operator()(uint8_t, uint8_t) const = 0;
};