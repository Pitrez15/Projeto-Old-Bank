#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include <wchar.h>
#include <locale.h>

//fflush(stdin);
//aonde tem array, nao precis de &!!!

struct database_singular
{
		int social_security_number;
		int client_id;
		char client_name[70];
		char address[40];
		char postal_code[10];
		char city[22];
		char district[17];
		char country[57];
		int mobile_phone;
		char mail[50];
		char birth_date[11];
		int tax_number;
		char professional_situation;
		double monthly_income;
		char home_status;	
};


void open_account() { //listar conta
	

}

void create_account() { //criar conta
	struct database_singular client;
	system("cls");
	
	FILE *clientfileopen;
	
	clientfileopen = fopen("Clientes.txt", "a+");
	
	client.tax_number = 0;
	
	printf("\nIntroduza o numero de Segurança Social: ");
	scanf("%i", &client.social_security_number);
	fprintf(clientfileopen,"%i|",client.social_security_number);
	
	fflush(stdin);
	printf("\nIntroduza o nome do cliente: ");
	scanf("%[^\n]s%*c", &client.client_name);
	fprintf(clientfileopen,"%s|",&client.client_name);
	fflush(stdin);
	printf("\nIntroduza a Morada: ");
	scanf("%[^\n]s%*c",&client.address);
	fprintf(clientfileopen,"%s|",&client.address);
	
	printf("\nIntroduza o código postal (denote que tem que separar o código postal com hífen): ");
	scanf("%s",&client.postal_code);
	fprintf(clientfileopen,"%s|",&client.postal_code);
	
	printf("\nIntroduz a cidade: ");
	scanf("%s",&client.city);
	fprintf(clientfileopen,"%s|",&client.city);
	fflush(stdin);
	
	printf("\nIntroduz o distrito: ");
	scanf("%s",&client.district);
	fprintf(clientfileopen,"%s|",&client.district);
	
	printf("\nIntroduz o país: ");
	scanf("%s",&client.country);
	fprintf(clientfileopen,"%s|",&client.country);
	
	printf("\nIntroduz o telefone (Caso não tenha insira 0 e clique enter): ");
	scanf("%i",&client.mobile_phone);
	fprintf(clientfileopen,"%i|",client.mobile_phone);
	
	printf("\nIntroduz o email (Caso não tenha insira X e clique enter): ");
	scanf("%s",&client.mail);
	
	if(client.mail[0] == 'X'){
		scanf("Sem Email",&client.mail);
	}
	fprintf(clientfileopen,"%s|",&client.mail);
	
	printf("\nIntroduz data de nascimento: ");
	scanf("%s",&client.birth_date);
	fprintf(clientfileopen,"%s|",&client.birth_date);
	
	fflush(stdin);
	
	while(client.tax_number<100000000 || client.tax_number>999999999){
		printf("\nInserir NIF: ");
		scanf("%i",&client.tax_number);
	}
	fprintf(clientfileopen,"%i|",client.tax_number);
	
	printf("\nInserir mensalidade: ");
	scanf("%lf", &client.monthly_income);
	printf("%lf", client.monthly_income);
	
	fprintf(clientfileopen,"%lf|",client.monthly_income);
	
	fflush(stdin);
	printf("\nInserir situação profissional\n");
	printf("D- Desempregado ; C - Conta própria ; O - Conta de Outrem \n");
	scanf("%c",&client.professional_situation);
	fprintf(clientfileopen,"%s|",&client.professional_situation);
	
	fflush(stdin);
	printf("\nInserir situação da habitação\n");
	printf("A- Casa arrendada ; B - Casa propria ; C - Vive com familiares\n");
	scanf("%c",&client.home_status);
	fprintf(clientfileopen,"%s|\n",&client.home_status);
	
	
	fclose(clientfileopen);

}

int main(){
	setlocale(LC_ALL,"Portuguese");
	create_account();
	return 0;
}
