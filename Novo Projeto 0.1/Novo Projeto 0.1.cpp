// Novo Projeto 0.1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>
// file opening modes
#define FILEMODE_r "r"
#define FILEMODE_w "w"
#define FILEMODE_a "a"
#define FILEMODE_rU "r+"
#define FILEMODE_wU "w+"
#define FILEMODE_aU "a+"
#define FILEMODE_rb "rb"
#define FILEMODE_wb "wb"
#define FILEMODE_ab "ab"
#define FILEMODE_rUb "r+b"
#define FILEMODE_wUb "w+b"
#define FILEMODE_aUb "a+b"


//------>>> Estruturas Utilizadas neste Trabalho!

//Estrutura para o número de cada valor de moedas.
typedef struct MoedasDisponiveis {

	int moedas0_05;
	int moedas0_10;
	int moedas0_20;
	int moedas0_50;
	int moedas1_00;
	int moedas2_00;
}MOEDASDISPONIVEIS;

//As seguintes duas estruturas foram utilizadas na estrutura InformaçõesdeProdutos
typedef struct { int ano, mes, dia; }DATA;
typedef struct { int horas, minutos; }HORAS;

//Estrutura que contem as informacoes de cada produto.
//=s nomes das variaveis correspondem às informacoes referentes ao mesmo produto.
typedef struct InformacoesdeProdutos {
	int Disponibilidade;
	char codigo[3];
	char nome[30];
	float preco;
	int quantidadedisponivel;
	int nVendas;
	DATA dataReposicao;
	HORAS horaReposicao;
}INFORMACOESDEPRODUTOS;

//Estrutura geral da Maquina que contem a estrutura do numero de moedas e a estrutura das Informações de Produtos
typedef struct Maquina {
	INFORMACOESDEPRODUTOS TotaldeProdutos[5][3];
	MOEDASDISPONIVEIS TotaldeMoedas;
}MAQUINA;

//------>>> Funções utilizadas neste programa

//Função que repõem as moedas
MOEDASDISPONIVEIS reporMoedas(MOEDASDISPONIVEIS x)
{
	x.moedas0_05 = 35;
	x.moedas0_10 = 30;
	x.moedas0_20 = 30;
	x.moedas0_50 = 25;
	x.moedas1_00 = 15;
	x.moedas2_00 = 10;

	return x;
}

// Função Inicial.
void Bemvindo()
{

	printf("\t\t\tBem vindo a maquina de vendas do IPV!!!\n\n");
	printf("\t\t\tEsta maquina e patrocinada pela ESTGV-IPV!!\n\n\n");
	printf("\t\t\t(Pressione 'ENTER' para continuar)");
	
}

void GravarReposicaoFich(MAQUINA* MaquinaReal, float lucro, DATA DataMomento, HORAS HoraMomento)
{
	


	FILE* fic;
	fic = fopen("Vendas.dat", "ab");
	if (fic == NULL)
		printf("Erro ao criar o ficheiro 'Vendas.dat'!!!");
	else
	{
		fprintf(fic, "\n-------------------------------------------------------------------");
		fprintf(fic, "\n|| %d/%d/%d  ", DataMomento.dia, DataMomento.mes, DataMomento.ano);
		fprintf(fic, "|| %dh%dmin ||\n\n", HoraMomento.horas, HoraMomento.minutos);
		fprintf(fic, "\t\t\tReposição efetuada!Todas as Moedas e Produtos Repostos!\n");
		fprintf(fic, "LucroDiário: %.2f\n", lucro);
		fprintf(fic, "\t\tInformações de Produtos:\n");
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 3; j++)
			{
				fprintf(fic, "<><><><>\n");
				fprintf(fic, "Nome:%s\nUnidades em stock: %d\nTotaldeVendas:%d\n", MaquinaReal->TotaldeProdutos[i][j].nome,
					MaquinaReal->TotaldeProdutos[i][j].quantidadedisponivel, MaquinaReal->TotaldeProdutos[i][j].nVendas);
			}
		}
		fprintf(fic, "<><><><>");
		fprintf(fic, "\n-------------------------------------------------------------------");
		fprintf(fic, "\n\n");
		fclose(fic);
	}
}

