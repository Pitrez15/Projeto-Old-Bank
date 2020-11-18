#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct credentials{
	
	
};

void get_ID_and_PASS(char fileName[30],char *id,char *pass, int *userType){
	
	FILE *F = fopen(fileName,"r");
	if(F){
		
		int count = 0;
		while(!feof(F)){
			
			char rawLine[50];
			fscanf(F,"%s",rawLine);			
			printf("rawline - %s \n", rawLine);
			
			if(!count++){

				strcpy(id,rawLine);
				printf("id - %s \n", id);
			}
			else {
			
				strcpy(pass,rawLine);
				printf("pass - %s \n", pass);
				break;
			}
		}
	}
	else 
		printf("Cannot open this file");
	fclose(F);
}

int main(){
	
	char fileName[30] = "users.txt";
	char userID[50],userPassW[50];
	int userType;
	char strID[50]="\0",strPASSW[50]="\0";
	char IDpref[50] = "user_id:\0",PASSWpref[50] = "password:\0";
	
	get_ID_and_PASS(fileName,userID,userPassW, &userType);
	
	char c;
	int pos = 0;
	
	printf("\n\n");
	printf("\tLOGIN SECURITY SYSTEM IN C USING TEXT FILES");
	printf("\n\n");
	printf("\tEnter User Name : ");
	scanf("%s",&strID);
	printf("\n");
	printf("\tEnter Your Password : ");
	

	do {
		c = getch();
		if( isprint(c) ){
			strPASSW[ pos++ ] = c;
			printf("%c", '*');
		}
		else if( c == 9 && pos ){
			
			strPASSW[pos--] = '\0';
			printf("%s", "\b \b");
		}
	} while( c != 13 );
	
	int a = strcmp(strID,userID);
	int b = strcmp(strPASSW,userPassW);
	
	if (a==0 && b==0){
		
		printf("\n\n");
		printf("\tCorrect Username And Password\n");
		printf("\n\n\tWelcome to the System\n\n"); 
	}
	else{
		
		printf("\n\n");
		printf("\tInvalid Username And Password. Try Again\n\n");
	}
	
	
	
}
