#include "mat2.h"

float mat2::determinate()
{
	return (m[0] * m[3]) - (m[1] * m[2]);
}