//Função responsável por repor as quantidades dos produtos todas a 10 unidades de cada produto
//Tb guarda a hora a que os produtos foram repostos!
void FuncaoRepor(MAQUINA* MaquinaReal)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	DATA DataMomento;
	HORAS HoraMomento;
	DataMomento.dia = tm.tm_mday;
	DataMomento.mes = tm.tm_mon + 1;
	DataMomento.ano = tm.tm_year + 1900;

	HoraMomento.horas = tm.tm_hour;
	HoraMomento.minutos = tm.tm_min;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++) {
			if (MaquinaReal->TotaldeProdutos[i][j].Disponibilidade == 1)
			{
				MaquinaReal->TotaldeProdutos[i][j].quantidadedisponivel = 10;
				MaquinaReal->TotaldeProdutos[i][j].dataReposicao = DataMomento;
				MaquinaReal->TotaldeProdutos[i][j].horaReposicao = HoraMomento;
			}
		}
	}
	float a = MaquinaReal->TotaldeMoedas.moedas2_00;
	float b = MaquinaReal->TotaldeMoedas.moedas1_00;
	float c = MaquinaReal->TotaldeMoedas.moedas0_50;
	float d = MaquinaReal->TotaldeMoedas.moedas0_20;
	float e = MaquinaReal->TotaldeMoedas.moedas0_10;
	float f = MaquinaReal->TotaldeMoedas.moedas0_05;

	float lucro = (a - 5) * 2 + (b - 10) + (c - 20) * 0.5 + (d - 30) * 0.2 + (e - 30) * 0.1 + (f - 30) * 0.05;
	MaquinaReal->TotaldeMoedas.moedas2_00 = 5;
	MaquinaReal->TotaldeMoedas.moedas1_00 = 10;
	MaquinaReal->TotaldeMoedas.moedas0_50 = 20;
	MaquinaReal->TotaldeMoedas.moedas0_20 = 30;
	MaquinaReal->TotaldeMoedas.moedas0_10 = 30;
	MaquinaReal->TotaldeMoedas.moedas0_05 = 30;

	GravarReposicaoFich(MaquinaReal, lucro, DataMomento, HoraMomento);//vai gravar em no ficheiro Vendas.dat a informação da Reposição

	printf("\n\n\t\t\t\tProdutos e Moedas Repostos com sucesso!");
	printf("\n\nO seu Lucro foi de:%.2f $!", lucro);
	getchar();
}

//Função que mostra os produtos dispoíveis para venda!
void FuncaoVitrine(MAQUINA* MaquinaReal)
{

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	DATA DataMomento;
	HORAS HoraMomento;
	DataMomento.dia = tm.tm_mday;
	DataMomento.mes = tm.tm_mon + 1;
	DataMomento.ano = tm.tm_year + 1900;

	HoraMomento.horas = tm.tm_hour;
	HoraMomento.minutos = tm.tm_min;
	printf("\n|| %d/%d/%d  ", DataMomento.dia, DataMomento.mes, DataMomento.ano);
	printf("|| %dh%dmin ||\n\n", HoraMomento.horas, HoraMomento.minutos);


	for (int i = 0; i < 5; i++)
	{
		printf("|| ");
		for (int j = 0; j < 3; j++) {
			if (MaquinaReal->TotaldeProdutos[i][j].Disponibilidade == 1)
			{
				printf("%s, ", MaquinaReal->TotaldeProdutos[i][j].codigo);
				printf("%s\t", MaquinaReal->TotaldeProdutos[i][j].nome);
			}
			else
				printf("Sem stock\t");
		}
		printf(" ||");
		printf("\n\n");
	}
	if (HoraMomento.horas == 9 && HoraMomento.minutos == 0)	//Parte da Função responsável para repor todos os produtos e moedas as nove da manhã de cada dia!
		FuncaoRepor(MaquinaReal);

}
//Função que verifica se existe um número defeciário de moedas
void VerificarMoedas(MAQUINA* MaquinaReal)
{
	if (MaquinaReal->TotaldeMoedas.moedas2_00 == 0 || MaquinaReal->TotaldeMoedas.moedas1_00 == 0 || MaquinaReal->TotaldeMoedas.moedas0_50 == 0
		|| MaquinaReal->TotaldeMoedas.moedas0_20 == 0 || MaquinaReal->TotaldeMoedas.moedas0_10 == 0 || MaquinaReal->TotaldeMoedas.moedas0_05 == 0)
		printf("\nTroco pode estar indisponível, porfavor introduza o valor certo!\n");
}



