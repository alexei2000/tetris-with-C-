#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>
#include <vector>
using namespace sf;


const int M = 20;
const int N = 10;
const int translateX=400,translateY=40;

int field[M][N]={0};

struct Point{
    int x,y;
}a[4],b[4],a1[4],a2[4];

int figures[7][4]={
    1,3,5,7, //I
    2,4,5,7, //Z
    3,5,4,6, //S
    3,5,4,7, //T
    2,3,5,7, //L
    3,5,7,6, //J
    2,3,4,5, //O
};

bool check(){
    for(int i=0;i<4;i++){
        if(a[i].x<0 || a[i].y>=M || a[i].x>=N)
            return 0;
        else if(field[a[i].y][a[i].x]) return 0;
    }
    return 1;
}

RectangleShape botton(int r,int g,int b, int a){
    RectangleShape botton;
    Vector2 <float>size(100.0,50.0);
    botton.setSize(size);
    botton.setOutlineColor(Color(235,129,0,92));
    botton.setOutlineThickness(3);

    botton.setFillColor(Color(r,g,b,a));
    botton.setPosition(750,525);
    return botton;
}

int main(){
    //VideoMode::getFullscreenModes();

    Image icon;
    icon.loadFromFile("images/icono.png");

    srand(time(0));
    RenderWindow window(VideoMode::getFullscreenModes()[1], "Tetris",Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);
    window.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());



    //sprites
    Texture marc;
    marc.loadFromFile("images/marco.png");
    Sprite marco(marc);
    marco.setPosition(313,-235+translateY);

    Texture t;
    t.loadFromFile("images/texturas.png");
    Sprite s(t);

    Texture bckgr;
    bckgr.loadFromFile("images/bckgr.png");
    Sprite background(bckgr);


    //fonts

    Font font;
    font.loadFromFile("font/Roboto-Medium.ttf");

    Text points;
    Text lvl;
    Text restart;

    points.setFont(font);
    lvl.setFont(font);
    restart.setFont(font);

    points.setCharacterSize(20);
    lvl.setCharacterSize(20);
    restart.setCharacterSize(20);

    points.setStyle(sf::Text::Regular);
    lvl.setStyle(sf::Text::Regular);
    restart.setStyle(sf::Text::Regular);


    lvl.setPosition(750,400);
    points.setPosition(750,450);

    restart.setPosition(768,536);
    restart.setString("restart");


    //figures position
    int dx=0; bool rotate=0; int colorNum,colorNum1,colorNum2;
    float timer=0,delay=0.3; int n,n1,n2; int numberPoints=0,numberLvl=1;
    bool gameOver=0;
    String cad="";
    Clock clock;
    Cursor cursor;

    RectangleShape Botton=botton(207,162,50,255);

    n=rand()%7;
    n1=rand()%7;
    n2=rand()%7;

    colorNum=1+rand()%7;
    colorNum1=1+rand()%7;
    colorNum2=1+rand()%7;


    for(int i=0;i<4;i++){
        a[i].x = figures[n][i]%2+4;
        a[i].y = figures[n][i]/2;

        a1[i].x = figures[n1][i]%2+31;
        a1[i].y = figures[n1][i]/2+2;

        a2[i].x = figures[n2][i]%2+31;
        a2[i].y = figures[n2][i]/2+9;
    }

    Font();

    while(window.isOpen()){

        float time=clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event e;



        while(window.pollEvent(e)){
            if(e.type == Event::Closed){
                window.close();
            }
            if(e.type == Event::KeyPressed){
                if(e.key.code==Keyboard::Up){
                    if(n!=6){
                        rotate=true;
                    }
                }
                else if(e.key.code==Keyboard::Left){
                    dx=-1;
                }
                else if(e.key.code==Keyboard::Right){
                    dx=1;
                }
            }
            if(e.type == Event::MouseButtonPressed){
                if(e.mouseButton.button==Mouse::Left){
                    if((e.mouseButton.x>=750 && e.mouseButton.x<=850) &&(e.mouseButton.y>=525 && e.mouseButton.y<=575)){
                        std::cout<<e.mouseButton.x<<" "<<e.mouseButton.y<<std::endl;
                    }


                }

            }
            if(e.type == Event::MouseMoved){
                if((e.mouseMove.x>=750 && e.mouseMove.x<=850) &&(e.mouseMove.y>=525 && e.mouseMove.y<=575)){
                    Botton = botton(186,133,41,255);
                    cursor.loadFromSystem(Cursor::Hand);
                }
                else{
                    Botton= botton(207,162,50,255);
                    cursor.loadFromSystem(Cursor::Arrow);
                }
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Down)){
            delay=0.05;
        }



        //<--move-->//
        for(int i=0; i<4;i++){
            b[i]=a[i];
            a[i].x+=dx;
        }

        if(!check()){ //si colisiona
            for(int i=0;i<4;i++){
                a[i]=b[i];
            }
        }

        //<--rotate-->//
        if(rotate){
            Point p=a[1];
            for(int i=0;i<4;i++){
                int x= a[i].y-p.y;
                int y = a[i].x-p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if(!check()){
                for(int i=0;i<4;i++){
                    a[i]=b[i];
                }
            }
        }


        //<--tick-->//
        if(timer>delay){
            for (int i=0;i<4;i++){
                b[i]=a[i];
                a[i].y+=1;

            }
            if(!check()){
                for(int i=0;i<4;i++){
                    field[b[i].y][b[i].x]=colorNum;
                }

                colorNum=colorNum1;
                n=n1;

                colorNum1=colorNum2;
                n1=n2;

                colorNum2=1+rand()%7;
                n2=rand()%7;

                

                for(int i=0;i<4;i++){
                    a[i].x = figures[n][i]%2+4;
                    a[i].y = figures[n][i]/2;

                    a1[i].x = figures[n1][i]%2+31;
                    a1[i].y = figures[n1][i]/2+2;

                    a2[i].x = figures[n2][i]%2+31;
                    a2[i].y = figures[n2][i]/2+9;
                }
            }
            timer=0;
        }

        /////////<--check lines-->//////

        int k=M-1;
        for(int i=M-1;i>0;i--){
            int count = 0;
            for(int j=0;j<N;j++){
                if(i==1 && field[i][j]){
                    gameOver=1;
                }
                if(field[i][j]){
                    count++;
                }
                field[k][j]=field[i][j];
            }
            if(count<N){
                k--;
            }
            else{
                numberPoints+=10;
                if(numberPoints!=0 && numberPoints%100==0){
                    numberLvl++;
                    delay=delay-0,1;
                }
            }
        }

        dx=0; rotate=0; delay=1;

        /////<--draw/////
        if(!gameOver){
            window.clear(Color::Black);
            window.draw(background);

            for(int i=0;i<M;i++){
                for(int j=0;j<N;j++){
                    
                    if(field[i][j]==0){
                        continue;
                    }
                    s.setTextureRect(IntRect((field[i][j]-1)*30,0,30,30));
                    s.setPosition(j*30+translateX,i*30+translateY);
                    window.draw(s);
                }
                
            }
            //figures
            s.setTextureRect(IntRect((colorNum-1)*30,0,30,30));
            for(int i=0;i<4;i++){
                s.setPosition(a[i].x*30+translateX, a[i].y*30+translateY);
                window.draw(s);
            }
            s.setTextureRect(IntRect((colorNum1-1)*30,0,30,30));
            s.setScale(25.0/30.0,25.0/30.0);

            int rest;
            
            if(n1==6 || n1==0){
                rest=15;
            }
            else{
                rest=0;
            }
            for(int i=0;i<4;i++){
                s.setPosition(a1[i].x*25-(n1==0 ? 12 : 0), a1[i].y*25+20+rest);
                window.draw(s);
            }
            s.setTextureRect(IntRect((colorNum2-1)*30,0,30,30));

            if(n2==6 || n2==0){
                rest=15;
            }
            else{
                rest=0;
            }
            for(int i=0;i<4;i++){
                s.setPosition(a2[i].x*25-(n2==0 ? 12 : 0), a2[i].y*25-10+rest);
                window.draw(s);
            }
            s.setScale(1,1);


            window.draw(marco);

            

            cad=std::to_string(numberLvl);
            lvl.setString("Nivel: "+cad);

            cad=std::to_string(numberPoints);
            points.setString("Puntos: "+cad);

            window.draw(points);
            window.draw(lvl);

            window.draw(Botton);
            window.draw(restart);

            window.setMouseCursor(cursor);
        }

        window.display();
    }

    return 0;
}