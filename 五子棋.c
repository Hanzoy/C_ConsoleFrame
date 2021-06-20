#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#define Piece int
#define Winner int
#define null 0
#define black 1
#define white -1
void Update();int _game_exit=1;int gameFramesCounter=0;int getGameFramesCount(){return gameFramesCounter;}void Awake();void OnEnable();void exitGame(){_game_exit=0;}void _checkInput();void Start();int gotoxy(int x,int y){COORD cd;cd.X=x;cd.Y=y;return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cd);}void paint(int x,int y,char n){gotoxy(x,y);printf("%c",n);}char key[12];int _key_number=0;void setKey(char n){if(_key_number<12){key[_key_number] = n;_key_number++;}}int _key_down=0;int _the_key[12]={1,2,4,8,16,32,64,128,256,512,1024,2048};void _checkInput(){if(kbhit()!=0){char n;while(!kbhit()==0){n=getch();int i;for(i=0;i<_key_number;i++){if(key[i]==n){_key_down |= _the_key[i];}}}}}int getKeyDown(char n){int i=0;int flag=0;for(;i<_key_number;i++){if(key[i] == n){flag = 1;break;}}return _key_down&_the_key[i] && flag;}int gameFrames=10;void setGameFrames(int n){gameFrames = n;}void clear(){system("cls");}void End(); int _height = 50;int _width = 100;void setHeight(int height){_height = height;}void setWidth(int width){_width = width;}void _updateHandW(){int i;char* cmd = (char*)malloc(sizeof(char)*35);int lenth = 0;const char* _cmd_1 = "mode con cols=";const char* _cmd_2 = " lines=";for(i=0; _cmd_1[i]; i++){cmd[lenth++] = _cmd_1[i];}char temp[10];for(i=0; temp[i]; i++){temp[i] = '\0';}itoa(_width, temp, 10);for(i=0; temp[i]; i++){cmd[lenth++] = temp[i];}for(i=0; _cmd_2[i]; i++){cmd[lenth++] = _cmd_2[i];}for(i=0; temp[i]; i++){temp[i] = '\0';}itoa(_height, temp, 10);for(i=0; temp[i]; i++){cmd[lenth++] = temp[i];}cmd[lenth++] = '\0';const char* _cmd = cmd;system(_cmd);}void start(){Awake();CONSOLE_CURSOR_INFO cursor_info = {1, 0};SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);OnEnable();_updateHandW();Start();while(_game_exit){_key_down=0;_checkInput();Update();gameFramesCounter++;Sleep(920/gameFrames);}End();}
/*===============上面是框架，不用管，下面是框架内一些函数的说明===============*/
//	void setGameFrames(int gameFrames);		设置游戏帧数,未设置则默认为10帧。
//	void setKey(char n);					设置按键，调用后会监听按键 n。最多支持12个按键。
//	int  getKeyDown(char n);				在设置了按键的情况下，如果玩家在该帧内按下按键 n，则返回1，否则返回0，最多支持同时按下12个按键。 
//	void paint(int x,int y,char n);			在坐标为(x,y)的地方画下符号 n。
//	int  gotoxy(int x,int y);				移动光标到(x,y)。 
//	void clear();							清屏（大量使用会导致屏幕闪烁，小范围修改建议使用paint(x,y,' ');来手动擦除，以避免屏幕闪烁）。
//	void exitGame();						退出游戏； 
//	int  getGameFramesCount();				返回当前所在的总帧数；
//  void setHeight(int height);				设置窗口高度；请在OnEnable函数中调用 
//  void setWidth(int width); 				设置窗口宽度；请在OnEnable函数中调用 
/*============================================================================*/   

typedef struct NODE{
	struct NODE* last;
	int x,y;
} Node;

/*==================变量区，请将需要的全局变量放在变量区======================*/
//全局变量
int cursor_x = 0;
int cursor_y = 0;
Piece piece = black;
Piece checkerboard[15][15];
Node* p = NULL;
Winner winner = null;
/*============================================================================*/ 

