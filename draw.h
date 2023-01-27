#include <graphics.h>
#include "agorithm.h"
using namespace std;

void drawxyAxis(){
    int x = getmaxx();
    int y = getmaxy();
    setcolor(BLACK);
    line(10,10,x,10);
    line(10,10,10,y);
    outtextxy(10,12,"0");
    outtextxy(110,12,"100");
    outtextxy(210,12,"200");
    outtextxy(310,12,"300");
    outtextxy(410,12,"400");
    outtextxy(510,12,"500");
    outtextxy(610,12,"600");
    outtextxy(710,12,"700");
    outtextxy(810,12,"800");
    outtextxy(12,110,"100");
    outtextxy(12,210,"200");
    outtextxy(12,310,"300");
    outtextxy(12,410,"400");
    outtextxy(12,510,"500");
    outtextxy(12,610,"600");
}
void drawVertex(int x,int y,char* names){
    setlinestyle(0,0,2);
    setcolor(BLACK);
    circle(x+10,y+10,radius);
    outtextxy(x-4-radius,y+10+radius+2, names);
}
void drawOneWayEdge(Vertex v1, Vertex v2,char* name, char* cost ){
    setlinestyle(0,0,3);
    setcolor(BLACK);
    pair<pair<int,int>,pair<int,int>> eCor = getIntersectionCoordinates(v1,v2);
    pair<int,int> sPoint = eCor.first;
    pair<int,int> ePoint = eCor.second;
    line(sPoint.first+10,sPoint.second+10,ePoint.first+10,ePoint.second+10);
    pair<pair<int,int>,pair<int,int>> aCor = getArrowCoordinates(sPoint,ePoint);
    pair<int,int> aPoint1 = aCor.first;
    pair<int,int> aPoint2 = aCor.second;
    line(ePoint.first+10,ePoint.second+10,aPoint1.first+10,aPoint1.second+10);
    line(ePoint.first+10,ePoint.second+10,aPoint2.first+10,aPoint2.second+10);
    outtextxy((v1.x+v2.x)/2+10,(v1.y+v2.y)/2-10, cost);
    outtextxy((v1.x+v2.x)/2-20,(v1.y+v2.y)/2+20, name);
}
void drawTwoWayEdge(Vertex v1, Vertex v2,char* name, char* cost ){
    setlinestyle(0,0,3);
    setcolor(BLACK);
    pair<pair<int,int>,pair<int,int>> eCor = getIntersectionCoordinates(v1,v2);
    pair<int,int> sPoint = eCor.first;
    pair<int,int> ePoint = eCor.second;
    line(sPoint.first+10,sPoint.second+10,ePoint.first+10,ePoint.second+10);
    outtextxy((v1.x+v2.x)/2+10,(v1.y+v2.y)/2-6, cost);
    outtextxy((v1.x+v2.x)/2-20,(v1.y+v2.y)/2+20, name);
}
void deleteVertex(Vertex v1){
    setlinestyle(0,0,2);
    setcolor(BLACK);
    circle(v1.x+10,v1.y+10,radius);
    outtextxy(v1.x-4-radius,v1.y+10+radius+2, "                 ");
}
void deleteTwoWayEdge(Vertex v1,Vertex v2){
    setcolor(WHITE);
    setlinestyle(0,0,3);
    pair<pair<int,int>,pair<int,int>> eCor = getIntersectionCoordinates(v1,v2);
    pair<int,int> sPoint = eCor.first;
    pair<int,int> ePoint = eCor.second;
    line(sPoint.first+10,sPoint.second+10,ePoint.first+10,ePoint.second+10);
    outtextxy((v1.x+v2.x)/2+10,(v1.y+v2.y)/2-10, "       ");
    outtextxy((v1.x+v2.x)/2+10,(v1.y+v2.y)/2-9,  "       ");
    outtextxy((v1.x+v2.x)/2-20,(v1.y+v2.y)/2+20, "       ");
    setlinestyle(0,0,2);
    setcolor(BLACK);
    circle(v1.x+10,v1.y+10,radius);
    circle(v2.x+10,v2.y+10,radius);
    // delay(1000);
}
void deleteOneWayEdge(Vertex v1, Vertex v2){
    setcolor(WHITE);
    setlinestyle(0,0,3);
    pair<pair<int,int>,pair<int,int>> eCor = getIntersectionCoordinates(v1,v2);
    pair<int,int> sPoint = eCor.first;
    pair<int,int> ePoint = eCor.second;
    line(sPoint.first+10,sPoint.second+10,ePoint.first+10,ePoint.second+10);
    pair<pair<int,int>,pair<int,int>> aCor = getArrowCoordinates(sPoint,ePoint);
    pair<int,int> aPoint1 = aCor.first;
    pair<int,int> aPoint2 = aCor.second;
    line(ePoint.first+10,ePoint.second+10,aPoint1.first+10,aPoint1.second+10);
    line(ePoint.first+10,ePoint.second+10,aPoint2.first+10,aPoint2.second+10);
    outtextxy((v1.x+v2.x)/2+10,(v1.y+v2.y)/2-10, "       ");
    outtextxy((v1.x+v2.x)/2+10,(v1.y+v2.y)/2-9,  "       ");
    outtextxy((v1.x+v2.x)/2-20,(v1.y+v2.y)/2+20, "       ");
    setlinestyle(0,0,2);
    setcolor(BLACK);
    circle(v1.x+10,v1.y+10,radius);
    circle(v2.x+10,v2.y+10,radius);
}
void highlightVertex(Vertex v1){
    setfillstyle(LTSLASH_FILL,BLUE);
    floodfill(v1.x+10,v1.y+10,BLACK);
}
void highlightEdge(Vertex v1, Vertex v2){
    deleteTwoWayEdge(v1,v2);
    setcolor(BLUE);
    setlinestyle(1,0,3);
    pair<pair<int,int>,pair<int,int>> eCor = getIntersectionCoordinates(v1,v2);
    pair<int,int> sPoint = eCor.first;
    pair<int,int> ePoint = eCor.second;
    line(sPoint.first+10,sPoint.second+10,ePoint.first+10,ePoint.second+10);
    setcolor(BLACK);
}
void unHighlightVertex(Vertex v1){
    setfillstyle(EMPTY_FILL,WHITE);
    floodfill(v1.x,v1.y,BLACK);
}
void unHighlightEdge(Vertex v1, Vertex v2){
    setlinestyle(0,0,3);
    setcolor(BLACK);
    pair<pair<int,int>,pair<int,int>> eCor = getIntersectionCoordinates(v1,v2);
    pair<int,int> sPoint = eCor.first;
    pair<int,int> ePoint = eCor.second;
    line(sPoint.first+10,sPoint.second+10,ePoint.first+10,ePoint.second+10);    
}