void VerificarProdsNotification(MAQUINA* MaquinaReal)
{
	int x = 0;
	FILE* fic;
	fic = fopen("Vendas.dat", "ab");
	if (fic == NULL)
		printf("Erro ao criar o ficheiro 'Vendas.dat'!!!");
	else
	{
		fprintf(fic, "Estado dos Produtos:\n\n");
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (MaquinaReal->TotaldeProdutos[i][j].quantidadedisponivel <= 3)
				{
					fprintf(fic, "AVISO!!! Produto:%s encontra-se com sotck reduzido(stock=%d) - Necessita Reposição\n",
						MaquinaReal->TotaldeProdutos[i][j].nome, MaquinaReal->TotaldeProdutos[i][j].quantidadedisponivel);
					x++;
				}
			}
		}



		if (x == 0)
			fprintf(fic, "Nenhum produto em falta de Stock!\n");
		int y = 0;
		if (MaquinaReal->TotaldeMoedas.moedas2_00 <= 3){
			fprintf(fic, "AVISO!!! Moedas de 2$ encontra-se com Stock reduzido(stock=%d) - Necessita Reposição\n", MaquinaReal->TotaldeMoedas.moedas2_00); y++;
		}
		if (MaquinaReal->TotaldeMoedas.moedas1_00 <= 3){
			fprintf(fic, "AVISO!!! Moedas de 1$ encontra-se com Stock reduzido(stock=%d) - Necessita Reposição\n", MaquinaReal->TotaldeMoedas.moedas1_00); y++;
		}
		if (MaquinaReal->TotaldeMoedas.moedas0_50 <= 3){
			fprintf(fic, "AVISO!!! Moedas de 0.5$ encontra-se com Stock reduzido(stock=%d) - Necessita Reposição\n", MaquinaReal->TotaldeMoedas.moedas0_50); y++;
		}
	if (MaquinaReal->TotaldeMoedas.moedas0_20 <= 3){
		fprintf(fic, "AVISO!!! Moedas de 0.2$ encontra-se com Stock reduzido(stock=%d) - Necessita Reposição\n", MaquinaReal->TotaldeMoedas.moedas0_20); y++;
		}
		if (MaquinaReal->TotaldeMoedas.moedas0_10 <= 3){
			fprintf(fic, "AVISO!!! Moedas de 0.1$ encontra-se com Stock reduzido(stock=%d) - Necessita Reposição\n", MaquinaReal->TotaldeMoedas.moedas0_10); y++;
		}
		if (MaquinaReal->TotaldeMoedas.moedas0_05 <= 3){
			fprintf(fic, "AVISO!!! Moedas de 0.05$ encontra-se com Stock reduzido(stock=%d) - Necessita Reposição\n", MaquinaReal->TotaldeMoedas.moedas0_05); y++;
		}
		if (y == 0)
			fprintf(fic, "Nenhuma Moeda em falta de Stock!\n");


		fprintf(fic, "-------------------------------------------------------------------");
		fclose(fic);
	}
}

