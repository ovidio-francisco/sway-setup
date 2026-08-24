#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include "sysusage.h"


/* Compile with  */
/* gcc cpu-usage.c -lm -o cpu-usage */


CpuTimes getCpuTimes(void) {
    CpuTimes c = {0};

    FILE *fp = fopen("/proc/stat", "r");

    if (fp == NULL) {
        perror("/proc/stat");
        return c;
    }

    fscanf(fp,
           "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
           &c.user,
           &c.nice,
           &c.system,
           &c.idle,
           &c.iowait,
           &c.irq,
           &c.softirq,
           &c.steal);

    fclose(fp);

    return c;
}

float cpuUsage(CpuTimes a, CpuTimes b) {
    unsigned long long idleA = a.idle + a.iowait;
    unsigned long long idleB = b.idle + b.iowait;

    unsigned long long totalA =
        a.user + a.nice + a.system +
        a.idle + a.iowait +
        a.irq + a.softirq + a.steal;

    unsigned long long totalB =
        b.user + b.nice + b.system +
        b.idle + b.iowait +
        b.irq + b.softirq + b.steal;

    unsigned long long totalDiff = totalB - totalA;
    unsigned long long idleDiff  = idleB - idleA;

    if (totalDiff == 0)
        return 0.0f;

    return 100.0f *
           (totalDiff - idleDiff) /
           totalDiff;
}



const char* usageToBar(float usage) {

	float g = usage/(100.0/BAR_LEVELS);
	int i = (int)g; 

	return barSymbols[i];
}


int usageColorIndex(float usage){

	float g = usage/(100.0/N_CL);
	int i = (int)g; 

	return i;
}





void printIcon(float u) {
	
	const char* icon;

	if (u<80)
		icon = ICON_BRAIN;
	else if (u<90)
		icon = ICON_SKULL3;
	else if (u<95)	
		icon = ICON_FIRE1;
	else	
		icon = ICON_FIRE1;


	int ci = usageColorIndex(u);


	printf("<span color='%s'>%s</span>", redscale[ci], icon);
}

void printPercent(float u) {
	if (u < 1)
		printf(MSG_PERCENT_ZERO);
	else if (u < 10) 
		printf(MSG_PERCENT_LESS_THAN_10, u);
	else if (u < 100)
		printf(MSG_PERCENT_LESS_THAN_100, u);
	else
		printf(MSG_PERCENT_100, u);
}

void printBar(float u) {
	int ci = usageColorIndex(u);
	const char* bar = usageToBar(u);
	const char* barColor = redscale[ci];

	if (u < 1)
		printf(MSG_BAR_ZERO);
	else 
		printf(MSG_BAR_GREATER_THAN_0,barColor,bar);
}


int main(int argc, char *argv[]) {

	int si = SHOW_ICON;
	int sp = SHOW_PERCENT;
	int sb = SHOW_BAR;


	if(argc>1) {
		int i = 0;
		char c;
		while((c = argv[1][i++]))
			if (c=='i') si = 1; else
			if (c=='n') si = 0; else
			if (c=='p') sp = 1; else
			if (c=='b') sb = 1; 
	}


	CpuTimes previous = getCpuTimes();

	while(1) {

		sleep(1);

		CpuTimes current = getCpuTimes();

		float u = cpuUsage(previous, current);  // usage

		if (si) printIcon(u);
		if (sp) printPercent(u);
		if (sb) printBar(u);

		printf("\n");
		fflush(stdout);  

		previous = current;
	}
}



