#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdbool.h>
#include <wchar.h>
#include <locale.h>

#define _GNU_SOURCE
#define MAX 100
#define BUFFER 1000

struct singular_client{	
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
	double monthly_income;
	double balance;
};

struct worker{
	char* username;
	char* password;
};

struct account_manager{
	char* username;
	char* password;
};

struct general_manager{
	char* username;
	char* password;
};

void pop_buffer(char buffer[], int size){
	int i = 0;
	while(i < size){
		buffer[i] = '!';
		i++;
	}
}

/*void initialize_SC(struct singular_client client_list[]){
	int i = 0;
	while(i < MAX){
		client_list[i].client_id = " ";
		client_list[i].client_name = " ";
		client_list[i].adress = " ";
		client_list[i].postal_code = " ";
		client_list[i].city = " ";
		client_list[i].country = " ";
		client_list[i].mobile_phone = " ";
		client_list[i].mail = " ";
		client_list[i].birth_date = " ";
		client_list[i].ss_number = " ";
		client_list[i].tax_numberr = " ";
		client_list[i].pro_situation = " ";
		client_list[i].mothly_income = " ";
		client_list[i].balance = " ";
		i++;
	}
}*/

/*void initialize_W(struct worker workers[]){
	int i = 0;
	while(i < MAX){
		workers[i].username = " ";
		workers[i].password = " ";
		workers[i].type = " ";
		i++;
	}
}*/

struct account_manager* initialize_AM(){
	int i = 0;
	struct account_manager am[MAX];
	while(i < MAX){
		am[i].username = " ";
		am[i].password = " ";
		i++;
	}
	return am;
}

struct general_manager initialize_GM(){
	struct general_manager gm;
	gm.username = " ";
	gm.password = " ";
	return gm;
}

/*int parser_clients(struct singular_client client_list[]){
	initialize_SC(client_list);
  	char str[BUFFER];
  	pop_buffer(str, BUFFER);
  	int fp = open("clients.txt", O_RDWR);
  	read(fp, str, MAX);
  	close(fp);
  	//write(1, str, MAX);
	int i = 0;
	int j = 0;
	int k = 0;
  	while(str[i] != '/n'){
  		while(str[j] != '/'){
  			while(k < j){
  				client_id[k] = str[k];
  				k++;
			}
			
  			j++;
		}
		
		i++;
	}
  	return 1;
}*/

/*int parser_workers(struct worker workers[]){
	initialize_SC(workers);
  	char str[BUFFER];
  	pop_buffer(str, BUFFER);
  	int fp = open("workers.txt", O_RDWR);
  	read(fp, str, MAX);
  	close(fp);
  	//write(1, str, MAX);
  	return 1;
}*/

struct account_manager* parser_acc_managers(struct account_manager* acc_managers){
	acc_managers = initialize_AM();
	
/*  char str[BUFFER];
  	pop_buffer(str, BUFFER);
  	int fp = open("account_managers.txt", O_RDWR);
  	read(fp, str, MAX);
  	close(fp);
  	printf("%s", str);
	int i = 0;
	int j = 0;
	int k = 0;
	int index = 0;
	while (str[j] != '!'){
		while(str[j] != '/'){
			j++;
		}
		char acc_manager_username[j-i];
		k = 0;
		while(i < j){
			acc_manager_username[k] = str[i];
			i++;
			k++;
		}
		j++;
		i++;
		while(str[j] != '/'){
			j++;
		}
		k = 0;
		char acc_manager_password[j-i];
		while(i < j){
			acc_manager_password[k] = str[i];
			i++;
			k++;
		}
		j++;
		i++;
		j++;
		i++;
		
		acc_managers[index].username = acc_manager_username;
		acc_managers[index].password = acc_manager_password;
		index++;
	}
	
	i = 0;
/*	while (str[i] != '!'){
		printf("user - %s pass - %s", acc_managers[i].username, acc_managers[i].password);
		i++;
	}*/
	return acc_managers;
}

struct general_manager parser_gen_manager(struct general_manager gen_manager){
	gen_manager = initialize_GM();
	char str[BUFFER];
	pop_buffer(str, BUFFER);
	int fp = open("general_manager.txt", O_RDWR);
	read(fp, str, MAX);
	close(fp);
	
	int i = 0;
	int j = 0;
	int k = 0;
	while(str[j] != '/'){
		j++;
	}
	char gen_manager_username[j-i];
	while(i < j){
		gen_manager_username[i] = str[i];
		i++;
	}
	j++;
	i++;
	while(str[j] != '/'){
		j++;
	}
	k = 0;
	char gen_manager_password[j-i];
	while(i < j){
		gen_manager_password[k] = str[i];
		i++;
		k++;
	}
	j++;
	i++;
	gen_manager.username = gen_manager_username;
	gen_manager.password = gen_manager_password;
	
	return gen_manager;
}

/*Menu inicial para permissoes do tipo 1*/
/*void start_menu_1(){
	int flag = 1;
	int choice = -1;
	while (flag != 0){
		system("clear");
		printf("\n\n");
		printf("\tOLD BANK MANAGEMENT SYSTEM");
		printf("\n\n");
		printf("\tChoose one option:\n\n");
		printf("\t1 - Open Client Page\n\t2 - Create a New Client\n"
				"\t3 - Deposit\n\t4 - Withdraw\n\n\t0 - Logout\n");
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
}*/