//Função responsável por devolver o troco ao utilizador em moedas de 2€,1€,0.50€,0.20€,0.10€ e 0.05€
void FuncaoTroco(MAQUINA *MaquinaReal, float troco)
{
	if (troco == 0)
		printf("\n\nO seu troco e de 0.00 Euros, Obrigado pela sua compra.");
	else
		printf("\n\nO seu troco e de %.2f Euros\n\n\n", troco);

	while (troco - 2 >= 0 && MaquinaReal->TotaldeMoedas.moedas2_00 > 0) {
		printf("Devolve moeda de 2Euros\n");
		troco = troco - 2.00;
		MaquinaReal->TotaldeMoedas.moedas2_00--;
	}
	while (troco - 1 >= 0 && MaquinaReal->TotaldeMoedas.moedas1_00 > 0) {
		printf("Devolve moeda de 1Euro\n");
		troco = troco - 1.00;
		MaquinaReal->TotaldeMoedas.moedas1_00--;	
	}
	while (troco - 0.5 >= 0 && MaquinaReal->TotaldeMoedas.moedas0_50 > 0) {
		printf("Devolve moeda de 50 centimos.\n");
		troco -= 0.5;
		MaquinaReal->TotaldeMoedas.moedas0_50--;	
	}
	while (troco - 0.2 >= 0 && MaquinaReal->TotaldeMoedas.moedas0_20 > 0) {
		printf("Devolve moeda de 20 centimos\n");
		troco = troco - 0.2;
		MaquinaReal->TotaldeMoedas.moedas0_20--;	
	}
	while (troco - 0.1 >= 0 && MaquinaReal->TotaldeMoedas.moedas0_10 > 0) {
		printf("Devolve moeda de 10 centimos\n");
		troco = troco - 0.1;
		MaquinaReal->TotaldeMoedas.moedas0_10--;
	}
	while ((troco-(0.05)) >= (-0.01) && MaquinaReal->TotaldeMoedas.moedas0_05 > 0) {
		printf("Devolve moeda de 5 centimos\n");
		troco = troco - 0.05;
		MaquinaReal->TotaldeMoedas.moedas0_05--;
	}
	
	if (troco <= -0.01)
		printf("\nImpossivel devolver a totalidade do troco, porfavor entre em contacto com o fornecedor!");
	return;
}

//Função responsável por efetuar o pagamento de um produto.
void funcaoPagar(INFORMACOESDEPRODUTOS* cProduto, MAQUINA* MaquinaReal)
{
	int moeda;
	float valorInserido = 0, preco,devolver;
	int a=0, b=0, c=0, d=0, e=0, f=0;//a,b,c,d,e,f são variaveis temporarias usadas no caso de ser necessário devolver dinheiro inserido!
	
	preco = cProduto->preco;
	printf("\n\n");
	printf("Produto escolhido");
	printf("\n\nNome: %s", cProduto->nome);
	printf("\n\nQuantidade: %d", cProduto->quantidadedisponivel);
	printf("\nPreco: %.2f $", preco);

	printf("\n\n Na maquinda de Vendas do IPV aceitamos Moedas de:");
	printf("\n ('1') 2 Euros, ('2') 1 Euro, ('3') 50 centimos, ('4') 20 centimos, ('5') 10 centimos e de ('6') 5 centimos - ('0') para cancelar compra!");
	printf("\n (A moeda deve ser inserida pelo respetivo codigo - Exemplo: Escreva '1' para inserir uma moeda de 2 euros!\n");
	do {
		scanf("%d", &moeda);
		switch (moeda)
		{
		case 1:
			valorInserido += 2.00;
			printf("Moeda de 2 Euros inserida, valor total inserido: %.2f\n", valorInserido);
			MaquinaReal->TotaldeMoedas.moedas2_00++;
			a++;
			break;
		case 2:
			valorInserido += 1;
			printf("Moeda de 1 Euro Inserida, valor total inserido: %.2f\n", valorInserido);
			MaquinaReal->TotaldeMoedas.moedas1_00++;
			b++;
			break;
		case 3:
			valorInserido += 0.5;
			printf("Moeda de 50 centimos inserida, valor total inserido: %.2f\n", valorInserido);
			MaquinaReal->TotaldeMoedas.moedas0_50++;
			c++;
			break;
		case 4:
			valorInserido += 0.20;
			printf("Moeda de 2o centimos inserida, valor total inserido: %.2f\n", valorInserido);
			MaquinaReal->TotaldeMoedas.moedas0_20++;
			d++;
			break;
		case 5:
			valorInserido += 0.10;
			printf("Moeda de 10 centimos inserida, valor total inserido: %.2f\n", valorInserido);
			MaquinaReal->TotaldeMoedas.moedas0_10++;
			e++;
			break;
		case 6:
			valorInserido += 0.05;
			printf("Moeda de 5 centimos inserida, valor total inserido: %.2f\n", valorInserido);
			MaquinaReal->TotaldeMoedas.moedas0_05++;
			f++;
			break;
		case 0:
			devolver= (a) * 2 + (b) + (c) * 0.5 + (d) * 0.2 + (e) * 0.1 + (f) * 0.05;
			printf("Maquina devolve %.2f$", devolver);
			MaquinaReal->TotaldeMoedas.moedas2_00 -= a;
			MaquinaReal->TotaldeMoedas.moedas1_00 -= b;
			MaquinaReal->TotaldeMoedas.moedas0_50 -= c;
			MaquinaReal->TotaldeMoedas.moedas0_20 -= d;
			MaquinaReal->TotaldeMoedas.moedas0_10 -= e;
			MaquinaReal->TotaldeMoedas.moedas0_05 -= f;
			return;
		default:
			break;
		}
	} while (valorInserido < cProduto->preco);


	float troco = valorInserido - preco;
	if (troco > 0){
		FuncaoTroco(MaquinaReal, troco);
		return;
	}
	else{
		printf("Obrigado pela sua compra!");
		return;
	}

}

