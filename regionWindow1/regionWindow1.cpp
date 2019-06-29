// regionWindow1.cpp: определяет точку входа для приложения.
//
//#include <d3d9.h>
#include "stdafx.h"
#include "regionWindow1.h"
#include "Winuser.h"
#include "string.h"
#include "stdio.h"
#include "windows.h"
#include "Winbase.h"
#include "intsafe.h"
#include "AtlBase.h"
#include "Atlimage.h"
#include "DXGI.h"
#include "ddraw.h"
#include <mmsystem.h>
#include "commdlg.h"
#include <dshow.h>

//#include "ddutil.h"

//#include "direct3D.h"
//#include "afxwin.h"
//#include "text.h"
//using namespace std;


#define MAX_LOADSTRING 100
HRESULT hr1;
ICreateDevEnum *pSysDevEnum = NULL;
int xf=120;
// Глобальные переменные:
HINSTANCE hInst; // текущий экземпляр
BOOL vert;
unsigned __int32 savebuff[1024+24];// массив для записи
TCHAR szTitle[MAX_LOADSTRING];
TCHAR lprname [MAX_LOADSTRING];
TCHAR lprtype[MAX_LOADSTRING];// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];
BYTE lpr[1024*16];
HRESULT dd;
//CDisplay*            g_pDisplay          = NULL;
WINDOWPLACEMENT wplace;
LPDDSURFACEDESC surfdes;
LPDIRECTDRAW ddraw1;
//LPDIRECT3D9EX             g_pD3D       = NULL; // Used to create the D3DDevice
//LPDIRECT3DDEVICE9EX       g_pd3dDevice = NULL; // Our rendering device
LPDIRECTDRAWSURFACE FAR* surf;
char r[30];
char r1[20];
char r2[20];
TCHAR device[10];// имя класса главного окна
POINT rgn1[4]={-10,-10,0,400,300,300,400,0};
HANDLE h1;
OPENFILENAME ofn1;
OPENFILENAME ofn2;
TCHAR filename[1024];
HANDLE hfile;
HANDLE hfile1;
DWORD button_id[1024];//массив для кнопок
bool autoload;
unsigned int portN;
unsigned int runHotKey;
bool trayicon;

COLORREF color;
HRSRC hregion1;DWORD regnsize;
const RGNDATA* lpReg12;
LPVOID lpReg1;
DWORD temp;
HRGN hrgn1;
HGLOBAL hr;
HDC memdc1;
HDC memdc2;
int wx1=0;

//RECT rect1=(0,0,640,480);


	HINSTANCE hInstance;
	HDC memdc;
	HANDLE hbitpict;
	HBITMAP hbit;
	HBITMAP background;
	HBITMAP hbitloadbutton;
	HBITMAP hbitsavebutton;
	HBITMAP hbitminbutton;
	HBITMAP hbitexitbutton;
	HBITMAP hbitselectboxOn;
	HBITMAP hbitselectbox;
	HBITMAP hbit1;
	HBITMAP hbit2;
	HBITMAP hbit3;
	HBITMAP hbit4;
	HBITMAP hbit5;
	HBITMAP hbit6;
	HBITMAP hbit7;
	HBITMAP hbit8;
	HBITMAP hbit9;
	HBITMAP hbitloadbuttonZ;
	HBITMAP hbitsavebuttonZ;
	HBITMAP hbitexitbuttonZ;
	HBITMAP hbitminbuttonZ;
	HBITMAP hbitloadbuttonX;
	HBITMAP hbitsavebuttonX;
	HBITMAP hbitexitbuttonX;
	HBITMAP hbitminbuttonX;
	HBRUSH hbrush;
	int maxX, maxY;

