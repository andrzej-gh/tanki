// SERV.cpp : implementation file
//
#include "stdafx.h"
#include "TankiServ.h"
#include "SERV.h"
#include ".\serv.h"
#include ".\cobiekt.h"
#include ".\cbonus.h"
#include ".\cgora.h"
#include ".\clas.h"
#include ".\cmina.h"
#include ".\cwoda.h"
#include ".\cpocisk.h"
#include ".\ctank.h"
#include <math.h>
#define PI 3.14159265



int object_idx=0;     //< ilosc obiektow na mapie; 
CObiekt* object[500]; //< tabela obiektow;
int player_idx=0;     //< liczba aktywnych graczy;
CTank* player[12];    //< tabela czolgow;
int shot_idx=0;       //< liczba pociskow w powietrzu
CPocisk* shot[100];   //< tablica w.w. pociskow
char czat[500][100];  //< tablica wiadomosci do czatu
int miny_idx=0;       //< liczba min na mapie;
CObiekt* miny[200];   //< tabela min;
CObiekt* bonus[5];    //< tablica bonusow


int las_temp[100];///<tablica indeksów zniszczonych drzew
int las_idx=0;///<liczba zniszczonych drzew

int czat_temp=0;///<zmienna pomocnicza do wyswietlania czatu
int czat_idx=0;///<ilosc wiadomosci 
int map_id;
char up_id;
int temp_frag;///<zmienna pomocnicza - limit fragow (zmiennej CSERV::frag_limit nie widzi w watkach
int nad;///<zmienna pomocnicza watku przyjmowania nowych graczy (watek_dolacz) wysyla informacje czy server jest pelen lub czy jest juz gracz o danym kolorze
int temp=0;///<zmienna pomocnicza przy wlaczaniu watkow i inicjowaniu mapy
int temp_end=0;

//! struktura przesylana w komunikacji czatu
struct sRamka
{
	int id;/**< \brief numer identyfikacyjny wiadomosci
* 
1-gracz przesyla wiadomosc
2-grzcz pyta o nowe wiadomosci
3-gracz chce otrzymac konkretna wiadomosc
*/
	int rozm;///<do klijenta przesyla ilosc wiadomosci, a na serwer wiadomosc ktora klijent chce pobrac
	char tekst[100];///<przesyla tekst wiadomosci
};

//! struktura przesylana w komunikacji polozenie i id bitmapy bonosow
struct SBonus
{
int bm_id;///<id bitmapy
float x,y;///<wspolrzedne
};
//!struktura sluzaca do wysylania informacji o tankach
struct STank
{
	int bm_id;///<id bitmapy
	int tank_id;///<id czolgu (id koloru)
	float x, y;///<wspolrzedne
 int score;///<ilosc zdobytych fragow
 int HP;///<ilosc zycia
 int armor;///<ilosc pancerza
 int weapon_id;///<id broni
 int iloscM, iloscL;///<ilosc min oraz lasera
 int speed_time;///<czas bonusowego speeda
 float speed;///<zmienna pomocnicza do obliczania speeda
};
//!struktura sluzaca do przesylania informacji o minach
struct SMina
{
	float x,y;//<wspolrzedne
};
//!struktura sluzaca do przesylania informacji o pociskach
struct SPocisk
{
int bm_id;///<id bitmapy
float x, y; ///<wspolrzedne
};

