USERS parser_users(USERS users){
	
	FILE* fp;
	char str [BUFFER];
	pop_buffer(str, BUFFER);
	fp = fopen("users.txt", "r");
	if(fp == NULL){
		
		printf("I/O error\n");
		exit(1);
	}
	fgets(str, MAX, fp);
	fclose(fp);
	
	USERS aux = users;
	
	int i = 0;
	int j = 0;
	int k = 0;
	
	while (j < strlen(str) - 1){

		while (str(j) != '/'){
			
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
		while(str(j) != '/'){
			
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
			
			user_type = str[i];
			i++;
		}
		j += 2;
		i += 2;
		
		aux->id = user_id;
		aux->pass = user_pass;
		aux->type = user_type;
		aux->next = init_users ();
		aux = aux->next;
	}
}
