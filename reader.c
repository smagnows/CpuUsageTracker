#include <stdio.h>
#include "reader.h"
#include "printError.h"


FILE* cpuUsageFileCreate(void)
{
	FILE *cpuUsage;
        cpuUsage = fopen ("/proc/stat", "r");
        if(!cpuUsage)
        {
                fprintf(stderr,"fopen\n");
                exit(10);
        }
	return cpuUsage;
}


int cpuUsageFileClose(FILE* file)
{
        return fclose(file);
}

void getCpuNumberCount(FILE *proc, int* cpuCount, int* numberCount)
{
	int cPcount=0, nUcount=0;
	char temp[128];
	rewind(proc);
	char* t;
	fgets(temp,120,proc);
	t = strtok (temp, " ");
        t = strtok(NULL, " ");
        //for(int j=0;j<cpuCount;++j)
        for(int i=0;t != NULL;++i)
                {
                        t = strtok(NULL," ");
                        ++nUcount;
                }
//        printf("Count: %d\n",count);
	(*numberCount) = nUcount;
	do
	{
		fgets(temp,120,proc);
		//printf("DEBUG: %s\n",temp);
		if(temp[0]!='c') break;
		++cPcount;
	} while(1);
	rewind(proc);
	(*cpuCount)=cPcount;
	return;
}



int saveToStruct(char *data, struct datas *str, short cpuCount)
{
	char *temp;
	int count=0;
	temp = strtok (data, " ");
	temp = strtok(NULL, " ");
	//for(int j=0;j<cpuCount;++j)
	{
		for(int i=0;temp != NULL;++i)
		{
			//str->number++=atoi();
		//	printf("%s\n",temp);
			str->numbers[i][cpuCount] = atoi(temp);
			temp = strtok(NULL," ");
			++count;
		}
	}
//	printf("Count: %d\n",count);
	return count;
}

struct datas *readData(int *cpuCounts, int*numberCounts)
{
	FILE* cpuUsage;
	//printf("CpuUsageDatas1\n");
	cpuUsage = cpuUsageFileCreate();
	//printf("CpuUsageDatas2\n");
	struct datas *temp = malloc(sizeof(struct datas));
	if((*cpuCounts)<0) getCpuNumberCount(cpuUsage,cpuCounts,numberCounts);
	temp->cpuCount = *cpuCounts;
	temp->numberCount = *numberCounts;
	//printf("\nCPUCPUCOUNT: %d\n",temp->cpuCount);
	char dataFromFile[121];
	fgets(dataFromFile,120,cpuUsage);
	int numberCount = temp->numberCount;
	int cpuCount = temp->cpuCount;
	for(int i=0;(i<cpuCount)&&(!feof(cpuUsage));++i)
	{
		fgets(dataFromFile,120,cpuUsage);
		//printf("%s\n", dataFromFile);
		saveToStruct(dataFromFile, temp, i);
	}
	cpuUsageFileClose(cpuUsage);
	return temp;
}

void readStruct(struct datas *st)
{
	int cpuCount = st->cpuCount;
	int numberCount = st->numberCount;
//	printf("DEBUG\n");
/*                for(int i=0;i<cpuCount;++i)
                        for(int j=0;j<numberCount;++j)
                                printf("CPU: %d, NUMBER: %d: %d\n",i,j,st->numbers[j][i]);*/
}

void analyze(struct datas *st, struct datas *st2)
{
	if((st->numberCount)<8) return;
	double totald[st->cpuCount];
	double idled[st->cpuCount];
	double cpuPercentage[st->cpuCount];
	for(int i=0;i<st->cpuCount;++i)
	/*
	 *      user    	nice   		system  	idle      	iowait 		irq   		softirq  	steal  		guest  		guest_nice
	 *  cpu numbers[0][i]   numbers[1][i]   numbers[2][i]	numbers[3][i]	numbers[4][i]	numbers[5][i]	numbers[6][i]	numbers[7][i]	numbers[8][i]	numbers[9][i]
	 */
		{
			totald[i] = (double) st2->numbers[3][i]+ st2->numbers[4][i] + st2->numbers[0][i]+ st2->numbers[1][i] + st2->numbers[2][i]+ st2->numbers[5][i]+ st2->numbers[6][i] + st2->numbers[7][i] - (st->numbers[3][i] + st->numbers[4][i] + st->numbers[0][i]+ st->numbers[1][i] + st->numbers[2][i]+ st->numbers[5][i]+ st->numbers[6][i] + st->numbers[7][i]);
			idled[i] = (double)st2->numbers[3][i]+ st2->numbers[4][i] - (st->numbers[3][i] + st->numbers[4][i]);
			cpuPercentage[i] = (totald[i] - idled[i])/totald[i];
			printf("CPU %d: %.2f%%\t\t",i,100.0*cpuPercentage[i]);
		}
		printf("\n");
		return;

//			st->numbers[0][i]+=st->numbers[j][i];
}

int main()
{
	//printf("Main1\n");
	int cpuCount = -1;
	int numberCount=-1;
	struct datas *struktura = readData(&cpuCount,&numberCount);
	struct datas *struktura2;
	//sleep (1);
	//struktura2=readData();
	//readStruct(struktura);
	int i=0;
	do{
		sleep(2);
		struktura2=readData(&cpuCount,&numberCount);
		analyze(struktura,struktura2);
		free(struktura);
		struktura=struktura2;
		++i;
	}while(i<10);
	//readStruct(struktura);
	free(struktura);

	//printf("Main2\n");
	return 0;
}
