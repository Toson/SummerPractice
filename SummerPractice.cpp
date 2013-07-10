// SummerPractice.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "SummerPractice.h"
#include <stdlib.h> //библиотека для использования rand и srand
#include <time.h> //библиотека для использования time

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна

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
	LoadString(hInstance, IDC_SUMMERPRACTICE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SUMMERPRACTICE));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SUMMERPRACTICE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SUMMERPRACTICE);
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, 
	 450 , 200, 380, 450, 0, NULL, NULL, hInstance, NULL);

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

//ОБЪЯВЛЕНИЕ ПЕРЕМЕННЫХ
double *vctr1, *vctr2, *vctr3, temp1=0, temp2=0;
double **mtrx;
FILE *vect, *matr;
int cnt=0,cnt1=0, tmp=0, tmp1=0, ord=0, checker=0;
//ВЕКТОРНАЯ АРИФМЕТИКА
//Сложение Векторов
void add()
{
	tmp=0;
	while(tmp!=(cnt))
	{
		vctr3[tmp]=vctr1[tmp]+vctr2[tmp];
		tmp++;
	}
}

//Сложение Векторов
void sub()
{
	tmp=0;
	while(tmp!=(cnt))
	{
		vctr3[tmp]=vctr1[tmp]-vctr2[tmp];
		tmp++;
	}
}

//Умножение Векторов
void mul()
{
	tmp=0;
	while(tmp!=(cnt))
	{
		vctr3[tmp]=vctr1[tmp]*vctr2[tmp];
		tmp++;
	}
}

//Деление Векторов
void divid()
{
	tmp=0;
	while(tmp!=(cnt))
	{
		vctr3[tmp]=vctr1[tmp]/vctr2[tmp];
		tmp++;
	}
}
//поиск максимальных значений векторов 1 и 2
void sort()
{
	tmp=1;
	temp1=vctr1[tmp-1];
	temp2=vctr2[tmp-1];
	while(tmp!=(cnt))
	{
		if(temp1<vctr1[tmp])
		{
			temp1=vctr1[tmp];
		}
		if(temp2<vctr2[tmp])
		{
			temp2=vctr2[tmp];
		}
		tmp++;
	}
}
//Заполняем значение элементов псевдослучайными числами
void initvect()
{
	vctr1=new double [cnt];
	vctr2=new double [cnt];
	vctr3=new double [cnt];

	srand(time(NULL));
	tmp=0;
	while(tmp!=(cnt))
	{
		vctr1[tmp]=rand();
		vctr2[tmp]=rand();
		vctr3[tmp]=0;
		tmp++;
	}
	temp1=0;
	temp2=0;
}
//пишем содержимое векторов в файл
void savevect()
{
	vect=fopen("VECTOR.txt","w");
	tmp=0;
	fprintf(vect,"Вектор 1:( ");
	while(tmp!=cnt)
	{
		fprintf(vect,"%f ; ", vctr1[tmp]);
		tmp++;
	}
	fprintf(vect," )\n");
	tmp=0;
	fprintf(vect,"Вектор 2:( ");
	while(tmp!=cnt)
	{
		fprintf(vect,"%f ; ", vctr2[tmp]);
		tmp++;
	}
	fprintf(vect," )\n");
	tmp=0;
	fprintf(vect,"Вектор 3:( ");
	while(tmp!=cnt)
	{
		fprintf(vect,"%f ; ", vctr3[tmp]);
		tmp++;
	}
	fprintf(vect," )\n");
	fprintf(vect,"Макс. значение 1 вектора: ");
	fprintf(vect,"%f ; ", temp1);
	fprintf(vect,"\n");
	fprintf(vect,"Макс. значение 2 вектора: ");
	fprintf(vect,"%f ; ", temp2);
	fclose(vect);
}

