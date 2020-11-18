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
		int social_security_number[1];
		int client_id;
		char client_name[70];
		char address[40];
		char postal_code[10];
		char city[22];
		char district[8];
		char country[57];
		int mobile_phone[1];
		char mail[50];
		char birth_date[11];
		int tax_number[1];
		char professional_situation[3];
		float monthly_income[5];
};


void open_account() { //listar conta
	

}

void create_account() { //criar conta
struct database_singular client;
system("cls");

FILE *clientfileopen;

clientfileopen = fopen("Clientes.txt", "a+");


printf("\nIntroduza o numero de Seguran�a Social : ");
scanf("%i%*c", &client.social_security_number);
fprintf(clientfileopen,"%i\n|",&client.social_security_number);

printf("\nIntroduza o nome do cliente : ");
scanf("%[^\n]s%*c", &client.client_name);
fprintf(clientfileopen,"%s|",&client.client_name);


printf("\nIntroduza o Sexo");
printf("\nM - Masculino , F - Feminino , O - Outro\n");

char gendercheck;
while (scanf("%.1s%*c", &gendercheck) < 0)
	{
		printf("Error");
	}


switch(gendercheck){//Verificar se s�o somente introduzidos valores v�lidos
	case 'm': client.gender = 'M';break;
	case 'f': client.gender = 'F';break;
	case 'M': client.gender = 'M';break;
	case 'F': client.gender = 'F';break;
	default: client.gender = 'O';break;
}

fflush(stdin);
fprintf(clientfileopen,"%s|",&client.gender);

printf("\nIntroduza a Morada: ");
scanf("%[^\n]s%*c",&client.address);
fprintf(clientfileopen,"%s|",&client.address);

printf("\nIntroduza o c�digo postal (denote que tem que separar o c�digo postal com h�fen): ");
scanf("%s",&client.postal_code);
fprintf(clientfileopen,"%s|",&client.postal_code);

printf("\nIntroduz a cidade: ");
scanf("%s",&client.city);
fprintf(clientfileopen,"%s|",&client.city);
fflush(stdin);

printf("\nIntroduz o distrito: ");
scanf("%s",&client.district);
fprintf(clientfileopen,"%s|",&client.district);

printf("\nIntroduz o pa�s: ");
scanf("%s",&client.country);
fprintf(clientfileopen,"%s|",&client.country);

printf("\nIntroduz o telefone (Caso n�o tenha insira 0 e clique enter): ");
scanf("%i",&client.mobile_phone);
fprintf(clientfileopen,"%i|",&client.mobile_phone);

printf("\nIntroduz o email (Caso n�o tenha insira X e clique enter): ");
scanf("%s",&client.mail);

if(client.mail == "X"){
	strcpy(client.mail ,"Sem Email");
}
fprintf(clientfileopen,"%s|",&client.mail);

printf("\nIntroduz data de nascimento : ");
scanf("%s",&client.birth_date);
fprintf(clientfileopen,"%s|",&client.birth_date);

fflush(stdin);

printf("\nIntroduz naturalidade");
scanf("%s",&client.birth_country);
	
printf("\nInserir pa�s de nascen�a\n");
scanf("%s",&client.birth_city);
	

fprintf(clientfileopen,"%s|%s|",&client.birth_country,&client.birth_city);

printf("\nInserir estado civil\n");
printf("S - Solteiro ; C - Casado ; D - Divorciado ; O - Outro\n");
scanf("%s",&client.marital_status);
fprintf(clientfileopen,"%s|",&client.marital_status);

printf("\nInserir nome da esposa (Opcional , caso deseja saltar insira X e prossiga) : ");
scanf("%[^\n]s%*c",&client.spouse_name);
fprintf(clientfileopen,"%s|",&client.spouse_name);

printf("\nInserir tipo de casamento:");
printf("\n1 - Comunh�o de adquiridos\n2 - Comunh�o geral\n3 - Separa��o de bens\n0 - N�o � casado\n");
scanf("%i",&client.marriage_type);
fprintf(clientfileopen,"%i|",&client.marriage_type);

printf("\nInserir numero de pessoas no agregado familiar:\t");
scanf("%i",&client.household);
fprintf(clientfileopen,"%i|",&client.household);
fflush(stdin);

printf("\nInserir NIF:\n");
scanf("%i",&client.tax_number);
fprintf(clientfileopen,"%i|",&client.tax_number);

fflush(stdin);
printf("Inserir situa��o profissional\n");
printf("D- Desempregado ; C - Conta pr�pria ; O - Conta de Outrem \n");
scanf("%c",&client.professional_situation);
fprintf(clientfileopen,"%c|",&client.professional_situation);

fflush(stdin);
printf("Insira emprego do cliente (caso n�o tenha escreva X e prossiga) :\t");
scanf("%[^\n]s%*c",&client.job);
fprintf(clientfileopen,"%s|",&client.job);

fflush(stdin);
printf("Insira empresa do emprego do cliente  (caso n�o tenha escreva X e prossiga) :\t");
scanf("%[^\n]s%*c",&client.job_company);
fprintf(clientfileopen,"%s|",&client.job_company);

fflush(stdin);
printf("Insira morada da empresa do emprego do cliente  (caso n�o tenha escreva X e prossiga) :\t");
scanf("%[^\n]s%*c",&client.job_company_address);
fprintf(clientfileopen,"%s|",&client.job_company_address);

fflush(stdin);
printf("Insira o tipo de contrata��o\n");
printf("A- Efetivo ; B - Prazo \n");
scanf("%c" , &client.job_hiring_type);
fprintf(clientfileopen,"%c|",&client.job_hiring_type);

printf("Inserir mensalidade mensal\n");
scanf("%f", client.monthly_income);
fprintf(clientfileopen,"%f|",client.monthly_income);

fflush(stdin);
printf("Inserir situa��o profissional\n");
printf("A- Casa arrendada ; B - Casa propria ; C - Vive com familiares\n");
scanf("%c",&client.home_status);
fprintf(clientfileopen,"%s|",&client.home_status);


fclose(clientfileopen);

}

int main(){
	setlocale(LC_ALL,"Portuguese");
	create_account();
	return 0;
}
