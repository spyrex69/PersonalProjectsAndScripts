#include <time.h>
#include <cstdio>
#include <graphics.h>

using namespace std;

int main(){
    int gd=DETECT;
    int gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    //Built-in tm struct has time infos like hours date and second etc as there member variables
    struct tm *ptr;
    char arr[100];//for holding time info return in string type
    int holdtime;//for holding that time info after it's converted from string to int
    int centerX=(getmaxx()/2);
    int centerY=(getmaxy()/2);

    //Actual co-ordinates for the clock sticks to follow

    int coordsForHoursX[12]={50,86,100,86,50,0,-50,-86,-100,-86,-50,0};
    int coordsForHoursY[12]={-86,-50,0,50,86,100,86,50,0,-50,-86,-100};

    int coordsForMinSecX[60]={0,23,34,45,55,65,34,92,100,107,113,122,126,128,130,130,130,128,
                            126,122,113,107,100,92,65,55,45,34,23,0,-23,-34,-45,-55,-65,-84,-92,
                            -100,-107,-113,-122,-126,-128,-130,-130,-130,-128,-126,-122,-113,-107,-100,-92,-84,
                            -65,-55,-45,-34,-23};

    int coordsForMinSecY[60]={-130,-128,-126,-122,-118,-113,-100,-92,-84,-75,-65,-45,-34,-23,-12,0,12,
                             23,34,45,65,75,84,92,100,113,118,122,126,128,130,128,126,122,118,113,100,92,84,
                             75,65,45,34,23,12,0,-12,-23,-34,-45,-65,-75,-84,-92,-100,-113,-118,-122,-126,-128};
    while(true){
    //"now" is the object of time_t class that hold time info and in time function we pass NULL cuz it means time is contonuesly changing
    time_t now=time(NULL);
    ptr=localtime(&now);//ptr is a pointer that returns a string of time info
    setcolor(WHITE);
    //radius=200,but I'll calculate co-ordinates with radius=190 because we want those numbers to be inside
    //the circumference of the circle not on it.
    circle(centerX,centerY,200);

    //x co-ordinate=cos(angle) and y co-ordinate=sin(angle),calculated manually
    setcolor(YELLOW);
    outtextxy(centerX+95+(-6),centerY+165+(-6),"5");
    outtextxy(centerX-95,centerY-165,"11");
    outtextxy(centerX+165+(-5),centerY+95+(-5),"4");
    outtextxy(centerX-165,centerY-95,"10");
    outtextxy(centerX+190,centerY+0,"3");
    outtextxy(centerX-190,centerY+0,"9");
    outtextxy(centerX+165,centerY-95,"2");
    outtextxy(centerX-165,centerY+95,"8");
    outtextxy(centerX+95,centerY-165,"1");
    outtextxy(centerX-95+(5),centerY+165+(-5),"7");
    outtextxy(centerX+0,centerY-190,"12");
    outtextxy(centerX+0,centerY+190+(-7),"6");

    //getting time info and drawing the hour line
    strftime(arr,100,"%I",ptr);
    sscanf(arr,"%d",&holdtime);
    setcolor(DARKGRAY);
    line(centerX,centerY,centerX+coordsForHoursX[holdtime-1],centerY+coordsForHoursY[holdtime-1]);

    //getting time info and drawing the minutes line
    setcolor(5);
    strftime(arr,100,"%M",ptr);
    sscanf(arr,"%d",&holdtime);
    line(centerX,centerY,centerX+coordsForMinSecX[holdtime],centerY+coordsForMinSecY[holdtime]);

    //getting time info and drawing seconds line
    setcolor(13);
    strftime(arr,100,"%S",ptr);
    sscanf(arr,"%d",&holdtime);
    line(centerX,centerY,centerX+coordsForMinSecX[holdtime],centerY+coordsForMinSecY[holdtime]);

    delay(100);
    cleardevice();
    }

    getch();
    closegraph();
}
