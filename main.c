#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/*
			#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif
*/

	char nomefantasia[40],razaosocial[40],email[40],nomedoresponsavel[40];
	char inscricaoestadual[18], cnpj[19],telefone[13],telefonedoresponsavel[13];
	char rua[30],bairro[30],cidade[30],UF[5],numero[6];
	
	int margemlucro,numero_de_hospedes,numero_de_produtos,numero_de_fornecedores,numero_de_acomodacoes,numero_de_tipo_acomodacoes;
	int numero_reservas,historico_de_compras,num_operadores,nivel_permissao;
	float caixa;
	int jafez=0;
	int dia,mes,ano,horas,minutos;
	
	
	
	struct HOSPEDE{
        int codigohospede;
        char nome[45],email[45],sexo[15],estadocivil[20];
        char rua[25],bairro[30],cidade[30],UF[6],numero[9];
        char cpf[13],telefone[13],datanascimento[13];
	};
        
    struct ACOMODACOES{
        int codigoacomodacoes,categoria;
        char descricao_acomodacao[250],facilidades[250];
	};
    
    struct CATEGORIA_ACOMODACOES{
            int codigo_cat_acomodacoes,qtd_pessoas;
            float valordiaria;
            char descricao[250];
	};
	
	struct PRODUTOSDISPONIVEISPARACONSUMO{
		int codigo_produto,estoque,estoque_minimo;
		float preco_custo,preco_venda;
		char descricao_produto[101];
	};
	
	struct FORNECEDORES{
        int codigo_fornecedor;
        char nomefantasia[40],razaosocial[40],email[40];
        char inscricaoestadual[16],cnpj[16],telefone[14];
		char rua[30],bairro[30],cidade[30],UF[6],numero[9];
	};
	
	struct OPERADORESDOSISTEMA{
		int codigo,nivel_permissao;
		char nome[40],usuario[15],senha[15];
	};
	
int data_sistema(){
	
	int i;
	char dataSis[9],hora[9],Dia[3],Mes[3],Ano[3],Hora[3],Minuto[3];

	_strdate(dataSis); //armazena a data na variavel
	//3,4,5= Dia || 0,1,2=Mes || 6,7=Ano || 8= \0
	
	_strtime(hora); //armazena o horario na variavel 
	//0,1,2=Hora || 3,4,5=Minutos || 6,7=Segundos || 8= \0 

	Mes[0] = (dataSis[0]);
	Mes[1] = (dataSis[1]);
	Mes[2] = ('\0');
    Dia[0] = (dataSis[3]);
    Dia[1] = (dataSis[4]);
    Dia[2] = ('\0');
    Ano[0] = (dataSis[6]);
	Ano[1] = (dataSis[7]);
	Ano[2] = ('\0');

	Hora[0] = (hora[0]);
	Hora[1] = (hora[1]);
	Minuto[0] = (hora[3]);
	Minuto[1] = (hora[4]);
	

	fflush(stdin); // limpa o buffer do teclado
	dia=atoi(Dia); //converte string para inteiro
	mes=atoi(Mes); //converte string para inteiro
	ano=atoi(Ano); //converte string para inteiro
	ano = ano+2000;
	horas=atoi(Hora);
	minutos=atoi(Minuto);
	
}

int checagem_reservas(){//verifica aqui
	
	FILE *open_reservas;
	int i;
	int *codigo_reserva = malloc(numero_reservas*sizeof(int));
	int *dia_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *dias_reservado = malloc(numero_reservas*sizeof(int));
	int *dia_final_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_final_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_final_reserva = malloc(numero_reservas*sizeof(int));
	int *quarto_reservado = malloc(numero_reservas*sizeof(int));
	int *codhosp_reserva = malloc(numero_reservas*sizeof(int));
	int *situacao = malloc(numero_reservas*sizeof(int));
	int terminou = 0;
	
	char txt[5]=".txt",numero_reserva[3],openreserva[23];
	for(i=0;i<numero_reservas;i++){//pega os dados das reservas ja efetuadas
		sprintf(numero_reserva, "%i", i+1);//converte interio em string
		strcpy (openreserva, "dados\\reserva");//define valor a string
		strcat (openreserva, numero_reserva); // junta duas strings
		strcat (openreserva, txt); // junta duas strings
		
		open_reservas = fopen(openreserva,"r");
		
		fscanf(open_reservas,"%i",&codigo_reserva[i]);
		fscanf(open_reservas,"%i",&dia_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&mes_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&ano_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&dias_reservado[i]);
		fscanf(open_reservas,"%i",&dia_final_reserva[i]);
		fscanf(open_reservas,"%i",&mes_final_reserva[i]);
		fscanf(open_reservas,"%i",&ano_final_reserva[i]);
		fscanf(open_reservas,"%i",&quarto_reservado[i]);
		fscanf(open_reservas,"%i",&codhosp_reserva[i]);
		fscanf(open_reservas,"%i",&situacao[i]);

		fclose(open_reservas);
	}

	for(i=0;i<numero_reservas;i++){
		terminou =0;
		if((situacao[i] ==1)){
			if(ano_final_reserva[i] == ano){
				if(mes_final_reserva[i] == mes){
					if(dia_final_reserva[i]<=dia){
						terminou=1;//
					}
				}
				if(mes_final_reserva[i] < mes){
					terminou =1;//
				}
			}
			if(ano_final_reserva[i] < ano){
				terminou =1;//
			}
		}
		if(terminou ==1){
			sprintf(numero_reserva, "%i", i+1);//converte interio em string
			strcpy (openreserva, "dados\\reserva");//define valor a string
			strcat (openreserva, numero_reserva); // junta duas strings
			strcat (openreserva, txt); // junta duas strings
			
			open_reservas = fopen(openreserva,"w");
			
			fprintf(open_reservas,"%i\n",codigo_reserva[i]);
			fprintf(open_reservas,"%i\n",dia_inicio_reserva[i]);
			fprintf(open_reservas,"%i\n",mes_inicio_reserva[i]);
			fprintf(open_reservas,"%i\n",ano_inicio_reserva[i]);
			fprintf(open_reservas,"%i\n",dias_reservado[i]);
			fprintf(open_reservas,"%i\n",dia_final_reserva[i]);
			fprintf(open_reservas,"%i\n",mes_final_reserva[i]);
			fprintf(open_reservas,"%i\n",ano_final_reserva[i]);
			fprintf(open_reservas,"%i\n",quarto_reservado[i]);
			fprintf(open_reservas,"%i\n",codhosp_reserva[i]);
			fprintf(open_reservas,"3");
			// 0 = cancelada
			// 1 = Ativa
			// 2 = em uso
			// 3 = já passpo
		
			fclose(open_reservas);
		}
	}
}

int verificar_contas_cartao(){
	
	char ql;
	int numero_linhas=0,alocar,i,j,exibir,recebe;
	FILE *contas;
	FILE *caixa_Hotel;
	FILE *historico_mes;
	FILE *historico_completo;
	FILE *hitorico_recibos;
	
	contas = fopen("dados\\contas.txt","r");
	while((ql = fgetc(contas)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(contas);
	
	alocar=numero_linhas/5;

	int *dia_receber = malloc(alocar*sizeof(int));
	int *mes_receber = malloc(alocar*sizeof(int));
	int *ano_receber = malloc(alocar*sizeof(int));
	float *valor = malloc(alocar*sizeof(float));
	char *descricao[alocar];
	
	contas = fopen("dados\\contas.txt","r");
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		
		fscanf(contas,"%i\n",&dia_receber[i]);
		fscanf(contas,"%i\n",&mes_receber[i]);
		fscanf(contas,"%i\n",&ano_receber[i]);
		fscanf(contas,"%f\n",&valor[i]);
		fscanf(contas,"\n%[^\n]s",descricao[i]);
	}
	fclose(contas);
	
	contas = fopen("dados\\contas.txt","w");
	fclose(contas);
	for(i=0;i<alocar;i++){
		recebe =0;
		if(ano_receber[i] == ano){
			if(mes_receber[i] == mes){
				if(dia_receber[i] <= dia){
					recebe =1;
				}
			}else if(mes_receber[i] < mes){
				recebe =1;
			}
		}else if(ano_receber[i] < ano){
			recebe =1;
		}
		
		if(recebe == 1){
			
			caixa = caixa+valor[i];
			
			historico_mes = fopen("dados\\Historico mes.txt","a");
			fprintf(historico_mes,"Recebendo= %s\n",descricao[i]);
			fprintf(historico_mes,"%f\n",valor[i]);
			fprintf(historico_mes,"%f\n",caixa);
			fprintf(historico_mes,"%d\n%d\n%d\n",dia_receber[i],mes_receber[i],ano_receber[i]);
			fclose(historico_mes);
			
			historico_completo = fopen("dados\\Historico completo.txt","a");
			fprintf(historico_completo,"Recebendo= %s\n",descricao[i]);
			fprintf(historico_completo,"%f\n",valor[i]);
			fprintf(historico_completo,"%f\n",caixa);
			fprintf(historico_completo,"%d/%d/%d\n",dia_receber[i],mes_receber[i],ano_receber[i]);
			fclose(historico_completo);
			
			hitorico_recibos = fopen("dados\\Historico recibos.txt","a");
			fprintf(hitorico_recibos,"%s\n",descricao[i]);
			fprintf(hitorico_recibos,"%f\n",valor[i]);
			fprintf(hitorico_recibos,"%d/%d/%d\n",dia_receber[i],mes_receber[i],ano_receber[i]);
			fclose(hitorico_recibos);
			
			caixa_Hotel = fopen("dados\\caixa.txt","w");
			fprintf(caixa_Hotel,"%f",caixa);
			fclose(caixa_Hotel);

		}else{
			contas = fopen("dados\\contas.txt","a");
			fprintf(contas,"%i\n",dia_receber[i]);
			fprintf(contas,"%i\n",mes_receber[i]);
			fprintf(contas,"%i\n",ano_receber[i]);
			fprintf(contas,"%f\n",valor[i]);
			fprintf(contas,"%s\n",descricao[i]);
			fclose(contas);
		}
	}
}

int verificar_contas_pagar(){
	
	char ql;
	int numero_linhas=0,alocar,i,j,exibir,recebe;
	FILE *contas;
	FILE *caixa_Hotel;
	FILE *historico_mes;
	FILE *historico_completo;
	FILE *hitorico_recibos;
	
	contas = fopen("dados\\pagar.txt","r");
	while((ql = fgetc(contas)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(contas);
	
	alocar=numero_linhas/5;

	int *dia_receber = malloc(alocar*sizeof(int));
	int *mes_receber = malloc(alocar*sizeof(int));
	int *ano_receber = malloc(alocar*sizeof(int));
	float *valor = malloc(alocar*sizeof(float));
	char *descricao[alocar];
	
	contas = fopen("dados\\pagar.txt","r");
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		
		fscanf(contas,"%i\n",&dia_receber[i]);
		fscanf(contas,"%i\n",&mes_receber[i]);
		fscanf(contas,"%i\n",&ano_receber[i]);
		fscanf(contas,"%f\n",&valor[i]);
		fscanf(contas,"\n%[^\n]s",descricao[i]);
	}
	fclose(contas);
	
	contas = fopen("dados\\pagar.txt","w");
	fclose(contas);
	
	for(i=0;i<alocar;i++){
		recebe =0;
		if(ano_receber[i] == ano){
			if(mes_receber[i] == mes){
				if(dia_receber[i] <= dia){
					recebe =1;
				}
			}else if(mes_receber[i] < mes){
				recebe =1;
			}
		}else if(ano_receber[i] < ano){
			recebe =1;
		}
		
		if(recebe == 1){
			
			caixa = caixa-valor[i];
			
			historico_mes = fopen("dados\\Historico mes.txt","a");
			fprintf(historico_mes,"Pagando= %s\n",descricao[i]);
			fprintf(historico_mes,"%f\n",0-valor[i]);
			fprintf(historico_mes,"%f\n",caixa);
			fprintf(historico_mes,"%d\n%d\n%d\n",dia_receber[i],mes_receber[i],ano_receber[i]);
			fclose(historico_mes);
			
			historico_completo = fopen("dados\\Historico completo.txt","a");
			fprintf(historico_completo,"Pagando= %s\n",descricao[i]);
			fprintf(historico_completo,"%f\n",0-valor[i]);
			fprintf(historico_completo,"%f\n",caixa);
			fprintf(historico_completo,"%d/%d/%d\n",dia_receber[i],mes_receber[i],ano_receber[i]);
			fclose(historico_completo);
			
			hitorico_recibos = fopen("dados\\Historico pagamentos.txt","a");
			fprintf(hitorico_recibos,"%s\n",descricao[i]);
			fprintf(hitorico_recibos,"%f\n",valor[i]);
			fprintf(hitorico_recibos,"%d/%d/%d\n",dia_receber[i],mes_receber[i],ano_receber[i]);
			fclose(hitorico_recibos);
			
			hitorico_recibos = fopen("dados\\Historico pagamentos mes.txt","a");
			fprintf(hitorico_recibos,"%s\n",descricao[i]);
			fprintf(hitorico_recibos,"%f\n",valor[i]);
			fprintf(hitorico_recibos,"%d\n%d\n%d\n",dia_receber[i],mes_receber[i],ano_receber[i]);
			fclose(hitorico_recibos);
			
			caixa_Hotel = fopen("dados\\caixa.txt","w");
			fprintf(caixa_Hotel,"%f",caixa);
			fclose(caixa_Hotel);

		}else{
			contas = fopen("dados\\pagar.txt","a");
			fprintf(contas,"%i\n",dia_receber[i]);
			fprintf(contas,"%i\n",mes_receber[i]);
			fprintf(contas,"%i\n",ano_receber[i]);
			fprintf(contas,"%f\n",valor[i]);
			fprintf(contas,"%s\n",descricao[i]);
			fclose(contas);
		}
	}
}

int login(){
	int i,entrar,a,b;
	char txt[5] = ".txt",numerodooperador[3],novooperador[23];
	FILE *operador;
	int *codigo_operador = malloc(num_operadores*sizeof(int)),*permissao = malloc(num_operadores*sizeof(int));
	char *nome[num_operadores],*usuario[num_operadores],*senha[num_operadores],*user = malloc(sizeof(char)*15),*pass = malloc(sizeof(char)*15);
	
	for(i=0;i<num_operadores;i++){
		nome[i] = malloc(40*sizeof(char));
		usuario[i] = malloc(15*sizeof(char));
		senha[i] = malloc(15*sizeof(char));
	
		sprintf(numerodooperador, "%i", i+1);//converte interio em string
		strcpy (novooperador, "dados\\user");//define valor a string
		strcat (novooperador, numerodooperador); // junta duas strings
		strcat (novooperador, txt); // junta duas strings
		
		operador = fopen(novooperador,"r");
		if(operador != NULL){
			fscanf(operador,"%d",&codigo_operador[i]);
			fscanf(operador,"\n%[^\n]s",nome[i]);
			fscanf(operador,"\n%[^\n]s",usuario[i]);
			fscanf(operador,"\n%[^\n]s",senha[i]);
			fscanf(operador,"%d",&permissao[i]);
		}
		fclose(operador);
	}
	
	do{
		#ifdef WIN32
			system("CLS");
		#else
			system("clear");
		#endif

		printf("=====================================================================\n");
		printf("======================== Login no Sistema ===========================\n");
		printf("===== Digite o Usuario: ");
		scanf("%s",user);
		printf("===== Digite a Senha: ");
		scanf("%s",pass);
		
		entrar=0;
		printf("=====================================================================\n");
		
		for(i=0;i<num_operadores;i++){
			if((strcmp(user,usuario[i]) ==0) && (strcmp(pass,senha[i]) ==0 )){
				entrar=1;
				nivel_permissao=permissao[i];
			}
		}
		
		if(entrar==1){
			printf("Login Realizado Com Sucesso\n");
		}else{
			printf("Usuario ou senha incorretos, Tente Novamente\n");
		}
		
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}while(entrar==0);
	//free(codigo_operador);
	//free(permissao);
	
	for(i=0;i<num_operadores;i++){
	//	free(nome[i]);
	//	free(usuario[i]);
	//	free(senha[i]);
	}
}

int binario(){
	int converter;
	FILE *arq;
	FILE *hosp;
	int i,j;
	char txt[5] = ".txt";
	char caminhobin[23];
	struct HOSPEDE hospedes;
	char numerodohospede[3];
	char newhospede[23];
	int exibir = 1;
	FILE *acomod; //Cria o arquivo
	char numerodaacomodacao[3];
	char acomodacao[23];
	
	FILE *prod;
	int *codigo_produto = malloc(numero_de_produtos*sizeof(int));
	char numerodeprodutos[3];
	char openproduto[23];
	char *descricao_produto[numero_de_produtos];
	
	int *estoque = malloc(numero_de_produtos*sizeof(int)),*estoque_minimo= malloc(numero_de_produtos*sizeof(int));
	float *preco_custo= malloc(numero_de_produtos*sizeof(float)),*preco_venda= malloc(numero_de_produtos*sizeof(float));
	
	int *codigo = malloc(numero_de_acomodacoes * sizeof(int));
	char *descricao[numero_de_acomodacoes];
	char *facilidades[numero_de_acomodacoes];
	int *tipo = malloc(numero_de_acomodacoes * sizeof(int));
	
	FILE *forn;
	
	int *codigo_fornecedor = malloc(numero_de_fornecedores*sizeof(int));
	char *nome_fornecedor[numero_de_fornecedores];
	char *razaosocial[numero_de_fornecedores];
	char *email[numero_de_fornecedores];
	char *inscricaoestadual[numero_de_fornecedores];
	char *cnpj[numero_de_fornecedores];
	char *telefone[numero_de_fornecedores];
	char *rua[numero_de_fornecedores];
	char *bairro[numero_de_fornecedores];
	char *cidade[numero_de_fornecedores];
	char *UF[numero_de_fornecedores];
	char *numero[numero_de_fornecedores];

	char numerodofornecedor[3];
	char openfornecedor[23];
	
	
	
	printf("=====================================================================\n");
	printf("=============== Converter Dados de texto para Binario ===============\n");
	printf("====== 1. Dados Do Hotel ============================================\n");
	printf("====== 2. Dados dos Hospedes ========================================\n");
	printf("====== 3. Dados Das Acomodacoes =====================================\n");
	printf("====== 4. Dados dos Produtos ========================================\n");
	printf("====== 5. Dados Dos Fornecedores ====================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	scanf("%d",&converter);
	switch(converter){
		case 1:
			arq = fopen("binario\\hotel.bin","wb");
			
			fwrite(&nomefantasia,sizeof(char),strlen(nomefantasia),arq);
			fwrite(&razaosocial,sizeof(char),strlen(razaosocial),arq);
			fwrite(&inscricaoestadual,sizeof(char),strlen(inscricaoestadual),arq);
			fwrite(&cnpj,sizeof(char),strlen(cnpj),arq);
			fwrite(&rua,sizeof(char),strlen(rua),arq);
			fwrite(&numero,sizeof(char),strlen(numero),arq);
			fwrite(&bairro,sizeof(char),strlen(bairro),arq);
			fwrite(&cidade,sizeof(char),strlen(cidade),arq);
			fwrite(&UF,sizeof(char),strlen(UF),arq);
			fwrite(&telefone,sizeof(char),strlen(telefone),arq);
			fwrite(&email,sizeof(char),strlen(email),arq);
			fwrite(&nomedoresponsavel,sizeof(char),strlen(nomedoresponsavel),arq);
			fwrite(&telefonedoresponsavel,sizeof(char),strlen(telefonedoresponsavel),arq);
			fwrite(&margemlucro,sizeof(int),1,arq);
			fclose(arq);
		break;
		case 2:
			for(i=0;i<numero_de_hospedes;i++){
				sprintf(numerodohospede, "%i", i+1);//converte interio em string
				strcpy (newhospede, "dados\\hospede");//define valor a string
				strcat (newhospede, numerodohospede); // junta duas strings
				strcat (newhospede, txt); // junta duas strings
				
				hosp = fopen(newhospede,"r");
				if(hosp!=NULL){
					fscanf(hosp,"%i\n",&hospedes.codigohospede);
					fscanf(hosp,"\n%[^\n]s",hospedes.nome);
					fscanf(hosp,"\n%[^\n]s",hospedes.email);
					fscanf(hosp,"\n%[^\n]s",hospedes.sexo);
					fscanf(hosp,"\n%[^\n]s",hospedes.rua);
					fscanf(hosp,"\n%[^\n]s",hospedes.numero);
					fscanf(hosp,"\n%[^\n]s",hospedes.bairro);
					fscanf(hosp,"\n%[^\n]s",hospedes.cidade);
					fscanf(hosp,"\n%[^\n]s",hospedes.UF);
					fscanf(hosp,"\n%[^\n]s",hospedes.cpf);
					fscanf(hosp,"\n%[^\n]s",hospedes.telefone);
					fscanf(hosp,"\n%[^\n]s",hospedes.datanascimento);
					
					strcpy (caminhobin, "binario\\Hospede");//define valor a string
					strcat (newhospede, numerodohospede); // junta duas strings
					arq = fopen(caminhobin,"wb");
			
					fwrite(&hospedes.codigohospede,sizeof(int),1,arq);
					fwrite(&hospedes.nome,sizeof(char),strlen(hospedes.nome),arq);
					fwrite(&hospedes.email,sizeof(char),strlen(hospedes.email),arq);
					fwrite(&hospedes.sexo,sizeof(char),strlen(hospedes.sexo),arq);
					fwrite(&hospedes.rua,sizeof(char),strlen(hospedes.rua),arq);
					fwrite(&hospedes.numero,sizeof(char),strlen(hospedes.numero),arq);
					fwrite(&hospedes.bairro,sizeof(char),strlen(hospedes.bairro),arq);
					fwrite(&hospedes.cidade,sizeof(char),strlen(hospedes.cidade),arq);
					fwrite(&hospedes.UF,sizeof(char),strlen(hospedes.UF),arq);
					fwrite(&hospedes.cpf,sizeof(char),strlen(hospedes.cpf),arq);
					fwrite(&hospedes.telefone,sizeof(char),strlen(hospedes.telefone),arq);
					fwrite(&hospedes.datanascimento,sizeof(char),strlen(hospedes.datanascimento),arq);
					fclose(arq);	
				}
				fclose(hosp);
			}	
		break;
		case 3:
			for(i=0; i<numero_de_acomodacoes; i++){
				descricao[i] = malloc(250 * sizeof(char));
				facilidades[i] = malloc(250 * sizeof(char));
			
				sprintf(numerodaacomodacao, "%i", i+1);//converte interio em string
				strcpy (acomodacao,"dados\\acomodacao"); //Define valor a string
				strcat (acomodacao, numerodaacomodacao);//Junta a string de caminho com o numero	
				strcat (acomodacao, txt);//junta a string de caminho+numero com o formato .txt
				
				acomod = fopen(acomodacao,"r");	
				if(acomod != NULL){
					fscanf(acomod,"%i\n",&codigo[i]);
					fscanf(acomod,"\n%[^\n]s",descricao[i]);
					fscanf(acomod,"\n%[^\n]s",facilidades[i]);
					fscanf(acomod,"%i\n",&tipo[i]);	

					strcpy (caminhobin, "binario\\Acomodacao");//define valor a string
					strcat (newhospede, numerodaacomodacao); // junta duas strings
					
					arq = fopen(caminhobin,"wb");
			
					fwrite(&codigo[i],sizeof(int),1,arq);
					fwrite(&descricao[i],sizeof(char),strlen(descricao[i]),arq);
					fwrite(&facilidades[i],sizeof(char),strlen(facilidades[i]),arq);
					fwrite(&tipo[i],sizeof(int),1,arq);
					fclose(arq);	
				}
				fclose(acomod);
			}	
		break;

		case 4:
			for(i=0;i<numero_de_produtos;i++){
				descricao_produto[i] = malloc(260*sizeof(char));
				sprintf(numerodeprodutos, "%i", i+1);//converte interio em string
				strcpy (openproduto, "dados\\produto");//define valor a string
				
				strcat (openproduto, numerodeprodutos); // junta duas strings
				strcat (openproduto, txt); // junta duas strings
				
				prod = fopen(openproduto,"r");
				if(prod != NULL){
					fscanf(prod,"%i\n",&codigo_produto[i]);
					fscanf(prod,"\n%[^\n]s",descricao_produto[i]);
					fscanf(prod,"%i\n",&estoque[i]);
					fscanf(prod,"%i\n",&estoque_minimo[i]);
					fscanf(prod,"%f\n",&preco_custo[i]);
					fscanf(prod,"%f\n",&preco_venda[i]);
					

					strcpy (caminhobin, "binario\\Produto");//define valor a string
					strcat (newhospede, numerodeprodutos); // junta duas strings
					
					arq = fopen(caminhobin,"wb");
			
					fwrite(&codigo_produto[i],sizeof(int),1,arq);
					fwrite(&descricao_produto[i],sizeof(char),strlen(descricao_produto[i]),arq);
					fwrite(&estoque[i],sizeof(int),1,arq);
					fwrite(&estoque_minimo[i],sizeof(int),1,arq);
					fwrite(&preco_custo[i],sizeof(float),1,arq);
					fwrite(&preco_venda[i],sizeof(float),1,arq);
					fclose(arq);	
				}
				fclose(prod);
			}	
		break;
		case 5:
			for(i=0;i<numero_de_fornecedores;i++){
				
				nome_fornecedor[i] = malloc(40*sizeof(char));
				razaosocial[i] = malloc(40*sizeof(char));
				email[i] = malloc(40*sizeof(char));
        		inscricaoestadual[i] = malloc(16*sizeof(char));
				cnpj[i] = malloc(16*sizeof(char));
				telefone[i] = malloc(16*sizeof(char));
				rua[i] = malloc(30*sizeof(char));
				bairro[i] = malloc(30*sizeof(char));
				cidade[i] = malloc(30*sizeof(char));
				UF[i] = malloc(6*sizeof(char));
				numero[i] = malloc(9*sizeof(char));
				
				sprintf(numerodofornecedor, "%i", i+1);//converte interio em string
				strcpy (openfornecedor, "dados\\fornecedor");//define valor a string
				
				strcat (openfornecedor, numerodofornecedor); // junta duas strings
				strcat (openfornecedor, txt); // junta duas strings
				
				forn = fopen(openfornecedor,"r");
				if (forn != NULL){
					fscanf(forn,"%i\n",&codigo_fornecedor[i]);
					fscanf(forn,"\n%[^\n]s",nome_fornecedor[i]);
					fscanf(forn,"\n%[^\n]s",razaosocial[i]);
					fscanf(forn,"\n%[^\n]s",email[i]);
					fscanf(forn,"\n%[^\n]s",inscricaoestadual[i]);
					fscanf(forn,"\n%[^\n]s",cnpj[i]);
					fscanf(forn,"\n%[^\n]s",rua[i]);
					fscanf(forn,"\n%[^\n]s",numero[i]);
					fscanf(forn,"\n%[^\n]s",bairro[i]);
					fscanf(forn,"\n%[^\n]s",cidade[i]);
					fscanf(forn,"\n%[^\n]s",UF[i]);
					fscanf(forn,"\n%[^\n]s",telefone[i]);
					
					strcpy (caminhobin, "binario\\Fornecedor");//define valor a string
					strcat (newhospede, numerodohospede); // junta duas strings
					arq = fopen(caminhobin,"wb");
			
					fwrite(&codigo_fornecedor[i],sizeof(int),1,arq);
					fwrite(&nome_fornecedor[i],sizeof(char),strlen(nome_fornecedor[i]),arq);
					fwrite(&razaosocial[i],sizeof(char),strlen(razaosocial[i]),arq);
					fwrite(&email[i],sizeof(char),strlen(email[i]),arq);
					fwrite(&inscricaoestadual[i],sizeof(char),strlen(inscricaoestadual[i]),arq);
					fwrite(&cnpj[i],sizeof(char),strlen(cnpj[i]),arq);
					fwrite(&rua[i],sizeof(char),strlen(rua[i]),arq);
					fwrite(&numero[i],sizeof(char),strlen(numero[i]),arq);
					fwrite(&bairro[i],sizeof(char),strlen(bairro[i]),arq);
					fwrite(&cidade[i],sizeof(char),strlen(cidade[i]),arq);
					fwrite(&UF[i],sizeof(char),strlen(UF[i]),arq);
					fwrite(&telefone[i],sizeof(char),strlen(telefone[i]),arq);
					fclose(arq);
				}
				fclose(forn);
			}
		break;
		default:
			binario();
	}
	main();
}

////////////////////////
//modulo 1//////////////
////////////////////////
int alterardados(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==================== O Que Deseja Alterar? ==========================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==== 1. Nome do Hotel: %s\n",nomefantasia);
	printf("==== 2. Razao Social: %s\n",razaosocial);
	printf("==== 3. Inscricao Estadual: %s\n",inscricaoestadual);
	printf("==== 4. CNPJ: %s\n",cnpj);
	
	printf("==== Endereco\n");
	printf("========= 5. Rua: %s\n",rua);
	printf("========= 6. Numero: %s\n",numero);
	printf("========= 7. Bairro: %s\n",bairro);
	printf("========= 8. Cidade: %s\n",cidade);
	printf("========= 9. UF: %s\n",UF);
	
	printf("==== 10. Telefone: %s\n",telefone);
	printf("==== 11. E-mail: %s\n",email);
	printf("==== 12. Nome Do Responsavel(Dono Ou Gerente): %s\n",nomedoresponsavel);
	printf("==== 13. Telefone do responsavel: %s\n",telefonedoresponsavel);
	printf("==== 14. Margem de lucro de produtos vendidos: %d%%\n",margemlucro);
	printf("==== 15. Alterar Todos:\n");
	printf("==== 16. Voltar =====================================================\n");
	printf("==== 0. Sair ========================================================\n");
	int opcaoalterar =0;
	scanf("%d", &opcaoalterar);
	switch(opcaoalterar){
		case 0:
			exit(0);
		break;
		case 1:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(nomefantasia);
		break;
		
		case 2:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(razaosocial);
		break;
		
		case 3:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(inscricaoestadual);
		break;
		
		case 4:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(cnpj);
		break;
		
		case 5:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(rua);
		break;
		
		case 6:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(numero);
		break;
		
		case 7:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(bairro);
		break;
		
		case 8:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(cidade);
		break;
		
		case 9:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(UF);
		break;
		
		case 10:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(telefone);
		break;
		
		case 11:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(email);
		break;
		
		case 12:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(nomedoresponsavel);
		break;
		
		case 13:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(telefonedoresponsavel);
		break;
		
		case 14:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			scanf("%f",&margemlucro);
		break;
		
		case 15:
			fflush(stdin); // limpa o buffer do teclado
			printf("==== Nome do Hotel:");
			gets(nomefantasia);
			printf("==== Razao Social:");
			gets(razaosocial);
			printf("==== Inscricao Estadual:");
			gets(inscricaoestadual);
			printf("==== CNPJ:");
			gets(cnpj);
			printf("========= endereco:\n");
			printf("========= Rua:");
			gets(rua);
			printf("========= Numero:");
			gets(numero);
			printf("========= Bairro:");
			gets(bairro);
			printf("========= Cidade:");
			gets(cidade);
			printf("========= UF:");
			gets(UF);
			printf("==== Telefone:");
			gets(telefone);
			printf("==== E-mail:");
			gets(email);
			printf("==== Nome Do Responsavel(Dono Ou Gerente):");
			gets(nomedoresponsavel);
			printf("==== Telefone do responsavel:");
			gets(telefonedoresponsavel);
			printf("==== Margem de lucro de produtos vendidos:");
			scanf("%d",&margemlucro);
		break;
		case 16:
			dadosdohotel();
		break;
		default:
			alterardados();	
	}
	
	FILE *hotel;
	hotel = fopen("dados\\hotel.txt","w");
	
	fprintf(hotel,"%s\n",nomefantasia);
	fprintf(hotel,"%s\n",razaosocial);
	fprintf(hotel,"%s\n",inscricaoestadual);
	fprintf(hotel,"%s\n",cnpj);
	fprintf(hotel,"%s\n",rua);
	fprintf(hotel,"%s\n",numero);
	fprintf(hotel,"%s\n",bairro);
	fprintf(hotel,"%s\n",cidade);
	fprintf(hotel,"%s\n",UF);
	fprintf(hotel,"%s\n",telefone);
	fprintf(hotel,"%s\n",email);
	fprintf(hotel,"%s\n",nomedoresponsavel);
	fprintf(hotel,"%s\n",telefonedoresponsavel);
	fprintf(hotel,"%d",&margemlucro);
	
	fclose(hotel);
	
	
	alterardados();
}

int verificardadosdohotel(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==== Nome do Hotel: %s \n",nomefantasia);
	printf("==== Razao Social: %s \n",razaosocial);
	printf("==== Inscricao Estadual: %s \n",inscricaoestadual);
	printf("==== CNPJ: %s \n",cnpj);
	
	printf("==== Endereco\n");
	printf("=========Rua: %s\n",rua);
	printf("========= Numero: %s\n",numero);
	printf("========= Bairro: %s\n",bairro);
	printf("========= Cidade: %s\n",cidade);
	printf("========= UF: %s\n",UF);
	
	printf("==== Telefone: %s \n",telefone);
	printf("==== E-mail: %s \n",email);
	printf("==== Nome Do Responsavel(Dono Ou Gerente): %s \n",nomedoresponsavel);
	printf("==== Telefone do responsavel: %s \n",telefonedoresponsavel);
	printf("==== Margem de Lucro: %d%% \n",margemlucro);
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==== 1. Voltar ======================================================\n");
	printf("==== 0. Sair ========================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	int op;
	scanf("%d",&op);
	switch(op){
		case 1:
			dadosdohotel();
		break;
		case 0:
			exit(0);
		break;
		default:
			verificardadosdohotel();
	}
	
}

int dadosdohotel(){ /* 1*/
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==== 1. Alterar Dados ===============================================\n");
	printf("==== 2. Verificar Dados =============================================\n");
	printf("==== 3. Voltar ======================================================\n");
	printf("=====================================================================\n");
	int categoriadesejada;
	categoriadesejada = 0;
	scanf("%d", &categoriadesejada);
	
	switch (categoriadesejada){
	case 1:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		alterardados();
	break;
	case 2:
		verificardadosdohotel();
	break;
	case 3:
		modulodecadastrosegestaodedados();
	break;
	default:
		dadosdohotel();
	}
	main();
}
///////////////////////////////////////////////////////////
int dadosdoshospedes(){/* 2*/
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==== 1. Exibir ou Alterar Dados dos Hospedes ========================\n");
	printf("==== 2. Inserir Novo Hospede ========================================\n");
	printf("==== 3. Voltar ======================================================\n");
	printf("=====================================================================\n");
	
	int categoriadesejada;
	categoriadesejada = 0;
	scanf("%d", &categoriadesejada);
	
	switch (categoriadesejada){
	case 1:
		pesquisarhospedes();
	break;
	case 2:
		inserirhospede();
	break;
	case 3:
		modulodecadastrosegestaodedados();
	break;
	default:
		dadosdohotel();
	}
	main();
}

int	pesquisarhospedes(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int op;
	
	printf("=====================================================================\n");
	printf("======================= Pesquisar Hospedes ==========================\n");
	printf("=====================================================================\n");
	printf("====== 1. Pesquisar Hospede por codigo: =============================\n");
	printf("====== 2. Exibir Nome e Codigo de Todos Os Hospedes Cadastrados: ====\n");
	printf("====== 3. Voltar ====================================================\n");
	printf("====== 0. Sair ======================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op);
	
	switch(op){
	case 1:
		pesquisarcodigohospede();
	break;
	case 2:
		exibirtodos();
	break;
	case 3:
		dadosdoshospedes();
	break;
	case 0:
		exit(0);
	break;
	default:
		pesquisarhospedes();
	}
	main();
}

int pesquisarcodigohospede(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i;
	
	FILE *hosp;
	
	int codigo_pesquisado;
	char txt[5] = ".txt";
	char numerodohospede[3];
	char openhospede[23]="dados\\hospede";
	
	printf("=====================================================================\n");
	printf("====================== Pesquisar por Codigo =========================\n");
	printf("=====================================================================\n");
	printf("====== Insira o codigo do hospede que deseja acessar: ===============\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&codigo_pesquisado);
		
		sprintf(numerodohospede, "%i", codigo_pesquisado);//converte interio em string		
		strcat (openhospede, numerodohospede); // junta duas strings
		strcat (openhospede, txt); // junta duas strings
		
		hosp = fopen(openhospede,"r");
	
	if (hosp == NULL){
		printf("Hospede com codigo %d Inexistente, Tente Novamente\n", codigo_pesquisado);
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		fclose(hosp);
	}
	else{
		fclose(hosp);
		opcaohospede(codigo_pesquisado);
		
	}
	pesquisarcodigohospede();
	
}

int opcaohospede(int codigo){
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int op;
	
	printf("=====================================================================\n");
	printf("====================== Digite sua opcao =============================\n");
	printf("=====================================================================\n");
	printf("====== 1. Alterar dados do Hospede: ================================\n");
	printf("====== 2. Deletar Hospede ==========================================\n");	
	printf("====== 3. Voltar ====================================================\n");
	printf("====== 0. Sair ======================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op);
	
	switch(op){
	case 1:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		alterardadoshospedes(codigo);
	break;
	case 2:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		deletarhospede(codigo);
	break;
	case 3:
		dadosdoshospedes();
	break;		
	case 0:
		exit(0);
	break;
	default:
		opcaohospede(codigo);
	}
	main();
}

int alterardadoshospedes(int codigo){ 
	
	struct HOSPEDE alterarhospede;
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i;
	FILE *hosp, *savehospede;
	
	char newhospede[23] = "dados\\hospede";
	char txt[5] = ".txt";
	char numerodohospede[3];
	sprintf(numerodohospede, "%i", codigo);//converte interio em string
	
	strcat (newhospede, numerodohospede); // junta duas strings
	strcat (newhospede, txt); // junta duas strings
	
	hosp = fopen(newhospede,"r");
	
	fscanf(hosp,"%i\n",&codigo);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.nome);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.email);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.sexo);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.estadocivil);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.rua);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.numero);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.bairro);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.cidade);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.UF);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.cpf);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.telefone);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.cidade);
	fscanf(hosp,"\n%[^\n]s",alterarhospede.datanascimento);
	
	fclose(hosp);

	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==================== O Que Deseja Alterar? ==========================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==== Codigo: %i\n",codigo);
	printf("==== 1. Nome: %s\n",alterarhospede.nome);
	printf("==== 2. E-mail: %s\n",alterarhospede.email);
	printf("==== 3. Sexo: %s\n",alterarhospede.sexo);
	printf("==== 4. Estado Civil: %s\n",alterarhospede.estadocivil);
	
	printf("==== Endereco\n");
	printf("========= 5. Rua: %s\n",alterarhospede.rua);
	printf("========= 6. Numero: %s\n",alterarhospede.numero);
	printf("========= 7. Bairro: %s\n",alterarhospede.bairro);
	printf("========= 8. Cidade: %s\n",alterarhospede.cidade);
	printf("========= 9. UF: %s\n",alterarhospede.UF);
	
	printf("==== 10. CPF: %s\n",alterarhospede.cpf);
	printf("==== 11. Telefone: %s\n",alterarhospede.telefone);
	printf("==== 12. Data de Nascimento: %s\n",alterarhospede.datanascimento);
	printf("==== 13. Alterar Todos ==============================================\n");
	printf("==== 14. Voltar =====================================================\n");
	printf("==== 0. Sair ========================================================\n");
	int opcaoalterar =0;
	scanf("%d", &opcaoalterar);
	
	switch(opcaoalterar){
		case 0:
			exit(0);
		break;
		
		case 1:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.nome);
		break;
		
		case 2:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.email);
		break;
		
		case 3:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.sexo);
		break;
		
		case 4:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.estadocivil);
		break;
		
		case 5:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.rua);
		break;
		
		case 6:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.numero);
		break;
		
		
		case 7:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.bairro);
		break;
		
		case 8:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.cidade);
		break;
		
		case 9:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.UF);
		break;
		
		case 10:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.cpf);
		break;
		
		case 11:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.telefone);
		break;
		
		case 12:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarhospede.datanascimento);
		break;
		
		case 13:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo Nome:");
			gets(alterarhospede.nome);
			
			printf("Insira o novo E-mail:");
			gets(alterarhospede.email);
	
			printf("Insira o novo Sexo:");
			gets(alterarhospede.sexo);
		
			printf("Insira o novo Estado Civil:");
			gets(alterarhospede.estadocivil);
		
			printf("Insira a nova Rua:");
			gets(alterarhospede.rua);
		
			printf("Insira o novo Numero:");
			gets(alterarhospede.numero);
		
			printf("Insira o novo Bairro:");
			gets(alterarhospede.bairro);
		
			printf("Insira a nova Cidade:");
			gets(alterarhospede.cidade);
		
			printf("Insira o novo UF:");
			gets(alterarhospede.UF);

			printf("Insira o novo CPF:");
			gets(alterarhospede.cpf);
		
			printf("Insira o novo Telefone:");
			gets(alterarhospede.telefone);
		
			printf("Insira a nova Data de Nascimento:");
			gets(alterarhospede.datanascimento);

		break;
		
		case 14:
			dadosdoshospedes();
		break;
		default:
			alterardadoshospedes(codigo);
	}
	
	savehospede = fopen(newhospede,"w");
	fprintf(savehospede,"%d\n",codigo);
	fprintf(savehospede,"%s\n",alterarhospede.nome);		
	fprintf(savehospede,"%s\n",alterarhospede.email);
	fprintf(savehospede,"%s\n",alterarhospede.sexo);
	fprintf(savehospede,"%s\n",alterarhospede.estadocivil);
	fprintf(savehospede,"%s\n",alterarhospede.rua);
	fprintf(savehospede,"%s\n",alterarhospede.numero);
	fprintf(savehospede,"%s\n",alterarhospede.bairro);
	fprintf(savehospede,"%s\n",alterarhospede.cidade);
	fprintf(savehospede,"%s\n",alterarhospede.UF);
	fprintf(savehospede,"%s\n",alterarhospede.cpf);
	fprintf(savehospede,"%s\n",alterarhospede.telefone);
	fprintf(savehospede,"%s\n",alterarhospede.datanascimento);
	fclose(savehospede);
	
	alterardadoshospedes(codigo);
}

int exibirtodos(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	
	int i,j;
	
	FILE *hosp;
	
	int *codigo_hospede;
	codigo_hospede = malloc(numero_de_hospedes*sizeof(int));
	char txt[5] = ".txt";
	char numerodohospede[3];
	char newhospede[23];
	
	char *nome_hospede[numero_de_hospedes];
	int exibir = 1;

	for(i=0;i<numero_de_hospedes;i++){
			
		nome_hospede[i] = malloc(40*sizeof(char));
		sprintf(numerodohospede, "%i", i+1);//converte interio em string
		strcpy (newhospede, "dados\\hospede");//define valor a string
		
		strcat (newhospede, numerodohospede); // junta duas strings
		strcat (newhospede, txt); // junta duas strings
		
		hosp = fopen(newhospede,"r");
		if(hosp!=NULL){
			fscanf(hosp,"%i\n",&codigo_hospede[i]);
			fscanf(hosp,"\n%[^\n]s",nome_hospede[i]);
			fclose(hosp);
			printf("Codigo do Hospede: %i\n",codigo_hospede[i]);
			printf("Nome Do Hospede: %s\n",nome_hospede[i]);	
		}
		//free(codigo_hospede[i]);
		//free(nome_hospede[i]);
	}
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
}

int deletarhospede(int codigo){	

		#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
		
		char txt[5] = ".txt";
		char numerodohospede[3];
		char openhospede[23]="dados\\hospede";
				
		sprintf(numerodohospede, "%i", codigo);//converte interio em string		
		strcat (openhospede, numerodohospede); // junta duas strings
		strcat (openhospede, txt); // junta duas strings	
		
		remove(openhospede); //Deleta o arquivo.txt
		
		printf("=====================================================================\n");
		printf("=============== Hospede excluido com sucesso!========================\n");
		printf("=====================================================================\n");
		
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		main();		
}

int inserirhospede(){

	struct HOSPEDE novohospede;
	
	char txt[5] = ".txt";

	char numerodehospedes[3];
	numero_de_hospedes = numero_de_hospedes+1;
	sprintf(numerodehospedes, "%i", numero_de_hospedes);//converte interio em string
	
	char newhospede[23] = "dados\\hospede";
	
	strcat (newhospede, numerodehospedes); // junta duas strings
	strcat (newhospede, txt); // junta duas strings

	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("========== Insira os Dados do novo Hospede do Hotel==================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	FILE *hosp;
	
	hosp = fopen(newhospede,"w");
	
	novohospede.codigohospede = numero_de_hospedes;
	printf("Codigo: %d",novohospede.codigohospede);
	fprintf(hosp,"%d",novohospede.codigohospede);
	
	fflush(stdin); // limpa o buffer do teclado
	printf("\nNome: ");
	gets(novohospede.nome);
	fprintf(hosp,"\n%s",novohospede.nome);
	
	printf("\nE-mail: ");
	gets(novohospede.email);
	fprintf(hosp,"\n%s",novohospede.email);
	
	printf("\nSexo(Masculino, Feminino, Outros): ");
	gets(novohospede.sexo);
	fprintf(hosp,"\n%s",novohospede.sexo);
	
	printf("\nEstado Civil: ");
	gets(novohospede.estadocivil);
	fprintf(hosp,"\n%s",novohospede.estadocivil);
	
	printf("\nEndereco:\n");
	
	printf("\nRua: ");
	gets(novohospede.rua);
	fprintf(hosp,"\n%s",novohospede.rua);
	
	printf("\nNumero: ");
	gets(novohospede.numero);
	fprintf(hosp,"\n%s",novohospede.numero);
	
	printf("\nBairro: ");
	gets(novohospede.bairro);
	fprintf(hosp,"\n%s",novohospede.bairro);
	
	printf("\nCidade: ");
	gets(novohospede.cidade);
	fprintf(hosp,"\n%s",novohospede.cidade);
	
	printf("\nUF: ");
	gets(novohospede.UF);
	fprintf(hosp,"\n%s",novohospede.UF);
	
	printf("\nCPF: ");
	gets(novohospede.cpf);
	fprintf(hosp,"\n%s",novohospede.cpf);
	
	printf("\nTelefone: (xxzyxxxxzzzz)");
	gets(novohospede.telefone);
	fprintf(hosp,"\n%s",novohospede.telefone);
	
	printf("\nData de Nascimento: (xx/yy/zzzz)");
	gets(novohospede.datanascimento);
	fprintf(hosp,"\n%s",novohospede.datanascimento);
	
	fclose(hosp);
	
	FILE *numhospedes;
	numhospedes = fopen("dados\\Nhospedes.txt","w");
	fprintf(numhospedes,"%d",numero_de_hospedes);
	fclose(numhospedes);
	
	dadosdoshospedes();
}
///////////////////////////////////////////////////////////
int dadosdeacomodacoes(){ /* 3*/ //TEM Q TERMINAR
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==== 1. Exibir ou Alterar Dados de Acomodacoes ======================\n");
	printf("==== 2. Inserir Nova Acomodacao =====================================\n");
	printf("==== 3. Exibir ou Alterar Dados das Categorias de Acomodacoes =======\n");
	printf("==== 4. Inserir Nova Categoria de Acomodacoes =======================\n");
	printf("==== 5. Voltar ======================================================\n");
	printf("=====================================================================\n");
	
	int categoriadesejada;
	categoriadesejada = 0;
	scanf("%d", &categoriadesejada);
	
	switch (categoriadesejada){
	case 1:
		pesquisaracomodacao();
	break;
	case 2:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		inseriracomodacoes();
	break;
	case 3:
		
	break;
	case 4:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		inseriracategoriacomodacoes();
	break;
	case 5:
		modulodecadastrosegestaodedados();
	break;
	default:
		dadosdeacomodacoes();
	}
	main();
}

int	pesquisaracomodacao(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int op;
	
	printf("=====================================================================\n");
	printf("======================= Pesquisar Acomodacao ========================\n");
	printf("=====================================================================\n");
	printf("====== 1. Pesquisar Acomodacao por codigo: ==========================\n");
	printf("====== 2. Exibir Nome e Codigo de Todos As Acomodacoes Cadastradas: =\n");
	printf("====== 3. Voltar ====================================================\n");
	printf("====== 0. Sair ======================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op);
	
	switch(op){
	case 1:
		pesquisar_acomodacoes();
	break;
	case 2:
		exibirtodasacomodacoes();
	break;
	case 3:
		dadosdeacomodacoes();
	break;
	case 0:
		exit(0);
	break;
	default:
		pesquisaracomodacao();
	}
	main();
}

int pesquisar_acomodacoes(){
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i;
	
	FILE *acomod;
	
	int codigo_pesquisado;
	char txt[5] = ".txt";
	char numerodaacomod[3];
	char openacomod[23]="dados\\acomodacao";
	
	printf("=====================================================================\n");
	printf("====================== Pesquisar por Codigo =========================\n");
	printf("=====================================================================\n");
	printf("====== Insira o codigo da acomodacao que deseja acessar: ============\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&codigo_pesquisado);
		
		sprintf(numerodaacomod, "%i", codigo_pesquisado);//converte interio em string		
		strcat (openacomod, numerodaacomod); // junta duas strings
		strcat (openacomod, txt); // junta duas strings
		
		acomod = fopen(openacomod,"r");
	
	if (acomod == NULL){
		printf("Acomodacao com codigo %d Inexistente, Tente Novamente\n", codigo_pesquisado);
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();

		fclose(acomod);
	}
	else{
		fclose(acomod);
		opcoes_acomodacoes(codigo_pesquisado);
		
	}
	pesquisar_acomodacoes();
	
}

int opcoes_acomodacoes(int codigo){
	
	int op;
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("====== 1. Exibir e Alterar Dados ====================================\n");
	printf("=======2. Deletar Acomodacao=========================================\n");
	printf("====== 3. Voltar ====================================================\n");
	printf("====== 0. Sair ======================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op);
	
	switch(op){
	case 1:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		alteraracomodacoes(codigo);
	break;
	case 2:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		deletar_acomodacoes(codigo);
	break;
	case 3:
		dadosdeacomodacoes();
	break;
	case 0:
		exit(0);
	break;
	default:
		opcoes_acomodacoes( codigo);
	}
	main();
}

int alteraracomodacoes(int codigo){
	
	struct ACOMODACOES alterar_acomodacao;
			
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i,opcao;
	FILE *acomod;
	char txt[5] = ".txt";
	char numerodaacomodacao[3];
	sprintf(numerodaacomodacao, "%i", codigo);//converte interio em string
	char newacomodacao[23] = "dados\\acomodacao";
	
	strcat (newacomodacao, numerodaacomodacao); // junta duas strings
	strcat (newacomodacao, txt); // junta duas strings
	
	acomod = fopen(newacomodacao,"r");
	
	fscanf(acomod,"%i\n",&codigo);
	fscanf(acomod,"\n%[^\n]s",alterar_acomodacao.descricao_acomodacao);
	fscanf(acomod,"\n%[^\n]s",alterar_acomodacao.facilidades);
	fscanf(acomod,"%i",&alterar_acomodacao.categoria );
	fclose(acomod);
	
	printf("O que deseja Alterar: \n");
	
	printf("1. Descrição da Acomodacao: %s\n",alterar_acomodacao.descricao_acomodacao);
	printf("2. Facilidades da Acomodacao: %s\n",alterar_acomodacao.facilidades);
	printf("3. Categoria de Acomodacao: %s\n",alterar_acomodacao.categoria);
	printf("4. Voltar\n");
	scanf("%d",opcao);
	switch(opcao){
		case 1:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterar_acomodacao.descricao_acomodacao);
		break;
		case 2:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterar_acomodacao.facilidades);
		break;
		case 3:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			scanf("%d",&alterar_acomodacao.categoria);
		break;
		case 4:
			dadosdeacomodacoes();
		break;
		default:
			alteraracomodacoes(codigo);
	}
	acomod = fopen(newacomodacao,"w");
	
	fprintf(acomod,"%i\n",codigo);
	fprintf(acomod,"%s\n",alterar_acomodacao.descricao_acomodacao);
	fprintf(acomod,"%s\n",alterar_acomodacao.facilidades);
	fprintf(acomod,"%i",alterar_acomodacao.categoria);
	fclose(acomod);
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	alteraracomodacoes(codigo);
}

int deletar_acomodacoes(int codigo){
	
		#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
		
		char txt[5] = ".txt";
		char numerodaacomod[3];
		char openacomod[23]="dados\\acomodacao";
				
		sprintf(numerodaacomod, "%i", codigo);//converte interio em string		
		strcat (openacomod, numerodaacomod); // junta duas strings
		strcat (openacomod, txt); // junta duas strings
				
		remove(openacomod); //Deleta o arquivo.txt
		printf("=====================================================================\n");
		printf("=============== Acomodacao excluida com sucesso!=====================\n");
		printf("=====================================================================\n");
		
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		
		dadosdeacomodacoes();
}

int exibirtodasacomodacoes(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//Limpa a tela
	int i;
	FILE *acomod; //Cria o arquivo
	char txt[5] = ".txt";
	char numerodaacomodacao[3];
	char acomodacao[23];
	
	int *codigo = malloc(numero_de_acomodacoes * sizeof(int));
	char *descricao[numero_de_acomodacoes];
	char *facilidades[numero_de_acomodacoes];
	int *tipo = malloc(numero_de_acomodacoes * sizeof(int));
	
	
	for(i=0; i<numero_de_acomodacoes; i++){
		descricao[i] = malloc(250 * sizeof(char));
		facilidades[i] = malloc(250 * sizeof(char));
	
		sprintf(numerodaacomodacao, "%i", i+1);//converte interio em string
		strcpy (acomodacao,"dados\\acomodacao"); //Define valor a string
		strcat (acomodacao, numerodaacomodacao);//Junta a string de caminho com o numero	
		strcat (acomodacao, txt);//junta a string de caminho+numero com o formato .txt
		
		acomod = fopen(acomodacao,"r");	
		if(acomod != NULL){
			fscanf(acomod,"%i\n",&codigo[i]);
			fscanf(acomod,"%[^\n]s",descricao[i]);
			fscanf(acomod,"\n%[^\n]s",facilidades[i]);
			fscanf(acomod,"%i\n",&tipo[i]);	
			
			printf("Codigo %d\n",codigo[i]);
			printf("Descricao %s\n",descricao[i]);
			printf("Facilidades %s\n",facilidades[i]);
			printf("Tipo %d\n\n", tipo[i]);
		}
		fclose(acomod);
	}
printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
}

int exibirtiposdeacomodacoes(){
	
	char txt[5] = ".txt";
	int i;
	
	FILE *tipoacomod;
	int *codtipoacomod = malloc(numero_de_tipo_acomodacoes*sizeof(int));
	float *ValorDiaria = malloc(numero_de_tipo_acomodacoes*sizeof(float));
	int *qtdHospedes = malloc(numero_de_tipo_acomodacoes*sizeof(int));
	char numtipacomodacao[3];
	char abriracomod[23];
	char *destipoacomod[numero_de_tipo_acomodacoes];
	
	for(i=0;i<numero_de_tipo_acomodacoes;i++){
		destipoacomod[i] = malloc(250*sizeof(char));
		
		sprintf(numtipacomodacao, "%i", i+1);//converte interio em string
		strcpy (abriracomod, "dados\\tacomodacao"); // Define o valor da string
		strcat (abriracomod, numtipacomodacao); // junta duas strings
		strcat (abriracomod, txt); // junta duas strings
		
		tipoacomod = fopen(abriracomod,"r");
		
		fflush(stdin); // limpa o buffer do teclado
		fscanf(tipoacomod,"%i\n",&codtipoacomod[i]);
		fscanf(tipoacomod,"\n%[^\n]s",destipoacomod[i]);
		fflush(stdin); // limpa o buffer do teclado
		fscanf(tipoacomod,"%f",&ValorDiaria[i]);
		fscanf(tipoacomod,"\n%i",&qtdHospedes[i]);
		fclose(tipoacomod);
		
		printf("Codigo da categoria: %d\n",codtipoacomod[i]);
		printf("Descricao da categoria: %s\n",destipoacomod[i]);
		printf("Valor da Diaria: %.2f\n",ValorDiaria[i]);
		printf("Quantidade de Pessoas: %d\n\n",qtdHospedes[i]);
		
	}
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
}

int inseriracomodacoes(){
	
	struct ACOMODACOES novaacomodacao;
	struct CATEGORIA_ACOMODACOES categorias;
	char txt[5] = ".txt";
	int repetir;
	FILE *acomod,*checktipo;
	
	
	char numerodaacomodacao[3];
	numero_de_acomodacoes = numero_de_acomodacoes+1;
	sprintf(numerodaacomodacao, "%i", numero_de_acomodacoes);//converte interio em string
	char newacomodacao[23] = "dados\\acomodacao";
	
	strcat (newacomodacao, numerodaacomodacao); // junta duas strings
	strcat (newacomodacao, txt); // junta duas strings
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("============== Insira os Dados da nova Acomodação ===================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	
	acomod = fopen(newacomodacao,"w");
	
	novaacomodacao.codigoacomodacoes = numero_de_acomodacoes;
	printf("Codigo: %d",novaacomodacao.codigoacomodacoes);
	fprintf(acomod,"%d",novaacomodacao.codigoacomodacoes);
	
	fflush(stdin); // limpa o buffer do teclado
	printf("\nDigite a descrição da Acomodação:");
	gets(novaacomodacao.descricao_acomodacao);
	fprintf(acomod,"\n%s",novaacomodacao.descricao_acomodacao);
	
	printf("\nDigite as facilidades da Acomodação:");
	printf("\n(coisas que a acomodação possui. Ex.: televisão, arcondicionado,etc).");
	gets(novaacomodacao.facilidades);
	fprintf(acomod,"\n%s",novaacomodacao.facilidades);

	exibirtiposdeacomodacoes();
	char openacomodacao[23];
	printf("\nDigite o codigo da categoria da acomodacao:\n");
	do{
		repetir=0;
		scanf("%d",&novaacomodacao.categoria);
		strcpy (openacomodacao, "dados\\tacomodacao");
		sprintf(numerodaacomodacao, "%i", novaacomodacao.categoria);//converte interio em string
		strcat (openacomodacao, numerodaacomodacao); // junta duas strings
		strcat (openacomodacao, txt); // junta duas strings
		checktipo = fopen(openacomodacao,"r");
		if (checktipo == NULL){
			printf("Codigo %d Invalido, Tente Novamente\n", novaacomodacao.categoria);
			repetir=1;
		}
		fclose(checktipo);
	}while(repetir==1);
	fprintf(acomod,"\n%d",novaacomodacao.categoria);
	
	fclose(acomod);
	
	FILE *num_acomodacoes;
	num_acomodacoes = fopen("dados\\Nacomodacoes.txt","w");
	fprintf(num_acomodacoes,"%i",numero_de_acomodacoes);
	fclose(num_acomodacoes);
printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	dadosdeacomodacoes();
}

int inseriracategoriacomodacoes(){
	struct CATEGORIA_ACOMODACOES novacategoriaacomodacao;
	
	char txt[5] = ".txt";

	char numerodacategoriaacomodacao[3];
	numero_de_tipo_acomodacoes = numero_de_tipo_acomodacoes+1;
	sprintf(numerodacategoriaacomodacao, "%i", numero_de_tipo_acomodacoes);//converte interio em string
	char newcat_acomodacao[23] = "dados\\tacomodacao";
	
	strcat (newcat_acomodacao, numerodacategoriaacomodacao); // junta duas strings
	strcat (newcat_acomodacao, txt); // junta duas strings
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=========== Insira os Dados da nova Categoria de Acomodação =========\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	FILE *acomod;
	acomod = fopen(newcat_acomodacao,"w");

	novacategoriaacomodacao.codigo_cat_acomodacoes = numero_de_tipo_acomodacoes;
	printf("Codigo da categoria: %d",novacategoriaacomodacao.codigo_cat_acomodacoes);
	fprintf(acomod,"%d",novacategoriaacomodacao.codigo_cat_acomodacoes);
	
	fflush(stdin); // limpa o buffer do teclado
	printf("\nDigite a descrição da Acomodacao:");
	printf("\nEconomica,standard,luxo,presidencial,etc.");
	gets(novacategoriaacomodacao.descricao);
	fprintf(acomod,"\n%s",novacategoriaacomodacao.descricao);
	
	printf("\nDigite o valor da diaria:");
	scanf("%f",&novacategoriaacomodacao.valordiaria);
	fprintf(acomod,"\n%f",novacategoriaacomodacao.valordiaria);
	
	printf("\nDigite a quantidade de hospedes que a acomodacao suporta:");
	scanf("%d",&novacategoriaacomodacao.qtd_pessoas);
	fprintf(acomod,"\n%d",novacategoriaacomodacao.qtd_pessoas);
	fclose(acomod);
	
	FILE *num_cat_acomodacoes;
	num_cat_acomodacoes = fopen("dados\\Ntipoacomodacoes.txt","w");
	fprintf(num_cat_acomodacoes,"%i",numero_de_tipo_acomodacoes);
	fclose(num_cat_acomodacoes);
	
	dadosdeacomodacoes();
}
///////////////////////////////////////////////////////////
int dadosdeprodutos(){/* 4*/
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==== 1. Exibir ou Alterar Dados dos Produtos ========================\n");
	printf("==== 2. Inserir Novo Produto ========================================\n");
	printf("==== 3. Voltar ======================================================\n");
	printf("=====================================================================\n");
	
	int categoriadesejada;
	scanf("%d", &categoriadesejada);
	
	switch (categoriadesejada){
	case 1:
		pesquisarproduto();
	break;
	case 2:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		novoproduto();
	break;
	case 3:
		modulodecadastrosegestaodedados();
	break;
	default:
		dadosdeprodutos();
	}
	main();
}

int pesquisarproduto(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int op;
	
	printf("=====================================================================\n");
	printf("======================= Pesquisar Produtos ==========================\n");
	printf("=====================================================================\n");
	printf("====== 1. Pesquisar Produto por codigo: =============================\n");
	printf("====== 2. Exibir Nome e Codigo de Todos Os Produtos Cadastrados: ====\n");
	printf("====== 3. Voltar ====================================================\n");
	printf("====== 0. Sair ======================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op);
	
	switch(op){
	case 1:
		pesquisarcodigoproduto();
	break;
	case 2:
		exibirtodosprodutos();
	break;
	case 3:
		dadosdeprodutos();
	break;
	case 0:
		exit(0);
	break;
	default:
		pesquisarproduto();
	}
	main();
}

int pesquisarcodigoproduto(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i;
	
	FILE *produto;

	int codigo_pesquisado;
	
	char txt[5] = ".txt";
	char numerodoproduto[3];
	char openproduto[23] = "dados\\produto";
	
	printf("=====================================================================\n");
	printf("====================== Pesquisar por Codigo =========================\n");
	printf("=====================================================================\n");
	printf("====== Insira o codigo do Produto que deseja acessar: ===============\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&codigo_pesquisado);

		
	sprintf(numerodoproduto, "%i", codigo_pesquisado);//converte interio em string
	
	strcat (openproduto, numerodoproduto); // junta duas strings
	strcat (openproduto, txt); // junta duas strings
	
	produto = fopen(openproduto,"r");
	
	if (produto == NULL){
		printf("Produto com codigo %d Inexistente, Tente Novamente\n", codigo_pesquisado);
		fclose(produto);
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		
	}
	else{
		fclose(produto);
		opcaoproduto(codigo_pesquisado);
	}
	pesquisarcodigoproduto();
	main();
}

int opcaoproduto (int codigo){
	
	int op;
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("====== 1. Exibir e Alterar Dados ====================================\n");
	printf("=======2. Deletar Produto ===========================================\n");
	printf("====== 3. Voltar ====================================================\n");
	printf("====== 0. Sair ======================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op);
	
	switch(op){
	case 1:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		alterardadosprodutos(codigo);
	break;
	case 2:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		deletar_produto(codigo);
	break;
	case 3:
		dadosdeprodutos();
	break;
	case 0:
		exit(0);
	break;
	default:
		opcaoproduto(codigo);
	}
	main();
}

int alterardadosprodutos(int codigo){
	struct PRODUTOSDISPONIVEISPARACONSUMO alterarproduto;
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i;
	FILE *produto;
	char openproduto[23] = "dados\\produto";
	char txt[5] = ".txt";
	char codigoproduto[3];
	sprintf(codigoproduto, "%i", codigo);//converte interio em string
	
	strcat (openproduto, codigoproduto); // junta duas strings
	strcat (openproduto, txt); // junta duas strings
	
	produto = fopen(openproduto,"r");
	
	fscanf(produto,"%i\n",&codigo);
	fscanf(produto,"\n%[^\n]s",alterarproduto.descricao_produto);
	fscanf(produto,"%i\n",&alterarproduto.estoque);
	fscanf(produto,"%i\n",&alterarproduto.estoque_minimo);
	fscanf(produto,"%f\n",&alterarproduto.preco_custo);
	fscanf(produto,"%f",&alterarproduto.preco_venda);

	fclose(produto);
	#ifdef WIN32
			system("CLS");
		#else
				system("clear");
		#endif
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==================== O Que Deseja Alterar? ==========================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==== Codigo: %i\n",codigo);
	printf("==== 1. Descricao do Produto: %s\n",alterarproduto.descricao_produto);
	printf("==== 2. Estoque: %d\n",alterarproduto.estoque);
	printf("==== 3. Estoque Minimo: %d\n",alterarproduto.estoque_minimo);
	printf("==== 4. Preco de Custo: %f\n",alterarproduto.preco_custo);
	printf("==== 5. Preco de Venda: %f\n",alterarproduto.preco_venda);

	printf("==== 6. Alterar Todos ==============================================\n");
	printf("==== 7. Voltar =====================================================\n");
	printf("==== 0. Sair ========================================================\n");
	int opcaoalterar =0;
	scanf("%d", &opcaoalterar);

	switch(opcaoalterar){

		case 0:
			exit(0);
		break;
		case 1:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarproduto.descricao_produto);
		break;
		
		case 2:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			scanf("%d",&alterarproduto.estoque);
		break;
		
		case 3:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			scanf("%d",&alterarproduto.estoque_minimo);
		break;
		
		case 4:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			scanf("%f",&alterarproduto.preco_custo);
		break;
		
		case 5:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			scanf("%f",&alterarproduto.preco_venda);
		break;
		
		case 6:
			printf("Insira a Nova Descricao do Produto:");
			gets(alterarproduto.descricao_produto);
		
			printf("Insira o novo Estoque do produto:");
			scanf("%d",&alterarproduto.estoque);
		
			printf("Insira o novo Estoque minimo do produto:");
			scanf("%d",&alterarproduto.estoque_minimo);
		
			printf("Insira o novo preco de custo:");
			scanf("%f",&alterarproduto.preco_custo);
	
			printf("Insira o novo preco de venda:");
			scanf("%f",&alterarproduto.preco_venda);
		break;
		
		case 7:
			pesquisarproduto();
		break;
		default:
			alterardadosprodutos(codigo);

	}
	
	produto = fopen(openproduto,"w");
	
	fprintf(produto,"%d\n",codigo);
	fprintf(produto,"%s\n",alterarproduto.descricao_produto);
	fprintf(produto,"%d\n",alterarproduto.estoque);
	fprintf(produto,"%d\n",alterarproduto.estoque_minimo);
	fprintf(produto,"%f\n",alterarproduto.preco_custo);
	fprintf(produto,"%f",alterarproduto.preco_venda);
	
	fclose(produto);
	
	alterardadosprodutos(codigo);
	main();
}

int exibirtodosprodutos(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i;
	FILE *prod;

	int *codigo_produto = malloc(numero_de_produtos*sizeof(int));

	char txt[5] = ".txt";
	char numerodeprodutos[3];
	char openproduto[23];
	
	char *descricao_produto[numero_de_produtos];
	
	int *estoque = malloc(numero_de_produtos*sizeof(int)),*estoque_minimo= malloc(numero_de_produtos*sizeof(int));
	float *preco_custo= malloc(numero_de_produtos*sizeof(float)),*preco_venda= malloc(numero_de_produtos*sizeof(float));
	printf("=====================================================================\n");
	for(i=0;i<numero_de_produtos;i++){
		descricao_produto[i] = malloc(260*sizeof(char));
		sprintf(numerodeprodutos, "%i", i+1);//converte interio em string
		strcpy (openproduto, "dados\\produto");//define valor a string
		
		strcat (openproduto, numerodeprodutos); // junta duas strings
		strcat (openproduto, txt); // junta duas strings
		
		prod = fopen(openproduto,"r");
		if(prod != NULL){
			fscanf(prod,"%i\n",&codigo_produto[i]);
			fscanf(prod,"\n%[^\n]s",descricao_produto[i]);
			fscanf(prod,"%i\n",&estoque[i]);
			fscanf(prod,"%i\n",&estoque_minimo[i]);
			fscanf(prod,"%f\n",&preco_custo[i]);
			fscanf(prod,"%f\n",&preco_venda[i]);
			
			printf("Codigo do Produto: %i\n",codigo_produto[i]);
			printf("Descricao Do Produto: %s\n",descricao_produto[i]);
			printf("Estoque do Produto: %i\n",estoque[i]);
			printf("Preco do Produto: %.2f\n",preco_venda[i]);
			printf("=====================================================================\n");
		}
		fclose(prod);
	}
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
}

int deletar_produto(int codigo){
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	
	char txt[5] = ".txt";
	char numerodoproduto[3];
	char openproduto[23]="dados\\produto";
			
	sprintf(numerodoproduto, "%i", codigo);//converte interio em string		
	strcat (openproduto, numerodoproduto); // junta duas strings
	strcat (openproduto, txt); // junta duas strings
	
	remove(openproduto); //Deleta o arquivo.txt
	printf("=====================================================================\n");
	printf("================= Produto excluido com sucesso!======================\n");
	printf("=====================================================================\n");
	
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	
	dadosdeprodutos();
	
}

int novoproduto(){
	struct PRODUTOSDISPONIVEISPARACONSUMO novoproduto;
	
	char txt[5] = ".txt";

	char numerodeprodutos[3];
	numero_de_produtos = numero_de_produtos+1;
	sprintf(numerodeprodutos, "%i", numero_de_produtos);//converte interio em string
	
	char newproduto[23] = "dados\\produto";
	
	strcat (newproduto, numerodeprodutos); // junta duas strings
	strcat (newproduto, txt); // junta duas strings

	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("========== Insira os Dados do novo Produto do Hotel==================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	FILE *produto;
	
	produto = fopen(newproduto,"w");
	
	novoproduto.codigo_produto = numero_de_produtos;
	printf("Codigo: %d\n",novoproduto.codigo_produto);
	fprintf(produto,"%d\n",novoproduto.codigo_produto);
	fflush(stdin); // limpa o buffer do teclado
	printf("Descricao do produto:(Descricao Detalhada)");
	gets(novoproduto.descricao_produto);
	fprintf(produto,"%s\n",novoproduto.descricao_produto);
	
	printf("Estoque: 0\n");
	novoproduto.estoque=0;
	fprintf(produto,"%d\n",novoproduto.estoque);
	
	printf("Estoque Minimo:");
	scanf("%d",&novoproduto.estoque_minimo);
	fprintf(produto,"%d\n",novoproduto.estoque_minimo);
	
	printf("Preco de Custo:");
	scanf("%f",&novoproduto.preco_custo);
	fprintf(produto,"%f\n",novoproduto.preco_custo);
	
	novoproduto.preco_venda = 0;
	printf("Preco de Venda: %.2f\n",novoproduto.preco_venda);
	fprintf(produto,"%f\n",novoproduto.preco_venda);
	
	fclose(produto);
	
	FILE *numprodutos;
	numprodutos = fopen("dados\\Nprodutos.txt","w");
	fprintf(numprodutos,"%d",numero_de_produtos);
	fclose(numprodutos);
	
printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	
	dadosdeprodutos();
}
///////////////////////////////////////////////////////////
int dadosdefornecedores(){/* 5*/
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==== 1. Exibir ou Alterar Dados dos Fornecedores ====================\n");
	printf("==== 2. Inserir Novo Fornecedor =====================================\n");
	printf("==== 3. Voltar ======================================================\n");
	printf("=====================================================================\n");
	
	int categoriadesejada;
	scanf("%d", &categoriadesejada);
	
	switch (categoriadesejada){
	case 1:
		
		pesquisarfornecedor();
	break;
	case 2:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		novofornecedor();
	break;
	case 3:
		modulodecadastrosegestaodedados();
	break;
	default:
		dadosdefornecedores();
	}
	main();
}

int pesquisarfornecedor(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int op;
	
	printf("=====================================================================\n");
	printf("======================= Pesquisar Fornecedores ======================\n");
	printf("=====================================================================\n");
	printf("====== 1. Pesquisar Fornecedore por codigo: =========================\n");
	printf("====== 2. Exibir Nome e Codigo de Todo Fornecedor Cadastrado: =======\n");
	printf("====== 3. Voltar ====================================================\n");
	printf("====== 0. Sair ======================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op);
	
	switch(op){
	case 1:
		pesquisarcodigofornecedor();
	break;
	case 2:
		exibirtodosfornecedores();
	break;
	case 3:
		dadosdefornecedores();
	break;
	case 0:
		exit(0);
	break;
	default:
		pesquisarfornecedor();
	}
}

int pesquisarcodigofornecedor(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i;
	
	FILE *fornecedor;

	int codigo_pesquisado;
	
	char txt[5] = ".txt";
	char numerodofornecedor[3];
	char openfornecedor[23] = "dados\\fornecedor";
	
	printf("=====================================================================\n");
	printf("====================== Pesquisar por Codigo =========================\n");
	printf("=====================================================================\n");
	printf("====== Insira o codigo do Fornecedor que deseja acessar: ============\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&codigo_pesquisado);

		
	sprintf(numerodofornecedor, "%i", codigo_pesquisado);//converte interio em string
	
	strcat (openfornecedor, numerodofornecedor); // junta duas strings
	strcat (openfornecedor, txt); // junta duas strings
	
	fornecedor = fopen(openfornecedor,"r");
	
	if (fornecedor == NULL){
		printf("Fornecedor com codigo %d Inexistente, Tente Novamente\n", codigo_pesquisado);
		fclose(fornecedor);
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}
	else{
		fclose(fornecedor);
		opcoes_fornecedor(codigo_pesquisado);
	}
	pesquisarcodigofornecedor();
}

int opcoes_fornecedor(int codigo){ 
	int op;
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("====== 1. Exibir e Alterar Dados ====================================\n");
	printf("=======2. Deletar Fornecedor ========================================\n");
	printf("====== 3. Voltar ====================================================\n");
	printf("====== 0. Sair ======================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op);
	
	switch(op){
	case 1:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		alterardadosfornecedor(codigo);
	break;
	case 2:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		deletar_fornecedor(codigo);
	break;
	case 3:
		dadosdeacomodacoes();
	break;
	case 0:
		exit(0);
	break;
	default:
		opcoes_fornecedor(codigo);
	}
	main();
}

int alterardadosfornecedor(int codigo){
	struct FORNECEDORES alterarfornecedor;
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i;
	FILE *fornecedor;
	
	char openfornecedor[23] = "dados\\fornecedor";
	char txt[5] = ".txt";
	char codigofornecedor[3];
	sprintf(codigofornecedor, "%i", codigo);//converte interio em string
	
	strcat (openfornecedor, codigofornecedor); // junta duas strings
	strcat (openfornecedor, txt); // junta duas strings
	
	fornecedor = fopen(openfornecedor,"r");
	
	fscanf(fornecedor,"%i\n",&codigo);
	
	fscanf(fornecedor,"\n%[^\n]s",alterarfornecedor.nomefantasia);
	fscanf(fornecedor,"\n%[^\n]s",alterarfornecedor.razaosocial);
	fscanf(fornecedor,"\n%[^\n]s",alterarfornecedor.email);
	fscanf(fornecedor,"\n%[^\n]s",alterarfornecedor.inscricaoestadual);
	fscanf(fornecedor,"\n%[^\n]s",alterarfornecedor.cnpj);
	fscanf(fornecedor,"\n%[^\n]s",alterarfornecedor.rua);
	fscanf(fornecedor,"\n%[^\n]s",alterarfornecedor.numero);
	fscanf(fornecedor,"\n%[^\n]s",alterarfornecedor.bairro);
	fscanf(fornecedor,"\n%[^\n]s",alterarfornecedor.cidade);
	fscanf(fornecedor,"\n%[^\n]s",alterarfornecedor.UF);
	fscanf(fornecedor,"\n%[^\n]s",alterarfornecedor.telefone);

	fclose(fornecedor);

	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==================== O Que Deseja Alterar? ==========================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("==== Codigo: %i\n",codigo);
	printf("==== 1. Nome Fantazia: %s\n",alterarfornecedor.nomefantasia);
	printf("==== 2. Razao Social: %s\n",alterarfornecedor.razaosocial);
	printf("==== 3. E-mail: %s\n",alterarfornecedor.email);
	printf("==== 4. Inscricao Estadual: %s\n",alterarfornecedor.inscricaoestadual);
	printf("==== 5. CNPJ: %s\n",alterarfornecedor.cnpj);
	printf("==== Endereco\n");
	printf("========= 6. Rua: %s\n",alterarfornecedor.rua);
	printf("========= 7. Numero: %s\n",alterarfornecedor.numero);
	printf("========= 8. Bairro: %s\n",alterarfornecedor.bairro);
	printf("========= 9. Cidade: %s\n",alterarfornecedor.cidade);
	printf("========= 10. UF: %s\n",alterarfornecedor.UF);
	printf("==== 11. Telefone: %s\n",alterarfornecedor.telefone);
	printf("==== 12. Alterar Todos ==============================================\n");
	printf("==== 13. Voltar =====================================================\n");
	printf("==== 0. Sair ========================================================\n");
	int opcaoalterar;
	scanf("%d",&opcaoalterar);

	switch(opcaoalterar){

		case 0:
			exit(0);
		break;
		case 1:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarfornecedor.nomefantasia);
		break;
		case 2:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarfornecedor.razaosocial);
		break;
		
		case 3:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarfornecedor.email);
		break;
		
		case 4:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarfornecedor.inscricaoestadual);
		break;
		
		case 5:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarfornecedor.cnpj);
		break;
		
		case 6:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarfornecedor.rua);
		break;
		
		case 7:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarfornecedor.numero);
		break;
		
		case 8:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarfornecedor.bairro);
		break;
		
		case 9:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarfornecedor.cidade);
		break;
		
		case 10:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarfornecedor.UF);
		break;

		
		case 11:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo dado:");
			gets(alterarfornecedor.telefone);
		break;
		
		case 12:
			
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo Nome Fantasia:");
			gets(alterarfornecedor.nomefantasia);

			printf("Insira a nova Razao Social:");
			gets(alterarfornecedor.razaosocial);
	
			printf("Insira o novo E-mail:");
			gets(alterarfornecedor.email);
	
			printf("Insira a nova Inscricao Estadual:");
			gets(alterarfornecedor.inscricaoestadual);

			printf("Insira o novo CNPJ:");
			gets(alterarfornecedor.cnpj);

			printf("Insira a nova Rua:");
			gets(alterarfornecedor.rua);

			printf("Insira o novo Numero:");
			gets(alterarfornecedor.numero);

			printf("Insira o novo Bairro:");
			gets(alterarfornecedor.bairro);

			printf("Insira a nova Cidade:");
			gets(alterarfornecedor.cidade);

			printf("Insira o novo UF:");
			gets(alterarfornecedor.UF);

			printf("Insira o novo Telefone:");
			gets(alterarfornecedor.telefone);
		break;
		
		case 13:
			pesquisarfornecedor();
		break;
		default:
			alterardadosfornecedor(codigo);
	}
	
	fornecedor = fopen(openfornecedor,"w");
	
	fprintf(fornecedor,"%d\n",codigo);
	fprintf(fornecedor,"%s\n",alterarfornecedor.nomefantasia);
	fprintf(fornecedor,"%s\n",alterarfornecedor.razaosocial);
	fprintf(fornecedor,"%s\n",alterarfornecedor.email);
	fprintf(fornecedor,"%s\n",alterarfornecedor.inscricaoestadual);
	fprintf(fornecedor,"%s\n",alterarfornecedor.cnpj);
	fprintf(fornecedor,"%s\n",alterarfornecedor.rua);
	fprintf(fornecedor,"%s\n",alterarfornecedor.numero);
	fprintf(fornecedor,"%s\n",alterarfornecedor.bairro);
	fprintf(fornecedor,"%s\n",alterarfornecedor.cidade);
	fprintf(fornecedor,"%s\n",alterarfornecedor.UF);
	fprintf(fornecedor,"%s\n",alterarfornecedor.telefone);
	
	fclose(fornecedor);
	
	alterardadosfornecedor(codigo);
}

int exibirtodosfornecedores(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i;
	FILE *forn;

	int *codigo_fornecedor;
	codigo_fornecedor = malloc(numero_de_fornecedores*sizeof(int));

	char txt[5] = ".txt";
	char numerodofornecedor[3];
	char openfornecedor[23];
	
	char *nome_fornecedor[numero_de_fornecedores];
	
	for(i=0;i<numero_de_fornecedores;i++){
		
		nome_fornecedor[i] = malloc(40*sizeof(char));
		sprintf(numerodofornecedor, "%i", i+1);//converte interio em string
		strcpy (openfornecedor, "dados\\fornecedor");//define valor a string
		
		strcat (openfornecedor, numerodofornecedor); // junta duas strings
		strcat (openfornecedor, txt); // junta duas strings
		
		forn = fopen(openfornecedor,"r");
		if (forn != NULL){
			fscanf(forn,"%i\n",&codigo_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",nome_fornecedor[i]);
			
			printf("Codigo do Fornecedor: %i\n",codigo_fornecedor[i]);
			printf("Nome Do Fornecedor: %s\n",nome_fornecedor[i]);
			printf("=====================================================================\n");
		}
		fclose(forn);
	}
	free(codigo_fornecedor);
	for(i=0;i<numero_de_fornecedores;i++){
		free(nome_fornecedor[i]);
	}	
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
}

int deletar_fornecedor(int codigo){
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
	#endif//limpa a tela
	
	char txt[5] = ".txt";
	char numerodofornecedor[3];
	char openfornecedor[23]="dados\\fornecedor";
			
	sprintf(numerodofornecedor, "%i", codigo);//converte interio em string		
	strcat (openfornecedor, numerodofornecedor); // junta duas strings
	strcat (openfornecedor, txt); // junta duas strings
	
	remove(openfornecedor); //Deleta o arquivo.txt
	printf("=====================================================================\n");
	printf("============== Fornecedor excluido com sucesso!======================\n");
	printf("=====================================================================\n");
	
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	dadosdefornecedores();
}

int novofornecedor(){
	struct FORNECEDORES novofornecedor;
	
	char txt[5] = ".txt";

	char numerodefornecedores[3];
	numero_de_fornecedores = numero_de_fornecedores+1;
	sprintf(numerodefornecedores, "%i", numero_de_fornecedores);//converte interio em string
	
	char newfornecedor[23] = "dados\\fornecedor";
	
	strcat (newfornecedor, numerodefornecedores); // junta duas strings
	strcat (newfornecedor, txt); // junta duas strings

	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("========== Insira os Dados do novo Fornecedor do Hotel ==============\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	FILE *forn;
	
	forn = fopen(newfornecedor,"w");
	
	novofornecedor.codigo_fornecedor = numero_de_fornecedores;
	printf("Codigo do Fornecedor: %d",novofornecedor.codigo_fornecedor);
	fprintf(forn,"%d",novofornecedor.codigo_fornecedor);
	
	fflush(stdin); // limpa o buffer do teclado
	printf("\nNome Fantazia: ");
	gets(novofornecedor.nomefantasia);
	fprintf(forn,"\n%s",novofornecedor.nomefantasia);
	
	printf("\nRazao Social: ");
	gets(novofornecedor.razaosocial);
	fprintf(forn,"\n%s",novofornecedor.razaosocial);
	
	printf("\nE-mail: ");
	gets(novofornecedor.email);
	fprintf(forn,"\n%s",novofornecedor.email);
	
	printf("\nInscricao Estadual: ");
	gets(novofornecedor.inscricaoestadual);
	fprintf(forn,"\n%s",novofornecedor.inscricaoestadual);
	
	printf("\nCNPJ: ");
	gets(novofornecedor.cnpj);
	fprintf(forn,"\n%s",novofornecedor.cnpj);
	
	printf("\nEndereco:\n");
	
	printf("\nRua: ");
	gets(novofornecedor.rua);
	fprintf(forn,"\n%s",novofornecedor.rua);
	
	printf("\nNumero: ");
	gets(novofornecedor.numero);
	fprintf(forn,"\n%s",novofornecedor.numero);
	
	printf("\nBairro: ");
	gets(novofornecedor.bairro);
	fprintf(forn,"\n%s",novofornecedor.bairro);
	
	printf("\nCidade: ");
	gets(novofornecedor.cidade);
	fprintf(forn,"\n%s",novofornecedor.cidade);
	
	printf("\nUF: ");
	gets(novofornecedor.UF);
	fprintf(forn,"\n%s",novofornecedor.UF);

	printf("\nTelefone: (xxzyxxxxzzzz)");
	gets(novofornecedor.telefone);
	fprintf(forn,"\n%s",novofornecedor.telefone);
	
	fclose(forn);
	
	FILE *numfornecedores;
	numfornecedores = fopen("dados\\Nfornecedores.txt","w");
	fprintf(numfornecedores,"%d",numero_de_fornecedores);
	fclose(numfornecedores);
	
	dadosdefornecedores();
}
//////////////////////////////////////////////////////////

int novooperador(){
	struct OPERADORESDOSISTEMA novo;
	int repetir;
	FILE *operador;
	
	
	char txt[5] = ".txt";
	char numerodooperador[3];
	num_operadores = num_operadores+1;
	sprintf(numerodooperador, "%i", num_operadores);//converte interio em string
	
	char novooperador[23] = "dados\\user";
	
	strcat (novooperador, numerodooperador); // junta duas strings
	strcat (novooperador, txt); // junta duas strings
	
	printf("=====================================================================\n");
	printf("========== Insira os Dados do Novo Operador: ========================\n");
	printf("=====================================================================\n");
	printf("===== Nome:");
	fflush(stdin); // limpa o buffer do teclado
	scanf("%[^\n]s",novo.nome);
	printf("===== Usuario EX(Pedro), Sem Espacos:");
	fflush(stdin); // limpa o buffer do teclado
	scanf("%[^\n]s",novo.usuario);
	printf("===== Senha:");
	fflush(stdin); // limpa o buffer do teclado
	scanf("%[^\n]s",novo.senha);
	printf("===== Nivel de Permissão:");
	printf("\n1. Adiministrador\n2. Gerente\n3. Recepcionista\n4. Caixa\n");
	fflush(stdin); // limpa o buffer do teclado
	do{
		repetir =0;
		scanf("%d",&novo.nivel_permissao);
		if((novo.nivel_permissao <=0) || (novo.nivel_permissao >=5)){
			repetir =1;
			printf("!Nivel Inexistente!\nTente Novamente");
		}
	}while(repetir==1);
	printf("=====================================================================\n");
	operador = fopen(novooperador,"w");
	fprintf(operador,"%d\n",num_operadores);
	fprintf(operador,"%s\n",novo.nome);
	fprintf(operador,"%s\n",novo.usuario);
	fprintf(operador,"%s\n",novo.senha);
	fprintf(operador,"%d",novo.nivel_permissao);
	fclose(operador);
	
	FILE *operadores;
	operadores = fopen("dados\\Noperadores.txt","w");
	fprintf(operadores,"%i",num_operadores);
	fclose(operadores);
	printf("=================== Cadastro Realizado Com Sucesso ==================\n");
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	adm_sistema();
}

int alteraroperador(int cod_pesquisa){
	int repetir,op;
	char txt[5] = ".txt";
	char numerodooperador[3],novooperador[23];
	FILE *operador;
	int *codigo_operador = malloc(sizeof(int));
	int *permissao = malloc(sizeof(int));
	char *nome = malloc(40*sizeof(char));
	char *usuario = malloc(15*sizeof(char));
	char *senha = malloc(15*sizeof(char));
	
	sprintf(numerodooperador, "%i", cod_pesquisa);//converte interio em string
	strcpy (novooperador, "dados\\user");//define valor a string
	strcat (novooperador, numerodooperador); // junta duas strings
	strcat (novooperador, txt); // junta duas strings
	
	operador = fopen(novooperador,"r");
	
	fscanf(operador,"%d",&codigo_operador);
	fscanf(operador,"\n%[^\n]s",nome);
	fscanf(operador,"\n%[^\n]s",usuario);
	fscanf(operador,"\n%[^\n]s",senha);
	fscanf(operador,"%d",&permissao);
	fclose(operador);
	printf("1. Nome: %s\n",nome);
	printf("2. Nome de Usuario: %s\n",usuario);
	printf("3. Senha:\n");
	printf("4. Nivel de permissao: %d\n",permissao);
	printf("5. Alterar Todos\n");
	printf("6. Voltar\n");
	scanf("%d",&op);
	switch(op){
		case 1:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo Nome:");
			gets(nome);
		break;
		case 2:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo Nome de usuario:");
			gets(usuario);
		break;
		case 3:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira a nova senha:");
			gets(senha);
		break;
		case 4:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo nivel de permicao:");
			scanf("%d",&permissao);
		break;
		case 5:
			fflush(stdin); // limpa o buffer do teclado
			printf("Insira o novo Nome:");
			gets(nome);
			printf("Insira o novo Nome de usuario:");
			gets(usuario);
			printf("Insira a nova senha:");
			gets(senha);
			printf("Insira o novo nivel de permicao:");
			scanf("%d",&permissao);
		break;
		case 6:
			adm_sistema();
		break;
		default:
			alteraroperador(cod_pesquisa);
	}
	operador = fopen(novooperador,"w");
	
	fprintf(operador,"%d\n",codigo_operador);
	fprintf(operador,"%s\n",nome);
	fprintf(operador,"%s\n",usuario);
	fprintf(operador,"%s\n",senha);
	fprintf(operador,"%d",permissao);
	fclose(operador);
	printf("=====================================================================\n");
printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	alteraroperador(cod_pesquisa);
}

int pesquisa_operadores(){
	int cod_pesquisa,repetir,op;
	char txt[5] = ".txt";
	char numerodooperador[3],novooperador[23];
	FILE *operador;
	int *codigo_operador = malloc(sizeof(int));
	int *permissao = malloc(sizeof(int));
	char *nome = malloc(40*sizeof(char));
	char *usuario = malloc(15*sizeof(char));
	char *senha = malloc(15*sizeof(char));
	do{
		repetir=0;
		printf("=====================================================================\n");
		printf("===== Insira o codigo do operador pesquisado: ");
		scanf("%d",&cod_pesquisa);
		
		sprintf(numerodooperador, "%i", cod_pesquisa);//converte interio em string
		strcpy (novooperador, "dados\\user");//define valor a string
		strcat (novooperador, numerodooperador); // junta duas strings
		strcat (novooperador, txt); // junta duas strings
		
		operador = fopen(novooperador,"r");
		if(operador != NULL){
			fscanf(operador,"%d",&codigo_operador);
			fscanf(operador,"\n%[^\n]s",nome);
			fscanf(operador,"\n%[^\n]s",usuario);
			fscanf(operador,"\n%[^\n]s",senha);
			fscanf(operador,"%d",&permissao);
			
			printf("Codigo: %d\n",codigo_operador);
			printf("Nome: %s\n",nome);
			printf("Nome de Usuario: %s\n",usuario);
			printf("Nivel de permissao: %d\n",permissao);
		}else{
			printf("Codigo Invalido, Tente Novamente\n");
			repetir=1;
		}
		fclose(operador);
		printf("=====================================================================\n");
		
	}while(repetir==1);
	
	printf("=====================================================================\n");
	printf("==== 1. Deletar Operador ============================================\n");
	printf("==== 2. Alterar Operador ============================================\n");
	printf("==== 3. Nao fazer nada ==============================================\n");
	scanf("%d",&op);
	switch(op){
		case 1:
			if(cod_pesquisa != 1){
				remove(novooperador); //Deleta o arquivo.txt
				printf("=====================================================================\n");
				printf("============== Operador excluido com sucesso!========================\n");
				printf("=====================================================================\n");
printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
			}else{
				printf("======== IMPOSIVEL DELETAR O ADIMISTRADOR PRIMARIO DO SISTEMA =======\n");
printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
			}
			adm_sistema();
		break;
		case 2:
			alteraroperador(cod_pesquisa);
		break;
		case 3:
			adm_sistema();
		break;
		default:
			pesquisa_operadores();
	}
	
		
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	
	free(codigo_operador);
	free(permissao);
	free(nome);
	free(usuario);
	free(senha);
	printf("=====================================================================\n");
printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	adm_sistema();
}

int exibir_todos_operadores(){
	
	int i;
	char txt[5] = ".txt";
	char numerodooperador[3],novooperador[23];
	FILE *operador;
	int *codigo_operador = malloc(num_operadores*sizeof(int));
	int *permissao = malloc(num_operadores*sizeof(int));
	char *nome[num_operadores];
	char *usuario[num_operadores];
	char *senha[num_operadores];
	
	printf("=====================================================================\n");
	for(i=0;i<num_operadores;i++){
		nome[i] = malloc(40*sizeof(char));
		usuario[i] = malloc(15*sizeof(char));
		senha[i] = malloc(15*sizeof(char));
	
		sprintf(numerodooperador, "%i", i+1);//converte interio em string
		strcpy (novooperador, "dados\\user");//define valor a string
		strcat (novooperador, numerodooperador); // junta duas strings
		strcat (novooperador, txt); // junta duas strings
		
		operador = fopen(novooperador,"r");
		if(operador != NULL){
			fscanf(operador,"%d",&codigo_operador[i]);
			fscanf(operador,"\n%[^\n]s",nome[i]);
			fscanf(operador,"\n%[^\n]s",usuario[i]);
			fscanf(operador,"\n%[^\n]s",senha[i]);
			fscanf(operador,"%d",&permissao[i]);
			
			printf("Codigo: %d\n",codigo_operador[i]);
			printf("Nome: %s\n",nome[i]);
			printf("Nome de Usuario: %s\n",usuario[i]);
			printf("Nivel de permissao: %d\n",permissao[i]);
			printf("=====================================================================\n");
		}
		fclose(operador);
	}
	
	//free(codigo_operador);
	//free(permissao);
	
	for(i=0;i<num_operadores;i++){
	//	free(nome[i]);
	//	free(usuario[i]);
	//	free(senha[i]);
	}
	

	printf("=====================================================================\n");
printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	adm_sistema();
	
}

int adm_sistema(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	int op,repetir,op2;
	printf("=====================================================================\n");
	printf("===================== Operadores do sistema =========================\n");
	printf("=====================================================================\n");
	printf("===== 1. Exibir ou alterar operadores do sistema: ===================\n");
	printf("===== 2. Inserir novo operador: =====================================\n");
	printf("===== 3. Voltar =====================================================\n");
	printf("===== 0. sair =======================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op);
	switch(op){
		case 0:
			exit(0);
		break;
		case 1:
				printf("=====================================================================\n");
				printf("======================= Pesquisar operadores ========================\n");
				printf("=====================================================================\n");
				printf("====== 1. Pesquisar Operadores por codigo: ==========================\n");
				printf("====== 2. Exibir Todos operadores Cadastrados: ======================\n");
				printf("====== 3. Voltar ====================================================\n");
				printf("=====================================================================\n");
				do{
					repetir=0;
					scanf("%d",&op2);
					switch(op2){
						case 1:
							pesquisa_operadores();
							repetir=0;
						break;
						case 2:
							exibir_todos_operadores();
							repetir=0;
						break;
						case 3:
							adm_sistema();
						break;
						default:
							repetir=1;
					}
				}while(repetir==1);
		break;
		case 2:
			novooperador();
		break;
		case 3:
			modulodecadastrosegestaodedados();
		break;
		default:
			adm_sistema();
	}
	modulodecadastrosegestaodedados();
}

int modulodecadastrosegestaodedados(){

	int categoriadesejada;
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("================ Qual Area Deseja Acessar? ==========================\n");
	printf("=====================================================================\n");
	printf("===== 1. Dados do Hotel =============================================\n");
	printf("===== 2. Dados dos Hospedes =========================================\n");
	printf("===== 3. Dados das Acomodacoes ======================================\n");
	printf("===== 4. Dados dos Produtos Fornecidos ==============================\n");
	printf("===== 5. Dados dos Fornecedores =====================================\n");
	printf("===== 6. Adiministradores do Sistema ================================\n");
	printf("===== 7. Converter arquivos para binario ============================\n");
	printf("===== 8. Voltar =====================================================\n");
	printf("===== 0. Sair do Sistema ============================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	scanf("%d", &categoriadesejada);
		
	switch (categoriadesejada){
	case 1:
		dadosdohotel();
	break;
	case 2:
		dadosdoshospedes();		
	break;
	case 3:
		dadosdeacomodacoes();		
	break;
	case 4:
		dadosdeprodutos();		
	break;
	case 5:
		dadosdefornecedores();
	break;
	case 6:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		adm_sistema();
	break;
	case 7:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		binario();
	break;
	case 8:
		main();
	break;
	case 0:
		exit;
	break;
	default:
		modulodecadastrosegestaodedados();
	}
	main();
}

////////////////////////
//modulo 2 /////////////
////////////////////////

/////////////////verifica aqui ainda
int verificar_data(){
	
	
	int dia_usuario, mes_usuario, ano_usuario; //Data inicial da reserva desejada pelo usuario
	int diaf_usuario, mesf_usuario, anof_usuario; //Data final da reserva desejada pelo usuario
	
	int *dia_reserva, *mes_reserva, *ano_reserva; //Estas variaveis recebem as datas iniciais ja reservadas no sistema
	int *diaf_reserva, *mesf_reserva, *anof_reserva; //Estas variaveis recebem as datas finais ja reservadas no sistema
	
	int flag = 0, flag2 = 0; //Variavel de controle que sera usada para verificar a disponibilidade da reserva
	int *identifica_quarto; //Identifica o codigo do quarto reservado
	
	/*     Aloca memoria para as variaveis dinamicamente     */
	dia_reserva	= malloc(numero_reservas*sizeof(int));
	mes_reserva	= malloc(numero_reservas*sizeof(int));
	ano_reserva	= malloc(numero_reservas*sizeof(int));
	diaf_reserva = malloc(numero_reservas*sizeof(int));
	mesf_reserva = malloc(numero_reservas*sizeof(int));
	anof_reserva = malloc(numero_reservas*sizeof(int));
	identifica_quarto = malloc(numero_reservas*sizeof(int));
	/////////////////////////////////////////////////////////
	
	printf("Digite uma data para verificar a disponibilidade:\n");
	
	printf("Data de entrada:\n");
		
	do { //As estruturas de repeticao Do/while forcam o usuario a digitar um data valida
		printf("Dia:");
		scanf("%d",&dia_usuario);
	} while(dia_usuario<0 && dia_usuario>=31);
		
	do {
	printf("\nMes(numerioco):");
	scanf("%d",&mes_usuario);
	} while(mes_usuario<0 && mes_usuario>=12);
	
	do {	
	printf("\nAno:");
	scanf("%d",&ano_usuario);
	} while(ano_usuario<ano);
		
	printf("\nData de saida:\n");

	do {
	printf("Dia:");
	scanf("%d",&diaf_usuario);
	} while(diaf_usuario<0 && diaf_usuario>=31);
	
	do {
	printf("\nMes(numerioco):");
	scanf("%d",&mesf_usuario);
	} while(mesf_usuario<0 && mesf_usuario>=12);
	
	do {
	printf("\nAno:");
	scanf("%d",&anof_usuario);
	} while(anof_usuario<ano);
	
	printf("\nOs seguintes quartos estao reservados no periodo desejado:\n");
	
	////// Os comandos abaixo verificam as reservas ja existentes ////////
	//1,2,3,5,6,7
	int i;
		
	FILE *reservados;
	char txt[5] = ".txt";
	char abrir_reserva[23];
	char numreservas[3];	
		
	for(i=0; i<numero_reservas; i++){
		
		sprintf(numreservas, "%i", i+1);//converte interio em string
		strcpy (abrir_reserva, "dados\\reserva"); // Define valor a string
		strcat (abrir_reserva, numreservas); // junta duas strings
		strcat (abrir_reserva, txt); // junta duas strings
		
		reservados = fopen(abrir_reserva,"r"); //Abre o arquivo
		
		fscanf(reservados,"%d",&dia_reserva[i]);
		fscanf(reservados,"%d",&dia_reserva[i]);
		fscanf(reservados,"%d",&mes_reserva[i]);
		fscanf(reservados,"%d",&ano_reserva[i]);
		fscanf(reservados,"%d",&diaf_reserva[i]);
		fscanf(reservados,"%d",&diaf_reserva[i]);
		fscanf(reservados,"%d",&mesf_reserva[i]);
		fscanf(reservados,"%d",&anof_reserva[i]);
		fscanf(reservados,"%d",&identifica_quarto[i]);
		
				
		/* Estrutura condicional que ira verificar se a data esta disponivel */
		
		if(ano_usuario<= ano_reserva[i] && anof_usuario >= anof_reserva[i]){
			flag = 1;
		} else flag = 0;
						
		if(mes_usuario<= mes_reserva[i] && mesf_usuario >= mesf_reserva[i]){
			flag = 1;
		} else flag = 0;
				
		if (dia_usuario<=dia_reserva[i] && diaf_usuario<=diaf_reserva[i]){ 
			flag = 1;
		} else flag = 0;
		
		///////////////////////////////////////////////////////////////////////
		
		/* Estrutura condicional que verifica a variavel flag e printa se o quarto esta ou nao disponivel */
		
		if(flag == 1){
			printf("Quarto %d\n",identifica_quarto[i]);
			flag2 = 1;
		}
		
		////////////////////////////////////////////////////////////////////////////////////////////////////
		
		fclose(reservados);
	}
	
	if(flag2 == 0){
		printf("Não a quartos reservados na data desejada.\n");
		printf("\nPrecione qualquer tecla para voltar ao menu:\n");
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		modulodereservas();
	}
	
	printf("Os outros quartos estao disponiveis.\n");
	
	printf("\nPrecione qualquer tecla para voltar ao menu:\n");
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	modulodereservas();
	
}

int verificar_categoria(){
	/* Mostra todos os tipos de acomodacoes */

	char txt[5] = ".txt";
	int i;
	
	FILE *tipoacomod;
	int *codtipoacomod = malloc(numero_de_tipo_acomodacoes*sizeof(int));
	float *ValorDiaria = malloc(numero_de_tipo_acomodacoes*sizeof(float));
	int *qtdHospedes = malloc(numero_de_tipo_acomodacoes*sizeof(int));
	char numtipacomodacao[3];
	char abriracomod[23];
	char *destipoacomod[numero_de_tipo_acomodacoes];
	
	for(i=0;i<numero_de_tipo_acomodacoes;i++){
		destipoacomod[i] = malloc(250*sizeof(char));
		
		sprintf(numtipacomodacao, "%i", i+1);//converte interio em string
		strcpy (abriracomod, "dados\\tacomodacao"); // Define o valor da string
		strcat (abriracomod, numtipacomodacao); // junta duas strings
		strcat (abriracomod, txt); // junta duas strings
		
		tipoacomod = fopen(abriracomod,"r");
		fflush(stdin); // limpa o buffer do teclado
		fscanf(tipoacomod,"%i\n",&codtipoacomod[i]);
		fscanf(tipoacomod,"%[^\n]s",destipoacomod[i]);		
		fscanf(tipoacomod,"%f\n",&ValorDiaria[i]);
		fscanf(tipoacomod,"%d",&qtdHospedes[i]);
		fclose(tipoacomod);
		
		printf("Codigo da categoria: %d\n",codtipoacomod[i]);
		printf("Descricao da categoria: %s\n",destipoacomod[i]);
		printf("Valor da Diaria: %.2f\n",ValorDiaria[i]);
		printf("Quantidade de Pessoas: %d\n\n",qtdHospedes[i]);
		printf("=======================================================================\n");
	}
	////////////////////////////////////////////////////////////
	
	/* Recebe o tipo de categoria desejada pelo usuario */
	int tipo_op; //Armazena a escolha do usuario;
	
	printf("Digite o tipo de categoria desejada\n");
	scanf ("%d",&tipo_op);
	
	printf("Descricao da categoria: %s\n",destipoacomod[tipo_op-1]);
	printf("Valor da Diaria: %.2f\n",ValorDiaria[tipo_op-1]);
	printf("Quantidade de Pessoas: %d\n\n",qtdHospedes[tipo_op-1]);
	/////////////////////////////////////////////////////////
	
	printf("Quartos disponiveis com o tipo de acomodacao desejado:\n");
	
	/* Procura as acomodacoes com o tipo de acomodacao desejado */
	FILE *acomod;
	char numerodaacomodacao[3];
	char acomodacao[23] = "dados\\acomodacao";
	
	/* variaveis que receberam o codigo da acomodacao e seu tipo */
	int *codigo = malloc(numero_de_acomodacoes * sizeof(int));
	char *descricao[numero_de_acomodacoes];
	char *facilidades[numero_de_acomodacoes];
	int *tipo = malloc(numero_de_acomodacoes * sizeof(int));
	//////////////////////////////////////////////////////////////////
	for(i=0; i<numero_de_acomodacoes; i++){
	
		descricao[i] = malloc(250 * sizeof(char));
		facilidades[i] = malloc(250 * sizeof(char));
		
		sprintf(numerodaacomodacao, "%i", i+1);//converte interio em string
		strcpy (acomodacao,"dados\\acomodacao");
		strcat (acomodacao, numerodaacomodacao); // junta duas strings
		strcat (acomodacao, txt); // junta duas strings
	
		acomod = fopen(acomodacao,"r");	
		if(acomod != NULL){
			fscanf(acomod,"%i\n",&codigo[i]);
			fscanf(acomod,"%[^\n]s",descricao[i]);
			fscanf(acomod,"\n%[^\n]s",facilidades[i]);
			fscanf(acomod,"%i\n",&tipo[i]);	
			if(tipo_op == tipo[i]){
				printf("Quarto: %d\n",codigo[i]);
			}
		}
	fclose(acomod);
	}
	printf("Descricao: %s\n",descricao[tipo_op-1]);
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
}

int verificar_vagas(){
	
	int vd; //vagas desejadas
	int i;
	char txt[5] = ".txt";
	FILE *tipoacomod;
	int *codtipoacomod = malloc(numero_de_acomodacoes*sizeof(int));
	float *ValorDiaria = malloc(numero_de_acomodacoes*sizeof(float));
	int *qtdHospedes = malloc(numero_de_acomodacoes*sizeof(int));
	char numtipacomodacao[3];
	char abriracomod[23];
	char *destipoacomod[numero_de_acomodacoes];
	FILE *acomod;
	char numerodaacomodacao[3];
	char acomodacao[23] = "dados\\acomodacao";
		
	printf("Digite a quantidade de vagas que voce deseja:\n");
	scanf("%d",&vd);
	printf("Quartos disponiveis :\n");

	/* variaveis que receberam o codigo da acomodacao e seu tipo */
	int *codigo = malloc(numero_de_acomodacoes * sizeof(int));
	char *descricao[numero_de_acomodacoes];
	char *facilidades[numero_de_acomodacoes];
	int *tipo = malloc(numero_de_acomodacoes*sizeof(int));
	//////////////////////////////////////////////////////////////////
	for(i=0;i<numero_de_acomodacoes;i++){
		destipoacomod[i] = malloc(250*sizeof(char));
	}
	
	for(i=0; i<numero_de_acomodacoes; i++){
		descricao[i] = malloc(250 * sizeof(char));
		facilidades[i] = malloc(250 * sizeof(char));
		
		sprintf(numerodaacomodacao, "%i", i+1);//converte interio em string
		strcpy (acomodacao,"dados\\acomodacao");
		strcat (acomodacao, numerodaacomodacao); // junta duas strings
		strcat (acomodacao, txt); // junta duas strings
	
		acomod = fopen(acomodacao,"r");	
		if(acomod!=NULL){
			fscanf(acomod,"%i\n",&codigo[i]);
			fscanf(acomod,"\n%[^\n]s",descricao[i]);
			fscanf(acomod,"\n%[^\n]s",facilidades[i]);
			fscanf(acomod,"%i\n",&tipo[i]);
			
			
			sprintf(numtipacomodacao, "%i", tipo[i]);//converte interio em string
			strcpy (abriracomod, "dados\\tacomodacao"); // Define o valor da string
			strcat (abriracomod, numtipacomodacao); // junta duas strings
			strcat (abriracomod, txt); // junta duas strings
			
			tipoacomod = fopen(abriracomod,"r");
			
			fflush(stdin); // limpa o buffer do teclado
			fscanf(tipoacomod,"%i\n",&codtipoacomod[i]);
			fscanf(tipoacomod,"\n%[^\n]s",destipoacomod[i]);
			fflush(stdin); // limpa o buffer do teclado
			fscanf(tipoacomod,"%f",&ValorDiaria[i]);
			fscanf(tipoacomod,"\n%i",&qtdHospedes[i]);
			fclose(tipoacomod);
			if(qtdHospedes[i]==vd){
				printf("Quarto: %d\n",codigo[i]);
				printf("Descricao: %s\n",descricao[i]);
				printf("Valor da Diaria: %.2f\n",ValorDiaria[i]);
				printf("Quantidade de Pessoas: %d\n\n",qtdHospedes[i]);
			}
		}
		fclose(acomod);
	}
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	///////////////////////////////////////////////
}

int cancelar_reserva(){
	
	FILE *open_reservas;
	int i,reserva_cancelar;
	int *codigo_reserva = malloc(numero_reservas*sizeof(int));
	int *dia_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *dias_reservado = malloc(numero_reservas*sizeof(int));
	int *dia_final_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_final_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_final_reserva = malloc(numero_reservas*sizeof(int));
	int *quarto_reservado = malloc(numero_reservas*sizeof(int));
	int *codhosp_reserva = malloc(numero_reservas*sizeof(int));
	int *situacao = malloc(numero_reservas*sizeof(int));	
	
	char *nome_hospede[numero_reservas];
	int *codigo_hospede= malloc(numero_reservas*sizeof(int));
	char numerodohospede[3],txt[5] = ".txt";
	FILE * hosp;
	
	char numero_reserva[3],openreserva[23],openhospede[23];

	for(i=0;i<numero_reservas;i++){//pega os dados das reservas ja efetuadas
		nome_hospede[i] = malloc(40*sizeof(char));
		sprintf(numero_reserva, "%i", i+1);//converte interio em string
		strcpy (openreserva, "dados\\reserva");//define valor a string
		strcat (openreserva, numero_reserva); // junta duas strings
		strcat (openreserva, txt); // junta duas strings
		
		open_reservas = fopen(openreserva,"r");
		
		fscanf(open_reservas,"%i",&codigo_reserva[i]);
		fscanf(open_reservas,"%i",&dia_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&mes_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&ano_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&dias_reservado[i]);
		fscanf(open_reservas,"%i",&dia_final_reserva[i]);
		fscanf(open_reservas,"%i",&mes_final_reserva[i]);
		fscanf(open_reservas,"%i",&ano_final_reserva[i]);
		fscanf(open_reservas,"%i",&quarto_reservado[i]);
		fscanf(open_reservas,"%i",&codhosp_reserva[i]);
		fscanf(open_reservas,"%i",&situacao[i]);

		fclose(open_reservas);

		sprintf(numerodohospede, "%i", codhosp_reserva[i]);//converte interio em string
		strcpy (openhospede, "dados\\hospede");//define valor a string
		strcat (openhospede, numerodohospede); // junta duas strings
		strcat (openhospede, txt); // junta duas strings
		
		hosp = fopen(openhospede,"r");
		fscanf(hosp,"%i\n",&codigo_hospede[i]);
		fscanf(hosp,"\n%[^\n]s",nome_hospede[i]);
		fclose(hosp);	
	}
	
	printf("=====================================================================\n");
	printf("====================== Cancelar uma reserva =========================\n");
	printf("=====================================================================\n");
	
	for(i=0;i<numero_reservas;i++){
		if (situacao[i] ==1){
			printf("=====================================================================\n");
			printf("Codigo da reserva: %d\n",codigo_reserva[i]);
			printf("Data de Inicio da reserva: %d/%d/%d\n",dia_inicio_reserva[i],mes_inicio_reserva[i],ano_inicio_reserva[i]);
			printf("Ficara %d dias reservado\n",dias_reservado[i]);
			printf("Data do Fim da reserva: %d/%d/%d\n",dia_final_reserva[i],mes_final_reserva[i],ano_final_reserva[i]);
			printf("Quarto Reservado: %d\n",quarto_reservado[i]);
			printf("Hospede que reservou o quarto: %s\n",nome_hospede[i]);
			printf("Status da reserva: %d\n",situacao[i]);
			printf("=====================================================================\n");
		}
	}
	printf("======= Qual reserva voce deseja cancelar? ==========================\n");
	scanf("%d",&reserva_cancelar);

	sprintf(numero_reserva, "%i", reserva_cancelar);//converte interio em string
	strcpy (openreserva, "dados\\reserva");//define valor a string
	strcat (openreserva, numero_reserva); // junta duas strings
	strcat (openreserva, txt); // junta duas strings
	
	open_reservas = fopen(openreserva,"w");
	
	fprintf(open_reservas,"%i\n",codigo_reserva[reserva_cancelar-1]);
	fprintf(open_reservas,"%i\n",dia_inicio_reserva[reserva_cancelar-1]);
	fprintf(open_reservas,"%i\n",mes_inicio_reserva[reserva_cancelar-1]);
	fprintf(open_reservas,"%i\n",ano_inicio_reserva[reserva_cancelar-1]);
	fprintf(open_reservas,"%i\n",dias_reservado[reserva_cancelar-1]);
	fprintf(open_reservas,"%i\n",dia_final_reserva[reserva_cancelar-1]);
	fprintf(open_reservas,"%i\n",mes_final_reserva[reserva_cancelar-1]);
	fprintf(open_reservas,"%i\n",ano_final_reserva[reserva_cancelar-1]);
	fprintf(open_reservas,"%i\n",quarto_reservado[reserva_cancelar-1]);
	fprintf(open_reservas,"%i\n",codhosp_reserva[reserva_cancelar-1]);
	fprintf(open_reservas,"0");
	// 0 = cancelada
	// 1 = Ativa
	// 2 = em uso
	// 3 = já passpo

	fclose(open_reservas);
	
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	modulodereservas();
}

int reserva(){
	int diafinaldareserva,mes_fimreserva,ano_fimreserva,cod_hosp_reserva,dias_mes[12];
	int *dia_inicio_reserva,*mes_inicio_reserva,*ano_inicio_reserva,*dias_reservado,*codigo_reserva;
	int *dia_final_reserva,*mes_final_reserva,*ano_final_reserva,*quarto_reservado,*codhosp_reserva;
	int i,j,quartoreservado,dia_inicioreserva,dias_reserva,mes_inicioreserva,ano_inicioreserva;
	int *codtipoacomod,*qtdHospedes,*codacomod,*categ;
	char txt[5] = ".txt",num_acomodacao[3],abrir_acomod[23],numtipacomodacao[3],abriracomod[23];
	char *desc_acomodacao[numero_de_acomodacoes],*facil[numero_de_acomodacoes],*destipoacomod[numero_de_tipo_acomodacoes];
	char numero_reserva[3],openreserva[23];
	FILE *tipoacomod,*quartos,*reservas,*num_reservas,*open_reservas,*situacao;
	float *ValorDiaria;
	int *mostrar = malloc(numero_reservas*sizeof(int));
	
	
		
	FILE *hosp;
	
	int *codigo_hospede = malloc(numero_de_hospedes*sizeof(int));
	char numerodohospede[3];
	char newhospede[23];
	
	char *nome_hospede[numero_de_hospedes];
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("========================= Reservar Quarto ===========================\n");
	printf("========================= Data:%i/%i/%i ===========================\n",dia,mes,ano);
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	printf("======= Digite o Dia de inicio da reserva: (Sem o Mes) ==============\n");
	scanf("%d",&dia_inicioreserva);
	printf("======= Digite o Mes de inicio da reserva: ==========================\n");
	scanf("%d",&mes_inicioreserva);
	printf("======= Digite o Ano de inicio da reserva: ==========================\n");
	scanf("%d",&ano_inicioreserva);
	printf("======= Digite quantos dias o quarto ficara reservado: ==============\n");
	scanf("%d",&dias_reserva);
	
	diafinaldareserva = dia_inicioreserva+dias_reserva;
	ano_fimreserva=ano_inicioreserva;
	
	dias_mes[0] = 31;//janeiro
	if ((ano % 4 == 0) && (ano % 400 == 0 || ano % 100 != 0)){ //verificar se é ano bissexto
		dias_mes[1] = 29;//fevereiro
		}else{
			dias_mes[1] = 28;//fevereiro
		}
	dias_mes[2] = 31;//marco
	dias_mes[3] = 30;//abril
	dias_mes[4] = 31;//maio
	dias_mes[5] = 30;//junho
	dias_mes[6] = 31;//julho
	dias_mes[7] = 31;//agosto
	dias_mes[8] = 30;//setembro
	dias_mes[9] = 31;//outubro
	dias_mes[10] = 30;//novembro
	dias_mes[11] = 31;//dezembro
	
	int dias_mes_fimreserva;
	mes_fimreserva = mes_inicioreserva;
	dias_mes_fimreserva = dias_mes[mes_inicioreserva-1];
	
	if(diafinaldareserva > dias_mes[mes_inicioreserva-1]){

		while(diafinaldareserva > dias_mes_fimreserva){

			diafinaldareserva = diafinaldareserva - dias_mes[mes_fimreserva-1];

			if(mes_fimreserva ==12){
				mes_fimreserva=1;
				ano_fimreserva++;
			}else{
				mes_fimreserva++;
			}
			dias_mes_fimreserva = dias_mes[mes_fimreserva-1];
		}
	}
	
	ValorDiaria = malloc(numero_de_tipo_acomodacoes*sizeof(float));
	codtipoacomod = malloc(numero_de_tipo_acomodacoes*sizeof(int));
	qtdHospedes = malloc(numero_de_tipo_acomodacoes*sizeof(int));
	codacomod = malloc(numero_de_acomodacoes*sizeof(int));
	categ = malloc(numero_de_acomodacoes*sizeof(int));
	
	for(i=0;i<numero_de_tipo_acomodacoes;i++){//tipos de acomodacoes
		
		destipoacomod[i] = malloc(250*sizeof(char));
		
		sprintf(numtipacomodacao, "%i", i+1);//converte interio em string
		
		strcpy (abriracomod, "dados\\tacomodacao"); // Define o valor da string
		
		strcat (abriracomod, numtipacomodacao); // junta duas strings
		strcat (abriracomod, txt); // junta duas strings
		
		tipoacomod = fopen(abriracomod,"r");
	
		if (tipoacomod != NULL){
			fflush(stdin); // limpa o buffer do teclado
			fscanf(tipoacomod,"%i\n",&codtipoacomod[i]);
			fscanf(tipoacomod,"\n%[^\n]s",destipoacomod[i]);
			
			fflush(stdin); // limpa o buffer do teclado
			fscanf(tipoacomod,"%f",&ValorDiaria[i]);
			fscanf(tipoacomod,"\n%i",&qtdHospedes[i]);
		}
		fclose(tipoacomod);
	}
	
	for(i=0;i<numero_de_acomodacoes;i++){//acomodacoes
		desc_acomodacao[i] = malloc(250*sizeof(char));
		facil[i] = malloc(250*sizeof(char));
		
		sprintf(num_acomodacao, "%i", i+1);//converte interio em string
		
		strcpy (abrir_acomod, "dados\\acomodacao"); // Define o valor da string
		
		strcat (abrir_acomod, num_acomodacao); // junta duas strings
		strcat (abrir_acomod, txt); // junta duas strings
		
		quartos = fopen(abrir_acomod,"r");
		
		if (quartos != NULL){
			fflush(stdin); // limpa o buffer do teclado
			fscanf(quartos,"%i\n",&codacomod[i]);
			
			fscanf(quartos,"\n%[^\n]s",desc_acomodacao[i]);
			fscanf(quartos,"\n%[^\n]s",facil[i]);

			fscanf(quartos,"\n%i",&categ[i]);
		}
		fclose(quartos);
	}

	codigo_reserva = malloc(numero_reservas*sizeof(int));
	dia_inicio_reserva = malloc(numero_reservas*sizeof(int));
	mes_inicio_reserva = malloc(numero_reservas*sizeof(int));
	ano_inicio_reserva = malloc(numero_reservas*sizeof(int));
	dias_reservado = malloc(numero_reservas*sizeof(int));
	dia_final_reserva = malloc(numero_reservas*sizeof(int));
	mes_final_reserva = malloc(numero_reservas*sizeof(int));
	ano_final_reserva = malloc(numero_reservas*sizeof(int));
	quarto_reservado = malloc(numero_reservas*sizeof(int));
	codhosp_reserva = malloc(numero_reservas*sizeof(int));
	situacao = malloc(numero_reservas*sizeof(int));
	

	for(i=0;i<numero_reservas;i++){//pega os dados das reservas ja efetuadas
		
		sprintf(numero_reserva, "%i", i+1);//converte interio em string
		strcpy (openreserva, "dados\\reserva");//define valor a string
		strcat (openreserva, numero_reserva); // junta duas strings
		strcat (openreserva, txt); // junta duas strings
		
		open_reservas = fopen(openreserva,"r");
		
		
		fscanf(open_reservas,"%i",&codigo_reserva[i]);
		fscanf(open_reservas,"%i",&dia_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&mes_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&ano_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&dias_reservado[i]);
		fscanf(open_reservas,"%i",&dia_final_reserva[i]);
		fscanf(open_reservas,"%i",&mes_final_reserva[i]);
		fscanf(open_reservas,"%i",&ano_final_reserva[i]);
		fscanf(open_reservas,"%i",&quarto_reservado[i]);
		fscanf(open_reservas,"%i",&codhosp_reserva[i]);
		fscanf(open_reservas,"%i",&situacao[i]);
		
		fclose(open_reservas);
		
		
	//	printf("%d\n",codigo_reserva[i]);
	//	printf("%d\n",dia_inicio_reserva[i]);
	//	printf("%d\n",mes_inicio_reserva[i]);
	//	printf("%d\n",ano_inicio_reserva[i]);
	//	printf("%d\n",dias_reservado[i]);
	//	printf("%d\n",dia_final_reserva[i]);
	//	printf("%d\n",mes_final_reserva[i]);
	//	printf("%d\n",ano_final_reserva[i]);
	//	printf("%d\n",quarto_reservado[i]);
	//	printf("%d\n",codhosp_reserva[i]);
	}

	
	for(i=0;i<numero_de_acomodacoes;i++){//exibir acomodacoes
		mostrar[i] = 1;
		
		for(j=0;j<numero_reservas;j++){// verificar quartos disponiveis
			if(i+1 == quarto_reservado[j]){
				
				if(ano_inicioreserva == ano_final_reserva[j]){
					//a
					if(mes_inicioreserva > mes_final_reserva[j]){//mes Inicio || Mes fim 
						mostrar[i]=1;
					}
					else if (mes_inicioreserva < mes_final_reserva[j]){
						if(mes_fimreserva > mes_inicio_reserva[j]){ // mes Fim || mes inicio
							mostrar[i]=0;
						}else if(mes_fimreserva < mes_inicio_reserva[j]){
							mostrar[i]=1;
						}else if(mes_fimreserva == mes_inicio_reserva[j]){
							if(diafinaldareserva < dia_inicio_reserva[j]){ // dia fim || dia inicio
								mostrar[i] = 1;
							}else if(diafinaldareserva >= dia_inicio_reserva[j]){
								mostrar[i]=0;
							}
						}
					}
					else if(mes_inicioreserva == mes_final_reserva[j]){
						if(dia_inicioreserva <= dia_final_reserva[j]){
							mostrar[i]=0;
						}else if(dia_inicioreserva > dia_final_reserva[j]){
							mostrar[i] =1;
						}
					}
					//a
				}
				
				else if(ano_inicioreserva > ano_final_reserva[j]){
					mostrar[i]=1;
				}
				
				else if (ano_inicioreserva < ano_final_reserva[j]){
					
					if(ano_fimreserva < ano_inicio_reserva[j]){
						mostrar[i]=1;
					}
					else if(ano_fimreserva == ano_inicio_reserva[j]){
						//A
						if(mes_fimreserva > mes_inicio_reserva[j]){//mes Inicio || Mes fim 
							mostrar[i]=0;
						}else if(mes_fimreserva < mes_inicio_reserva[j]){
							mostrar[i]=1;
						}else if(mes_fimreserva == mes_inicio_reserva[j]){
							if(diafinaldareserva < dia_inicio_reserva[j]){ // dia fim || dia inicio
								mostrar[i]=1;
							}else if(diafinaldareserva >= dia_inicio_reserva[j]){
								mostrar[i]=0;
							}
						}
					}else if (ano_fimreserva > ano_inicio_reserva[j]){
						mostrar[i]=0;
					}
				}
			}
		}
		
		sprintf(num_acomodacao, "%i", i+1);//converte interio em string
		strcpy (abrir_acomod, "dados\\acomodacao"); // Define o valor da string
		strcat (abrir_acomod, num_acomodacao); // junta duas strings
		strcat (abrir_acomod, txt); // junta duas strings
		
		quartos = fopen(abrir_acomod,"r");

		if (quartos != NULL){
			if(mostrar[i]==1){
				printf("=====================================================================\n");
				printf("Codigo da acomodacao: %d\n",codacomod[i]);
				printf("Descricao da acomodacao: %s\n",desc_acomodacao[i]);
				printf("Facilidades: %s\n",facil[i]);
				//printf("Categoria: %i\n",categ[i]);
				printf("Valor da Diaria: %.2f\n",ValorDiaria[categ[i]]);
				printf("Quantidade de Pessoas: %d\n\n",qtdHospedes[categ[i]]);
				printf("=====================================================================\n");
			}
		}
		
		fclose(quartos);
	}
	
	
	printf("======= Escolha um dos quartos disponiveis acima: ===================\n");
	scanf("%d",&quartoreservado);
	
	for(i=0;i<numero_de_hospedes;i++){//exibir hospedes
		mostrar[i] = 1;
		
		for(j=0;j<numero_reservas;j++){ // verificar Hospedes disponiveis
			if(i+1 == codhosp_reserva[i]){
				if(ano_inicioreserva == ano_final_reserva[j]){
					//a
					if(mes_inicioreserva > mes_final_reserva[j]){//mes Inicio || Mes fim 
						mostrar[i]=1;
					}
					else if (mes_inicioreserva < mes_final_reserva[j]){
						if(mes_fimreserva > mes_inicio_reserva[j]){ // mes Fim || mes inicio
							mostrar[i]=0;
						}else if(mes_fimreserva < mes_inicio_reserva[j]){
							mostrar[i]=1;
						}else if(mes_fimreserva == mes_inicio_reserva[j]){
							if(diafinaldareserva < dia_inicio_reserva[j]){ // dia fim || dia inicio
								mostrar[i] = 1;
							}else if(diafinaldareserva >= dia_inicio_reserva[j]){
								mostrar[i]=0;
							}
						}
					}
					else if(mes_inicioreserva == mes_final_reserva[j]){
						if(dia_inicioreserva <= dia_final_reserva[j]){
							mostrar[i]=0;
						}else if(dia_inicioreserva > dia_final_reserva[j]){
							mostrar[i] =1;
						}
					}
					//a
				}
				
				else if(ano_inicioreserva > ano_final_reserva[j]){
					mostrar[i]=1;
				}
				
				else if (ano_inicioreserva < ano_final_reserva[j]){
					
					if(ano_fimreserva < ano_inicio_reserva[j]){
						mostrar[i]=1;
					}
					else if(ano_fimreserva == ano_inicio_reserva[j]){
						//A
						if(mes_fimreserva > mes_inicio_reserva[j]){//mes Inicio || Mes fim 
							mostrar[i]=0;
						}else if(mes_fimreserva < mes_inicio_reserva[j]){
							mostrar[i]=1;
						}else if(mes_fimreserva == mes_inicio_reserva[j]){
							if(diafinaldareserva < dia_inicio_reserva[j]){ // dia fim || dia inicio
								mostrar[i]=1;
							}else if(diafinaldareserva >= dia_inicio_reserva[j]){
								mostrar[i]=0;
							}
						}
					}else if (ano_fimreserva > ano_inicio_reserva[j]){
						mostrar[i]=0;
					}
				}
			}
		}
			
		nome_hospede[i] = malloc(40*sizeof(char));
		sprintf(numerodohospede, "%i", i+1);//converte interio em string
		strcpy (newhospede, "dados\\hospede");//define valor a string
		
		strcat (newhospede, numerodohospede); // junta duas strings
		strcat (newhospede, txt); // junta duas strings
		
		hosp = fopen(newhospede,"r");
		if(hosp!=NULL){
			if(mostrar[i]==1){
				fscanf(hosp,"%i\n",&codigo_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",nome_hospede[i]);
				fclose(hosp);
				printf("Codigo do Hospede: %i\n",codigo_hospede[i]);
				printf("Nome Do Hospede: %s\n",nome_hospede[i]);
				printf("=====================================================================\n");
				
			}
		}
		//free(codigo_hospede[i]);
		//free(nome_hospede[i]);
	}
	
	printf("======= Informe o Codigo do Hospede que ficara no quarto: ===========\n");
	scanf("%d",&cod_hosp_reserva);
	
	char abrir_reserva[23] = "dados\\reserva";
	char numreservas[3];
	
	sprintf(numreservas, "%i", numero_reservas+1);//converte interio em string
	
	strcat (abrir_reserva, numreservas); // junta duas strings
	strcat (abrir_reserva, txt); // junta duas strings
	
	reservas = fopen(abrir_reserva,"w");
	
	fprintf(reservas,"%i\n",numero_reservas+1);
	fprintf(reservas,"%i\n",dia_inicioreserva);
	fprintf(reservas,"%i\n",mes_inicioreserva);
	fprintf(reservas,"%i\n",ano_inicioreserva);
	fprintf(reservas,"%i\n",dias_reserva);
	fprintf(reservas,"%i\n",diafinaldareserva);
	fprintf(reservas,"%i\n",mes_fimreserva);
	fprintf(reservas,"%i\n",ano_fimreserva);
	fprintf(reservas,"%i\n",quartoreservado);
	fprintf(reservas,"%i\n",cod_hosp_reserva);
	fprintf(reservas,"1\n");
	fprintf(reservas,"0\n");
	fprintf(reservas,"0");
	// 0 = cancelada
	// 1 = Ativa
	// 2 = em uso
	// 3 = já passpo
	
	fclose(reservas);
	
	num_reservas = fopen("dados\\Nreservas.txt","w");
	fprintf(num_reservas,"%i",numero_reservas+1);
	fclose(num_reservas);
	
	free(codigo_reserva);
	free(dia_inicio_reserva);
	free(mes_inicio_reserva);
	free(ano_inicio_reserva);
	free(dias_reservado);
	free(dia_final_reserva);
	free(mes_final_reserva);
	free(ano_final_reserva);
	free(quarto_reservado);
	free(codhosp_reserva);
	
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		main();
}

int exibir_reservas(){
		
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
		
	int i;
	
	int *codigo_reserva = malloc(numero_reservas*sizeof(int));
	int *dia_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *dias_reservado = malloc(numero_reservas*sizeof(int));
	int *dia_final_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_final_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_final_reserva = malloc(numero_reservas*sizeof(int));
	int *quarto_reservado = malloc(numero_reservas*sizeof(int));
	int *codhosp_reserva = malloc(numero_reservas*sizeof(int));
	int *situacao = malloc(numero_reservas*sizeof(int));
	
	
	char txt[5] = ".txt";
	FILE *open_reservas,*hosp;
	
	char abrir_reserva[23];
	char numreservas[3];
	
	char *nome_hospede[numero_reservas];
	int *codigo_hospede= malloc(numero_reservas*sizeof(int));
	char numerodohospede[3],openhospede[23];
		
	for(i=0;i<numero_reservas;i++){//pega os dados das reservas ja efetuadas
		nome_hospede[i] = malloc(40*sizeof(char));
		sprintf(numreservas, "%i", i+1);//converte interio em string
		strcpy (abrir_reserva, "dados\\reserva");//define valor a string
		strcat (abrir_reserva, numreservas); // junta duas strings
		strcat (abrir_reserva, txt); // junta duas strings
		
		open_reservas = fopen(abrir_reserva,"r");
		
		fscanf(open_reservas,"%i",&codigo_reserva[i]);
		fscanf(open_reservas,"%i",&dia_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&mes_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&ano_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&dias_reservado[i]);
		fscanf(open_reservas,"%i",&dia_final_reserva[i]);
		fscanf(open_reservas,"%i",&mes_final_reserva[i]);
		fscanf(open_reservas,"%i",&ano_final_reserva[i]);
		fscanf(open_reservas,"%i",&quarto_reservado[i]);
		fscanf(open_reservas,"%i",&codhosp_reserva[i]);
		fscanf(open_reservas,"%i",&situacao[i]);
		
		fclose(open_reservas);
		
		sprintf(numerodohospede, "%i", codhosp_reserva[i]);//converte interio em string
		strcpy (openhospede, "dados\\hospede");//define valor a string
		
		strcat (openhospede, numerodohospede); // junta duas strings
		strcat (openhospede, txt); // junta duas strings
		
		hosp = fopen(openhospede,"r");
		
		fscanf(hosp,"%i\n",&codigo_hospede[i]);
		fscanf(hosp,"\n%[^\n]s",nome_hospede[i]);	

		fclose(hosp);
		printf("======================================================================\n");
		printf("Reserva: %d\n",codigo_reserva[i]);
		printf("Inicio da reserva: %d/%d/%d\n",dia_inicio_reserva[i],mes_inicio_reserva[i],ano_inicio_reserva[i]);
		printf("Dias Reservados: %d\n",dias_reservado[i]);
		printf("Fim da reserva: %d/%d/%d\n",dia_final_reserva[i],mes_final_reserva[i],ano_final_reserva[i]);
		printf("Quarto Reservado%d\n",quarto_reservado[i]);
		printf("Hospede que reservou o quarto: %s\n",nome_hospede[i]);
		
		switch(situacao[i]){
			case 0:
				printf("Status da reserva: CANCELADA\n");
			break;
			case 1:
				printf("Status da reserva: Reservada\n");
			break;
			case 2:
				printf("Status da reserva: Em Uso\n");
			break;
			case 3:
				printf("Status da reserva: Passou\n");
			break;
		}
		
	}

		
	printf("\nPrecione qualquer tecla para voltar ao menu:\n");
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	modulodereservas();
	
}

int modulodereservas(){
	int categoriadesejada;
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("================ Qual Area Deseja Acessar? ==========================\n");
	printf("=====================================================================\n");
	printf("===== 1. Realizar Reserva ===========================================\n");
	printf("===== 2. Exibir Reservars ===========================================\n");
	printf("===== 3. Verificar Disponibilidade do quarto por data ===============\n");
	printf("===== 4. Verificar Disponibilidade do quarto por categoria ==========\n");
	printf("===== 5. Verificar Disponibilidade do quarto por vagas disponiveis ==\n");
	printf("===== 6. Cancelar uma reserva =======================================\n");
	printf("===== 7. Voltar =====================================================\n");
	printf("===== 0. Sair do Sistema ============================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	scanf("%d", &categoriadesejada);
		
	switch (categoriadesejada){
	case 1:
		reserva();
	break;
	case 2:
		exibir_reservas();
	break;
	case 3:
		verificar_data();
	break;
	case 4:
		verificar_categoria();
	break;
	case 5:
		verificar_vagas();
	break;
	case 6:
		cancelar_reserva();
	break;
	case 7:
		main();
	break;
	case 0:
		exit(0);
	break;
	}
	modulodereservas();
}

////////////////////////
//modulo 3 /////////////
////////////////////////

void adicionarcontaareceber(int dia_receber, int mes_receber,int ano_receber, float total,char descricao[300]){
			
	FILE *contas;
	contas = fopen("dados\\contas.txt","a");
	fprintf(contas,"%i\n",dia_receber);
	fprintf(contas,"%i\n",mes_receber);
	fprintf(contas,"%i\n",ano_receber);
	fprintf(contas,"%f\n",total);
	fprintf(contas,"%s\n",descricao);
	fclose(contas);
	
}

void adicionar_contas_pagar(int dia_pagar, int mes_pagar,int ano_pagar, float total,char descricao[300]){
			
	FILE *pagar;
	pagar = fopen("dados\\pagar.txt","a");
	fprintf(pagar,"%i\n",dia_pagar);
	fprintf(pagar,"%i\n",mes_pagar);
	fprintf(pagar,"%i\n",ano_pagar);
	fprintf(pagar,"%f\n",total);
	fprintf(pagar,"%s\n",descricao);
	fclose(pagar);
}

///////////////////////////////

int compra(int ncompra){
	
	FILE *carrinho,*prod,*compra_atual;
	char numero_venda[3],open_carrinho[23],txt[5] = ".txt";
	int cod_prod,qtd_prod,adicionar_produtos,opcao;
	
	int *codigo = malloc(numero_de_produtos*sizeof(int));
	int *estoque = malloc(numero_de_produtos*sizeof(int));
	int *estoque_minimo = malloc(numero_de_produtos*sizeof(int));
	
	float *preco_custo = malloc(numero_de_produtos*sizeof(float));
	float *preco_venda = malloc(numero_de_produtos*sizeof(float));
	
	char *descricao_produto[numero_de_produtos];

	int i,continuar=0,op,repetir,j;
	float preco_total_compra_atual,preco_total=0;
	
	char ql;
	int numero_linhas=0;

	char numerodeprodutos[3];
	char openproduto[23];
	
	for(i=0;i<numero_de_produtos;i++){
		descricao_produto[i] = malloc(300*sizeof(char));
	
		sprintf(numerodeprodutos, "%i", i+1);//converte interio em string
		strcpy (openproduto, "dados\\produto");//define valor a string
		strcat (openproduto, numerodeprodutos); // junta duas strings
		strcat (openproduto, txt); // junta duas strings
		
		prod = fopen(openproduto,"r");
		if(prod!=NULL){
			fscanf(prod,"%i\n",&codigo[i]);
			fscanf(prod,"\n%[^\n]s",descricao_produto[i]);
			fscanf(prod,"%i\n",&estoque[i]);
			fscanf(prod,"%i\n",&estoque_minimo[i]);
			fscanf(prod,"%f\n",&preco_custo[i]);
			fscanf(prod,"%f",&preco_venda[i]);
		}
		fclose(prod);
	}
	
	printf("================== Adicionar produtos a compra ======================\n");
	printf("=====================================================================\n");
	printf("===== 1. Exibir Todos os Produtos: ==================================\n");
	printf("===== 2. Inserir codigo do produto: =================================\n");
	do{
		scanf("%d",&opcao);
		switch(opcao){
			case 1:
				exibirtodosprodutos();
				repetir=0;
			break;
			case 2:
				repetir=0;
			break;
			default:
				printf("!Opcao Invalida!\nTente Novamene\n");
				repetir=1;
		}
	}while(repetir==1);
	adicionar_produtos=1;
	while(adicionar_produtos ==1){
		do{
			printf("===== Insira o codigo do produto no pra compra: =====================\n");
			
			scanf("%d",&cod_prod);

			sprintf(numerodeprodutos, "%i", cod_prod);//converte interio em string
			strcpy (openproduto, "dados\\produto");//define valor a string
			strcat (openproduto, numerodeprodutos); // junta duas strings
			strcat (openproduto, txt); // junta duas strings
			prod = fopen(openproduto,"r");
			
			if (prod != NULL){
				printf("Codigo: %d\n",codigo[cod_prod-1]);
				printf("Descricao: %s\n",descricao_produto[cod_prod-1]);
				printf("Estoque Atual: %d\n",estoque[cod_prod-1]);
				printf("Preco de compra: %.2f\n",preco_custo[cod_prod-1]);
				continuar =1;
			}else{
				printf("!Codigo Invalido!\n");
				continuar=0;
			}
		}while(continuar==0);
		continuar =0;
		
		printf("===== Quantidade:");
		scanf("%d",&qtd_prod);
		
		sprintf(numero_venda, "%i", ncompra);//converte interio em string
		strcpy (open_carrinho, "dados\\reestoque");//define valor a string
		strcat (open_carrinho, numero_venda); // junta duas strings
		strcat (open_carrinho, txt); // junta duas strings
		
		
		compra_atual = fopen(open_carrinho,"a");
		fprintf(compra_atual,"%i\n",codigo[cod_prod-1]);
		fprintf(compra_atual,"%s\n",descricao_produto[cod_prod-1]);
		fprintf(compra_atual,"%i\n",qtd_prod);
		fprintf(compra_atual,"%f\n",preco_custo[cod_prod-1]);
		preco_total_compra_atual = qtd_prod*preco_custo[cod_prod-1];
		fprintf(compra_atual,"%f\n",preco_total_compra_atual);
		fclose(compra_atual);
		
		printf("===== Deseja adicionar mais produtos ao carrinho: ===================\n");
		printf("===== 1.Sim\n");
		printf("===== 2.Nao\n");
		do{
			scanf("%d", &op);
			switch(op){
				case 1:
					adicionar_produtos=1;
					repetir =0;
				break;
				case 2:
					adicionar_produtos=0;
					repetir =0;
				break;
				default:
					repetir =1;
			}
		}while(repetir==1);
		printf("=====================================================================\n");
	}
}

int entrada_de_produtos(){
	
	int cod_fornecedor,opcao,repetir,i,op,imprimir,produto_salvar,qtd_total=0,op_pagamento,forma_pagamento,dividir_fatura;
	int dia_fatura,mes_fatura,ano_fatura,dia_dividir,mes_dividir,ano_dividir;
	float frete,impostos,valor_nota=0,valor_prodts=0,frete_produto,imposto_produto,resto,pagar,entrada;
	char txt[5] = ".txt",numerodofornecedor[3],num[3],pag[3],numerodeprodutos[3],numero_venda[3],openfornecedor[23],open_carrinho[23],notinha[23],openproduto[23];
	char ql;
	int numero_linhas=0,alocar;
	int *codigo_fornecedor = malloc(sizeof(int));
	char *nome_fornecedor = malloc(50*sizeof(char));
	char *razaosocial_fornecedor = malloc(50*sizeof(char));
	char *email_fornecedor = malloc(50*sizeof(char));
	char *inscricaoestadual_fornecedor = malloc(17*sizeof(char));
	char *cnpj_fornecedor = malloc(17*sizeof(char));
	char *telefone_fornecedor = malloc(15*sizeof(char));
	char *UF_fornecedor = malloc(4*sizeof(char));
	char *bairro_fornecedor = malloc(35*sizeof(char));
	char *cidade_fornecedor = malloc(35*sizeof(char));
	char *rua_fornecedor = malloc(35*sizeof(char));
	char *numero_fornecedor = malloc(9*sizeof(char));
	
	
	
	int *codigo = malloc(numero_de_produtos*sizeof(int));
	int *estoque = malloc(numero_de_produtos*sizeof(int));
	int *estoque_minimo = malloc(numero_de_produtos*sizeof(int));
	float *preco_custo = malloc(numero_de_produtos*sizeof(float));
	float *preco_venda = malloc(numero_de_produtos*sizeof(float));
	char *descricao_produto[numero_de_produtos];
	
	FILE *forn,*compra_atual,*nota,*prod;
	
	for(i=0;i<numero_de_produtos;i++){//pega todos os produtos
		descricao_produto[i] = malloc(300*sizeof(char));
	
		sprintf(numerodeprodutos, "%i", i+1);//converte interio em string
		strcpy (openproduto, "dados\\produto");//define valor a string
		strcat (openproduto, numerodeprodutos); // junta duas strings
		strcat (openproduto, txt); // junta duas strings
		
		prod = fopen(openproduto,"r");
		if(prod != NULL){
			fscanf(prod,"%i\n",&codigo[i]);
			fscanf(prod,"\n%[^\n]s",descricao_produto[i]);
			fscanf(prod,"%i\n",&estoque[i]);
			fscanf(prod,"%i\n",&estoque_minimo[i]);
			fscanf(prod,"%f\n",&preco_custo[i]);
			fscanf(prod,"%f",&preco_venda[i]);
		}
		fclose(prod);
	}
	
	printf("=====================================================================\n");
	printf("====================== Entrada de produtos ==========================\n");
	printf("===== 1. Exibir Todos os fornecedores: ==============================\n");
	printf("===== 2. inserir codigo do fornecedor: ==============================\n");
	do{
		scanf("%d",&opcao);
		switch(opcao){
			case 1:
				exibirtodosfornecedores();
				repetir=0;
			break;
			case 2:
				repetir=0;
			break;
			default:
				printf("!Opcao Invalida!\nTente Novamene\n");
				repetir=1;
		}
	}while(repetir==1);
	printf("=====================================================================\n");
	printf("===== Insira o codigo do fornecedor:");
	do{
		repetir=1;
		scanf("%d",&cod_fornecedor);
		sprintf(numerodofornecedor, "%i", cod_fornecedor);//converte interio em string
		strcpy (openfornecedor, "dados\\fornecedor");//define valor a string
		strcat (openfornecedor, numerodofornecedor); // junta duas strings
		strcat (openfornecedor, txt); // junta duas strings
		
		forn = fopen(openfornecedor,"r");
		if (forn != NULL){
			fscanf(forn,"%i\n",&codigo_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",nome_fornecedor);
			fscanf(forn,"\n%[^\n]s",razaosocial_fornecedor);
			fscanf(forn,"\n%[^\n]s",email_fornecedor);
			fscanf(forn,"\n%[^\n]s",inscricaoestadual_fornecedor);
			fscanf(forn,"\n%[^\n]s",cnpj_fornecedor);
			fscanf(forn,"\n%[^\n]s",rua_fornecedor);
			fscanf(forn,"\n%[^\n]s",numero_fornecedor);
			fscanf(forn,"\n%[^\n]s",bairro_fornecedor);
			fscanf(forn,"\n%[^\n]s",cidade_fornecedor);
			fscanf(forn,"\n%[^\n]s",UF_fornecedor);
			fscanf(forn,"\n%[^\n]s",telefone_fornecedor);
			repetir=0;
		}else{
			printf("!Codigo de fornecedor Invalido!\nTente Novamente: ");
			repetir=1;
		}
		fclose(forn);
	}while(repetir==1);
	
	printf("=====================================================================\n");
	printf("===== Preco do frete:");
	scanf("%f",&frete);
	printf("=====================================================================\n");
	printf("===== Valor dos Impostos cobrados:");
	scanf("%f",&impostos);
	printf("=====================================================================\n");
	historico_de_compras=historico_de_compras+1;
	
	FILE *compras;
	compras = fopen("dados\\Ncompras.txt","w");
	fprintf(compras,"%i",historico_de_compras);
	fclose(compras);
	
	compra(historico_de_compras);
	//
	
	sprintf(numero_venda, "%i", historico_de_compras);//converte interio em string
	strcpy (open_carrinho, "dados\\reestoque");//define valor a string
	strcat (open_carrinho, numero_venda); // junta duas strings
	strcat (open_carrinho, txt); // junta duas strings
	
	compra_atual = fopen(open_carrinho,"r");
	while((ql = fgetc(compra_atual)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(compra_atual);
	
	alocar=numero_linhas/5;
	
	int *codigo_produto_comprado = malloc(alocar*sizeof(int));
	int *qtd_prod_comprado = malloc(alocar*sizeof(int));
	
	float *preco_custo_comprado = malloc(alocar*sizeof(float));
	float *preco_total_comprado = malloc(alocar*sizeof(float));
	
	char *descricao_produto_comprado[alocar];
	
	//notinha
	printf("=====================================================================\n");
	printf("=== Fornecedor: %s\n",nome_fornecedor);
	printf("=== CNPJ: %s\n",cnpj_fornecedor);
	printf("=== Frete: %.2f \t\t\t\t Impostos: %.2f\n",frete,impostos);
	printf("============================ Produtos ===============================\n");
	printf("Produto \t\t Preco de Custo \t Quantidade \t Total\n");
	compra_atual = fopen(open_carrinho,"r");
	for(i=0;i<alocar;i++){
		descricao_produto[i] = malloc(100*sizeof(char));
		fscanf(compra_atual,"%d",&codigo_produto_comprado[i]);
		fscanf(compra_atual,"\n%[^\n]s",descricao_produto_comprado[i]);
		fscanf(compra_atual,"%d",&qtd_prod_comprado[i]);
		fscanf(compra_atual,"%f",&preco_custo_comprado[i]);
		fscanf(compra_atual,"%f",&preco_total_comprado[i]);
		valor_prodts = valor_prodts+preco_total_comprado[i];
		qtd_total = qtd_total+qtd_prod_comprado[i];
		printf("%-20s \t R$% 8.2f \t\t %5d \t\t R$% 5.2f\n",descricao_produto_comprado[i],preco_custo_comprado[i],qtd_prod_comprado[i],preco_total_comprado[i]);	
	}
	fclose(compra_atual);
	printf("=====================================================================\n");

	valor_nota = valor_prodts+frete+impostos;
	printf("=== Total da nota (produtos + frete + impostos):\t\t R$ %.2f\n",valor_nota);
	printf("=====================================================================\n");
	//fim da notinha
	
	frete_produto = frete/qtd_total;
	imposto_produto = impostos/qtd_total;
	
	for(i=0;i<alocar;i++){//atualiza o produto
		produto_salvar=codigo_produto_comprado[i];
		sprintf(numerodeprodutos, "%i", produto_salvar);//converte interio em string
		strcpy (openproduto, "dados\\produto");//define valor a string
		
		strcat (openproduto, numerodeprodutos); // junta duas strings
		strcat (openproduto, txt); // junta duas strings
		
		prod = fopen(openproduto,"w");
		fprintf(prod,"%i\n",codigo[produto_salvar-1]);
		fprintf(prod,"%s\n",descricao_produto[produto_salvar-1]);
		
		estoque[produto_salvar-1] = estoque[produto_salvar-1] + qtd_prod_comprado[i];
		fprintf(prod,"%i\n",estoque[produto_salvar-1]);
		fprintf(prod,"%i\n",estoque_minimo[produto_salvar-1]);
		fprintf(prod,"%f\n",preco_custo[produto_salvar-1]);
		preco_venda[produto_salvar-1] = preco_custo[produto_salvar-1] + frete_produto + imposto_produto + ((margemlucro/100)*preco_custo[produto_salvar-1]);
		fprintf(prod,"%f",preco_venda[produto_salvar-1]);
		fclose(prod);
	}
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	printf("Deseja Imprimir em arquivo esta nota?\n");
	printf("1.Sim \t\t 2. Nao\n");
	do{
		scanf("%d",&op);
		switch(op){
			case 1:
				imprimir=1;
				repetir=0;
			break;
			case 2:
				imprimir=0;
				repetir=0;
			break;
			default:
				repetir=1;
		}
	}while(repetir==1);
	
	//salvar historico
	sprintf(numero_venda, "%i", historico_de_compras);//converte interio em string
	strcpy (notinha, "dados\\nota");//define valor a string
	strcat (notinha, numero_venda); // junta duas strings
	strcat (notinha, txt); // junta duas strings
	
	nota = fopen(notinha,"w");
	fprintf(nota,"=====================================================================\n");
	fprintf(nota,"=== Fornecedor: %s\n",nome_fornecedor);
	fprintf(nota,"=== CNPJ: %s\n",cnpj_fornecedor);
	fprintf(nota,"=== Frete: %.2f \t\t\t\t Impostos: %.2f\n",frete,impostos);
	fprintf(nota,"============================ Produtos ===============================\n");
	fprintf(nota,"Produto \t\t Preco de Custo \t Quantidade \t Total\n");
	for(i=0;i<alocar;i++){
		fprintf(nota,"%-20s \t R$% 8.2f \t\t %5d \t\t R$% 5.2f\n",descricao_produto_comprado[i],preco_custo_comprado[i],qtd_prod_comprado[i],preco_total_comprado[i]);	
	}
	fprintf(nota,"=====================================================================\n");
	fprintf(nota,"=== Total da nota (produtos + frete + impostos):\t\t R$ %.2f\n",valor_nota);
	fprintf(nota,"=====================================================================\n");
	fclose(nota);
	
	printf("=====================================================================\n");
	printf("============================ Pagamento ==============================\n");
	printf("=====================================================================\n");
	printf("===== Total das Contas: R$ %.2f \n",valor_nota);
	printf("===== Valor em caixa: R$ %.2f \n",caixa);
	printf("=====================================================================\n");
	
	
	resto = caixa-valor_nota;
	if(resto <= 0){
		printf("Valor em caixa insuficiente para pagar esta transacao a vista\n");
		op_pagamento=2;
	}
	else{
		printf("===== 1. Realizar Pagamento agora ===================================\n");
		printf("===== 2. Realizar Pagamento a prazo =================================\n");
		do{
			scanf("%d",&op_pagamento);
			switch(op_pagamento){
				case 1:
					repetir=0;
				break;
				case 2:
					repetir=0;
				break;
				default:
					repetir=1;
			}
		}while(repetir==1);
	}

	if(op_pagamento==1){
		printf("=====================================================================\n");
		printf("===== Forma de pagamento: ===========================================\n");
		printf("===== 1. Dinheiro ===================================================\n");
		printf("===== 2. Cartão =====================================================\n");
		printf("=====================================================================\n");
		do{
			scanf("%d",&forma_pagamento);
			switch(forma_pagamento){
				case 1:
					repetir=0;
				break;
				case 2:
					repetir=0;
				break;
				default:
					printf("!Opcao Invalida!\nTente Novamente:");
					repetir=1;
			}
		}while(repetir==1);
		if(forma_pagamento==1){
			caixa = caixa - valor_nota;
			FILE *caixa_Hotel;
			caixa_Hotel = fopen("dados\\caixa.txt","w");
			fprintf(caixa_Hotel,"%f",caixa);
			fclose(caixa_Hotel);
			
			printf("===== Pagamento efetuado com sucesso ================================\n");
			printf("=====================================================================\n");
			
			FILE *historico_mes;
			historico_mes = fopen("dados\\Historico mes.txt","a");
			fprintf(historico_mes,"Pagamento em dinheiro do reestoque: %d\n",historico_de_compras);
			fprintf(historico_mes,"%f\n",0-valor_nota);
			fprintf(historico_mes,"%f\n",caixa);
			fprintf(historico_mes,"%d\n%d\n%d\n",dia,mes,ano);
			fclose(historico_mes);
			
			FILE *historico_completo;
			historico_completo = fopen("dados\\Historico completo.txt","a");
			fprintf(historico_completo,"Pagamento em dinheiro do reestoque: %d\n",historico_de_compras);
			fprintf(historico_completo,"%f\n",0-valor_nota);
			fprintf(historico_completo,"%f\n",caixa);
			fprintf(historico_completo,"%d/%d/%d\n",dia,mes,ano);
			fclose(historico_completo);
		}
		else{
			char descricao[300];
			printf("=====================================================================\n");
			printf("===== quantidade de veses para dividir: (ate 12 vezes) ==============\n");
			do{
				scanf("%d",&dividir_fatura);
				if((dividir_fatura <=0) || (dividir_fatura >12)){
					repetir=1;
				}else{
					repetir=0;
				}
			}while(repetir==1);
			
			printf("=====================================================================\n");
			printf("===== Informe a dia de fatura do cartao: ============================\n");
			scanf("%d",&dia_fatura);
			
			dia_dividir = dia;
			mes_dividir = mes;
			ano_dividir = ano;
			
			if(dia_fatura > dia_dividir){
				mes_fatura = mes_dividir;
				ano_fatura = ano_dividir;
			}else{
				mes_fatura = mes_dividir+1;
				ano_fatura = ano_dividir;
				if (mes_fatura>12){
					mes_fatura=1;
					ano_fatura = ano_dividir+1;
				}
			}

			repetir=1;
			pagar = valor_nota/dividir_fatura;
			while(repetir<=dividir_fatura){
				
				
				strcpy (descricao, "Pagamento ");//define valor a string
				sprintf(pag, "%i", repetir);//converte interio em string
				strcat (descricao, pag); // junta duas strings
				strcat (descricao, " de "); // junta duas strings
				sprintf(pag, "%i", dividir_fatura);//converte interio em string
				strcat (descricao, pag); // junta duas strings
				strcat (descricao, " no cartao do reestoque: "); // junta duas strings
				sprintf(num, "%i", historico_de_compras);//converte interio em string
				strcat (descricao, num); // junta duas strings
				
				
				adicionar_contas_pagar(dia_fatura,mes_fatura,ano_fatura, pagar,descricao);
				
				repetir++;
				
				mes_fatura++;
				if (mes_fatura>12){
					mes_fatura=1;
					ano_fatura++;
				}
			}
			
			printf("=====================================================================\n");
			printf("===== Pagamento efetuado com sucesso ================================\n");
			printf("=====================================================================\n");
		}
	}else{
		printf("=====================================================================\n");
		printf("===== Pagar valor de entrada ========================================\n");
		printf("===== 1. Sim =========== 2. Nao =====================================\n");
		do{
			scanf("%d",&op);
			switch(op){
				case 1:
					repetir=0;
				break;
				case 2:
					repetir=0;
				break;
				default:
					repetir=1;
			}
		}while(repetir==1);
		
		printf("=====================================================================\n");
		pagar=valor_nota;
		if(op==1){
			printf("===== Total a pagar: %2.f\n",pagar);
			printf("===== Valor em caixa: R$ %.2f \n",caixa);
			printf("===== Digite o valor da entrada, ate metade do valor total: ");
			do{
				repetir=0;
				scanf("%f",&entrada);
				if(entrada >valor_nota/2){
					printf("!Valor Muito auto, tente novamente!\n");
					repetir=1;
				}
				if(entrada >= caixa){
					printf("!Valor Muito auto, tente novamente!\n");
					repetir=1;
				}
			}while(repetir==1);
			caixa = caixa - entrada;
			FILE *caixa_Hotel;
			caixa_Hotel = fopen("dados\\caixa.txt","w");
			fprintf(caixa_Hotel,"%f",caixa);
			fclose(caixa_Hotel);
			pagar=pagar-entrada;
		}
		
		printf("===== Total a pagar: %2.f\n",pagar);
		printf("=====================================================================\n");
		char descricao[300];
		printf("=====================================================================\n");
		printf("===== quantidade de veses para dividir: (ate 12 vezes) ==============\n");
		do{
			scanf("%d",&dividir_fatura);
			if((dividir_fatura <=0) || (dividir_fatura >12)){
				repetir=1;
			}else{
				repetir=0;
			}
		}while(repetir==1);
		
		printf("=====================================================================\n");
		printf("===== Informe o ano de inicio do pagamento: =========================\n");
		scanf("%d",&ano_fatura);
		printf("===== Informe o mes de inicio do pagamento: =========================\n");
		scanf("%d",&mes_fatura);
		printf("===== Informe o dia de inicio do pagamento: =========================\n");
		scanf("%d",&dia_fatura);
		
		repetir=1;
		pagar = pagar/dividir_fatura;
		while(repetir<=dividir_fatura){
			
			strcpy (descricao, "Pagamento ");//define valor a string
			sprintf(pag, "%i", repetir);//converte interio em string
			strcat (descricao, pag); // junta duas strings
			strcat (descricao, " de "); // junta duas strings
			sprintf(pag, "%i", dividir_fatura);//converte interio em string
			strcat (descricao, pag); // junta duas strings
			strcat (descricao, " dividido do reestoque: "); // junta duas strings
			sprintf(num, "%i", historico_de_compras);//converte interio em string
			strcat (descricao, num); // junta duas strings
			adicionar_contas_pagar(dia_fatura,mes_fatura,ano_fatura, pagar,descricao);
			
			repetir++;
			mes_fatura++;
			if (mes_fatura>12){
				mes_fatura=1;
				ano_fatura++;
			}
		}
		printf("=====================================================================\n");
		printf("===== Pagamento efetuado com sucesso ================================\n");
		printf("=====================================================================\n");
	}
	
	//imprimir para o usuario
	if(imprimir==1){
		sprintf(numero_venda, "%i", historico_de_compras);//converte interio em string
		strcpy (notinha, "Nota da Compra ");//define valor a string
		strcat (notinha, numero_venda); // junta duas strings
		strcat (notinha, txt); // junta duas strings
		
		nota = fopen(notinha,"w");
		fprintf(nota,"=====================================================================\n");
		fprintf(nota,"=== Fornecedor: %s\n",nome_fornecedor);
		fprintf(nota,"=== CNPJ: %s\n",cnpj_fornecedor);
		fprintf(nota,"=== Frete: %.2f \t\t\t\t Impostos: %.2f\n",frete,impostos);
		fprintf(nota,"============================ Produtos ===============================\n");
		fprintf(nota,"Produto \t\t Preco de Custo \t Quantidade \t Total\n");
		for(i=0;i<alocar;i++){
			fprintf(nota,"%-20s \t R$% 8.2f \t\t %5d \t\t R$% 5.2f\n",descricao_produto_comprado[i],preco_custo_comprado[i],qtd_prod_comprado[i],preco_total_comprado[i]);	
		}
		fprintf(nota,"=====================================================================\n");
		fprintf(nota,"=== Total da nota (produtos + frete + impostos):\t\t R$ %.2f\n",valor_nota);
		fprintf(nota,"=====================================================================\n");
		fclose(nota);
	}
	
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
}

///////////////////////////////
int Historico_contas(){
	char ql;
	int numero_linhas=0,alocar,i;
	FILE *contas;
	
	contas = fopen("dados\\Historico recibos.txt","r");
	while((ql = fgetc(contas)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(contas);

	alocar=numero_linhas/3;
	
	char *data[alocar];
	float *valor = malloc(alocar*sizeof(float));
	char *descricao[alocar];

	contas = fopen("dados\\Historico recibos.txt","r");
	
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		data[i] = malloc(11*sizeof(char));
		
		fscanf(contas,"\n%[^\n]s",descricao[i]);
		fscanf(contas,"%f\n",&valor[i]);
		fscanf(contas,"\n%[^\n]s",data[i]);
		
		
		printf("Descricao: %s\n",descricao[i]);
		printf("Valor: %.2f\n",valor[i]);
		printf("Data: %s\n",data[i]);
		printf("=====================================================================\n");
	}
	fclose(contas);
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
}

int historico_mes(){
	char ql;
	int numero_linhas=0,alocar,i;
	FILE *historico_mes;
	
	historico_mes = fopen("dados\\Historico mes.txt","r");
	while((ql = fgetc(historico_mes)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(historico_mes);

	alocar=numero_linhas/6;
	
	char *descricao[alocar];
	int *dia_entrada = malloc(alocar*sizeof(int));
	int *mes_entrada = malloc(alocar*sizeof(int));
	int *ano_entrada = malloc(alocar*sizeof(int));
	int *exibir = malloc(alocar*sizeof(int));
	float *entrada = malloc(alocar*sizeof(float));
	float *caixa = malloc(alocar*sizeof(float));

	historico_mes = fopen("dados\\Historico mes.txt","r");
	
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		exibir[i]=0;
		fscanf(historico_mes,"\n%[^\n]s",descricao[i]);
		fscanf(historico_mes,"%f\n",&entrada[i]);
		fscanf(historico_mes,"%f\n",&caixa[i]);		
		fscanf(historico_mes,"%i\n",&dia_entrada[i]);
		fscanf(historico_mes,"%i\n",&mes_entrada[i]);
		fscanf(historico_mes,"%i\n",&ano_entrada[i]);
		
		if(ano_entrada[i] ==ano){
			if(mes_entrada[i]+1 == mes){
				if(dia_entrada[i] < dia){
					exibir[i]=0;
				}else if(dia_entrada[i] >= dia){
					exibir[i]=1;
				}
			}else if (mes_entrada[i] == mes){
				exibir[i]=1;
			}else{
				exibir[i]=0;
			}
		}else if(ano_entrada[i]+1 == ano){
			if((mes_entrada[i]==12) && (mes ==1)){
				if(dia_entrada[i] < dia){
					exibir[i]=0;
				}else if(dia_entrada[i] >= dia){
					exibir[i]=1;
				}
			}else{
				exibir[i]=0;
			}
			
		}
		
		if(exibir[i] ==1){
			printf("Descricao: %s\n",descricao[i]);
			printf("Valor: %.2f\n",entrada[i]);
			printf("Caixa apos essa operacao: %.2f\n",caixa[i]);
			printf("Data: %i/%i/%i\n",dia_entrada[i],mes_entrada[i],ano_entrada[i]);
			printf("=====================================================================\n");
		}
	}
	fclose(historico_mes);
	historico_mes = fopen("dados\\Historico mes.txt","w");
	for(i=0;i<alocar;i++){
		if(exibir[i] ==1){
			fprintf(historico_mes,"%s\n",descricao[i]);
			fprintf(historico_mes,"%f\n",entrada[i]);
			fprintf(historico_mes,"%f\n",caixa[i]);		
			fprintf(historico_mes,"%i\n",dia_entrada[i]);
			fprintf(historico_mes,"%i\n",mes_entrada[i]);
			fprintf(historico_mes,"%i\n",ano_entrada[i]);
		}
	}
	fclose(historico_mes);			
}

int checar_contas_receber(){
	
	char ql;
	int numero_linhas=0,alocar,i;
	FILE *contas;
	
	contas = fopen("dados\\contas.txt","r");
	while((ql = fgetc(contas)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(contas);

	alocar=numero_linhas/5;
	
	int *dia_receber = malloc(alocar*sizeof(int));
	int *mes_receber = malloc(alocar*sizeof(int));
	int *ano_receber = malloc(alocar*sizeof(int));
	float *valor = malloc(alocar*sizeof(float));
	char *descricao[alocar];

	contas = fopen("dados\\contas.txt","r");
	
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		
		fscanf(contas,"%d\n",&dia_receber[i]);
		fscanf(contas,"%d\n",&mes_receber[i]);
		fscanf(contas,"%d\n",&ano_receber[i]);
		fscanf(contas,"%f\n",&valor[i]);
		fscanf(contas,"\n%[^\n]s",descricao[i]);

		
		printf("Descricao: %s\n",descricao[i]);
		printf("Valor: %.2f\n",valor[i]);
		printf("Data: %d/%d/%d\n",dia_receber[i],mes_receber[i],ano_receber[i]);
		printf("=====================================================================\n");
	}
	fclose(contas);	
}

int checar_contas_pagar(){
	
	char ql;
	int numero_linhas=0,alocar,i;
	FILE *contas;
	
	contas = fopen("dados\\pagar.txt","r");
	while((ql = fgetc(contas)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(contas);

	alocar=numero_linhas/5;
	
	int *dia_receber = malloc(alocar*sizeof(int));
	int *mes_receber = malloc(alocar*sizeof(int));
	int *ano_receber = malloc(alocar*sizeof(int));
	float *valor = malloc(alocar*sizeof(float));
	char *descricao[alocar];

	contas = fopen("dados\\pagar.txt","r");
	
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		
		fscanf(contas,"%d\n",&dia_receber[i]);
		fscanf(contas,"%d\n",&mes_receber[i]);
		fscanf(contas,"%d\n",&ano_receber[i]);
		fscanf(contas,"%f\n",&valor[i]);
		fscanf(contas,"\n%[^\n]s",descricao[i]);

		
		printf("Descricao: %s\n",descricao[i]);
		printf("Valor: %.2f\n",valor[i]);
		printf("Data: %d/%d/%d\n",dia_receber[i],mes_receber[i],ano_receber[i]);
		printf("=====================================================================\n");
	}
	fclose(contas);	
}

int historico_completo(){
	
	char ql;
	int numero_linhas=0,alocar,i;
	FILE *historico;
	
	historico = fopen("dados\\Historico completo.txt","r");
	while((ql = fgetc(historico)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(historico);

	alocar=numero_linhas/4;
	
	char *descricao[alocar];
	char *data[alocar];
	float *entrada = malloc(alocar*sizeof(float));
	float *caixa = malloc(alocar*sizeof(float));

	historico = fopen("dados\\Historico completo.txt","r");
	
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		data[i] = malloc(11*sizeof(char));
		
		fscanf(historico,"\n%[^\n]s",descricao[i]);
		fscanf(historico,"%f\n",&entrada[i]);
		fscanf(historico,"%f\n",&caixa[i]);
		fscanf(historico,"%[^\n]s",data[i]);
		
		printf("Descricao: %s\n",descricao[i]);
		printf("Valor: %.2f\n",entrada[i]);
		printf("Caixa apos essa operacao: %.2f\n",caixa[i]);
		printf("Data: %s\n",data[i]);
		printf("=====================================================================\n");
	}
	fclose(historico);				

}

int historico_contas_pagas(){
	char ql;
	int numero_linhas=0,alocar,i;
	FILE *historico;
	
	historico = fopen("dados\\Historico pagamentos.txt","r");
	while((ql = fgetc(historico)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(historico);

	alocar=numero_linhas/3;
	
	char *descricao[alocar];
	char *data[alocar];
	float *entrada = malloc(alocar*sizeof(float));

	historico = fopen("dados\\Historico pagamentos.txt","r");
	
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		data[i] = malloc(11*sizeof(char));
		
		fscanf(historico,"\n%[^\n]s",descricao[i]);
		fscanf(historico,"%f\n",&entrada[i]);
		fscanf(historico,"%[^\n]s",data[i]);
		
		printf("Descricao: %s\n",descricao[i]);
		printf("Valor: %.2f\n",entrada[i]);
		printf("Data: %s\n",data[i]);
		printf("=====================================================================\n");
	}
	fclose(historico);	
}

int historico_contas_pagas_mes(){
	char ql;
	int numero_linhas=0,alocar,i;
	FILE *historico_mes;
	
	historico_mes = fopen("dados\\Historico pagamentos mes.txt","r");
	while((ql = fgetc(historico_mes)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(historico_mes);

	alocar=numero_linhas/5;
	
	char *descricao[alocar];
	int *dia_entrada = malloc(alocar*sizeof(int));
	int *mes_entrada = malloc(alocar*sizeof(int));
	int *ano_entrada = malloc(alocar*sizeof(int));
	int *exibir = malloc(alocar*sizeof(int));
	float *entrada = malloc(alocar*sizeof(float));

	historico_mes = fopen("dados\\Historico pagamentos mes.txt","r");
	
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		fscanf(historico_mes,"\n%[^\n]s",descricao[i]);
		fscanf(historico_mes,"%f\n",&entrada[i]);	
		fscanf(historico_mes,"%i\n",&dia_entrada[i]);
		fscanf(historico_mes,"%i\n",&mes_entrada[i]);
		fscanf(historico_mes,"%i\n",&ano_entrada[i]);
		
		if(ano_entrada[i] ==ano){
			if(mes_entrada[i]+1 == mes){
				if(dia_entrada[i] < dia){
					exibir[i]=0;
				}else if(dia_entrada[i] >= dia){
					exibir[i]=1;
				}
			}else if (mes_entrada[i] == mes){
				exibir[i]=1;
			}else{
				exibir[i]=0;
			}
		}else if(ano_entrada[i]+1 == ano){
			if((mes_entrada[i]==12) && (mes ==1)){
				if(dia_entrada[i] < dia){
					exibir[i]=0;
				}else if(dia_entrada[i] >= dia){
					exibir[i]=1;
				}
			}else{
				exibir[i]=0;
			}
			
		}
		
		if(exibir[i] ==1){
			printf("Descricao: %s\n",descricao[i]);
			printf("Valor: %.2f\n",entrada[i]);
			printf("Data: %i/%i/%i\n",dia_entrada[i],mes_entrada[i],ano_entrada[i]);
			printf("=====================================================================\n");
		}
	}
	fclose(historico_mes);
	
	historico_mes = fopen("dados\\Historico pagamentos mes.txt","w");
	for(i=0;i<alocar;i++){
		if(exibir[i] ==1){
			fprintf(historico_mes,"%s\n",descricao[i]);
			fprintf(historico_mes,"%f\n",entrada[i]);	
			fprintf(historico_mes,"%i\n",dia_entrada[i]);
			fprintf(historico_mes,"%i\n",mes_entrada[i]);
			fprintf(historico_mes,"%i\n",ano_entrada[i]);
		}
	}
	fclose(historico_mes);	
}

int controle_caixa(){

	int op;
	
	printf("=====================================================================\n");
	printf("======================== Controle de Caixa ==========================\n");
	printf("=====================================================================\n");
	printf("===== Caixa do hotel: R$%.2f\n",caixa);
	printf("=====================================================================\n");
	printf("===== 1. Historico do caixa (Ultimo mes) ============================\n");
	printf("===== 2. Historico do caixa (total) =================================\n");
	printf("===== 3. Contas a receber (pagos pelo cartao) =======================\n");
	printf("===== 4. Historico de contas recebidas ==============================\n");
	printf("===== 5. Contas a pagar =============================================\n");
	printf("===== 6. Historico de Contas pagas (Total) ==========================\n");
	printf("===== 7. Historico de Contas pagas (Ultimo Mes) =====================\n");
	printf("===== 8. Voltar =====================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op);
	switch(op){
		case 1:
			historico_mes();
		break;
		case 2:
			historico_completo();
		break;
		case 3:
			checar_contas_receber();
		break;
		case 4:
			Historico_contas();
		break;
		case 5:
			checar_contas_pagar();
		break;
		case 6:
			historico_contas_pagas();
		break;
		case 7:
			historico_contas_pagas_mes();
		break;
		case 8:
			modulo_transacoes();
		break;
		default:
			controle_caixa();
	}
	controle_caixa();
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
}
/////////////////////////////
int carrinho(int ncarrinho){//erradao
	
	FILE *carrinho,*prod,*compra_atual;
	char numero_venda[3],open_carrinho[23],txt[5] = ".txt";
	int cod_prod,qtd_prod,adicionar_produtos;
	
	int *codigo = malloc(numero_de_produtos*sizeof(int));
	int *estoque = malloc(numero_de_produtos*sizeof(int));
	int *estoque_minimo = malloc(numero_de_produtos*sizeof(int));
	
	float *preco_custo = malloc(numero_de_produtos*sizeof(float));
	float *preco_venda = malloc(numero_de_produtos*sizeof(float));
	
	char *descricao_produto[numero_de_produtos];

	int i,continuar=0,op,repetir,j;
	float preco_total_compra_atual,preco_total=0;
	
	char ql;
	int numero_linhas=0;

	char numerodeprodutos[3];
	char openproduto[23];
	
	for(i=0;i<numero_de_produtos;i++){
		descricao_produto[i] = malloc(300*sizeof(char));
	
		sprintf(numerodeprodutos, "%i", i+1);//converte interio em string
		strcpy (openproduto, "dados\\produto");//define valor a string
		
		strcat (openproduto, numerodeprodutos); // junta duas strings
		strcat (openproduto, txt); // junta duas strings
		
		prod = fopen(openproduto,"r");
		
		fscanf(prod,"%i\n",&codigo[i]);
		fscanf(prod,"\n%[^\n]s",descricao_produto[i]);
		fscanf(prod,"%i",&estoque[i]);
		fscanf(prod,"%i",&estoque_minimo[i]);
		fscanf(prod,"%f",&preco_custo[i]);
		fscanf(prod,"%f",&preco_venda[i]);
		
		fclose(prod);
	}
	sprintf(numero_venda, "%i", ncarrinho);//converte interio em string
	strcpy (open_carrinho, "dados\\compra");//define valor a string
	strcat (open_carrinho, numero_venda); // junta duas strings
	strcat (open_carrinho, txt); // junta duas strings
	
	printf("================== Adicionar produtos ao carrinho ===================\n");
	adicionar_produtos=1;
	
	carrinho = fopen(open_carrinho,"r");
	while((ql = fgetc(carrinho)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(carrinho);
	
	int *codigo_ver = malloc((numero_linhas)*sizeof(int));
	int *qtd_prod_ver= malloc((numero_linhas/4)*sizeof(int));
	float *preco_ver= malloc((numero_linhas/4)*sizeof(float));
	char *descricao_produto_ver[numero_linhas/4];

	carrinho = fopen(open_carrinho,"r");
	if(numero_linhas>=4){
		for(j=0;j<(numero_linhas/4);j++){
			descricao_produto_ver[j]= malloc(70*sizeof(char));
			
			fscanf(carrinho,"%i\n",&codigo_ver[j]);
			fscanf(carrinho,"\n%[^\n]s",descricao_produto_ver[j]);
			fscanf(carrinho,"%i\n",&qtd_prod_ver[j]);
			fscanf(carrinho,"%f",&preco_ver[j]);
		}
	}
	fclose(carrinho);

	while(adicionar_produtos ==1){
		do{
			printf("===== Insira o codigo do produto no carrinho: =======================\n");
			scanf("%d",&cod_prod);
			sprintf(numerodeprodutos, "%i", cod_prod);//converte interio em string
			strcpy (openproduto, "dados\\produto");//define valor a string
			strcat (openproduto, numerodeprodutos); // junta duas strings
			strcat (openproduto, txt); // junta duas strings
			prod = fopen(openproduto,"r");
			if (prod != NULL){
				printf("Codigo: %d\n",codigo[cod_prod-1]);
				printf("Descricao: %s\n",descricao_produto[cod_prod-1]);
				printf("Estoque: %d\n",estoque[cod_prod-1]);
				printf("Preco: %.2f\n",preco_venda[cod_prod-1]);
				continuar =1;
			}else{
				printf("!Codigo Invalido!\n");
				continuar=0;
			}
		}while(continuar==0);
		continuar =0;
		
		while(continuar==0){
			printf("===== Quantidade:");
			scanf("%d",&qtd_prod);
			
			if (qtd_prod > estoque[cod_prod-1]){
				printf("!Nao possui estoque suficiente!\n");
				continuar =0;
			}else{
				continuar=1;
			}
		}
		
		sprintf(numerodeprodutos, "%i", cod_prod);//converte interio em string
		strcpy (openproduto, "dados\\produto");//define valor a string
		
		strcat (openproduto, numerodeprodutos); // junta duas strings
		strcat (openproduto, txt); // junta duas strings
		
		prod = fopen(openproduto,"w");
		fprintf(prod,"%i\n",codigo[cod_prod-1]);
		fprintf(prod,"%s\n",descricao_produto[cod_prod-1]);
		estoque[cod_prod-1] = estoque[cod_prod-1]- qtd_prod;
		fprintf(prod,"%i\n",estoque[cod_prod-1]);
		fprintf(prod,"%i\n",estoque_minimo[cod_prod-1]);
		fprintf(prod,"%f\n",preco_custo[cod_prod-1]);
		fprintf(prod,"%f",preco_venda[cod_prod-1]);
		fclose(prod);
		
		compra_atual = fopen("dados\\compraatual.txt","a");
		fprintf(compra_atual,"%i\n",codigo[cod_prod-1]);
		fprintf(compra_atual,"%s\n",descricao_produto_ver[cod_prod-1]);
		fprintf(compra_atual,"%i\n",qtd_prod);
		preco_total_compra_atual = qtd_prod*preco_venda[cod_prod-1];
		fprintf(compra_atual,"%f\n",preco_total_compra_atual);
		fclose(compra_atual);
		
		if (estoque[cod_prod-1] <=estoque_minimo[cod_prod-1]){
			FILE *produtos_falta;
			produtos_falta = fopen("dados\\produtos_em_falta.txt","a");
			fprintf(produtos_falta,"\n%i",codigo[cod_prod-1]);
			fclose(produtos_falta);
		}
		printf("===== Valor desta Compra: %.2f \n",preco_total_compra_atual);
		preco_total = preco_total+preco_total_compra_atual;
		printf("===== Valor total Total: %.2f \n",preco_total);
		printf("===== Deseja adicionar mais produtos ao carrinho: ===================\n");
		printf("===== 1.Sim\n");
		printf("===== 2.Nao\n");
		do{
			scanf("%d", &op);
			switch(op){
				case 1:
					adicionar_produtos=1;
					repetir =0;
				break;
				case 2:
					adicionar_produtos=0;
					repetir =0;
				break;
				default:
					repetir =1;
			}
		}while(repetir==1);
		printf("=====================================================================\n");
	}
	return(preco_total);
}

int vendas(){//acho q ta pronto

	int i,j,reserva_check,opcao, ncarrinho,continuar,op_pagamento,forma_pagamento,dia_fatura,mes_fatura,ano_fatura;
	float total=0,comprinha=0,total_pagar=0;
	//reserva
	FILE *open_reservas,*hosp,*carr,*compra_atual;
	int *codigo_reserva = malloc(numero_reservas*sizeof(int));
	int *dia_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *dias_reservado = malloc(numero_reservas*sizeof(int));
	int *dia_final_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_final_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_final_reserva = malloc(numero_reservas*sizeof(int));
	int *quarto_reservado = malloc(numero_reservas*sizeof(int));
	int *codhosp_reserva = malloc(numero_reservas*sizeof(int));
	int *situacao = malloc(numero_reservas*sizeof(int));
	float *totaldiarias = malloc(numero_reservas*sizeof(float));
	float *valor_contas = malloc(numero_reservas*sizeof(float));
	
	char numero_reserva[3],openreserva[23];
	char numero_venda[3],open_carrinho[23],ql;
	int numero_linhas=0;
	
	compra_atual = fopen("dados\\compraatual.txt","w");
	fclose(compra_atual);
	
	//hospede
	char *nome_hospede[numero_reservas];
	int *codigo_hospede= malloc(numero_reservas*sizeof(int));
	char numerodohospede[3],num_acomodacao[3],openhospede[23],numtipacomodacao[3],txt[5] = ".txt";
	
	for(i=0;i<numero_reservas;i++){//pega os dados das reservas ja efetuadas
		nome_hospede[i] = malloc(40*sizeof(char));

		//reserva
		sprintf(numero_reserva, "%i", i+1);//converte interio em string
		strcpy (openreserva, "dados\\reserva");//define valor a string
		strcat (openreserva, numero_reserva); // junta duas strings
		strcat (openreserva, txt); // junta duas strings
		
		open_reservas = fopen(openreserva,"r");
		
		fscanf(open_reservas,"%i",&codigo_reserva[i]);
		fscanf(open_reservas,"%i",&dia_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&mes_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&ano_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&dias_reservado[i]);
		fscanf(open_reservas,"%i",&dia_final_reserva[i]);
		fscanf(open_reservas,"%i",&mes_final_reserva[i]);
		fscanf(open_reservas,"%i",&ano_final_reserva[i]);
		fscanf(open_reservas,"%i",&quarto_reservado[i]);
		fscanf(open_reservas,"%i",&codhosp_reserva[i]);
		fscanf(open_reservas,"%i",&situacao[i]);
		fscanf(open_reservas,"%f",&totaldiarias[i]);
		fscanf(open_reservas,"%f",&valor_contas[i]);

		fclose(open_reservas);
		
		//hospede
		sprintf(numerodohospede, "%i", codhosp_reserva[i]);//converte interio em string
		strcpy (openhospede, "dados\\hospede");//define valor a string
		
		strcat (openhospede, numerodohospede); // junta duas strings
		strcat (openhospede, txt); // junta duas strings
		
		hosp = fopen(openhospede,"r");
		
		fscanf(hosp,"%i\n",&codigo_hospede[i]);
		fscanf(hosp,"\n%[^\n]s",nome_hospede[i]);
		fclose(hosp);
	}
	
	printf("=====================================================================\n");
	printf("============================== Vendas ===============================\n");
	printf("=====================================================================\n");
	printf("========================== Reservas Ativas ==========================\n");
	for(i=0;i<numero_reservas;i++){
		if (situacao[i] ==2){
			printf("=====================================================================\n");
			printf("Codigo da reserva: %d\n",codigo_reserva[i]);
			printf("Data de Inicio da reserva: %d/%d/%d\n",dia_inicio_reserva[i],mes_inicio_reserva[i],ano_inicio_reserva[i]);
			printf("Ficara %d dias reservado\n",dias_reservado[i]);
			printf("Data do Fim da reserva: %d/%d/%d\n",dia_final_reserva[i],mes_final_reserva[i],ano_final_reserva[i]);
			printf("Quarto Reservado: %d\n",quarto_reservado[i]);
			printf("Hospede que reservou o quarto: %s\n",nome_hospede[i]);
			printf("Status da reserva: ATIVA\n");
			printf("=====================================================================\n");
		}
	}
	printf("====== Digite o codigo da reserva que deseja realizar o Compras =====\n");
	scanf("%d",&reserva_check);
	
	ncarrinho = reserva_check;
	continuar =0;
	
	do{
		printf("=====================================================================\n");
		printf("=====================================================================\n");
		printf("====== 1. Adicionar produtos ao carrinho ============================\n");
		printf("====== 2. Exibir Todos os Produtos ==================================\n");
		printf("====== 3. Finalizar Compra ==========================================\n");
		printf("=====================================================================\n");
		scanf("%d",&opcao);
		switch(opcao){
			case 1:
				comprinha = carrinho(ncarrinho);
			break;
			case 2:
				exibirtodosprodutos();
			break;
			case 3:
				continuar=1;
			break;
		}
	}while(continuar ==0);
	
	
	carr = fopen("dados\\compraatual.txt","r");
		
	while((ql = fgetc(carr)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(carr);
	
	int *codigo_ver = malloc((numero_linhas/4)*sizeof(int));
	int *qtd_prod_ver= malloc((numero_linhas/4)*sizeof(int));
	float *preco_ver= malloc((numero_linhas/4)*sizeof(float));
	char *descricao_produto_ver[numero_linhas/4];
	
	carr = fopen("dados\\compraatual.txt","r");

	for(j=0;j<(numero_linhas/4);j++){
		descricao_produto_ver[j]= malloc(50*sizeof(char));
		
		fscanf(carr,"%i\n",&codigo_ver[j]);
		fscanf(carr,"\n%[^\n]s",descricao_produto_ver[j]);	
		fscanf(carr,"%i\n",&qtd_prod_ver[j]);
		fscanf(carr,"%f",&preco_ver[j]);
		total_pagar=total_pagar+preco_ver[j];
	}
	fclose(carr);
	total=total+total_pagar;
	
	
	printf("=====================================================================\n");
	printf("===== Total das Compras: R$ %.2f \n",total);
	printf("===== 1. Realizar Pagamento agora ===================================\n");
	printf("===== 2. Realizar Pagamento na saida ================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op_pagamento);
	
	if(op_pagamento==1){
		printf("=====================================================================\n");
		printf("===== Forma de pagamento: ===========================================\n");
		printf("===== 1. Dinheiro ===================================================\n");
		printf("===== 2. Cartão =====================================================\n");
		printf("=====================================================================\n");
		scanf("%d",&forma_pagamento);
		
		switch(forma_pagamento){
			case 1:
				printf("=====================================================================\n");
				caixa = caixa + total;

				FILE *caixa_Hotel;
				caixa_Hotel = fopen("dados\\caixa.txt","w");
				fprintf(caixa_Hotel,"%f",caixa);
				fclose(caixa_Hotel);
				printf("===== Pagamento efetuado com sucesso ================================\n");
				printf("=====================================================================\n");
				
				FILE *historico_mes;
				historico_mes = fopen("dados\\Historico mes.txt","a");
				fprintf(historico_mes,"Pagamento em dinheiro das compras do hospede: %s\n",nome_hospede[reserva_check-1]);
				fprintf(historico_mes,"%f\n",total);
				fprintf(historico_mes,"%f\n",caixa);
				fprintf(historico_mes,"%d\n%d\n%d\n",dia,mes,ano);
				fclose(historico_mes);
				
				FILE *historico_completo;
				historico_completo = fopen("dados\\Historico completo.txt","a");
				fprintf(historico_completo,"Pagamento em dinheiro das compras do hospede: %s\n",nome_hospede[reserva_check-1]);
				fprintf(historico_completo,"%f\n",total);
				fprintf(historico_completo,"%f\n",caixa);
				fprintf(historico_completo,"%d/%d/%d\n",dia,mes,ano);
				fclose(historico_completo);
				
			break;
			case 2:
				printf("=====================================================================\n");
				printf("===== Informe a dia de fatura do cartão do cartao: ==================\n");
				scanf("%d",&dia_fatura);
				if(dia_fatura > dia){
						mes_fatura = mes;
						ano_fatura = ano;
					}else{
						mes_fatura = mes+1;
						if (mes_fatura>12){
							mes_fatura=1;
							ano_fatura = ano+1;
						}
				}
				
				char descricao[300];
				strcpy (descricao, "Pagamento no cartao das compras do hospede: ");//define valor a string
				strcat (descricao, nome_hospede[reserva_check-1]); // junta duas strings
				
				adicionarcontaareceber(dia_fatura,mes_fatura,ano_fatura,total,descricao);
				printf("=====================================================================\n");
				printf("===== Pagamento efetuado com sucesso ================================\n");
				printf("=====================================================================\n");
			break;
		}
	//faça uma notinha aqui
		
	}
	else if (op_pagamento==2){
		printf("=====================================================================\n");
		for(i=0;i<(numero_linhas/4);i++){
			printf("Codigo do Produto: %d\n",codigo_ver[i]);
			printf("Produto: %s\n",descricao_produto_ver[i]);
			printf("Quantidade do Produto: %d\n",qtd_prod_ver[i]);
			printf("Preco: %.2f\n",preco_ver[i]);
			printf("=====================================================================\n");
		}
		
		printf("===== Total a pagar: %.2f\n",total_pagar);
		printf("=====================================================================\n");
		
		
		sprintf(numero_reserva, "%i", reserva_check);//converte interio em string
		strcpy (openreserva, "dados\\reserva");//define valor a string
		strcat (openreserva, numero_reserva); // junta duas strings
		strcat (openreserva, txt); // junta duas strings
		
		open_reservas = fopen(openreserva,"w");
		
		fprintf(open_reservas,"%i\n",codigo_reserva[reserva_check-1]);
		fprintf(open_reservas,"%i\n",dia_inicio_reserva[reserva_check-1]);
		fprintf(open_reservas,"%i\n",mes_inicio_reserva[reserva_check-1]);
		fprintf(open_reservas,"%i\n",ano_inicio_reserva[reserva_check-1]);
		fprintf(open_reservas,"%i\n",dias_reservado[reserva_check-1]);
		fprintf(open_reservas,"%i\n",dia_final_reserva[reserva_check-1]);
		fprintf(open_reservas,"%i\n",mes_final_reserva[reserva_check-1]);
		fprintf(open_reservas,"%i\n",ano_final_reserva[reserva_check-1]);
		fprintf(open_reservas,"%i\n",quarto_reservado[reserva_check-1]);
		fprintf(open_reservas,"%i\n",codhosp_reserva[reserva_check-1]);
		fprintf(open_reservas,"%i\n",situacao[reserva_check-1]);
		fprintf(open_reservas,"%f\n",totaldiarias[reserva_check-1]);
		total=total+valor_contas[reserva_check-1];
		fprintf(open_reservas,"%f",total);
		
		fclose(open_reservas);
		
		sprintf(numero_venda, "%i", reserva_check);//converte interio em string
		strcpy (open_carrinho, "dados\\compra");//define valor a string
		strcat (open_carrinho, numero_venda); // junta duas strings
		strcat (open_carrinho, txt); // junta duas strings
		
		carr = fopen(open_carrinho,"a");
		for(j=0;j<(numero_linhas/4);j++){

			fprintf(carr,"%i\n",codigo_ver[j]);
			fprintf(carr,"%s\n",descricao_produto_ver[j]);
			fprintf(carr,"%i\n",qtd_prod_ver[j]);
			fprintf(carr,"%f\n",preco_ver[j]);
		}
		
		fclose(carr);
	}
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
}
////////////////////////////////
int realizar_checkout(){
	
	FILE *open_reservas,*quartos,*hosp,*tipoacomod, *caixa_Hotel;
	int i,reserva_check,op_pagamento,forma_pagamento,dia_fatura,mes_fatura,ano_fatura,atraso=0,opcao,repetir;
	float totaldiarias,diaria_saida,totalcontas,totalpagar,multa=0;
	
	//reserva
	int *codigo_reserva = malloc(numero_reservas*sizeof(int));
	int *dia_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *dias_reservado = malloc(numero_reservas*sizeof(int));
	int *dia_final_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_final_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_final_reserva = malloc(numero_reservas*sizeof(int));
	int *quarto_reservado = malloc(numero_reservas*sizeof(int));
	int *codhosp_reserva = malloc(numero_reservas*sizeof(int));
	int *situacao = malloc(numero_reservas*sizeof(int));
	float *valor_pagar = malloc(numero_reservas*sizeof(int));
	float *valor_contas = malloc(numero_reservas*sizeof(int));
	
	//acomodacoes
	int *codacomod = malloc(numero_reservas*sizeof(int));
	int *categ = malloc(numero_reservas*sizeof(int));	
	char *desc_acomodacao[numero_reservas];
	char *facil[numero_reservas];
	
	//tipoacomodacao
	float *ValorDiaria = malloc(numero_reservas*sizeof(float));
	int *qtdHospedes = malloc(numero_reservas*sizeof(int));
	int *codtipoacomod = malloc(numero_reservas*sizeof(int));
	char *destipoacomod[numero_reservas];
	
	//hospede
	char *nome_hospede[numero_reservas];
	int *codigo_hospede= malloc(numero_reservas*sizeof(int));
	char numerodohospede[3],num_acomodacao[3],numtipacomodacao[3],txt[5] = ".txt";

	char numero_reserva[3],openreserva[23],openhospede[23],abrir_acomod[23],abriracomod[23];

	for(i=0;i<numero_reservas;i++){//pega os dados das reservas ja efetuadas
	
		nome_hospede[i] = malloc(40*sizeof(char));
		desc_acomodacao[i] = malloc(250*sizeof(char));
		facil[i] = malloc(250*sizeof(char));
		destipoacomod[i] = malloc(250*sizeof(char));
		
		//reserva
		sprintf(numero_reserva, "%i", i+1);//converte interio em string
		strcpy (openreserva, "dados\\reserva");//define valor a string
		strcat (openreserva, numero_reserva); // junta duas strings
		strcat (openreserva, txt); // junta duas strings
		
		open_reservas = fopen(openreserva,"r");
		if (open_reservas != NULL){
			fscanf(open_reservas,"%i",&codigo_reserva[i]);
			fscanf(open_reservas,"%i",&dia_inicio_reserva[i]);
			fscanf(open_reservas,"%i",&mes_inicio_reserva[i]);
			fscanf(open_reservas,"%i",&ano_inicio_reserva[i]);
			fscanf(open_reservas,"%i",&dias_reservado[i]);
			fscanf(open_reservas,"%i",&dia_final_reserva[i]);
			fscanf(open_reservas,"%i",&mes_final_reserva[i]);
			fscanf(open_reservas,"%i",&ano_final_reserva[i]);
			fscanf(open_reservas,"%i",&quarto_reservado[i]);
			fscanf(open_reservas,"%i",&codhosp_reserva[i]);
			fscanf(open_reservas,"%i",&situacao[i]);
			fscanf(open_reservas,"%f",&valor_pagar[i]);
			fscanf(open_reservas,"%f",&valor_contas[i]);
		}
		fclose(open_reservas);
		
		//hospede
		sprintf(numerodohospede, "%i", codhosp_reserva[i]);//converte interio em string
		strcpy (openhospede, "dados\\hospede");//define valor a string
		strcat (openhospede, numerodohospede); // junta duas strings
		strcat (openhospede, txt); // junta duas strings
		
		hosp = fopen(openhospede,"r");
		if (hosp != NULL){
			fscanf(hosp,"%i\n",&codigo_hospede[i]);		
			fscanf(hosp,"\n%[^\n]s",nome_hospede[i]);	
		}
		fclose(hosp);
		
		//acomodacao
		sprintf(num_acomodacao, "%i", quarto_reservado[i]);//converte interio em string
		strcpy (abrir_acomod, "dados\\acomodacao"); // Define o valor da string
		strcat (abrir_acomod, num_acomodacao); // junta duas strings
		strcat (abrir_acomod, txt); // junta duas strings
		
		quartos = fopen(abrir_acomod,"r");
		
		if (quartos != NULL){
			fflush(stdin); // limpa o buffer do teclado
			fscanf(quartos,"%i\n",&codacomod[i]);
			
			fscanf(quartos,"\n%[^\n]s",desc_acomodacao[i]);	
			fscanf(quartos,"\n%[^\n]s",facil[i]);	

			fscanf(quartos,"\n%i",&categ[i]);
		}
		fclose(quartos);
		
		
		
		
		
		//tipodeacomodacao
		sprintf(numtipacomodacao, "%i", categ[i]);//converte interio em string
		strcpy (abriracomod, "dados\\tacomodacao"); // Define o valor da string
		strcat (abriracomod, numtipacomodacao); // junta duas strings
		strcat (abriracomod, txt); // junta duas strings
		
		tipoacomod = fopen(abriracomod,"r");
	
		if (tipoacomod != NULL){
			fflush(stdin); // limpa o buffer do teclado
			fscanf(tipoacomod,"%i\n",&codtipoacomod[i]);
			fscanf(tipoacomod,"\n%[^\n]s",destipoacomod[i]);	

			fflush(stdin); // limpa o buffer do teclado
			fscanf(tipoacomod,"%f",&ValorDiaria[i]);
			fscanf(tipoacomod,"\n%i",&qtdHospedes[i]);
		}
		fclose(tipoacomod);
	}
	
	printf("=====================================================================\n");
	printf("========================== Realizar Check-out =======================\n");
	printf("=====================================================================\n");
	printf("========================== Reservas para Hoje =======================\n");

	for(i=0;i<numero_reservas;i++){
		if (situacao[i] ==2){
			
			if((dia_final_reserva[i] ==dia) && (mes_final_reserva[i] == mes)  && (ano_final_reserva[i] == ano)){
				printf("=====================================================================\n");
				printf("Codigo da reserva: %d\n",codigo_reserva[i]);
				printf("Data de Inicio da reserva: %d/%d/%d\n",dia_inicio_reserva[i],mes_inicio_reserva[i],ano_inicio_reserva[i]);
				printf("Ficou %d dias reservado\n",dias_reservado[i]);
				printf("Data do Fim da reserva: %d/%d/%d\n",dia_final_reserva[i],mes_final_reserva[i],ano_final_reserva[i]);
				printf("Quarto Reservado: %d\n",quarto_reservado[i]);
				printf("Hospede que reservou o quarto: %s\n",nome_hospede[i]);
				printf("Status da reserva: ATIVA\n");

				printf("=====================================================================\n");
			}else if((dia_final_reserva[i] > dia) && (mes_final_reserva[i] > mes)  && (ano_final_reserva[i] > ano)){
				printf("=====================================================================\n");
				printf("Codigo da reserva: %d\n",codigo_reserva[i]);
				printf("Data de Inicio da reserva: %d/%d/%d\n",dia_inicio_reserva[i],mes_inicio_reserva[i],ano_inicio_reserva[i]);
				printf("Ficou %d dias reservado\n",dias_reservado[i]);
				printf("Data do Fim da reserva: %d/%d/%d\n",dia_final_reserva[i],mes_final_reserva[i],ano_final_reserva[i]);
				printf("Quarto Reservado: %d\n",quarto_reservado[i]);
				printf("Hospede que reservou o quarto: %s\n",nome_hospede[i]);
				printf("Status da reserva: ATIVA\n");
				atraso=(dia_final_reserva[i]-dia)*-1;
				multa = ((ValorDiaria[i]*10/100)+ValorDiaria[i])*atraso;
				
				
				printf("Dias de atraso: %d\n",atraso);
				printf("Multa de atraso: %.2f\n",multa);
				printf("=====================================================================\n");
			}
		}
	}
	
	do{
		printf("===== 1. Realizar Check-out =========================================\n");
		printf("===== 2. Voltar =====================================================\n");
		scanf("%d",&opcao);
		switch(opcao){
			case 1:
				repetir=0;
			break;
			case 2:
				modulo_transacoes();
			break;
			default:
				repetir=1;
		}
	}while(repetir==1);
	printf("====== Digite o codigo da reserva que deseja realizar o Check-out ===\n");
	scanf("%d",&reserva_check);
	
	totaldiarias = valor_pagar[reserva_check-1];
	totalcontas = valor_contas[reserva_check-1];
	totalpagar = totaldiarias + totalcontas+multa;
	
	printf("=====================================================================\n");
	printf("===== Total das Diarias: R$ %.2f \n",totaldiarias);
	printf("===== Total das Contas: R$ %.2f \n",totalcontas);
	if(multa>0){
		printf("===== Total das Multas: R$ %.2f \n",multa);
	}
	printf("===== Contas totais do hospede: %.2f\n",totalpagar);
	if (totalpagar>0){
		printf("=====================================================================\n");
		printf("===== Forma de pagamento: ===========================================\n");
		printf("===== 1. Dinheiro ===================================================\n");
		printf("===== 2. Cartao =====================================================\n");
		printf("=====================================================================\n");
		scanf("%d",&forma_pagamento);
		switch(forma_pagamento){
			case 1:
				printf("=====================================================================\n");
				caixa = caixa + totalpagar;
				caixa_Hotel = fopen("dados\\caixa.txt","w");
				fprintf(caixa_Hotel,"%f",caixa);
				fclose(caixa_Hotel);
				totaldiarias = 0;
				totalcontas = 0;
				printf("===== Pagamento efetuado com sucesso ================================\n");
				printf("=====================================================================\n");
				
				FILE *historico_mes;
				historico_mes = fopen("dados\\Historico mes.txt","a");
				fprintf(historico_mes,"Pagamento em dinheiro no CheckOut da reserva: %d\n",reserva_check);
				fprintf(historico_mes,"%f\n",totalpagar);
				fprintf(historico_mes,"%f\n",caixa);
				fprintf(historico_mes,"%d\n%d\n%d\n",dia,mes,ano);
				fclose(historico_mes);
				
				FILE *historico_completo;
				historico_completo = fopen("dados\\Historico completo.txt","a");
				fprintf(historico_completo,"Pagamento em dinheiro no checkOut da reserva: %d\n",reserva_check);
				fprintf(historico_completo,"%f\n",totalpagar);
				fprintf(historico_completo,"%f\n",caixa);
				fprintf(historico_completo,"%d/%d/%d\n",dia,mes,ano);
				fclose(historico_completo);

			break;
			case 2:
				printf("=====================================================================\n");
				printf("===== Informe a dia de fatura do cartão do cartao: ==================\n");
				scanf("%d",&dia_fatura);
				if(dia_fatura > dia){
						mes_fatura = mes;
						ano_fatura = ano;
					}else{
						mes_fatura = mes+1;
						if (mes_fatura>12){
							mes_fatura=1;
							ano_fatura = ano+1;
						}
					}
				
				char descricao[300];
				strcpy (descricao, "Pagamento em cartao no CheckOut da reserva: ");//define valor a string
				sprintf(num_acomodacao, "%i", reserva_check);//converte interio em string
				strcat (descricao, num_acomodacao); // junta duas strings
				
				adicionarcontaareceber(dia_fatura,mes_fatura,ano_fatura,totalpagar,descricao);
				totaldiarias = 0;
				totalcontas = 0;
				printf("=====================================================================\n");
				printf("===== Pagamento efetuado com sucesso ================================\n");
				printf("=====================================================================\n");
			break;
		}
	}else{
		totaldiarias = 0;
		totalcontas = 0;
	}
	
	
	sprintf(numero_reserva, "%i", reserva_check);//converte interio em string
	strcpy (openreserva, "dados\\reserva");//define valor a string
	strcat (openreserva, numero_reserva); // junta duas strings
	strcat (openreserva, txt); // junta duas strings
	
	open_reservas = fopen(openreserva,"w");
	
	fprintf(open_reservas,"%i\n",codigo_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",dia_inicio_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",mes_inicio_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",ano_inicio_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",dias_reservado[reserva_check-1]);
	fprintf(open_reservas,"%i\n",dia_final_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",mes_final_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",ano_final_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",quarto_reservado[reserva_check-1]);
	fprintf(open_reservas,"%i\n",codhosp_reserva[reserva_check-1]);
	fprintf(open_reservas,"3\n");
	fprintf(open_reservas,"%f\n",totaldiarias);
	fprintf(open_reservas,"%f",totalcontas);
	// 0 = cancelada
	// 1 = Ativa
	// 2 = em uso
	// 3 = já passpo

	fclose(open_reservas);

	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();

}

int realizar_checkin(){//acho q ta pronto
	
	FILE *open_reservas,*quartos,*hosp,*tipoacomod;
	int i,reserva_check,op_pagamento,forma_pagamento,dia_fatura,mes_fatura,ano_fatura;
	float totaldiarias,diaria_saida;

	//reserva
	int *codigo_reserva = malloc(numero_reservas*sizeof(int));
	int *dia_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_inicio_reserva = malloc(numero_reservas*sizeof(int));
	int *dias_reservado = malloc(numero_reservas*sizeof(int));
	int *dia_final_reserva = malloc(numero_reservas*sizeof(int));
	int *mes_final_reserva = malloc(numero_reservas*sizeof(int));
	int *ano_final_reserva = malloc(numero_reservas*sizeof(int));
	int *quarto_reservado = malloc(numero_reservas*sizeof(int));
	int *codhosp_reserva = malloc(numero_reservas*sizeof(int));
	int *situacao = malloc(numero_reservas*sizeof(int));	
	
	//acomodacoes
	int *codacomod = malloc(numero_reservas*sizeof(int));
	int *categ = malloc(numero_reservas*sizeof(int));	
	char *desc_acomodacao[numero_reservas];
	char *facil[numero_reservas];
	
	//tipoacomodacao
	float *ValorDiaria = malloc(numero_reservas*sizeof(float));
	int *qtdHospedes = malloc(numero_reservas*sizeof(int));
	int *codtipoacomod = malloc(numero_reservas*sizeof(int));
	char *destipoacomod[numero_reservas];
	
	//hospede
	char *nome_hospede[numero_reservas];
	int *codigo_hospede= malloc(numero_reservas*sizeof(int));
	char numerodohospede[3],num_acomodacao[3],numtipacomodacao[3],txt[5] = ".txt";

	
	char numero_reserva[3],openreserva[23],openhospede[23],abrir_acomod[23],abriracomod[23];

	for(i=0;i<numero_reservas;i++){//pega os dados das reservas ja efetuadas
		nome_hospede[i] = malloc(40*sizeof(char));
		
		desc_acomodacao[i] = malloc(250*sizeof(char));
		facil[i] = malloc(250*sizeof(char));
		
		destipoacomod[i] = malloc(250*sizeof(char));

		//reserva
		sprintf(numero_reserva, "%i", i+1);//converte interio em string
		strcpy (openreserva, "dados\\reserva");//define valor a string
		strcat (openreserva, numero_reserva); // junta duas strings
		strcat (openreserva, txt); // junta duas strings
		
		open_reservas = fopen(openreserva,"r");
		
		fscanf(open_reservas,"%i",&codigo_reserva[i]);
		fscanf(open_reservas,"%i",&dia_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&mes_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&ano_inicio_reserva[i]);
		fscanf(open_reservas,"%i",&dias_reservado[i]);
		fscanf(open_reservas,"%i",&dia_final_reserva[i]);
		fscanf(open_reservas,"%i",&mes_final_reserva[i]);
		fscanf(open_reservas,"%i",&ano_final_reserva[i]);
		fscanf(open_reservas,"%i",&quarto_reservado[i]);
		fscanf(open_reservas,"%i",&codhosp_reserva[i]);
		fscanf(open_reservas,"%i",&situacao[i]);

		fclose(open_reservas);
		
		
		//hospede
		sprintf(numerodohospede, "%i", codhosp_reserva[i]);//converte interio em string
		strcpy (openhospede, "dados\\hospede");//define valor a string
		
		strcat (openhospede, numerodohospede); // junta duas strings
		strcat (openhospede, txt); // junta duas strings
		
		hosp = fopen(openhospede,"r");
		
		fscanf(hosp,"%i\n",&codigo_hospede[i]);
		fscanf(hosp,"\n%[^\n]s",nome_hospede[i]);

		fclose(hosp);
		
		
		//acomodacao
		sprintf(num_acomodacao, "%i", quarto_reservado[i]);//converte interio em string
		
		strcpy (abrir_acomod, "dados\\acomodacao"); // Define o valor da string
		
		strcat (abrir_acomod, num_acomodacao); // junta duas strings
		strcat (abrir_acomod, txt); // junta duas strings
		
		quartos = fopen(abrir_acomod,"r");
		
		if (quartos != NULL){
			fflush(stdin); // limpa o buffer do teclado
			fscanf(quartos,"%i\n",&codacomod[i]);
			fscanf(quartos,"\n%[^\n]s",desc_acomodacao[i]);
			fscanf(quartos,"\n%[^\n]s",facil[i]);
			fscanf(quartos,"\n%i",&categ[i]);
		}
		fclose(quartos);
		
		//tipodeacomodacao
		
		sprintf(numtipacomodacao, "%i", categ[i]);//converte interio em string
		strcpy (abriracomod, "dados\\tacomodacao"); // Define o valor da string
		strcat (abriracomod, numtipacomodacao); // junta duas strings
		strcat (abriracomod, txt); // junta duas strings
		
		tipoacomod = fopen(abriracomod,"r");
	
		if (tipoacomod != NULL){
			fflush(stdin); // limpa o buffer do teclado
			fscanf(tipoacomod,"%i\n",&codtipoacomod[i]);
			fscanf(tipoacomod,"\n%[^\n]s",destipoacomod[i]);
			fflush(stdin); // limpa o buffer do teclado
			fscanf(tipoacomod,"%f",&ValorDiaria[i]);
			fscanf(tipoacomod,"\n%i",&qtdHospedes[i]);
		}
		fclose(tipoacomod);
	}
	
	printf("=====================================================================\n");
	printf("========================== Realizar Check-In ========================\n");
	printf("=====================================================================\n");
	printf("========================== Reservas para Hoje =======================\n");

	for(i=0;i<numero_reservas;i++){
		if (situacao[i] ==1){
			if((dia_inicio_reserva[i] ==dia) && (mes_inicio_reserva[i] == mes)  && (ano_inicio_reserva[i] == ano)){
				printf("=====================================================================\n");
				printf("Codigo da reserva: %d\n",codigo_reserva[i]);
				printf("Data de Inicio da reserva: %d/%d/%d\n",dia_inicio_reserva[i],mes_inicio_reserva[i],ano_inicio_reserva[i]);
				printf("Ficara %d dias reservado\n",dias_reservado[i]);
				printf("Data do Fim da reserva: %d/%d/%d\n",dia_final_reserva[i],mes_final_reserva[i],ano_final_reserva[i]);
				printf("Quarto Reservado: %d\n",quarto_reservado[i]);
				printf("Hospede que reservou o quarto: %s\n",nome_hospede[i]);
				printf("Status da reserva: ATIVA\n");
				printf("=====================================================================\n");
			}
		}
	}
	
	printf("====== Digite o codigo da reserva que deseja realizar o Check-In ====\n");
	scanf("%d",&reserva_check);
	
	totaldiarias = dias_reservado[reserva_check-1] * ValorDiaria[reserva_check-1];
	printf("=====================================================================\n");
	printf("===== Total das Diarias: R$ %.2f \n",totaldiarias);
	printf("===== 1. Realizar Pagamento agora ===================================\n");
	printf("===== 2. Realizar Pagamento na saida ================================\n");
	printf("=====================================================================\n");
	scanf("%d",&op_pagamento);
	
	if(op_pagamento==1){
		printf("=====================================================================\n");
		printf("===== Forma de pagamento: ===========================================\n");
		printf("===== 1. Dinheiro ===================================================\n");
		printf("===== 2. Cartao =====================================================\n");
		printf("=====================================================================\n");
		scanf("%d",&forma_pagamento);
		switch(forma_pagamento){
			case 1:
				printf("=====================================================================\n");
				caixa = caixa + totaldiarias;
				diaria_saida=0;
				
				FILE *caixa_Hotel;
				caixa_Hotel = fopen("dados\\caixa.txt","w");
				fprintf(caixa_Hotel,"%f",caixa);
				fclose(caixa_Hotel);
				
				printf("===== Pagamento efetuado com sucesso ================================\n");
				printf("=====================================================================\n");
				
				FILE *historico_mes;
				historico_mes = fopen("dados\\Historico mes.txt","a");
				fprintf(historico_mes,"Pagamento em dinheiro no CheckIn da reserva: %d\n",reserva_check);
				fprintf(historico_mes,"%f\n",totaldiarias);
				fprintf(historico_mes,"%f\n",caixa);
				fprintf(historico_mes,"%d\n%d\n%d\n",dia,mes,ano);
				fclose(historico_mes);
				
				FILE *historico_completo;
				historico_completo = fopen("dados\\Historico completo.txt","a");
				fprintf(historico_completo,"Pagamento em dinheiro no CheckIn da reserva: %d\n",reserva_check);
				fprintf(historico_completo,"%f\n",totaldiarias);
				fprintf(historico_completo,"%f\n",caixa);
				fprintf(historico_completo,"%d/%d/%d\n",dia,mes,ano);
				fclose(historico_completo);
				
			break;
			case 2:
				printf("=====================================================================\n");
				printf("===== Informe a dia de fatura do cartão do cartao: ==================\n");
				scanf("%d",&dia_fatura);
				if(dia_fatura > dia){
					mes_fatura = mes;
					ano_fatura = ano;
				}else{
					mes_fatura = mes+1;
					if (mes_fatura>12){
						mes_fatura=1;
						ano_fatura = ano+1;
					}
				}
				
				char descricao[300];
				strcpy (descricao, "Pagamento em cartao no CheckIn da reserva: ");//define valor a string
				sprintf(num_acomodacao, "%i", reserva_check);//converte interio em string
				strcat (descricao, num_acomodacao); // junta duas strings
				
				adicionarcontaareceber(dia_fatura,mes_fatura,ano_fatura, totaldiarias,descricao);
				printf("=====================================================================\n");
				printf("===== Pagamento efetuado com sucesso ================================\n");
				printf("=====================================================================\n");
			break;
		}
	}else{
		diaria_saida = totaldiarias;
	}

	sprintf(numero_reserva, "%i", reserva_check);//converte interio em string
	strcpy (openreserva, "dados\\reserva");//define valor a string
	strcat (openreserva, numero_reserva); // junta duas strings
	strcat (openreserva, txt); // junta duas strings
	
	open_reservas = fopen(openreserva,"w");
	
	fprintf(open_reservas,"%i\n",codigo_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",dia_inicio_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",mes_inicio_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",ano_inicio_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",dias_reservado[reserva_check-1]);
	fprintf(open_reservas,"%i\n",dia_final_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",mes_final_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",ano_final_reserva[reserva_check-1]);
	fprintf(open_reservas,"%i\n",quarto_reservado[reserva_check-1]);
	fprintf(open_reservas,"%i\n",codhosp_reserva[reserva_check-1]);
	fprintf(open_reservas,"2\n");
	fprintf(open_reservas,"%f",diaria_saida);
	// 0 = cancelada
	// 1 = Ativa
	// 2 = em uso
	// 3 = já passpo

	fclose(open_reservas);
	
}
///////////////////////////////
int modulo_transacoes(){
	int categoriadesejada;
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("================ Qual Area Deseja Acessar? ==========================\n");
	printf("=====================================================================\n");
	printf("===== 1. Check-in ===================================================\n");
	printf("===== 2. Check-out ==================================================\n");
	printf("===== 3. Saída de produtos (venda) ==================================\n");
	printf("===== 4. Controle de Caixa e Contas a Pagar e Receber ===============\n");
	printf("===== 5. Entrada de produtos industrializados =======================\n");
	printf("===== 6. Voltar =====================================================\n");
	printf("===== 0. Sair do Sistema ============================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	scanf("%d", &categoriadesejada);
		
	switch (categoriadesejada){
	case 1:
		realizar_checkin();
	break;
	case 2:
		realizar_checkout();
	break;
	case 3:
		vendas();
	break;
	case 4:
		controle_caixa();
	break;
	case 5:
		if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}
		entrada_de_produtos();
	break;
	case 6:
		main();
	break;
	case 0:
		exit(0);
	break;
	default:
		modulo_transacoes();
	}
	modulo_transacoes();
}

////////////////////////
//modulo 4 /////////////
////////////////////////


int rHospedes(){
	int i,j;
	FILE *hosp;
	char txt[5] = ".txt";
	char numerodohospede[3];
	char newhospede[23];
	int *codigo_hospede = malloc(numero_de_hospedes * sizeof(int));
	char *nome_hospede[numero_de_hospedes];
	char *email_hospede[numero_de_hospedes];
	char *sexo_hospede[numero_de_hospedes];
	char *estadocivil_hospede[numero_de_hospedes];
	char *rua_hospede[numero_de_hospedes];
	char *numero_hospede[numero_de_hospedes];
	char *bairro_hospede[numero_de_hospedes];
	char *cidade_hospede[numero_de_hospedes];
	char *UF_hospede[numero_de_hospedes];
	char *cpf_hospede[numero_de_hospedes];
	char *telefone_hospede[numero_de_hospedes];
	char *datanascimento_hospede[numero_de_hospedes];
	for(i=0;i<numero_de_hospedes;i++){
		nome_hospede[i] = malloc(45*sizeof(char));
		email_hospede[i] = malloc(45*sizeof(char));
		sexo_hospede[i] = malloc(15*sizeof(char));
		estadocivil_hospede[i] = malloc(20*sizeof(char));
		rua_hospede[i] = malloc(25*sizeof(char));
		numero_hospede[i] = malloc(10*sizeof(char));
		bairro_hospede[i] = malloc(30*sizeof(char));
		cidade_hospede[i] = malloc(40*sizeof(char));
		UF_hospede[i] = malloc(5*sizeof(char));
		cpf_hospede[i] = malloc(14*sizeof(char));
		telefone_hospede[i] = malloc(14*sizeof(char));
		datanascimento_hospede[i] = malloc(20*sizeof(char));
	}
	
	
	FILE *arq; //Cria um ponteiro arq que apontara para o arquivo			
	arq = fopen("RelatorioHospedes.csv","w"); //Cria o arquivo CSV e limpa ele caso exista algum antigo
	fclose(arq);
	
	/* Pergunta ao usuario se ele deseja mostrar o relatorio na tela ou gerar um arquivo */
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	int op, op2, filtro1, filtro2,filtro_codigo,filtro_sexo,n1,n2,filtragem_sexo,exibir;
	printf("=====================================================================\n");
	printf("======================== Digite sua opcao:===========================\n");
	printf("=====================================================================\n");
	printf("======= 1. Exibir Relatorio na tela =================================\n");	
	printf("======= 2. Gerar arquivo com o relatorio ============================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	do{
		scanf("%d",&op);
	}while(op<1 || op >2);
	
	//////////////////////////////////////////////////////////////////////////////////////////
	
	/* Exibe o relatorio na tela */
	
	printf("==================================\n");
	printf("==== Deseja utilizar filtros? ====\n");
	printf("==================================\n");
	printf("========== 1. Sim ================\n");	
	printf("========== 2. Nao ================\n");
	printf("==================================\n");
	scanf("%d",&op2);
	
	if (op2 == 1){
		
		printf("=====================================================================\n");
		printf("================== Qual filtro deseja utilizar? =====================\n");
		printf("=====================================================================\n");
		printf("======= 1. Faixa de Codigos =========================================\n");	
		printf("======= 2. Sexo =====================================================\n");
		printf("=====================================================================\n");
		printf("=====================================================================\n");

		////////////////////////////////////////////////////////
		do{
			scanf("%i",&filtro1);
		}while((filtro1 != 1 ) && ( filtro1 != 2));
		
		
		printf("=====================================================================\n");
		printf("================== Deseja utilizar o outro filtro? ==================\n");
		printf("=====================================================================\n");
		printf("======= 1. Sim ======================================================\n");	
		printf("======= 2. Nao ======================================================\n");
		printf("=====================================================================\n");
		printf("=====================================================================\n");

		do{
			scanf("%d",&filtro2);
		}while((filtro2 != 1 ) && (filtro2 != 2));
		
		switch(filtro2){
			case 1:
				filtro_codigo = 1;
				filtro_sexo = 1;
			break;
			case 2:
				switch(filtro1){
					case 1:
						filtro_codigo = 1;
						filtro_sexo = 0;
					break;
					case 2:
						filtro_codigo = 0;
						filtro_sexo = 1;
					break;
				}
			break;
		}
		
		
		if(filtro_codigo ==1){
			printf("=====================================================================\n");
			printf("===== De qual faixa de codigos deseja gerar o relatorio =============\n");
			printf("===== Inicio:");
			scanf("%d",&n1);
			n1=n1-1;
			printf("===== Fim:");
			scanf("%d",&n2);
			printf("=====================================================================\n");
		}else{
			n1=0;
			n2=numero_de_hospedes;
		}
		if(filtro_sexo ==1){
			printf("=====================================================================\n");
			printf("===== Qual sexo deseja filtrar ======================================\n");
			printf("=====================================================================\n");
			printf("===== 1. Apenas Homens ==============================================\n");
			printf("===== 2. Apenas Mulheres ============================================\n");
			printf("===== 3. Apenas Outros ==============================================\n");
			printf("=====================================================================\n");
			do{
				scanf("%d",&filtragem_sexo);
			}while((filtragem_sexo != 1) && (filtragem_sexo != 2) && (filtragem_sexo !=3));
		}else{
			filtragem_sexo=4;
		}
	}else{
		filtragem_sexo=4;
		n1=0;
		n2=numero_de_hospedes;
	}
	
	if(op == 1){
		#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
					
		for(i=n1;i<=n2;i++){
			sprintf(numerodohospede, "%i", i+1);//converte interio em string
			strcpy (newhospede, "dados\\hospede");//define valor a string
			
			strcat (newhospede, numerodohospede); // junta duas strings
			strcat (newhospede, txt); // junta duas strings
			
			hosp = fopen(newhospede,"r");
			
			if (hosp != NULL){
				fscanf(hosp,"%i\n",&codigo_hospede[i]);		
				fscanf(hosp,"\n%[^\n]s",nome_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",email_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",sexo_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",estadocivil_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",rua_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",numero_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",bairro_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",cidade_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",UF_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",cpf_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",telefone_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",datanascimento_hospede[i]);
			
				
				switch(filtragem_sexo){
					case 1:
						if((strcmp(sexo_hospede[i],"Masculino") ==0) || (strcmp(sexo_hospede[i],"masculino") ==0)){
							exibir=1;
						}else{
							exibir=0;
						}
					break;
					case 2:
						if((strcmp(sexo_hospede[i],"Feminino") ==0) || (strcmp(sexo_hospede[i],"feminino") ==0)){
							exibir=1;
						}else{
							exibir=0;
						}
					break;
					case 3:
						if((strcmp(sexo_hospede[i],"Masculino") !=0) && (strcmp(sexo_hospede[i],"masculino") !=0) && (strcmp(sexo_hospede[i],"Feminino") !=0) && (strcmp(sexo_hospede[i],"feminino") !=0)){
							exibir=1;
						}else{
							exibir=0;
						}
					break;
					case 4:
						exibir=1;
					break;
				}
				
				
				if(exibir ==1){
					printf("\n=====================================================================\n");
					printf("Codigo do Hospede: %i\n",codigo_hospede[i]);
					printf("Nome Do Hospede: %s\n",nome_hospede[i]);
					printf("Email Do Hospede:%s\n",email_hospede[i]);
					printf("Sexo Do Hospede:%s\n",sexo_hospede[i]);
					printf("Estado Civil do Hospede:%s\n",estadocivil_hospede[i]);
					printf("Rua do Hospede:%s\n",rua_hospede[i]);
					printf("Numero:%s\n",numero_hospede[i]);	
					printf("Bairro:%s\n",bairro_hospede[i]);
					printf("Cidade:%s\n",cidade_hospede[i]);
					printf("UF:%s\n",UF_hospede[i]);
					printf("CPF:%s\n",cpf_hospede[i]);
					printf("Telefone do Hospede:%s\n",telefone_hospede[i]);
					printf("Data de Nascimento do Hospede:%s\n",datanascimento_hospede[i]);
					printf("\n=====================================================================\n");
				}
			}
			
			fclose(hosp);
		}
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		///////////////////////////////
	}
	else if (op==2){
		/**************************** Gera o arquivo *****************************/
		for(i=n1;i<=n2;i++){
			sprintf(numerodohospede, "%i", i+1);//converte interio em string
			strcpy (newhospede, "dados\\hospede");//define valor a string
			strcat (newhospede, numerodohospede); // junta duas strings
			strcat (newhospede, txt); // junta duas strings
			
			hosp = fopen(newhospede,"r");
			
			if (hosp != NULL){
				fscanf(hosp,"%i\n",&codigo_hospede[i]);		
				fscanf(hosp,"%[^\n]s",nome_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",email_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",sexo_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",estadocivil_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",rua_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",numero_hospede[i]);		
				fscanf(hosp,"\n%[^\n]s",bairro_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",cidade_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",UF_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",cpf_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",telefone_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",datanascimento_hospede[i]);
				exibir=1;
				switch(filtragem_sexo){
					case 1:
						if((strcmp(sexo_hospede[i],"Masculino") ==0) || (strcmp(sexo_hospede[i],"masculino") ==0)){
							exibir=1;
						}else{
							exibir=0;
						}
					break;
					case 2:
						if((strcmp(sexo_hospede[i],"Feminino") ==0) || (strcmp(sexo_hospede[i],"feminino") ==0)){
							exibir=1;
						}else{
							exibir=0;
						}
					break;
					case 3:
						if((strcmp(sexo_hospede[i],"Masculino") !=0) && (strcmp(sexo_hospede[i],"masculino") !=0) && (strcmp(sexo_hospede[i],"Feminino") !=0) && (strcmp(sexo_hospede[i],"feminino") !=0)){
							exibir=1;
						}else{
							exibir=0;
						}
					break;
					case 4:
						exibir=1;
					break;
				}
								
				if(exibir == 1){
					arq = fopen("RelatorioHospedes.csv","a"); //Cria o arquivo CSV
					if(arq == NULL){
						printf("O arquivo nao pode ser aberto.\n");
						exit(0);
					}
					
					fprintf(arq,"Codigo do Hospede; %d\n ",codigo_hospede[i]); //Armazena o Codigo do Hospede no arquivo CSV
					fprintf(arq,"Nome do Hospede; %s\n",nome_hospede[i]);
					fprintf(arq,"Email; %s\n",email_hospede[i]);
					fprintf(arq,"Sexo; %s\n",sexo_hospede[i]);
					fprintf(arq,"Estado Civil; %s\n",estadocivil_hospede[i]);
					fprintf(arq,"Rua; %s\n",rua_hospede[i]);
					fprintf(arq,"Numero; %s\n",numero_hospede[i]);
					fprintf(arq,"Bairro; %s\n",bairro_hospede[i]);
					fprintf(arq,"Cidade; %s\n",cidade_hospede[i]);
					fprintf(arq,"Estado; %s\n",UF_hospede[i]);
					fprintf(arq,"CPF; %s\n",cpf_hospede[i]);
					fprintf(arq,"Telefone do Hospede; %s\n",telefone_hospede[i]);
					fprintf(arq,"Data de Nascimento; %s\n\n",datanascimento_hospede[i] );
					fclose(arq); //Fecha o arquivo
				}
			}
			
			fclose(hosp);
		}
		printf("Relatorio gerado com sucesso!\n");
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		/**************************************************************************/
	}
	
}

int rAcomodacoes(){ 
	
	int i,j;
	FILE *acomod;
	char txt[5] = ".txt";
	char numerodaacomodacao[3];
	char acomodacao[23] = "dados\\acomodacao";
	
	/* variaveis que receberam o codigo da acomodacao, sua descricao, facilidades e seu tipo */
	int *codigo = malloc(numero_de_acomodacoes * sizeof(int));
	char *descricao[numero_de_acomodacoes];
	char *facilidades[numero_de_acomodacoes];
	int *tipo = malloc(numero_de_acomodacoes * sizeof(int));
	for(i=0;i<numero_de_acomodacoes;i++){
		descricao[i] = malloc(250*sizeof(char));
		facilidades[i] = malloc(250*sizeof(char));
	}
	//////////////////////////////////////////////////////////////////
	FILE *arq; //Cria um ponteiro arq que apontara para o arquivo			
	arq = fopen("RelatorioAcomodacoes.csv","w"); //Cria o arquivo CSV e limpa caso já exista algum
	fclose(arq);
	
	/* Pergunta ao usuario se ele deseja mostrar o relatorio na tela ou gerar um arquivo */
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	int op, op2, filtro1, filtro2, n1,n2, tipo_usuario, opfiltro2, exibir;//Variaveis que serao utilizadas no filtro
	printf("=====================================================================\n");
	printf("======================== Digite sua opcao:===========================\n");
	printf("=====================================================================\n");
	printf("======= 1. Exibir Relatorio na tela =================================\n");	
	printf("======= 2. Gerar arquivo com o relatorio ============================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	do{
		scanf("%d",&op);
	}while(op<1 || op >2);
	
	//////////////////////////////////////////////////////////////////////////////////////////
	
	/* Exibe o relatorio na tela */
	
	printf("==================================\n");
	printf("==== Deseja utilizar filtros? ====\n");
	printf("==================================\n");
	printf("========== 1. Sim ================\n");	
	printf("========== 2. Nao ================\n");
	printf("==================================\n");
	scanf("%d",&op2);
	int filtro_codigo = 0, filtro_categoria = 0;
	if (op2 == 1){
		
		printf("=====================================================================\n");
		printf("================== Qual filtro deseja utilizar? =====================\n");
		printf("=====================================================================\n");
		printf("======= 1. Faixa de Codigos =========================================\n");	
		printf("======= 2. Categoria ================================================\n");
		printf("=====================================================================\n");
		printf("=====================================================================\n");

		////////////////////////////////////////////////////////
		do{
			scanf("%i",&filtro1);
		}while((filtro1 != 1 ) && ( filtro1 != 2));
		
		if(filtro1 == 1){
			filtro_codigo = 1;
		} else if (filtro1 == 2){
			filtro_categoria = 1;
		}
		printf("=====================================================================\n");
		printf("================== Deseja utilizar outro filtro? ====================\n");
		printf("=====================================================================\n");
		printf("======= 1. Sim ======================================================\n");	
		printf("======= 2. Nao ======================================================\n");
		printf("=====================================================================\n");
		printf("=====================================================================\n");
		do{
			scanf("%d",&filtro2);
		}while((filtro2 != 1 ) && (filtro2 != 2) );
		
		if(filtro2 == 1){
			filtro_codigo = 1;
			filtro_categoria = 1;
		}
		if(filtro_categoria == 1){
			exibirtiposdeacomodacoes();
			printf("=====================================================================\n");
			printf("========== Digite o codigo do tipo de acomodacao desejado ===========\n");
			printf("=====================================================================\n");
			scanf("%d",&tipo_usuario);
			n1 = 0;
			n2 = numero_de_acomodacoes;
		}
		
		if(filtro_codigo == 1){
			printf("=====================================================================\n");
			printf("===== De qual faixa de codigos deseja gerar o relatorio =============\n");
			printf("===== Inicio:");
			scanf("%d",&n1);
			n1=n1-1;
			printf("===== Fim:");
			scanf("%d",&n2);
			printf("=====================================================================\n");
		}
	}
	else{
		n1 = 0;
		n2 = numero_de_acomodacoes;
		tipo_usuario = 0;	
	}
	if(op == 1){
		#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
		for(i=n1;i<n2;i++){

			sprintf(numerodaacomodacao, "%i", i+1);//converte interio em string
			strcpy (acomodacao, "dados\\acomodacao");//define valor a string
			strcat (acomodacao, numerodaacomodacao); // junta duas strings
			strcat (acomodacao, txt); // junta duas strings
			
			acomod = fopen(acomodacao,"r");
			
			if (acomod != NULL){
				fscanf(acomod,"%i\n",&codigo[i]);
				fscanf(acomod,"\n%[^\n]s",descricao[i]);
				fscanf(acomod,"\n%[^\n]s",facilidades[i]);
				fscanf(acomod,"%i",&tipo[i]);			
				
				if(tipo_usuario == 0){
					printf("\n=====================================================================\n");
					printf("Codigo da Acomodacao: %i\n",codigo[i]);
					printf("Descricao da Acomodacao: %s\n",descricao[i]);
					printf("Facilidades:%s\n",facilidades[i]);
					printf("Tipo de Acomodacao:%d",tipo[i]);
					printf("\n=====================================================================\n");
					
				}
				else{
					if(tipo_usuario == tipo[i]){
						printf("\n=====================================================================\n");
						printf("Codigo da Acomodacao: %i\n",codigo[i]);
						printf("Descricao da Acomodacao: %s\n",descricao[i]);
						printf("Facilidades:%s\n",facilidades[i]);
						printf("Tipo de Acomodacao:%d",tipo[i]);
						printf("\n=====================================================================\n");
					}
				}
			}
			fclose(acomod);
		}
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}
	else if (op==2){
		/**************************** Gera o arquivo *****************************/
		for(i=n1;i<=n2;i++){
			
			sprintf(numerodaacomodacao, "%i", i+1);//converte interio em string
			strcpy (acomodacao, "dados\\acomodacao");//define valor a string
			strcat (acomodacao, numerodaacomodacao); // junta duas strings
			strcat (acomodacao, txt); // junta duas strings
			
			acomod = fopen(acomodacao,"r");
			
			if (acomod != NULL){
				fscanf(acomod,"%i\n",&codigo[i]);
				fscanf(acomod,"\n%[^\n]s",descricao[i]);
				fscanf(acomod,"\n%[^\n]s",facilidades[i]);
				fscanf(acomod,"%i\n",&tipo[i]);
				
				arq = fopen("RelatorioAcomodacoes.csv","a"); //Cria o arquivo CSV
				if(arq == NULL){
					printf("O arquivo nao pode ser aberto.\n");
					exit(0);
				}
				if(tipo_usuario == 0){
					fprintf(arq,"Codigo da Acomodacao; %d\n ",codigo[i]); //Armazena o Codigo do Hospede no arquivo CSV
					fprintf(arq,"Descricao da Acomodacao; %s\n",descricao[i]);
					fprintf(arq,"Facilidades; %s\n",facilidades[i]);
					fprintf(arq,"Codigo de Tipo de Acomodacao; %d\n\n",tipo[i]);
				}
				else{
					if(tipo_usuario == tipo[i]){
						fprintf(arq,"Codigo da Acomodacao; %d\n ",codigo[i]); //Armazena o Codigo do Hospede no arquivo CSV
						fprintf(arq,"Descricao da Acomodacao; %s\n",descricao[i]);
						fprintf(arq,"Facilidades; %s\n",facilidades[i]);
						fprintf(arq,"Codigo de Tipo de Acomodacao; %d\n\n",tipo[i]);
					}
				}
				fclose(arq); //Fecha o arquivo
			}
		}
		fclose(acomod);
		printf("Relatorio gerado com sucesso!\n");
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		/**************************************************************************/
	}
}

int rReservas(){

	int i,j;
	
	char txt[5] = ".txt";
	
	/* Variaveis utilizadas para pegar os dados das reservas */
	FILE *reservas;
	char numerodareserva[3];
	char reserva[23];
	
	int *open_reservas, *cod_reserva;
	int *dia_inicio_reserva,*mes_inicio_reserva,*ano_inicio_reserva,*dias_reservado;
	int *dia_final_reserva,*mes_final_reserva,*ano_final_reserva,*quarto_reservado,*codhosp_reserva;
	
	cod_reserva = malloc(numero_reservas * sizeof(int));
	dia_inicio_reserva = malloc(numero_reservas*sizeof(int));
	mes_inicio_reserva = malloc(numero_reservas*sizeof(int));
	ano_inicio_reserva = malloc(numero_reservas*sizeof(int));
	dias_reservado = malloc(numero_reservas*sizeof(int));
	dia_final_reserva = malloc(numero_reservas*sizeof(int));
	mes_final_reserva = malloc(numero_reservas*sizeof(int));
	ano_final_reserva = malloc(numero_reservas*sizeof(int));
	quarto_reservado = malloc(numero_reservas*sizeof(int));
	codhosp_reserva = malloc(numero_reservas*sizeof(int));
	FILE *arq; //Cria um ponteiro arq que apontara para o arquivo			
	arq = fopen("RelatorioReservas.csv","w"); //Cria o arquivo CSV e limpa caso exista algum ja feito
	fclose(arq);
	
	//Pergunta ao usuario se ele deseja mostrar o relatorio na tela ou gerar um arquivo 
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	int op, op2;
	int n1,n2;
	int a1,a2;
	int codigo_hospede = 0, codigo_acomodacao = 0;
	///////////////
	printf("=====================================================================\n");
	printf("======================== Digite sua opcao:===========================\n");
	printf("=====================================================================\n");
	printf("======= 1. Exibir Relatorio na tela =================================\n");	
	printf("======= 2. Gerar arquivo com o relatorio ============================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	do{
		scanf("%d",&op);
	}while(op<1 || op >2);
	//////////////////////////////////////////////////////////////////////////////////////////
	
	printf("==================================\n");
	printf("==== Deseja utilizar filtros? ====\n");
	printf("==================================\n");
	printf("========== 1. Sim ================\n");	
	printf("========== 2. Nao ================\n");
	printf("==================================\n");
	scanf("%d",&op2);
			
	if (op2 == 1) {		
		int filtro1, filtro2;
		int opfiltro2;
		printf("=====================================================================\n");
		printf("================== Qual filtro deseja utilizar? =====================\n");
		printf("=====================================================================\n");
		printf("======= 1. Codigo do Hospede ========================================\n");	
		printf("======= 2. Codigo da Acomodacao =====================================\n");
		printf("=====================================================================\n");
		printf("=====================================================================\n");
	
		do{
			scanf("%i",&filtro1);
		}while((filtro1 != 1 ) && ( filtro1 != 2));
		
		if(filtro1 == 1){
			codigo_hospede = 1;
		} else if (filtro1 == 2){
			codigo_acomodacao = 1;
		}
		
		printf("=====================================================================\n");
		printf("================== Deseja utilizar outro filtro? ====================\n");
		printf("=====================================================================\n");
		printf("======= 1. Sim ======================================================\n");	
		printf("======= 2. Nao ======================================================\n");
		printf("=====================================================================\n");
		printf("=====================================================================\n");

		do{
			scanf("%d",&filtro2);
		}while((filtro2 != 1 ) && (filtro2 != 2));
		
		if(filtro2 == 1){
			codigo_hospede = 1;
			codigo_acomodacao = 1;
		}
		if(codigo_hospede == 1){
			printf("=====================================================================\n");
			printf("==== De qual faixa de codigos de Hospede deseja gerar o relatorio ===\n");
			printf("===== Inicio:");
			scanf("%d",&n1);
			n1=n1-1;
			printf("===== Fim:");
			scanf("%d",&n2);
			printf("=====================================================================\n");
		}else{
			n1 = 0;
			n2 = numero_reservas;
		}
		
		if(codigo_acomodacao == 1){
			printf("=====================================================================\n");
			printf("= De qual faixa de codigos de Acomodacao deseja gerar o relatorio ===\n");
			printf("===== Inicio:");
			scanf("%d",&a1);
			a1=a1-1;
			printf("===== Fim:");
			scanf("%d",&a2);
			printf("=====================================================================\n");
		}else{
			a1 = 0;
			a2 = numero_de_acomodacoes;
		}
	}
	else{
		n1 = 0;
		n2 = numero_reservas;
		a1 = 0;
		a2 = numero_de_acomodacoes;	
	}

	if (op == 1){
		printf("\nQuartos reservados:\n");
		for (i=n1; i<n2 ;i++){		
			sprintf(numerodareserva, "%i", i+1);//converte interio em string
			strcpy (reserva, "dados\\reserva");//define valor a string
			strcat (reserva, numerodareserva); // junta duas strings
			strcat (reserva, txt); // junta duas strings
			
			reservas = fopen(reserva,"r");
				if(reservas != NULL){
					fscanf(reservas,"%i\n",&cod_reserva[i]);
					fscanf(reservas,"%i\n",&dia_inicio_reserva[i]);
					fscanf(reservas,"%i\n",&mes_inicio_reserva[i]);
					fscanf(reservas,"%i\n",&ano_inicio_reserva[i]);
					fscanf(reservas,"%i\n",&dias_reservado[i]);
					fscanf(reservas,"%i\n",&dia_final_reserva[i]);
					fscanf(reservas,"%i\n",&mes_final_reserva[i]);
					fscanf(reservas,"%i\n",&ano_final_reserva[i]);
					fscanf(reservas,"%i\n",&quarto_reservado[i]);
					fscanf(reservas,"%i",&codhosp_reserva[i]);
						
					if(codigo_acomodacao == 0){
				
						printf("\nQuarto numero %d\n",quarto_reservado[i]); //Mostra o numero do quarto		
						printf("Reservado pelo Hospede %d\n",codhosp_reserva[i]);	 //Mostra o codigo do hospede que o reservou
						printf("Durante os dias %d/%d/%d\n",dia_inicio_reserva[i],mes_inicio_reserva[i],ano_inicio_reserva[i]); //Mostra o inicio da reserva
						printf("Ate os dias %d/%d/%d\n\n",dia_final_reserva[i],mes_final_reserva[i],ano_final_reserva[i]); //Mostra o final da reserva
					
					}else if(codigo_acomodacao == 1){
						if( a1>=quarto_reservado[i] && quarto_reservado[i] <=a2 ){
							printf("\nQuarto numero %d\n",quarto_reservado[i]); //Mostra o numero do quarto		
							printf("Reservado pelo Hospede %d\n",codhosp_reserva[i]);	 //Mostra o codigo do hospede que o reservou
							printf("Durante os dias %d/%d/%d\n",dia_inicio_reserva[i],mes_inicio_reserva[i],ano_inicio_reserva[i]); //Mostra o inicio da reserva
							printf("Ate os dias %d/%d/%d\n\n",dia_final_reserva[i],mes_final_reserva[i],ano_final_reserva[i]); //Mostra o final da reserva
						}
					}
				}				
			fclose(reservas);			
		}
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}
	
	else if(op == 2){
/***************************** Gera o arquivo ***********************************/
	for (i=n1; i<n2 ;i++){
		arq = fopen("RelatorioReservas.csv","a"); //Cria o arquivo CSV
		
		if(arq == NULL){
			printf("O arquivo nao pode ser aberto.\n");
			exit(0);
		}
		
		sprintf(numerodareserva, "%i", i+1);//converte interio em string
		strcpy (reserva, "dados\\reserva");//define valor a string
		strcat (reserva, numerodareserva); // junta duas strings
		strcat (reserva, txt); // junta duas strings
		
		reservas = fopen(reserva,"r");
		
		if(reservas != NULL){
			fscanf(reservas,"%i\n",&cod_reserva[i]);
			fscanf(reservas,"%i\n",&dia_inicio_reserva[i]);
			fscanf(reservas,"%i\n",&mes_inicio_reserva[i]);
			fscanf(reservas,"%i\n",&ano_inicio_reserva[i]);
			fscanf(reservas,"%i\n",&dias_reservado[i]);
			fscanf(reservas,"%i\n",&dia_final_reserva[i]);
			fscanf(reservas,"%i\n",&mes_final_reserva[i]);
			fscanf(reservas,"%i\n",&ano_final_reserva[i]);
			fscanf(reservas,"%i\n",&quarto_reservado[i]);
			fscanf(reservas,"%i",&codhosp_reserva[i]);
				
			if(codigo_acomodacao == 0){
		
			fprintf(arq,"Quarto numero; %d\n",quarto_reservado[i]);
			fprintf(arq,"Reservado pelo Hospede; %d\n",codhosp_reserva[i]);
			fprintf(arq,"Durante os dias; %d/%d/%d\n",dia_inicio_reserva[i],mes_inicio_reserva[i],ano_inicio_reserva[i]);
			fprintf(arq,"Ate os dias; %d/%d/%d\n\n", dia_final_reserva[i],mes_final_reserva[i],ano_final_reserva[i]);
						
			}else if(codigo_acomodacao == 1){
				if( a1>=quarto_reservado[i] && quarto_reservado[i] <=a2 ){
					fprintf(arq,"Quarto numero; %d\n",quarto_reservado[i]);
					fprintf(arq,"Reservado pelo Hospede; %d\n",codhosp_reserva[i]);
					fprintf(arq,"Durante os dias; %d/%d/%d\n",dia_inicio_reserva[i],mes_inicio_reserva[i],ano_inicio_reserva[i]);
					fprintf(arq,"Ate os dias; %d/%d/%d\n\n", dia_final_reserva[i],mes_final_reserva[i],ano_final_reserva[i]);
				}
			}						
		}			
		fclose(reservas);
		fclose(arq);
	}
	printf("Arquivo Gerado com Sucesso !!\n");
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
//////////////////////////////////////////////////////////////////////////////////
	}
}

int rProdutos(){
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i,j;
	FILE *prod;
	char txt[5] = ".txt";
	char numerodeprodutos[3];
	char openproduto[23];	
	int *codigo_produto = malloc(numero_de_produtos*sizeof(int));
	char *descricao[numero_de_produtos];
	for(j=0;j<numero_de_produtos;j++){
		descricao[j] = malloc(250 * sizeof(char));
	}
	int *estoque = malloc(numero_de_produtos * sizeof(int));
	int *estoque_min = malloc(numero_de_produtos * sizeof(int));
	float *preco_custo = malloc(numero_de_produtos * sizeof(float));
	float *preco_venda = malloc(numero_de_produtos * sizeof(float));
	FILE *arq; //Cria um ponteiro arq que apontara para o arquivo			
	arq = fopen("RelatorioProdutos.csv","w"); //Cria o arquivo CSV e apaga caso exista algun
	fclose(arq);
	//Pergunta ao usuario se ele deseja mostrar o relatorio na tela ou gerar um arquivo 
	int op, op2;
	printf("=====================================================================\n");
	printf("======================== Digite sua opcao:===========================\n");
	printf("=====================================================================\n");
	printf("======= 1. Exibir Relatorio na tela =================================\n");	
	printf("======= 2. Gerar arquivo com o relatorio ============================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	do{
		scanf("%d",&op);
	}while(op<1 || op >2);
	//////////////////////////////////////////////////////////////////////////////////////////
	
		int n1,n2;
		printf("==========================================\n");
		printf("== Deseja utilizar o filtro de Codigos? ==\n");
		printf("==========================================\n");
		printf("============== 1. Sim ====================\n");	
		printf("============== 2. Nao ====================\n");
		printf("==========================================\n");
		scanf("%d",&op2);
		
		if(op2 == 1){
			
			printf("=====================================================================\n");
			printf("===== De qual faixa de codigos deseja gerar o relatorio =============\n");
			printf("===== Inicio:");
			scanf("%d",&n1);
			n1=n1-1;
			printf("===== Fim:");
			scanf("%d",&n2);
			printf("=====================================================================\n");
			
		} else{
			n1 = 0;
			n2 = numero_de_produtos;
		}
		
		/* Exibe o relatorio na tela */
		if(op == 1){
			#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif
			for(i=n1;i<n2;i++){
				sprintf(numerodeprodutos, "%i", i+1);//converte interio em string
				strcpy (openproduto, "dados\\produto");//define valor a string
				strcat (openproduto, numerodeprodutos); // junta duas strings
				strcat (openproduto, txt); // junta duas strings
				
				prod = fopen(openproduto,"r");
				
				if(prod != NULL){
					fscanf(prod,"%d\n",&codigo_produto[i]);
					fscanf(prod,"\n%[^\n]s",descricao[i]);		
					fscanf(prod,"%d\n",&estoque[i]);
					fscanf(prod,"%d\n",&estoque_min[i]);
					fscanf(prod,"%f\n",&preco_custo[i]);
					fscanf(prod,"%f",&preco_venda[i]);					
					printf("Codigo do Produto: %d\n",codigo_produto[i]);
					printf("Descricao Do Produto: %s\n",descricao[i]);					
					printf("Estoque: %d\n",estoque[i]);
					printf("Estoque Minimo: %d\n",estoque_min[i]);					
					printf("Preco de Custo: %.2f\n",preco_custo[i]);
					printf("Preco de Venda: %.2f\n\n",preco_venda[i]);
				}
				fclose(prod);
			}
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		}
		///////////////////////////////
		/* Gera o arquivo */
		else if(op == 2) {
			for(i=n1;i<n2;i++){
				sprintf(numerodeprodutos, "%i", i+1);//converte interio em string
				strcpy (openproduto, "dados\\produto");//define valor a string
				strcat (openproduto, numerodeprodutos); // junta duas strings
				strcat (openproduto, txt); // junta duas strings
				
				prod = fopen(openproduto,"r");
				if(prod != NULL){
					
					fscanf(prod,"%i\n",&codigo_produto[i]);
					fscanf(prod,"\n%[^\n]s",descricao[i]);						
					fscanf(prod,"%i\n",&estoque[i]);
					fscanf(prod,"%i\n",&estoque_min[i]);
					fscanf(prod,"%f\n",&preco_custo[i]);
					fscanf(prod,"%f",&preco_venda[i]);
					
					arq = fopen("RelatorioProdutos.csv","a"); //Cria o arquivo CSV
					
					if(arq == NULL){
						printf("O arquivo nao pode ser aberto.\n");
						exit(0);
					}
					
					fprintf(arq,"Codigo do Produto; %i\n",codigo_produto[i]);
					fprintf(arq,"Descricao do Produto; %s\n",descricao[i]);
					fprintf(arq,"Estoque; %i\n",estoque[i]);
					fprintf(arq,"Estoque Minimo; %i\n",estoque_min[i]);
					fprintf(arq,"Preco de Custo; %.2f\n",preco_custo[i]);
					fprintf(arq,"Preco de Venda; %.2f\n\n",preco_venda[i]);
					fclose(arq);
					
				}
				fclose(prod);
			}
		printf("Relatorio Gerado com sucesso!!\n");
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}
//////////////////////////////////////////////////	
}

int rProdutos_estoque(){

	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i;
	FILE *prod;
	char txt[5] = ".txt";
	char numerodeprodutos[3];
	char openproduto[23];	
	int *codigo_produto = malloc(numero_de_produtos*sizeof(int));
	char *descricao[numero_de_produtos];
	for(i=0;i<numero_de_produtos;i++){
		descricao[i] = malloc(250 * sizeof(char));
	}
	int *estoque = malloc(numero_de_produtos * sizeof(int));
	int *estoque_min = malloc(numero_de_produtos * sizeof(int));
	float *preco_custo = malloc(numero_de_produtos * sizeof(float));
	float *preco_venda = malloc(numero_de_produtos * sizeof(float));
	FILE *arq; //Cria um ponteiro arq que apontara para o arquivo			
	arq = fopen("RelatorioProdutos_estoqueminimo.csv","w"); //Cria o arquivo CSV e apaga caso aja algun antigo
	fclose(arq);
	
	/*Pergunta ao usuario se ele deseja mostrar o relatorio na tela ou gerar um arquivo */
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	int op, op2;
	printf("=====================================================================\n");
	printf("======================== Digite sua opcao:===========================\n");
	printf("=====================================================================\n");
	printf("======= 1. Exibir Relatorio na tela =================================\n");	
	printf("======= 2. Gerar arquivo com o relatorio ============================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	do{
		scanf("%d",&op);
	}while(op<1 || op >2);
	//////////////////////////////////////////////////////////////////////////////////////////
	
	int n1,n2;
	printf("==========================================\n");
	printf("== Deseja utilizar o filtro de Codigos? ==\n");
	printf("==========================================\n");
	printf("============== 1. Sim ====================\n");	
	printf("============== 2. Nao ====================\n");
	printf("==========================================\n");
	scanf("%d",&op2);
	
	if(op2 == 1){
		
		printf("=====================================================================\n");
		printf("===== De qual faixa de codigos deseja gerar o relatorio =============\n");
		printf("===== Inicio:");
		scanf("%d",&n1);
		n1--;
		printf("===== Fim:");
		scanf("%d",&n2);
		printf("=====================================================================\n");
		
	} else{
		n1 = 0;
		n2 = numero_de_produtos;
	}
	
	/* Exibe o relatorio na tela */
	if(op == 1){
		
		for(i=n1;i<=n2;i++){
			sprintf(numerodeprodutos, "%i", i+1);//converte interio em string
			strcpy (openproduto, "dados\\produto");//define valor a string
			
			strcat (openproduto, numerodeprodutos); // junta duas strings
			strcat (openproduto, txt); // junta duas strings
			
			prod = fopen(openproduto,"r");
			
			if (prod != NULL){
				fscanf(prod,"%i\n",&codigo_produto[i]);
				fscanf(prod,"\n%[^\n]s",descricao[i]);					
				fscanf(prod,"%i\n",&estoque[i]);
				fscanf(prod,"%i\n",&estoque_min[i]);
				fscanf(prod,"%f\n",&preco_custo[i]);
				fscanf(prod,"%f\n",&preco_venda[i]);
				
				if (estoque_min[i]>estoque[i]){
					printf("Codigo do Produto: %i\n",codigo_produto[i]);
					printf("Descricao Do Produto: %s\n",descricao[i]);					
					printf("Estoque: %i\n",estoque[i]);
					printf("Estoque Minimo: %i\n",estoque_min[i]);					
					printf("Preco de Custo: %.2f\n",preco_custo[i]);
					printf("Preco de Venda: %.2f\n",preco_venda[i]);
				}
			}
			fclose(prod);
		}
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}
			
	///////////////////////////////
	/* Gera o arquivo */
	else if(op == 2) {
			
		for(i=n1;i<=n2;i++){
			sprintf(numerodeprodutos, "%i", i+1);//converte interio em string
			strcpy (openproduto, "dados\\produto");//define valor a string
			strcat (openproduto, numerodeprodutos); // junta duas strings
			strcat (openproduto, txt); // junta duas strings
			
			prod = fopen(openproduto,"r");
			
			if(prod != NULL){
				fscanf(prod,"%i\n",&codigo_produto[i]);
				fscanf(prod,"\n%[^\n]s",descricao[i]);		
				fscanf(prod,"%i\n",&estoque[i]);
				fscanf(prod,"%i\n",&estoque_min[i]);
				fscanf(prod,"%f\n",&preco_custo[i]);
				fscanf(prod,"%f",&preco_venda[i]);
				
						
				arq = fopen("RelatorioProdutos_estoqueminimo.csv","a"); //Cria o arquivo CSV
				
				if(arq == NULL){
					printf("O arquivo nao pode ser aberto.\n");
					exit(0);
				}
				
				if (estoque_min[i]>estoque[i]){
					fprintf(arq,"Codigo do Produto; %i\n",codigo_produto[i]);
					fprintf(arq,"Descricao do Produto; %s\n",descricao[i]);
					fprintf(arq,"Estoque; %i\n",estoque[i]);
					fprintf(arq,"Estoque Minimo; %i\n",estoque_min[i]);
					fprintf(arq,"Preco de Custo; %.2f\n",preco_custo[i]);
					fprintf(arq,"Preco de Venda; %.2f\n\n",preco_venda[i]);
				}
				fclose(arq);
			}
			fclose(prod);		
		}
		printf("Relatorio Gerado com sucesso!!\n");
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}	
//////////////////////////////////////////////////
}

int rContas_receber(){
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i,j,dia_filtro,mes_filtro,ano_filtro;
	char ql;
	int numero_linhas=0,alocar,exibir;
	FILE *contas;
	
	contas = fopen("dados\\contas.txt","r");
	while((ql = fgetc(contas)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(contas);

	alocar=numero_linhas/5;
	
	int *dia_receber = malloc(alocar*sizeof(int));
	int *mes_receber = malloc(alocar*sizeof(int));
	int *ano_receber = malloc(alocar*sizeof(int));
	float *valor = malloc(alocar*sizeof(float));
	char *descricao[alocar];

	contas = fopen("dados\\contas.txt","r");
	
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		fscanf(contas,"%d\n",&dia_receber[i]);
		fscanf(contas,"%d\n",&mes_receber[i]);
		fscanf(contas,"%d\n",&ano_receber[i]);
		fscanf(contas,"%f\n",&valor[i]);
		fscanf(contas,"\n%[^\n]s",descricao[i]);
	}
	fclose(contas);	
	
	
	FILE *arq; //Cria um ponteiro arq que apontara para o arquivo			
	arq = fopen("RelatorioContas_receber.csv","w"); //Cria o arquivo CSV e apaga caso exista algun
	fclose(arq);
	//Pergunta ao usuario se ele deseja mostrar o relatorio na tela ou gerar um arquivo 
	int op, op2;
	printf("=====================================================================\n");
	printf("======================== Digite sua opcao:===========================\n");
	printf("=====================================================================\n");
	printf("======= 1. Exibir Relatorio na tela =================================\n");	
	printf("======= 2. Gerar arquivo com o relatorio ============================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	do{
		scanf("%d",&op);
	}while(op<1 || op >2);
	//////////////////////////////////////////////////////////////////////////////////////////
	
	printf("==========================================\n");
	printf("== Deseja utilizar o filtro de data? =====\n");
	printf("==========================================\n");
	printf("============== 1. Sim ====================\n");	
	printf("============== 2. Nao ====================\n");
	printf("==========================================\n");
	scanf("%d",&op2);

	if(op2 == 1){
		printf("=====================================================================\n");
		printf("===== Data de Filtragem, a partir de qual data ======================\n");
		printf("===== dia:");
		scanf("%d",&dia_filtro);
		printf("===== Mes:");
		scanf("%d",&mes_filtro);
		printf("===== Ano:");
		scanf("%d",&ano_filtro);
		printf("=====================================================================\n");
	}
	
	/* Exibe o relatorio na tela */
	if(op == 1){
		for(i=0;i<alocar;i++){
			exibir=1;
			if(op2==1){
				exibir=0;
				if(ano_filtro == ano_receber[i]){
					if(mes_filtro == mes_receber[i]){
						if(dia_filtro <dia_receber[i]){
							exibir=1;
						}
					}else if(mes_filtro < mes_receber[i]){
						exibir=1;
					}else if(mes_filtro > mes_receber[i]){
						exibir=0;
					}
				}else if(ano_filtro > ano_receber[i]){
					exibir =0;
				}else if(ano_filtro < ano_receber[i]){
					exibir=1;
				}
			}
			if(exibir==1){
				printf("Descricao: %s\n",descricao[i]);
				printf("Valor: %.2f\n",valor[i]);
				printf("Data: %d/%d/%d\n",dia_receber[i],mes_receber[i],ano_receber[i]);
				printf("=====================================================================\n");
			}
		}
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}
		///////////////////////////////
		/* Gera o arquivo */
	else if(op == 2) {
		for(i=0;i<alocar;i++){
			arq = fopen("RelatorioContas_receber.csv","a"); //Cria o arquivo CSV
			for(i=0;i<alocar;i++){
				exibir=1;
				if(op2==1){
					exibir=0;
					if(ano_filtro == ano_receber[i]){
						if(mes_filtro == mes_receber[i]){
							if(dia_filtro <dia_receber[i]){
								exibir=1;
							}
						}else if(mes_filtro < mes_receber[i]){
							exibir=1;
						}else if(mes_filtro > mes_receber[i]){
							exibir=0;
						}
					}else if(ano_filtro > ano_receber[i]){
						exibir =0;
					}else if(ano_filtro < ano_receber[i]){
						exibir=1;
					}
				}
				if(exibir==1){
					fprintf(arq,"Descricao; %s\n",descricao[i]);
					fprintf(arq,"Valor; %.2f\n",valor[i]);
					fprintf(arq,"Data; %d/%d/%d\n",dia_receber[i],mes_receber[i],ano_receber[i]);
					printf("=====================================================================\n");
				}
			}
			fclose(arq);
		}
		printf("Relatorio Gerado com sucesso!!\n");
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}
}

int rContas_pagar(){
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i,j,dia_filtro,mes_filtro,ano_filtro;
	char ql;
	int numero_linhas=0,alocar,exibir;
	FILE *contas;
	
	contas = fopen("dados\\pagar.txt","r");
	while((ql = fgetc(contas)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(contas);

	alocar=numero_linhas/5;
	
	int *dia_pagar = malloc(alocar*sizeof(int));
	int *mes_pagar = malloc(alocar*sizeof(int));
	int *ano_pagar = malloc(alocar*sizeof(int));
	float *valor = malloc(alocar*sizeof(float));
	char *descricao[alocar];

	contas = fopen("dados\\pagar.txt","r");
	
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		fscanf(contas,"%d\n",&dia_pagar[i]);
		fscanf(contas,"%d\n",&mes_pagar[i]);
		fscanf(contas,"%d\n",&ano_pagar[i]);
		fscanf(contas,"%f\n",&valor[i]);
		fscanf(contas,"\n%[^\n]s",descricao[i]);
	}
	fclose(contas);	
	
	
	FILE *arq; //Cria um ponteiro arq que apontara para o arquivo			
	arq = fopen("RelatorioContas_pagar.csv","w"); //Cria o arquivo CSV e apaga caso exista algun
	fclose(arq);
	//Pergunta ao usuario se ele deseja mostrar o relatorio na tela ou gerar um arquivo 
	int op, op2;
	printf("=====================================================================\n");
	printf("======================== Digite sua opcao:===========================\n");
	printf("=====================================================================\n");
	printf("======= 1. Exibir Relatorio na tela =================================\n");	
	printf("======= 2. Gerar arquivo com o relatorio ============================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	do{
		scanf("%d",&op);
	}while(op<1 || op >2);
	//////////////////////////////////////////////////////////////////////////////////////////
	
	printf("==========================================\n");
	printf("== Deseja utilizar o filtro de data? =====\n");
	printf("==========================================\n");
	printf("============== 1. Sim ====================\n");	
	printf("============== 2. Nao ====================\n");
	printf("==========================================\n");
	scanf("%d",&op2);

	if(op2 == 1){
		printf("=====================================================================\n");
		printf("===== Data de Filtragem, a partir de qual data ======================\n");
		printf("===== dia:");
		scanf("%d",&dia_filtro);
		printf("===== Mes:");
		scanf("%d",&mes_filtro);
		printf("===== Ano:");
		scanf("%d",&ano_filtro);
		printf("=====================================================================\n");
	}
	
	/* Exibe o relatorio na tela */
	if(op == 1){
		for(i=0;i<alocar;i++){
			exibir=1;
			if(op2==1){
				exibir=0;
				if(ano_filtro == ano_pagar[i]){
					if(mes_filtro == mes_pagar[i]){
						if(dia_filtro <dia_pagar[i]){
							exibir=1;
						}
					}else if(mes_filtro < mes_pagar[i]){
						exibir=1;
					}else if(mes_filtro > mes_pagar[i]){
						exibir=0;
					}
				}else if(ano_filtro > ano_pagar[i]){
					exibir =0;
				}else if(ano_filtro < ano_pagar[i]){
					exibir=1;
				}
			}
			if(exibir==1){
				printf("Descricao: %s\n",descricao[i]);
				printf("Valor: %.2f\n",valor[i]);
				printf("Data: %d/%d/%d\n",dia_pagar[i],mes_pagar[i],ano_pagar[i]);
				printf("=====================================================================\n");
			}
		}
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}
		///////////////////////////////
		/* Gera o arquivo */
	else if(op == 2) {
		for(i=0;i<alocar;i++){
			arq = fopen("RelatorioContas_pagar.csv","a"); //Cria o arquivo CSV
			for(i=0;i<alocar;i++){
				exibir=1;
				if(op2==1){
					exibir=0;
					if(ano_filtro == ano_pagar[i]){
						if(mes_filtro == mes_pagar[i]){
							if(dia_filtro <dia_pagar[i]){
								exibir=1;
							}
						}else if(mes_filtro < mes_pagar[i]){
							exibir=1;
						}else if(mes_filtro > mes_pagar[i]){
							exibir=0;
						}
					}else if(ano_filtro > ano_pagar[i]){
						exibir =0;
					}else if(ano_filtro < ano_pagar[i]){
						exibir=1;
					}
				}
				if(exibir==1){
					fprintf(arq,"Descricao; %s\n",descricao[i]);
					fprintf(arq,"Valor; %.2f\n",valor[i]);
					fprintf(arq,"Data; %d/%d/%d\n",dia_pagar[i],mes_pagar[i],ano_pagar[i]);
					printf("=====================================================================\n");
				}
			}
			fclose(arq);
		}
		printf("Relatorio Gerado com sucesso!!\n");
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}
}

int rCaixa(){
	
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
	int i,j,dia_filtro,mes_filtro,ano_filtro;
	char ql;
	int numero_linhas=0,alocar,exibir;
	FILE *contas;
	
	contas = fopen("dados\\Historico completo.txt","r");
	while((ql = fgetc(contas)) != EOF ){
		if (ql == '\n'){
			numero_linhas++;
		}
	}
	fclose(contas);

	alocar=numero_linhas/4;
	
	float *valor = malloc(alocar*sizeof(float));
	float *caixa = malloc(alocar*sizeof(float));
	char *descricao[alocar];
	char *data[alocar];

	contas = fopen("dados\\Historico completo.txt","r");
	
	for(i=0;i<alocar;i++){
		descricao[i] = malloc(300*sizeof(char));
		data[i] = malloc(15*sizeof(char));
		fscanf(contas,"\n%[^\n]s",descricao[i]);
		fscanf(contas,"%f\n",&valor[i]);
		fscanf(contas,"%f\n",&caixa[i]);
		fscanf(contas,"\n%[^\n]s",data[i]);
	}
	fclose(contas);	
	
	FILE *arq; //Cria um ponteiro arq que apontara para o arquivo			
	arq = fopen("RelatorioCaixa.csv","w"); //Cria o arquivo CSV e apaga caso exista algun
	fclose(arq);
	//Pergunta ao usuario se ele deseja mostrar o relatorio na tela ou gerar um arquivo 
	int op, op2;
	printf("=====================================================================\n");
	printf("======================== Digite sua opcao:===========================\n");
	printf("=====================================================================\n");
	printf("======= 1. Exibir Relatorio na tela =================================\n");	
	printf("======= 2. Gerar arquivo com o relatorio ============================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	do{
		scanf("%d",&op);
	}while(op<1 || op >2);
	//////////////////////////////////////////////////////////////////////////////////////////
	
	/* Exibe o relatorio na tela */
	if(op == 1){
		for(i=0;i<alocar;i++){
			exibir=1;
			if(exibir==1){
				printf("Descricao: %s\n",descricao[i]);
				printf("Valor: %.2f\n",valor[i]);
				printf("Caixa: %.2f\n",caixa[i]);
				printf("Data: %s\n",data[i]);
				printf("=====================================================================\n");
			}
		}
	printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}
		///////////////////////////////
		/* Gera o arquivo */
	else if(op == 2) {
		for(i=0;i<alocar;i++){
			arq = fopen("RelatorioCaixa.csv","a"); //Cria o arquivo CSV
			for(i=0;i<alocar;i++){
				exibir=1;
				if(exibir==1){
					fprintf(arq,"Descricao; %s\n",descricao[i]);
					fprintf(arq,"Valor; %.2f\n",valor[i]);
					fprintf(arq,"Caixa; %.2f\n",caixa[i]);
					fprintf(arq,"Data; %s\n\n",data[i]);
					//printf("=====================================================================\n");
				}
			}
			fclose(arq);
		}
		printf("Relatorio Gerado com sucesso!!\n");
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
	}
}

int modulofeedback(){
	
	int categoriadesejada;
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("======================== Gerar Relatorios ===========================\n");
	printf("=====================================================================\n");
	printf("===== 1. Hospedes ===================================================\n");
	printf("===== 2. Acomodacoes ================================================\n");
	printf("===== 3. Reservas ===================================================\n");
	printf("===== 4. Produtos de Consumo ========================================\n");
	printf("===== 5. Produtos em Estoque Minimo =================================\n");
	printf("===== 6. Contas a Receber ===========================================\n");
	printf("===== 7. Contas a Pagar =============================================\n");
	printf("===== 8. Movimentacao de Caixa =====================================\n");
	printf("===== 9. Voltar ====================================================\n");
	printf("===== 0. Sair do Sistema ============================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	scanf("%d", &categoriadesejada);
	
	switch (categoriadesejada){
		case 1:
			rHospedes();
		break;
		case 2:
			rAcomodacoes();
		break;
		case 3:
			rReservas();
		break;
		case 4:
			rProdutos();
		break;
		case 5:
			rProdutos_estoque();
		break;
		case 6:
			rContas_receber();
		break;	
		case 7:
			rContas_pagar();
		break;	
		case 8:
			rCaixa();
		break;	
		case 9:
			main();
		break;
		case 0:
			exit(0);
		break;
		default:
			modulofeedback();
	}
	modulofeedback();
}


////////////////////////
//modulo 5 /////////////
////////////////////////

int importardados(){
	FILE *import, *hotel;
	int repetir,op,opcao,fim=0;
	
	char txt[5] = ".txt";
	FILE *numhospedes,*hosp,*acomod,*num_acomodacoes,*num_cat_acomodacoes,*produto,*numprodutos,*forn,*numfornecedores;
	char numerodefornecedores[3],newfornecedor[23],numerodehospedes[3],newhospede[23],numerodaacomodacao[3];
	char newacomodacao[23],numerodacategoriaacomodacao[3],newcat_acomodacao[23],numerodeprodutos[3],newproduto[23];

	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("========= Para Importação dos dados, usa-se um arquivo XML ==========\n");
	printf("=========== O arquivo deve esta na pasta raiz do sistema ============\n");
	printf("=====================================================================\n");
	printf("======= 1. Continuar                               2.Voltar =========\n");
	printf("=====================================================================\n");
	do{
		repetir=0;
		scanf("%d",&op);
		switch(op){
			case 1:
				printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
			break;
			case 2:
				 modulodados();
			break;
			default:
				repetir=1;
		}
	}while(repetir==1);
	
	import = fopen("dados.xml","r");
	if(import == NULL){
		printf("!Arquivo nao pode ser aberto, tente novamente mais tarde!");
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		//fclose(import);
		importardados();
	}
	
	char *dados = malloc(10*sizeof(char));
	char *tabela = malloc(10*sizeof(char));
	char *trash = malloc(10*sizeof(char));
	char *registro = malloc(15*sizeof(char));
	char *verifica = malloc(15*sizeof(char));
	fscanf(import,"%[^\n]s",dados);
	char lixo;
	fscanf(import,"\n%[^\n]s",tabela);
	
	do{
		fflush(stdin); // limpa o buffer do teclado
		if((strcmp(tabela,"<tabela-hospede>") ==0)  || (strcmp(tabela,"<tabela-Hospede>") ==0)){
			char *codigo_hospede = malloc(5*sizeof(char));
			char *nome_hospede = malloc(50*sizeof(char));
			char *rua_hospede = malloc(50*sizeof(char));
			char *numero_hospede = malloc(12*sizeof(char));
			char *bairro_hospede = malloc(50*sizeof(char));
			char *cidade_hospede = malloc(50*sizeof(char));
			char *uf_hospede = malloc(5*sizeof(char));
			char *telefone_hospede = malloc(15*sizeof(char));
			char *data_nascimento_hospede = malloc(15*sizeof(char));
			char *estadocivil_hospede = malloc(15*sizeof(char));
			char *sexo_hospede = malloc(15*sizeof(char));
			char *email_hospede = malloc(50*sizeof(char));
			char *cpf_hospede = malloc(15*sizeof(char));
			
			printf("=====================================================================\n");
			printf("======== Deseja Importar os dados de Hospedes? ======================\n");
			printf("======== 1. Sim\n======== 2. Nao\n");
			do{
				repetir=0;
				scanf("%d",&opcao);
				if(opcao <1 || opcao >2){
					repetir=1;
				}
			}while(repetir==1);
			printf("=====================================================================\n");
			fscanf(import,"\n%[^\n]s",registro);
			do{
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",codigo_hospede);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",nome_hospede);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",rua_hospede);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",numero_hospede);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",bairro_hospede);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",cidade_hospede);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",uf_hospede);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",cpf_hospede);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",telefone_hospede);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",email_hospede);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",sexo_hospede);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",estadocivil_hospede);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",data_nascimento_hospede);
				fscanf(import,"\n%[^\n]s",trash);
			
				fscanf(import,"\n%[^\n]s",registro);
				if(opcao ==1){
					printf("%s\n",registro);
					printf("%s\n",codigo_hospede);
					printf("%s\n",nome_hospede);
		
					printf("%s\n",rua_hospede);
					printf("%s\n",numero_hospede);
					printf("%s\n",bairro_hospede);
					printf("%s\n",cidade_hospede);
					printf("%s\n",uf_hospede);
					
					printf("%s\n",cpf_hospede);
					printf("%s\n",telefone_hospede);
					printf("%s\n",email_hospede);
					printf("%s\n",sexo_hospede);
					printf("%s\n",estadocivil_hospede);
					printf("%s\n",data_nascimento_hospede);
					printf("=====================================================================\n");
					
					numero_de_hospedes = numero_de_hospedes+1;
					sprintf(numerodehospedes, "%i", numero_de_hospedes);//converte interio em string
					strcpy (newhospede, "dados\\hospede");
					strcat (newhospede, numerodehospedes); // junta duas strings
					strcat (newhospede, txt); // junta duas strings
					
					hosp = fopen(newhospede,"w");

					fprintf(hosp,"%d\n",numero_de_hospedes);
					fprintf(hosp,"%s\n",nome_hospede);
					fprintf(hosp,"%s\n",email_hospede);
					fprintf(hosp,"%s\n",sexo_hospede);
					fprintf(hosp,"%s\n",estadocivil_hospede);
					fprintf(hosp,"%s\n",rua_hospede);
					fprintf(hosp,"%s\n",numero_hospede);;
					fprintf(hosp,"%s\n",bairro_hospede);
					fprintf(hosp,"%s\n",cidade_hospede);
					fprintf(hosp,"%s\n",uf_hospede);
					fprintf(hosp,"%s\n",cpf_hospede);
					fprintf(hosp,"%s\n",telefone_hospede);
					fprintf(hosp,"%s",data_nascimento_hospede);
					fclose(hosp);
					
					numhospedes = fopen("dados\\Nhospedes.txt","w");
					fprintf(numhospedes,"%d",numero_de_hospedes);
					fclose(numhospedes);
				}
				fscanf(import,"\n%[^\n]s",verifica);
			}while(strcmp(verifica,"<registro>")==0);
		}
		else if((strcmp(tabela,"<tabela-acomodacao>") ==0)  || (strcmp(tabela,"<tabela-Acomodacao>") ==0)){
			char *codigo_acomodacao = malloc(5*sizeof(char));
			char *descricao_acomodacao = malloc(250*sizeof(char));
			char *facilidades_acomodacao = malloc(250*sizeof(char));
			char *tipo_acomodacao = malloc(5*sizeof(char));
			
			printf("=====================================================================\n");
			printf("======== Deseja Importar os dados de Acomodacoes? ===================\n");
			printf("======== 1. Sim\n======== 2. Nao\n");
			do{
				repetir=0;
				scanf("%d",&opcao);
				if(opcao <1 || opcao >2){
					repetir=1;
				}
			}while(repetir==1);
			
			fscanf(import,"\n%[^\n]s",registro);
			do{
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",codigo_acomodacao);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",descricao_acomodacao);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",facilidades_acomodacao);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",tipo_acomodacao);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n]s",registro);
				
				if(opcao==1){
					printf("%s\n",codigo_acomodacao);
					printf("%s\n",descricao_acomodacao);
					printf("%s\n",facilidades_acomodacao);
					printf("%s\n",tipo_acomodacao);
					printf("=====================================================================\n");

					numero_de_acomodacoes = numero_de_acomodacoes+1;
					sprintf(numerodaacomodacao, "%i", numero_de_acomodacoes);//converte interio em string
					strcpy (newacomodacao, "dados\\acomodacao");
					strcat (newacomodacao, numerodaacomodacao); // junta duas strings
					strcat (newacomodacao, txt); // junta duas strings

					acomod = fopen(newacomodacao,"w");

					fprintf(acomod,"%d\n",numero_de_acomodacoes);
					fprintf(acomod,"%s\n",descricao_acomodacao);
					fprintf(acomod,"%s\n",facilidades_acomodacao);
					fprintf(acomod,"%s",tipo_acomodacao);
					fclose(acomod);
					
					num_acomodacoes = fopen("dados\\Nacomodacoes.txt","w");
					fprintf(num_acomodacoes,"%i",numero_de_acomodacoes);
					fclose(num_acomodacoes);	
				}
				fscanf(import,"\n%[^\n]s",verifica);
			}while(strcmp(verifica,"<registro>")==0);
		}
		else if((strcmp(tabela,"<tabela-TipoAcomodacao>") ==0)  || (strcmp(tabela,"<tabela-tipoacomodacao>") ==0)){
			char *codigo_tipo_acomodacao = malloc(5*sizeof(char));
			char *descricao_tipo_acomodacao = malloc(250*sizeof(char));
			char *valor_tipo_acomodacao = malloc(250*sizeof(char));
			char *qtdhosp_tipo_acomodacao = malloc(5*sizeof(char));
			
			printf("=====================================================================\n");
			printf("======== Deseja Importar os dados de Tipo de Acomodacao? ============\n");
			printf("======== 1. Sim\n======== 2. Nao\n");
			do{
				repetir=0;
				scanf("%d",&opcao);
				if(opcao <1 || opcao >2){
					repetir=1;
				}
			}while(repetir==1);
			
			fscanf(import,"\n%[^\n]s",registro);
			do{
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",codigo_tipo_acomodacao);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",descricao_tipo_acomodacao);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",valor_tipo_acomodacao);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",qtdhosp_tipo_acomodacao);
				fscanf(import,"\n%[^\n]s",trash);
				
			
				fscanf(import,"\n%[^\n]s",registro);
				
				if(opcao==1){
					printf("%s\n",codigo_tipo_acomodacao);
					printf("%s\n",descricao_tipo_acomodacao);
					printf("%s\n",valor_tipo_acomodacao);
					printf("%s\n",qtdhosp_tipo_acomodacao);
					printf("=====================================================================\n");
					
					numero_de_tipo_acomodacoes = numero_de_tipo_acomodacoes+1;
					sprintf(numerodacategoriaacomodacao, "%i", numero_de_tipo_acomodacoes);//converte interio em string
					strcpy (newcat_acomodacao, "dados\\tacomodacao");
					strcat (newcat_acomodacao, numerodacategoriaacomodacao); // junta duas strings
					strcat (newcat_acomodacao, txt); // junta duas strings
	
					acomod = fopen(newcat_acomodacao,"w");
				
					fprintf(acomod,"%d\n",numero_de_tipo_acomodacoes);
					fprintf(acomod,"%s\n",descricao_tipo_acomodacao);
					fprintf(acomod,"%s\n",valor_tipo_acomodacao);
					fprintf(acomod,"%s",qtdhosp_tipo_acomodacao);
					
					fclose(acomod);

					num_cat_acomodacoes = fopen("dados\\Ntipoacomodacoes.txt","w");
					fprintf(num_cat_acomodacoes,"%i",numero_de_tipo_acomodacoes);
					fclose(num_cat_acomodacoes);	
					
				}
				fscanf(import,"\n%[^\n]s",verifica);
			}while(strcmp(verifica,"<registro>")==0);
		}
		else if((strcmp(tabela,"<tabela-Produtos>") ==0)  || (strcmp(tabela,"<tabela-produtos>") ==0)){
			char *codigo_produto = malloc(5*sizeof(char));

			char *descricao_produto = malloc(250*sizeof(char));
			char *estoque_produto = malloc(5*sizeof(char));
			char *estoque_minimo_produto = malloc(5*sizeof(char));
			char *preco_custo_produto = malloc(5*sizeof(char));
			char *preco_venda_produto = malloc(5*sizeof(char));
			
			printf("=====================================================================\n");
			printf("======== Deseja Importar os dados de Produtos? ======================\n");
			printf("======== 1. Sim\n======== 2. Nao\n");
			do{
				repetir=0;
				scanf("%d",&opcao);
				if(opcao <1 || opcao >2){
					repetir=1;
				}
			}while(repetir==1);
			
			fscanf(import,"\n%[^\n]s",registro);
			do{
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",codigo_produto);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",descricao_produto);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",estoque_produto);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",estoque_minimo_produto);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",preco_custo_produto);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",preco_venda_produto);
				fscanf(import,"\n%[^\n]s",trash);
				
			
				fscanf(import,"\n%[^\n]s",registro);
				
				if(opcao==1){
					printf("%s\n",codigo_produto);
					printf("%s\n",descricao_produto);
					printf("%s\n",estoque_produto);
					printf("%s\n",estoque_minimo_produto);
					printf("%s\n",preco_custo_produto);
					printf("%s\n",preco_venda_produto);
					printf("=====================================================================\n");
	
					numero_de_produtos = numero_de_produtos+1;
					sprintf(numerodeprodutos, "%i", numero_de_produtos);//converte interio em string
					strcpy (newproduto, "dados\\produto");
					strcat (newproduto, numerodeprodutos); // junta duas strings
					strcat (newproduto, txt); // junta duas strings

					
					
					produto = fopen(newproduto,"w");

					fprintf(produto,"%d\n",numero_de_produtos);
					fprintf(produto,"%s\n",descricao_produto);
					fprintf(produto,"%s\n",estoque_produto);
					fprintf(produto,"%s\n",estoque_minimo_produto);
					fprintf(produto,"%s\n",preco_custo_produto);
					fprintf(produto,"%s\n",preco_venda_produto);
					
					fclose(produto);
					
					numprodutos = fopen("dados\\Nprodutos.txt","w");
					fprintf(numprodutos,"%d",numero_de_produtos);
					fclose(numprodutos);

				}
				
				fscanf(import,"\n%[^\n]s",verifica);
			}while(strcmp(verifica,"<registro>")==0);
		
		}
		else if((strcmp(tabela,"<tabela-Fornecedor>") ==0)  || (strcmp(tabela,"<tabela-fornecedor>") ==0)){
			char *codigo_fornecedor = malloc(5*sizeof(char));
			char *nome_fornecedor = malloc(50*sizeof(char));
			char *razaosocial_fornecedor = malloc(50*sizeof(char));
			char *email_fornecedor = malloc(50*sizeof(char));
			char *inscricaoestadual_fornecedor = malloc(20*sizeof(char));
			char *cnpj_fornecedor = malloc(20*sizeof(char));
			char *rua_fornecedor = malloc(50*sizeof(char));
			char *numero_fornecedor = malloc(12*sizeof(char));
			char *bairro_fornecedor = malloc(50*sizeof(char));
			char *cidade_fornecedor = malloc(50*sizeof(char));
			char *uf_fornecedor = malloc(5*sizeof(char));
			char *telefone_fornecedor = malloc(15*sizeof(char));
			
			printf("=====================================================================\n");
			printf("======== Deseja Importar os dados de Fornecedores? ==================\n");
			printf("======== 1. Sim\n======== 2. Nao\n");
			do{
				repetir=0;
				scanf("%d",&opcao);
				if(opcao <1 || opcao >2){
					repetir=1;
				}
			}while(repetir==1);
			
			fscanf(import,"\n%[^\n]s",registro);
			do{
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",codigo_fornecedor);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",nome_fornecedor);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",razaosocial_fornecedor);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",inscricaoestadual_fornecedor);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",cnpj_fornecedor);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",rua_fornecedor);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",numero_fornecedor);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",bairro_fornecedor);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",cidade_fornecedor);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",uf_fornecedor);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",telefone_fornecedor);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",email_fornecedor);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n]s",registro);
				
				if(opcao==1){
					printf("%s\n",codigo_fornecedor);
					printf("%s\n",nome_fornecedor);
					printf("%s\n",razaosocial_fornecedor);
					printf("%s\n",email_fornecedor);
					printf("%s\n",inscricaoestadual_fornecedor);
					printf("%s\n",cnpj_fornecedor);
					printf("%s\n",rua_fornecedor);
					printf("%s\n",numero_fornecedor);
					printf("%s\n",bairro_fornecedor);
					printf("%s\n",cidade_fornecedor);
					printf("%s\n",uf_fornecedor);
					printf("%s\n",telefone_fornecedor);
					printf("=====================================================================\n");
					
					numero_de_fornecedores = numero_de_fornecedores+1;
					sprintf(numerodefornecedores, "%i", numero_de_fornecedores);//converte interio em string
					strcpy (newfornecedor, "dados\\fornecedor");
					strcat (newfornecedor, numerodefornecedores); // junta duas strings
					strcat (newfornecedor, txt); // junta duas strings


					forn = fopen(newfornecedor,"w");

					fprintf(forn,"%d\n",numero_de_fornecedores);
					fprintf(forn,"%s\n",nome_fornecedor);
					fprintf(forn,"%s\n",razaosocial_fornecedor);
					fprintf(forn,"%s\n",email_fornecedor);
					fprintf(forn,"%s\n",inscricaoestadual_fornecedor);
					fprintf(forn,"%s\n",cnpj_fornecedor);
					fprintf(forn,"%s\n",rua_fornecedor);
					fprintf(forn,"%s\n",numero_fornecedor);
					fprintf(forn,"%s\n",bairro_fornecedor);
					fprintf(forn,"%s\n",cidade_fornecedor);
					fprintf(forn,"%s\n",uf_fornecedor);
					fprintf(forn,"%s\n",telefone_fornecedor);
					
					fclose(forn);
					
					numfornecedores = fopen("dados\\Nfornecedores.txt","w");
					fprintf(numfornecedores,"%d",numero_de_fornecedores);
					fclose(numfornecedores);
				}
				
				fscanf(import,"\n%[^\n]s",verifica);
			}while(strcmp(verifica,"<registro>")==0);
		
		}
		else if((strcmp(tabela,"<tabela-Hotel>") ==0)  || (strcmp(tabela,"<tabela-hotel>") ==0)){
	
			char *nome_hotel = malloc(50*sizeof(char));
			char *razaosocial_hotel = malloc(50*sizeof(char));
			char *email_hotel = malloc(50*sizeof(char));
			char *inscricaoestadual_hotel = malloc(20*sizeof(char));
			char *cnpj_hotel = malloc(20*sizeof(char));
			char *rua_hotel = malloc(50*sizeof(char));
			char *numero_hotel = malloc(12*sizeof(char));
			char *bairro_hotel = malloc(50*sizeof(char));
			char *cidade_hotel = malloc(50*sizeof(char));
			char *uf_hotel = malloc(5*sizeof(char));
			char *telefone_hotel = malloc(15*sizeof(char));
			char *nome_responsavel_hotel = malloc(50*sizeof(char));
			char *telefone_responsave_hotel = malloc(15*sizeof(char));
			char *margem_lucro_hotel = malloc(5*sizeof(char));
			
			printf("=====================================================================\n");
			printf("======== Deseja Importar os dados do Hotel? =========================\n");
			printf("======== 1. Sim\n======== 2. Nao\n");
			do{
				repetir=0;
				scanf("%d",&opcao);
				if(opcao <1 || opcao >2){
					repetir=1;
				}
			}while(repetir==1);
			
			fscanf(import,"\n%[^\n]s",registro);
			do{
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",nome_hotel);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",razaosocial_hotel);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",inscricaoestadual_hotel);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",cnpj_hotel);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",rua_hotel);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",numero_hotel);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",bairro_hotel);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n,]s",cidade_hotel);
				fscanf(import,"%c",&lixo);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",uf_hotel);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",telefone_hotel);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",email_hotel);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",nome_responsavel_hotel);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",telefone_responsave_hotel);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n>]s",trash);
				fscanf(import,"%c",&lixo);
				fscanf(import,"\n%[^\n<]s",margem_lucro_hotel);
				fscanf(import,"\n%[^\n]s",trash);
				
				fscanf(import,"\n%[^\n]s",registro);
				
				if(opcao==1){
					printf("%s\n",nome_hotel);
					printf("%s\n",razaosocial_hotel);
					printf("%s\n",email_hotel);
					printf("%s\n",inscricaoestadual_hotel);
					printf("%s\n",cnpj_hotel);
					printf("%s\n",rua_hotel);
					printf("%s\n",numero_hotel);
					printf("%s\n",bairro_hotel);
					printf("%s\n",cidade_hotel);
					printf("%s\n",uf_hotel);
					printf("%s\n",telefone_hotel);
					printf("%s\n",nome_responsavel_hotel);
					printf("%s\n",telefone_responsave_hotel);
					printf("%s\n",margem_lucro_hotel);
					printf("=====================================================================\n");
					
					hotel = fopen("dados\\hotel.txt","r");
					
					fprintf(hotel,"%s\n",nome_hotel);
					fprintf(hotel,"%s\n",razaosocial_hotel);
					fprintf(hotel,"%s\n",inscricaoestadual_hotel);
					fprintf(hotel,"%s\n",cnpj_hotel);
					fprintf(hotel,"%s\n",rua_hotel);
					fprintf(hotel,"%s\n",numero_hotel);
					fprintf(hotel,"%s\n",bairro_hotel);
					fprintf(hotel,"%s\n",cidade_hotel);
					fprintf(hotel,"%s\n",uf_hotel);
					fprintf(hotel,"%s\n",telefone_hotel);
					fprintf(hotel,"%s\n",email_hotel);
					fprintf(hotel,"%s\n",nome_responsavel_hotel);
					fprintf(hotel,"%s\n",telefone_responsave_hotel);
					fprintf(hotel,"%s",margem_lucro_hotel);
					
					fclose(hotel);

				}
				
				fscanf(import,"\n%[^\n]s",verifica);
			}while(strcmp(verifica,"<registro>")==0);
			
		}
		
		fscanf(import,"%c",&lixo);
		fscanf(import,"\n%[^\n]s",tabela);
		if (strcmp(tabela,"</dados>") ==0){
			fim=1;
			
		}
		
	}while(fim==0);
	fflush(stdin); // limpa o buffer do teclado
	//fclose(import);
	
printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
}

int exportardados(){
	
	int op; //Variavel de selecao
	
	int IHospedes = 0; //Variavel que indicara a necessidade ou nao de uma tabela
	
	/*       Verifica a necessidade de Exportacao de dados de hospedes          */
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//Limpa a tela
	printf("=====================================================================\n");
	printf("============ Deseja Exportar Dados dos Hospedes?  ===================\n");
	printf("=====================================================================\n");
	printf("============  1. Sim ================================================\n");
	printf("============  2. Nao ================================================\n");
	printf("============  3. Concluir Exportacao ================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	do{
		scanf("%d",&op);
		if (op!=1 && op!=2 && op!=3){
			printf("Por favor, Digite uma data valida...\n");
		}	
	} while(op!=1 && op!=2 && op!=3);
	
	if (op == 1){
		
		IHospedes = 1;
		
	} else if (op == 2){
		
		IHospedes = 0;
		
	} else if(op == 3){
	
		exit(0); //TEM QUE TIRAR ESSE COMANDO
		
	}
	
	/////////////////////////////////////////////////////////////////////////////////
		
	/*       Verifica a necessidade de Exportacao de dados de acomodacao          */
	int IAcomodacao = 0; //Variavel que indicara a necessidade ou nao de uma tabela
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//Limpa a tela
	printf("=====================================================================\n");
	printf("============ Deseja Exportar Dados das Acomodacoes?  ================\n");
	printf("=====================================================================\n");
	printf("============  1. Sim ================================================\n");
	printf("============  2. Nao ================================================\n");
	printf("============  3. Concluir Exportacao ================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	do{
		scanf("%d",&op);
		if (op!=1 && op!=2 && op!=3){
			printf("Por favor, Digite uma data valida...\n");
		}	
	} while(op!=1 && op!=2 && op!=3);
	
	if (op==1){
		
		IAcomodacao = 1;
		
	} else if (op==2){
		
		IAcomodacao = 0;
		
	} else if(op == 3){
	
		exit(0);
		
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	
	/*  Verifica a necessidade de Exportacao de dados de tipos de acomodacao     */
	int ITAcomodacao = 0; //Variavel que indicara a necessidade ou nao de uma tabela
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//Limpa a tela
	printf("=====================================================================\n");
	printf("========= Deseja Exportar Dados de Tipos de Acomodacoes?  ===========\n");
	printf("=====================================================================\n");
	printf("============  1. Sim ================================================\n");
	printf("============  2. Nao ================================================\n");
	printf("============  3. Concluir Exportacao ================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	do{
		scanf("%d",&op);
		if (op!=1 && op!=2 && op!=3){
			printf("Por favor, Digite uma data valida...\n");
		}	
	} while(op!=1 && op!=2 && op!=3);
	
	if (op==1){
		
		ITAcomodacao = 1;
		
	} else if (op==2){
		
		ITAcomodacao = 0;
		
	} else if(op == 3){
	
		exit(0);
		
	}
	/////////////////////////////////////////////////////////////////////////////////

	/*         Verifica a necessidade de Exportacao de dados de Produtos           */
	int IProdutos = 0; //Variavel que indicara a necessidade ou nao de uma tabela
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//Limpa a tela
	printf("=====================================================================\n");
	printf("============= Deseja Exportar Dados de Produtos?  ===================\n");
	printf("=====================================================================\n");
	printf("============  1. Sim ================================================\n");
	printf("============  2. Nao ================================================\n");
	printf("============  3. Concluir Exportacao ================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	do{
		scanf("%d",&op);
		if (op!=1 && op!=2 && op!=3){
			printf("Por favor, Digite uma data valida...\n");
		}	
	} while(op!=1 && op!=2 && op!=3);
	
	if (op==1){
		
		IProdutos = 1;
		
	} else if (op==2){
		
		IProdutos = 0;
		
	} else if(op == 3){
	
		exit(0);
		
	}
	/////////////////////////////////////////////////////////////////////////////////
		
	/*         Verifica a necessidade de Exportacao de dados de Fornecedores      */
	int IFornecedor = 0; //Variavel que indicara a necessidade ou nao de uma tabela
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//Limpa a tela
	printf("=====================================================================\n");
	printf("============= Deseja Exportar Dados de Fornecedor?  =================\n");
	printf("=====================================================================\n");
	printf("============  1. Sim ================================================\n");
	printf("============  2. Nao ================================================\n");
	printf("============  3. Concluir Exportacao ================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	do{
		scanf("%d",&op);
		if (op!=1 && op!=2 && op!=3){
			printf("Por favor, Digite uma data valida...\n");
		}	
	} while(op!=1 && op!=2 && op!=3);
	
	if (op==1){
		
		IFornecedor = 1;
		
	} else if (op==2){
		
		IFornecedor = 0;
		
	} else if(op == 3){
	
		exit(0);
		
	}
	/////////////////////////////////////////////////////////////////////////////////
	
			
	/*         Verifica a necessidade de Exportacao de dados de Fornecedores      */
	int IHotel = 0; //Variavel que indicara a necessidade ou nao de uma tabela
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//Limpa a tela
	printf("=====================================================================\n");
	printf("============= Deseja Exportar Dados de Hotel?  ======================\n");
	printf("=====================================================================\n");
	printf("============  1. Sim ================================================\n");
	printf("============  2. Nao ================================================\n");
	printf("============  3. Concluir Exportacao ================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	do{
		scanf("%d",&op);
		if (op!=1 && op!=2 && op!=3){
			printf("Por favor, Digite uma data valida...\n");
		}	
	} while(op!=1 && op!=2 && op!=3);
	
	if (op==1){
		
		IHotel = 1;
		
	} else if (op==2){
		
		IHotel = 0;
		
	} else if(op == 3){
	
		exit(0);
		
	}
	/////////////////////////////////////////////////////////////////////////////////
	
	
	
	/*         Verifica quais tabelas deverao ser geradas e gera o arquivo        */
	
	FILE *arq; //Cria o arquivo
	//char xml[5] = ".xml";char dados[24];	strcat (dados,xml); //Junta as duas Strings
	
	arq = fopen("dados.xml","w"); //Abre o arquivo

	if(arq == NULL){
		printf("O arquivo não pode ser aberto\n");
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		exit(0);
	}
	
	fprintf(arq,"<dados>\n"); //Escreve a primeira linha do arquivo xml
		
	if (IHospedes == 1){ //Cria a tabela de hospedes
		
		/* Aloca dinamicamente memoria para os hospedes */
		int i,j;
		FILE *hosp;
		char txt[5] = ".txt";
		char numerodohospede[3];
		char newhospede[23];
		int *codigo_hospede = malloc(numero_de_hospedes * sizeof(int));
		char *nome_hospede[numero_de_hospedes];
		char *email_hospede[numero_de_hospedes];
		char *sexo_hospede[numero_de_hospedes];
		char *estadocivil_hospede[numero_de_hospedes];
		char *rua_hospede[numero_de_hospedes];
		char *numero_hospede[numero_de_hospedes];
		char *bairro_hospede[numero_de_hospedes];
		char *cidade_hospede[numero_de_hospedes];
		char *UF_hospede[numero_de_hospedes];
		char *cpf_hospede[numero_de_hospedes];
		char *telefone_hospede[numero_de_hospedes];
		char *datanascimento_hospede[numero_de_hospedes];
				
		fprintf(arq,"\t<tabela-hospede>\n"); //Inicia a tabela de hospedes
		
		for(i=0; i< numero_de_hospedes; i++){
			
			nome_hospede[i] = malloc(60*sizeof(char));
			email_hospede[i] = malloc(60*sizeof(char));
			sexo_hospede[i] = malloc(15*sizeof(char));
			estadocivil_hospede[i] = malloc(20*sizeof(char));
			rua_hospede[i] = malloc(30*sizeof(char));
			numero_hospede[i] = malloc(10*sizeof(char));
			bairro_hospede[i] = malloc(30*sizeof(char));
			cidade_hospede[i] = malloc(40*sizeof(char));
			UF_hospede[i] = malloc(5*sizeof(char));
			cpf_hospede[i] = malloc(20*sizeof(char));
			telefone_hospede[i] = malloc(20*sizeof(char));
			datanascimento_hospede[i] = malloc(20*sizeof(char));
			
			sprintf(numerodohospede, "%i", i+1);//converte interio em string
			strcpy (newhospede, "dados\\hospede");//define valor a string			
			strcat (newhospede, numerodohospede); // junta duas strings
			strcat (newhospede, txt); // junta duas strings
			
			hosp = fopen(newhospede,"r");
			
			if (hosp != NULL){
				fscanf(hosp,"%i\n",&codigo_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",nome_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",email_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",sexo_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",estadocivil_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",rua_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",numero_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",bairro_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",cidade_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",UF_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",cpf_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",telefone_hospede[i]);
				fscanf(hosp,"\n%[^\n]s",datanascimento_hospede[i]);				
				fclose(hosp);
					
				//Escrevem no Arquivo
				fprintf(arq,"\t\t<registro>\n");
				
				fprintf(arq,"\t\t\t<codigo>%d</codigo>\n",codigo_hospede[i]);
				fprintf(arq,"\t\t\t<nome>%s</nome>\n",nome_hospede[i]);
				fprintf(arq,"\t\t\t<endereco>%s, %s, %s, %s, %s</endereco>\n",rua_hospede[i],numero_hospede[i],bairro_hospede[i],cidade_hospede[i],UF_hospede[i]);
				fprintf(arq,"\t\t\t<CPF>%s</CPF>\n",cpf_hospede[i]);
				fprintf(arq,"\t\t\t<telefone_hospede>%s</telefone_hospede>\n",telefone_hospede[i]);
				fprintf(arq,"\t\t\t<email>%s</email>\n",email_hospede[i]);
				fprintf(arq,"\t\t\t<sexo>%s</sexo>\n",sexo_hospede[i]);
				fprintf(arq,"\t\t\t<estado_civil>%s</estado_civil>\n",estadocivil_hospede[i]);
				fprintf(arq,"\t\t\t<data_nascimento> %s</data_nascimento>\n",datanascimento_hospede[i]);
				
				fprintf(arq,"\t\t</registro>\n");
				}
			}
			fprintf(arq,"\t</tabela-hospede>\n\n"); //Termina a tabela de hospedes
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	if (IAcomodacao == 1){ //Cria a tabela para as acomodacoes caso necessario
			
		int i;
		FILE *acomod; //Cria o arquivo
		char txt[5] = ".txt";
		char numerodaacomodacao[3];
		char acomodacao[23];
		
		int *codigo = malloc(numero_de_acomodacoes * sizeof(int));
		char *descricao[numero_de_acomodacoes];
		char *facilidades[numero_de_acomodacoes];
		int *tipo = malloc(numero_de_acomodacoes * sizeof(int));
		
		fprintf(arq,"\t<tabela-acomodacao>\n"); //Inicia a tabela de Acomodacoes
	
		for(i=0; i<numero_de_acomodacoes; i++){ //Pega os dados de todas as acomodacoes
			descricao[i] = malloc(250 * sizeof(char));
			facilidades[i] = malloc(250 * sizeof(char));
			sprintf(numerodaacomodacao, "%i", i+1);//converte interio em string
			strcpy (acomodacao,"dados\\acomodacao"); //Define valor a string
			strcat (acomodacao, numerodaacomodacao);//Junta a string de caminho com o numero	
			strcat (acomodacao, txt);//junta a string de caminho+numero com o formato .txt
			
			acomod = fopen(acomodacao,"r");	
		
			if(acomod != NULL){
				fscanf(acomod,"%i\n",&codigo[i]);			
				fscanf(acomod,"\n%[^\n]s",descricao[i]);
				fscanf(acomod,"\n%[^\n]s",facilidades[i]);
				fscanf(acomod,"%i\n",&tipo[i]);	
				
				fprintf(arq,"\t\t<registro>\n");
				
				fprintf(arq,"\t\t\t<codigo>%d</codigo>\n",codigo[i]);
				fprintf(arq,"\t\t\t<descricao>%s</descricao>\n",descricao[i]);
				fprintf(arq,"\t\t\t<facilidades>%s</facilidades>\n",facilidades[i]);
				fprintf(arq,"\t\t\t<tipo>%d</tipo>\n",tipo[i]);
				
				fprintf(arq,"\t\t</registro>\n");
				}
			fclose (acomod);							
			}
			fprintf(arq,"\t</tabela-acomodacao>\n\n");//Termina a tabela de Acomodacoes
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	if (ITAcomodacao == 1){//Cria a tabela para os tipos de acomodacoes caso necessario
			char txt[5] = ".txt";
			int i;
			
			FILE *tipoacomod;
			int *codtipoacomod;
			codtipoacomod = malloc(numero_de_tipo_acomodacoes*sizeof(int));			
			float *ValorDiaria;
			ValorDiaria = malloc(numero_de_tipo_acomodacoes*sizeof(float));			
			int *qtdHospedes;
			qtdHospedes = malloc(numero_de_tipo_acomodacoes*sizeof(int));			
			char numtipacomodacao[3];
			char abriracomod[23];			
			char *destipoacomod[numero_de_tipo_acomodacoes];
			
			fprintf(arq,"\t<tabela-TipoAcomodacao>\n"); //Inicia a tabela de tipos de acomodacoes
			
			for(i=0;i<numero_de_tipo_acomodacoes;i++){
				
				destipoacomod[i] = malloc(250*sizeof(char));
				
				sprintf(numtipacomodacao, "%i", i+1);//converte interio em string		
				strcpy (abriracomod, "dados\\tacomodacao"); // Define o valor da string		
				strcat (abriracomod, numtipacomodacao); // junta duas strings
				strcat (abriracomod, txt); // junta duas strings
				
				tipoacomod = fopen(abriracomod,"r");
		
				fflush(stdin); // limpa o buffer do teclado
				fscanf(tipoacomod,"%i\n",&codtipoacomod[i]);
				fscanf(tipoacomod,"\n%[^\n]s",destipoacomod[i]);		
				fflush(stdin); // limpa o buffer do teclado		
				fscanf(tipoacomod,"%f",&ValorDiaria[i]);
				fscanf(tipoacomod,"\n%i",&qtdHospedes[i]);
				
				fclose(tipoacomod);
				
				//Escreve no arquivo
				if(tipoacomod != NULL){
					
					fprintf(arq,"\t\t<registro>\n");
					
					fprintf(arq,"\t\t\t<codigo>%d</codigo>\n",codtipoacomod[i]);
					fprintf(arq,"\t\t\t<descricao>%s</descricao>\n",destipoacomod[i]);
					fprintf(arq,"\t\t\t<valor>%.2f</valor>\n",ValorDiaria[i]);
					fprintf(arq,"\t\t\t<QuantidadeHospedes>%d</QuantidadeHospedes>\n",qtdHospedes[i]);
					
					fprintf(arq,"\t\t</registro>\n");
				}
			}
			fprintf(arq,"\t</tabela-TipoAcomodacao>\n\n");
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	if (IProdutos == 1){//Cria a tabela para os produtos caso necessario
		
		#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
		int i;
		FILE *prod;
		char txt[5] = ".txt";
		char numerodeprodutos[3];
		char openproduto[23];	
		int *codigo_produto = malloc(numero_de_produtos*sizeof(int));
		char *descricao[numero_de_produtos];
		int *estoque = malloc(numero_de_produtos * sizeof(int));
		int *estoque_min = malloc(numero_de_produtos * sizeof(int));
		float *preco_custo = malloc(numero_de_produtos * sizeof(float));
		float *preco_venda = malloc(numero_de_produtos * sizeof(float));

		fprintf(arq,"\t<tabela-Produtos>\n"); //Inicia a tabela de Produtos

		for(i=0;i<numero_de_produtos;i++){
	
			descricao[i] = malloc(250*sizeof(char));
			sprintf(numerodeprodutos, "%i", i+1);//converte interio em string
			strcpy (openproduto, "dados\\produto");//define valor a string			
			strcat (openproduto, numerodeprodutos); // junta duas strings
			strcat (openproduto, txt); // junta duas strings

			prod = fopen(openproduto,"r");
			
			fscanf(prod,"%i\n",&codigo_produto[i]);	
			fscanf(prod,"\n%[^\n]s",descricao[i]);
			fscanf(prod,"%i\n",&estoque[i]);
			fscanf(prod,"%i\n",&estoque_min[i]);
			fscanf(prod,"%f\n",&preco_custo[i]);
			fscanf(prod,"%f\n",&preco_venda[i]);
			
			fclose(prod);
			if(prod != NULL){
					fprintf(arq,"\t\t<registro>\n");
					
					fprintf(arq,"\t\t\t<codigo>%d</codigo>\n",codigo_produto[i]);
					fprintf(arq,"\t\t\t<descricao>%s</descricao>\n",descricao[i]);
					fprintf(arq,"\t\t\t<estoque>%d</estoque>\n",estoque[i]);
					fprintf(arq,"\t\t\t<estoque_min>%d</estoque_min>\n",estoque_min[i]);
					fprintf(arq,"\t\t\t<preco_custo>%f</preco_custo>\n",preco_custo[i]);
					fprintf(arq,"\t\t\t<preco_venda>%f</preco_venda>\n",preco_venda[i]);
					
					fprintf(arq,"\t\t</registro>\n");
			} 
		}
		fprintf(arq,"\t</tabela-Produtos>\n\n"); //Termina a tabela de Produtos
				
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	if(IFornecedor == 1){//Cria a tabela para os fornecedores caso necessario
		
		#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif//limpa a tela
		int i;
		FILE *forn;		
		char txt[5] = ".txt";
		char numerodofornecedor[3];
		char openfornecedor[23];
		int *codigo_fornecedor = malloc(numero_de_fornecedores*sizeof(int));
		char *nome_fornecedor[numero_de_fornecedores];
		char *razaosocial_fornecedor[numero_de_fornecedores];
		char *email_fornecedor[numero_de_fornecedores];
		char *inscricaoestadual_fornecedor[numero_de_fornecedores];
		char *cnpj_fornecedor[numero_de_fornecedores];
		char *rua_fornecedor[numero_de_fornecedores];
		char *num_fornecedor[numero_de_fornecedores];
		char *bairro_fornecedor[numero_de_fornecedores];
		char *cidade_fornecedor[numero_de_fornecedores];
		char *uf_fornecedor[numero_de_fornecedores];
		char *telefone_fornecedor[numero_de_fornecedores];
		
	
		fprintf(arq,"\t<tabela-Fornecedor>\n"); //Inicia a tabela de Fornecedores
		
		for(i=0;i<numero_de_fornecedores;i++){
			
			nome_fornecedor[i] = malloc(40*sizeof(char));
			razaosocial_fornecedor[i] = malloc(250*sizeof(char));
			email_fornecedor[i] = malloc(60*sizeof(char));
			inscricaoestadual_fornecedor[i] = malloc(100*sizeof(char));
			cnpj_fornecedor[i] = malloc(20*sizeof(char));
			rua_fornecedor[i] = malloc(30*sizeof(char));
			num_fornecedor[i] = malloc(10*sizeof(char));
			bairro_fornecedor[i] = malloc(30*sizeof(char));
			cidade_fornecedor[i] = malloc(40*sizeof(char));
			uf_fornecedor[i] = malloc(5*sizeof(char));
			telefone_fornecedor[i] = malloc(20*sizeof(char));			
			
			sprintf(numerodofornecedor, "%i", i+1);//converte interio em string
			strcpy (openfornecedor, "dados\\fornecedor");//define valor a string
			strcat (openfornecedor, numerodofornecedor); // junta duas strings
			strcat (openfornecedor, txt); // junta duas strings
			
			forn = fopen(openfornecedor,"r");
			
			fscanf(forn,"%i\n",&codigo_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",nome_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",razaosocial_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",email_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",inscricaoestadual_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",cnpj_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",rua_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",num_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",bairro_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",cidade_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",uf_fornecedor[i]);
			fscanf(forn,"\n%[^\n]s",telefone_fornecedor[i]);
			
			fclose(forn);
				if(forn != NULL){
					fprintf(arq,"\t\t<registro>\n");
			
					fprintf(arq,"\t\t\t<codigo>%d</codigo>\n",codigo_fornecedor[i]);						
					fprintf(arq,"\t\t\t<nome>%s</nome>\n",nome_fornecedor[i]);				
					fprintf(arq,"\t\t\t<razaosocial>%s</razaosocial>\n",razaosocial_fornecedor[i]);
					fprintf(arq,"\t\t\t<inscricaoestadual>%s</inscricaoestadual>\n",inscricaoestadual_fornecedor[i]);
					fprintf(arq,"\t\t\t<cnpj>%s</cnpj>\n",cnpj_fornecedor[i]);
					fprintf(arq,"\t\t\t<endereco>%s, %s, %s, %s, %s</endereco>\n",rua_fornecedor[i],num_fornecedor[i],bairro_fornecedor[i],cidade_fornecedor[i],uf_fornecedor[i]);
					fprintf(arq,"\t\t\t<telefone>%s</telefone>\n",telefone_fornecedor[i]);
					fprintf(arq,"\t\t\t<email>%s</email>\n",email_fornecedor[i]);
					fprintf(arq,"\t\t</registro>\n");
				}
		}
	
		fprintf(arq,"\t</tabela-Fornecedor>\n\n"); //Termina a tabela de Fornecedores
		
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	if(IHotel == 1){//Cria a tabela para o hotel caso necessario
		
		int i;
		FILE *hotel;
		
		fprintf(arq,"\t<tabela-Hotel>\n"); //Inicia a tabela do hotel
		
		fprintf(arq,"\t\t<registro>\n");
						
		fprintf(arq,"\t\t\t<nome>%s</nome>\n",nomefantasia);				
		fprintf(arq,"\t\t\t<razaosocial>%s</razaosocial>\n",razaosocial);
		fprintf(arq,"\t\t\t<inscricaoestadual>%s</inscricaoestadual>\n",inscricaoestadual);
		fprintf(arq,"\t\t\t<cnpj>%s</cnpj>\n",cnpj);
		fprintf(arq,"\t\t\t<endereco>%s, %s, %s, %s, %s</endereco>\n",rua,numero,bairro,cidade,UF);
		fprintf(arq,"\t\t\t<telefone>%s</telefone>\n",telefone);
		fprintf(arq,"\t\t\t<email>%s</email>\n",email);
		fprintf(arq,"\t\t\t<nomeresponsavel>%s</nomeresponsavel>\n",nomedoresponsavel);
		fprintf(arq,"\t\t\t<telefonedoresponsavel>%s</telefonedoresponsavel>\n",telefonedoresponsavel);
		fprintf(arq,"\t\t\t<margemdelucro>%d</margemdelucro>\n",margemlucro);
		fprintf(arq,"\t\t</registro>\n");
		
		fprintf(arq,"\t</tabela-Hotel>\n\n"); //Termina a tabela de Fornecedores
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

		fprintf(arq,"</dados>\n"); //Termina o arquivo xml
		printf("Prescione Enter para Continuar!\n");
		getchar();
		getchar();
		fclose(arq);
}	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

int modulodados(){
	
	int categoriadesejada;
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=================== Importar / Exportar Dados =======================\n");
	printf("=====================================================================\n");
	printf("===== 1. Importar ===================================================\n");
	printf("===== 2. Exportar ===================================================\n");
	printf("===== 3. Voltar =====================================================\n");
	printf("===== 0. Sair do Sistema ============================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	
	do{	
			scanf("%d", &categoriadesejada);
		if(categoriadesejada <0 || categoriadesejada >3){
			printf("Digite uma opcao valida...\n");
		}
	}while (categoriadesejada <0 || categoriadesejada >3);
	
	switch (categoriadesejada){
		case 1:
			importardados();
		break;
		case 2:
			exportardados();
		break;
		case 3:
			main();
		break;
		case 0:
			exit(0);
		break;
		default:
			modulodados();
	}
	modulodados();
}

////////////////////////
//modulo 0 /////////////
////////////////////////

int main(){
	
	int i;
	
	FILE *hotel;
	hotel = fopen("dados\\hotel.txt","r");
	
	fscanf(hotel,"\n%[^\n]s",nomefantasia);
	fscanf(hotel,"\n%[^\n]s",razaosocial);
	fscanf(hotel,"\n%[^\n]s",inscricaoestadual);
	fscanf(hotel,"\n%[^\n]s",cnpj);
	fscanf(hotel,"\n%[^\n]s",rua);
	fscanf(hotel,"\n%[^\n]s",numero);
	fscanf(hotel,"\n%[^\n]s",bairro);
	fscanf(hotel,"\n%[^\n]s",cidade);
	fscanf(hotel,"\n%[^\n]s",UF);
	fscanf(hotel,"\n%[^\n]s",telefone);
	fscanf(hotel,"\n%[^\n]s",email);
	fscanf(hotel,"\n%[^\n]s",nomedoresponsavel);
	fscanf(hotel,"\n%[^\n]s",telefonedoresponsavel);
	fscanf(hotel,"%d",&margemlucro);
	
	fclose(hotel);
	
	FILE *numhospedes;
	numhospedes = fopen("dados\\Nhospedes.txt","r");
	fscanf(numhospedes,"%i",&numero_de_hospedes);
	fclose(numhospedes);
	
	FILE *num_acomodacoes;
	num_acomodacoes = fopen("dados\\Nacomodacoes.txt","r");
	fscanf(num_acomodacoes,"%i",&numero_de_acomodacoes);
	fclose(num_acomodacoes);
	
	FILE *num_cat_acomodacoes;
	num_cat_acomodacoes = fopen("dados\\Ntipoacomodacoes.txt","r");
	fscanf(num_cat_acomodacoes,"%i",&numero_de_tipo_acomodacoes);
	fclose(num_cat_acomodacoes);
	
	FILE *numprodutos;
	numprodutos = fopen("dados\\Nprodutos.txt","r");
	fscanf(numprodutos,"%i",&numero_de_produtos);
	fclose(numprodutos);
	
	FILE *numfornecedores;
	numfornecedores = fopen("dados\\Nfornecedores.txt","r");
	fscanf(numfornecedores,"%i",&numero_de_fornecedores);
	fclose(numfornecedores);
	
	FILE *numreservas;
	numreservas = fopen("dados\\Nreservas.txt","r");
	fscanf(numreservas,"%i",&numero_reservas);
	fclose(numreservas);
	
	FILE *caixa_Hotel;
	caixa_Hotel = fopen("dados\\caixa.txt","r");
	fscanf(caixa_Hotel,"%f",&caixa);
	fclose(caixa_Hotel);
	
	FILE *compras;
	compras = fopen("dados\\Ncompras.txt","r");
	fscanf(compras,"%i",&historico_de_compras);
	fclose(compras);
	
	FILE *operadores;
	operadores = fopen("dados\\Noperadores.txt","r");
	fscanf(operadores,"%i",&num_operadores);
	fclose(operadores);
	
	
	//IMPORTANTE
	data_sistema();
	checagem_reservas();
	verificar_contas_cartao();
	verificar_contas_pagar();
	
	if(jafez==0){
		login();
		jafez=1;
	}
	
	int modulodesejado;
	#ifdef WIN32
				system("CLS");
			#else
				system("clear");
			#endif //limpa a tela
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	printf("============================= Bem Vindo =============================\n");
	printf("==================== Qual Modulo Deseja Acessar? ====================\n");
	printf("===== 1. Cadastro e Gestao De Dados =================================\n");
	printf("===== 2. Reservas ===================================================\n");
	printf("===== 3. Transacoes =================================================\n");
	printf("===== 4. Feedback ===================================================\n");
	printf("===== 5. Importacao/Exportacao de Dados =============================\n");
	printf("===== 0. Sair do Sistema ============================================\n");
	printf("=====================================================================\n");
	printf("=====================================================================\n");
	scanf("%d",&modulodesejado);
	
	switch (modulodesejado){
		case 1:
			modulodecadastrosegestaodedados();
		break;
		case 2:
			modulodereservas();
		break;
		case 3:
			modulo_transacoes();
		break;
		case 4:
			modulofeedback();
		break;
		case 5:
			if((nivel_permissao ==3) || (nivel_permissao ==4)){
				printf("Nivel de Permissao Insuficiente\n");
				printf("Prescione Enter para Continuar!\n");
				getchar();
				getchar();
				main();
			}else{
				modulodados();
			}
		break;
		case 0:
			exit(0);
		break;
		default:
			main();
	}
	main();
}
