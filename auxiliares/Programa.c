#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>

#define MAX 500
#define BUFFER 1000
#define ID_SIZE 5
#define PASS_SIZE 6

//--------------------------------------------------------------------------DATA

//Define estrutura de dados ligados
typedef struct users * USERS;

struct users{ // lista ligada dos users
	
	char* id;
	char* pass;
	int type;
	USERS next;
};

typedef struct clients * CLIENTS;

struct clients{ // lista ligada dos clients
	
	int client_id;
	char* client_name;
	char* address;
	char* postal_code;
	char* city;
	char* country;
	int mobile_phone;
	char* mail;
	char* birth_date;
	int tax_number;
	int monthly_income;
	int balance;
	CLIENTS next;
};


//---------------------------------------------------------------------------AUX

//Preenche estrutura de dados ate ao maximo do buffer
void pop_buffer(char buffer[], int size){
	int i = 0;
	while(i < size){
		buffer[i] = '!';
		i++;
	}
}

//inicializa a estrutura de dados
USERS init_USERS(){

	USERS users = malloc(sizeof(struct users));
	users->id = " ";
	users->pass = " ";
	users->type = 0;
	users->next = NULL;

	return users;
}

CLIENTS init_CLIENTS(){

	CLIENTS clients = malloc(sizeof(struct clients));
	clients->client_id = 0;
	clients->client_name = " ";
	clients->address = " ";
	clients->postal_code = " ";
	clients->city = " ";
	clients->country = " ";
	clients->mobile_phone = 0;
	clients->mail = " ";
	clients->birth_date = " ";
	clients->tax_number = 0;
	clients->monthly_income = 0;
	clients->balance = 0;
	clients->next = NULL;

	return clients;
}

void add_user(USERS users, char* id, char* pass, int type){
	
	USERS aux = users;
	if(aux == NULL){
		
		aux = init_USERS();
		aux->id = id;
		aux->pass = pass;
		aux->type = type;
		aux->next = NULL;
	}

	while (aux->next != NULL){
		
		aux = aux->next;
	}
	aux->next = init_USERS();
	aux = aux->next;
	aux->id = id;
	aux->pass = pass;
	aux->type = type;
	aux->next = NULL;
}

void add_client(CLIENTS clients, int client_id, char* client_name, char* address, 
				char* postal_code, char* city, char* country, int mobile_phone, 
				char* mail, char* birth_date, int tax_number, double monthly_income, 
				double balance){
	
	CLIENTS aux = clients;
	if(aux == NULL){
		
		aux = init_CLIENTS();
		aux->client_id = client_id;
		aux->client_name = client_name;
		aux->address = address;
		aux->postal_code = postal_code;
		aux->city = city;
		aux->country = country;
		aux->mobile_phone = mobile_phone;
		aux->mail = mail;
		aux->birth_date = birth_date;
		aux->tax_number = tax_number;
		aux->monthly_income = monthly_income;
		aux->balance = balance;
		aux->next = NULL;
	}
	while (aux->next != NULL){
		
		aux = aux->next;
	}
	aux = init_CLIENTS();
	aux->client_id = client_id;
	aux->client_name = client_name;
	aux->address = address;
	aux->postal_code = postal_code;
	aux->city = city;
	aux->country = country;
	aux->mobile_phone = mobile_phone;
	aux->mail = mail;
	aux->birth_date = birth_date;
	aux->tax_number = tax_number;
	aux->monthly_income = monthly_income;
	aux->balance = balance;
	aux->next = NULL;
}


//------------------------------------------------------------------------PARSER

