// Gra.cpp : implementation file
//

#include "stdafx.h"
#include "Tanki.h"
#include "Gra.h"
#include "Dolacz.h"
#include "Czat.h"
#include ".\cobiekt.h"
#include ".\cgora.h"
#include ".\clas.h"
#include ".\cwoda.h"
#include <math.h>
#include ".\gra.h"
#include ".\MeinMenu.h"
#include "WYNIKI.h"
#define PI 3.14159265

int frag_limit;///<przechowuje limit fragow

int ik;///<
SOCKET down;///<gniazdo pobierania informacji o graczach, minach, pociskach, bonusach i zniszczonych lasach
SOCKET up;///<gniazdo wysylania informacji o dzialaniu ktore gracz chce podjac

int object_idx=0;     ///<ilosc obiektow na mapie; 
CObiekt* object[500]; ///<tabela obiektow;
int player_idx=0;     ///<liczba aktywnych graczy;
int shot_idx=0;       ///<liczba pociskow w powietrzu
int miny_idx=0;     ///<liczba min na mapie;

	int temp_id;///<zmienna pomoznicza
	int las_temp[100];///<tablica identyfikatorow zniszczonych lasow
	int las_idx;///<ilosc zniszczonych lasow
	int map_id;///<identyfikator mapy ktora zostala zalozona na serwerze
	char serv_ip[20];///<IP serwera
	int player_id;///<ilosc graczy na serwerze
	char up_id;///<zmienna pomocnicza przy wysylaniu informacji o dzialaniu



//! struktura przesylana w komunikacji polozenie i id bitmapy bonosow
struct SBonus
{
int bm_id;///<id bitmapy
float x,y;///<wspolrzedne
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


