// Czat.cpp : implementation file
//

#include "stdafx.h"
#include "Tanki.h"
#include "Czat.h"
#include ".\czat.h"

char czat[500][100]; ///<tablica wiadomosci czatu
// CCzat dialog
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

int temp=0;///<zmienna pomoznicza do sciagania wiadomosci



IMPLEMENT_DYNAMIC(CCzat, CDialog)
CCzat::CCzat(CWnd* pParent /*=NULL*/)
	: CDialog(CCzat::IDD, pParent)
	, tekst(_T(""))
{
}

CCzat::~CCzat()
{
}

void CCzat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TXT, tekst);
	DDX_Control(pDX, IDC_LISTA, lista_czat);
}


BEGIN_MESSAGE_MAP(CCzat, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
//	ON_WM_TIMER()
ON_WM_TIMER()
END_MESSAGE_MAP()


// CCzat message handlers
///wysylanie wiadomosci
/**
*tworzy gniazdo, laczy sie z serwerem, wysyla ramke z wiadomoscia
*/
void CCzat::OnBnClickedOk()
{
	sRamka nad; ///<wysylana wiadomosc
	UpdateData(true);
	nad.id=1;

    char temp[100];
    sprintf(temp,"<%s: > %s",nick,(LPCTSTR)tekst);
    strcpy(nad.tekst,temp);
   


	nad.rozm=sizeof(nad.tekst);
	if(nad.tekst!=NULL){
	SOCKET sock;///<gniazdo
   sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
   if ( sock == INVALID_SOCKET ) AfxMessageBox("Invalid socket");    
              
   sockaddr_in clientService;
   clientService.sin_family = AF_INET; 
   clientService.sin_addr.s_addr = inet_addr(serv_ip); 
   clientService.sin_port = htons( 10003 );          

   //connect:
if ( connect( sock, (SOCKADDR*) &clientService, sizeof(clientService) ) ==SOCKET_ERROR)
 { 
AfxMessageBox("Nie znaleziono serwera"); 
WSACleanup(); 
return ;
}
		send(sock,(char*)&nad,sizeof(nad),0);
		closesocket(sock);
		}
	tekst.Empty();
	UpdateData(false);
}


///deklaruje Timer
BOOL CCzat::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetTimer(2,100,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
///Pobieranie wiadomosci
/**
*tworzy gniazdo, laczy sie z serwerem, wysyla zapytanie o ilosc wiadomosci, odbiera informacje
o ilosci wiadomosci, rozlacza i laczy sie na nowo przy pobieraniu kazdej nie odebranej jeszcze wiadomosci
(wysylaniu informacji ktora wiadomosc chce pobrac i jej odebraniu)
*/
void CCzat::OnTimer(UINT nIDEvent)
{
sRamka nad,odb;///< ramki wysylana i odbierana
SOCKET czat_down_sock;///<gniazdo serwera
	czat_down_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( czat_down_sock == INVALID_SOCKET ) AfxMessageBox("Invalid socket");        
	sockaddr_in clientService;
	clientService.sin_family = AF_INET; 
	clientService.sin_addr.s_addr = inet_addr(serv_ip); 
	clientService.sin_port = htons( 10004 );          
	  //connect:
	if ( connect( czat_down_sock, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR) 
	{ 
	AfxMessageBox("Nie znaleziono serwera"); 
	WSACleanup(); 
	return ;
	}

	nad.id=2;
		send(czat_down_sock, (char*)&nad, sizeof(nad), 0);
		recv(czat_down_sock, (char*)&odb, sizeof(odb), 0);
      closesocket(czat_down_sock);
	int todb=odb.rozm;
	  for(;todb>temp;temp++)
	  {
		  nad.id=3;
      nad.rozm=temp;

    SOCKET czat_down_sock;/// gniazdo serwera
	czat_down_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( czat_down_sock == INVALID_SOCKET ) AfxMessageBox("Invalid socket");        
	sockaddr_in clientService;
	clientService.sin_family = AF_INET; 
	clientService.sin_addr.s_addr = inet_addr(serv_ip); 
	clientService.sin_port = htons( 10004 );          

	  //connect:
      if ( connect( czat_down_sock, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR) 
       { 
        WSACleanup(); 
        return ;
       }
      //              
      send(czat_down_sock, (char*)&nad, sizeof(nad), 0);
      recv(czat_down_sock, (char*)&odb, sizeof(odb), 0);
      closesocket(czat_down_sock);
	  UpdateData(true);
	  lista_czat.AddString(odb.tekst);
 lista_czat.SetCaretIndex(temp, TRUE); 
	  UpdateData(false);
	  
	  }








	CDialog::OnTimer(nIDEvent);
}
