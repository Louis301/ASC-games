//outputFormatters.cpp

#include "outputFormatters.h" 

void SetCur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void SetColor(int text, int bg) { 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void CursorHide() {
	CONSOLE_CURSOR_INFO curs = {0};
   	curs.dwSize = sizeof(curs);
  	curs.bVisible = FALSE;
   	::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);
}

void setColorText(int color1, string text, int color2) {
	SetColor(color1, black); 
	cout << text;
	SetColor(color2, black); 
}

int GetX_cur() {
    CONSOLE_SCREEN_BUFFER_INFO info_x;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_x);
    return info_x.dwCursorPosition.X;
}
 
int GetY_cur() {
    CONSOLE_SCREEN_BUFFER_INFO info_y;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
    return info_y.dwCursorPosition.Y;
}

/*template<class type>
void printVector(vector<type *> vect)
{
	if(vect.empty()) cout << "\n- empty -";
	else
	for(int i = 0; i < vect.size(); i++) 
		vect[i]->Print();
} */

//printing objects
void FieldPrinter(char simb, int textColor, int bgColor, int width, int height, int x, int y) {
	SetColor(textColor, bgColor);
	for(int i = 0; i < height; i++) {
    	for(int j = 0; j < width; j++) {
    		SetCur(j + x, i + y);
    		cout << simb;
		}
	}
	SetColor(white, black);
}
