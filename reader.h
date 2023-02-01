#ifndef _READER_H_
#define _READER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CPUMAXCORE 10
#define STATMAXNUMBERS 10

struct datas
{
	int cpuCount;
	int numberCount;
	int numbers[STATMAXNUMBERS][CPUMAXCORE];
};

//analyzer:
#include <unistd.h>


#endif
