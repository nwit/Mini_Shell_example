
#include <stdio.h>
#include <stdlib.h>

#include "memory.h"


void *eipa_malloc(size_t size, const int line, const char *file) {
	void *ptr = malloc(size);
	if( ptr == NULL ) {
		fprintf(stderr, "[%d@%s][ERROR] can't malloc %zu bytes\n",
			       	line, file, size);
	}
	return ptr;
}


void eipa_free(void **ptr, const int line, const char *file) {
	(void)line;
	(void)file;	
	free(*ptr);
	*ptr = NULL;
}
