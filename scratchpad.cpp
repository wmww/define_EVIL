#include "macro_utils.h"

int main()
{
	EXPAND_TO_STRING(CHECK_IF_THING(9))
	EXPAND_TO_STRING(CHECK_IF_THING())
	CHECK_IF_THING(9)
	CHECK_IF_THING()
	return 0;
}
