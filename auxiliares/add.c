void add_user(USERS users, char* id, char* pass, int type){
	
	USERS aux = users;
	if(aux == NULL){
		
		aux = init_USERS();
		aux->id = id;
		aux->pass = pass;
		aux-type = type;
		aux->next = NULL;
		return users;
	}
	while (aux->next != NULL){
		
		aux = aux->next;
	}
	aux->next = init_USERS();
	aux = aux->next;
	aux->id = id;
	aux->pass = pass;
	aux-type = type;
	aux->next = NULL;
	return users;
}

void add_client(CLIENTS clients, int client_id, char* client_name, char* address, 
				char* postal_code, char* city, char* country, int mobile_number, 
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
		aux->mobile_number = mobile_number;
		aux->mail = mail;
		aux->birth_date = birth_date;
		aux->tax_number = tax_number;
		aux->monthly_income = monthly_income;
		aux->balance = balance;
		aux->next = NULL;
		return clients;
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
	aux->mobile_number = mobile_number;
	aux->mail = mail;
	aux->birth_date = birth_date;
	aux->tax_number = tax_number;
	aux->monthly_income = monthly_income;
	aux->balance = balance;
	aux->next = NULL;
	return clients;
}