	STank player[12];///<tablica graczy
	SMina mina[100];///<tablica min
	SPocisk shot[100];///<tablica pociskow
	SBonus bonus[5];///<tablica bonusow


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
 skladowa=SKLADOWA;
 kol_id=1;
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


void CLas::Wybuch()
{              
 bm_id=22;
	//animacja, zmiana bitmapy na zniszczony las;
 kol_id=0;                   
}

int CGora::Kolizja() {return 0;} 
int CLas::Kolizja() {return 0;}
int CWoda::Kolizja() {return 0;}
void CGora::Wybuch() {}
void CWoda::Wybuch() {}

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

object[object_idx] = new CGora(1575,(float)1175,50*sqrt((float)2),1,10);
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
       
object[object_idx] = new CGora(25+9*50,5*50,50,0,6);
object_idx++;       
object[object_idx] = new CGora(25+9*50,25+5*50,50*sqrt((float)2),1,9);
object_idx++;
object[object_idx] = new CGora(500,25+5*50,50,0,3);
object_idx++;

object[object_idx] = new CGora(300,525,50,0,1);
object_idx++;       
object[object_idx] = new CGora(325,525,50*sqrt((float)2),1,2);
object_idx++;
object[object_idx] = new CGora(350,525,50,0,3);
object_idx++;

object[object_idx] = new CGora(275,1025,50,0,6);
object_idx++;       
object[object_idx] = new CGora(275,1050,50*sqrt((float)2),1,9);
object_idx++;
object[object_idx] = new CGora(325,1050,50*sqrt((float)2),1,2);
object_idx++;
object[object_idx] = new CGora(350,1050,50,0,3);
object_idx++;

object[object_idx] = new CGora(475,650,50,0,6);
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
object[object_idx] = new CGora(625,750,50,0,7);
object_idx++;

object[object_idx] = new CGora(21*50+25,300,50,0,7);
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
object[object_idx] = new CGora(975,450,50,0,7);
object_idx++;

object[object_idx] = new CGora(950,725,50,0,1);
object_idx++;
object[object_idx] = new CGora(950,725,50,0,3);
object_idx++;

object[object_idx] = new CGora(1275,750,50,0,7);
object_idx++;
object[object_idx] = new CGora(1275,725,50*sqrt((float)2),1,4);
object_idx++;
object[object_idx] = new CGora(1325,725,50*sqrt((float)2),1,2);
object_idx++;
object[object_idx] = new CGora(1350,725,50,0,3);
object_idx++;

//kaluza:
         
object[object_idx] = new CWoda(300,175,50,0,11);
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
object[object_idx] = new CWoda(425,300,50,0,17);
object_idx++;   

object[object_idx] = new CWoda(175,950,50,0,16);
object_idx++;       
object[object_idx] = new CWoda(175,975,50*sqrt((float)2),1,18);
object_idx++;   
object[object_idx] = new CWoda(175,1000,50,0,17);
object_idx++;   

object[object_idx] = new CWoda(700,325,50,0,13);
object_idx++;       
object[object_idx] = new CWoda(675,325,50*sqrt((float)2),1,14);
object_idx++;   
object[object_idx] = new CWoda(675,350,50,0,17);
object_idx++;   

object[object_idx] = new CWoda(750,625,50,0,11);
object_idx++;       
object[object_idx] = new CWoda(775,625,50*sqrt((float)2),1,12);
object_idx++;   
object[object_idx] = new CWoda(800,625,50,0,13);
object_idx++; 

object[object_idx] = new CWoda(775,1000,50,0,16);
object_idx++;       
object[object_idx] = new CWoda(775,1025,50*sqrt((float)2),1,18);
object_idx++;          
object[object_idx] = new CWoda(775,1075,50*sqrt((float)2),1,19);
object_idx++;          
object[object_idx] = new CWoda(825,1075,50*sqrt((float)2),1,15);
object_idx++;   
object[object_idx] = new CWoda(825,1100,50,0,17);
object_idx++; 
  

object[object_idx] = new CWoda(1025,350,50,0,16);
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
object[object_idx] = new CWoda(1275,300,50,0,17);
object_idx++; 

object[object_idx] = new CWoda(1250,975,50,0,11);
object_idx++;      
object[object_idx] = new CWoda(1275,975,50*sqrt((float)2),1,15);
object_idx++;          
object[object_idx] = new CWoda(1275,1025,50*sqrt((float)2),1,19);
object_idx++;          
object[object_idx] = new CWoda(1325,1025,50*sqrt((float)2),1,15);
object_idx++; 
object[object_idx] = new CWoda(1325,1050,50,0,17);
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

}
/**
*Na poczatku zostaje wywolane okno dolaczania do gry, jezeli sie nie udalo polaczyc a okno zostalo zamknite
to program zostaje zamkniety
kopiowanie informacji o limicie fragow oraz id mapy
stworzenie mapy, zadeklarowanie bitmap
polaczenie z serwerem za pomoca gniazda down oraz up
zadeklarowanie Timera
*/
BOOL CGra::OnInitDialog()
{
	CDialog::OnInitDialog();


	CDolacz okno_dolacz;///<okno dolaczania do gry
	okno_dolacz.DoModal();
	strcpy(serv_ip,okno_dolacz.serv_ip);
	map_id=okno_dolacz.map_id;
	tank_id=okno_dolacz.kolor;
	strcpy(nick,okno_dolacz.nick);
	mapa(map_id);
    frag_limit=okno_dolacz.frag_limit;
	
	if(frag_limit==0)exit(0);
  
	/**
  *Ponizszy blok deklaraci :
  Inicjuje bitmape sluzaca do wyswietlania obiektu
  Przypisuje zmiennej CBitmap bitmape obiektu
  Przypisuje zmiennej CBitmap bitmape maski
  Pobiera inforamacje o bitmapie
  */

    BITMAP BM_TRAWA; 
	trawa.LoadBitmap(BM_GRASS);  
    trawa_maska.LoadBitmap(BM_GRASS_MASK);
	trawa.GetObject(sizeof(BM_TRAWA),&BM_TRAWA);

	BITMAP BM_CZOLG;
    czolg.LoadBitmap(BM_TANK);
	czolg_maska.LoadBitmap(BM_TANK_MASK);
    czolg.GetObject(sizeof(BM_CZOLG),&BM_CZOLG);
    
	BITMAP BM_OBJEKT;
    objekt.LoadBitmap(BM_OBJECT);
	objekt_maska.LoadBitmap(BM_OBJECT_MASK);
    objekt.GetObject(sizeof(BM_OBJEKT),&BM_OBJEKT);

	BITMAP BM_PREMIA;
    premia.LoadBitmap(BM_BONUS);
	premia_maska.LoadBitmap(BM_BONUS_MASK);
    premia.GetObject(sizeof(BM_PREMIA),&BM_PREMIA);

	BITMAP BM_POCISKI;
    pociski.LoadBitmap(BM_BULLETS);
	pociski_maska.LoadBitmap(BM_BULLETS_MASK);
    pociski.GetObject(sizeof(BM_POCISKI),&BM_POCISKI);

    BITMAP BM_MENU_DOL;
    menu_dol.LoadBitmap(BM_MENU_DOWN);
	menu_dol_maska.LoadBitmap(BM_MENU_DOWN_MASK);
    menu_dol.GetObject(sizeof(BM_MENU_DOWN),&BM_MENU_DOL);

	BITMAP BM_MENU_GORA;
    menu_gora.LoadBitmap(BM_MENU_UP);
	menu_gora_maska.LoadBitmap(BM_MENU_UP_MASK);
    menu_gora.GetObject(sizeof(BM_MENU_GORA),&BM_MENU_GORA);

    BITMAP BM_ZMIENNE;
    menl.LoadBitmap(BM_VARIABLE);
	menl_maska.LoadBitmap(BM_VARIABLE_MASK);
    menl.GetObject(sizeof(BM_ZMIENNE),&BM_ZMIENNE);

	BITMAP BM_CZOLG_ID;
    czolg_id.LoadBitmap(BM_TANK_ID);
	czolg_id_maska.LoadBitmap(BM_TANK_ID_MASK);
    czolg_id.GetObject(sizeof(BM_CZOLG_ID),&BM_CZOLG_ID);


player_id=okno_dolacz.kolor;
//tworzenie soketa do pobierania informacji o graczach


   down = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
   if ( down == INVALID_SOCKET ) AfxMessageBox("Invalid socket");
	sockaddr_in clientService1;
   clientService1.sin_family = AF_INET; 
   clientService1.sin_addr.s_addr = inet_addr(serv_ip); 
   clientService1.sin_port = htons( 10001 );     
    if ( connect( down, (SOCKADDR*) &clientService1, sizeof(clientService1) ) == SOCKET_ERROR) 
     { 
	AfxMessageBox("Nie znaleziono serwera"); 
        WSACleanup(); 
    }



//tworzenie soketa do wysy³ania informacji o ruchu

   up = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
   if ( up == INVALID_SOCKET ) AfxMessageBox("Invalid socket");	
   sockaddr_in clientService2;
   clientService2.sin_family = AF_INET; 
   clientService2.sin_addr.s_addr = inet_addr(serv_ip); 
   clientService2.sin_port = htons( 10002 );     
if ( connect( up, (SOCKADDR*) &clientService2, sizeof(clientService2) ) == SOCKET_ERROR) 
       { 
		AfxMessageBox("Nie znaleziono serwera"); 
        WSACleanup(); 
        return 0;
       }

	SetTimer(1,100,NULL);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


// CGra dialog
IMPLEMENT_DYNAMIC(CGra, CDialog)
CGra::CGra(CWnd* pParent /*=NULL*/)
	: CDialog(CGra::IDD, pParent)
	, tank_id(0)
{
	
}

CGra::~CGra()
{
}

void CGra::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGra, CDialog)
ON_WM_KEYDOWN()
ON_WM_TIMER()
ON_WM_PAINT()
END_MESSAGE_MAP()





