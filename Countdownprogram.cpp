#include <graphics.h>
#include <cstdio>
#include <iostream>
//#include <time.h>
using namespace std;
int main(){
    int gd=DETECT;
    int gm;
    initgraph(&gd,&gm,"C:\\tc\\bgi");
    char arr[50];
    int minutes,seconds;
    printf("Enter minutes :");
    cin>>minutes;
    printf("Enter seconds :");
    cin>>seconds;
    int miliseconds=60;
    setcolor(YELLOW);
    settextstyle(7,HORIZ_DIR,8);
    for(int i=minutes,k=minutes;i>=0;i--){//condition is i>=0 because when if min is 0 then there must be seconds left

        for(int j=seconds,s=seconds;j>0;j--){//k and s are just reference for comparing to make miliseconds to 60
                                             //when 1 second has passed and same for seconds and minutes.

            for(int f=miliseconds;f>0;f--){

                    sprintf(arr,"%d : %d : %d",i,j,f);
                    outtextxy(20,200,arr);
                    delay(17);//delay parameter at 17 is perfect
            }
            if(s>=j)
            { miliseconds=60; }
            cleardevice();
       }
        if(k>=i)
        { seconds=60; }
       // cleardevice();
    }
     settextstyle(BOLD_FONT,HORIZ_DIR,5);

    setcolor(RED);
    outtextxy(100,200,"HAPPY NEW YEAR");
    delay(700);

    setcolor(DARKGRAY);
    outtextxy(100,300,"HAPPY NEW YEAR");
    delay(700);

    setcolor(YELLOW);
    outtextxy(100,100,"HAPPY NEW YEAR");
    delay(700);
    cleardevice();

    settextstyle(TRIPLEX_SCR_FONT,HORIZ_DIR,5);
    for(int i=1;i<15;i++){
        setcolor(i);
        outtextxy(50,200,"HAPPY NEW YEAR");
        delay(500);
    }

    cleardevice();
//int c=5;
//char arr[10];
//sprintf(arr,"This is %d",c);
//outtextxy(100,100,arr);

    getch();
    closegraph();
}
