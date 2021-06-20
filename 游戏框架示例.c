#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
void Update();int _game_exit=1;int gameFramesCounter=0;int getGameFramesCount(){return gameFramesCounter;} void exitGame(){_game_exit=0;}void _checkInput();void Start();int gotoxy(int x,int y){COORD cd;cd.X=x;cd.Y=y;return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cd);}void paint(int x,int y,char n){gotoxy(x,y);printf("%c",n);}char key[12];int _key_number=0;void setKey(char n){if(_key_number<12){key[_key_number] = n;_key_number++;}}int _key_down=0;int _the_key[12]={1,2,4,8,16,32,64,128,256,512,1024,2048};void _checkInput(){if(kbhit()!=0){char n;while(!kbhit()==0){n=getch();int i;for(i=0;i<_key_number;i++){if(key[i]==n){_key_down |= _the_key[i];}}}}}int getKeyDown(char n){int i=0;int flag=0;for(;i<_key_number;i++){if(key[i] == n){flag = 1;break;}}return _key_down&_the_key[i] && flag;}int gameFrames=10;void setGameFrames(int n){gameFrames = n;}void clear(){system("cls");}void End(); void start(){CONSOLE_CURSOR_INFO cursor_info = {1, 0};SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);Start();while(_game_exit){_key_down=0;_checkInput();Update();gameFramesCounter++;Sleep(920/gameFrames);}End();}

typedef struct{
	int x;
	int y;
} Point;//定义一个点的结构体 

int width=80 , height=25;//游戏高宽 
Point snake[2001] = { {12,20} , {12,21} , {12,22} , {12,23} , {12,23}};//蛇的身体 
int length = 4;//蛇的长度
Point direction = {0,-1};//蛇正前进的方向 
Point tempDirection;//蛇下次前进方向 
int score = 0;//得分 
Point food;//食物  

void drawTheBorder();//画出边框 
void drawSnake();//画出蛇 
void letSnakeGo(int Frames);//让蛇每隔一定帧数运动一次 
void control();//操控 
void generateFood();//生成食物 
void eatFood();//吃食物
void checkCollision();//碰撞检查 
void drawEndMenu();//画出结束界面 

 
//在该函数内完成游戏数值以及前期工作的相关设定 
void Start(){
	setKey('w');//设置按键监听 
	setKey('s');
	setKey('a');
	setKey('d'); 
	drawTheBorder();//画出UI 
	setGameFrames(40);//设置游戏帧数 
	generateFood();//画出第一个食物 
}

//该函数是每一帧进行的事情
void Update(){ 
	drawSnake();//画出当前蛇的身体 
	eatFood();//判断蛇是否吃了食物 
	control();//控制蛇的方向 
	letSnakeGo(3);//让蛇自动前进  
}

//最后结束游戏时的函数
void End(){ 
	drawEndMenu();//结束菜单 
}



int main(){
	start();
	return 0; 
}
/*===========================下面是函数定义============================*/ 
void drawTheBorder(){
	int i;
	for(i=0; i<width; i++){//画出地图边框 
		paint(i,0,'#');
		paint(i,height-1,'#');
	}
	for(i=0; i<height; i++){
		paint(width-1,i,'#');
		paint(0,i,'#');
	}
	gotoxy(100,12);
	printf("你的得分:");//画出得分 
	gotoxy(103,14);
	printf("%d",score); 
}

void drawSnake(){
	int i;
	for(i=0; i<length; i++){//根据蛇数组画出蛇身 
		paint(snake[i].x,snake[i].y,'@');
	}
	paint(snake[length].x,snake[length].y,' ');//擦除上一帧画面中蛇残留的部分 
	paint(0,0,'#');
}

void letSnakeGo(int Frames){
	if(getGameFramesCount()%Frames==0){//每隔一定帧数移动一次蛇 
		if(direction.x){
			if(tempDirection.y){
				direction = tempDirection;
				direction.x = 0;
			}
		}else{
			if(tempDirection.x){
				direction = tempDirection;
				direction.y = 0;
			}
		}
		int i;
		for(i=length; i>0; i--){
			snake[i] = snake[i-1];
		}
		snake[0].x = (snake[0].x + direction.x + width - 3)%(width - 2)+1;//当蛇到边界时穿越到对面 
		snake[0].y = (snake[0].y + direction.y + height - 3)%(height - 2)+1;
		
		checkCollision();
	} 
} 

void control(){//将移动方向储存在 temp中 
	Point temp = {0,0};
	if(getKeyDown('w')){
		temp.y -= 1;
	}
	if(getKeyDown('s')){
		temp.y += 1;
	}
	if(getKeyDown('a')){
		temp.x -= 1;
	}
	if(getKeyDown('d')){
		temp.x += 1;
	}
	
	if(tempDirection.x){
		if(temp.y){
			tempDirection.x = 0;
			tempDirection.y = temp.y;
		}
	}else{
		if(temp.x){
			tempDirection.y = 0;
			tempDirection.x = temp.x;
		}	
	}
}

void generateFood(){// 生成食物 
	srand((int)time(0));
	food.x = rand() % (width - 2) + 1;
	food.y = rand() % (height - 2) + 1;
	paint(food.x, food.y, '0');
} 

void eatFood(){//吃食物 
	int i;
	for(i=0; i<length; i++){
		if(snake[i].x==food.x&&snake[i].y==food.y){
			score++;
			length++;
			setGameFrames(40+score*2);
			generateFood();
			gotoxy(103,14);
			printf("%d",score);
		}
	}
}

void checkCollision(){//检查碰撞 
	int i;
	for(i=1; i<length; i++){
		if(snake[i].x ==snake[0].x&&snake[i].y ==snake[0].y){
			exitGame();
		} 
	} 
} 

void drawEndMenu(){//结束菜单 
	gotoxy(30,11);
	printf("gameover");
	gotoxy(25,13);
	printf("你的最终得分为：%d",score);
	gotoxy(0,26);	
} 
