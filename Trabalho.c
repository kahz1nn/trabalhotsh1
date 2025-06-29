//Trabalho ALG - v4.c
/*******************************************************************************
                            Trabalho de Algoritmos 1

Turma: EC41A - C11
Grupo: 5
Alunos: Alan Davi Souza de Andrade - Julia Romano Gomes - Kaio Gabriel Rampazo
*******************************************************************************/

// Bibliotecas externas
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Criacao de Structs
typedef struct Data{
    int dia;
    int mes;
    int ano;
} dtData;

typedef struct Cliente{
    char nomeDoCliente[50];
    char telefoneDoCliente[15];
    dtData aniversarioDoCliente;
} dtCliente;

typedef struct Carro{
    dtCliente cliente;
    char modelo[50];
    char placa[10];
    int anoFabricacao;
    float kilometragem;
} dtCarro;

typedef struct Servico{
    int identificador;
    dtData dataDoServico;
    dtCarro carro;
    int tipoDeServico;
    char pago;
} dtServico;

// Funcoes de Estilizacao
void jump(void){
    printf("\n");
}
void styleCadastro(void){
    printf("=================================================================");
}

// Variaveis Globais
int         contagemCliente = 0,
            contagemCarros = 0;

dtCliente   clientesCadastrados[50];

dtCarro     carrosCadastrados[50];

// Criacao de Funcoes do Sistema
int validarNomes(char nomeCliente[]){
    int     i = 0;
    
    // Verificar se nome possui tamanho desejado
    if(strlen(nomeCliente) < 5){
        printf("Erro: Nome de cliente muito curto.");
        return 1;
    }
    // Verificar espacamento no inicio do nome
    if(nomeCliente[0] == ' '){
        printf("Erro: Espacamento no inicio do nome.");
        return 1;
    }
    // Verificar se ha numeros
    for(i = 0; i < strlen(nomeCliente); i++){
        if(nomeCliente[i] >= '0' && nomeCliente[i] <= '9'){
            printf("Erro: O nome nao pode conter numeros.");
            return 1;
        }
    }
    
    return 0;
}

int validarTelefone(char telefoneCliente[]){
    int     i = 0;
    
    // Verificar se numero inicial e 0
    if(telefoneCliente[0] != '0'){
        printf("Erro: Primeiro digito do telefone nao e 0.");
        return 1;
    }
    // Verificar se telefone possui tamanho desejado
    if(strlen(telefoneCliente) < 11 || strlen(telefoneCliente) > 12){
        printf("Erro: Numero de telefone muito grande ou muito pequeno.");
        return 1;
    }
    // Verificar se ha caracteres nao numericos
    for(i = 0; i < strlen(telefoneCliente); i++){
        if(telefoneCliente[i] < '0' || telefoneCliente[i] > '9'){
            printf("Erro: Numero de telefone invalido.");
            return 1;
        }
    }
    
    return 0;
}

int ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int diasNoMes(int mes, int ano) {
    switch (mes) {
        case 1:  // Janeiro
        case 3:  // Março
        case 5:  // Maio
        case 7:  // Julho
        case 8:  // Agosto
        case 10: // Outubro
        case 12: // Dezembro
            return 31;

        case 4:  // Abril
        case 6:  // Junho
        case 9:  // Setembro
        case 11: // Novembro
            return 30;

        case 2:  // Fevereiro
            return ehBissexto(ano) ? 29 : 28;

        default:
            return 0; 
    }
}

struct tm dataAtual; //dia, mes, ano, hora

void atualizarData() {
    time_t agora = time(NULL); // tempo atual 
    localtime_r(&agora, &dataAtual); //converte seg em data/hora e
}

void exibirData() {
    printf("Data de hoje: %02d/%02d/%04d\n",
        dataAtual.tm_mday,  
        dataAtual.tm_mon + 1,  //inicia no 0, por isso o +1
        dataAtual.tm_year + 1900);
}

int validarData(dtData data) {
    if (data.ano < 1950 || data.ano > 2025) {
        return 0;
    }

    if (data.mes < 1 || data.mes > 12) {
        return 0;
    }

    int dias = diasNoMes(data.mes, data.ano);
    if (data.dia < 1 || data.dia > dias) {
        return 0;
    }

    if (data.ano == 2025) {
        if (data.mes > 6 || (data.mes == 6 && data.dia > 27)) {
            return 0;
        }
    }

    return 1;
}

