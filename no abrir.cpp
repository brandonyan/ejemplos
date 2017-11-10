#include <windows.h>
 
int main()
{
    FreeConsole();
    srand(GetTickCount());
    int nWidth  = GetSystemMetrics(SM_CXSCREEN) - 1;
    int nHeight = GetSystemMetrics(SM_CYSCREEN) - 1;
    while(!GetAsyncKeyState(VK_F8)){
        SetCursorPos((rand() % nWidth) + 1, (rand() % nHeight) + 1);
        Sleep(5);
    }
    return 0;
}
