/*
 * Xavi-Gui-Win32.c: GUI Frontend for Xavi using Win32 API
 * Copyright 2015 Vincent Damewood
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <windows.h>

#include <Xavi/FunctionCaller.h>

#include "EvalWindow.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	HWND Handle;
	MSG Message;

	XaviFunctionCallerSetUp();

	if(!RegisterEvalWindowClass(hInstance))
	{
		MessageBox(NULL, "Xavi was unable to register the evaluation window.", "Startup Error", MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	if (!(Handle = CreateEvalWindow(hInstance)))
	{
		MessageBox(NULL, "Xavi was unable to create the evaluation window.", "Startup Error", MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	ShowWindow(Handle, nCmdShow);
	UpdateWindow(Handle);

	while(GetMessage(&Message, NULL, 0, 0) > 0)
	{
		if(!HandleEvalWindowEvent(Handle, &Message))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	XaviFunctionCallerTearDown();
	return (int) Message.wParam;
}