//очищаем память от векторов
void DeletVec()
{
	delete [] vctr1;
	delete [] vctr2;
	delete [] vctr3;
}
//считываем введенное число из диалога для ввода размерности вектора
INT_PTR CALLBACK ReadResolVectr(HWND HRes1, UINT message, WPARAM wParam, LPARAM lParam)
{

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			cnt=0;
			cnt=GetDlgItemInt(HRes1, IDC_EDIT1, NULL, false);
			if(cnt==0 || cnt>3)
			{
				break;
			}
			EndDialog(HRes1, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// Обработчик сообщений для окна "Векторная Арифметика".
INT_PTR CALLBACK VectArif(HWND HVec, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	char buf[100];
	int n = 0;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
			
		case WM_COMMAND:

			if (LOWORD(wParam) == IDC_BUTTON2)
			{
				add();
				checker=1;
				InvalidateRect(HVec, NULL, TRUE);
				break;
			}
			else if (LOWORD(wParam) == IDC_BUTTON3)
			{
				sub();
				checker=1;
				InvalidateRect(HVec, NULL, TRUE);
				break;
			}
			else if(LOWORD(wParam) == IDC_BUTTON4)
			{
				mul();
				checker=1;
				InvalidateRect(HVec, NULL, TRUE);
				break;
			}
			else if (LOWORD(wParam) == IDC_BUTTON5)
			{
				divid();
				checker=1;
				InvalidateRect(HVec, NULL, TRUE);
				break;
			}
			else if(LOWORD(wParam) == IDC_BUTTON6)
			{
				sort();
				checker=2;
				InvalidateRect(HVec, NULL, TRUE);
				break;
			}
			else if(LOWORD(wParam) == IDC_BUTTON7)
			{
				savevect();
				checker=3;
				InvalidateRect(HVec, NULL, TRUE);
				break;
			}
			if (LOWORD(wParam) == IDCLOSE)
			{
				DeletVec();
				EndDialog(HVec, LOWORD(wParam));
				return (INT_PTR)TRUE;
				break;
			}
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);

	case WM_PAINT:
		hdc = BeginPaint(HVec, &ps);
		tmp=0;
		n=0;
		sprintf(buf, "Вектор1:  (");
		TextOutA(hdc, 170, 25, (LPCSTR)buf, strlen(buf));
		sprintf(buf, "Вектор2:  (");
		TextOutA(hdc, 170, 65, (LPCSTR)buf, strlen(buf));
		while(tmp!=(cnt))
		{
			sprintf(buf, "%f;", (double)vctr1[tmp]);
			TextOutA(hdc, 260+n, 25, (LPCSTR)buf, strlen(buf));
			sprintf(buf, "%f;", (double)vctr2[tmp]);
			TextOutA(hdc, 260+n, 65, (LPCSTR)buf, strlen(buf));
			n=n+110;
			tmp++;
		}
		sprintf(buf, ")");
		TextOutA(hdc, 260+n, 25, (LPCSTR)buf, strlen(buf));
		sprintf(buf, ")");
		TextOutA(hdc, 260+n, 65, (LPCSTR)buf, strlen(buf));
		if (checker == 1)
			{
				sprintf(buf, "Результат: (");
				TextOutA(hdc, 170, 150, (LPCSTR)buf, strlen(buf));
				tmp=0;
				n=0;
				while(tmp!=(cnt))
				{
					sprintf(buf, " %f ;", (double)vctr3[tmp]);
					TextOutA(hdc, 260+n, 150, (LPCSTR)buf, strlen(buf));
					n=n+140;
					tmp++;
				}
				sprintf(buf, " )");
				TextOutA(hdc, 260+n, 150, (LPCSTR)buf, strlen(buf));
			}
			else if(checker==2)
			{
				sprintf(buf, "Результат: 1):");
				TextOutA(hdc, 206, 150, (LPCSTR)buf, strlen(buf));
				sprintf(buf, "\n%f;", (double)temp1);
				TextOutA(hdc, 300, 150, (LPCSTR)buf, strlen(buf));
				sprintf(buf, "2):");
				TextOutA(hdc, 281, 200, (LPCSTR)buf, strlen(buf));
				sprintf(buf, "\n\n%f;", (double)temp2);
				TextOutA(hdc, 301, 200, (LPCSTR)buf, strlen(buf));
			}
			else if(checker==3)
			{
				sprintf(buf, "Запись прошла успешно");
				TextOutA(hdc, 250, 150, (LPCSTR)buf, strlen(buf));
			}
		EndPaint(HVec, &ps);
		break;
	}
	return (INT_PTR)FALSE;
}

