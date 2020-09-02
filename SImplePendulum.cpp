#include <graphics.h>
#include <math.h>

using namespace std;
int main(){
    int gd=DETECT;
    int gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");

    int pivotX=getmaxx()/2,pivotY=getmaxy()/2-100;
    int lenght=200;
    int bobX=getmaxx()/2,bobY=lenght;
    int Angle=(atan(1)*4);//this is basically pie which means 3.14.....=atan(1)*4 which is 180 degree
    float AngleVel=0.0;
    float AngleAcc=0.0;
    const float g=0.8;
//    float timeTaken;

    while(true){
    //these co-ordinates will change as the Angle changes
    int x=(pivotX+lenght*sin(Angle));
    int y=(pivotY+lenght*cos(Angle));
    bobX=x;
    bobY=y;
    line(pivotX,pivotY,bobX,bobY);

    setfillstyle(SOLID_FILL,DARKGRAY);
    circle(bobX,bobY,30);
    floodfill(100,200,WHITE);
//    timeTaken=(2*3.14*sqrt(lenght/g));

    AngleAcc=(-1+g/lenght)*sin(Angle);//calculating angle's acceleration with formula

    Angle+=AngleVel;//now changing angle according to angular velocity

    AngleVel+=AngleAcc;//angle velocity is increased or decreased by angle acceleration, it basically determines velocity

    AngleVel*=0.95;//this is for decreasing velocity as pendulum swings ,but it seems to not work
    delay(100);

    cleardevice();
    }

    getch();
    closegraph();
}
