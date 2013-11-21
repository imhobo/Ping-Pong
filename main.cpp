
#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <cstdio>
#include <cmath>

using namespace std;

int x,y,maxx,maxy,posx=1,posy=1,up_left,bottom_left,up_right,bottom_right,value=0;
char ch,temp;

void Start();
void update_score(int value);
void Initialize();
void welcome_screen();
void end_screen();
void paddle();
void menu();
void upper_boundary();
void drawdot(int color=YELLOW);
void display(int x,int y, char text[],int size=1,int box=BLUE,int txt=WHITE);
void draw(int x1,int y1,int x2,int y2,int color=WHITE);
void initial_values();
bool collision();

int main()
{
    Initialize();
    while(1)
        Start();
}

void Start()
{
    initial_values();
    welcome_screen();
    upper_boundary();
    update_score(0);
    paddle();

    while(1)
    {
        drawdot(BLACK);
        if(kbhit())
        {
            if(GetAsyncKeyState(0x57)&&!GetAsyncKeyState(0x53)&&up_left>50)
            {
                up_left-=5;
                bottom_left-=5;
                draw(0,up_left,20,up_left+5);
                draw(0,bottom_left,20,bottom_left+5,BLACK);
            }
            else if(GetAsyncKeyState(0x53)&&!GetAsyncKeyState(0x57)&&bottom_left<maxy)
            {
                draw(0,bottom_left,20,bottom_left+5);
                draw(0,up_left,20,up_left+5,BLACK);
                up_left+=5;
                bottom_left+=5;
            }
            if(GetAsyncKeyState(0x49)&&!GetAsyncKeyState(0x4B)&&up_right>50)
            {
                up_right-=5;
                bottom_right-=5;
                draw(maxx-20,up_right,maxx,up_right+5);
                draw(maxx-20,bottom_right,maxx,bottom_right+5,BLACK);
            }
            else if(GetAsyncKeyState(0x4B)&&!GetAsyncKeyState(0x49)&&bottom_right<maxy)
            {
                draw(maxx-20,bottom_right,maxx,bottom_right+5);
                draw(maxx-20,up_right,maxx,up_right+5,BLACK);
                up_right+=5;
                bottom_right+=5;
            }


            if(GetAsyncKeyState(0x51))
            {
                end_screen();
                while(1)
                {
                    ch=getch();
                    if(ch=='n')
                        return;
                    else if(ch=='y')
                        exit(0);
                }
            }
          /*  else if(GetAsyncKeyState(0x50))
            {
                cleardevice();
                display(maxx/2-90,maxy/2-55,"Paused...",5);
                display(maxx/2-110,maxy/2-5,"Press r to resume..",3);

                while(getch()!='r');

                cleardevice();
                paddle();
                upper_boundary();
                update_score(value);
            }*/
            else if(GetAsyncKeyState(0x52))
                return;

        }

        if(collision())
            return;
        x+=posx;y+=posy;
        drawdot();
        delay(8);
    }
}

void Initialize()
{
    int gd=DETECT,gmode;
    initgraph(&gd,&gmode,"");
    setbkcolor(BLACK);
}

void welcome_screen()
{

    display(70,140,"WELCOME TO PONG",4);
    display(80,210,"Press p to begin...",3);
    display(80,310,"Credits :");
    display(200,310,"Safal Pandita",1,YELLOW,BLACK);
    display(200,340,"Pulkit Kariryaa",1,YELLOW,BLACK);
    display(200,370,"Aditya Kathuria",1,YELLOW,BLACK);

    while(getch()!='p');
    cleardevice();
}

void update_score(int value)
{
    char arr[5];
    sprintf(arr,"%d",value);
    display(5,5,"Score : ");
    display(100,5,arr);
}

void end_screen()
{
    delay(8);
    cleardevice();
    update_score(value);
    display(80,180,"GAME OVER",6);
    display(100,270,"Really wanna quit(y/n)?",4);
}

void paddle()
{
    draw(0, up_left, 20, bottom_left,WHITE);
    draw(maxx-20, up_right, maxx, bottom_right,WHITE);
}

void menu()
{
    display(5,5,"Score : ");
    display(170,5,"Pause : P");
    display(340,5,"Restart : R");
    display(510,5,"Quit : Q");
}

void upper_boundary()
{
    setfillstyle(SOLID_FILL, BLUE);
    bar(0, 0, maxx, 50);
    menu();
}

void drawdot(int color)
{
    setfillstyle(SOLID_FILL, color);
    bar(x, y, x+10, y+10);
}

void display(int x,int y, char text[],int size,int box,int txt)
{
    setbkcolor(box);
    setcolor(txt);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,size);
    outtextxy(x,y,text);
    setbkcolor(BLACK);
}

void draw(int x1,int y1,int x2,int y2,int color)
{
    setfillstyle(SOLID_FILL, color);
    bar(x1, y1, x2, y2);
}

void initial_values()
{
    cleardevice();
    maxx=getmaxx(),maxy=getmaxy();
    x=maxx/2;
    y=maxy/2;
    up_right=up_left=maxy/2-25;
    bottom_right=bottom_left=up_left+75;
}

bool collision()
{
    if(x<=0||x+10>=maxx)
    {
        end_screen();
        char ch;
        while(1)
        {
            ch=getch();
            if(ch=='y'||ch=='Y')
                exit(0);
            if(ch=='n'||ch=='N')
                return true;
        }
    }

    if(y+posy>maxy-10)
    {
        y=maxy-10;
        posy=(-1)*abs(posy);
    }
    else if(y+posy<=50)
    {
        y=50;
        posy=abs(posy);
    }

    if(x>=maxx-30)
    {
        if(x>maxx-30)
        {
            if(y+posy<=bottom_right)
            {
                if(y+posy>=up_right-9)
                {
                    if(y<up_right+20)
                    {
                        y=up_right-10;
                        posy=(-1)*abs(posy);
                    }
                    else
                    {
                        y=bottom_right;
                        posy=abs(posy);
                    }
                    posx=-1;
                    return false;
                }
            }
        }
        else
        {
            if(y<=bottom_right)
            {
                if(y>=up_right-9)
                {
                    posx=-1;
                    return false;
                }
            }
        }
    }
    else if(x<=20)
    {
        if(x<20)
        {
            if(y+posy<=bottom_left)
            {
                if(y+posy>=up_left-9)
                {
                    if(y<up_left+20)
                    {
                        y=up_left-10;
                        posy=(-1)*abs(posy);
                    }
                    else
                    {
                        y=bottom_left;
                        posy=abs(posy);
                    }
                    posx=1;
                    return false;
                }
            }
        }
        else
        {
            if(y<=bottom_left)
            {
                if(y>=up_left-9)
                {
                    posx=1;
                    return false;
                }
            }
        }
    }
    return false;
}