//
void drawMap(); 
void moveCursor();
void currsorBlinks();
void dropPiece();
void drawUI();
void repentance();
void checkWin(int x, int y);
//



/**
 * Awake()唤醒函数，该函数会在程序加载初执行一次； 
 */
void Awake(){
	
} 

/**
 * OnEnable()加载函数，该函数会执行游戏初始化设定 
 */
void OnEnable(){
	setHeight(50);
	setWidth(150);	
	setKey('w');
	setKey('a');	
	setKey('s');
	setKey('d');
	setKey(' ');
	setKey('r');
	setKey('q');
}

/**
 * Start()开始函数，该函数会在游戏开始时执行一次； 
 */ 
void Start(){
	drawMap(); 
}

/**
 * Update()运行函数，该函数会每一帧执行一次； 
 */
void Update(){
	moveCursor();
	currsorBlinks();
	drawUI();
}

/**
 * End()结束函数，该函数在执行exitGame()后执行一次； 
 */ 
void End(){

}

int main(){
	start();
	return 0; 
}

void drawMap(){
	printf(" ________________________________________________________________________________________________________\n");
	for(int i=0; i<15; i++){
		printf("|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |\n");
		printf("|      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |\n");
		printf("|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|\n");
	}
}

void moveCursor(){
	if(winner == null){
		if(getKeyDown('a')){
			cursor_x = (cursor_x == 0?0:cursor_x-1);
		}
		if(getKeyDown('d')){
			cursor_x = (cursor_x == 14?14:cursor_x+1);
		}
		if(getKeyDown('w')){
			cursor_y = (cursor_y == 0?0:cursor_y-1);
		}
		if(getKeyDown('s')){
			cursor_y = (cursor_y == 14?14:cursor_y+1);
		}
		if(getKeyDown('r')){
			repentance();
		}
		if(getKeyDown(' ')){
			dropPiece();
		}
		if(getKeyDown('q')){
			exitGame();
		}
	}else{
		if(getKeyDown('r')){
			gotoxy(0,0);
			drawMap(); 
			cursor_x = 0;
			cursor_y = 0;
			piece = black;
			for(int i=0; i<15; i++){
				for(int j=0; j<15; j++){
					checkerboard[i][j] = 0;
				}
			}
			p = NULL;
			winner = null;
		}
		if(getKeyDown('q')){
			exitGame();
		}
	}
}

void currsorBlinks(){
	static int cursor_x_temp = 0;
	static int cursor_y_temp = 0;
	static int count = 0;
	if(cursor_x_temp == cursor_x && cursor_y_temp == cursor_y){
		if(count > 4){
			gotoxy(cursor_x_temp*7+1, cursor_y_temp*3);
			printf("______");
			gotoxy(cursor_x_temp*7, cursor_y_temp*3+1);
			printf("|      |");
			gotoxy(cursor_x_temp*7, cursor_y_temp*3+2);
			printf("|");
			gotoxy(cursor_x_temp*7+7, cursor_y_temp*3+2);
			printf("|");
			gotoxy(cursor_x_temp*7, cursor_y_temp*3+3);
			printf("|______|");
		}else{
			gotoxy(cursor_x_temp*7+1, cursor_y_temp*3);
			printf("      ");
			gotoxy(cursor_x_temp*7, cursor_y_temp*3+1);
			printf("        ");
			gotoxy(cursor_x_temp*7, cursor_y_temp*3+2);
			printf(" ");
			gotoxy(cursor_x_temp*7+7, cursor_y_temp*3+2);
			printf(" ");
			gotoxy(cursor_x_temp*7, cursor_y_temp*3+3);
			printf("        ");
		}
	}else{
		count = 0;
		gotoxy(cursor_x_temp*7+1, cursor_y_temp*3);
		printf("______");
		gotoxy(cursor_x_temp*7, cursor_y_temp*3+1);
		printf("|      |");
		gotoxy(cursor_x_temp*7, cursor_y_temp*3+2);
		printf("|");
		gotoxy(cursor_x_temp*7+7, cursor_y_temp*3+2);
		printf("|");
		gotoxy(cursor_x_temp*7, cursor_y_temp*3+3);
		printf("|______|");
		cursor_x_temp = cursor_x;
		cursor_y_temp = cursor_y;
		gotoxy(cursor_x_temp*7+1, cursor_y_temp*3);
		printf("      ");
		gotoxy(cursor_x_temp*7, cursor_y_temp*3+1);
		printf("        ");
		gotoxy(cursor_x_temp*7, cursor_y_temp*3+2);
		printf(" ");
		gotoxy(cursor_x_temp*7+7, cursor_y_temp*3+2);
		printf(" ");
		gotoxy(cursor_x_temp*7, cursor_y_temp*3+3);
		printf("        ");
	}
	count = (count+1)%10;
}

