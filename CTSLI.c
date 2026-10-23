//v1
#include <stdio.h>

#define PLAYER 0
#define CUBE 1

#define V 100 //объекты карты
#define W 101
#define F 102
#define B 104
#define H 107
#define L 108
#define OL 109
#define Y 110
#define YN 111
#define U 112
#define C 113
#define D 114
#define A 115
#define X 103

#define TUTORIAL_CUBE 1 //катсцены
#define TUTORIAL_ACID 2
#define TUTORIAL_VOID 3
#define TUTORIAL_CONVEYOR 4
#define TUTORIAL_LASER 5
#define TUTORIAL_END 6
#define END_EFFECTIVE 7
#define END_NO_EFFECTIVE 8
#define END_ANOMALY 9

#define END_GAME 1 //активные катсцены

#define UP 10
#define DOWN 20
#define LEFT 30
#define RIGHT 40
#define PULL 50

unsigned int action_counter=0,deaths=0,efficiency=0; //счётчики
char input,up='w',down='s',left='a',right='d',pull='f',exitlevel=0,restartlevel=0,start_level=0; //управление и флаги
unsigned char level;

void clear(void) {
printf("\e[0;0H"); //курсор в самое начало консоли
printf("\e[J"); //очистить всё перед курсором
}

void inputt(char *input) {
printf("\e[37minput: ");
scanf("%c" ,&*input);
while(getchar() != '\n');
}

void numinputt(char *input) {
printf("\e[37minput: ");
scanf("%hhu" ,&*input);
while(getchar() != '\n');
}

void About_the_game(void) {
clear();
printf("                Created by:              /\\\n");
printf("                   TIZUVE                \\/\n");
printf("                                            \n");
printf("                 Inspiring:                 \n");
printf("             The game ''Portal''            \n");
printf("                                            \n");
printf("                                            \n");
printf("            Enter any character             \n");
printf("           to return to the menu            \n");
printf("                                            \n");
inputt(&input);
}

void calebritewindow(void) {                             //настройки
clear();
printf("============================================\n");
printf("=            Window calibration            =\n");
printf("=                                          =\n");
printf("=                                          =\n");
printf("=            Enter any character           =\n");
printf("=                to continue               =\n");
printf("=                                          =\n");
printf("=            Recommended size:             =\n");
printf("=                  44x12                   =\n");
printf("============================================\n");
inputt(&input);
}

void Changing_settings(char change) {
clear();
printf("\n");
printf("\n");
printf("\n");
printf("\n");
printf("     Enter what you want to reassign to:    \n");
if(change == UP) {
printf("                     UP                     \n");
}
else if (change == DOWN) {
printf("                    DOWN                    \n");
}
else if (change == LEFT) {
printf("                    LEFT                    \n");
}
else if (change == RIGHT) {
printf("                    RIGHT                   \n");
}
else if (change == PULL) {
printf("                    PULL                    \n");
}
printf("\n");
printf("\n");
printf("\n");
printf("\n");
if(change == UP) {
inputt(&up);
}
else if (change == DOWN) {
inputt(&down);
}
else if (change == LEFT) {
inputt(&left);
}
else if (change == RIGHT) {
inputt(&right);
}
else if (change == PULL) {
inputt(&pull);
}
}

void Setting_menu(void) {
while(1) {
clear();
printf("#==========================================#\n");
printf("|   1 UP...............................%c   |\n",up);
printf("|   2 DOWN.............................%c   |\n",down);
printf("|   3 LEFT.............................%c   |\n",left);
printf("|   4 RIGHT............................%c   |\n",right);
printf("|   5 PULL.............................%c   |\n",pull);
printf("|           6 Window calibration           |\n");
printf("|            7 Default settings            |\n");
printf("|            8 Exit to the menu            |\n");
printf("#==========================================#\n");
numinputt(&input);
if (input == 1) {
Changing_settings(UP);
}
else if (input == 2) {
Changing_settings(DOWN);
}
else if (input == 3) {
Changing_settings(LEFT);
}
else if (input == 4) {
Changing_settings(RIGHT);
}
else if (input == 5) {
Changing_settings(PULL);
}
else if (input == 6) {
calebritewindow();
}
else if (input == 7) {
up='w',down='s',left='a',right='d',pull='f';
}
else if (input == 8) {
break;
}
}
} 
                                                //конец настроек
void game_over(void) {
deaths++;
while(1) {
clear();
printf("   ####      #     #       # ######         \n");
printf("  #         # #    ##     ## #              \n");
printf("  #  ###   #   #   # #   # # ######         \n");
printf("  #    #  #######  #  # #  # #              \n");
printf("   ####  #       # #   #   # ######         \n");
printf("            ####  #       # ###### #####    \n");
printf("R = Return #    #  #     #  #      #    #   \n");
printf("           #    #   #   #   ###### #####    \n");
printf("E = Exit   #    #    # #    #      # #      \n");
printf("            ####      #     ###### #  #     \n");
inputt(&input);
if (input == 'R'||input == 'r') {
restartlevel=1;
break;
}
else if (input == 'E'||input == 'e') {
exitlevel=1;
break;
}
}
}

int walls(char dis_y,char dis_x,char y,char x,char type,unsigned char (*struclevel)[10][44]) { //таблица столкновений
if (!(
x+dis_x>43||
x+dis_x<0||
y+dis_y>9||
y+dis_y<0||
(*struclevel)[y + dis_y][x + dis_x] == W ||
(*struclevel)[y + dis_y][x + dis_x] == H ||
(*struclevel)[y + dis_y][x + dis_x] == L ||
(*struclevel)[y + dis_y][x + dis_x] == X
)) {
if(type==CUBE) {
if(!(
(*struclevel)[y + dis_y][x + dis_x] == OL
)) {return 1;}
else {return 0;}
}
else {return 1;}
}
else {return 0;}
}

