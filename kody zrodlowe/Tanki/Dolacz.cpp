// Dolacz.cpp : implementation file
//

#include "stdafx.h"
#include "Tanki.h"
#include "Dolacz.h"
#include ".\dolacz.h"
#include "CIP.h"


// CDolacz dialog

	char nad_nick[20];///<zmienna wysylna na serwer, przechowujaca nick gracza
	int nad_kolor;///<zmienna wysylana na serwer, przechowuje kolor gracza


IMPLEMENT_DYNAMIC(CDolacz, CDialog)
CDolacz::CDolacz(CWnd* pParent /*=NULL*/)
	: CDialog(CDolacz::IDD, pParent)
	, nick(_T(""))
	, map_id(0)
	, frag_limit(0)
	, kolor(FALSE)
{

}

CDolacz::~CDolacz()
{
}

void CDolacz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NICK, nick);
	DDX_Radio(pDX, IDC_KOLOR1, kolor);
}


BEGIN_MESSAGE_MAP(CDolacz, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDolacz message handlers

	///dolaczanie do gry
	/**
	*Tworzone jest gniazdo i podlacza sie do serwera
	jezeli jest bledne blad gniazda lub nie moze znalezc serwera
	wyskakuje ponownie okinko wpisywania IP
	Po nawiazaniu polaczenia wysyla na serwer informacje o kolorze i nick
	dostaje informacje zwrotna czy serwer jest pelen lub czy dany kolor nie jest zajety
	oraz identyfikator mapy oraz limit fragow
	jezeli jest zajety wyskakuje alert z taka informacja oraz wyswietla sie ponownie okienko wpisywania IP
	jezeli jest juz gracz o takim kolorze to wyskakuje rowniez alert z taka informacja i mozna zmienic kolor
	gdy wszystko jest ok zostaje wywolana funkcja OnOK() po ktorej okno jest zamkniete i wyswietla sie okno gry
	*/
void CDolacz::OnBnClickedOk()
{
	

	UpdateData(true);
	SOCKET dolacz_sock;///<gniazdo serwera
   dolacz_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
   if ( dolacz_sock == INVALID_SOCKET ) {
	AfxMessageBox("Invalid socket");    
    CCIP okno_ip;///<okno wpisywania IP
	okno_ip.DoModal();
	strcpy(serv_ip,(LPCTSTR)okno_ip.serv_ip);
   }
   sockaddr_in clientService;
   clientService.sin_family = AF_INET; 
   clientService.sin_addr.s_addr = inet_addr(serv_ip); 
   clientService.sin_port = htons( 10000 );          

   //connect:
if ( connect( dolacz_sock, (SOCKADDR*) &clientService, sizeof(clientService) ) ==SOCKET_ERROR)
 { 
AfxMessageBox("Nie znaleziono serwera");     
CCIP okno_ip;///<okno wpisywania IP
okno_ip.DoModal();
strcpy(serv_ip,(LPCTSTR)okno_ip.serv_ip); 
}
else{
		int odb;/** /brief zmienna pomocnicza
				*przechowoje informacje zwrotna czy serwer jest zajety lub istnieje gracz o takim kolorze
				*0 - wszystko ok
				*1 - istnieje gracz o takim kolorze
				*2- serwer jest pelen
				*/
		UpdateData(true);
		strcpy(nad_nick,(LPCTSTR)nick);
		nad_kolor=kolor;
		send(dolacz_sock,(char*)&nad_kolor,sizeof(nad_kolor),0);
		send(dolacz_sock,(char*)&nad_nick,sizeof(nad_nick),0);
		recv(dolacz_sock,(char*)&odb,sizeof(odb),0);
		recv(dolacz_sock,(char*)&map_id,sizeof(map_id),0);
		recv(dolacz_sock,(char*)&frag_limit,sizeof(frag_limit),0);
		closesocket(dolacz_sock);
		switch(odb){
case 0: 	OnOK();break;
case 1:		AfxMessageBox("Istnieje juz gracz o takim kolorze, wybierz inny.");break;
case 2:		{
	AfxMessageBox("Serwer jest pelen, sproboj ponownie pozniej lub wpisz IP innego serwera"); 
    CCIP okno_ip;///<okno wpisywania IP
	okno_ip.DoModal();
	strcpy(serv_ip,(LPCTSTR)okno_ip.serv_ip);
	break;}
		}}
   

}
///wyswietla okno wpisywania IP oraz deklaracja bitmap
BOOL CDolacz::OnInitDialog()
{
	CDialog::OnInitDialog();

	CCIP okno_ip;///<okno wpisywania IP
	okno_ip.DoModal();
	strcpy(serv_ip,(LPCTSTR)okno_ip.serv_ip);

	//rysowany jest wybor kolorow
 //   BITMAP BM_KOLORY;
	///kolory.LoadBitmap(BM_COLORS);
	//kolory.GetObject(sizeof(BM_KOLORY),&BM_KOLORY);
///Inicjacja bitmapy kolorow czolgow do wyboru przy laczeniu sie z serwerem
    BITMAP BM_KOLORY;
	rysuj_kolor.LoadBitmap(BM_COLORS);
	rysuj_kolor_maska.LoadBitmap(BM_COLORS_MASK);
	rysuj_kolor.GetObject(sizeof(BM_KOLORY),&BM_KOLORY);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDolacz::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
///Wyswietlanie bitmap czolgow w oknie
RysujKoloryCzolgow(50,50,1);
RysujKoloryCzolgow(185,50,2);




	// Do not call CDialog::OnPaint() for painting messages
}

/// Rysuje kolory czolgow w menu
void CDolacz::RysujKoloryCzolgow(int x, int y, int z)
{
CDC MemDC_KOLOR;
CClientDC Kontekst_Kolor(this);
MemDC_KOLOR.CreateCompatibleDC(&Kontekst_Kolor);
MemDC_KOLOR.SelectObject(&rysuj_kolor_maska);
Kontekst_Kolor.StretchBlt(x,y,40,200,&MemDC_KOLOR,z*40-40,0,40,200,SRCAND);
MemDC_KOLOR.SelectObject(&rysuj_kolor);
Kontekst_Kolor.StretchBlt(x,y,40,200,&MemDC_KOLOR,z*40-40,0,40,200,SRCINVERT);
}
