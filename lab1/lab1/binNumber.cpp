#include "binNumber.h"

binNumber::binNumber(unsigned short int posSign, unsigned short int posOerder, unsigned short int posMantissa)
{
	sign = posSign;
	order = posOerder;
	mantissa = posMantissa;
}

binNumber::binNumber()
{
	sign = order = mantissa = 0;
}
