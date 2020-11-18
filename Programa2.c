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
	float monthly_income;
	float balance;
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

char *get_some_string(int size){
	
	int i = 0;
	
	char* str = (char*) calloc(size, sizeof(char));
	
    while(i < size){

        str[i] = '!';
        i++;
    }
    str[i] = '\0';
    return str;
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
		pop_buffer(user_id, j - i);
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
		pop_buffer(user_pass, j - i);
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
		
//		aux->id = user_id;
//		aux->pass = user_pass;
		
		aux->id = (char*) malloc(strlen(user_id)+1);
		strcpy(aux->id, user_id);
		
		aux->pass = (char*) malloc(strlen(user_pass)+1);
		strcpy(aux->pass, user_pass);
		
		aux->type = user_type;
		
//		free(user_id);
//		free(user_pass);
		
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

/*int alloc(char* aux, int size){
	
	aux = (char*) malloc(size);
	
	return aux;
}*/


CLIENTS parser_clients(CLIENTS clients){
	
	FILE* fp;
	char str [BUFFER];
	char* aux1;
	char* aux2;
	char* aux3;
//	char* aux4;
//	char* aux5;
//	char* aux6;
//	char* aux7;
	
	pop_buffer(str, BUFFER);
	fp = fopen("clients.TXT", "r");
	if(fp == NULL){
		
		printf("I/O error\n");
		exit(1);
	}
	fgets(str, MAX, fp);
	
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
		
//		aux12 = get_some_string(b - a);
		char temp1[b - a];
		pop_buffer(temp1, b - a);
		c = 0;
		while (a < b){
			
			temp1[c] = str[a];
			a++;
			c++;
		}
		client_id = atoi(temp1);
//		free(aux12);
		a++;
		b++;
		
//------client_name----------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		
		aux1 = get_some_string(b - a);
		
/*		char client_name[b - a];
		pop_buffer(client_name, b-a);*/
		while (a < b){
			
			aux1[c] = str[a];
			a++;
			c++;
		}
//		free(aux12);
		b++;
		a++;
		
//------address--------------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		aux2 = get_some_string(b - a);
		
/*		char address[b - a];
		pop_buffer(address, b - a);*/
		while (a < b){
			
			aux2[c] = str[a];
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
//		aux3 = get_some_string(b - a);
		char postal_code[b - a];
		pop_buffer(postal_code, b - a);
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
//		aux4 = get_some_string(b - a);
		char city[b - a];
		pop_buffer(city, b - a);
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
//		aux5 = get_some_string(b - a);
		char country[b - a];
		pop_buffer(country, b - a);
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
		pop_buffer(temp2, b - a);
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
//		aux6 = get_some_string(b - a);
		char mail[b - a];
		pop_buffer(mail, b - a);
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
//		aux7 = get_some_string(b - a);
		char birth_date[b - a];
		pop_buffer(birth_date, b - a);
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
		pop_buffer(temp3, b - a);
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
		float monthly_income = 0;
		char temp4[b -a];
		pop_buffer(temp4, b - a);
		while (a < b){
			
			temp4[c] = str[a];
			a++;
			c++;
		}
		monthly_income = atof(temp4);
		b++;
		a++;
		
//------balance--------------------------------------------
		while(str[b] != '/'){
			
			b++;
		}
		c = 0;
		float balance = 0;
		char temp5[b - a];
		pop_buffer(temp5, b - a);
		while (a < b){
			
			temp5[c] = str[a];
			a++;
			c++;
		}
		balance = atof(temp5);
		b = b + 2;
		a = a + 2;

//---------------------------------------------------------

		aux->client_id = client_id; //int 
		aux->client_name = aux1; //char
		aux->address = aux2; //char
		aux->postal_code = aux3; //char
		aux->city = city; //char
		aux->country = country; //char
		aux->mobile_phone = mobile_phone; //int
		aux->mail = mail; //char
		aux->birth_date = birth_date; //char
		aux->tax_number = tax_number; //int
		aux->monthly_income = monthly_income; //double
		aux->balance = balance; //double
		
//		free(aux->client_name);
		aux->client_name = (char*) malloc(strlen(aux1));
		strcpy(aux->client_name, aux1);
		free(aux1);
		aux1 = NULL;
		
//		free(aux->address);
		aux->address = (char*) malloc(strlen(aux2));
		strcpy(aux->address, aux2);
		free(aux2);
		aux2 = NULL;
		
//		free(aux->postal_code);
		aux->postal_code = (char*) malloc(strlen(postal_code)+1);
		strcpy(aux->postal_code, postal_code);
//		free(aux3);
//		aux3 = NULL;
		
		aux->city = (char*) malloc(strlen(city)+1);
		strcpy(aux->city, city);
//		free(aux4);

		aux->country = (char*) malloc(strlen(country)+1);
		strcpy(aux->country, country);
//		free(aux5);
		
		aux->mail = (char*) malloc(strlen(mail)+1);
		strcpy(aux->mail, mail);
//		free(aux6);
		
		aux->birth_date = (char*) malloc(strlen(birth_date)+1);
		strcpy(aux->birth_date, birth_date);
//		free(aux7);
		
/*		free(client_name);
		free(address);
		free(postal_code);
		free(city);
		free(country);
		free(mail);
		free(birth_date);*/
		
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

//	free(aux);
	aux->next = NULL;
	aux = clients;
	fclose(fp);
	
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
void login(USERS users, CLIENTS clients);


//-------------------------------------------------------------------Show Client
void show_account(CLIENTS clients){
	
    int temp_search;
    int flag = 1;
    system("cls");

    CLIENTS aux = clients;

    //Pedir ID
    printf("\n\n\t\t\tInput Account ID > "); 
	scanf("%d",&temp_search);
	system("cls");

    while (flag != 0 && aux->next != NULL){
    	
    	if (temp_search == aux->client_id){
    		
    		flag = 0;
    	
	        printf("\n\n\t\t\t[Client Info]");
	        printf("\n\n\t\t\tID :"); 
			printf("\t%d",aux->client_id);
			
	        printf("\n\t\t\tName :"); 
			printf("\t%s",aux->client_name);
			
	        printf("\n\t\t\tAddress :");      
			printf("\t%s",aux->address);
			
	        printf("\n\t\t\tPostal Code :"); 
			printf("\t%s",aux->postal_code);
			
	        printf("\n\t\t\tCity :"); 
			printf("\t%s",aux->city);
			
	        printf("\n\t\t\tCountry :"); 
			printf("\t%s",aux->country);
			
	        printf("\n\t\t\tMobile Phone :"); 
			printf("\t%d",aux->mobile_phone);
			
	        printf("\n\t\t\tMail :");
			printf("\t%s",aux->mail);
			
	        printf("\n\t\t\tBirth Date :"); 
			printf("\t%s",aux->birth_date);
			
	        printf("\n\t\t\tTax Number :"); 
			printf("\t%d",aux->tax_number);
			
	        printf("\n\t\t\tMonthly Income :"); 
			printf("\t%0.2f",aux->monthly_income);
	
	        printf("\n\t\t\tBalance :"); 
			printf("\t%0.2f",aux->balance);
	        printf("\n");
	        
	        system("pause");
	        system("cls");
    	}
    	
        aux=aux->next;
    }
    
    if(flag == 1){
    	
    	if (temp_search == aux->client_id){
    		
    		flag = 0;
    	
	        printf("\n\n\t\t\t[Client Info]");
	        printf("\n\n\t\t\tID :"); 
			printf("\t%d",aux->client_id);
			
	        printf("\n\t\t\tName :"); 
			printf("\t%s",aux->client_name);
			
	        printf("\n\t\t\tAddress :");      
			printf("\t%s",aux->address);
			
	        printf("\n\t\t\tPostal Code :"); 
			printf("\t%s",aux->postal_code);
			
	        printf("\n\t\t\tCity :"); 
			printf("\t%s",aux->city);
			
	        printf("\n\t\t\tCountry :"); 
			printf("\t%s",aux->country);
			
	        printf("\n\t\t\tMobile Phone :"); 
			printf("\t%d",aux->mobile_phone);
			
	        printf("\n\t\t\tMail :");
			printf("\t%s",aux->mail);
			
	        printf("\n\t\t\tBirth Date :"); 
			printf("\t%s",aux->birth_date);
			
	        printf("\n\t\t\tTax Number :"); 
			printf("\t%d",aux->tax_number);
			
	        printf("\n\t\t\tMonthly Income :"); 
			printf("\t%0.2f",aux->monthly_income);
	
	        printf("\t\t\tBalance :"); 
			printf("\t%0.2f",aux->balance);
	        printf("\n");
	        
	        system("pause");
	        system("cls");
    	}
	}
	if (flag == 1){
    	
    	printf("\n\n\tClient not found.\n");
    	sleep(1);
	}
}

//-----------------------------------------------------------------Creat Account
void create_account(CLIENTS clients){
	
	system("cls");
	int checkexist=0;
	
	int client_id;
	char client_name[50];
	char address[100];
	char postal_code[8];
	char city[50];
	char country[50];
	int mobile_phone;
	char mail[50];
	char birth_date[10];
	int tax_number;
	float monthly_income;
	float balance;
	
	CLIENTS aux = clients;
	
	fflush(stdin);
	printf("\n\t\tInsert Client ID: ");
	scanf("%i",&client_id);
//	sleep(1);
	fflush(stdin);
	printf("\n\t\tInsert Client Name: ");
	scanf("%s",&client_name);
//	sleep(1);
	fflush(stdin);
	printf("\n\t\tInsert Client Address: ");
	scanf("%s",&address);
//	sleep(1);
	fflush(stdin);
	printf("\n\t\tInsert Client Postal Code: ");
	scanf("%s",&postal_code);
//	sleep(1);
	fflush(stdin);
	printf("\n\t\tInsert City: ");
	scanf("%s",&city);
//	sleep(1);
	fflush(stdin);
	printf("\n\t\tInsert Country: ");
	scanf("%s",&country);
//	sleep(1);
	fflush(stdin);
	printf("\n\t\tInsert Mobile Phone: ");
	scanf("%i",&mobile_phone);
//	sleep(1);
	fflush(stdin);
	printf("\n\t\tInsert Mail: ");
	scanf("%s",&mail);
//	sleep(1);
	fflush(stdin);
	printf("\n\t\tInsert Birth date: ");
	scanf("%s",&birth_date);
//	sleep(1);
	fflush(stdin);
	printf("\n\t\tInsert Client Tax Number: ");
	scanf("%i",&tax_number);
//	sleep(1);
	fflush(stdin);
	printf("\n\t\tInsert Monthly Income of the Client: ");
	scanf("%f",&monthly_income);
//	sleep(1);
	fflush(stdin);
	printf("\n\t\tInsert Balance: ");
	scanf("%f",&balance);
	
	char auxclient_name[strlen(client_name)];
	pop_buffer(auxclient_name, strlen(client_name));
	strcpy(auxclient_name, client_name);
	
	char auxaddress[strlen(address)];
	pop_buffer(auxaddress, strlen(address));
	strcpy(auxaddress, address);
	
	char auxpostal_code[strlen(postal_code)];
	pop_buffer(auxpostal_code, strlen(postal_code));
	strcpy(auxpostal_code, postal_code);
	
	char auxcity[strlen(city)];
	pop_buffer(auxcity, strlen(city));
	strcpy(auxcity, city);
	
	char auxcountry[strlen(country)];
	pop_buffer(auxcountry, strlen(country));
	strcpy(auxcountry, country);
	
	char auxmail[strlen(mail)];
	pop_buffer(auxmail, strlen(mail));
	strcpy(auxmail, mail);
	
	char auxbirth_date[strlen(birth_date)];
	pop_buffer(auxbirth_date, strlen(birth_date));
	strcpy(auxbirth_date, birth_date);
	
	while (aux->next != NULL){
		
		aux = aux->next;
	}
	
	aux->next = init_CLIENTS();
	aux = aux->next;
	
	aux->client_id = client_id;
	
	aux->client_name = (char*) malloc(strlen(auxclient_name) + 1);
	strcpy(aux->client_name, auxclient_name);
	
	aux->address = (char*) malloc(strlen(auxaddress) + 1);
	strcpy(aux->address, auxaddress);
	
	aux->postal_code = (char*) malloc(strlen(auxpostal_code) + 1);
	strcpy(aux->postal_code, auxpostal_code);
	
	aux->city = (char*) malloc(strlen(auxcity) + 1);
	strcpy(aux->city, auxcity);
	
	aux->country = (char*) malloc(strlen(auxcountry) + 1);
	strcpy(aux->country, auxcountry);
	
	aux->country = (char*) malloc(strlen(auxcountry) + 1);
	strcpy(aux->country, auxcountry);
	
	aux->mobile_phone = mobile_phone;
	
	aux->mail = (char*) malloc(strlen(auxmail) + 1);
	strcpy(aux->mail, auxmail);
	
	aux->birth_date = (char*) malloc(strlen(auxbirth_date) + 1);
	strcpy(aux->birth_date, auxbirth_date);
	
	aux->monthly_income = monthly_income;
	aux->balance = balance;
	aux->next = NULL;
	
/*	aux->address = address;
	aux->postal_code = postal_code;
	aux->city = city;
	aux->country = country;
	
	aux->mail = mail;
	aux->birth_date = birth_date;
	aux->tax_number = tax_number;*/
	
	aux = clients;
	
	system("pause");
}

//----------------------------------------------------------------------Deposits

void deposits(CLIENTS clients){
    int temp_id =0, m, temp_balance;

    system("cls");

    CLIENTS aux=clients;
//    FILE *fp;
  //  fp = fopen ("clients.txt","r");

    //Pedir ID
    printf("\n\n\t\t\tInput Account ID > "); scanf("%d",&temp_id);
    system("cls");


    while (temp_id != aux->client_id)
    {
        aux=aux->next;
    }

    if (temp_id == aux->client_id)
    {
        printf("\n\n\t\t\t[Client Info]");
        printf("\n\n\t\t\tID :"); printf("\t%d",aux->client_id);
        printf("\n\t\t\tName :"); printf("\t%s",aux->client_name);
        printf("\n\t\t\tAddress :"); printf("\t%s",aux->address);
        printf("\n\t\t\tPostal Code :"); printf("\t%s",aux->postal_code);
        printf("\n\t\t\tCity :"); printf("\t%s",aux->city);
        printf("\n\t\t\tCountry :"); printf("\t%s",aux->country);
        printf("\n\t\t\tMobile Phone :"); printf("\t%d",aux->mobile_phone);
        printf("\n\t\t\tMail :"); printf("\t%s",aux->mail);
        printf("\n\t\t\tBirth Date :"); printf("\t%s",aux->birth_date);
        printf("\n\t\t\tTax Number :"); printf("\t%d",aux->tax_number);
        printf("\n\t\t\tMonthly Income :"); printf("\t%0.2f",aux->monthly_income);
        printf("\t\t\tBalance :"); printf("\t%0.2f",aux->balance);
        printf("\n");
    }

    printf("\n\t\t\tHow much do you want to deposit?"); 
	scanf("%d",&m);
    system("cls");
    temp_balance=aux->balance+m;
    aux->balance=temp_balance;

//    if (temp_id == aux->client_id)
//    {
//    fprintf(fp,"%d",aux->balance);
//    }
}

//----------------------------------------------------------------------withdraw
void withdraws(CLIENTS clients){
	
	system("cls");
	int removemoney,balance;
	int client_id_inserted,equalusers=0;
	
	printf("\nInsert Client ID: ");
	scanf("%i",&client_id_inserted);
	CLIENTS aux = clients;
	
	while(equalusers==0){
		if(aux->client_id==client_id_inserted){
			equalusers=1;
		}
		else{
			aux = aux->next;
		}
		if(aux->next==NULL){
			printf("\n---Client not found , disconnecting---\n");
			equalusers=2;
		}
	}
	
	if(equalusers==2 || equalusers==0){
		
		printf("\n---Client Found---\n\n\n");
		printf("\n\n\t\t\t[Client Info]");
    	printf("\n\n\t\t\tID :"); printf("\t%d",aux->client_id);
    	printf("\n\t\t\tName :"); printf("\t%s",aux->client_name);
    	printf("\n\t\t\tAddress :"); printf("\t%s",aux->address);
    	printf("\n\t\t\tPostal Code :"); printf("\t%s",aux->postal_code);
        printf("\n\t\t\tCity :"); printf("\t%s",aux->city);
        printf("\n\t\t\tCountry :"); printf("\t%s",aux->country);
        printf("\n\t\t\tMobile Phone :"); printf("\t%d",aux->mobile_phone);
        printf("\n\t\t\tMail :"); printf("\t%s",aux->mail);
        printf("\n\t\t\tBirth Date :"); printf("\t%s",aux->birth_date);
        printf("\n\t\t\tTax Number :"); printf("\t%d",aux->tax_number);
        printf("\n\t\t\tMonthly Income :"); printf("\t%d",aux->monthly_income);
        printf("\t\t\tBalance :"); printf("\t%d",aux->balance);
        printf("\n");
	
		while(removemoney < 0){
			printf("\nInsert withdrawn to balance: ");
			scanf("%i",&removemoney);
		}
		
		if((aux->balance-removemoney) < 0){
			
			printf("\nInvalid Amount");
		}
		else{
			aux->balance = aux->balance-removemoney;
			printf("\nWithdrawn Sucessful");
			printf("\nCurrent Balance: %i \n\n", aux->balance);
			system("pause");
			system("cls");
		}
	}
}

//-----------------------------------------------------------------------credits

void simulate_credit(CLIENTS clients){
	system("cls");
	char yn;
	float taeg = -1, tan = -1;
	float credit = -1, prestacao = 0;
	int months, balance = 0;
	int client_id_inserted = 0, equalusers = 0;
	
	CLIENTS aux = clients;
	
	printf("\n\n");
	printf("\tInsert Client ID: ");
	scanf("%i", &client_id_inserted);
	
	while(equalusers == 0){
		
		if(aux->client_id == client_id_inserted){
			
			equalusers = 1;
		}
		else if(aux->next == NULL){
			
			printf("\n\t---Client not found---\n");
			equalusers=2;
		}
		else{
			aux = aux->next;
		}
		
	}
	if(aux->client_id == client_id_inserted){
			
			equalusers = 1;
		}
	else if(aux->next == NULL){
		
		printf("\n\t---Client not found---\n");
		equalusers=2;
	}
	
	if(equalusers==2 || equalusers==0){}
	
	else{
		fflush(stdin);
		printf("\n\n");
		printf("\tClient found, welcome %s",aux->client_name);
		printf("\n\t\tInsert credit amount needed: ");
		scanf("%f",&credit);
		fflush(stdin);
		printf("\n\t\tInsert number of months to pay: ");
		scanf("%i",&months);
		fflush(stdin);
		printf("\n\t\tInsert current TAN (in percentage %): ");
		scanf("%f",&tan);
		fflush(stdin);
		printf("\n\t\tInsert current TAEG (in percentage %): ");
		scanf("%f",&taeg);
        
		while(credit < 0){
			
			fflush(stdin);
        	printf("\n\t\tInsert valid credit amount needed: ");
			scanf("%f",&credit);	
		}
		
        while(months < 0){
        	
        	fflush(stdin);
        	printf("\n\t\tInsert valid number of months to pay: ");
			scanf("%i",&months);	
		}
		
		while(tan < 0){
			
			fflush(stdin);
			printf("\n\t\tInsert valid TAN (in percentage %): ");
			scanf("%f",&tan);
		}
		
		while(taeg < 0){
			
			fflush(stdin);
			printf("\n\t\tInsert valid TAEG (in percentage %): ");
			scanf("%f",&taeg);
		}
		
		prestacao = (credit + (credit * (tan / 100)) + (credit * (taeg / 100))) / months;
		
		printf("\n\n\t\t[Credit Info]");
		printf("\n\t\t\tID: %i", aux->client_id); 
		printf("\n\t\t\tName: %s", aux->client_name);
    	printf("\n\t\t\tQuantity: %0.2f",credit); 
    	printf("\n\t\t\tTAN: %0.2f %%", tan);
		printf("\n\t\t\tTAEG: %0.2f %%",taeg); 
    	printf("\n\t\t\tYou will have to pay %0.2f for %i months.", prestacao, months);
		
		fflush(stdin);
		printf("\n\n\t\tClient Accept Credit? Y/N: ");
		scanf("%c", &yn);
		
		if(yn == 'Y'){
			
			printf("\n\t\tCredit Accepted");
			aux->balance = aux->balance + credit;
			printf("\n\n\t\tCurrent Balance: %0.2f\n", aux->balance);
			system("pause");
			system("cls");
		}
		else{
			
			printf("\n\n\t\tCredit not accepted\n");
			sleep(2);
		}
	}
}

//----------------------------------------------------------------creat new user
void new_user(USERS users){
	
	system("cls");
//    char user[20], userpassword[20];
	char user[10];
	char userpassword[10];
    int usertype;
    
    USERS aux = users;

    system("cls");

    printf("\n\n\t\t[USER REGISTER]\n");

    //Introduzir username
    printf("\n\t\t\tEnter Username > ");
    //fgets(user, 19, stdin);
    scanf("%s",&user);

   //    scanf("%19[^\n]",&user);

    //Introduzir password
    printf("\n\t\t\tEnter Password > ");
    //fgets(userpassword, 19, stdin);
    scanf("%s",&userpassword);

    //Introduzir tipo de conta
    printf("\n\t\t\tEnter User Type: 1 - Employee  2 - Account Manager\n\t\t>");
    //fgets(userpassword, 19, stdin);
    scanf("%d",&usertype);
    
    while (usertype >=3 || usertype<=0){
    	//write some input
    	fputs("\t\t\tInvalid input\n",stdout);

    	//wait one second to change line above
    	sleep(1);

	    //remove line
	    printf("\r");
	    fputs("\033[A\033[2K",stdout);
	    rewind(stdout);
	
	    //write new line
	    scanf("%d",&usertype);
    }
	
	char auxuser[strlen(user)];
	pop_buffer(auxuser, strlen(user));
	strcpy(auxuser, user);
	char auxpass[strlen(userpassword)];
	pop_buffer(auxpass, strlen(userpassword));
	strcpy(auxpass, userpassword);	
	
	while (aux->next != NULL){
		
		aux = aux->next;
	}
	aux->next = init_USERS();
	
	aux = aux->next;
	
//	aux->id = user;
//	aux->pass = userpassword;
	
	aux->id = (char*) malloc(strlen(auxuser)+1);
	strcpy(aux->id, auxuser);
	
	aux->pass = (char*) malloc(strlen(auxpass)+1);
	strcpy(aux->pass, auxpass);
	
	aux->type = usertype;	
	
/*	aux->id = (char*) malloc(strlen(user)+1);
	strcpy(aux->id, user);
	
	aux->pass = (char*) malloc(strlen(userpassword)+1);
	strcpy(aux->pass, userpassword);*/
	
	
	
/*	aux = aux->next;
	aux->id = user;
	aux->pass = userpassword;
	aux->type = usertype;*/
	aux->next = NULL;
	
	aux = users;
//	printf("%s", aux->id);
//	system("pause");
/*	users = aux;
	FILE* fp;
	fp = fopen("users.txt", "a");
	char ch = getc(fp);
	
	if(fp == NULL){
		
		printf("I/O error\n");
		exit(1);
	}
	  		
	fprintf(fp, "%s/", user);
	fprintf(fp, "%s/", userpassword);
	fprintf(fp, "%i/-", usertype);
	printf("\n\tData saved in the file."); 
		
	fclose(fp);*/
//	system("cls");
	system("pause");
//	return aux;
}

//----------------------------------------Menu inicial para permissoes do tipo 1
void start_menu_1(USERS users, CLIENTS clients){
	int flag = 1;
	int choice = -1;
	while (flag != 0){
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		system("cls");
		printf("\n\n");
		printf("\tOLD BANK MANAGEMENT SYSTEM");
		printf("\n\n");
		printf("\tChoose one option:\n\n");
		printf("\t1 - Open Client Page\n\t2 - Create a New Client\n"
				"\t3 - Deposit\n\t4 - Withdraw\n\n\t0 - Logout\n\n\n\tS - Save and Quit\n");
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		scanf(" %d", &choice);
		switch (choice){
			case '1':
				show_account(clients);
				break;
			case '2':
				create_account(clients);
				break;
			case '3':
				deposits(clients);
				break;
			case '4':
				withdraws(clients);
				break;
			case '0':
				login(users, clients);
				break;
			case 's':
				flag = 0;
				break;
			default:
				printf("\tInvalid operation.\nPlease, choose a valid option.\n\n");
		}
	}
}

//----------------------------------------Menu inicial para permissoes do tipo 2
void start_menu_2(USERS users, CLIENTS clients){
	int flag = 1;
	char choice = -1;
	while (flag != 0){
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		system("cls");
		printf("\n\n");
		printf("\tOLD BANK MANAGEMENT SYSTEM");
		printf("\n\n");
		printf("\tChoose one option:\n\n");
		printf("\t1 - Open Client Page\n\t2 - Create a New Client\n"
				"\t3 - Deposit\n\t4 - Withdraw\n\t5 - Simulate and Approve Credit\n"
				"\t6 - Search for a Client\n\n\t0 - Logout\n\n\n\tS - Save and Quit\n");
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		scanf(" %c", &choice);
		switch (choice){ 
			case '1':
				show_account(clients); 
				break;
			case '2':
				create_account(clients); 
				break;
			case '3':
				deposits(clients); 
				break;
			case '4':
				withdraws(clients); 
				break;
			case '5':
				simulate_credit(clients); 
				break;
			case '6':
//				search_clients(); 
				break;
			case '0':
				login(users, clients); 
				break;
			case 's':
				flag = 0;
				break;
			default:
				printf("\tInvalid operation.\nPlease, choose a valid option.\n\n");
		}
	}
}

//----------------------------------------Menu inicial para permissoes do tipo 3
void start_menu_3(USERS users, CLIENTS clients){
	
	USERS aux = users;
	int flag = 1; 
	char choice = -1; 
	while (flag != 0){
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		system("cls");
		printf("\n\n");
		printf("\tOLD BANK MANAGEMENT SYSTEM");
		printf("\n\n");
		printf("\tChoose one option:\n\n");
		printf("\t1 - Open Client Page\n\t2 - Create a New Client\n"
				"\t3 - Deposit\n\t4 - Withdraw\n\t5 - Simulate and Approve Credit\n"
				"\t6 - Search for a Client\n\t7 - Create a new User\n\t8 - Delete User\n"
				"\t9 - Backup All Data\n\n\t0 - Logout\n\n\n\tS - Save and Quit\n");
//		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		scanf(" %c", &choice);
		switch (choice){
			case '1':
				show_account(clients); 
				break;
			case '2':
				create_account(clients); 
				break;
			case '3':
				deposits(clients); 
				break;
			case '4':
				withdraws(clients); 
				break;
			case '5':
				simulate_credit(clients); 
				break;
			case '6':
//				search_clients(); 
				break;
			case '7':
				new_user(users);
				break;
			case '8':
//				delete_user(); 
				break;
			case '9':
//				backup(); 
				break;
			case '0':
				login(users, clients);
				break;
			case 's':
				flag = 0;
				break;
			default:
				printf("\tInvalid operation.\nPlease, choose a valid option.\n\n");
		}
	}
}

//-------------------------------------------------------------------------SAVER

void save_users(USERS users){
	
	USERS aux = users;
	char buffer[10000];
	pop_buffer(buffer, 10000);
	
	int i = 0;
	int j = 0;
	char* str;
	
	while(aux->next != NULL){
		
		j = 0;
		while(j < strlen(aux->id)){
			
			buffer[i] = aux->id[j];
			j++;
			i++;
		}
		
		buffer[i] = '/';
		i++;
		
		j = 0;
		while(j < strlen(aux->pass)){
			
			buffer[i] = aux->pass[j];
			i++;
			j++;
		}
		
		buffer[i] = '/';
		i++;
		buffer[i] = aux->type + '0';
		i++;
		buffer[i] = '/';
		i++;
		buffer[i] = '-';
		i++;
				
		aux = aux->next;
	}
	
	j = 0;
	while(j < strlen(aux->id)){
		
		buffer[i] = aux->id[j];
		j++;
		i++;
	}
	buffer[i] = '/';
	i++;
	
	j = 0;
	while(j < strlen(aux->pass)){
		
		buffer[i] = aux->pass[j];
		i++;
		j++;
	}
	buffer[i] = '/';
	i++;
	buffer[i] = aux->type + '0';
	i++;
	buffer[i] = '/';
	i++;
	buffer[i] = '-';
	i++;
	
	int index = 0;
	
	while (buffer[index] != '!'){
		
		index++;
	}
	
	int k = 0;
	char s1[index];
	
	while(k < index){
		
		s1[k] = buffer[k];
		k++;
	}
	
	FILE *fp;
	
	fp = fopen("users.txt", "w");
	
	if (fp == NULL) {
        printf("Error!");
        exit(1);
    }
    
    fprintf(fp, "%s", s1);
    
    fclose(fp);
    
}

void save_clients(CLIENTS clients){
	
	CLIENTS aux = clients;
	char buffer[10000];
	pop_buffer(buffer, 10000);
	
	int i = 0;
	int j = 0;
	
	while(aux->next != NULL){
		
		j = 0;
/*		while(j < strlen(aux->client_id)){
			
			buffer[i] = aux->client_id + '0';
			j++;
			i++;
		}*/
		
		buffer[i] = aux->client_id + '0';
		i++;
		
		buffer[i] = '/';
		i++;
		
		j = 0;
		while(j < strlen(aux->client_name)){
			
			buffer[i] = aux->client_name[j];
			i++;
			j++;
		}
		
		buffer[i] = '/';
		i++;
		
		j = 0;
		while(j < strlen(aux->address)){
			
			buffer[i] = aux->address[j];
			i++;
			j++;
		}
		
		buffer[i] = '/';
		i++;
		
		j = 0;
		while(j < strlen(aux->postal_code)){
			
			buffer[i] = aux->postal_code[j];
			i++;
			j++;
		}
		
		buffer[i] = '/';
		i++;
		
		j = 0;
		while(j < strlen(aux->city)){
			
			buffer[i] = aux->city[j];
			i++;
			j++;
		}
		
		buffer[i] = '/';
		i++;
		
		j = 0;
		while(j < strlen(aux->country)){
			
			buffer[i] = aux->country[j];
			i++;
			j++;
		}
		
		buffer[i] = '/';
		i++;
		
		j = 0;
/*		while(j < strlen(aux->mobile_phone)){
			
			buffer[i] = aux->mobile_phone + '0';
			i++;
			j++;
		}*/
		
		buffer[i] = aux->mobile_phone + '0';
		i++;
		
		buffer[i] = '/';
		i++;
		
		j = 0;
		while(j < strlen(aux->mail)){
			
			buffer[i] = aux->mail[j];
			i++;
			j++;
		}
		
		buffer[i] = '/';
		i++;
		
		j = 0;
		while(j < strlen(aux->birth_date)){
			
			buffer[i] = aux->birth_date[j];
			i++;
			j++;
		}
		
		buffer[i] = '/';
		i++;
		
		j = 0;
/*		while(j < strlen(aux->tax_number)){
			
//			buffer[i] = aux->tax_number + '0';
			sprintf(buffer[i], "%f", aux->tax_number);
			i++;
			j++;
		}*/
		
		buffer[i] = aux->tax_number + '0';
		
		buffer[i] = '/';
		i++;
		
		j = 0;
/*		while(j < strlen(aux->monthly_income)){
			
//			buffer[i] = aux->monthly_income + '0';
			sprintf(buffer[i], "%f", aux->monthly_income);
			i++;
			j++;
		}*/
		
		sprintf(buffer[i], "%f", aux->monthly_income);
		i++;
		
		buffer[i] = '/';
		i++;
		
		j = 0;
/*		while(j < strlen(aux->balance)){
			
//			buffer[i] = aux->balance + '0';
			sprintf(buffer[i], "%f", aux->balance);
			i++;
			j++;
		}*/
		
		sprintf(buffer[i], "%f", aux->balance);
		
		buffer[i] = '/';
		i++;
		buffer[i] = '-';
		i++;
				
		aux = aux->next;
	}
	
	j = 0;
/*		while(j < strlen(aux->client_id)){
		
		buffer[i] = aux->client_id + '0';
		j++;
		i++;
	}*/
	
	buffer[i] = aux->client_id + '0';
	i++;
	
	buffer[i] = '/';
	i++;
	
	j = 0;
	while(j < strlen(aux->client_name)){
		
		buffer[i] = aux->client_name[j];
		i++;
		j++;
	}
	
	buffer[i] = '/';
	i++;
	
	j = 0;
	while(j < strlen(aux->address)){
		
		buffer[i] = aux->address[j];
		i++;
		j++;
	}
	
	buffer[i] = '/';
	i++;
	
	j = 0;
	while(j < strlen(aux->postal_code)){
		
		buffer[i] = aux->postal_code[j];
		i++;
		j++;
	}
	
	buffer[i] = '/';
	i++;
	
	j = 0;
	while(j < strlen(aux->city)){
		
		buffer[i] = aux->city[j];
		i++;
		j++;
	}
	
	buffer[i] = '/';
	i++;
	
	j = 0;
	while(j < strlen(aux->country)){
		
		buffer[i] = aux->country[j];
		i++;
		j++;
	}
	
	buffer[i] = '/';
	i++;
	
	j = 0;
/*		while(j < strlen(aux->mobile_phone)){
		
		buffer[i] = aux->mobile_phone + '0';
		i++;
		j++;
	}*/
	
	buffer[i] = aux->mobile_phone + '0';
	i++;
	
	buffer[i] = '/';
	i++;
	
	j = 0;
	while(j < strlen(aux->mail)){
		
		buffer[i] = aux->mail[j];
		i++;
		j++;
	}
	
	buffer[i] = '/';
	i++;
	
	j = 0;
	while(j < strlen(aux->birth_date)){
		
		buffer[i] = aux->birth_date[j];
		i++;
		j++;
	}
	
	buffer[i] = '/';
	i++;
	
	j = 0;
/*		while(j < strlen(aux->tax_number)){
		
//			buffer[i] = aux->tax_number + '0';
		sprintf(buffer[i], "%f", aux->tax_number);
		i++;
		j++;
	}*/
	
	buffer[i] = aux->tax_number + '0';
	
	buffer[i] = '/';
	i++;
	
	j = 0;
/*		while(j < strlen(aux->monthly_income)){
		
//			buffer[i] = aux->monthly_income + '0';
		sprintf(buffer[i], "%f", aux->monthly_income);
		i++;
		j++;
	}*/
	
	sprintf(buffer[i], "%f", aux->monthly_income);
	i++;
	
	buffer[i] = '/';
	i++;
	
	j = 0;
/*		while(j < strlen(aux->balance)){
		
//			buffer[i] = aux->balance + '0';
		sprintf(buffer[i], "%f", aux->balance);
		i++;
		j++;
	}*/
	
	sprintf(buffer[i], "%f", aux->balance);
	
	buffer[i] = '/';
	i++;
	buffer[i] = '-';
	i++;
	
	int index = 0;
	
	while (buffer[index] != '!'){
		
		index++;
	}
	
	int k = 0;
	char s1[index];
	
	while(k < index){
		
		s1[k] = buffer[k];
		k++;
	}
	
	FILE *fp;
	
	fp = fopen("clients.txt", "w");
	
	if (fp == NULL) {
        printf("Error!");
        exit(1);
    }
    
    fprintf(fp, "%s", s1);
    
    fclose(fp);
    
}

//-------------------------------------------------------------------------LOGIN

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

//-------Compara dados introduzidos com os dados presentes na estrutura de dados
int check(char* id, char* pass, USERS users){
	
	int i = 0;
	int flag = 0;
	
	USERS aux = users;
		
	while (aux->next != NULL){
		
		i = compare(id, pass, aux->id, aux->pass);
		
		if (i == 1){
		
			flag = aux->type;
		}
		aux = aux->next;
	}
	i = compare(id, pass, aux->id, aux->pass);
		
		if (i == 1){
							
			flag = aux->type;
		}
	return flag;
}

//---------------------------Obtem username e password do utilizador do programa
int get_credentials(char *id, char *password){
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
	do{
	c = getch();
		if(isprint(c) ){
			password[ pos++ ] = c;
			printf("%c", '*');
		}
		else if( c == 9 && pos ){
			
			password[pos--] = '\0';
			printf("%s", "\b \b");
		}
	} while( c != 13 );	
}

//-------------------------------------------------------------------------Login
void login(USERS users, CLIENTS clients){
	
	USERS aux = users;
	
	int type = 0;
	char id[ID_SIZE];
	char password[PASS_SIZE];
	
	while (type == 0){
	
		get_credentials(id, password);

		type = check(id, password, users);
	
		if(type > 0){
			printf("\n\n");
			printf("\tCorrect Username And Password\n");
			printf("\n\n\tWelcome to the System\n\n");
			sleep(2);
			
			if (type == 1){
				start_menu_1(users, clients);
				type = -1;
			}
			else if (type == 2){	
				start_menu_2(users, clients);
				type = -1;
			}
			else if (type == 3){	
				start_menu_3(users, clients);
				type = -1;
			}
		}
		else if (type == 0){
			printf("\n\n");
			printf("\tInvalid Username And Password. Try Again\n\n");
			sleep(2);
		}
		system("cls");
	}
}

//--------------------------------------------------------------------------MAIN
int main(){
	
	USERS us = init_USERS();	
	us = parser_users(us);
	USERS aux1 = us;
	
	CLIENTS cl = init_CLIENTS();
	cl = parser_clients(cl);
	CLIENTS aux2 = cl;
	
	login(us, cl);
	
	save_users(us);
	
	save_clients(cl);
	
	return 1;
}