//função responsável por efetuar o pagamento de um produto


void WriteVendasFich(INFORMACOESDEPRODUTOS* cProduto)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	DATA DataMomento;
	HORAS HoraMomento;
	DataMomento.dia = tm.tm_mday;
	DataMomento.mes = tm.tm_mon + 1;
	DataMomento.ano = tm.tm_year + 1900;

	HoraMomento.horas = tm.tm_hour;
	HoraMomento.minutos = tm.tm_min;


	FILE* fic;
	fic = fopen("Vendas.dat", "ab");
	if(fic==NULL)
		printf("Erro ao criar o ficheiro 'Vendas.dat'!!!");
	else
	{
		fprintf(fic, "\n-------------------------------------------------------------------");
		fprintf(fic,"\n|| %d/%d/%d  ", DataMomento.dia, DataMomento.mes, DataMomento.ano);
		fprintf(fic,"|| %dh%dmin ||\n\n", HoraMomento.horas, HoraMomento.minutos);
		fprintf(fic, "Nova compra:\n");
		fprintf(fic, "Codigo:%s\n", cProduto->codigo);
		fprintf(fic, "Nome:%s\n", cProduto->nome);
		fprintf(fic, "Lucro:%.2f\n", cProduto->preco);
		fprintf(fic, "Nº Total de Vendas: %d", cProduto->nVendas);
		fprintf(fic, "\n\n");
		fclose(fic);
	}
}

//As próximas 4 funções sao responsáveis por escrever ou ler nos ficheiros que guardam as informações de Produtos e Moedas, arrayProds.dat e structMoney.dat respetivamente.
void WriteProdFich(MAQUINA* MaquinaReal)
{
	FILE* fic;
	fic = fopen("Produtos.dat", "wb");
	if (fic == NULL)
		printf("Erro ao criar o ficheiro 'Produtos.dat'!!!");
	else
	{
		fwrite(MaquinaReal->TotaldeProdutos, sizeof(INFORMACOESDEPRODUTOS), 15, fic);
		fclose(fic);
	}

}

void LeProdFich(MAQUINA* MaquinaReal)
{
	FILE* fic;
	fic = fopen("Produtos.dat", "rb");
	if (fic == NULL)
		printf("Erro ao ler o ficheiro 'Produtos.dat'!!!");
	else
	{
		fread(MaquinaReal->TotaldeProdutos, sizeof(INFORMACOESDEPRODUTOS), 15, fic);
		fclose(fic);
	}
}