//Abrem os ficheiros users e clients e populam a estrutura de daodos
USERS parser_users(USERS users){
	
	FILE* fp;
	char str [BUFFER];
	pop_buffer(str, BUFFER);
	fp = fopen("users.TXT", "r");
	if(fp == NULL){
		
		printf("I/O error\n");
		exit(1);
	}
	fgets(str, MAX, fp);
	fclose(fp);
	int index = 0; 	
	while(str[index] != '!'){

		index++;
	}
	
	USERS aux = users;
	
	int i = 0;
	int j = 0;
	int k = 0;
	
	while (j < index-1){

		while (str[j] != '/'){
			
			j++;
		}
		char user_id[j - i];
		k = 0;
		while (i < j){
			
			user_id[k] = str[i];
			i++;
			k++;
		}

		i++;
		j++;
		while(str[j] != '/'){
			
			j++;
		}
		k = 0;
		char user_pass[j - i];
		while (i < j){
			
			user_pass[k] = str[i];
			i++;
			k++;
		}

		j++;
		i++;
		while(str[j] != '/'){
			
			j++;
		}
		k = 0;
		int user_type = 0;
		while (i < j){
			
			user_type = atoi(&str[i]);
			i++;
		}

		j = j + 2;
		i = i + 2;
		
		aux->id = user_id;
		aux->pass = user_pass;
		
		aux->id = (char*) malloc(strlen(user_id)+1);
		strcpy(aux->id, user_id);
		aux->pass = (char*) malloc(strlen(user_pass)+1);
		strcpy(aux->pass, user_pass);
		aux->type = user_type;
		aux->next = init_USERS();

//		printf("%s\n", user_id);
//		printf("%s\n", user_pass);
//		printf("%d\n", user_type);

		aux = aux->next;
	}

//	free(aux);
	aux->next = NULL;
	aux = users;
	
/*	while(aux->next != NULL){

		puts("\n");
		printf("%d\n", atoi(aux->id));
		printf("%d\n", atoi(aux->pass));
		printf("%d\n", aux->type);
		aux = aux->next;
	}*/

	return users;
}

CLIENTS parser_clients(CLIENTS clients){
	
	FILE* fp;
	char str [BUFFER];
	pop_buffer(str, BUFFER);
	fp = fopen("clients.TXT", "r");
	if(fp == NULL){
		
		printf("I/O error\n");
		exit(1);
	}
	fgets(str, MAX, fp);
	fclose(fp);
	int index = 0; 	
	while(str[index] != '!'){

		index++;
	}
	
	CLIENTS aux = clients;
	
	int a = 0;
	int b = 0;
	int c = 0;
	
	while (b < index-1){

//------client_id------------------------------------------
		while (str[b] != '/'){
			
			b++;
		}
		int client_id = 0;
		char temp1[b - a];
		c = 0;
		while (a < b){
			
			temp1[c] = str[a];
			a++;
			c++;
		}
		client_id = atoi(temp1);
		a++;
		b++;
		
//------client_name----------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		char client_name[b - a];
		while (a < b){
			
			client_name[c] = str[a];
			a++;
			c++;
		}
		b++;
		a++;
		
//------address--------------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		char address[b - a];
		while (a < b){
			
			address[c] = str[a];
			a++;
			c++;
		}
		b++;
		a++;
		
//------postal_code----------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		char postal_code[b - a];
		while (a < b){
			
			postal_code[c] = str[a];
			a++;
			c++;
		}
		b++;
		a++;
		
//------city-----------------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		char city[b - a];
		while (a < b){
			
			city[c] = str[a];
			a++;
			c++;
		}
		b++;
		a++;
		
//------country--------------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		char country[b - a];
		while (a < b){
			
			country[c] = str[a];
			a++;
			c++;
		}
		b++;
		a++;
		
//------mobile_phone---------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		int mobile_phone = 0;
		char temp2[b - a];
		while (a < b){
			
			temp2[c] = str[a];
			a++;
			c++;
		}
		mobile_phone = atoi(temp2);
		b++;
		a++;
		
//------mail-----------------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		char mail[b - a];
		while (a < b){
			
			mail[c] = str[a];
			a++;
			c++;
		}
		b++;
		a++;
		
//------birth_date-----------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		char birth_date[b - a];
		while (a < b){
			
			birth_date[c] = str[a];
			a++;
			c++;
		}
		b++;
		a++;
		
//------tax_number-----------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		int tax_number = 0;
		char temp3[b - a];
		while (a < b){
			
			temp3[c] = str[a];
			a++;
			c++;
		}
		tax_number = atoi(temp3);
		b++;
		a++;

//------monthly_income-------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		int monthly_income = 0;
		char temp4[b -a];
		while (a < b){
			
			temp4[c] = str[a];
			a++;
			c++;
		}
		monthly_income = atoi(temp4);
		b++;
		a++;
		
//------balance--------------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		int balance = 0;
		char temp5[b - a];
		while (a < b){
			
			temp5[c] = str[a];
			a++;
			c++;
		}
		balance = atoi(temp5);
		b = b + 2;
		a = a + 2;

//---------------------------------------------------------

		aux->client_id = client_id; //int 
		aux->client_name = client_name; //char
		aux->address = address; //char
		aux->postal_code = postal_code; //char
		aux->city = city; //char
		aux->country = country; //char
		aux->mobile_phone = mobile_phone; //int
		aux->mail = mail; //char
		aux->birth_date = birth_date; //char
		aux->tax_number = tax_number; //int
		aux->monthly_income = monthly_income; //double
		aux->balance = balance; //double
		
		aux->client_name = (char*) malloc(strlen(client_name)+1);
		strcpy(aux->client_name, client_name);
		
		aux->address = (char*) malloc(strlen(address)+1);
		strcpy(aux->address, address);
		
		aux->postal_code = (char*) malloc(strlen(postal_code)+1);
		strcpy(aux->postal_code, postal_code);
		
		aux->city = (char*) malloc(strlen(city)+1);
		strcpy(aux->city, city);

		aux->country = (char*) malloc(strlen(country)+1);
		strcpy(aux->country, country);
		
		aux->mail = (char*) malloc(strlen(mail)+1);
		strcpy(aux->mail, mail);
		
		aux->birth_date = (char*) malloc(strlen(birth_date)+1);
		strcpy(aux->birth_date, birth_date);
		
		aux->next = init_CLIENTS();

/*		printf("%d\n", client_id);
		printf("%s\n", client_name);
		printf("%s\n", address);
		printf("%s\n", postal_code);
		printf("%s\n", city);
		printf("%s\n", country);
		printf("%d\n", mobile_phone);
		printf("%s\n", mail);
		printf("%s\n", birth_date);
		printf("%d\n", tax_number);
		printf("%d\n", monthly_income);
		printf("%d\n\n", balance);*/

		aux = aux->next;
	}

	free(aux);
	aux->next = NULL;
	aux = clients;
	
/*	while(aux->next != NULL){

		printf("%d\n", client_id);
		printf("%s\n", client_name);
		printf("%s\n", address);
		printf("%s\n", postal_code);
		printf("%s\n", city);
		printf("%s\n", country);
		printf("%d\n", mobile_phone);
		printf("%s\n", mail);
		printf("%s\n", birth_date);
		printf("%d\n", tax_number);
		printf("%d\n", monthly_income);
		printf("%d\n\n", balance);
		aux = aux->next;
	}*/

	return clients;
}


