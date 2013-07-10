//check 1
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