//TCHAR text1[13]="Eah textout!";
// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	CodecDlg(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_REGIONWINDOW1, szWindowClass, MAX_LOADSTRING);
	LoadString(hInst,IDS_STRING104,lprtype,MAX_LOADSTRING);
	LoadString(hInst,IDS_STRING105,lprname,MAX_LOADSTRING);
	hbitloadbutton=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP3));
	hbitsavebutton=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP2));
	hbitexitbutton=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP5));
	hbitminbutton=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP4));
	hbitselectbox=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP6));
	hbitselectboxOn=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP7));
	hbitloadbuttonZ=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP9));
	hbitsavebuttonZ=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP10));
	hbitexitbuttonZ=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP11));
	hbitminbuttonZ=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP12));
	hbitloadbuttonX=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP13));
	hbitsavebuttonX=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP14));
	hbitexitbuttonX=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP15));
	hbitminbuttonX=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP16));
	background=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP1));
	hbit1=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP3));
	hbit2=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP2));
	hbit3=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP13));
	hbit4=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP14));
	hbit5=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP4));
	hbit6=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP16));
	hbit7=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP5));
	hbit8=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP15));
	
	hbit9=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP10));

	//background=LoadBitmap(NULL,L"asm cell.bmp");
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REGIONWINDOW1));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
//  КОММЕНТАРИИ:
//
//    Эта функция и ее использование необходимы только в случае, если нужно, чтобы данный код
//    был совместим с системами Win32, не имеющими функции RegisterClassEx'
//    которая была добавлена в Windows 95. Вызов этой функции важен для того,
//    чтобы приложение получило "качественные" мелкие значки и установило связь
//    с ними.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW |CS_DROPSHADOW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REGIONWINDOW1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindowEx(	NULL	,szWindowClass, szTitle, WS_POPUPWINDOW,
      200, 500,640,580, NULL, NULL, hInstance, NULL);
 
   if (!hWnd)
   {
      return FALSE;
   }
ofn1.hInstance=hInst;
ofn1.hwndOwner=hWnd;
ofn1.lpstrFile=filename;
ofn1.nMaxFile=512;
ofn1.lpstrFileTitle=NULL;
ofn1.nMaxFileTitle=NULL;
ofn1.nFileOffset=NULL;
ofn1.lpstrInitialDir=NULL;
ofn1.Flags=NULL;
ofn1.nFileOffset=NULL;
ofn1.nFileExtension=NULL;
ofn1.lpstrDefExt=NULL;
ofn1.lpfnHook=NULL;
ofn1.lCustData=NULL;
ofn1.lpTemplateName=NULL;
ofn1.lStructSize=sizeof OPENFILENAME;
ofn1.lpstrFilter=NULL;
ofn1.nMaxCustFilter=NULL;
ofn1.lpstrCustomFilter=NULL;
ofn1.nFilterIndex=NULL;
   hregion1=FindResource(hInst,lprname,lprtype);
   if (!hregion1)
   {
	   return FALSE;
   }
   hr=LoadResource(hInst,hregion1);
   if (!hr)
   {
	   return FALSE;
   }
   regnsize=SizeofResource(hInst,hregion1);
	lpReg1=LockResource(hr);
	if(!lpReg1)
	{
		return FALSE;
	}
	
lpReg12=(RGNDATA*)lpReg1;

  
hrgn1=ExtCreateRegion(NULL,regnsize,(const RGNDATA*)lpReg1);


  SetWindowRgn(hWnd,hrgn1,true);
   
  SetTimer(hWnd,1,100,NULL);
  // D3D init===============================
//   if( NULL == (Direct3DCreate9Ex( D3D_SDK_VERSION,&g_pD3D ) ) )
 //       return E_FAIL;
//  D3DPRESENT_PARAMETERS d3dpp;
 //   ZeroMemory( &d3dpp, sizeof(d3dpp) );
 //   d3dpp.Windowed = TRUE;
 //   d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  //  d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
//    Create the D3DDevice
 //   if( FAILED( g_pD3D->CreateDeviceEx( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
 //                                     D3DCREATE_SOFTWARE_VERTEXPROCESSING,
 //                                     &d3dpp,NULL, &g_pd3dDevice ) ) )
  //  {
  //      return E_FAIL;
  //  }
	
//==========================================
dd=DirectDrawCreate(NULL,&ddraw1,NULL);
   dd=ddraw1->SetCooperativeLevel( hWnd, DDSCL_NORMAL );
   ShowWindow(hWnd, nCmdShow);
   //InvalidateRgn(hWnd,CreatePolygonRgn(rgn1,4,WINDING),true);
   UpdateWindow(hWnd);
 hr1 = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
    IID_ICreateDevEnum, (void **)&pSysDevEnum);
if (FAILED(hr1))
{
	
    Beep(440,1000);
	
}
TextOut(memdc,10,100,L"ok",3);
// Obtain a class enumerator for the video compressor category.
IEnumMoniker *pEnumCat = NULL;
hr1 = pSysDevEnum->CreateClassEnumerator(CLSID_VideoCompressorCategory, &pEnumCat, 0);