void WriteMoedasFich(MAQUINA* MaquinaReal)
{
	FILE* fic;
	fic = fopen("Moedas.dat", "wb");
	if (fic == NULL)
	printf("Falha ao escrever no ficheiro 'Moedas.dat'!!!");
	else
	{
	fprintf(fic, "%d %d %d %d %d %d", MaquinaReal->TotaldeMoedas.moedas2_00, MaquinaReal->TotaldeMoedas.moedas1_00, MaquinaReal->TotaldeMoedas.moedas0_50, MaquinaReal->TotaldeMoedas.moedas0_20, MaquinaReal->TotaldeMoedas.moedas0_10, MaquinaReal->TotaldeMoedas.moedas0_05);
	fclose(fic);
	}
}

void LeMoedasFich(MAQUINA* MaquinaReal)
{
	FILE* fic;
	fic = fopen("Moedas.dat", "r");
	if (fic == NULL)
		printf("Falha ao ler o ficheiro 'Moedas.dat'!!!");
	else
	{
		fscanf(fic,"%d%d%d%d%d%d", &MaquinaReal->TotaldeMoedas.moedas2_00, &MaquinaReal->TotaldeMoedas.moedas1_00, &MaquinaReal->TotaldeMoedas.moedas0_50, &MaquinaReal->TotaldeMoedas.moedas0_20, &MaquinaReal->TotaldeMoedas.moedas0_10, &MaquinaReal->TotaldeMoedas.moedas0_05);
		fclose(fic);
	}
}

//Ao sair o programa guarda os dados em ficheiro!
void FuncaoSair(MAQUINA* MaquinaReal) {

	WriteProdFich(MaquinaReal);
	WriteMoedasFich(MaquinaReal);
	
	printf("\n\n\t\t\t\tObrigado por Utilizar Maquina IPV!");
	printf("\n\n\t(Este programa foi escrito por David Sousa: 18748, Joao Fragao: 18747, Ricardo Amaral: 18746, Carlos Machado: 18723) (Grupo 7)\n\n");

}

void funcaoCompra(MAQUINA* MaquinaReal)
{
	system("cls");
	FuncaoVitrine(MaquinaReal);
	VerificarMoedas(MaquinaReal);

	printf("\n\nPorfavor insira o codigo do produto que deseja comprar!: ");
	char Codigo[3];
	gets_s(Codigo);
	int x = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			INFORMACOESDEPRODUTOS* cProduto = &(MaquinaReal->TotaldeProdutos[i][j]);

			if (cProduto->Disponibilidade)
			{
				if (strcmp(cProduto->codigo, Codigo) == 0)
				{
					if (cProduto->quantidadedisponivel > 0)
					{
						funcaoPagar(cProduto, MaquinaReal);
						cProduto->quantidadedisponivel--;
						cProduto->nVendas++;
						x = 1;
						WriteVendasFich(cProduto);
						VerificarProdsNotification(MaquinaReal);
						printf("\n\t\t\t(Pressione 'ENTER' para continuar)");
						getchar();
						getchar();
						return;


					}
					else {
						printf("SEM STOCK!");
						printf("\n\t\t\t(Pressione 'ENTER' para continuar)");
						getchar();
						return;
					}
				}
			}
		}
	}

}

void FuncaoAlterarPreco(MAQUINA* MaquinaReal)
{
	system("cls");
	FuncaoVitrine(MaquinaReal);
	printf("\n\nPorfavor inisira o codigo do produto cujo qual deseja alterar o preco: ");
	char codigo[3];
	gets_s(codigo);
	float temp;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			INFORMACOESDEPRODUTOS* cProduto = &(MaquinaReal->TotaldeProdutos[i][j]);

			if (cProduto->Disponibilidade)
			{
				if (strcmp(cProduto->codigo, codigo) == 0)
				{
					
					printf("Nome: %s\n", cProduto->nome);
					printf("Preco atual: %.2f$\n", cProduto->preco);
					printf("\nQual o novo Preco pretendido?\n");
					do{
					scanf("%f", &temp);
					if (temp <= 0)
						printf("Porfavor introduza um valor positivo!\n");
					} while (temp <= 0);
					cProduto->preco = temp;
					printf("Preco alterado para %.2f$ !\n", cProduto->preco);
					printf("\n\t\t\t(Pressione 'ENTER' para continuar)");
					getchar();
					getchar();
					return;
					
					
				}
			}
		}
	}

}