void graphics(char player_y,char player_x,unsigned char (*struclevel)[10][44],unsigned char (*object)[10][44]) { //вывод уровня
clear();
for(char v=0;v<10;v++) {
for(char g=0;g<45;g++) {
printf("\e[0m");
if (g==44) {
printf("\e[37m");
printf("\n");
continue;
}
if ((*struclevel)[v][g]>199) {
printf("\e[41m");
(*struclevel)[v][g]-=100;
}
if (v==player_y&&player_x==g) {
printf("@");
}
else if ((*object)[v][g]) {
printf("N");
}
else if ((*struclevel)[v][g] == V) {
printf("\e[37m");
printf(" ");
}
else if ((*struclevel)[v][g] == F) {
printf("=");
}
else if ((*struclevel)[v][g] == W) {
printf("#");
}
else if ((*struclevel)[v][g] == B) {
printf("O");
}
else if ((*struclevel)[v][g] == H) {
printf("0");
}
else if ((*struclevel)[v][g] == L) {
printf("$");
}
else if ((*struclevel)[v][g] == OL) {
char c432='%';
printf("%c",c432);
}
else if ((*struclevel)[v][g] == Y) {
printf("\e[32m");
printf("~");
}
else if ((*struclevel)[v][g] == YN) {
printf("\e[32m");
printf("N");
}
else if ((*struclevel)[v][g] == A) {
printf("^");
}
else if ((*struclevel)[v][g] == C) {
printf("<");
}
else if ((*struclevel)[v][g] == D) {
printf(">");
}
else if ((*struclevel)[v][g] == U) {
printf("V");
}
else if ((*struclevel)[v][g] == X) {
printf("X");
}
else {
printf("\e[32m");
printf("🮕");
}
}
}
}

void fbatton(unsigned char (*struclevel)[10][44],unsigned char (*object)[10][44]) {
char batton=1; //работа кнопок
for (char v=0;v<10;v++) {
	for(char g=0;g<44;g++) {
		if ((*struclevel)[v][g]==B) {
			if ((*object)[v][g]) {
				(*object)[v][g]=0;
				(*struclevel)[v][g]=H;
			}
			else {
				batton=0;
			}
		}
	}
}
if(batton) {
	for (char v=0;v<10;v++) {
		for(char g=0;g<44;g++) {
			if ((*struclevel)[v][g]==L) {
				(*struclevel)[v][g]=OL;
			}
		}
	}
}
}

char golaser(char direction,char v,char g,unsigned char (*struclevel)[10][44],unsigned char (*object)[10][44],char player_y,char player_x) {
	char dis_y,dis_x;
	if(direction==UP) {
		dis_y=-1,dis_x=0;
		v-=1;
	}
	else if(direction==DOWN) {
		dis_y=1,dis_x=0;
		v+=1;
	}
	else if(direction==RIGHT) {
		dis_y=0,dis_x=1;
		g+=1;
	}
	else{
		dis_y=0,dis_x=-1;
		g-=1;
	}
	while(walls(0,0,v,g,CUBE,&(*struclevel))) {
		if(!((*object)[v][g])) {
			if(!((*struclevel)[v][g]>199)) {
				if(!(v==player_y&&player_x==g)) {
					(*struclevel)[v][g]+=100;
					v+=dis_y;
					g+=dis_x;
				}
				else {
					game_over();
					break;
				}
			}
			else {
				v+=dis_y;
				g+=dis_x;
			}
		}
		else {break;}
	}
	return 0;
}

void laser(unsigned char (*struclevel)[10][44],unsigned char (*object)[10][44],char player_y,char player_x){
	for (char v=0;v<10;v++) {
		for(char g=0;g<44;g++) {
			if((*struclevel)[v][g] == X) {
				golaser(UP,v,g,&(*struclevel),&(*object),player_y,player_x);
				golaser(DOWN,v,g,&(*struclevel),&(*object),player_y,player_x);
				golaser(RIGHT,v,g,&(*struclevel),&(*object),player_y,player_x);
				golaser(LEFT,v,g,&(*struclevel),&(*object),player_y,player_x);
			}
		}
	}
}

char conv_move(char dis_y,char dis_x,char *y,char *x,char type,unsigned char (*struclevel)[10][44],unsigned char (*object)[10][44],char player_y,char player_x) {
	if (walls(dis_y,dis_x,*y,*x,type,&(*struclevel))) {
		if(!((*object)[*y+dis_y][*x+dis_x]||*y+dis_y==player_y&&*x+dis_x==player_x)) {
			if((*struclevel)[*y+dis_y][*x+dis_x] == Y) {
				if (type) {
					(*struclevel)[*y+dis_y][*x+dis_x] = YN;
					(*object)[*y][*x]=0;
					return 1;
				}
				else {
					game_over();
					return 1;
				}
			}
			else if((*struclevel)[*y+dis_y][*x+dis_x] == V) {
				if (type) {
					(*object)[*y][*x]=0;
					return 1;
				}
				else {
					game_over();
					return 1;
				}
			}
			else {
				if (type) {
					(*object)[*y][*x]=0;
					(*object)[*y+dis_y][*x+dis_x]=1;
					return 1;
				}
				else {
					*y=*y+dis_y;
					*x=*x+dis_x;
					return 1;
				}
			}
		}
	}
	return 0;
}

