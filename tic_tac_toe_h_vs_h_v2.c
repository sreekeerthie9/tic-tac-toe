#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<conio.h>

#define PERSON_1_VALUE 'X'
#define PERSON_2_VALUE 'O'
#define PERSON_1 1
#define PERSON_2 0
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

void box(int col,int row){
	int ctr1;
	int ctr2;
	int ctr3;
	int ctr4;
	
	gotol(col,row);
	printf("%c",TLE);
	for(ctr1=0;ctr1<DIM;ctr1++){
		for(ctr2=0;ctr2<WIDTH;ctr2++){
			printf("%c",HOR);
		}
		printf("%c",TT);
	}
	printf("%c",BS);
	printf("%c",TRE);
	
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
		printf("%c", LT);
		for(ctr2=0;ctr2<DIM;ctr2++){
			for(ctr1=0;ctr1<WIDTH;ctr1++){
				printf("%c",HOR);
			}
			printf("%c",PLUS);
		}
		printf("%c%c", BS, RT);
	}
	
	gotol(col,row);
	printf("%c",BLE);
	for( ctr2 = 0; ctr2 < DIM; ctr2+=1)
   	{
       for(ctr1 = 0;  ctr1 < WIDTH ; ctr1+=1)
       {
      		printf("%c", HOR);
       }
       printf("%c", BT );
	}
   printf("%c%c", BS, BRE);
	
}

void declarewinner(int winner){
	gotol(0,20);
	if(winner==PERSON_1)
		printf("person 1 has won\n");
	else
		printf("person 2 has won\n");
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




void playtictactoe(int whoseTurn){
	char board[SIDE][SIDE];
	int moveindex=0;
	int r=0;
	int c=0;
	
	showinstructions();
	initialise(board);
	showboard(board);
	
	while(gameover(board)==false && moveindex!=SIDE*SIDE){
		int n;
		if(whoseTurn==PERSON_1){
			int n;
			int i;
			int j;
			gotol(0,13);
			printf("\nperson 1\n");
			gotol(0,14);
			printf("\nenter the position\n");
			scanf("%d",&n);
			n--;
			r=n/SIDE;
			c=n%SIDE;
			if(board[r][c]=='*' && n<9 && n>=0){
				board[r][c]=PERSON_1_VALUE;
				showboard(board);
				moveindex++;
				whoseTurn = PERSON_2;
			}
			else if(board[r][c]!='*' && n<9 && n>=0){
				gotol(0,11);
				printf("\nposition is occupied\n");
			}
			else if( n<0 || n>8){
				gotol(0,12);
				printf("\ninvalid position\n");
			}
		}
		
		else if(whoseTurn==PERSON_2){
			int pos;
			int i;
			int j;
			gotol(0,13);
			printf("\nperson 2\n");
			gotol(0,14);
			printf("\nenter the position\n");
			scanf("%d",&pos);
			pos--;
			r=pos/SIDE;
			c=pos%SIDE;
			if(board[r][c]=='*' && pos<9 && pos>=0){
				board[r][c]=PERSON_2_VALUE;
				showboard(board);
				moveindex++;
				whoseTurn = PERSON_1;
			}
			else if(board[r][c]!='*' && pos<9 && pos>=0){
				gotol(0,11);
				printf("\nposition is occupied\n");
			}
			else if( pos<0 || pos>8){
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
			if(whoseTurn==PERSON_1)
				whoseTurn=PERSON_2;
			else 
				whoseTurn=PERSON_1;
			
			declarewinner(whoseTurn);
		}
	
}

int main(){
	bool cont=true;
	char temp;
	int turn;
	do{
		printf("\nwho want to play first person 1 or 2(1/2):\n");
		scanf("%d",&turn);
		if(turn==1){
			playtictactoe(PERSON_1);
		}
		else if(turn == 2){
			playtictactoe(PERSON_2);
		}
		else{
			printf("\ninvalid choice\n");
		}
		printf("\n\n\n\ndo you want to quit the game(y/n):\n");
		scanf("%s",&temp);
		if(temp=='y'){
			cont=false;
		}
		else{
			cont=true;
		}
	}while(cont==true);
}