/*Menu inicial para permissoes do tipo 2*/
/*void start_menu_2(){
	int flag = 1;
	int choice = -1;
	while (flag != 0){
		system("clear");
		printf("\n\n");
		printf("\tOLD BANK MANAGEMENT SYSTEM");
		printf("\n\n");
		printf("\tChoose one option:\n\n");
		printf("\t1 - Open Client Page\n\t2 - Create a New Client\n"
				"\t3 - Deposit\n\t4 - Withdraw\n\t5 - Simulate and Approve Credit\n"
				"\t6 - Search for a Client\n\n\t0 - Logout\n");
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
}*/

/*Menu inicial para permissoes do tipo 3*/
/*void start_menu_3(){
	int flag = 1; 
	int choice = -1; 
	while (flag != 0){
		system("cls");
		printf("\n\n");
		printf("\tOLD BANK MANAGEMENT SYSTEM");
		printf("\n\n");
		printf("\tChoose one option:\n\n");
		printf("\t1 - Open Client Page\n\t2 - Create a New Client\n"
				"\t3 - Deposit\n\t4 - Withdraw\n\t5 - Simulate and Approve Credit\n"
				"\t6 - Search for a Client\n\t7 - Creat a new User\n\t8 - Delete User\n"
				"\t9 - Backup All Data\n\n\t0 - Logout\n");
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
}*/

//int check_credentials(char id[15], char pass[15], char *userID, char *userPassword/*struct worker workers[], , struct general_manager gen_manager*/){
/*	int flag = 0;
	int i = 0;
//	while(flag == 0){
		/*while(workers[i].username != ' ' || flag == 0){
			if(strcmp(id, workers[i].username)){
				if(strcmp(pass, workers[i].password)){
					flag = 1;
				}
			}
			i++;
		}
		i = 0;*/
/*		while(acc_managers[i].username != ' ' || flag == 0){
			if(strcmp(id, acc_managers[i].username)){
				if(strcmp(pass, acc_managers[i].password)){
					flag = 2;
				}
			}
			i++;
		}
		if(strcmp(id, userID) == 0){
			if(strcmp(pass, userPassword) == 0){
				flag = 3;
			}
		}
//	}
	return flag;
}*/

//criar conta
void create_account(){
	struct singular_client client;
	system("cls");
	FILE *fp;
	fp = fopen("clientes.txt", "a+");
	
	rintf("\n\n");
	printf("\tInsert Account ID: ");
	scanf("%i", &client.client_id);
	
	fflush(stdin);
	printf("\n\tInsert Client Name: ");
	scanf("%[^\n]s%*c", &client.client_name);
	
	fflush(stdin);
	printf("\ntInsert Date of Birth(dd-mm-yyyy): ");
	scanf("%s",&client.birth_date);
	
	fflush(stdin);
	printf("\n\tInsert Client Adress: ");
	scanf("%[^\n]s%*c",&client.address);
	
	fflush(stdin);
	printf("\n\tInsert Postal Code(####-###): ");
	scanf("%s",&client.postal_code);
	
	fflush(stdin);
	printf("\n\tInsert City: ");
	scanf("%s",&client.city);
	
	fflush(stdin);
	printf("\n\tInsert Country: ");
	scanf("%s",&client.country);
	
	fflush(stdin);
	printf("\n\tInsert Mobile Phone Number(in case you don't have, insert 0): ");
	scanf("%i",&client.mobile_phone);
	
	fflush(stdin);
	printf("\n\tInsert e-mail(in case you don't have, insert +): ");
	scanf("%s",&client.mail);
	if(client.mail[0] == '+'){
		scanf("no e-mail", &client.mail);
	}
	
	fflush(stdin);
	while(client.tax_number<100000000 || client.tax_number>999999999){
		printf("\n\tInsert VAT Identification Number: ");
		scanf("%i",&client.tax_number);
	}
	
	fflush(stdin);
	printf("\n\tInsert Monthly Income: ");
	scanf("%lf", &client.monthly_income);	
	
	fflush(stdin);
	printf("\n\tInsert Balance: ");
	scanf("%lf", &client.balance);	
	
	fprintf(fp,"%i/%s/%s/%s/%s/%s/%i/%s/%s/%i/%lf/%lf/", client.client_id, 
		client.client_name, client.address, client.postal_code, client.city, 
		client.country, client.mobile_phone, client.mail, client.birth_date, 
		client.tax_number, client.monthly_income, client.balance);
	
	fclose(clientfileopen);
}

/*Funcao para executar Login*/
/*int login(char *id, char *password){
	char c;
	int pos = 0;
	int flag = 0;

	printf("\n\n");
	printf("\tOLD BANK MANAGEMENT SYSTEM");
	printf("\n\n");
	printf("\tUSER LOGIN");
	printf("\n\n");
	printf("\tEnter User Username : ");
	gets(id);
	printf("\n");
	printf("\tEnter Your Password : ");
	gets(password);		
}*/

int main (){
//	struct singular_client client_list[MAX];
//	struct worker workers[MAX];
	struct account_manager* acc_managers;
	struct general_manager gen_manager;
//	parser_clients(client_list);
//	parser_workers(workers);
	acc_managers = parser_acc_managers(acc_managers);
	gen_manager = parser_gen_manager(gen_manager);
	int flag = 0;
	char id[15];
	char password[15];
	int userType = 0;
/*	while (flag == 0){
		login(&id, &password);
		userType = check_credentials(id, password, acc_managers.username, acc_managers.password, gen_manager.username, gen_manager.password);
		if(flag != 0){
			printf("\n\n");
			printf("\tCorrect Username And Password\n");
			printf("\n\n\tWelcome to the System\n\n");
		}
		else{
			printf("\n\n");
			printf("\tInvalid Username And Password. Try Again\n\n");
		}
		if (userType == 1){
			start_menu_1();
		}
		else if (userType == 2){	
			start_menu_2();
		}
		else if (userType == 3){	
			start_menu_3();
		}
	}*/
}