//!tworzenie mapy
/**
*Funkcja tworzy konkretna mape w zaleznosci od parametru mapa_id
/param map_id przyjmuje wartosc identyfikatora mapy ktora ma zostac stworzona
*/
void mapa(int mapa_id)
{
	if(mapa_id==0){
//ramka:
object[object_idx] = new CGora(25,25,50*sqrt((float)2),1,4);
object_idx++;

for(int i=1; i<=22; i++)
{
 object[object_idx] = new CGora(25,(float)25+50*i,50*sqrt((float)2),1,8);
 object_idx++;
}

object[object_idx] = new CGora(25,1175,50*sqrt((float)2),1,9);
object_idx++; 

for(int i=1; i<=30; i++)
{
 object[object_idx] = new CGora((float)25+50*i,1175,50*sqrt((float)2),1,2);
 object_idx++;
}

object[object_idx] = new CGora(1575,1175,50*sqrt((float)2),1,10);
object_idx++; 

for(int i=1; i<=22; i++)
{
 object[object_idx] = new CGora(1575,(float)25+50*i,50*sqrt((float)2),1,8);
 object_idx++;
}

object[object_idx] = new CGora(1575,25,50*sqrt((float)2),1,5);
object_idx++; 

for(int i=1; i<=30; i++)
{
 object[object_idx] = new CGora((float)25+50*i,25,50*sqrt((float)2),1,2);
 object_idx++;
}
//gory:
       
object[object_idx] = new CGora(25+9*50,5*50,25,0,6);
object_idx++;       
object[object_idx] = new CGora(25+9*50,25+5*50,50*sqrt((float)2),1,9);
object_idx++;
object[object_idx] = new CGora(500,25+5*50,25,0,3);
object_idx++;

object[object_idx] = new CGora(300,525,25,0,1);
object_idx++;       
object[object_idx] = new CGora(325,525,50*sqrt((float)2),1,2);
object_idx++;
object[object_idx] = new CGora(350,525,25,0,3);
object_idx++;

object[object_idx] = new CGora(275,1025,25,0,6);
object_idx++;       
object[object_idx] = new CGora(275,1050,50*sqrt((float)2),1,9);
object_idx++;
object[object_idx] = new CGora(325,1050,50*sqrt((float)2),1,2);
object_idx++;
object[object_idx] = new CGora(350,1050,25,0,3);
object_idx++;

object[object_idx] = new CGora(475,650,25,0,6);
object_idx++;       
object[object_idx] = new CGora(475,675,50*sqrt((float)2),1,9);
object_idx++;
object[object_idx] = new CGora(525,675,50*sqrt((float)2),1,2);
object_idx++;
object[object_idx] = new CGora(575,675,50*sqrt((float)2),1,2);
object_idx++;       
object[object_idx] = new CGora(625,675,50*sqrt((float)2),1,5);
object_idx++;
object[object_idx] = new CGora(625,725,50*sqrt((float)2),1,8);
object_idx++;
object[object_idx] = new CGora(625,750,25,0,7);
object_idx++;

object[object_idx] = new CGora(21*50+25,300,25,0,7);
object_idx++;
object[object_idx] = new CGora(1075,275,50*sqrt((float)2),1,5);
object_idx++;       
object[object_idx] = new CGora(1025,275,50*sqrt((float)2),1,2);
object_idx++;
object[object_idx] = new CGora(975,275,50*sqrt((float)2),1,4);
object_idx++;
object[object_idx] = new CGora(975,325,50*sqrt((float)2),1,8);
object_idx++;       
object[object_idx] = new CGora(975,375,50*sqrt((float)2),1,8);
object_idx++;
object[object_idx] = new CGora(975,425,50*sqrt((float)2),1,8);
object_idx++;
object[object_idx] = new CGora(975,450,25,0,7);
object_idx++;

object[object_idx] = new CGora(950,725,25,0,1);
object_idx++;
object[object_idx] = new CGora(950,725,25,0,3);
object_idx++;

object[object_idx] = new CGora(1275,750,25,0,7);
object_idx++;
object[object_idx] = new CGora(1275,725,50*sqrt((float)2),1,4);
object_idx++;
object[object_idx] = new CGora(1325,725,50*sqrt((float)2),1,2);
object_idx++;
object[object_idx] = new CGora(1350,725,25,0,3);
object_idx++;

//kaluza:
         
object[object_idx] = new CWoda(300,175,25,0,11);
object_idx++;       
object[object_idx] = new CWoda(325,175,50*sqrt((float)2),1,12);
object_idx++;   
object[object_idx] = new CWoda(375,175,50*sqrt((float)2),1,15);
object_idx++;   
object[object_idx] = new CWoda(375,225,50*sqrt((float)2),1,19);
object_idx++;   
object[object_idx] = new CWoda(425,225,50*sqrt((float)2),1,15);
object_idx++;   
object[object_idx] = new CWoda(425,275,50*sqrt((float)2),1,18);
object_idx++;   
object[object_idx] = new CWoda(425,300,25,0,17);
object_idx++;   

object[object_idx] = new CWoda(175,950,25,0,16);
object_idx++;       
object[object_idx] = new CWoda(175,975,50*sqrt((float)2),1,18);
object_idx++;   
object[object_idx] = new CWoda(175,1000,25,0,17);
object_idx++;   

object[object_idx] = new CWoda(700,325,25,0,13);
object_idx++;       
object[object_idx] = new CWoda(675,325,50*sqrt((float)2),1,14);
object_idx++;   
object[object_idx] = new CWoda(675,350,25,0,17);
object_idx++;   

object[object_idx] = new CWoda(750,625,25,0,11);
object_idx++;       
object[object_idx] = new CWoda(775,625,50*sqrt((float)2),1,12);
object_idx++;   
object[object_idx] = new CWoda(800,625,25,0,13);
object_idx++; 

object[object_idx] = new CWoda(775,1000,25,0,16);
object_idx++;       
object[object_idx] = new CWoda(775,1025,50*sqrt((float)2),1,18);
object_idx++;          
object[object_idx] = new CWoda(775,1075,50*sqrt((float)2),1,19);
object_idx++;          
object[object_idx] = new CWoda(825,1075,50*sqrt((float)2),1,15);
object_idx++;   
object[object_idx] = new CWoda(825,1100,25,0,17);
object_idx++; 
  

object[object_idx] = new CWoda(1025,350,25,0,16);
object_idx++;      
object[object_idx] = new CWoda(1025,375,50*sqrt((float)2),1,19);
object_idx++;          
object[object_idx] = new CWoda(1075,375,50*sqrt((float)2),1,12);
object_idx++;          
object[object_idx] = new CWoda(1125,375,50*sqrt((float)2),1,20);
object_idx++;   
object[object_idx] = new CWoda(1125,325,50*sqrt((float)2),1,18);
object_idx++;          
object[object_idx] = new CWoda(1125,275,50*sqrt((float)2),1,14);
object_idx++;          
object[object_idx] = new CWoda(1175,275,50*sqrt((float)2),1,12);
object_idx++;   
object[object_idx] = new CWoda(1225,275,50*sqrt((float)2),1,12);
object_idx++;          
object[object_idx] = new CWoda(1275,275,50*sqrt((float)2),1,15);
object_idx++;          
object[object_idx] = new CWoda(1275,300,25,0,17);
object_idx++; 

object[object_idx] = new CWoda(1250,975,25,0,11);
object_idx++;      
object[object_idx] = new CWoda(1275,975,50*sqrt((float)2),1,15);
object_idx++;          
object[object_idx] = new CWoda(1275,1025,50*sqrt((float)2),1,19);
object_idx++;          
object[object_idx] = new CWoda(1325,1025,50*sqrt((float)2),1,15);
object_idx++; 
object[object_idx] = new CWoda(1325,1050,25,0,17);
object_idx++;   

//drzewka:
          
object[object_idx] = new CLas(75,175,50,0,21);
object_idx++; 
object[object_idx] = new CLas(250,300,50,0,21);
object_idx++;   
object[object_idx] = new CLas(275,425,50,0,21);
object_idx++; 
object[object_idx] = new CLas(280,410,50,0,21);
object_idx++;
object[object_idx] = new CLas(275,475,50,0,21);
object_idx++; 
object[object_idx] = new CLas(175,700,50,0,21);
object_idx++; 
object[object_idx] = new CLas(325,875,50,0,21);
object_idx++; 
object[object_idx] = new CLas(375,875,50,0,21);
object_idx++; 
object[object_idx] = new CLas(525,625,50,0,21);
object_idx++; 
object[object_idx] = new CLas(525,975,50,0,21);
object_idx++; 
object[object_idx] = new CLas(675,225,50,0,21);
object_idx++; 
object[object_idx] = new CLas(925,125,50,0,21);
object_idx++; 
object[object_idx] = new CLas(875,275,50,0,21);
object_idx++; 
object[object_idx] = new CLas(875,975,50,0,21);
object_idx++; 
object[object_idx] = new CLas(825,675,50,0,21);
object_idx++; 
object[object_idx] = new CLas(825,875,50,0,21);
object_idx++; 
object[object_idx] = new CLas(975,975,50,0,21);
object_idx++; 
object[object_idx] = new CLas(1125,625,50,0,21);
object_idx++;
object[object_idx] = new CLas(1175,175,50,0,21);
object_idx++;
object[object_idx] = new CLas(1175,325,50,0,21);
object_idx++;
object[object_idx] = new CLas(1175,825,50,0,21);
object_idx++;
object[object_idx] = new CLas(1375,250,50,0,21);
object_idx++;
object[object_idx] = new CLas(1375,900,50,0,21);
object_idx++;
object[object_idx] = new CLas(1450,1050,50,0,21);
object_idx++;
object[object_idx] = new CLas(1410,590,50,0,21); //moje drzewo!! :)
object_idx++;
}
for(int i=0;i<5;i++){
 bonus[i]=new CBonus(rand()%1600,rand()%1200,i,i);
 bonus[i]->Wybuch();
}
}
//funkcje tank
CTank::CTank(int BM, int X, int Y,int kol,char* nick)
{   
 bm_id=BM;

 strcpy(name,nick);
 tank_id=kol;   
 x=(float)X; y=(float)Y; phi=(float)PI/4;
 przekatna=50*sqrt((float)2);  //?? trzeba ustalic
 
 score=0;                
 HP=300; armor=0;
 weapon_id=0;     
 iloscM=0; iloscL=0;
 step=4.5;
 step_id=0;      
 speed=1;      
 dmg_min=90; dmg_max=150;
 shot_time=0;
 speed_time=0;
 shot_reload=0;
 bonus_speed=0;   
}
 /**
 * Funkcja CTank::Jazda(int i) operuje zmienna step_id odpowiedzialna za wykonywanie ruchu
   Funkcja jest wywo³ywana po wcisnieciu klawisza W S i przekazywane do wewnatrz jest 1 lub -1
   Nastepnie zwiekszamy step_id o ta wartosc i sprawdzane jest, czy nie wykroczyla poza zbior wartosci {-1,0,1}
 */
void CTank::Jazda(int i)
{     
 step_id+=i;
 if(step_id<-1) 
  {
   step_id=-1;
  }
  if(step_id>1) 
  {
   step_id=1;
  }       
}
 /**
 * Funkcja CTank::Mina() tworzy nowa mine jesli liczbaM gracza jest wieksza od zera
   Funkcja jest wywo³ywana po wcisnieciu klawisza M
   Nastepnie obliczamy wspolrzedne postawienia miny, jesli czolg: stoi lub jedzie do przodu to mina stawiana jest za czolgiem, jesli sie cofa- przed 
 */