void conv(unsigned char (*struclevel)[10][44],char *player_y,char *player_x,unsigned char (*object)[10][44]) {
	unsigned char cc = 255; //точность обработки конвейеров
	unsigned char done[10][44] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
	do {
		for (char v=0;v<10;v++) {
			for(char g=0;g<44;g++) {
				if(done[v][g]) {
					if((*struclevel)[v][g]==U) {
						if((*object)[v][g]) {
							if(conv_move(1,0,&v,&g,CUBE,&(*struclevel),&(*object),*player_y,*player_x)) {
								done[v+1][g]=0;
							}
						}
						else if(*player_y==v&&*player_x==g) {
							if(conv_move(1,0,&*player_y,&*player_x,PLAYER,&(*struclevel),&(*object),*player_y,*player_x)) {
								done[v+1][g]=0;
							}
						}
					}
					else if((*struclevel)[v][g]==C) {
						if((*object)[v][g]) {
							if(conv_move(0,-1,&v,&g,CUBE,&(*struclevel),&(*object),*player_y,*player_x)) {
								done[v][g-1]=0;
							}
						}
						else if(*player_y==v&&*player_x==g) {
							if(conv_move(0,-1,&*player_y,&*player_x,PLAYER,&(*struclevel),&(*object),*player_y,*player_x)) {
								done[v][g-1]=0;
							}
						}
					}
					else if((*struclevel)[v][g]==D) {
						if((*object)[v][g]) {
							if(conv_move(0,1,&v,&g,CUBE,&(*struclevel),&(*object),*player_y,*player_x)) {
								done[v][g+1]=0;
							}
						}
						else if(*player_y==v&&*player_x==g) {
							if(conv_move(0,1,&*player_y,&*player_x,PLAYER,&(*struclevel),&(*object),*player_y,*player_x)) {
								done[v][g+1]=0;
							}
						}
					}
					else if((*struclevel)[v][g]==A) {
						if((*object)[v][g]) {
							if(conv_move(-1,0,&v,&g,CUBE,&(*struclevel),&(*object),*player_y,*player_x)) {
								done[v-1][g]=0;
							}
						}
						else if(*player_y==v&&*player_x==g) {
							if(done[v][g]) {
								if(conv_move(-1,0,&*player_y,&*player_x,PLAYER,&(*struclevel),&(*object),*player_y,*player_x)) {
									done[v-1][g]=0;
								}
							}
						}
					}
				}
			}
		}
		cc-=1;
	} while(cc);
}

void fpull(char *pullup,char *pulldown,char *pullright,char *pullleft,char *player_y,char *player_x,unsigned char (*object)[10][44],unsigned char (*struclevel)[10][44]) {
char dis_x,dis_y;
if(*pullup==1) {
dis_x=0,dis_y=1;
}
else if(*pulldown==1){
dis_x=0,dis_y=-1;
}
else if(*pullright==1){
dis_x=-1,dis_y=0;
}
else if(*pullleft==1){
dis_x=1,dis_y=0;
}
if((*object)[*player_y+(0-dis_y)][*player_x+(0-dis_x)]) {
	if(walls(dis_y,dis_x,*player_y,*player_x,PLAYER,&(*struclevel))) {
		if(!((*object)[*player_y+dis_y][*player_x+dis_x])) {
			if((*struclevel)[*player_y+dis_y][*player_x+dis_x] == V||(*struclevel)[*player_y+dis_y][*player_x+dis_x] == Y) {
				game_over();
			}
			else if((*struclevel)[*player_y+dis_y][*player_x+dis_x] == OL) {
				level+=1;
				restartlevel=1;
			}
			else {
				(*object)[*player_y][*player_x]=1;
				(*object)[*player_y+(0-dis_y)][*player_x+(0-dis_x)]=0;
				*player_y+=dis_y,*player_x+=dis_x;
			}
		}
	}
}
}

void move(char dis_y,char dis_x,char *player_y,char *player_x,unsigned char (*object)[10][44],unsigned char (*struclevel)[10][44],char *pullup,char *pulldown,char *pullleft,char *pullright) {
if (dis_y<0) {
	*pullup=1;
}
else {*pullup=0;}
if (dis_y>0) {
	*pulldown=1;
}
else {*pulldown=0;}
if (dis_x<0) {
	*pullleft=1;
}
else {*pullleft=0;}
if (dis_x>0) {
	*pullright=1;
}
else {*pullright=0;}
	if (walls(dis_y,dis_x,*player_y,*player_x,PLAYER,&(*struclevel))) {
		if (!((*object)[*player_y+dis_y][*player_x+dis_x])) {
			if ((*struclevel)[*player_y+dis_y][*player_x+dis_x] == V||(*struclevel)[*player_y+dis_y][*player_x+dis_x] == Y) {
				game_over();
			}
			else if ((*struclevel)[*player_y+dis_y][*player_x+dis_x] == OL) {
				level +=1;
				restartlevel=1;
			}
			else {
				*player_y+=dis_y;
				*player_x+=dis_x;
			}
		}
		else {
			if(walls(dis_y+dis_y,dis_x+dis_x,*player_y,*player_x,CUBE,&(*struclevel))) {
				if(!((*object)[*player_y+dis_y*2][*player_x+dis_x*2])) {
					if((*struclevel)[*player_y+dis_y*2][*player_x+dis_x*2] == V) {
						(*object)[*player_y+dis_y][*player_x+dis_x]=0;
						*player_y+=dis_y;
						*player_x+=dis_x;
					}
					else if((*struclevel)[*player_y+dis_y*2][*player_x+dis_x*2] == Y) {
						(*object)[*player_y+dis_y][*player_x+dis_x]=0;
						(*struclevel)[*player_y+dis_y*2][*player_x+dis_x*2] = YN;
						*player_y+=dis_y;
						*player_x+=dis_x;
					}
					else {
						(*object)[*player_y+dis_y][*player_x+dis_x]=0;
						(*object)[*player_y+dis_y*2][*player_x+dis_x*2]=1;
						*player_y+=dis_y;
						*player_x+=dis_x;
					}
				}
			}
		}
	}
}

void physics(char *player_y,char *player_x,unsigned char (*object)[10][44],unsigned char (*struclevel)[10][44]) {
	conv(&(*struclevel),&*player_y,&*player_x,&(*object));
	fbatton(&(*struclevel),&(*object));
	laser(&(*struclevel),&(*object),*player_y,*player_x);
}