//-------------------------------------------------------------------------FUNCS

//Obtem username e password do utilizador do programa
int login(char *id, char *password){
	char c;
	int pos = 0;
	int flag = 0;

	printf("\n\n");
	printf("\tOLD BANK MANAGEMENT SYSTEM");
	printf("\n\n");
	printf("\tUSER LOGIN");
	printf("\n\n");
	printf("\tEnter User Username : ");
	scanf("%s", id);
	printf("\n");
	printf("\tEnter Your Password : ");
	scanf("%s", password);		
}

//Compara dados introduzidos com os dados presentes na estrutura de dados
int check(char* id, char* pass, USERS users){
	
	int i = 0;
	int flag = 0;
	
	USERS aux = users;
		
	while (aux->next != NULL){
		
		i = compare(id, pass, aux->id, aux->pass);
		
		if (i == 1){
							
			flag = aux->type;
//			return flag;
		}
		aux = aux->next;
	}
	return flag;
}

int compare(char* id, char* pass, char* aux_id, char* aux_pass){
	
	int i = 0;
	int j = 0;
	int k = 0;
	int r = 0;
	
	while(i < ID_SIZE){
		
		if(id[i] == aux_id[i]){
			
			j++;
		}
		i++;
	}
	
	if(i == j){
		
		while(k < PASS_SIZE){
			
			if(pass[k] == aux_pass[k]){
				
				r++;
			}
			k++;
		}
	}
	
	if(i == j && k == r){
		
		return 1;
	}
	else{
		
		return 0;		
	}
}