void FuncaoAlterarProduto(MAQUINA* MaquinaReal)
{
	system("cls");
	FuncaoVitrine(MaquinaReal);
	printf("\n\nPorfavor inisira o codigo do produto que deseja substituir: ");
	char codigo[3];
	gets_s(codigo);
	float temp1;
	int temp2;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			INFORMACOESDEPRODUTOS* cProduto = &(MaquinaReal->TotaldeProdutos[i][j]);

			if (cProduto->Disponibilidade)
			{
				if (strcmp(cProduto->codigo, codigo) == 0)
				{
					printf("\nQual o Nome do Novo Produto que deseja vender? ");
					char nNome[30];
					gets_s(cProduto->nome);
					//cProduto->nome[30] = nNome[30];
					printf("\nQual o novo Preco pretendido?\n");
					do {
						scanf("%f", &temp1);
						if (temp1 <= 0)
							printf("Porfavor introduza um valor positivo!\n");
					} while (temp1 <= 0);
					cProduto->preco = temp1;
					printf("Quantas Unidades deseja inserir?(Introduza um numero entre 1 e 10): ");
					do {
						scanf("%d", &temp2);
						if (temp2 < 1 || temp2>10)
							printf("Porfavor Introduza um número válido!\n");
					} while (temp2 < 1 || temp2>10);

					printf("\nProduto Alterado com sucesso!\n");
					
					printf("\n\t\t\t(Pressione 'ENTER' para continuar)");
					getchar();
					getchar();
					return;


				}
			}
		}
	}
	
}

void FuncaoMaisComprado(MAQUINA* MaquinaReal) {
	system("cls");
	FuncaoVitrine(MaquinaReal);
	int maiscomp = 0;
	char codigo[3], nome[30];
	for (int i = 0; i < 5; i++) {
		
		for (int j = 0; j < 3; j++) {
			
			INFORMACOESDEPRODUTOS* cProduto = &(MaquinaReal->TotaldeProdutos[i][j]);
			
			if (cProduto->nVendas > maiscomp) {
				
				maiscomp = cProduto->nVendas;
				strcpy(codigo, cProduto->codigo);
				strcpy(nome, cProduto->nome);


			}
		}
	}

	printf("\n Produto mais comprado: %s - %s", codigo, nome);
	printf("\n Numero de vendas: %d", maiscomp);
	printf("\n\t\t\t(Pressione 'ENTER' para continuar)");
	getchar();
	return;


}

void FuncaoMenu(MAQUINA* MaquinaReal) {
	getchar();
	int x = 0;
	int op;
	do {
		system("cls");
		FuncaoVitrine(MaquinaReal);
		printf("\n\n\nPorfavor escolha a operacao que deseja efetuar:\n");
		printf("'1'->Comprar um Produto; '2'->Repor produtos e moedas; '3' Alterar preco de um Produto; '4' Alterar Produto; '5' Verificar produto mais comprado; 0' Sair.\n");
		scanf("%d", &op);
		switch (op) {
		case 1: 
			getchar();
			funcaoCompra(MaquinaReal);
			
			break;
		case 2:
			getchar();
			FuncaoRepor(MaquinaReal);
			break;
		case 3:
			getchar();
			FuncaoAlterarPreco(MaquinaReal);
			break;
		case 4:
			getchar();
			FuncaoAlterarProduto(MaquinaReal);
			break;
		case 5:
			getchar();
			FuncaoMaisComprado(MaquinaReal);
			break;
		case 0:
			getchar();
			FuncaoSair(MaquinaReal);
			x = 1;
			break;
		default:
			getchar();
			break;
		}

	} while (x == 0);


}
MAQUINA* MaquinaReal = (MAQUINA*)malloc(sizeof(MAQUINA));
int main()
{
	Bemvindo();



	LeProdFich(MaquinaReal);
	LeMoedasFich(MaquinaReal);
	FuncaoMenu(MaquinaReal);
	

	return 0;
}