/**
*za pomoca switcha wysyla do serwera informacje o dzialaniu gracza
*/
void CGra::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{


///Sterowanie klawiatury
	switch(nChar)
	{
	case 'w': case 'W':
		{

	up_id='w';
	send(up,(char*)&up_id,sizeof(up_id),0);
	send(up,(char*)&tank_id,sizeof(tank_id),0);		
    break;
		}
	case 'a': case 'A':
		{
	up_id='a';
	send(up,(char*)&up_id,sizeof(up_id),0);
	send(up,(char*)&tank_id,sizeof(tank_id),0);
	break;
		}
	case 's': case 'S':
		{
	up_id='s';
	send(up,(char*)&up_id,sizeof(up_id),0);
	send(up,(char*)&tank_id,sizeof(tank_id),0);
	break;
		}
	case 'd': case 'D':
		{
    up_id='d';
	send(up,(char*)&up_id,sizeof(up_id),0);
	send(up,(char*)&tank_id,sizeof(tank_id),0);
	break;
		}
    case VK_SPACE: case '32':
		
		{
	up_id=32;
	send(up,(char*)&up_id,sizeof(up_id),0);
	send(up,(char*)&tank_id,sizeof(tank_id),0);
    break;
		}
	case 'm': case 'M':
		{
    up_id='m';
	send(up,(char*)&up_id,sizeof(up_id),0);
	send(up,(char*)&tank_id,sizeof(tank_id),0);
	break;
		}
	case 'q': case 'Q':
		{
	up_id='q';
	send(up,(char*)&up_id,sizeof(up_id),0);
	send(up,(char*)&tank_id,sizeof(tank_id),0);
	break;
		}
	case 'e': case 'E':
		{
	up_id='e';
	send(up,(char*)&up_id,sizeof(up_id),0);
	send(up,(char*)&tank_id,sizeof(tank_id),0);
	break;
		}
	case 'x': case 'X':
	{
	CMeinMenu okno_menu;
	okno_menu.DoModal();
	break;
	}
	case 'c': case'C':
	{
	CCzat okno_czat;
	strcpy(okno_czat.serv_ip,serv_ip);
	strcpy(okno_czat.nick,nick);
	okno_czat.DoModal();
	break;
	}
	}
	
CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
	
}


/**
*sprawdza czy ktos uzyskal limit fragow, jezeli tak to wyswietla okno wyniki, a nastepnie zamyka program
pobiera z serwera informacje o graczach, minach, pociskach, zniszczonych lasach i bonusach
kopjuje te informacje do tablic struktur STank, SMina, SBonus, SPocisk oraz to tablicy indeksow zniszczonych drzew
wywoluje funkcje OnPaint()
*/
void CGra::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	ik=0;///<zmienna pomoznicza
	STank odb_tank;///<zmienna pomocnicza odbioru czolgow
	SMina odb_mina;///<zmienna pomocnicza odbioru min
	SPocisk odb_shot;///<zmienna pomocnicza odbioru pociskow
	SBonus odb_bonus;///<zmienna pomocnicza odbioru bonusow

