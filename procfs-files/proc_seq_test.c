#include<unistd.h>
#include<sys/types.h>
#include<linux/fcntl.h>
#include<stdio.h>

int main()
{

   int fd,ret,buf[8192];
   fd = open("/proc/proc_test/test",O_RDONLY);
   if(fd<0){
           perror("error in opening");
           exit(1);
   }
   //lseek(fd,22,SEEK_SET);

   //ret = read(fd,buf,11);
   
   //printf("the no. characters returned is %d\n", ret);

   //if(ret>0) { write(STDOUT_FILENO,buf,ret); }
   
   //ret = read(fd,buf,11);
   //ret = read(fd,buf,11);
while(1){
   ret = read(fd,buf,8192);
   printf("the no. characters returned is %d\n", ret);
   if(ret==0) break;
   if(ret>0)  write(STDOUT_FILENO,buf,ret); 
  } //pause();
   exit(0);

}
