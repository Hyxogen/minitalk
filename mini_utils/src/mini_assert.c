#include "mini_assert.h"
#include <stdlib.h>

void mini_assert(ft_bool assertion) {
	if (!assertion)
		exit(EXIT_FAILURE);
}

