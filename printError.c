#include "printError.h"

void displayErrorMessage(int code)
{
	char exceptionDescription [][100] =
	{
		"","",""
	};
	fprintf(stderr,"%s\n",exceptionDescription[-code-1]);
	return;
}