if (hr1 == S_OK) 
{TextOut(memdc,10,120,L"ok",3);
    // Enumerate the monikers.
    IMoniker *pMoniker = NULL;
    ULONG cFetched;
    while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
    {
        IPropertyBag *pPropBag;
        hr1 = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, 
            (void **)&pPropBag);
        if (SUCCEEDED(hr1))
        {
			TextOut(memdc,10,137,L"ok",3);
            // To retrieve the filter's friendly name, do the following:
            VARIANT varName;
            VariantInit(&varName);
            hr1 = pPropBag->Read(L"FriendlyName", &varName, 0);
            if (SUCCEEDED(hr1))
            {
				xf=xf+16;
				TextOut(memdc,10,xf,varName.bstrVal,SysStringLen(varName.bstrVal));
                // Display the name in your UI somehow.
				
            }
            VariantClear(&varName);

            // To create an instance of the filter, do the following:
            IBaseFilter *pFilter;
            hr1 = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter,
                (void**)&pFilter);
            // Now add the filter to the graph. 
            //Remember to release pFilter later.
            pPropBag->Release();
        }
        pMoniker->Release();
    }
    pEnumCat->Release();
}
pSysDevEnum->Release();

   
   
 
    // Create the D3DDevice
	
   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	HDC hdc1;
	DWORD fl1;
	bool exitb;
	bool saveb;
	bool minb;
	bool loadb;
	fl1=0;
	int wx;
	int wy;
	int button_on=0;
	int sbutton_on=0;
	CImage cimage1;
	
	CHAR* Cwx;
	CHAR* Cwy;
	Cwx=new CHAR [10];
	Cwy=new CHAR [10];
	switch (message)
	{
		color=0;
		case WM_CREATE:
		maxX=GetSystemMetrics(SM_CXSCREEN);
		maxY=GetSystemMetrics(SM_CYSCREEN);
		hdc=GetDC(hWnd);
		memdc=CreateCompatibleDC(hdc);
		hbit=CreateCompatibleBitmap(hdc,maxX,maxY);
		SelectObject(memdc,hbit);
//		hbrush=CreateSolidBrush(9000);
//		SelectObject(memdc,hbrush);
//		PatBlt(memdc,0,0,maxX,maxY,PATCOPY);
		memdc1=CreateCompatibleDC(hdc);
		SelectObject(memdc1,background);
		BitBlt(memdc,4,-16,640,580,memdc1,0,0,SRCCOPY);
		//TextOut(memdc,100,100,L"fgherhyfhgerhbb",15);
		ReleaseDC(hWnd,memdc1);
		break;
		


	case WM_TIMER:
		
		//Beep(2000,50);
		sprintf(r1,"time %d   ms ",wx1);
		TextOut(memdc,390,390,CA2W(r1),13);
		//g_pd3dDevice->IDirect3DDevice9Ex::WaitForVBlank(NULL);
		//ddraw1->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN,NULL);
	//	ddraw1->Initialize(
		
		InvalidateRect(hWnd,NULL,false);

		wx1++;
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	
	case WM_NCRBUTTONDOWN:
	
			Beep(1345,850);
			saveb=((wx>472)&(wx<523)&(wy>500)&(wy<550));
			exitb=((wx>577)&(wx<630)&(wy>500)&(wy<550));
		if (saveb)
		{
			//Beep(1345,50);
		memdc2=CreateCompatibleDC(memdc);
		SelectObject(memdc2,hbitsavebutton);
		BitBlt(memdc,470,500,50,350,memdc2,0,0,SRCCOPY);
		ReleaseDC(hWnd,memdc);
		DeleteDC(memdc2);
		
			if (!GetOpenFileName(&ofn1))
			{
			sprintf(r1,"error: %d",GetLastError());
		TextOut(memdc,100,500,CA2W(r1),24);
			
			}
		}
		if(exitb)
		{
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_NCLBUTTONDOWN:
					saveb=((wx>472)&(wx<523)&(wy>500)&(wy<550));
			exitb=((wx>577)&(wx<630)&(wy>500)&(wy<550));
			minb=((wx>527)&(wx<578)&(wy>500)&(wy<550));
			loadb=((wx>417)&(wx<465)&(wy>500)&(wy<550));
		if (saveb)
		{
			//Beep(1345,50);
		memdc2=CreateCompatibleDC(memdc);
		SelectObject(memdc2,hbit2);
		BitBlt(memdc,470,500,50,350,memdc2,0,0,SRCCOPY);
		ReleaseDC(hWnd,memdc);
		DeleteDC(memdc2);
		
			if (!GetOpenFileName(&ofn1))
			{
			sprintf(r1,"error: %d",GetLastError());
		TextOut(memdc,100,500,CA2W(r1),24);
		TextOut(memdc,100,400,filename,30);
		//PlaySound(filename,NULL,SND_FILENAME|SND_ASYNC);
			}
			cimage1.Load(filename);
			cimage1.TransparentBlt(memdc,100,100,100,100,1);
			hbitpict=LoadImage(hInst,filename,IMAGE_BITMAP,100,100,LR_LOADFROMFILE);
			memdc2=CreateCompatibleDC(memdc);
			SelectObject(memdc2,hbitpict);
			BitBlt(memdc,100,200,100,100,memdc2,0,0,SRCCOPY);
			DeleteDC(memdc2);
			ReleaseDC(hWnd,memdc);
			TextOut(memdc,100,400,filename,30);
		}
		if(loadb)
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, CodecDlg);
		}
		if(exitb)
		{
			DestroyWindow(hWnd);
			break;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;

//=============================================================
	case WM_NCMOUSEMOVE:
		//Beep(1345,1000);
		wx=LOWORD (lParam);
		wy=HIWORD (lParam);
		//SetPixel(memdc,200,200,65535);
		GetWindowPlacement(hWnd,&wplace);
		wx=wx-wplace.rcNormalPosition.left;
		wy=wy-wplace.rcNormalPosition.top;
		//memdc1=CreateCompatibleDC(hdc);
//=================================load_button==========
		if ((wx>417)&(wx<465)&(wy>500)&(wy<550))
		{
			//Beep(1345,50);
		memdc2=CreateCompatibleDC(memdc);
		SelectObject(memdc2,hbit1);
		DeleteDC(memdc2);
		ReleaseDC(hWnd,memdc);

		button_on=1;
		}
		else{
		}
//=============================================================

//===================================save_button===============
if ((wx>472)&(wx<523)&(wy>500)&(wy<550))
		{
			//Beep(1345,50);
		memdc2=CreateCompatibleDC(memdc);
		SelectObject(memdc2,hbit2);
		BitBlt(memdc,470,500,50,350,memdc2,0,0,SRCCOPY);
		DeleteDC(memdc2);
		ReleaseDC(hWnd,memdc);
		sbutton_on=1;
		}
		else{
		memdc2=CreateCompatibleDC(memdc);
		SelectObject(memdc2,hbit4);
		BitBlt(memdc,470,500,50,350,memdc2,0,0,SRCCOPY);
		DeleteDC(memdc2);
		ReleaseDC(hWnd,memdc);
		sbutton_on=0;
		}
//=================================================================


//===================================min_button===============
if ((wx>527)&(wx<578)&(wy>500)&(wy<550))
		{
			//Beep(1345,50);
		memdc2=CreateCompatibleDC(memdc);
		SelectObject(memdc2,hbit5);
		BitBlt(memdc,526,500,50,350,memdc2,0,0,SRCCOPY);
		DeleteDC(memdc2);
		ReleaseDC(hWnd,memdc);
		sbutton_on=1;
		}
		else{
		memdc2=CreateCompatibleDC(memdc);
		SelectObject(memdc2,hbit6);
		BitBlt(memdc,525,500,50,350,memdc2,0,0,SRCCOPY);
		DeleteDC(memdc2);
		ReleaseDC(hWnd,memdc);
		sbutton_on=0;
		}
//=================================================================

//===================================exit_button===============
		exitb=((wx>577)&(wx<630)&(wy>500)&(wy<550));
if (exitb)
		{
			//Beep(1345,50);
		memdc2=CreateCompatibleDC(memdc);
		SelectObject(memdc2,hbit7);
		BitBlt(memdc,581,500,50,350,memdc2,0,0,SRCCOPY);
		DeleteDC(memdc2);
		ReleaseDC(hWnd,memdc);
		sbutton_on=1;
		}
		else{
		memdc2=CreateCompatibleDC(memdc);
		SelectObject(memdc2,hbit8);
		BitBlt(memdc,581,500,50,350,memdc2,0,0,SRCCOPY);
		DeleteDC(memdc2);
		ReleaseDC(hWnd,memdc);
		sbutton_on=0;
		}
//=================================================================


		
		sprintf(r,"cursor pos x=%d y=%d  BO=%d",wx,wy,button_on);
		TextOut(memdc,350,350,CA2W(r),29);
		//memdc2=CreateCompatibleDC(hdc);
		//SelectObject(memdc1,hbitloadbuttonZ);
		//BitBlt(memdc,4,-16,640,580,memdc1,0,0,SRCCOPY);
		
		InvalidateRect(hWnd,NULL,false);
		break;

	case WM_PAINT:
		//ddraw1->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN,h1);
	//	g_pd3dDevice->WaitForVBlank(NULL);
		//ddraw1->GetVerticalBlankStatus(&vert);
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(memdc,hbit);
		BitBlt(hdc,0,0,maxX,maxY,memdc,0,0,SRCCOPY);
	//	memdc2=CreateCompatibleDC(hdc);
	//	SelectObject(memdc2,hbit1);
	//	BitBlt(hdc,10,10,200,200,memdc2,0,0,SRCCOPY);
	//	ReleaseDC(hWnd,memdc2);
		// TODO: добавьте любой код отрисовки...
		//TextOut(hdc,10,10,filename,70);
		//sprintf(device,"display");
		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd,hdc);
		//hdc = BeginPaint(hWnd, &ps);
		//hdc = GetDCEx(hWnd,CreatePolygonRgn(rgn1,4,WINDING), fl1);
		//GetWindowDC(hWnd);
		//SelectObject(memdc,CreateSolidBrush(200));
		//PaintRgn(memdc,CreatePolygonRgn(rgn1,4,ALTERNATE));
		//TextOut(memdc,10,10,(LPCWSTR)"EAH",12);
		//ReleaseDC(hWnd,hdc);
		
		// TODO: добавьте любой код отрисовки...
		//EndPaint(hWnd, &ps);
		//ReleaseDC(hWnd,hdc);
		break;
	case WM_DESTROY:
		//ddraw1->Release();
		KillTimer(hWnd,1);
		PostQuitMessage(0);

		break;
	case WM_NCHITTEST:
		wx=LOWORD (lParam);
		wy=HIWORD (lParam);
		//SetPixel(memdc,200,200,65535);
		GetWindowPlacement(hWnd,&wplace);
		wx=wx-wplace.rcNormalPosition.left;
		wy=wy-wplace.rcNormalPosition.top;
		exitb=((wx>577)&(wx<630)&(wy>500)&(wy<550));
		if(exitb)
		{
			//Beep(1345,200);
			return HTRIGHT;
			break;
		}
		return HTCAPTION;
	default:
			
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
			
			//Beep(1345,1000);
		TextOut(memdc,300,300,L"test mode",10);
		sprintf(r2,"button_on %d",button_on);
		TextOut(memdc,450,450,CA2W(r2),12);

		if (button_on==1)
		{
				//TextOut(memdc,500,400,L"if is working",15);
			//Beep(1345,50);
		memdc2=CreateCompatibleDC(memdc);
		SelectObject(memdc2,hbit1);
		BitBlt(memdc, 413,500,50,50,memdc2,0,0,SRCCOPY);
		DeleteDC(memdc2);
		ReleaseDC(hWnd,memdc);
		InvalidateRect(hWnd,NULL,false);
		}
		if (button_on==0)
		{
			
		memdc2=CreateCompatibleDC(memdc);
		SelectObject(memdc2,hbit3);
		BitBlt(memdc,413,500,50,50,memdc2,0,0,SRCCOPY);
		DeleteDC(memdc2);
		ReleaseDC(hWnd,memdc);

		//InvalidateRect(hWnd,NULL,false);

		}
			
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
// Обработчик сообщений для диалога "выбор кодека".

