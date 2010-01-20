#include<time.h>
#include<curses.h>
#include<unistd.h>
#include<sys/types.h>
#include<linux/fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int current_getch=0,j=0;
static WINDOW *mainwnd;
static WINDOW *screen;
char cmdname[50];
char* b;

struct psd_info_t
{
	unsigned int pid;
	unsigned int tgid;
	int prio;
	char command[50];
}psd_info[172];

void  openfile_and_setdisplay(void);
void read_proc(void);
void display_array(void);
void array_allocation(void);
void screen_init(void);
void screen_end(void);
