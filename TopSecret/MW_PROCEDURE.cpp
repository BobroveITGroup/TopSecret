#include "MainWindow.h"

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}