int max=0;///<zmienna pomocnicza sprawdzania czy ktos osiagnol limit fragow
for(int i=0;i<player_idx;i++){
if(max<player[i].score)max=player[i].score;
}
if(max==frag_limit){
CWYNIKI okno_wyniki;///<okno wynikow
for(int j=0;j<player_idx;j++){
okno_wyniki.player[j]=player[j];
}
okno_wyniki.player_idx=player_idx;
okno_wyniki.DoModal();
exit(0);
}  
	send(down,(char*)&ik,sizeof(ik),0);

	recv(down,(char*)&player_idx,sizeof(player_idx),0);
	for(int i=0;i<player_idx;i++){
		recv(down,(char*)&odb_tank,sizeof(odb_tank),0);
		player[i].bm_id=odb_tank.bm_id;
		player[i].tank_id=odb_tank.tank_id;
		player[i].x=odb_tank.x;
		player[i].y=odb_tank.y;
		player[i].score=odb_tank.score;
		player[i].HP=odb_tank.HP;
		player[i].armor=odb_tank.armor;
		player[i].weapon_id=odb_tank.weapon_id;
		player[i].iloscM=odb_tank.iloscM;
		player[i].iloscL=odb_tank.iloscL;
		player[i].speed_time=odb_tank.speed_time;
		player[i].speed=odb_tank.speed;
	}

	recv(down,(char*)&shot_idx,sizeof(shot_idx),0);
	for(int i=0;i<shot_idx;i++){
		recv(down,(char*)&odb_shot,sizeof(odb_shot),0);
		shot[i].bm_id=odb_shot.bm_id;
		shot[i].x=odb_shot.x;
		shot[i].y=odb_shot.y;}

	recv(down,(char*)&miny_idx,sizeof(miny_idx),0);
	for(int i=0;i<miny_idx;i++){
		recv(down,(char*)&odb_mina,sizeof(odb_mina),0);
		mina[i].x=odb_mina.x;
		mina[i].y=odb_mina.y;}

	for(int i=0;i<5;i++){
		recv(down,(char*)&odb_bonus,sizeof(odb_bonus),0);
		bonus[i].bm_id=odb_bonus.bm_id;
		bonus[i].x=odb_bonus.x;
		bonus[i].y=odb_bonus.y;}

	recv(down,(char*)&las_idx,sizeof(las_idx),0);
	recv(down,(char*)&las_temp,sizeof(las_temp),0);

	for(int i=0;i<las_idx;i++){
		object[las_temp[i]]->Wybuch();
	}



	OnPaint(); ///Wczytywanie funkcji wyswietlajacej bitmapy
	


	CDialog::OnTimer(nIDEvent);
}
/**
*rysuje po kolej trawe, obiekty mapy, bonusy, pociski, czolgi i elementy interface'u
*/
void CGra::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
if(player_idx>0)  ///Funkcja sprawdza czy na mapie istnieje czolg
	{
	float x, y;
	for(int i=0;i<player_idx;i++)
	{
		if(tank_id==player[i].tank_id)
		{
			temp_id=i;
		}
	}
        /**
		Grupa ta w kolejnosci i analogicznie do nastepnych:
		*Tworzy obiekt kontekstu pamieciowego
		*Tworzy kontekst wewn¹trz klasy pochodz¹cej od CView lub CDialog
		*Tworzy kontekst pamieciowy kompatybilny kontekstem okna
		*Wiaze zmienna skojazona z dana bitmapa z kontekstem pamiêciowym
		*Wyswietla kontekst pamiêciowy na ekranie
        
		*/

	    ///Wyswietla bitmape trawy na ekranie
        CDC MemDC_GRASS;
        CClientDC Kontekst_Grass(this);
        MemDC_GRASS.CreateCompatibleDC(&Kontekst_Grass);
        MemDC_GRASS.SelectObject(&trawa_maska);
        Kontekst_Grass.StretchBlt(0,0,800,600,&MemDC_GRASS,0,0,800,600,SRCAND);
		MemDC_GRASS.SelectObject(&trawa);
        Kontekst_Grass.StretchBlt(0,0,800,600,&MemDC_GRASS,0,0,800,600,SRCINVERT);


	for(int i=0;i<object_idx;i++) ///Petla sprawdza i rysuje w oknie obiekty typu gora ,woda, drzewo dla kazdego elementu znajdujacego sie na planszy
	{
		if(object[i]->x <= (player[temp_id].x + 450) && 
		   object[i]->x >= (player[temp_id].x - 450) &&
		   object[i]->y <= (player[temp_id].y + 350) &&
		   object[i]->y >= (player[temp_id].y - 350) )

		{

			if(object[i]->bm_id <=22)
			{
				switch(object[i]->bm_id)
				
				{
				case 1: x=object[i]->x - player[temp_id].x + 350; y=object[i]->y - player[temp_id].y + 275; break;
				case 2: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				case 3: x=object[i]->x - player[temp_id].x + 400; y=object[i]->y - player[temp_id].y + 275; break;
				case 4: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
			    case 5: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				case 6: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 250; break;
				case 7: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 300; break;
				case 8: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				case 9: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				case 10: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				case 11: x=object[i]->x - player[temp_id].x + 350; y=object[i]->y - player[temp_id].y + 275; break;
				case 12: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				case 13: x=object[i]->x - player[temp_id].x + 400; y=object[i]->y - player[temp_id].y + 275; break;
				case 14: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
			    case 15: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				case 16: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 250; break;
				case 17: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 300; break;
				case 18: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				case 19: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				case 20: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				case 21: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				case 22: x=object[i]->x - player[temp_id].x + 375; y=object[i]->y - player[temp_id].y + 275; break;
				}
///Wyswietla bitmape gory wody lub drzewa w zaleznosci od zmiennej bm_id
 CDC MemDC_OBJECT;
 CClientDC Kontekst_Objekt(this);
 MemDC_OBJECT.CreateCompatibleDC(&Kontekst_Objekt);
 MemDC_OBJECT.SelectObject(&objekt_maska);
 Kontekst_Objekt.StretchBlt((int)x,(int)y,50,50,&MemDC_OBJECT,(object[i]->bm_id*50-50),0,50,50,SRCAND);
 MemDC_OBJECT.SelectObject(&objekt);
 Kontekst_Objekt.StretchBlt((int)x,(int)y,50,50,&MemDC_OBJECT,(object[i]->bm_id*50-50),0,50,50,SRCINVERT);
				}

for(int i=0;i<5;i++)///Petla odpowiedzialna jest za wyswietlanie w oknie wszystkich elementow bonus
{
x=bonus[i].x - player[temp_id].x + 392; 
y=bonus[i].y - player[temp_id].y + 292;
///Wyswietlana jest bitmapa bonusow w zaleznosci od zmiennej bm_id
 CDC MemDC_BONUS;
 CClientDC Kontekst_Premia(this);
 MemDC_BONUS.CreateCompatibleDC(&Kontekst_Premia);
 MemDC_BONUS.SelectObject(&premia_maska);
 Kontekst_Premia.StretchBlt((int)x,(int)y,16,16,&MemDC_BONUS,(bonus[i].bm_id*16),0,16,16,SRCAND);
 MemDC_BONUS.SelectObject(&premia);
 Kontekst_Premia.StretchBlt((int)x,(int)y,16,16,&MemDC_BONUS,(bonus[i].bm_id*16),0,16,16,SRCINVERT);
}	

for(int i=0;i<miny_idx;i++)///Petla odpowiedzialna jest za wyswietlanie w oknie wszystkich obiektow min
{
	x=mina[i].x - player[temp_id].x + 392; 
y=mina[i].y - player[temp_id].y + 292;
///Wyswietla bitmape miny w oknie 
 CDC MemDC_BONUS;
 CClientDC Kontekst_Premia(this);
 MemDC_BONUS.CreateCompatibleDC(&Kontekst_Premia);
 MemDC_BONUS.SelectObject(&premia_maska);
 Kontekst_Premia.StretchBlt((int)x,(int)y,16,16,&MemDC_BONUS,(6*16),0,16,16,SRCAND);
 MemDC_BONUS.SelectObject(&premia);
 Kontekst_Premia.StretchBlt((int)x,(int)y,16,16,&MemDC_BONUS,(6*16),0,16,16,SRCINVERT);
}
		}
	}

	for(int i=0;i<shot_idx;i++)///Petla odpowiedzialna jest za wyswietlanie pociskow jak i lasera w zaleznosci od kata strzalu
	{
		if(shot[i].x <= (player[temp_id].x + 400) && 
		   shot[i].x >= (player[temp_id].x - 400) &&
		   shot[i].y <= (player[temp_id].y + 300) &&
		   shot[i].y >= (player[temp_id].y - 300) )
		{
x=shot[i].x - player[temp_id].x + 400-5;
y=shot[i].y - player[temp_id].y + 300-5; 


CDC MemDC_BULLETS;
 CClientDC Kontekst_Pociski(this);
 MemDC_BULLETS.CreateCompatibleDC(&Kontekst_Pociski);
 MemDC_BULLETS.SelectObject(&pociski_maska);
 Kontekst_Pociski.StretchBlt((int)x,(int)y,10,10,&MemDC_BULLETS,(shot[i].bm_id*10),0,10,10,SRCAND);
 MemDC_BULLETS.SelectObject(&pociski);
 Kontekst_Pociski.StretchBlt((int)x,(int)y,10,10,&MemDC_BULLETS,(shot[i].bm_id*10),0,10,10,SRCINVERT);

		}
	}
	for(int i=0;i<player_idx;i++)///Petla odpowiedzialna jest za wyswietlanie czolgu na mapie idealnie po srodku okna wzg tego punktu przemieszczaja sie inne obiekty na ekranie
	{
        if(player[i].x <= (player[temp_id].x + 364) && 
		   player[i].x >= (player[temp_id].x - 364) &&
		   player[i].y <= (player[temp_id].y + 264) &&
		   player[i].y >= (player[temp_id].y - 264) )  
		{
			x=player[i].x-player[temp_id].x + 364;
			y=player[i].y - player[temp_id].y + 264; 
///Wyswietla bitmape czolgu w oknie wizualnie zmieniajac kat widzianego czolgu za pomoca zmiennej bm_id		
CDC MemDC_TANK;
 CClientDC Kontekst_Czolg(this);
 MemDC_TANK.CreateCompatibleDC(&Kontekst_Czolg);
 MemDC_TANK.SelectObject(&czolg_maska);
 Kontekst_Czolg.StretchBlt((int)x,(int)y,72,72,&MemDC_TANK,(player[i].bm_id*72),player[i].tank_id*72,72,72,SRCAND);
 MemDC_TANK.SelectObject(&czolg);
 Kontekst_Czolg.StretchBlt((int)x,(int)y,72,72,&MemDC_TANK,(player[i].bm_id*72),player[i].tank_id*72,72,72,SRCINVERT);
			
		}
	}
	///Wyswietlana jest bitmapa tla menu dolnego
 CDC MemDC_MENU_DOWN;
 CClientDC Kontekst_Menu_Dol(this);
 MemDC_MENU_DOWN.CreateCompatibleDC(&Kontekst_Menu_Dol);
 MemDC_MENU_DOWN.SelectObject(&menu_dol_maska);
 Kontekst_Menu_Dol.StretchBlt(0,550,800,50,&MemDC_MENU_DOWN,0,0,800,50,SRCAND);
 MemDC_MENU_DOWN.SelectObject(&menu_dol);
 Kontekst_Menu_Dol.StretchBlt(0,550,800,50,&MemDC_MENU_DOWN,0,0,800,50,SRCINVERT);
 ///Wyswietlana jest bitmapa tla menu gornego
 CDC MemDC_MENU_UP;
 CClientDC Kontekst_Menu_Gora(this);
 MemDC_MENU_UP.CreateCompatibleDC(&Kontekst_Menu_Gora);
 MemDC_MENU_UP.SelectObject(&menu_gora_maska);
 Kontekst_Menu_Gora.StretchBlt(0,0,800,50,&MemDC_MENU_UP,0,0,800,50,SRCAND);
 MemDC_MENU_UP.SelectObject(&menu_gora);
 Kontekst_Menu_Gora.StretchBlt(0,0,800,50,&MemDC_MENU_UP,0,0,800,50,SRCINVERT);


///wyswietla punkty hp
///zmienne temp od wysietlania statsow
int temphpa;
int temphpb;
int temphpc;
///Liczba HP rozdzielana jest na skladowe w celu wyswietlenia odpowiedniej bitmapy numerycznej
temphpc=player[temp_id].HP%10;
temphpb=((player[temp_id].HP%100)-temphpc)/10;
temphpa=((player[temp_id].HP-temphpb)-temphpc)/100;


RysujZmienneMen(126,554,temphpa+1);
RysujZmienneMen(153,554,temphpb+1);
RysujZmienneMen(180,554,temphpc+1);
///wyswietla ilosc armora
///Zmienne temp od wysietlania statsow
int tempara;
int temparb;
int temparc;
///Liczba ARMOR rozdzielana jest na skladowe w celu wyswietlenia odpowiedniej bitmapy numerycznej
temparc=player[temp_id].armor%10;
temparb=((player[temp_id].armor%100)-temparc)/10;
tempara=((player[temp_id].armor-temphpb)-temphpc)/100;

RysujZmienneMen(255,554,tempara+1);
RysujZmienneMen(282,554,temparb+1);
RysujZmienneMen(309,554,temparc+1);
///Rysuje ikone broni w zaleznosci od weapon_id wyswietla albo ikone lasera albo rakiety
RysujZmienneMen(344,553,22+player[temp_id].weapon_id); 
///Wyswietla w zaleznosci od posiadanej aktualnie broni, weapon_id, ilosc amunicji lub znak nieskonczonosci
switch(player[temp_id].weapon_id+1)
{
case 1:
	{
RysujZmienneMen(441,553,21);
break;
	}
case 2:
	{
int tempamb;
int tempamc;
///Liczba iloscL(asera) rozdzielana jest na skladowe w celu wyswietlenia odpowiedniej bitmapy numerycznej
tempamc=player[temp_id].iloscL%10;
tempamb=((player[temp_id].iloscL%100)-tempamc)/10;

RysujZmienneMen(441,554,tempamb+1);
RysujZmienneMen(468,554,tempamc+1);
break;

	}
}
///Wyswietla ilosc min
///Zmienne temp od wysietlania statsow
int tempminb;
int tempminc;
///Liczba iloscM(in) rozdzielana jest na skladowe w celu wyswietlenia odpowiedniej bitmapy numerycznej
tempminc=player[temp_id].iloscM%10;
tempminb=((player[temp_id].iloscM%100)-tempminc)/10;

RysujZmienneMen(553,554,tempminb+1);
RysujZmienneMen(580,554,tempminc+1);
///Wyswietla czas trwania przyspieszenia
///Zmienne temp od wysietlania statsow
int tempspb;
int tempspc;
///Liczba speed_time rozdzielana jest na skladowe w celu wyswietlenia odpowiedniej bitmapy numerycznej
tempspc=player[temp_id].speed_time%10;
tempspb=((player[temp_id].speed_time%100)-tempspc)/10;

RysujZmienneMen(666,554,tempspb+1);
RysujZmienneMen(693,554,tempspc+1);
///Wyswiela ilosc frago gracza
///Zmienne temp od wysietlania statsow
int tempscora;
int tempscorb;
int tempscorc;
///Liczba score rozdzielana jest na skladowe w celu wyswietlenia odpowiedniej bitmapy numerycznej
tempscorc=player[temp_id].score%10;
tempscorb=((player[temp_id].score%100)-temparc)/10;
tempscora=((player[temp_id].score-tempscorb)-tempscorc)/100;

RysujZmienneMen(657,3,tempscora+11);
RysujZmienneMen(679,3,tempscorb+11);
RysujZmienneMen(701,3,tempscorc+11);

///Wyswietla bitmape koloru gracza tank_id
WyswietlKolorCzolguId(614,2,player[temp_id].tank_id);
///Wyswietla frag limit  frag_limit ustawiony na serwerze
///Zmienne temp od wysietlania statsow
int tempfragla;
int tempbraglb;
int tempfraglc;
///Liczba frag_limit rozdzielana jest na skladowe w celu wyswietlenia odpowiedniej bitmapy numerycznej
tempfraglc=frag_limit%10;
tempbraglb=((frag_limit%100)-tempfraglc)/10;
tempfragla=((frag_limit-tempbraglb)-tempfraglc)/100;


RysujZmienneMen(131,3,tempfragla+11);
RysujZmienneMen(153,3,tempbraglb+11);
RysujZmienneMen(175,3,tempfraglc+11);

///Sostuje tanki wedlug liczby fragow 
int temp_x[2]; ///Zmienna tymczasowa przechowywujaca informacje o jednym z graczy podczas zamiany w sortowaniu bombelkowym
int temp_player[10][2]; ///Zmienna tymczasowa potrzebna do sortowania bombelkowego

for(int k=0; k<player_idx;k++)///Petla sortujaca bombelkowo graczy wedlug liczby fragow score, temp_player[0][0] jest to gracz na najwyzszym wynikiem
{
	temp_player[k][0]=player[k].score; ///Zmienna przechowuje liczbe fragow
	temp_player[k][1]=player[k].tank_id;///Zmienna przechowuje kolor gracza o danej liczbie fragow
}
for(int j=player_idx-1;j>=0;j--)
{
	for(int i=0;i<j;i++)
	{
		if(temp_player[i][0]<temp_player[i+1][0])
		{
			temp_x[0]=temp_player[i][0];
			temp_x[1]=temp_player[i][1];
			temp_player[i][0]=temp_player[i+1][0];
			temp_player[i][1]=temp_player[i+1][1];
			temp_player[i+1][0]=temp_x[0];
			temp_player[i+1][1]=temp_x[1];
		}
	}
}





///Wyswietla liczbe fragow gracza z najlepszym wynikiem
///Zmienne temp od wysietlania statsow
int tempfirsta;
int tempfirstb;
int tempfirstc;
///Liczba fragow rozdzielana jest na skladowe w celu wyswietlenia odpowiedniej bitmapy numerycznej
tempfirstc=temp_player[0][0]%10;
tempfirstb=((temp_player[0][0]%100)-tempfirstc)/10;
tempfirsta=((temp_player[0][0]-tempfirstb)-tempfirstc)/100;


RysujZmienneMen(326,3,tempfirsta+11);
RysujZmienneMen(348,3,tempfirstb+11);
RysujZmienneMen(370,3,tempfirstc+11);

///Wyswietla liczbe fragow gracza z 2gim wynikiem
///Zmienne temp od wysietlania statsow
int tempseconda;
int tempsecondb;
int tempsecondc;
///Petla zapobiegajaca bledowi powstalemu w chwili gdy na planszy nie ma stworzonego drugiego czolgu
if(player_idx>1){
tempsecondc=temp_player[1][0]%10;
tempsecondb=((temp_player[1][0]%100)-tempsecondc)/10;
tempseconda=((temp_player[1][0]-tempsecondb)-tempsecondc)/100;


RysujZmienneMen(488,3,tempseconda+11);
RysujZmienneMen(510,3,tempsecondb+11);
RysujZmienneMen(532,3,tempsecondc+11);
///Wyswietla kolor gracza z drugim wynikiem 
WyswietlKolorCzolguId(446,2,temp_player[1][1]);
}

else{
tempsecondc=temp_player[0][0]%10;
tempsecondb=((temp_player[0][0]%100)-tempsecondc)/10;
tempseconda=((temp_player[0][0]-tempsecondb)-tempsecondc)/100;


RysujZmienneMen(488,3,tempseconda+11);
RysujZmienneMen(510,3,tempsecondb+11);
RysujZmienneMen(532,3,tempsecondc+11);
///Wyswietla kolor 2giego gracza wedlug fagow
WyswietlKolorCzolguId(446,2,temp_player[0][1]);
}
///Wyswietla kolor 1szego gracza wedlug fragow
WyswietlKolorCzolguId(283,2,temp_player[0][1]);
}
}




	// Do not call CDialog::OnPaint() for painting messages
