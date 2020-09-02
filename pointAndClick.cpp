#include <graphics.h>
#include <iostream>
using namespace std;

bool gameOver=false;
int startX=20,startY=45;
POINT curPos;
void Draw(int,int);
void Logic(int,int);
int main(){
    int gd=DETECT;
    int gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    int width=getmaxx()-100,height=getmaxy()-50;
    while(!gameOver){
         Draw(width,height);
         Logic(width,height);
    }
    if(gameOver)
        exit(0);
    getch();
    closegraph();
    return 0;
}
void Draw(int width,int height){
    GetCursorPos(&curPos);
    int x=curPos.x-5,y=curPos.y-20;
    //this gap is the distance between all the internal lines to each other
    const int gap=25;
    //Had to manually put all the fuking co-ordinates for the lines of the maze someone kill me pls
    //HORIZONTAL LINES OF THE MAZE
    setcolor(YELLOW);
    line(startX,startY,width,startY);
    line(startX,startY+gap,width/2,startY+gap);
    line(width/2+gap,startY+gap,width-gap,startY+gap);
    line(width/2+gap*3,startY+gap*2,width-gap,startY+gap*2);
    line(startX+gap,startY+gap*2,width/2,startY+gap*2);
    line(width/2,startY+gap,width/2,startY+gap*2);
    line(startX+gap,startY+gap*3,width/2,startY+gap*3);
    line(startX+gap*2,startY+gap*4,width/2-gap,startY+gap*4);
    line(startX+gap*3,startY+gap*5,width/2-gap,startY+gap*5);
    line(startX+gap*3,startY+gap*6,width/2,startY+gap*6);
    line(width/2+gap,startY+gap*6,width/2+gap*2,startY+gap*6);
    line(width/2+gap*3,startY+gap*6,width,startY+gap*6);
    line(startX+gap*3,startY+gap*7,width/2-gap,startY+gap*7);
    line(width/2,startY+gap*7,width/2+gap*4,startY+gap*7);
    line(width/2+gap*5,startY+gap*7,width-gap*2,startY+gap*7);
    line(startX+gap*3,startY+gap*8,width/2-gap*2,startY+gap*8);
    line(width/2+gap*2,startY+gap*8,width/2+gap*3,startY+gap*8);
    line(startX+gap*2,startY+gap*9,width/2-gap,startY+gap*9);
    line(width/2+gap*3,startY+gap*9,width/2+gap*4,startY+gap*9);
    line(width/2+gap*6,startY+gap*9,width-gap,startY+gap*9);
    line(startX,startY+gap*10,startX+gap*4,startY+gap*10);
    line(startX+gap*6,startY+gap*10,width/2,startY+gap*10);
    line(startX+gap*2,startY+gap*11,startX+gap*3,startY+gap*11);
    line(width/2+gap,startY+gap*11,width/2+gap*4,startY+gap*11);
    line(width/2+gap*5,startY+gap*11,width,startY+gap*11);
    line(startX+gap*2,startY+gap*12,startX+gap*4,startY+gap*12);
    line(startX+gap*5,startY+gap*12,width/2+gap*4,startY+gap*12);
    line(startX+gap,startY+gap*13,width/2+gap*2,startY+gap*13);
    line(width-gap*6,startY+gap*8,width-gap*2,startY+gap*8);
    line(width-gap*6,startY+gap*10,width,startY+gap*10);
    line(width/2+gap*3,startY+gap*13,width/2+gap*4,startY+gap*13);
    line(width/2+gap*5,startY+gap*13,width-gap,startY+gap*13);
    line(width/2+gap*4,startY+gap*14,width,startY+gap*14);
    line(startX+gap,startY+gap*14,width/2+gap*4,startY+gap*14);
    line(startX,startY+gap,startX,height);
    line(startX,height,width,height);
    line(width,startY,width,height-gap);

    //VERTICAL LINES OF THE MAZE
    line(width/2+gap,startY+gap,width/2+gap,startY+gap*6);
    line(startX+gap,startY+gap*3,startX+gap,startY+gap*6);
    line(width/2,startY+gap*3,width/2,startY+gap*6);
    line(width/2+gap*2,startY+gap*2,width/2+gap*2,startY+gap*6);
    line(width/2+gap*3,startY+gap*2,width/2+gap*3,startY+gap*6);
    line(width/2-gap,startY+gap*4,width/2-gap,startY+gap*5);
    line(startX+gap*3,startY+gap*5,startX+gap*3,startY+gap*6);
    line(startX+gap*2,startY+gap*4,startX+gap*2,startY+gap*9);
    line(startX+gap,startY+gap*7,startX+gap,startY+gap*12);
    line(width/2-gap,startY+gap*7,width/2-gap,startY+gap*9);
    line(width/2,startY+gap*7,width/2,startY+gap*10);
    line(width/2+gap*2,startY+gap*8,width/2+gap*2,startY+gap*9);
    line(width/2+gap*3,startY+gap*8,width/2+gap*3,startY+gap*9);
    line(width/2+gap*4,startY+gap*7,width/2+gap*4,startY+gap*9);
   // line(width/2+gap*5,startY+gap*7,width/2+gap*5,startY+gap*12);
    line(width-gap*2,startY+gap*7,width-gap*2,startY+gap*8);
    line(width-gap*6,startY+gap*8,width-gap*6,startY+gap*9);
    line(width-gap*6,startY+gap*9,width-gap*6,startY+gap*10);
    line(width-gap*6,startY+gap*11,width-gap*6,startY+gap*12);
    line(startX+gap*4,startY+gap*10,startX+gap*4,startY+gap*12);
    line(startX+gap*5,startY+gap*10,startX+gap*5,startY+gap*12);
    line(width/2+gap*4,startY+gap*11,width/2+gap*4,startY+gap*13);
    if(GetAsyncKeyState(VK_LBUTTON)){
        bar(x,y,x+3,y+3);
    }
}
void Logic(int width,int height){
    GetCursorPos(&curPos);
    int x=curPos.x,y=curPos.y;
    const int gap=25;
    //Collision Logic for all walls(i don't know why do i have to add "gap" in their tho??? fuck my life i guess startY and height are a "gap" less than the actual co-ordinates in the drawing function)
    if((x>=startX && x<=width && (y==startY+gap || y==height+gap))||(y>=startY+gap*2 && y<=height &&(x==startX || x==width)))//start+gap= Y co-ordinate of top wall and height+gap= Y co-ordinate of the bottom wall
        gameOver=true;

//Collision logic for all the internal Horizontal lines of top left
    else if((x>=startX || x>=startX+gap  || x>=startX+gap*2 || x>=startX+gap*3)&&
            (x<=width/2 || x<=width/2 || x<=width/2-gap)&&
            (y==startY+gap*2 || y==startY+gap*3 || y==startY+gap*4 || y==startY+gap*5 || y==startY+gap*6  || y==startY+gap*7 ))
    gameOver=true;

//Collision logic for all the internal Horizontal lines of mid left
    else if((x>=startX+gap*3 || x>=startX+gap*2 )&&
            (x<=width/2-gap || x<=width/2-gap*2)&&
            (y==startY+gap*8 || y==startY+gap*9|| y==startY+gap*10)
            )
    gameOver=true;

//Collision logic for all the internal Horizontal lines bottom left
    else if(((x>=startX || x>=startX+gap*2 )&& x<=startX+gap*4 && (y==startY+gap*11  || y==startY+gap*13)) || (x>=startX+gap*6 && x<=width/2 && y==startY+gap*11) ||
            (x>=startX+gap*5 && x<=width/2+gap*4 && y==startY+gap*13) || (x>=startX+gap && x<=width && y==startX+gap*16) || (x<=width/2+gap*2 && x>=startX+gap && y==startX+gap*15))
    gameOver=true;

//Collision logic for all the internal Horizontal lines top right
    else if((x>=width/2+gap && x<=width-gap && y==startY+gap*2) || (x>=width/2+gap*3 && x<=width-gap && y==startY*3) || (x>=width/2+gap*3 && x<=width && y==startY+gap*7)
            || (x>=width/2+gap && x<=width/2+gap*2 && y==startY+gap*7))
    gameOver=true;

//Collision logic for all the internal horizontal line mid-bottom right
     else if((x>=width/2 && x<=width/2+gap*4  && y==startY+gap*8) || (x>=width/2+gap*6 && x<=width-gap*2 && (y==startY+gap*8 || y==startY+gap*9)) || (x>=width/2+gap*2 && x<=width/2+gap*3 && y==startY+gap*9) ||
            (x>=width/2+gap*6 && x<=width-gap && y==startY+gap*10) || (x>=width/2+gap*5 && x<=width && (y==startY+gap*11 || y==startY+gap*12))
             || (x>=width/2+gap && x<=width/2+gap*4 && y==startY+gap*12) || (x>=width/2+gap*5 && x<=width-gap && y==startY+gap*14))
        gameOver=true;

}