dtCliente cadastrarCliente(void){
    int     i = 1,
            j = 1,
            k = 1;
    
    styleCadastro();
    jump();
    
    do{
        printf("Digite o nome do Cliente: ");
        fgets(clientesCadastrados[contagemCliente].nomeDoCliente, 50, stdin);
        clientesCadastrados[contagemCliente].nomeDoCliente[strlen(clientesCadastrados[contagemCliente].nomeDoCliente) - 1] = '\0';
        
        i = validarNomes(clientesCadastrados[contagemCliente].nomeDoCliente);
        
        jump();
        
    }while(i != 0);
    
    do{
        printf("Digite o telefone do Cliente: ");
        fgets(clientesCadastrados[contagemCliente].telefoneDoCliente, 15, stdin);
        clientesCadastrados[contagemCliente].telefoneDoCliente[strlen(clientesCadastrados[contagemCliente].telefoneDoCliente) - 1] = '\0';
        
        j = validarTelefone(clientesCadastrados[contagemCliente].telefoneDoCliente);
        
        jump();
    }while(j != 0);
    
    do{
        printf("Digite a data de aniversário do Cliente: ");
        scanf("%02d %02d %04d", 
            &clientesCadastrados[contagemCliente].aniversarioDoCliente.dia, 
            &clientesCadastrados[contagemCliente].aniversarioDoCliente.mes, 
            &clientesCadastrados[contagemCliente].aniversarioDoCliente.ano);
            
            while (getchar() != '\n');
            
            k = validarData(clientesCadastrados[contagemCliente].aniversarioDoCliente);
            if(!k){
                printf("Data inválida.\n");
            }
            
    }while(k != 1);
    
    jump();
    
    printf("* Dados Cadastrados *");
    printf("\nNom.: %s", clientesCadastrados[contagemCliente].nomeDoCliente);
    printf("\nTel.: %s", clientesCadastrados[contagemCliente].telefoneDoCliente);
    printf("\nAni.: %02d/%02d/%04d", 
        clientesCadastrados[contagemCliente].aniversarioDoCliente.dia,
        clientesCadastrados[contagemCliente].aniversarioDoCliente.mes,
        clientesCadastrados[contagemCliente].aniversarioDoCliente.ano);
    
    
    jump();
    styleCadastro();
    
    contagemCliente++;
}

dtCarro cadastrarCarro(void){
    carrosCadastrados[contagemCarros].cliente = clientesCadastrados[contagemCarros];
    
    styleCadastro();
    jump();
    
    printf("Digite o modelo do carro: ");
    fgets(carrosCadastrados[contagemCarros].modelo, 50, stdin);
    carrosCadastrados[contagemCarros].modelo[strlen(carrosCadastrados[contagemCarros].modelo) - 1] = '\0';
    jump();
    printf("Digite a Placa do Carro: ");
    fgets(carrosCadastrados[contagemCarros].placa, 10, stdin);
    carrosCadastrados[contagemCarros].placa[strlen(carrosCadastrados[contagemCarros].placa) - 1] = '\0';
    jump();
    printf("Digite o ano de Fabricacao do Carro: ");
    scanf("%d", &carrosCadastrados[contagemCarros].anoFabricacao);
    jump();
    printf("Digite a kilometragem do Carro: ");
    scanf("%f", &carrosCadastrados[contagemCarros].kilometragem);
    jump();
    
    printf("* Cliente Dono do Carro *");
    printf("\nNom.: %s", carrosCadastrados[contagemCarros].cliente.nomeDoCliente);
    jump();
    jump();
    printf("* Dados Cadastrados *");
    printf("\nMod.: %s", carrosCadastrados[contagemCarros].modelo);
    printf("\nPla.: %s", carrosCadastrados[contagemCarros].placa);
    printf("\nAno.: %d", carrosCadastrados[contagemCarros].anoFabricacao);
    printf("\nKm..: %.3f", carrosCadastrados[contagemCarros].kilometragem);
    
    jump();
    styleCadastro();
}

// Corpo do codigo
int main(){
    cadastrarCliente();
    jump();
    cadastrarCarro();
    
    printf("\n>0 --- %d<", validarNomes("Thiago"));
    printf("\n>1 --- %d<", validarNomes("Alan"));
    printf("\n>1 --- %d<", validarNomes(" Thiago"));
    printf("\n>1 --- %d<", validarNomes("Th1ago"));
    
    printf("\n>0 --- %d<", validarTelefone("022922222222"));
    return 0;
}