#include"psd.h"
int temp_key=0;


void openfile_and_setdisplay(void)
{
	int fd,ret;
	char buf[1024];
	fd = open("/proc/psd/pinfo",O_RDONLY);
	if(fd<0)
	{
		perror("error in opening");
		exit(1);
	}
	while(1){

		ret = read(fd,buf,1024);
		if(ret==0) {
			break;
		}
		if(ret>0){
			b = strstr(buf, "PID=");
			array_allocation();
		}
	}
	close(fd);
}

//reading the proc file and putting info in the array psd_info
void read_proc(void)
{
	openfile_and_setdisplay();
	display_array();
}

//displaying the contents of the array psd_info
void display_array(void)
{
	curs_set(0);
	 wsetscrreg(screen,0,100);
     scrollok(screen,true);
     wscrl(screen,0);

	int count=0,y=0,LINES=54;
	static int previous=0;

	if(current_getch==97)
	{
      if(previous==98 && j>108)
    	   LINES=108;
       else if(previous==97 && temp_key==97)
    	   previous++;
       else
    	   previous=97;

		for(count=LINES;count<j && j<172 ;count++)
		{
			mvwprintw(screen,y,0,"%d %d %s",psd_info[count].pid,psd_info[count].prio,psd_info[count].command);
			wrefresh(screen);
			y++;

		}

	}
	else
	{
		for(count=0;count<=53;count++)
		{
			mvwprintw(screen,y,0,"%d %d %s",psd_info[count].pid,psd_info[count].prio,psd_info[count].command);
			wrefresh(screen);
			y++;
		}
      previous=0;
	}
	refresh();
}

//allocation of values to the array
void array_allocation(void)
{
	int len1=strlen(b);
	int i=0,len2=0;
	static int breaking_Pid=0;
	char pidstring[15],tgidstring[10],priority[10],cmd[20];
	while(i<len1)
	{
		if(b)
		{
			sscanf(b,"%[^',']", &cmdname);
			sscanf(cmdname,"PID=%s TGID=%s Priority=%s CMDNAME=%s",&pidstring,&tgidstring,&priority,&psd_info[j].command);
			psd_info[j].pid=atoi(pidstring);
			if(breaking_Pid>psd_info[j].pid)
			{
				j--;
				breaking_Pid=0;
				break;
			}
			breaking_Pid=psd_info[j].pid;
			psd_info[j].tgid=atoi(tgidstring);
			psd_info[j].prio=atoi(priority);
			j++;
		}
		len2=strlen(cmdname);
		b+=len2+1;
		i+=len2+1;
	}
}



void screen_init(void) {
	mainwnd = initscr();
	noecho();
	cbreak();
	nodelay(mainwnd, TRUE);
	refresh();
	wrefresh(mainwnd);
	screen = newwin(0,0,0,0);
	idlok(screen,true);
}


void screen_end(void) {
	endwin();
}


int main(void) {
	screen_init();
//	int temp_key=0;
	static int doloop=1;
	while (doloop)
	{
		temp_key= getch();
		if(temp_key==-1)
			printf("***%d***",current_getch);
		else
			current_getch=temp_key;
		printf("***%d***",current_getch);
		if (current_getch == 113) {
			doloop = 0;
		}
		j=0;
		read_proc();
		sleep(2);
		clear();
	}
	screen_end();
	printf("TEST ENDS\n");
	return 0;
}
