// RegionArrayCreator.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "resource.h"
#include "commdlg.h"
#include <stdio.h>

#define MAX_LOADSTRING 100
unsigned __int32 rgndh[8];
unsigned __int32 lpbuf1[8192];
unsigned __int8 lpbuf[8192];
unsigned int Dataoffset;
DWORD numbytes;
DWORD Bwidth;
DWORD Bheght;
unsigned __int8 pixel;
//LONG fill;
unsigned int lineX;
unsigned int lineY;
bool flag;
unsigned int PointCount;
unsigned int count;
BY_HANDLE_FILE_INFORMATION finfo;
HWND hWnd;

DWORD nRgnSize;
DWORD nCount;
RECT rcBound;
DWORD iType;


void opencurfile();
void savecurfile();
void readnextdata();
void setnextcoord();
// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
//TCHAR filename[512];
TCHAR filename[1024];
HANDLE hfile;
HANDLE hfile1;
OPENFILENAME ofn1;
OPENFILENAME ofn2;
//REGIONDATAHEADER
	HDC DC;
	HDC memdc;
	HDC memdc1;
	HBITMAP hbit;
	HBITMAP hbit1;
	HBRUSH hbrush;
	int maxX, maxY;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_REGIONARRAYCREATOR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REGIONARRAYCREATOR));

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

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REGIONARRAYCREATOR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_REGIONARRAYCREATOR);
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
   

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
ofn2=ofn1;
//GetOpenFileName(ofn1);


	switch (message)
	{
	case WM_CREATE:
		maxX=GetSystemMetrics(SM_CXSCREEN);
		maxY=GetSystemMetrics(SM_CYSCREEN);
		hdc=GetDC(hWnd);
		memdc=CreateCompatibleDC(hdc);
		hbit=CreateCompatibleBitmap(hdc,maxX,maxY);
		SelectObject(memdc,hbit);
		hbrush=CreateSolidBrush(400);
		SelectObject(memdc,hbrush);
		PatBlt(memdc,0,0,maxX,maxY,PATCOPY);
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
		case IDM_OPENB:
			GetOpenFileName(&ofn1);
			opencurfile();
			break;
		case IDM_OPSEC:
			GetOpenFileName(&ofn2);
			savecurfile();
			break;

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
		
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc,hbit);
		BitBlt(hdc,0,0,maxX,maxY,memdc,0,0,SRCCOPY);
		// TODO: добавьте любой код отрисовки...
		TextOut(hdc,10,10,filename,70);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
void opencurfile()
{
	numbytes=4096;
	hfile=CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,NULL, OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
//	GetFileInformationByHandle(hfile,&finfo);
//	LPVOID hbit1=calloc(finfo.nFileSizeLow,1);
//	if(!ReadFile(hfile,hbit1,finfo.nFileSizeLow,&finfo.nFileSizeLow,NULL))
//	{return;}
//	DC=GetDC(hWnd);
//	memdc1=CreateCompatibleDC(DC);
//	SelectObject(memdc1,(HBITMAP)hbit1);
//	BitBlt(memdc,40,40,1000,1000,memdc1,0,0,SRCCOPY);
//	ReleaseDC(hWnd,DC);
//	DeleteDC(memdc1);


//	rewind((FILE*)hfile);

	if(!ReadFile(hfile,lpbuf,numbytes,&numbytes,NULL))
	{return;}
//	TextOut(memdc,10,100,lpbuf,100);
	//CloseHandle(hfile);
}
void savecurfile()
{
	bool pointflag;
	int bmpcorr;
	bool bmpcorrflag;
	Dataoffset=WORD MAKEWORD(lpbuf[10],lpbuf[11]);
	Bwidth=WORD MAKEWORD (lpbuf[18],lpbuf[19]);
	Bheght=WORD MAKEWORD (lpbuf[22],lpbuf[23]);
	lineX=0;
	lineY=0;
	PointCount=0;
	flag=false;
	pointflag=false;
	bmpcorr=0;
	bmpcorrflag=false;
	for(count=0;count<Bwidth*Bheght;count++)
	{
		pixel=WORD MAKEWORD(lpbuf[Dataoffset],0);
		//lpbuf1[Dataoffset]=lineX;
		if((pixel!=0) && (flag==false)){
			flag=true;
			//pointflag=true;
			lpbuf1[PointCount]=lineX;
			lpbuf1[PointCount+1]=lineY;
			PointCount=PointCount+2;
		}
		if((pixel==0) && (flag==true)){
			//if ((lineX==0) && (lineY!=0))
			//{lineX=Bwidth;
			//lineY--;
			//pointflag=true;
			//}
			flag=false;
			lpbuf1[PointCount]=lineX-1+1;
			lpbuf1[PointCount+1]=lineY+1;
			PointCount=PointCount+2;
		//	if (pointflag){
		//		pointflag=false;
		//		lineY++;
		//	}
			}
		Dataoffset++;
		bmpcorr++;
		if (bmpcorr==Bwidth){
			bmpcorrflag=true;
			Dataoffset=Dataoffset+(4-(Bwidth-((Bwidth/4)*4)));
			bmpcorr=0;
		}
//		Dataoffset++;
//		lpbuf1[count]=count;
//		lpbuf1[10]=255;
//		lpbuf1[11]=255;
//		lpbuf1[count]=lpbuf[count];
//		PointCount=PointCount+2;
		if (Dataoffset>=4096){
			readnextdata();
			Dataoffset=Dataoffset-4096;
			//if(bmpcorrflag){
			//	Dataoffset=Dataoffset+(Bwidth-((Bwidth/4)*4));
			//	bmpcorrflag=false;
			//}
		}
		if (bmpcorrflag){
			bmpcorrflag=false;
		}
		//lineX++;
		lineX++;
		if (lineX==Bwidth){
			lineY++;
			lineX=0;
		}

	}
	rgndh[0]=32;
	rgndh[1]=RDH_RECTANGLES;
	rgndh[2]=PointCount/4;
	rgndh[3]=PointCount*4;
	rgndh[4]=0;
	rgndh[5]=0;
	rgndh[6]=Bwidth;
	rgndh[7]=Bheght;
	
	CloseHandle(hfile);

	numbytes=32;
	hfile=CreateFile(filename,GENERIC_WRITE,FILE_SHARE_READ	,NULL, OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	WriteFile(hfile,rgndh,numbytes,&numbytes,NULL);
	numbytes=8192*4;
	//hfile=CreateFile(filename,GENERIC_WRITE,FILE_SHARE_READ	,NULL, OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	WriteFile(hfile,lpbuf1,numbytes,&numbytes,NULL);
	
	//TextOut(memdc,10,100,lpbuf,100);
	CloseHandle(hfile);
}
	void readnextdata(){
		numbytes=4096;
		if(!ReadFile(hfile,lpbuf,numbytes,&numbytes,NULL))
	{return;}
	}

	void setnextcoord(){
				
		lpbuf1[PointCount]=lineX;
		lpbuf1[PointCount+1]=lineY;
		PointCount=PointCount+2;
		return;	
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
