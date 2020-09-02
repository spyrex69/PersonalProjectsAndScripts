#include <graphics.h>
#include <cstdio>
#include <time.h>
using namespace std;

int main(){
    int gd=DETECT;
    int gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    //These two arrays are for storing time and data respectively
    char forTime[20];
    char forDate[20];
    struct tm *ptr;//This is a pointer to object type of 'tm' built-in structure which has member veriables like hours,minutes and day etc
    while(true){
        int ManageAMPM_forHours;
        char AMorPM[2];
        AMorPM[1]='M';
        time_t now=time(NULL);//'now' is an object of type time_t which return current system time and in time() we pass NULL because time is changing continouesly
        ptr=localtime(&now);//Here we pass 'now' object's reference in localtime() which returns a pointer to string of date and time

        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,9);
        setcolor(DARKGRAY);
        //This logic is for converting 14 hour system to 12 hour
        if((int)ptr->tm_hour>12)
            {
             AMorPM[0]='P';
             ManageAMPM_forHours=(((int)ptr->tm_hour)-12);
            }
        else{
                AMorPM[0]='A';
            {
            if(ptr->tm_hour==0)
               ManageAMPM_forHours=((ptr->tm_hour)+12);
            else
            ManageAMPM_forHours=ptr->tm_hour;
            }
           }

        sprintf(forTime,"%d: %d:  %d %S",ManageAMPM_forHours,ptr->tm_min,ptr->tm_sec);//now we just dereference that pointer and get those member variables in 'tm' structure
        outtextxy(50,200,forTime);
        outtextxy(500,200,AMorPM);

        setcolor(YELLOW);
        settextstyle(TRIPLEX_FONT,HORIZ_DIR,6);
        sprintf(forDate,"%d/%d/%d",ptr->tm_mday,ptr->tm_mon+1,(ptr->tm_year-100)+2000);//now we just dereference that pointer and get those memnber variables in 'tm' structure
        outtextxy(100,320,forDate);

        delay(500);//delay function is for preventing the screen flickering
        cleardevice();//this function is for updating the time and draw updated time every clock cycle
    }

    getch();
    closegraph();
}
