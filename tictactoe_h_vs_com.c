#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>

#define COMPUTERVALUE 'X'
#define HUMANVALUE 'O'
#define COMPUTER 0
#define HUMAN 1
#define SIDE 3

#define TLE 218
#define TRE 191
#define BRE 217
#define BLE 192
#define TT 194
#define LT 195
#define RT 180
#define BT 193
#define HOR 196
#define VER 179
#define SP 32
#define PLUS 197
#define BS 8
#define NL 10
#define TOTCOLS 100
#define TOTROWS 10
#define DIM     3
#define WIDTH   5

void gotol(int x, int y){


 COORD coord;

 coord.X = x;

 coord.Y = y;

 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void box(int col, int row){
	int ctr1;
	int ctr2;
	int ctr3;
	gotol(col,row);
	printf("%c",TLE);
	for(ctr2=0;ctr2<DIM;ctr2++){
		for(ctr1=0;ctr1<WIDTH;ctr1++){
			printf("%c",HOR);
		}
		printf("%c",TT);
	}
	printf("%c%c",BS,TRE);
	for(ctr3=0;ctr3<DIM;ctr3++){
		row+=1;
		gotol(col,row);
		for(ctr2=0;ctr2<=DIM;ctr2++){
			printf("%c",VER);
			for(ctr1=0;ctr1<WIDTH;ctr1++){
				printf("%c",SP);
			}
		}
		row+=1;
		gotol(col,row);
		printf("%c",LT);
		for(ctr2=0;ctr2<DIM;ctr2++){
			for(ctr1=0;ctr1<WIDTH;ctr1++){
				printf("%c",HOR);
			}
			printf("%c",PLUS);
		}
		printf("%c%c",BS,RT);
	}
	gotol(col,row);
	printf("%c",BLE);
	for(ctr2=0;ctr2<DIM;ctr2++){
		for(ctr1=0;ctr1<WIDTH;ctr1++){
			printf("%c",HOR);
		}
		printf("%c",BT);
	}
	printf("%c%c",BS,BRE);
}

void declarewinner(int winner){
	gotol(0,20);
	if(winner == COMPUTER)
		printf("COMPUTER has won\n");
	else
		printf("HUMAN has won\n");
}


void initialise(char board[][SIDE]){
	int i;
	int j;
	for(i=0;i<SIDE;i++){
		for(j=0;j<SIDE;j++){
			board[i][j]='*';
		}
	}
}

void showinstructions(){
	
	int row;
	int col;
	int ctr;
	int nums;
	
	col=50+((TOTCOLS/2)-(((WIDTH)*(DIM)+(DIM+1))/2));
	row=TOTROWS-(((1)*(DIM)+(DIM+1))/2);
	gotol(col-3,row-1);
	printf("enter any number from 1 to 9");
	box(col,row);
	row+=1;
	col+=3;
	gotol(col,row);
	for( nums = 1, ctr = 0; nums <= 9; nums+=1, ctr+=1)
   {
        if ( ctr == DIM)
        {
            ctr = 0;
            row += 2;
        }
       gotol(col + ( ctr * (WIDTH+1) ), row);
       printf("%d",nums);

   }
	
}

void showboard(char board[][SIDE]){
	
	int row;
	int col;
	int ctr;
	int i,j;
	int nums;
	
	i=0;
	j=0;
	
	col=((TOTCOLS/2)-(((WIDTH)*(DIM)+(DIM+1))/2));
	row=TOTROWS-(((1)*(DIM)+(DIM+1))/2);
	
	box(col,row);
	row+=1;
	col+=3;
	gotol(col,row);
	for( nums = 1, ctr = 0; nums <= 9; nums+=1, ctr+=1)
   {
        if ( ctr == DIM)
        {
            ctr = 0;
            row += 2;
            i++;
            j=0;
        }
       gotol(col + ( ctr * (WIDTH+1) ), row);
       printf("%c",board[i][j]);
       j++;
   }
}



bool columncrossed(char board[][SIDE]){
	int i;
	for(i=0;i<SIDE;i++){
		if( board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!='*')
			return(true);
	}
	return(false);
}

bool rowcrossed(char board[][SIDE]){
	int i;
	for(i=0;i<SIDE;i++){
		if( board[i][0]==board[i][1] &&
			board[i][1]==board[i][2] &&
			board[i][0]!='*')
		return true;
	}
	return false;
}

bool diagonalcrossed(char board[][SIDE]){
	
	if( board[0][0]==board[1][1] &&
		board[1][1]==board[2][2] &&
		board[0][0]!='*')
		return true;
		
	if( board[0][2]==board[1][1] &&
		board[1][1]==board[2][0] &&
		board[0][2]!='*')
		return true;
		
	return false;
}

bool gameover(char board[][SIDE]){
	return (rowcrossed(board) || columncrossed(board) || diagonalcrossed(board));
}

int minimax(char board[][SIDE], int depth, bool isCom){
	int i,j;
	int score;
	int bestscore;
	score = 0;
	
	if(gameover(board) == true){
		if(isCom == true)
			return -10;
		if(isCom == false)
			return 10;
	}
	else{
		if(depth<9){
			if(isCom == true){
				bestscore = -999;
				for(i=0;i<SIDE;i++){
					for(j=0;j<SIDE;j++){
						if(board[i][j] == '*'){
							board[i][j] = COMPUTERVALUE;
							score = minimax(board , depth+1 , false);
							board[i][j] = '*';
							if(score > bestscore){
								bestscore = score;
							}
						}
					}
				}
				return bestscore;
			}
			else if(isCom == false){
				bestscore = 999;
				for(i=0;i<SIDE;i++){
					for(j=0;j<SIDE;j++){
						if(board[i][j] == '*'){
							board[i][j] = HUMANVALUE;
							score = minimax(board , depth+1 , true);
							board[i][j] = '*';
							if(score < bestscore){
								bestscore = score;
							}
						}
					}
				}
				return bestscore;
				
			}
		}
		else{
			return 0;
		}
	}
}

int bestmove(char board[][SIDE] , int moveindex){
	int i,j;
	int x;
	int y;
	int score;
	int bestscore;
	x=-1;
	y=-1;
	score = 0;
	bestscore = -999;
	for(i=0;i<SIDE;i++){
		for(j=0;j<SIDE;j++){
			if(board[i][j] == '*'){
				board[i][j] = COMPUTERVALUE;
				score = minimax(board , moveindex+1 , false);
				board[i][j] = '*';
				if(score>bestscore){
					bestscore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*3+y;
}

void playtictactoe(int whoseturn){
	int moveindex;
	char board[SIDE][SIDE];
	moveindex=0;
	
	showinstructions();
	initialise(board);
	showboard(board);
	
	while(gameover(board) == false && moveindex != 9){
		int n;
		if(whoseturn == COMPUTER){
			int x;
			int y;
			n = bestmove(board,moveindex);
			x = n/SIDE;
			y = n%SIDE;
			board[x][y] = COMPUTERVALUE;
			showboard(board);
			moveindex++;
			whoseturn = HUMAN;
				
		}
		else if(whoseturn == HUMAN){
			int x;
			int y;
			gotol(0,14);
			printf("enter the position:\n");
			scanf("%d",&n);
			n--;
			x = n/SIDE;
			y = n%SIDE;
			if(board[x][y] == '*' && n<9 && n>=0){
				board[x][y] = HUMANVALUE;
				showboard(board);
				moveindex++;
				whoseturn = COMPUTER;
				
			}
			else if(board[x][y] != '*' && n<9 && n>=0){
				gotol(0,11);
				printf("\nposition already occupied\n");
			}
			else if(n>8 || n<0){
				gotol(0,12);
				printf("\ninvalid position\n");
			}
		}
	}
	if(gameover(board)==false && moveindex==SIDE*SIDE){
			gotol(0,20);
			printf("it is a draw");
	}
			
	else{
		if(whoseturn == COMPUTER)
			whoseturn = HUMAN;
		else 
			whoseturn = COMPUTER;
			
		declarewinner(whoseturn);
	}
}


int main(){
	
	bool cont=true;
	char temp;
	char turn;
	do{
		
		printf("\ndo you want to start(y/n):\n");
		scanf("%s",&turn);
		if(turn == 'n'){
			playtictactoe(COMPUTER);
		}
		else if(turn == 'y'){
			playtictactoe(HUMAN);
		}
		else{
			printf("\ninvalid choice\n");
		}
		gotol(0,24);
		printf("\n\n\n\ndo you want to quit the game(y/n):\n");
		scanf("%s",&temp);
		if(temp=='y'){
			cont=false;
		}
		else{
			cont=true;
		}
	}while(cont==true);
	
	return EXIT_SUCCESS;
}