void CTank::Mina()
{

 if(iloscM>0)
  {
   float bok=przekatna/sqrt((float)2);         
   float dx=x-step_id*(bok/2+(float)0.5)*cos(phi+(float)PI/4); 
   float dy=y-step_id*(bok/2+(float)0.5)*sin(phi+(float)PI/4);
   if(step_id==0) //jesli stoi
    {
     dx=x-(bok/2+(float)0.5)*cos((float)PI+phi+(float)PI/4); 
     dy=y-(bok/2+(float)0.5)*sin((float)PI+phi+(float)PI/4);                 
    }                  
   miny[miny_idx]=new CMina(dx,dy,6);  //nowy element-mina    
   iloscM--;          
   miny_idx++;           
  }
}
 /**
 * Funkcja CTank::Obrazenia(int DMG) zadaje obrazenia i zwraca wartosc 1 jesli czolg ulegl zniszczeniu
   Funkcja jest wywo³ywana po kolizji czolgu z pociskiem lub mina;
   Nastepnie sprawdza armor i zadaje obrazenia. Jak obrazenia przekraczaja armor, to obrazenia przechodza na HP i sprawdza, czy czolg zostal zniszczony
 */
int CTank::Obrazenia(int DMG)  
{
 if(armor>=0)
  { 
   armor-=DMG; 
  }
 if(armor<=0)
  { 
   HP+=armor;
   armor=0; 
  } 
 if(HP<=0)
  { 
   HP=0;       
   Wybuch();
   return 1;
  }  
 return 0;
}

 /**
 * Funkcja CTank::Obrot(int i) operuje zmienna phi odpowiedzialna za kat obrotu czolgu
   Funkcja jest wywo³ywana po wcisnieciu klawisza A D i przekazywane do wewnatrz jest 1 lub -1
   Nastepnie zmieniamy phi o i*PI/8
   Jesli nastapi kolizja to cofa czolg do poprzedniego polozenia
 */
void CTank::Obrot(int i) // i: 1(lewo) lub -1(prawo)     
{
 phi+=i*(float)PI/8;

if(phi<0)phi+=2*(float)PI;
if(phi>15/8*PI)phi-=2*(float)PI;

 if(Kolizja()==1)
  {
   phi-=i*(float)PI/8;
  }
 else{ if(i==-1){
if(bm_id==15)bm_id=0;
else bm_id++;
 }
 else{
if(bm_id==0)bm_id=15;
else bm_id--;
 }}
}
 /**
 * Funkcja CTank::Przesun() przesuwa czolg i sprawdza, czy wystapila kolizja
   Funkcja jest wywo³ywana przy kazdym cyklu programowym
   Nastepnie zmieniamy polozenie srodka (x,y) czolgu zaleznie, czy wykonywany jest ruch, w jakim kierunku i z jaka predkoscia
   Jesli nastapi kolizja to cofa czolg do poprzedniego polozenia
 */
void CTank::Przesun()
{ 
 x+=(speed)*(step)*(step_id)*cos((float)PI/4+phi);
 y+=(speed)*(step)*(step_id)*sin((float)PI/4+phi);
 if(Kolizja()==1)
  {
   x-=(speed)*(step)*(step_id)*cos((float)PI/4+phi);
   y-=(speed)*(step)*(step_id)*sin((float)PI/4+phi);
  }             
}    
 /**
 * Funkcja CTank::Strzelaj() tworzy nowy pocisk
   Funkcja jest wywo³ywana po wcisnieciu klawisza SPACE
   Nastepnie jesli "pocisk jest w komorze" generuje pocisk o wspolrzednych na koncu lufy
   Zalacza "przeladowanie pocisku", i jesli aktywna bronia byl laser i sie skoncyzla amunicja to zmienia na normalna bron
 */
void CTank::Strzelaj()
{     
 float bok=przekatna/sqrt((float)2);   
 if(shot_reload==0)
  {     
   shot[shot_idx]= new CPocisk(bm_id+weapon_id*16, x+(bok/2)*cos((float)PI+phi+(float)PI/4), y+(bok/2)*sin((float)PI+phi+(float)PI/4), (float)PI+phi+(float)PI/4, dmg_min+rand()%(dmg_max-dmg_min)+weapon_id*50, tank_id);        
   shot_idx++;
   shot_reload=1;
   shot_time=(unsigned long)(clock()/1000)+2;
   if(weapon_id==1) {iloscL--; }
   if(iloscL==0) {weapon_id=0; }   
  } 
}

 /**
 * Funkcja CTank::Wybuch() jesli czolg ulegnie zniszczeniu to zmienia jego polozenie
   Funkcja jest wywo³ywana jesli HP czolgu osiadnie wartosc zero
   Nastepnie resetuje zmienne czolgu oprocz score i nick
 */
void CTank::Wybuch()
{
 do                            /// szuka nowej lokacji tak, aby czolg z niczym nie kolidowal
  {
   x=(float)(rand()%1600);        
   y=(float)(rand()%1200);         
  } while(Kolizja()==1);         
 HP=300; armor=0;
 weapon_id=0;     
 iloscM=0; iloscL=0;
 step_id=0;      
 speed=1;      
 dmg_min=90; dmg_max=150;
 shot_time=0;
 speed_time=0;
 shot_reload=0;
 bonus_speed=0;    
} 

 /**
 * Funkcja CTank::ZmianaBroni(int i) zmienia aktywana bron, za co jest odpowiedzialna zmienna weapon_id
   Funkcja jest wywo³ywana po wcisnieciu Q lub E
   Jesli Q to zmienia bron na normalna, a jesli E, to sprawdza liczbe amunicji lasera jesli jest ona wieksza od zera to zmienia bron na laser
 */
void CTank::ZmianaBroni(int i)
{
 if(i==0) { weapon_id=0; }
 if(i==1)
  {
   if(iloscL>0)
    {  
     weapon_id=1;
    }
  }                       
}     

 /**
 * Funkcja int CTank::Kolizja()sprawdza, czy czolg koliduje z jakims innym elementem na mapie
   Funkcja jest wywo³ywana przy kazdym kroku
 */