INT_PTR CALLBACK CodecDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
			case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	case WM_INITDIALOG:
 hr1 = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
    IID_ICreateDevEnum, (void **)&pSysDevEnum);
if (FAILED(hr1))
{
	
    Beep(440,1000);
	
}
TextOut(memdc,10,100,L"ok",3);
// Obtain a class enumerator for the video compressor category.
IEnumMoniker *pEnumCat = NULL;
hr1 = pSysDevEnum->CreateClassEnumerator(CLSID_VideoCompressorCategory, &pEnumCat, 0);

if (hr1 == S_OK) 
{TextOut(memdc,10,120,L"ok",3);
    // Enumerate the monikers.
    IMoniker *pMoniker = NULL;
    ULONG cFetched;
    while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
    {
        IPropertyBag *pPropBag;
        hr1 = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, 
            (void **)&pPropBag);
        if (SUCCEEDED(hr1))
        {
			TextOut(memdc,10,137,L"ok",3);
            // To retrieve the filter's friendly name, do the following:
            VARIANT varName;
            VariantInit(&varName);
            hr1 = pPropBag->Read(L"FriendlyName", &varName, 0);
            if (SUCCEEDED(hr1))
            {
				SendDlgItemMessage(hDlg,IDC_LIST2,LB_ADDSTRING,0,(LPARAM)varName.bstrVal);
                // Display the name in your UI somehow.
				
            }
            VariantClear(&varName);

            // To create an instance of the filter, do the following:
            IBaseFilter *pFilter;
            hr1 = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter,
                (void**)&pFilter);
            // Now add the filter to the graph. 
            //Remember to release pFilter later.
            pPropBag->Release();
        }
        pMoniker->Release();
    }
    pEnumCat->Release();
	}
	pSysDevEnum->Release();
		return (INT_PTR)TRUE;


	}
	return (INT_PTR)FALSE;
}
