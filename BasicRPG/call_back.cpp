#include <stdio.h>

// Basic error call-back function for GLFW
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}