//Menu inicial para permissoes do tipo 1
void start_menu_1(){
	int flag = 1;
	int choice = -1;
	while (flag != 0){
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
//		system("cls");
		printf("\n\n");
		printf("\tOLD BANK MANAGEMENT SYSTEM");
		printf("\n\n");
		printf("\tChoose one option:\n\n");
		printf("\t1 - Open Client Page\n\t2 - Create a New Client\n"
				"\t3 - Deposit\n\t4 - Withdraw\n\n\t0 - Logout\n");
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		scanf(" %d", &choice);
		switch (choice){
			case 1:
//				open_account();
				break;
			case 2:
//				creat_new_account();
				break;
			case 3:
//				deposits();
				break;
			case 4:
//				withdraws();
				break;
			case 0:
//				logout();
				break;
			default:
				printf("\tInvalid operation.\nPlease, choose a valid option.\n\n");
		}
	}
}

//Menu inicial para permissoes do tipo 2
void start_menu_2(){
	int flag = 1;
	int choice = -1;
	while (flag != 0){
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
//		system("cls");
		printf("\n\n");
		printf("\tOLD BANK MANAGEMENT SYSTEM");
		printf("\n\n");
		printf("\tChoose one option:\n\n");
		printf("\t1 - Open Client Page\n\t2 - Create a New Client\n"
				"\t3 - Deposit\n\t4 - Withdraw\n\t5 - Simulate and Approve Credit\n"
				"\t6 - Search for a Client\n\n\t0 - Logout\n");
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		scanf(" %d", &choice);
		switch (choice){ 
			case 1:
//				open_account(); 
				break;
			case 2:
//				open_new_account(); 
				break;
			case 3:
//				deposits(); 
				break;
			case 4:
//				withdraws(); 
				break;
			case 5:
//				simulate_credit(); 
				break;
			case 6:
//				search_clients(); 
				break;
			case 0:
//				logout(); 
				break;
			default:
				printf("\tInvalid operation.\nPlease, choose a valid option.\n\n");
		}
	}
}

//Menu inicial para permissoes do tipo 3
void start_menu_3(){
	int flag = 1; 
	int choice = -1; 
	while (flag != 0){
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
//		system("cls");
		printf("\n\n");
		printf("\tOLD BANK MANAGEMENT SYSTEM");
		printf("\n\n");
		printf("\tChoose one option:\n\n");
		printf("\t1 - Open Client Page\n\t2 - Create a New Client\n"
				"\t3 - Deposit\n\t4 - Withdraw\n\t5 - Simulate and Approve Credit\n"
				"\t6 - Search for a Client\n\t7 - Creat a new User\n\t8 - Delete User\n"
				"\t9 - Backup All Data\n\n\t0 - Logout\n");
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		scanf(" %d", &choice);
		switch (choice){
			case 1:
//				open_account(); 
				break;
			case 2:
//				open_new_account(); 
				break;
			case 3:
//				deposits(); 
				break;
			case 4:
//				withdraws(); 
				break;
			case 5:
//				simulate_credit(); 
				break;
			case 6:
//				search_clients(); 
				break;
			case 7:
//				new_user(); 
				break;
			case 8:
//				delete_user(); 
				break;
			case 9:
//				backup(); 
				break;
			case 0:
//				logout(); 
				break;
			default:
				printf("\tInvalid operation.\nPlease, choose a valid option.\n\n");
		}
	}
}

//--------------------------------------------------------------------------MAIN
int main(){
	
	int flag, i = 0;
	char id[ID_SIZE];
	char password[PASS_SIZE];
	int userType = 0;
	
	USERS us = init_USERS();	
	us = parser_users(us);
	USERS aux1 = us;
	
	CLIENTS cl = init_CLIENTS();
	cl = parser_clients(cl);
	CLIENTS aux2 = cl;
	
	while (userType == 0){
	
		login(id, password);

		userType = check(id, password, us);
	
		if(userType != 0){
			printf("\n\n");
			printf("\tCorrect Username And Password\n");
			printf("\n\n\tWelcome to the System\n\n");
			
			if (userType == 1){
			start_menu_1();
			}
			else if (userType == 2){	
				start_menu_2();
			}
			else if (userType == 3){	
				start_menu_3();
			}
		}
		else{
			printf("\n\n");
			printf("\tInvalid Username And Password. Try Again\n\n");
		}
	}
	return 1;
}