int CTank::Kolizja() //zwraca 1 gdy kolizja zaistnieje;
{
 float vx, vy, c, bok, alfa, dphi, pomX, pomY;      
 for(int i=0; i<player_idx; i++)                  /// sprawdzenie kazdego czolgu na mapie
 ///Polega ona na sprawdzaniu wierzcholkow badanych dwoch czolgow, jesli wierzcholek 1 znajduje sie w drugim albo odwrotnie, to zaistnieje kolizja
  {
   if(player[i]!=this) /// nie mozna kolidowac z samym soba;
    {                                                         
     for(int iv=0; iv<4; iv++)
      {                  
       vx=x+(przekatna/2)*cos(phi+iv*(float)PI/2);     /// wspolrzetna x jednego z wierzcholkow
       vy=y+(przekatna/2)*sin(phi+iv*(float)PI/2);     /// wspolrzetna y jednego z wierzcholkow                  
       c=sqrt(pow(vy-player[i]->y,2)+pow(vx-player[i]->x,2)); /// odleglosc miedzy wierzcholkiem jednego a srodkiem druiego czolgu;
       bok=(player[i]->przekatna)/sqrt((float)2);
       alfa=atan((vy-player[i]->y)/(vx-player[i]->x)); /// kat miedzy wierzcholkiem a srodkiem tankow                
       if(vx<(player[i]->x))
        { 
         alfa=(float)PI+alfa; 
        }   
       dphi=(float)PI/4-(player[i]->phi);                    
       pomX=(player[i]->x)+c*cos(alfa+dphi);
       pomY=(player[i]->y)+c*sin(alfa+dphi);
       if(pomX>=((player[i]->x)-(bok/2)) && pomX<=((player[i]->x)+(bok/2)))
        {
         if(pomY>=((player[i]->y)-(bok/2)) && pomY<=((player[i]->y)+(bok/2)))
          {
           return 1;
          }   
        }                                         
      } 
     for(int vi=0; vi<4; vi++)
      {                  
       vx=player[i]->x+(player[i]->przekatna/2)*cos(player[i]->phi+vi*(float)PI/2); 
       vy=player[i]->y+(player[i]->przekatna/2)*sin(player[i]->phi+vi*(float)PI/2);   
       c=sqrt(pow(vy-y,2)+pow(vx-x,2));
       bok=(przekatna)/sqrt((float)2);
       alfa=atan((vy-y)/(vx-x));
       if(vx<x)
        { 
         alfa=(float)PI+alfa; 
        }   
       dphi=(float)PI/4-(phi);                    
       pomX=x+c*cos(alfa+dphi);
       pomY=y+c*sin(alfa+dphi);
       if(pomX>=(x-(bok/2)) && pomX<=(x+(bok/2)))
        {
         if(pomY>=(y-(bok/2)) && pomY<=(y+(bok/2)))
          {
           return 1;
          }   
        }                                                                              
      } 
    }        
  }
 for(int j=0; j<object_idx; j++)  /// ta czesc dotyczy obiektow na mapie, jak zaistnieje kolizja z obiektem sprawdza konkretna wart.kolizyjna i dokonuje odpowiednich zmian
  {         
   if(object[j]->kol_id==0 || object[j]->kol_id==1 || object[j]->kol_id==2) /// woda, zniszczony las; las; gory;
    {                         
     if(object[j]->figure==0) /// jesli figura jest okrag
      {                        
       c=sqrt(pow((object[j]->y)-y,2)+pow((object[j]->x)-x,2));                   
     bok=przekatna/sqrt((float)2);    
       alfa=atan(((object[j]->y)-y)/((object[j]->x)-x));     
       if(object[j]->x<x) 
        { 
         alfa=(float)PI+alfa; 
        }                     
       dphi=(float)PI/4-phi;                    
       pomX=x+(c-object[j]->skladowa)*cos(alfa+dphi);
       pomY=y+(c-object[j]->skladowa)*sin(alfa+dphi);                                                           
       if(pomX>=(x-bok/2) && pomX<=(x+bok/2))
        {
         if(pomY>=(y-bok/2) && pomY<=(y+bok/2))
          {
           return 1;          
          } 
        }               
      }
     if(object[j]->figure==1) /// jesli figura jest kwadrat
      {                                                         
       for(int iv=0; iv<4; iv++)
        {                  
         vx=x+(przekatna/2)*cos(phi+iv*(float)PI/2);
         vy=y+(przekatna/2)*sin(phi+iv*(float)PI/2);              
         c=sqrt(pow(vy-object[j]->y,2)+pow(vx-object[j]->x,2));
         bok=(object[j]->skladowa)/sqrt((float)2);
         alfa=atan((vy-object[j]->y)/(vx-object[j]->x));              
         if(vx<(object[j]->x))
          { 
           alfa=(float)PI+alfa; 
          }                      
         pomX=(object[j]->x)+c*cos(alfa);
         pomY=(object[j]->y)+c*sin(alfa);
         if(pomX>=((object[j]->x)-(bok/2)) && pomX<=((object[j]->x)+(bok/2)))
          {
           if(pomY>=((object[j]->y)-(bok/2)) && pomY<=((object[j]->y)+(bok/2)))
            {
             return 1;
            }   
          }                                         
        } 
       for(int vi=0; vi<4; vi++)
        {                  
         vx=object[j]->x+(object[j]->skladowa/2)*cos(vi*(float)PI/2); 
         vy=object[j]->y+(object[j]->skladowa/2)*sin(vi*(float)PI/2);   
         c=sqrt(pow(vy-y,2)+pow(vx-x,2));
         bok=(przekatna)/sqrt((float)2);
         alfa=atan((vy-y)/(vx-x));
         if(vx<x)
          { 
           alfa=(float)PI+alfa; 
          }   
         dphi=(float)PI/4-(phi);                    
         pomX=x+c*cos(alfa+dphi);
         pomY=y+c*sin(alfa+dphi);
         if(pomX>=(x-(bok/2)) && pomX<=(x+(bok/2)))
          {
           if(pomY>=(y-(bok/2)) && pomY<=(y+(bok/2)))
            {
             return 1;
            }   
          }                                                                              
        } 
      }
    }                                                           
  }     
 for(int b=0; b<5; b++)
  {
   if(bonus[b]->kol_id==4) /// bonus, zdefiniowany jako pkt na mapie
    {
     c=sqrt(pow((bonus[b]->y)-y,2)+pow((bonus[b]->x)-x,2));                   
     bok=przekatna/sqrt((float)2);    
     alfa=atan(((bonus[b]->y)-y)/((bonus[b]->x)-x));     
     if(bonus[b]->x<x) 
      { 
       alfa=(float)PI+alfa; 
      }                     
     dphi=(float)PI/4-phi;                    
     pomX=x+c*cos(alfa+dphi);
     pomY=y+c*sin(alfa+dphi);                                                           
     if(pomX>=(x-bok/2) && pomX<=(x+bok/2))
      {
       if(pomY>=(y-bok/2) && pomY<=(y+bok/2))
        {
         if(bonus[b]->bonus_id==0) 
          { 
           HP+=50;
           if(HP>300) {HP=300;} 
          }                  
         if(bonus[b]->bonus_id==1) 
          { 
           HP+=150;
           if(HP>300) {HP=300;} 
          }                  
         if(bonus[b]->bonus_id==2) 
          { 
           armor+=100;
          }                  
         if(bonus[b]->bonus_id==3) 
          { 
           speed=1.5;
           bonus_speed=1;
           speed_time=(unsigned int)(clock()/1000)+20;
          }                  
         if(bonus[b]->bonus_id==4) 
          { 
           iloscM=iloscM+5;
          }                 
         if(bonus[b]->bonus_id==5) 
          { 
           iloscL=iloscL+10;
          }                 
         bonus[b]->Wybuch();
         return 0;     
        } 
      }    
    } 
  }
 for(int m=0; m<miny_idx; m++)
  {
   if(miny[m]->kol_id==3) /// mina, zdefiniowana jako punkt na mapie
    {                          
     c=sqrt(pow((miny[m]->y)-y,2)+pow((miny[m]->x)-x,2));                   
     bok=przekatna/sqrt((float)2);    
     alfa=atan(((miny[m]->y)-y)/((miny[m]->x)-x));     
     if(miny[m]->x<x) 
      { 
       alfa=(float)PI+alfa; 
      }                     
     dphi=(float)PI/4-phi;                    
     pomX=x+c*cos(alfa+dphi);
     pomY=y+c*sin(alfa+dphi);                                                           
     if(pomX>=(x-bok/2) && pomX<=(x+bok/2))
      {
       if(pomY>=(y-bok/2) && pomY<=(y+bok/2))
        {
         Obrazenia(150);
         bonus_speed=1;
         speed=0.75;
         speed_time=(unsigned long)(clock()/1000)+10;
         miny[m]->Wybuch();                          
         return 0;          
        } 
      }               
    }
  }
 return 0;           
}

// funkcje obiekt
CBonus::CBonus(int X, int Y, int BONUS,int BM)
{
 object_id=object_idx;                   
 figure=0;       
 x=(float)X; y=(float)Y;  
 skladowa=0;
 kol_id=4;
 bonus_id=BONUS;
 bm_id=BM;               
}                   

