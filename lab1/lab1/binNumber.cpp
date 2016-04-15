#include "binNumber.h"

binNumber::binNumber( short int posSign,  short int posOerder,  short int posMantissa)
{
	sign = posSign;
	order = posOerder;
	mantissa = posMantissa;
}

binNumber::binNumber()
{
	sign = order = mantissa = 0;
}
