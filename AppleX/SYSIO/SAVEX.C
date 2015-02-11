#include <console.h>
#include <stdio.h>
#include <fcntl.h>
#include <prodos.h>
#include <sgtty.h>
#include <device.h>
#include <sysfunc.h>

#define SAVE    0
#define RESTORE 1
#define FILEHEADER 2

memfile(savex,address,length,action)
char *savex;
int address,length,action;
{
    int fh;


    if(action==SAVE)
     {
    if((fh = open(savex,O_CREAT|O_TRUNC|O_WRONLY,0x04)) != -1)
        {
        write(fh,(char *)address,length);
        close(fh);
        }
        }

    if(action==RESTORE)
     {
      if((fh = open(savex,O_RDONLY,0x04))!=-1)
      {
       if(length==0)read(fh,(char *)&length,FILEHEADER);
       read(fh,(char *)address,length);
       close(fh);
       }
       }

}