CGora::CGora(float X, float Y, float SKLADOWA, int FIGURE,int BM)
{
 object_id=object_idx;  
 figure=FIGURE;       
 x=X; y=Y;  
 skladowa=SKLADOWA;
 kol_id=2;
 bonus_id=-1;
 bm_id=BM;
} 

CLas::CLas(float X, float Y, float SKLADOWA,int FIGURE,int BM)
{
 object_id=object_idx;  
 figure=0;       
 x=X; y=Y;  
 skladowa=SKLADOWA/2;
 kol_id=1;
 bonus_id=-1;
 bm_id=BM;
}

CMina::CMina(float X, float Y,int BM)
{
 object_id=miny_idx;  
 figure=BM;       
 x=X; y=Y;  
 skladowa=0;
 kol_id=3;
 bonus_id=-1;
 bm_id=BM;
}

CWoda::CWoda(float X, float Y, float SKLADOWA, int FIGURE,int BM)
{
 object_id=object_idx;  
 figure=FIGURE;       
 x=X; y=Y;  
 skladowa=SKLADOWA;
 kol_id=0;
 bonus_id=-1;
 bm_id=BM;                     
}

//Wybuchy:
/**
* Funkcja CBonus::Wybuch() generuje bonus w losowym miejscu na mapie 
  Funkcja jest wywolywana po zebraniu bonusa
  Nastepnie generuje go w innym miejscu, jesli zaistnieje kolizja, to powtarza operacje
*/
void CBonus::Wybuch()
{
 do
  {
   x=(float)(rand()%1600);        
   y=(float)(rand()%1200); 
   bonus_id=rand()%6;
   bm_id=bonus_id;
  } while(Kolizja()==1);     
}                

/**
* Funkcja CLas::Wybuch() pali las i zmienia jego wartosc kolizyjna, ze pociski moga przezen przelatywac
  Funkcja jest wywolywana kolizji drzewa z pociskiem
  Nastepnie zmienia bitmape i wartosc kolizyjna obiektu
*/
void CLas::Wybuch()
{       

 las_temp[las_idx]=object_id;
 las_idx++;
 kol_id=0;                   
}

void CMina::Wybuch()
{
/// Funkcja usuwa mine i nastepne w tablicy cofa o jedno miejsce wstecz
 for(int i=object_id; i<miny_idx; i++)
  {
   miny[i]=NULL;         
   miny[i]=miny[i+1];
  }
 miny[miny_idx]=NULL;
 miny_idx--;
}
/// Funkcja CBonus::Kolizja() sprawdza czy podczas generowania nowego bonusu na mapie sprawdza, czy z niczym nie koliduje;
int CBonus::Kolizja()
{
 float bok, alfa, pomX, pomY;       
	float c;
 for(int j=0; j<object_idx; j++)     
  {     
   if(object[j]->kol_id==0 || object[j]->kol_id==1 || object[j]->kol_id==2)
    { 
     if(object[j]->figure==0)
      {
       c=sqrt(pow(y-object[j]->y,2)+pow(x-object[j]->x,2));
       if((c-10)<=object[j]->skladowa)
        {    
         return 1; 
        }   
      } 
     if(object[j]->figure==1)
      {
       c=sqrt(pow(y-object[j]->y,2)+pow(x-object[j]->x,2)); //odleglosc pocisku od srodka czolgu;
        {         
         bok=(object[j]->skladowa)/sqrt((float)2);
         alfa=atan((y-object[j]->y)/(x-object[j]->x));          
         if(x<object[j]->x) 
          { 
           alfa=(float)PI+alfa; 
          } 
         pomX=object[j]->x+c*cos(alfa);
         pomY=object[j]->y+c*sin(alfa);              
         if(pomX>=(object[j]->x-bok/2-10) && pomX<=(object[j]->x+bok/2+10))
          {
           if(pomY>=(object[j]->y-bok/2-10) && pomY<=(object[j]->y+bok/2+10))
            {                             
             return 1; 
            }
		  }
        }                 
      }              
    }
  } 
 return 0;
}


//smieci, czyli funkcje nie potrzebne, musialem zadeklarowac, bo mi sie nie kompilowalo:         
int CGora::Kolizja() {return 0;} 
int CLas::Kolizja() {return 0;} 
int CMina::Kolizja() {return 0;} 
int CWoda::Kolizja() {return 0;}
void CGora::Wybuch() {}
void CWoda::Wybuch() {}
// funkcje pocisk
CPocisk::CPocisk(int BM, float X, float Y, float PHI, int DMG, int TANK)
{

 bm_id=BM;            
 shot_id=shot_idx;                      
 step=(float)10;           
 step_id=50;        
 dmg=DMG;
 x=X; y=Y;
 phi=PHI;
 tank=TANK;
}

 /**
   Funkcja int CPocisk::Kolizja() sprawdza, czy pocisk koliduje z jakims obiektem na mapie
   Funkcja jest wywo³ywana podczas zmiany polozenia pocisku
 */ 
int CPocisk::Kolizja()
{
 float c, bok, alfa, dphi, pomX, pomY;               
 for(int i=0; i<player_idx; i++) /// sprawdzenie kazdego czolgu na mapie
  {
	  if(player[i]->tank_id!=tank) /// nie mozna ustrzelic samego siebie;
    {            
     c=sqrt(pow(y-player[i]->y,2)+pow(x-player[i]->x,2)); /// odleglosc pocisku od srodka czolgu;
      {         
       bok=(player[i]->przekatna)/sqrt((float)2);
       alfa=atan((y-player[i]->y)/(x-player[i]->x));          
       if(x<player[i]->x) 
        { 
			
         alfa=(float)PI+alfa; 
        }            
       dphi=(float)PI/4-(player[i]->phi);                    
       pomX=player[i]->x+c*cos(alfa+dphi);
       pomY=player[i]->y+c*sin(alfa+dphi);              
       if(pomX>=(player[i]->x-bok/2) && pomX<=(player[i]->x+bok/2))
        {
         if(pomY>=(player[i]->y-bok/2) && pomY<=(player[i]->y+bok/2))
          {                         
           if(player[i]->Obrazenia(dmg)==1)
            {  
             for(int g=0; g<player_idx; g++)
			  {
               if(player[g]->tank_id==tank)
    			{
                 player[g]->score++;                
				}            
			  }
            }
           return 1;
          }
        }                 
      }      
    }  
  }
 for(int j=0; j<object_idx; j++)     
  {
   if(object[j]->kol_id==1) /// kolizja dla lasu;
    {                       
     c=sqrt(pow(y-object[j]->y,2)+pow(x-object[j]->x,2)); /// odleglosc pocisku od srodka obiektu;
     if(c<=object[j]->skladowa)
      {
       object[j]->Wybuch();       
       return 1; 
      }                
    }
   if(object[j]->kol_id==2)  /// kolizja dla gor
    {
     if(object[j]->figure==0) /// jesli fugura jest okrag
      {                  
       c=sqrt(pow(y-object[j]->y,2)+pow(x-object[j]->x,2));          
       if(c<=object[j]->skladowa)
        {                   
         return 1; 
        }                                    
      }
     if(object[j]->figure==1)  /// jesli figura jest kwadrat
      {
       c=sqrt(pow(y-object[j]->y,2)+pow(x-object[j]->x,2));
        {         
         bok=(object[j]->skladowa)/sqrt((float)2);
         alfa=atan((y-object[j]->y)/(x-object[j]->x));          
         if(x<object[j]->x) 
          { 
           alfa=(float)PI+alfa; 
          } 
         pomX=object[j]->x+c*cos(alfa);
         pomY=object[j]->y+c*sin(alfa);              
         if(pomX>=(object[j]->x-bok/2) && pomX<=(object[j]->x+bok/2))
          {
           if(pomY>=(object[j]->y-bok/2) && pomY<=(object[j]->y+bok/2))
            {                             
             return 1; 
            }
		  }
        }                 
      }                    
    }                                             
  }   
return 0;}       

 /**
 * Funkcja int CPocisk::Lot() zmienia polozenie obiektu na mapie
   Funkcja jest wywo³ywana przy kazdym kroku zegarowym
   Jesli zaistnieje kolizja, lub pocisk wykona okreslona liczbe krokow to jest niszczony
 */ 