void dropPiece(){
	if(checkerboard[cursor_x][cursor_y] == 0){
		gotoxy(cursor_x*7+3, cursor_y*3+2);
		if(piece == black){
			printf("●");
			checkerboard[cursor_x][cursor_y] = black;
			piece = white;
		}else{
			printf("○");
			checkerboard[cursor_x][cursor_y] = white;
			piece = black;
		}
		checkWin(cursor_x, cursor_y);
		Node* temp = (Node*)malloc(sizeof(Node));
		temp->x = cursor_x;
		temp->y = cursor_y;
		temp->last = p;
		p = temp;
	}
}

void drawUI(){
	gotoxy(120, 25);
	printf("                       ");
	gotoxy(120, 25);
	printf("当前选中位置为(%d,%d)", cursor_x, cursor_y);
	if(winner != null){
		gotoxy(40, 20);
		printf("游戏结束,");
		winner == black?printf("黑棋获胜"):printf("白棋获胜");
		printf("按r重新开始");
	}
	gotoxy(120, 20);
	printf("当前操控玩家：");
	piece == black?printf("●"):printf("○");
	
	gotoxy(120,10);
	printf("w s a d键操控光标"); 
	gotoxy(120,12);
	printf("空格键确定");  
	gotoxy(120,14);
	printf("q键退出游戏，r键回退");
}

void repentance(){
	if(p == NULL)return;
	checkerboard[p->x][p->y] = 0;
	gotoxy((p->x)*7+3, (p->y)*3+2);
	printf("  ");
	p = p->last;
	piece = -piece;
}

void checkWin(int x, int y){
	Piece piece = checkerboard[x][y];
	int count = 0;
	for(int i=0; i<5&&x+i<=14; i++){
		if(checkerboard[x+i][y] == piece){
			count++;
		}else{
			break;
		}
	}
	for(int i=0; i<5&&x-i>=0; i++){
		if(checkerboard[x-i][y] == piece){
			count++;
		}else{
			break;
		}
	}
	if(count > 5){
		winner = piece;
		return;
	}
	count = 0;
	for(int i=0; i<5&&y+i<=14; i++){
		if(checkerboard[x][y+i] == piece){
			count++;
		}else{
			break;
		}
	}
	for(int i=0; i<5&&y-i>=0; i++){
		if(checkerboard[x][y-i] == piece){
			count++;
		}else{
			break;
		}
	}
	if(count > 5){
		winner = piece;
		return;
	}
	count = 0;
	for(int i=0; i<5 && y+i<=14 && x-i>=0; i++){
		if(checkerboard[x-i][y+i] == piece){
			count++;
		}else{
			break;
		}
	}
	for(int i=0; i<5 && y-i>=0 && x+i<=14; i++){
		if(checkerboard[x+i][y-i] == piece){
			count++;
		}else{
			break;
		}
	}
	if(count > 5){
		winner = piece;
		return;
	}
	count = 0;
	for(int i=0; i<5 && x+i<=14 && y-i>=0; i++){
		if(checkerboard[x+i][y-i] == piece){
			count++;
		}else{
			break;
		}
	}
	for(int i=0; i<5 && x-i>=0 && y+i<=14; i++){
		if(checkerboard[x-i][y+i] == piece){
			count++;
		}else{
			break;
		}
	}
	if(count > 5){
		winner = piece;
		return;
	}
}