void enter(char *player_y,char *player_x,unsigned char (*object)[10][44],unsigned char (*struclevel)[10][44],char *pullup,char *pulldown,char *pullleft,char *pullright) {
inputt(&input);
if (input==up) {
	move(-1,0,&*player_y,&*player_x,&(*object),&(*struclevel),&*pullup,&*pulldown,&*pullleft,&*pullright);
}
else if (input==down) {
	move(1,0,&*player_y,&*player_x,&(*object),&(*struclevel),&*pullup,&*pulldown,&*pullleft,&*pullright);
}
else if (input==left) {
	move(0,-1,&*player_y,&*player_x,&(*object),&(*struclevel),&*pullup,&*pulldown,&*pullleft,&*pullright);
}
else if (input==right) {
	move(0,1,&*player_y,&*player_x,&(*object),&(*struclevel),&*pullup,&*pulldown,&*pullleft,&*pullright);
}
else if (input==pull) {
	fpull(&*pullup,&*pulldown,&*pullright,&*pullleft,&*player_y,&*player_x,&(*object),&(*struclevel));
}
action_counter++;
}

unsigned char cutscenes(unsigned char id_cutscenes) {
if (id_cutscenes == 0) {}
else if (id_cutscenes == TUTORIAL_CUBE) { //начало катсцены
while (1) { //начало кадра катсцены
clear();
printf("SYSTEM ACTIVATION...                        \n");
printf("SYSTEM INITIALISATION...                    \n");
printf("LOAD TUTORIAL...                            \n");
printf("LOADING STEP 1/5...                         \n");
printf("Enter 'C' to Continue                       \n");
printf("Enter 'S' to Skip                           \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("My dear friend!                             \n");
printf("Welcome to the first stage                  \n");
printf("mandatory testing.                          \n");
printf("In this stage,                              \n");
printf("you will have to go through                 \n");
printf("10 test chambers.                           \n");
printf("But before that,                            \n");
printf("you will need to go through the training,   \n");
printf("it will take place in five stages.          \n");
printf("Now you will go to the first stage...       \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("             walking=[%c,%c,%c,%c]              \n",up,down,left,right);
printf("                                            \n");
printf("                                            \n");
printf("     ===     ===                            \n");
printf("    1N=@    2N@=                            \n");
printf("     =O=     =O=                            \n");
printf("                                            \n");
printf("                                            \n");
printf("To get started,                             \n");
printf("you'll probably need to go to the cube[N]   \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                  pull=[%c]                  \n",pull);
printf("                                            \n");
printf("                                            \n");
printf("     ===     ===     ===                    \n");
printf("    1N=@    2N@=    3=N@                    \n");
printf("     =O=     =O=     =O=                    \n");
printf("                                            \n");
printf("                                            \n");
printf("Then, you'll probably need to pull the cube \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("     ===     ===     ===     =@=     ===    \n");
printf("    1N=@    2N@=    3=N@    4=N=    5=@=    \n");
printf("     =O=     =O=     =O=     =O=     =0=    \n");
printf("                                            \n");
printf("                                            \n");
printf("Then, you'll probably need to pull the cube \n");
printf("and push it onto the button.[O]             \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("      After pressing all the buttons,       \n");
printf("         the lift[$] will open[%]           \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
} //конец катсцены
else if (id_cutscenes == TUTORIAL_ACID) { //начало катсцены
while (1) { //начало кадра катсцены
clear();
printf("LOADING STEP 2/5...                         \n");
printf("Enter 'C' to Continue                       \n");
printf("Enter 'S' to Skip                           \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf(" Next, you will get acquainted with acid[\e[32m~\e[0m] \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("   The acid eats away everything organic    \n");
printf("            at an amazing rate,             \n");
printf("   for this reason it is not recommended    \n");
printf("                to touch it.                \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("Luckily for you,                            \n");
printf("the laboratory uses only environmentally    \n");
printf("dirty materials.                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("           1         2                      \n");
printf("         ==\e[32m~\e[0mN=     ==\e[32m~\e[0mN=       \e[32m \e[0m            \n");
printf("         @N\e[32m~\e[0m==     =@\e[32mN\e[0m==       \e[32m \e[0m            \n");
printf("         ==\e[32m~\e[0m==     ==\e[32m~\e[0m==       \e[32m \e[0m            \n");
printf("         $=\e[32m~\e[0m=O     $=\e[32m~\e[0m=O       \e[32m \e[0m            \n");
printf("                                            \n");
printf("                                            \n");
printf("Therefore, you can throw the cube into acid \n");
printf("by creating a bridge[\e[32mN\e[0m] for yourself.       \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("           1         2         3            \n");
printf("         ==\e[32m~\e[0mN=     ==\e[32m~\e[0mN=     ==\e[32mN\e[0m@=          \n");
printf("         @N\e[32m~\e[0m==     =@\e[32mN\e[0m==     ==\e[32mN\e[0m==          \n");
printf("         ==\e[32m~\e[0m==     ==\e[32m~\e[0m==     ==\e[32m~\e[0m==          \n");
printf("         $=\e[32m~\e[0m=O     $=\e[32m~\e[0m=O     $=\e[32m~\e[0m=O          \n");
printf("                                            \n");
printf("if you messed up and, for example,          \n");
printf("drowned all your cubes when you need them   \n");
printf("somewhere else.                           \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("           1         2         3            \n");
printf("         ==\e[32m~\e[0mN=     ==\e[32m~\e[0mN=     ==\e[32mN\e[0m@=          \n");
printf("         @N\e[32m~\e[0m==     =@\e[32mN\e[0m==     ==\e[32mN\e[0m==          \n");
printf("         ==\e[32m~\e[0m==     ==\e[32m~\e[0m==     ==\e[32m~\e[0m==          \n");
printf("         $=\e[32m~\e[0m=O     $=\e[32m~\e[0m=O     $=\e[32m~\e[0m=O          \n");
printf("                                            \n");
printf("You can eliminate yourself,                 \n");
printf("after which we will reset the camera        \n");
printf("and send the next test subject into it.     \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
} //конец катсцены
else if (id_cutscenes == TUTORIAL_VOID) { //начало катсцены
while (1) { //начало кадра катсцены
clear();
printf("LOADING STEP 3/5...                         \n");
printf("Enter 'C' to Continue                       \n");
printf("Enter 'S' to Skip                           \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("         In the next test chamber,          \n");
printf("       you'll encounter the void[ ].        \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("        Having fallen into the void,        \n");
printf("        it is highly not recommended        \n");
printf("          to try to save yourself.          \n");
printf(" You can interfere with other test subjects \n");
printf("           in other test chambers           \n");
printf("          or damage the equipment.          \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("         It's better to just enjoy          \n");
printf("      your approx hundred-second drop.      \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("               After a fall,                \n");
printf("      your body will be identified by       \n");
printf("        specially trained employees.        \n");
printf("    You don't have to worry about them,     \n");
printf("   their helmets are prone to collisions    \n");
printf(" at speeds up to 3600 kilometres per hour.  \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("    Also, before the next test chamber,     \n");
printf("   keep in mind that the button mechanism   \n");
printf("     tightly fixes the cube in itself.      \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
} //конец катсцены
else if (id_cutscenes == TUTORIAL_CONVEYOR) { //начало катсцены
while (1) { //начало кадра катсцены
clear();
printf("LOADING STEP 4/5...                         \n");
printf("Enter 'C' to Continue                       \n");
printf("Enter 'S' to Skip                           \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("            In the next chamber,            \n");
printf(" you will get acquainted with the conveyors \n");
printf("                                            \n");
printf("      They can have a direction namely      \n");
printf("   up[^], down[V], left[<] and right[>].    \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("     1        2        3                    \n");
printf("      @>>$     >@>$     >>@$                \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("Conveyors can move you                      \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("     Expectation=[any unassigned input]     \n");
printf("     1        2        3        4           \n");
printf("      @>>$     >@>$     >>@$     >>>%       \n");
printf("                                            \n");
printf("      N>>O     >N>O     >>NO     >>>0       \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("Conveyors can move you                      \n");
printf("and cubes.                                  \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("   The speed of the conveyors is slightly   \n");
printf("   higher than the average walking speed.   \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
} //конец катсцены
else if (id_cutscenes == TUTORIAL_LASER) { //начало катсцены
while (1) { //начало кадра катсцены
clear();
printf("LOADING STEP 5/5...                         \n");
printf("Enter 'C' to Continue                       \n");
printf("Enter 'S' to Skip                           \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("         In the next test chamber,          \n");
printf("          you will meet lasers[\e[41m \e[0m]           \n");
printf("           and their sources.[X]            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("             1                              \n");
printf("           ==\e[41m=\e[0m==                            \n");
printf("           ==\e[41m=\e[0m==                            \n");
printf("           \e[41m==\e[0mX\e[41m==\e[0m                            \n");
printf("           ==\e[41m=\e[0m==                            \n");
printf("           ==\e[41m=\e[0m==                            \n");
printf("                                            \n");
printf("The source emits lasers                     \n");
printf("in four directions around itself.           \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("             1                2             \n");
printf("           ==\e[41m=\e[0m==            ==$==           \n");
printf("           ==\e[41m=\e[0m==            ==\e[41m=\e[0m==           \n");
printf("           \e[41m==\e[0mX\e[41m==\e[0m            N\e[41m=\e[0mX\e[41m=\e[0m0           \n");
printf("           ==\e[41m=\e[0m==            ==\e[41m=\e[0m==           \n");
printf("           ==\e[41m=\e[0m==            ==#==           \n");
printf("                                            \n");
printf("                                            \n");
printf("So, the laser goes to the first obstacle.   \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf(" It is not recommended to touch the laser,  \n");
printf("          because its temperature           \n");
printf("    is about 20 million degrees Celsius.    \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("     Although you can stand next to it,     \n");
printf("     because the air in the complex is      \n");
printf("            extremely rarefied.             \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
} //конец катсцены
else if (id_cutscenes == TUTORIAL_END) { //начало катсцены
while (1) { //начало кадра катсцены
clear();
printf("LOADING STEP 6/5...                         \n");
printf("ERROR:exit status 4                         \n");
printf("RUNNING THE ERROR CORRECTION TOOL...        \n");
printf("UNLOADING TUTORIAL...                       \n");
printf("LOAD THE CORE TEST PROTOCOL...              \n");
printf("Enter 'C' to Continue                       \n");
printf("Enter 'S' to Skip                           \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("We congratulate you,                        \n");
printf("test subject number %03d,                      \n",deaths);
printf("on successfully completing the training.    \n");
printf("There are 10 test chambers                  \n");
printf("ahead of you that you have to solve.        \n");
printf("Good luck!                                  \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
printf("                                            \n");
inputt(&input);
if (input=='S'||input=='s') {
return 0;
}
else if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
} //конец катсцены
else if (id_cutscenes == END_EFFECTIVE) { //начало катсцены
while (1) { //начало кадра катсцены
clear();
printf("Report on Subject № %03d                     \n",deaths);                                                                                                                                              
printf("                                            \n");                                                                                                                                                
printf("The effectiveness of the subject is %d%%\n",efficiency);                                                                                                                                                   
printf("                                            \n");
if (start_level!=1) {
printf("Verdict: Eliminate anomaly.                 \n");
}
else {
printf("Verdict: Eliminate.                         \n");
}
printf("                                            \n");                                                                                                                                                   
printf(" ########  Enter 'C'                        \n");                                                                                                                                                   
printf(" X====@=%%  to start executing.             \n");                                                                                                                                                   
printf(" ########                                   \n");                                                                                                                                                   
printf("                                            \n");
inputt(&input);
if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("Report on Subject № %03d                     \n",deaths);                                                                                                                                              
printf("                                            \n");                                                                                                                                                
printf("The effectiveness of the subject is %d%%\n",efficiency);                                                                                                                                                    
printf("                                            \n");                                                                                                                                                   
if (start_level!=1) {
printf("Verdict: Eliminate anomaly.                 \n");
}
else {
printf("Verdict: Eliminate.                         \n");
}                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf(" ########  Enter 'C'                        \n");                                                                                                                                                   
printf(" X\e[41m====\e[33m@\e[0m=%%  to start executing.              \n");                                                                                                                                                   
printf(" ########                                   \n");                                                                                                                                                   
printf("                                            \n");
inputt(&input);
if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("Report on Subject № %03d                     \n",deaths);                                                                                                                                              
printf("                                            \n");                                                                                                                                                
printf("The effectiveness of the subject is %d%%\n",efficiency);                                                                                                                                              
printf("                                            \n");                                                                                                                                                   
if (start_level!=1) {
printf("Verdict: Eliminate anomaly.                 \n");
}
else {
printf("Verdict: Eliminate.                         \n");
}                                                                                                                                                 
printf("                                            \n");                                                                                                                                                   
printf(" ########  Enter 'C'                        \n");                                                                                                                                                   
printf(" X\e[41m====\e[31;43ma\e[0m=%%  to start executing.              \n");                                                                                                                                                   
printf(" ########                                   \n");                                                                                                                                                   
printf("                                            \n");
inputt(&input);
if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");
inputt(&input);
if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("           Thank you for playing!           \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");
inputt(&input);
if (input=='C'||input=='c') {
break;
}
} //конец кадра катсцены
} //конец катсцены
else if (id_cutscenes == END_NO_EFFECTIVE) { //начало катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");
inputt(&input);
break;
} //конец кадра катсцены
while (1) { //начало кадра катсцены
clear();
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("           Thank you for playing!           \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");                                                                                                                                                   
printf("                                            \n");
inputt(&input);
break;
} //конец кадра катсцены
} //конец катсцены
else {}
}

void active_cutscenes(unsigned char id_cutscenes,char *step,char x) {
if (id_cutscenes==0) {
}
else if (id_cutscenes==END_GAME) {
if (efficiency==0) {
	efficiency=350000/action_counter;
}
printf("\e[8;2H");
printf("X");
if (x>=3||*step>=1) {
	if(!(*step>=1)) {
		*step=1;
	}
	printf("\e[1;1H");
	printf("Report on Subject № ");
	printf("%03d",deaths);
}
if (x>=4||*step>=2) {
	if(!(*step>=2)) {
		*step=2;
	}
	printf("\e[3;1H");
	printf("The effectiveness of the subject is ");
	printf("%d%%",efficiency);
}
if (x>=5||*step>=3) {
	if(!(*step>=3)) {
		*step=3;
	}
	if (start_level!=1) {
		printf("\e[5;1H");
		printf("Verdict: Eliminate anomaly.");
		*step=4;
	}
	else if (efficiency>=100) {
		printf("\e[5;1H");
		printf("Verdict: Eliminate.");
		*step=5;
	}
	else if (efficiency<=100) {
		printf("\e[5;1H");
		printf("Verdict: Postpone to the second stage.");
		*step=6;
	}
}
if (x>=6&&*step==4) {
	cutscenes(END_EFFECTIVE);
	About_the_game();
	exitlevel=1;
}
else if (x>=6&&*step==5) {
	cutscenes(END_EFFECTIVE);
	About_the_game();
	exitlevel=1;
}
printf("\e[11;0H");
}
else {}
}

void play_level(void) {
	while (1) {
		if (exitlevel!=0) {
			break;
		}
		if (level==0) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			char step=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,W,F,F,F,F,F,F,L,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка
 {V,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 7,player_x = 2; //стартовые координаты игрока
			cutscenes(0); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				active_cutscenes(END_GAME,&step,player_x);
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
			if (level!=0) {
				cutscenes(END_NO_EFFECTIVE);
				About_the_game();
				exitlevel=1;
			}
		}
		else if (level==1) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,V,V,V,V,V,V,V,W,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,V,V,V,V,V,V,V,W,F,F,F,W,F,F,B,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,V,V,V,V,V,V,V,W,F,F,F,F,F,F,F,L,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,V,V,V,V,V,V,V,W,F,F,F,W,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,V,V,V,V,V,V,V,W,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка L=дверь
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 4,player_x = 12; //стартовые координаты игрока
			cutscenes(TUTORIAL_CUBE); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==2) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,V,V,V,V,V,V,V,W,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,V,V,V,V,V,V,V,W,B,F,F,Y,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,V,V,V,V,V,V,V,W,F,F,F,Y,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,V,V,V,V,V,V,V,W,F,F,F,Y,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,V,V,V,V,V,V,V,W,F,F,F,Y,F,F,L,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,V,V,V,V,V,V,V,W,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка L=дверь
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 6,player_x = 13; //стартовые координаты игрока
			cutscenes(TUTORIAL_ACID); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==3) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,F,F,F,V,F,F,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,F,V,F,V,F,V,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,F,F,F,B,F,F,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,V,V,B,V,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,F,F,F,V,F,F,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,F,L,F,V,F,F,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка L=дверь
 {V,V,V,F,F,F,V,F,F,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 7,player_x = 8; //стартовые координаты игрока
			cutscenes(TUTORIAL_VOID); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==4) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,V,V,V,V,V,V,V,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,V,V,V,V,V,V,V,W,F,F,F,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,V,V,V,V,V,V,V,V,V,L,F,F,F,F,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,V,V,V,V,V,V,V,V,V,W,F,F,F,W,U,V,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,V,V,V,V,V,V,V,V,V,W,W,W,W,W,D,D,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,W,W,W,F,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,W,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,W,F,B,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,W,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 1,player_x = 15; //стартовые координаты игрока
			cutscenes(TUTORIAL_CONVEYOR); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==5) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,V,V,V,V,V,V,V,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,V,V,V,V,V,V,W,W,W,W,X,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,V,V,V,V,V,V,W,F,F,F,F,F,F,F,F,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,V,V,V,V,V,V,W,F,L,F,F,F,F,F,F,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,V,V,V,V,V,V,W,F,F,F,F,F,F,F,F,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,V,V,V,V,V,V,W,W,W,W,X,W,W,W,X,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,V,V,V,V,V,V,V,V,V,W,W,W,V,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка L=дверь
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 3,player_x = 15; //стартовые координаты игрока
			cutscenes(TUTORIAL_LASER); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==6) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,V,V,V,V,V,V,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,V,V,W,W,W,W,W,X,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,V,V,V,V,W,F,F,F,F,F,F,F,F,B,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,V,V,V,V,W,F,F,F,V,V,V,F,F,F,L,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,V,V,V,V,W,F,F,F,V,F,F,F,F,F,L,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,V,V,V,V,W,F,F,F,V,V,V,F,F,B,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,V,V,V,V,W,W,W,F,W,Y,W,F,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,V,V,V,V,V,V,W,F,W,Y,W,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка
 {V,V,V,V,V,V,V,V,V,W,F,F,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 5,player_x = 10; //стартовые координаты игрока
			cutscenes(TUTORIAL_END); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==7) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,V,V,V,V,V,V,W,W,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,V,V,V,V,V,V,W,D,D,D,D,D,D,D,D,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,V,V,V,V,V,V,V,V,W,F,W,W,W,W,Y,F,Y,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,V,V,V,V,V,V,V,V,W,F,F,V,V,V,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,V,V,V,V,V,V,V,W,W,F,F,F,F,V,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,V,V,V,V,V,V,V,W,F,F,F,V,F,V,F,F,L,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,V,V,V,V,V,V,V,W,W,F,F,V,F,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,V,V,V,V,V,V,V,V,W,F,F,V,V,V,B,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка L=дверь
 {V,V,V,V,V,V,V,V,V,V,V,W,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 5,player_x = 11; //стартовые координаты игрока
			cutscenes(0); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==8) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,V,V,L,F,F,F,F,F,B,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,V,V,F,V,V,F,V,V,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,V,V,F,V,F,F,F,V,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,V,V,F,V,F,V,F,V,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,V,V,F,V,F,F,F,V,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,V,V,F,V,V,F,V,V,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка
 {V,V,V,V,V,B,F,F,F,F,F,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 6,player_x = 8; //стартовые координаты игрока
			cutscenes(0); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==9) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,V,V,V,V,V,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,V,V,V,V,V,W,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,V,V,V,V,V,W,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,V,V,V,V,V,W,F,F,F,W,W,B,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,V,V,V,V,V,W,W,L,Y,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,V,V,V,V,V,V,V,W,F,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка
 {V,V,V,V,V,V,V,V,V,V,W,W,W,W,B,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 4,player_x = 10; //стартовые координаты игрока
			cutscenes(0); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==10) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,W,F,F,F,F,F,F,C,F,F,F,F,F,F,F,F,F,L,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,W,F,W,A,X,W,F,Y,F,F,U,W,V,V,V,V,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,W,F,F,F,W,W,F,F,F,F,U,W,V,V,V,V,V,V,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,W,F,F,F,F,F,F,Y,F,F,U,W,V,V,V,V,V,V,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,W,F,F,F,Y,Y,D,F,F,F,D,D,D,D,D,D,V,V,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка
 {V,V,V,W,W,W,W,W,W,W,W,W,W,W,W,X,X,X,X,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 7,player_x = 4; //стартовые координаты игрока
			cutscenes(0); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==11) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,W,L,D,U,U,C,L,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,W,U,F,U,U,F,U,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,W,D,D,F,F,C,C,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,W,D,D,F,F,C,C,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,W,A,F,A,A,F,A,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,W,L,D,A,A,C,L,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 3,player_x = 7; //стартовые координаты игрока
			cutscenes(0); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==12) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,U,C,C,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,W,F,F,W,F,F,V,V,V,F,F,F,V,V,V,F,F,F,V,V,U,X,A,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,W,F,F,W,F,F,Y,D,D,F,V,F,F,F,F,F,F,F,V,V,U,X,A,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,W,F,F,W,F,F,V,V,V,F,F,F,V,B,F,F,F,F,V,V,U,X,A,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,L,F,F,F,F,F,V,V,V,V,F,F,V,V,V,V,F,V,V,W,U,X,A,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,L,F,F,F,F,F,V,V,V,V,F,F,F,V,V,V,F,V,V,W,U,X,A,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,W,F,F,W,V,F,F,F,C,C,F,F,F,V,V,F,F,F,V,V,U,X,A,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,W,F,F,W,V,F,W,F,V,V,V,V,V,D,U,F,F,F,V,V,U,X,A,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка
 {V,V,V,W,F,F,W,V,F,F,F,F,D,D,D,D,A,C,F,F,F,V,V,U,X,A,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,W,W,W,W,W,W,W,W,W,W,W,W,W,X,W,W,W,W,W,W,D,D,A,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 5,player_x = 4; //стартовые координаты игрока
			cutscenes(0); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==13) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,V,V,V,V,W,W,W,W,B,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,V,V,V,V,W,D,D,D,D,D,D,U,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,V,V,V,W,W,A,D,D,D,D,U,U,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,V,V,V,W,X,A,A,W,W,W,U,U,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,V,V,V,W,X,A,A,W,B,D,U,U,Y,F,L,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,V,V,V,W,X,A,A,W,A,W,U,U,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,V,V,V,W,W,A,A,C,C,C,C,U,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,V,V,V,V,W,A,C,C,C,C,C,C,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка
 {V,V,V,V,V,W,W,W,W,W,W,W,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 4,player_x = 9; //стартовые координаты игрока
			cutscenes(0); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==14) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {W,X,D,D,D,D,D,D,D,D,D,U,D,D,D,D,D,D,D,D,D,U,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {W,X,A,D,D,D,D,D,D,D,U,U,A,D,D,D,D,D,D,D,U,U,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {W,X,A,A,D,D,D,D,D,U,U,U,A,A,D,D,D,D,D,U,U,U,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {W,W,A,A,A,V,V,V,V,U,U,U,A,A,A,V,V,V,V,U,U,U,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {W,W,A,A,A,W,W,F,F,U,U,U,A,A,A,F,F,W,W,U,U,U,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {W,W,A,A,A,B,W,F,F,U,U,U,A,A,A,F,L,W,B,U,U,U,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {W,W,A,A,A,W,W,F,F,U,U,U,A,A,A,F,F,W,W,U,U,U,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {W,W,A,A,A,C,C,C,C,C,U,U,A,A,A,C,C,C,C,C,U,U,X,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка
 {W,W,A,A,C,C,C,C,C,C,C,U,A,A,C,C,C,C,C,C,C,U,X,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {W,W,A,C,C,C,C,C,C,C,C,C,A,C,C,C,C,C,C,C,C,C,X,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 5,player_x = 7; //стартовые координаты игрока
			cutscenes(0); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
		}
		else if (level==15) { //номер уровня
			char pullup=1;  //то откуда игрок будет тянуть при старте
			char pulldown=0;
			char pullleft=0;
			char pullright=0;
			restartlevel=0; //оставить 0
unsigned char struclevel[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {V,W,F,F,F,F,F,F,X,W,C,C,C,W,F,F,F,F,F,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //0  V=пустота        массив отвечающий за игровую карту
 {V,W,F,F,F,F,F,F,X,W,F,F,Y,W,Y,Y,Y,Y,Y,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //1  F=пол
 {V,W,W,W,W,W,F,F,W,W,D,D,D,W,F,F,F,F,Y,F,F,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //2  W=стена
 {V,W,B,B,B,W,F,F,W,W,W,F,F,W,F,F,W,X,Y,F,F,W,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //3  A=конвеер_вверх
 {V,L,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,W,Y,F,F,F,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //4  C=конвеер_влево
 {V,L,F,F,F,F,F,F,F,F,F,F,F,F,F,F,F,W,Y,F,F,F,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //5  U=конвеер_вниз
 {V,W,B,B,B,W,W,F,W,W,W,F,W,W,W,F,W,X,Y,F,F,W,F,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //6  D=конвеер_вправо
 {V,W,W,W,W,W,F,F,F,W,U,C,C,W,F,F,F,F,Y,F,F,W,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //7  B=кнопка
 {V,W,X,U,F,F,F,F,F,W,U,Y,A,W,F,F,F,Y,Y,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}, //8  Y=кислота
 {V,W,W,A,F,F,F,F,F,W,D,D,A,W,F,F,F,F,F,F,F,F,W,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V,V}};//9  X=лазер(раздатчик)
unsigned char object[10][44] = {
//                    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
//0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3 4 4 4 4
 {0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0 массив отвечающий за положение кубов
 {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //1 1=куб присутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //2 0=куб отсутствует
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //3
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //4
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //5
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //6
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //7
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //8
 {0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};//9
			char player_y = 5,player_x = 2; //стартовые координаты игрока
			cutscenes(0); //отображаемая при старте катсцена
			while(1) { //начало цикла игры
				if (exitlevel!=0) {
					break;
				}
				else if(restartlevel!=0) {
					break;
				}
				physics(&player_y,&player_x,&object,&struclevel); //блок физики
				graphics(player_y,player_x,&struclevel,&object);         //блок графики
				if (restartlevel==0&&exitlevel==0) { //пропуск блока ввода
					enter(&player_y,&player_x,&object,&struclevel,&pullup,&pulldown,&pullleft,&pullright);//блок ввода
				}
			}
			if(level!=15) {
				level=0;
			}
		}
		else {
			clear();
			printf("error level\n");
			exitlevel=1;
		}
	}
}

void select_level(void) {
while(1) {
deaths=0;
action_counter=0;
efficiency=0;
exitlevel=0;
clear();
printf("        Enter the number of the level       \n");
printf("             you want to enter              \n");
printf("                                            \n");
printf("  1(cube    ) 7 (bridge  ) 13(orbits  )     \n");
printf("  2(acid    ) 8 (circles ) 14(vortices)     \n");
printf("  3(void    ) 9 (studio  ) 15(rooms   )     \n");
printf("  4(conveyor) 10(one cube)                  \n");
printf("  5(lasers  ) 11(centre  ) 0 to get out     \n");
printf("  6(beam    ) 12(ejection)                  \n");
printf("                                            \n");
numinputt(&level);
if (level == 0) {
break;
}
else {
start_level=level;
play_level();
}
}
}

int main(void) {
calebritewindow();
while (1) {
clear();
printf("v1                                        /\\\n");
printf("                ###########               \\/\n");
printf("                #\e[41mC.T.S.L.I\e[0m#                 \n");
printf("          #######################           \n");
printf("          #\e[47m     \e[0m#\e[47m  \e[0m#   #\e[47m  \e[0m#\e[47m     \e[0m#           \n");
printf("          #\e[47m     \e[0m#\e[47m  \e[0m#   #\e[47m  \e[0m#\e[47m     \e[0m#           \n");
printf("  /========================================|\n");
printf("  |       P = Play       S = Settings      |\n");
printf(" /        E = Exit    A = About the game   |\n");
printf(" |=========================================|\n");
inputt(&input);
if (input == 'a'||input == 'A') {
About_the_game();
}
else if(input == 'e'||input =='E') {
clear();
return 0;
}
else if(input == 's'||input == 'S') {
Setting_menu();
}
else if(input == 'p'||input == 'P') {
select_level();
}
}
}