#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX 20

char** createMaze(int row , int column  , char **maze , int *headRow , int *headColumn);
void printMaze(int row , int column , char **maze);
void replaceApples(int row , int column , int apple , char **maze);
int** visitedMatrix(int row , int column , char **maze , int** visited);
void printVisitedMatrix(int row , int column , int** visited);
int depthFirstSearch(int **visited , int row , int column , char **maze , int currRow , int currCol , int *score , int *wrong);


int main(){
	
	int row , column ,apple ;
	char **maze = NULL;
	int **visited = NULL;
	int *headRow =malloc(sizeof(int));
	int *headColumn =malloc(sizeof(int));
	int *score , *wrong;
	
	printf("\n\t\tBEYDA GULER\n\t\t  19011010\n\n");

	printf("Enter the number of rows and columns ! \n# of rows : ");
	scanf("%d",&row);
	printf("# of columns : ");
	scanf("%d",&column);
	
	if(row < 15)
		row=15;
	if(column < 15)
		column=15;
	
	maze = createMaze(row,column,maze,headRow,headColumn);
	printf("\n\t\tHERE IS THE MAZE !\n");
	printMaze(row,column,maze);
	
	printf("How many apples do you want to replace --> ");
	scanf("%d",&apple);
	system("cls");
	replaceApples(row,column,apple,maze);
	printf("\n\tMAZE WITH %d APPLES !!\n",apple);
	printMaze(row,column,maze);
	
	visited = visitedMatrix(row,column,maze,visited);
	//printVisitedMatrix(row,column,visited);
	score = malloc(sizeof(int));
	(*score) = 0 ;
	
	wrong = malloc(sizeof(int));
	
	

	if(depthFirstSearch(visited,row,column,maze,*headRow,*headColumn,score,wrong) != 1){  //c yoksa
		printf("Couldn't find exit !");
	}
		
	else{
		printMaze(row,column,maze);
		printf("I found the exit with score : %d",*score);
	}
	
	
	return 0;
}




void printVisitedMatrix(int row , int column , int** visited){
	
	int i,j;
	
	for(i = 0 ; i < row ; i++){
		for(j = 0 ; j < column ; j++)
			printf("%d",visited[i][j]);
		printf("\n");
	}
}


int** visitedMatrix(int row , int column , char **maze , int** visited){
	
	int i,j;
	visited = malloc(row * sizeof(int*));
	for(i = 0 ; i < column ; i++){
		visited[i] = malloc(column * sizeof(int*));
	}

	for(i = 0 ; i < row ; i++){
		for(j = 0 ; j < column ; j++){
			
			if(maze[i][j] == 'o')                                                      //apple
				visited[i][j] = 2 ;
			else if(maze[i][j] == 'c')                                                 //exit
				visited[i][j] = 3;
			else if(maze[i][j] == '+' || maze[i][j] == '-' || maze[i][j] == '|')      //walls
				visited[i][j] = 0; 
			else                                                                      //open road
				visited[i][j] = 1;  
		}
	}
	
	return visited;
}

void replaceApples(int row , int column , int apple , char **maze){
	
	int randomRow,randomCol ;
	int i = 0;
	printf("\n");
	do{
		randomRow = rand()%row;
		randomCol = rand()%column;
		if(maze[randomRow][randomCol] == ' '){
			maze[randomRow][randomCol] = 'o';
			i++;
		}
			
	}while(i < apple);
	
}

void printMaze(int row , int column , char **maze){
	
	int i,j ;
	printf("\n\n");
	for(i = 0 ; i < row ; i++){
		for( j =0 ; j < column ; j++)
			printf("%c",maze[i][j]);
			
	printf("\n");
	}
}

char** createMaze(int row , int column  , char **maze , int *headRow , int *headColumn){
	
	int i,j;
	FILE* f;
	char newChar ;  
	char fName[MAX];
	
	printf("\nEnter file name in the format xxx.txt : ") ;
	scanf("%s",fName);
	
	if((f = fopen(fName,"r")) == NULL){
		printf("Couldn't open file!");
		return;
	}
	
	maze = malloc(row * sizeof(char*));
	for(i = 0 ; i < column ; i++){
		maze[i] = malloc(column * sizeof(char*));
	}

	for(i = 0 ; i < row ; i++){
		
		for(j = 0 ; j < column ; j++){
			
			newChar = getc(f);
				//printf("sa");
			if(newChar == '\n'){
				newChar = getc(f);
			}
			
			maze[i][j] = newChar ;
			//printf("i : %d j : %d YENÝ CHAR : %c",i,j,newChar);
			if(newChar == 'b'){
				(*headRow)= i;
				(*headColumn) = j;
			}
				
		}
	}
	fclose(f);
	
	return maze;	
}
int depthFirstSearch(int **visited , int row , int column , char **maze , int currRow , int currCol , int *score , int *wrong){
	
	int *curr ;
	curr = &(visited[currRow][currCol]);
	
	if(*curr == 3)
		return 1;
	
	if(*curr == 2){
		*score += 10 ;
		printf("I found an apple ! New score : %d  ",*score);
	}
	if((*curr == 2 || *curr == 1) ){
		if(*wrong == 1){
			*score -= 5;
			printf("Wrong way ! New score : %d  ",*score);
		}
		
		printf("Go ahead !");
		printMaze(row,column,maze);
		printf("Total Score : %d\n",*score);
		
		if(*wrong == 1)
			(*wrong)--;
		
		sleep(1);
		system("cls");
		
		maze[currRow][currCol] = '*';
		*curr = 10;
		
		
		//Recursive DFS approach
		
		if(depthFirstSearch(visited,row,column,maze,currRow,currCol-1,score,wrong))
			return 1;
		
		if(depthFirstSearch(visited,row,column,maze,currRow-1,currCol,score,wrong))
			return 1;
		
		if(depthFirstSearch(visited,row,column,maze,currRow,currCol+1,score,wrong))
			return 1;
		
		if(depthFirstSearch(visited,row,column,maze,currRow+1,currCol,score,wrong))
			return 1;
		
		
		*wrong = 1;
		
		
		printMaze(row,column,maze);
		printf("Total Score : %d\n",*score);
		
		sleep(1);
		system("cls");
		
		maze[currRow][currCol] = ' ' ;  //Delete * character while coming back
	}
	
	
	return 0;
}


