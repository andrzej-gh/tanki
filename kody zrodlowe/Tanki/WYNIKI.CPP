// WYNIKI.cpp : implementation file
//

#include "stdafx.h"
#include "Tanki.h"
#include "WYNIKI.h"
#include ".\wyniki.h"



// CWYNIKI dialog

IMPLEMENT_DYNAMIC(CWYNIKI, CDialog)
CWYNIKI::CWYNIKI(CWnd* pParent /*=NULL*/)
	: CDialog(CWYNIKI::IDD, pParent)
{
}

CWYNIKI::~CWYNIKI()
{
}

void CWYNIKI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWYNIKI, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()



///zamyka program
void CWYNIKI::OnBnClickedOk()
{
	exit(0);
}

/**
*deklaracje bitmap
*/
BOOL CWYNIKI::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	///Inicjacja bitmapy odpowiedzialenj za wyswietlanie kolejnosci kolorow wzg wyniku
	BITMAP BM_CZOLG_ID;
    czolg_id.LoadBitmap(BM_TANK_ID);
	czolg_id_maska.LoadBitmap(BM_TANK_ID_MASK);
    czolg_id.GetObject(sizeof(BM_CZOLG_ID),&BM_CZOLG_ID);
    ///Inicjacja tla okna
	BITMAP BM_MIEJSCE;
    miejsce.LoadBitmap(BM_PLACE);
    miejsce.GetObject(sizeof(BM_MIEJSCE),&BM_MIEJSCE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
/**
*rysuje tabele wynikow
*/
void CWYNIKI::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
///Wyswietlanie tla okna z przypisanymi miejscami
 CDC MemDC_PLACE;
 CClientDC Kontekst_Miejsce(this);
 MemDC_PLACE.CreateCompatibleDC(&Kontekst_Miejsce);
 MemDC_PLACE.SelectObject(&miejsce);
 Kontekst_Miejsce.StretchBlt(0,0,240,251,&MemDC_PLACE,0,0,240,251,SRCAND);

	///Sostuje tanki wedlug liczby fragow 
int temp_x[2]; ///Zmienna tymczasowa przechowywujaca informacje o jednym z graczy podczas zamiany w sortowaniu bombelkowym
int temp_player[10][2]; ///Zmienna tymczasowa potrzebna do sortowania bombelkowego

for(int k=0; k<player_idx;k++)
{
	temp_player[k][0]=player[k].score;
	temp_player[k][1]=player[k].tank_id;
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

	// Do not call CDialog::OnPaint() for painting messages
///Wyswietla kolory czolgow w kolejnosci od najwiekszej liczby fragow do najmniejszej
for(int k=0; k<player_idx;k++){
	if(k<5)
	{
WyswietlKolorCzolguId(78,15+k*40,temp_player[k][1]);
}
	else
	{
		WyswietlKolorCzolguId(174,15+k*40-200,temp_player[k][1]);
	}

}
}

void CWYNIKI::WyswietlKolorCzolguId(int x, int y, int z)
{///Wyswietla inony czolgow
 CDC MemDC_TANK_ID;
 CClientDC Kontekst_CzolgId(this);
 MemDC_TANK_ID.CreateCompatibleDC(&Kontekst_CzolgId);
 MemDC_TANK_ID.SelectObject(&czolg_id_maska);
 Kontekst_CzolgId.StretchBlt(x,y,40,40,&MemDC_TANK_ID,z*40,0,40,40,SRCAND);
 MemDC_TANK_ID.SelectObject(&czolg_id);
 Kontekst_CzolgId.StretchBlt(x,y,40,40,&MemDC_TANK_ID,z*40,0,40,40,SRCINVERT);
}