//МАТРИЧНАЯ АРИФМЕТИКА
//считываем введенное число из диалога для ввода размерности матрицы
INT_PTR CALLBACK ReadResolMatrx(HWND HRes2, UINT message, WPARAM wParam, LPARAM lParam)
{

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			cnt=0;
			cnt1=0;
			cnt=GetDlgItemInt(HRes2, IDC_EDIT1, NULL, false);
			cnt1=GetDlgItemInt(HRes2, IDC_EDIT2, NULL, false);
			if(cnt==0 || cnt>5 || cnt1==0 || cnt1>5)
			{
				break;
			}
			EndDialog(HRes2, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
//считываем введенное число из диалога для строки, которую нужно упорядочить
INT_PTR CALLBACK ReadStrMatr(HWND HStr, UINT message, WPARAM wParam, LPARAM lParam)
{

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			ord=0;
			ord=GetDlgItemInt(HStr, IDC_EDIT1, NULL, false);
			if(ord==0 || ord>cnt)
			{
				break;
			}
			else
			{
				ord--;
			}
			EndDialog(HStr, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
//Заполняем матрицу псевдослучайными числами
void InitMatrx()
{
	tmp=0;
	mtrx=new double *[cnt];
	while(tmp!=cnt)
	{
		mtrx[tmp]= new double [cnt1];
		tmp++;
	}

	srand(time(NULL));
	tmp=0;
	tmp1=0;
	while(tmp!=cnt)
	{
		while(tmp1!=cnt1)
		{
			mtrx[tmp][tmp1]=rand()/20;
			tmp1++;
		}
		tmp1=0;
		tmp++;
	}
}
//упорядочиваем конкретную строку по убыванию
void order()
{
	tmp=0;
	tmp1=tmp+1;
	while(tmp!=cnt1)
	{
		while(tmp1!=cnt1)
		{
			if(mtrx[ord][tmp]<mtrx[ord][tmp1])
			{
				temp1=mtrx[ord][tmp];
				mtrx[ord][tmp]=mtrx[ord][tmp1];
				mtrx[ord][tmp1]=temp1;
				tmp1++;
			}
			else
			{
				tmp1++;
			}
		}
		tmp++;
		tmp1=tmp+1;
	}
}
//пишем содержимое матрицы в файл
void savematr()
{
	matr=fopen("MATRIX.txt","w");
	tmp=0;
	tmp1=0;
	while(tmp!=cnt)
	{
		while(tmp1!=cnt1)
		{
			fprintf(matr,"  %f  ", mtrx[tmp][tmp1]);
			tmp1++;
		}
		tmp1=0;
		fprintf(matr,"\n");
		tmp++;
	}
	fclose(matr);
}
//очищаем память от матрицы
void DeletMatr()
{
	tmp=0;
	while(tmp!=cnt)
	{
		delete [] mtrx[tmp];
		tmp++;
	}
	delete [] mtrx;
}
// Обработчик сообщений для окна "Матричная Арифметика".
INT_PTR CALLBACK MatrArif(HWND HMat, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	char buf[100];
	int n = 0, y=0;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
			
		case WM_COMMAND:

			if (LOWORD(wParam) == IDC_BUTTON1)
			{
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG5), HMat, ReadStrMatr);
				order();
				checker=1;
				InvalidateRect(HMat, NULL, TRUE);
				break;
			}
			else if (LOWORD(wParam) == IDC_BUTTON2)
			{
				savematr();
				checker=2;
				InvalidateRect(HMat, NULL, TRUE);
				break;
			}
			if (LOWORD(wParam) == IDCANCEL)
			{
				DeletMatr();
				EndDialog(HMat, LOWORD(wParam));
				return (INT_PTR)TRUE;
				break;
			}
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);

	case WM_PAINT:
		hdc = BeginPaint(HMat, &ps);
		if(checker==1)
		{
			tmp=0;
			tmp1=0;
			n=0;
			while(tmp!=cnt)
			{
				while(tmp1!=cnt1)
				{
					sprintf(buf, "\n%f;", (double)mtrx[tmp][tmp1]);
					TextOutA(hdc, 180+n, 100+y, (LPCSTR)buf, strlen(buf));
					n=n+100;
					tmp1++;
				}
				tmp1=0;
				n=0;
				y=y+50;
				tmp++;
			}
		}
		else if(checker==2)
		{
			sprintf(buf, "Запись прошла успешно");
			TextOutA(hdc, 250, 150, (LPCSTR)buf, strlen(buf));
		}
		EndPaint(HMat, &ps);
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	char buf[23];
	switch (message)
	{
	case WM_CREATE:
			CreateWindow(L"button", L"Векторная арифметика", WS_CHILD | WS_VISIBLE, 100, 100, 170, 50, hWnd, (HMENU)666, hInst, NULL);
			CreateWindow(L"button", L"Матричная арифметика", WS_CHILD | WS_VISIBLE, 100, 250, 170, 50, hWnd, (HMENU)777, hInst, NULL);
			
		case WM_COMMAND:

			if (LOWORD(wParam) == 666)
			{
				checker=0;
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, ReadResolVectr);
				initvect();
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, VectArif);
				break;
			}
			else if (LOWORD(wParam) == 777)
			{
				checker=1;
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, ReadResolMatrx);
				InitMatrx();
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hWnd, MatrArif);
				break;
			}
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
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		sprintf(buf, "[Летняя Практика 2013]");
		TextOutA(hdc, 10, 10, (LPCSTR)buf, strlen(buf));

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