//}

/// wyswietlanie liczb i znaczkow
/**
*
Rysuje liczby w menu oraz znaczki broni w zaleznosci od wprowadzonej zmiennej "z" wyswietlanyjest fragment bitmapy odpowiadajacy za inny element/**
/param x zmienna odpowiedzialna za polozenie w oknie w plaszczyznie x
/param y zmienna odpowiedzialna za polozenie w oknie w plaszczyznie y
/param z w zaleznosci od potrzeby wyswietla inna czesc bitmapy
*/
void CGra::RysujZmienneMen(int x, int y, int z)
{  
	int ra, rb, rc, rd; //zmienne odpowiadajace za polozenie na bitmapie oraz wielkosc obiektu
	
	switch(z)
	{


	case 1 : {ra=0;rb=0;rc=25;rd=40;break;}
	case 2 : {ra=25;rb=0;rc=25;rd=40;break;}
	case 3 : {ra=50;rb=0;rc=25;rd=40;break;}
	case 4 : {ra=75;rb=0;rc=25;rd=40;break;}
	case 5 : {ra=100;rb=0;rc=25;rd=40;break;}
	case 6 : {ra=0;rb=40;rc=25;rd=40;break;}
	case 7 : {ra=25;rb=40;rc=25;rd=40;break;}
	case 8 : {ra=50;rb=40;rc=25;rd=40;break;}
	case 9 : {ra=75;rb=40;rc=25;rd=40;break;}
	case 10 : {ra=100;rb=40;rc=25;rd=40;break;}
	case 11 : {ra=125;rb=0;rc=22;rd=35;break;}
	case 12 : {ra=147;rb=0;rc=22;rd=35;break;}
	case 13 : {ra=169;rb=0;rc=22;rd=35;break;}
	case 14 : {ra=191;rb=0;rc=22;rd=35;break;}
	case 15 : {ra=213;rb=0;rc=22;rd=35;break;}
	case 16 : {ra=125;rb=35;rc=22;rd=35;break;}
	case 17 : {ra=147;rb=35;rc=22;rd=35;break;}
	case 18 : {ra=169;rb=35;rc=22;rd=35;break;}
	case 19 : {ra=191;rb=35;rc=22;rd=35;break;}
	case 20 : {ra=213;rb=35;rc=22;rd=35;break;}
	case 21 : {ra=0;rb=80;rc=45;rd=45;break;}
	case 22 : {ra=45;rb=80;rc=45;rd=45;break;}
	case 23 : {ra=90;rb=80;rc=45;rd=45;break;}
	
	}
	///Wyswietlana jest bitmapa odpowiedzialna za cyfry oraz ikony broni

CDC MemDC_VARIABLE;
 CClientDC Kontekst_Menl(this);
 MemDC_VARIABLE.CreateCompatibleDC(&Kontekst_Menl);
 MemDC_VARIABLE.SelectObject(&menl_maska);
 Kontekst_Menl.StretchBlt(x,y,rc,rd,&MemDC_VARIABLE,ra,rb,rc,rd,SRCAND);
 MemDC_VARIABLE.SelectObject(&menl);
 Kontekst_Menl.StretchBlt(x,y,rc,rd,&MemDC_VARIABLE,ra,rb,rc,rd,SRCINVERT);
	
}


///Funkcja wyswietlajaca ikone czolgu 
/**
*w menu gornym sluzaca do pokazywania kolejnosci graczy wzg zdobytych fragow 
oraz ikony mowiacej nam o kolorze naszego czolgu
/param x zmienna odpowiedzialna za polozenie w oknie w plaszczyznie x
/param y zmienna odpowiedzialna za polozenie w oknie w plaszczyznie y
/param z w zaleznosci od potrzeby wyswietla inna czesc bitmapy
*/
void CGra::WyswietlKolorCzolguId(int x, int y, int z)
{
///Wyswietlana jest bitmapa czolgu id
 CDC MemDC_TANK_ID;
 CClientDC Kontekst_CzolgId(this);
 MemDC_TANK_ID.CreateCompatibleDC(&Kontekst_CzolgId);
 MemDC_TANK_ID.SelectObject(&czolg_id_maska);
 Kontekst_CzolgId.StretchBlt(x,y,40,40,&MemDC_TANK_ID,z*40,0,40,40,SRCAND);
 MemDC_TANK_ID.SelectObject(&czolg_id);
 Kontekst_CzolgId.StretchBlt(x,y,40,40,&MemDC_TANK_ID,z*40,0,40,40,SRCINVERT);
}