void CPocisk::Lot()
{
 step_id--;    
 x+=step*cos(phi);
 y+=step*sin(phi);
 
 if(Kolizja()==1 || step_id==0 ) { Wybuch(); return;}                              
}          

 /**
 * Funkcja int CPocisk::Wybuch() usuwa pocisk z tamblizy i zamienia go z ostatnim ten zas zeruje
   Funkcja jest wywolywana jesli pocisk ulegnie zniszczeniu
 */ 
void CPocisk::Wybuch()
{
 shot_idx--; 
 shot[shot_idx]->shot_id=shot_id;
 shot[shot_id]=shot[shot_idx];
 shot[shot_idx]=NULL;         
}      

//watki
//!Watek wysylania informacji o czolgach, minach, bonusach, pociskach i zniszczonych drzewach
/**
*W watku zostaje stworzona tablica gniazd do ktorych podlacza sie kazdy klijent
nastepie odbywa siê nasluchiwanie czy odbyl sie na gniazdach ruch,
jezeli tak to wysyla za pomoca struktur STank, SMina, SPocisk, SBonus
informacje o ka¿dym z tankow, min, pociskow, bonusow po kolei
oraz tablice indeksow zniszczonych drzew
*/
UINT watek_down(LPVOID params)
		{
int k;///<zmienna pomocnicza
SOCKET GniazdoSerwera;///<gniazdo serwera
GniazdoSerwera = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
if ( GniazdoSerwera == INVALID_SOCKET ) {
AfxMessageBox("Invalid socket") ;
WSACleanup();
} 

sockaddr_in service;
service.sin_family = AF_INET;
service.sin_addr.s_addr = ADDR_ANY;
service.sin_port = htons( 10001 );
if ( bind( GniazdoSerwera, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR ) {
printf( "bind() failed.\n" );
closesocket(GniazdoSerwera);
}
fd_set TablicaGniazd, TablicaGniazdTest;///<tablice gniazd
sockaddr_in sinRemote;
int nAddrSize = sizeof(sinRemote);
listen(GniazdoSerwera,14); //tworzy kolejkê
FD_ZERO(&TablicaGniazd); //czysci tablice gniazd
FD_SET(GniazdoSerwera,&TablicaGniazd); //dodaje gniazdo serwera do tablicy gniazd
while(1){ //nieskonczona pêta serwera
TablicaGniazdTest=TablicaGniazd;
  if (select(0, &TablicaGniazdTest, (fd_set*)NULL, (fd_set*)NULL, 0) > 0) {
      //// Cos sie stalo na jednym z gniazd.
  if (FD_ISSET(GniazdoSerwera, &TablicaGniazdTest)) { //nowe po³¹czenie
       SOCKET sd = accept(GniazdoSerwera, (sockaddr*)&sinRemote,&nAddrSize);
if (sd != INVALID_SOCKET) {
FD_SET(sd,&TablicaGniazd); //dodanie gniazda do tablicy



}
 else {     
                 return 0;
          }}
else{ //poszukiwanie gniazda na którym wyst¹pi³ ruch
	for(int i=0;i<TablicaGniazdTest.fd_count ;i++)
if(FD_ISSET(TablicaGniazdTest.fd_array[i],&TablicaGniazdTest))
{
SOCKET m_socket=TablicaGniazdTest.fd_array[i];
unsigned long odczytano=0;
ioctlsocket(m_socket,FIONREAD,&odczytano);
if(odczytano==0)
{
closesocket(m_socket);
FD_CLR(m_socket,&TablicaGniazd);
}

if(odczytano==NULL) //po³¹czenie zamkniete
{
closesocket(m_socket);
FD_CLR(m_socket,&TablicaGniazd);
}
else
{
STank nad_tank;/**< \brief wysylany czolg
*
* zmienna do ktorej sa kopiowane wszystkie informacje o tanku ktore maja zostac przeslane
a nastepnie zmienna zostaje przeslana
*/
SMina nad_mina;/**< \brief wysylana mina
*
* zmienna do ktorej sa kopiowane wszystkie informacje o minie ktore maja zostac przeslane
a nastepnie zmienna zostaje przeslana
*/
SPocisk nad_shot;/**< \brief wysylany pocisk
*
* zmienna do ktorej sa kopiowane wszystkie informacje o pocisku ktore maja zostac przeslane
a nastepnie zmienna zostaje przeslana
*/
SBonus nad_bonus;/**< \brief wysylany bonus
*
* zmienna do ktorej sa kopiowane wszystkie informacje o bonusie ktore maja zostac przeslane
a nastepnie zmienna zostaje przeslana
*/
	recv(m_socket,(char*)&k,sizeof(k),0);

	send(m_socket,(char*)&player_idx,sizeof(player_idx),0);
	for(int i=0;i<player_idx;i++){
        if((player[i]->speed_time-(clock()/1000))<=0)
		 {
		  nad_tank.speed_time=0;
		 }
		else
		 {
          nad_tank.speed_time=player[i]->speed_time-(clock()/1000);
		 }
		nad_tank.bm_id=player[i]->bm_id;
		nad_tank.tank_id=player[i]->tank_id;
		nad_tank.x=player[i]->x;
		nad_tank.y=player[i]->y;
		nad_tank.score=player[i]->score;
		nad_tank.HP=player[i]->HP;
		nad_tank.armor=player[i]->armor;
		nad_tank.weapon_id=player[i]->weapon_id;
		nad_tank.iloscM=player[i]->iloscM;
		nad_tank.iloscL=player[i]->iloscL;
		nad_tank.speed=player[i]->speed;
	send(m_socket,(char*)&nad_tank,sizeof(nad_tank),0);}

	send(m_socket,(char*)&shot_idx,sizeof(shot_idx),0);
	for(int i=0;i<shot_idx;i++){
		nad_shot.bm_id=shot[i]->bm_id;
		nad_shot.x=shot[i]->x;
		nad_shot.y=shot[i]->y; 
		send(m_socket,(char*)&nad_shot,sizeof(nad_shot),0);}

	send(m_socket,(char*)&miny_idx,sizeof(miny_idx),0);
	for(int i=0;i<miny_idx;i++){
		nad_mina.x=miny[i]->x;
		nad_mina.y=miny[i]->y;
		send(m_socket,(char*)&nad_mina,sizeof(nad_mina),0);}

	for(int i=0;i<5;i++){
		nad_bonus.bm_id=bonus[i]->bm_id;
		nad_bonus.x=bonus[i]->x;
		nad_bonus.y=bonus[i]->y;
		send(m_socket,(char*)&nad_bonus,sizeof(nad_bonus),0);}

	send(m_socket,(char*)&las_idx,sizeof(las_idx),0);
	send(m_socket,(char*)&las_temp,sizeof(las_temp),0);

int max=0;///<zmienna pomocnicza przy sprawdzaniu czy ktoryc gracz nie osiagnol limitu fragow
for(int i=0;i<player_idx;i++){
if(max<player[i]->score)max=player[i]->score;
}
if(max==temp_frag)temp_end++;


}}}}}
		}

//!Watek pobierania informacji o dzialaniach gracza
/**
*W watku zostaje stworzona tablica gniazd do ktorych podlacza sie kazdy klijent
nastepie odbywa siê nasluchiwanie czy odbyl sie na gniazdach ruch,
gdy nastapi ruch na ktoryms gniezdzie odbierane zostaja 2 wiadomosci
id gracza oraz id funkcji ktora gracz chce wywolac
*/
UINT watek_up(LPVOID params)
		{
			SOCKET GniazdoSerwera;///<gniazdo servera
GniazdoSerwera = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
if ( GniazdoSerwera == INVALID_SOCKET ) {
AfxMessageBox("Invalid socket") ;
WSACleanup();
} 

sockaddr_in service;
service.sin_family = AF_INET;
service.sin_addr.s_addr = ADDR_ANY;
service.sin_port = htons( 10002 );
if ( bind( GniazdoSerwera, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR ) {
printf( "bind() failed.\n" );
closesocket(GniazdoSerwera);
}
listen(GniazdoSerwera, 14 );
fd_set TablicaGniazd, TablicaGniazdTest;///<tablice gniazd
sockaddr_in sinRemote;
int nAddrSize = sizeof(sinRemote);
listen(GniazdoSerwera,14); //tworzy kolejkê
FD_ZERO(&TablicaGniazd); //czysci tablice gniazd
FD_SET(GniazdoSerwera,&TablicaGniazd); //dodaje gniazdo serwera do tablicy gniazd
while(1){ //nieskonczona pêta serwera
TablicaGniazdTest=TablicaGniazd;
  if (select(0, &TablicaGniazdTest, (fd_set*)NULL, (fd_set*)NULL, 0) > 0) {
      //// Cos sie stalo na jednym z gniazd.
  if (FD_ISSET(GniazdoSerwera, &TablicaGniazdTest)) { //nowe po³¹czenie
       SOCKET sd = accept(GniazdoSerwera, (sockaddr*)&sinRemote,&nAddrSize);
if (sd != INVALID_SOCKET) {
FD_SET(sd,&TablicaGniazd); //dodanie gniazda do tablicy



}
 else {     
                 return 0;
          }}
else{ //poszukiwanie gniazda na którym wyst¹pi³ ruch
	for(int i=0;i<TablicaGniazdTest.fd_count ;i++)
if(FD_ISSET(TablicaGniazdTest.fd_array[i],&TablicaGniazdTest))
{
SOCKET m_socket=TablicaGniazdTest.fd_array[i];
u_long odczytano=0;
ioctlsocket(m_socket,FIONREAD,&odczytano);
if(odczytano==0)
{
closesocket(m_socket);
FD_CLR(m_socket,&TablicaGniazd);
}

if(odczytano==NULL) //po³¹czenie zamkniete
{
closesocket(m_socket);
FD_CLR(m_socket,&TablicaGniazd);
}
else
{
	int temp_tank_id;///<zmienna pomocnicza 
	recv(m_socket,(char*)&up_id,sizeof(up_id),0);
	recv(m_socket,(char*)&temp_tank_id,sizeof(temp_tank_id),0);

	for(int i=0;i<player_idx;i++)
	{
		if(temp_tank_id==player[i]->tank_id){
			switch(up_id){
				case 'w': player[i]->Jazda(-1);break;
				case 's': player[i]->Jazda(1);break;
				case 'a': player[i]->Obrot(-1);break;
				case 'd': player[i]->Obrot(1);break;
				case 32: player[i]->Strzelaj();break;
				case 'm': player[i]->Mina();break;
				case 'q': player[i]->ZmianaBroni(0);break;
				case 'e': player[i]->ZmianaBroni(1);break;
			}}
	}

}}}}}
		}

//!Watek wysylania wiadomosci czatu
/**
*zostaje stworzone gniazdo z ktorym klijenci lacza sie pojedynczo
gdy klijent sie polaczy zostaje najpierw odczytana wiadomosc,
wedlog ktorej sprawdzane zostaje co ma zostac do klijenta wyslane
ilosc wiadomosci na serwerze czy konkretna wiadomosc,
a pozniej jest to wykonywane
*/
UINT watek_czat_send(LPVOID params)
		{
sRamka odb;///<odbierana wiadomosc
sRamka nadd;///<wysylana wiadomosc
SOCKET czat_send_sock;///<gniazdo serwera
czat_send_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
if ( czat_send_sock == INVALID_SOCKET ) {
AfxMessageBox("Invalid socket");
WSACleanup();
return 0;
} 

sockaddr_in service;
service.sin_family = AF_INET;
service.sin_addr.s_addr = ADDR_ANY;
service.sin_port = htons( 10004 );
if ( bind( czat_send_sock, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR ) {
AfxMessageBox( "bind() failed.\n" );
closesocket(czat_send_sock);
return 0;
}int max=8;
if ( listen( czat_send_sock, max ) == SOCKET_ERROR )AfxMessageBox( "bind() failed.\n" );

    while (1) {
		static SOCKET AcceptSocket;
           AcceptSocket = SOCKET_ERROR;
    while ( AcceptSocket == SOCKET_ERROR )
          {
          AcceptSocket = accept( czat_send_sock, NULL, NULL );
          }
	recv(AcceptSocket,(char*)&odb,sizeof(odb),0);
 
	switch(odb.id) {
           case 2 :{
nadd.id=1;
nadd.rozm=czat_idx;
send(AcceptSocket,(char*)&nadd,sizeof(nadd),0);
closesocket(AcceptSocket);
                    };break;
           case 3 :{
if(nadd.rozm<=czat_idx)
{
strcpy(nadd.tekst,czat[odb.rozm%100]);
nadd.rozm=sizeof(czat[odb.rozm%100]);
send(AcceptSocket,(char*)&nadd,sizeof(nadd),0);
closesocket(AcceptSocket);
}           
           else {
nadd.id=-1;
send(AcceptSocket,(char*)&nadd,sizeof(nadd),0); 
closesocket(AcceptSocket);
}             
};break;
}}  

    return 0;
		}


//!Watek odbierania wiadomosci czatu
/**
*zostaje stworzone gniazdo z ktorym klijenci lacza sie pojedynczo
gdy klijent sie polaczy zostaje odebrana wiadomosc i dodana do tablicy wiadomosci czatu
*/
UINT watek_czat(LPVOID params)
{
	sRamka odb;///< odbierana wiadomosc

SOCKET czat_sock;///<gniazdo servera
czat_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
if ( czat_sock == INVALID_SOCKET ) {
AfxMessageBox("Invalid socket");
WSACleanup();
return 0;
} 

sockaddr_in service;
service.sin_family = AF_INET;
service.sin_addr.s_addr = ADDR_ANY;
service.sin_port = htons( 10003 );
if ( bind( czat_sock, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR ) {
AfxMessageBox( "bind() failed.\n" );
closesocket(czat_sock);
return 0;
}int max=2;
if ( listen( czat_sock, max ) == SOCKET_ERROR )AfxMessageBox( "bind() failed.\n" );
    while (1) {
		static SOCKET AcceptSocket;
           AcceptSocket = SOCKET_ERROR;
    while ( AcceptSocket == SOCKET_ERROR )
          {
          AcceptSocket = accept( czat_sock, NULL, NULL );
          }

        recv(AcceptSocket,(char*)&odb,sizeof(odb),0);
		strcpy(czat[czat_idx%100],odb.tekst);
		czat_idx++;

	
		closesocket(AcceptSocket);
	}  
    return 0;
}

//!Watek dolaczania nowego gracza
/**
*zostaje stworzone gniazdo z ktorym klijenci lacza sie pojedynczo
gdy klijent sie polaczy najpierw zostaje odebrana wiadomosc z informacja
o kolorze gracza oraz jego nicku, nastepnie zostaje wyslana informacja czy serwer jest pelen,
czy kolor jest zajety lub czy wszystko jest ok, i na koncu wysylane zostaja id mapy oraz limit fragow
*/
UINT watek_dolacz(LPVOID params)
{
SOCKET dolacz_sock;///<gniazdo servera
dolacz_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
if ( dolacz_sock == INVALID_SOCKET ) {
AfxMessageBox("Invalid socket");
WSACleanup();
return 0;
} 
sockaddr_in service;
service.sin_family = AF_INET;
service.sin_addr.s_addr = ADDR_ANY;
service.sin_port = htons( 10000 );
if ( bind( dolacz_sock, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR ) {
AfxMessageBox( "bind() failed.\n" );
closesocket(dolacz_sock);
return 0;
}int max=5;
if ( listen( dolacz_sock, max ) == SOCKET_ERROR )AfxMessageBox( "bind() failed.\n" );

    while (1) {
		
		static	SOCKET AcceptSocket;
           AcceptSocket = SOCKET_ERROR;

    while ( AcceptSocket == SOCKET_ERROR )
          {
          AcceptSocket = accept( dolacz_sock, NULL, NULL );
          }
		char odb_nick[20];///<odbiera nick gracza
		int odb_kolor;///<odbiera kolor gracza
		recv(AcceptSocket,(char*)&odb_kolor,sizeof(odb_kolor),0);
		recv(AcceptSocket,(char*)&odb_nick,sizeof(odb_nick),0);
		nad=0;
		if(player_idx==0){nad=0;}
		else {
			for(int i=0;i<player_idx;i++){
				if (odb_kolor==player[i]->tank_id){	nad=1;}
			}}
		if(player_idx==10){nad=2;}
		if(nad==0){
				int a=rand()%4;
				int b=rand()%3;
				player[player_idx]=new CTank(0,100+a*475,100+b*400,odb_kolor,odb_nick);
				player_idx++;
		}
		send(AcceptSocket,(char*)&nad,sizeof(nad),0);
		send(AcceptSocket,(char*)&map_id,sizeof(map_id),0);
		send(AcceptSocket,(char*)&temp_frag,sizeof(temp_frag),0);
		closesocket(AcceptSocket);
	}
    return 0;
}
//!Watek sprawdzania czy zostal osiagniety limit fragow
/**
*
sprawdza czy gracz o maksymalnej liczbie fragow osiagnol liczbe podana w zmiennej frag_limit
jezeli tak to po odczekaniu az wszyscy gracze odbiora ostatnia serje informacji o czolgach itd
wyswietla komunikat ze gra jest skonczona oraz zamyka aplikacje
*/
UINT watek_end(LPVOID params)
{
	do{
int max=0;///<zmienna pomoznicza
for(int i=0;i<player_idx;i++){
if(max<player[i]->score)max=player[i]->score;
}
if(max==temp_frag){
if(temp_end==player_idx){
AfxMessageBox("Limit fragow zostal osiagniety - gra skonczona");
exit(0);}}}while(1);
}

// CSERV dialog
IMPLEMENT_DYNAMIC(CSERV, CDialog)
CSERV::CSERV(CWnd* pParent /*=NULL*/)
	: CDialog(CSERV::IDD, pParent)
	, map_id(0)
	, frag_limit(0)
	, up_id(0)
{
}

CSERV::~CSERV()
{
}

void CSERV::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRACZE, gracze);
	DDX_Control(pDX, IDC_CZATBOX, lista_czat);
}


BEGIN_MESSAGE_MAP(CSERV, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CSERV message handlers
//!wykonuje obliczenia
/**
*gdu wywolywana jest pierwszy raz zostaje zainicjowana mapa oraz rozpoczete wszystkie watki
za kazdym razem zostaje wyczyszczona i ponownie wyswietlona tablica graczy
jezeli sa nowe wiadomosci w tablicy wiadomosci czatu to zostaja one wyswietlone
zostaja wywolane funkcje obliczajace polozenia czolgow oraz pociskow
*/
void CSERV::OnTimer(UINT nIDEvent)
{

	if(temp==0){
	mapa(map_id);
temp_frag=frag_limit;

CWinThread *w_dolacz;
w_dolacz = AfxBeginThread(watek_dolacz,(LPVOID) this);

CWinThread *w_down;
w_down = AfxBeginThread(watek_down,(LPVOID) this);

CWinThread *w_up;
w_up = AfxBeginThread(watek_up,(LPVOID) this);

CWinThread *w_czat_down;
w_czat_down = AfxBeginThread(watek_czat_send,(LPVOID) this);

CWinThread *w_czat;
w_czat = AfxBeginThread(watek_czat,(LPVOID) this);

CWinThread *w_end;
w_end = AfxBeginThread(watek_end,(LPVOID) this);

temp=1;
	}

	gracze.ResetContent();
UpdateData(false);
for(int i=0;i<player_idx;i++)
{
	char gracz_temp[30];///<zmienna pomocnicza do wyswietlania informacji o graczach
	if(player[i]->score<1000){
		char temp3=(int)player[i]->score/100+48;///<zmienna pomoznicza do wyswietlania liczby fragow
char temp2=(int)(player[i]->score%100)/10+48;///<zmienna pomoznicza do wyswietlania liczby fragow
		char temp1=(int)(player[i]->score%10)+48;///<zmienna pomoznicza do wyswietlania liczby fragow
		sprintf(gracz_temp,"%s: %c%c%c",player[i]->name,temp3,temp2,temp1);}
	if(player[i]->score<100){
		char temp2=(int)(player[i]->score%100)/10+48;///<zmienna pomoznicza do wyswietlania liczby fragow
		char temp1=(int)(player[i]->score%10)+48;///<zmienna pomoznicza do wyswietlania liczby fragow
		sprintf(gracz_temp,"%s: %c%c",player[i]->name,temp2,temp1);}
	if(player[i]->score<10){
		char temp1=player[i]->score+48;///<zmienna pomoznicza do wyswietlania liczby fragow
		sprintf(gracz_temp,"%s: %c",player[i]->name,temp1);}
	gracze.AddString(gracz_temp);
UpdateData(false);
}
for(czat_temp;czat_temp<czat_idx;czat_temp++)
{
	lista_czat.AddString(czat[czat_temp]);
}
lista_czat.SetCaretIndex(czat_temp, TRUE);
UpdateData(false);



  for(int p=0; p<player_idx; p++) /// petla przesuwa tanki
   {
    if(player[p]->bonus_speed==1 && player[p]->speed_time<=(clock()/1000)) { player[p]->bonus_speed=0; player[p]->speed=1;} /// sprawdza czy czas bonusowej predkosci sie skonczyl
    if(player[p]->shot_reload==1 && player[p]->shot_time<=(clock()/1000))  { player[p]->shot_reload=0; } /// sprawdza czy czas "przeladowania" sie skonczyl"
    player[p]->Przesun();
   }    
  for(int s=0; s<shot_idx; s++) /// petla przesuwa pociski
   {
    shot[s]->Lot();
   }            
	CDialog::OnTimer(nIDEvent);
}


BOOL CSERV::OnInitDialog()
{
	CDialog::OnInitDialog();

SetTimer(1,100,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSERV::OnBnClickedCancel()
{
exit(-1);
}
