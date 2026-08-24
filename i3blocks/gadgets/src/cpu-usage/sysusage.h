#ifndef SYSUSAGE_H
#define SYSUSAGE_H

#define BAR_LEVELS 8                    // Number of bar simbols 
#define N_CL 16                   // Number of bar colors 
#define LOW_FREQ (100.0/BAR_LEVELS/4.0) // A frequency that I concider low 


#define ESCAPE_PERCENTS 0 


#define SHOW_ICON    1
#define SHOW_PERCENT 0
#define SHOW_BAR     0


#define ICON_TUX    ""
#define ICON_SKULL1 "☠"
#define ICON_SKULL2 ""
#define ICON_SKULL3 ""
// #define ICON_BRAIN  ""
#define ICON_BRAIN  ""
#define ICON_BOMB   ""
#define ICON_FIRE1  ""
#define ICON_FIRE2  ""


typedef struct {
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal;
} CpuTimes;



extern const char *redscale[];
extern const char *barSymbols[];



#define MSG_BAR_ZERO            "<span color='black'>▁</span>"
#define MSG_BAR_LOW             "<span color='%s'>▁</span>"
#define MSG_BAR_GREATER_THAN_0  "<span color='%s'>%s</span>"

// <span color='black'>0</span> is needed becouse status bar 
// sometimes hasn't a monospace font
#define MSG_PERCENT_ZERO           "<span color='black'>0</span>0%%"
#define MSG_PERCENT_LOW            "<span color='black'>0</span>%1.f%%"
#define MSG_PERCENT_LESS_THAN_10   "<span color='black'>0</span>%1.f%%"
#define MSG_PERCENT_LESS_THAN_100  "%2.f%%"
#define MSG_PERCENT_100            "%3.f%%"

#define MAX_STRING_SIZE 60
#define MSG_NUMBER 5

#endif






