#include <stdio.h>
// Criando o tipo de dados "Carta", para armazenar as características relevantes para o jogo
typedef struct  {
    char estado;            // Letra do Estado (A-H)
    int numero;             // Número da Cidade (1-4)
    
    char codigo[4];         // Código da carta (ex: A01)
    char cidade[100];       // Nome da Cidade
    
    int populacao;          // População da cidade
    int pontosTuristicos;   // Quantidade de pontos turísticos
    
    float area;             // Area em km²
    float pib;              // PIB em bilhões0
    
    float densidade;        // População / Área
    float pibPerCapita;     // Pib / População
    float superPoder;       // Soma das propriedades
} carta;

void cadastrarCarta(carta *carta) {
    // Solicita e grava código do estado, adicionado uma validação para aceitar somente as letras de A até H
    do {
        printf("Informe o estado (A-H):\n");
        scanf(" %c", &carta->estado);
        
        if (carta->estado <'A' || carta->estado > 'H') {
            printf("Erro: Estado incorreto, informe novamente o Estado (A-H):\n");
        }
    } while (carta->estado <'A' || carta->estado > 'H');
    // Solicita e grava o número da cidade, adicionado uma validação para aceitar somente os números de 1 até 4
    do {
        printf("Informe o número da carta (1-4):\n");
        scanf("%d", &carta->numero);
        
        if (carta->numero < 1 || carta->numero > 4) {
            printf("Erro: Número incorreto, informe novamente o número (1-4):\n");
        }
    } while (carta->numero < 1 || carta->numero > 4);
    // Solicita e grava o nome da cidade
    printf("Informe o nome da cidade:\n");
    scanf(" %[^\n]", carta->cidade);
    // Solicita e grava a quantidade populacional
    printf("Informe a população total da cidade:\n");
    scanf("%d", &carta->populacao);
    // Solicita e grava a área total da cidade
    printf("Informe a área em km²:\n");
    scanf("%f", &carta->area);
    // Solicita e grava o PIB da cidade em Bilhões (2.5) para facilitar para o usuário
    printf("Informe o PIB em bilhões(ex:1.83):\n");
    scanf("%f", &carta->pib);
    // Solicita e grava a quantidade de pontos turísticos
    printf("Informe a quantidade de pontos turísticos:\n");
    scanf("%d", &carta->pontosTuristicos);
    
    // Realiza cálculos dos demais atributos
    //concatena o código do estado mais a cidade acrescentando o zero antes do número
    sprintf(carta->codigo, "%c%02d", carta->estado, carta->numero);
    // Divida a quantidade populacional pela area para ter a densidade
    carta->densidade = carta->populacao/ carta->area;
    // Realiza a multiplicação do PIB por 1e9(1Bilhão para ter o valor bruto)
    carta->pibPerCapita = (carta->pib * 1e9) / carta->populacao;
    // Soma tudo para obter o super poder
    carta->superPoder =
        carta->populacao +
        carta->area +
        carta->pib +
        carta->pontosTuristicos +
        carta->pibPerCapita +
        (1 / carta->densidade); // Divide 1 pela densidade para inverter o peso do valor onde a menor densidade sempre será melhor
}
// Cria função para comparar os valores recebendo a propriedade que será comparada e os valores de cada carta
// e um flag para dizer se a comparação é pela maior ou não
void compararCartas(char *propriedade, char *cidadeCarta1, char *cidadeCarta2 , float valorCarta1, float valorCarta2, int maiorVence ) {
    //Inicia mostrando a propriedade que está comparando
    printf("%s: ", propriedade);
    
    if (maiorVence) {
        if (valorCarta1 > valorCarta2) printf("%s venceu!\n", cidadeCarta1);
        else if (valorCarta2 > valorCarta1) printf("%s venceu!\n", cidadeCarta2);
        else printf("Empate!\n");
    } else {
        if (valorCarta1 < valorCarta2) printf("%s venceu!\n", cidadeCarta1);
        else if (valorCarta2 < valorCarta1) printf("%s venceu!\n", cidadeCarta2);
        else printf("Empate!\n");
    }
}

void mostrarCarta(carta carta) {
    printf("Código: %s\n", carta.codigo);
    printf("Cidade: %s\n", carta.cidade);
    printf("População: %d\n", carta.populacao);
    printf("Pontos Turísticos: %d\n", carta.pontosTuristicos);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: %.2f bilhões\n", carta.pib);
    printf("Densidade: %.2f hab/km²\n", carta.densidade);
    printf("PIB per Capita: %.2f\n", carta.pibPerCapita);
    printf("Super Poder: %.2f\n", carta.superPoder);
}

int main()
{
    // Inicia declarando nosso tipo de dados criado
    carta carta1, carta2;
    
    // Inicia o cadastro da primeira carta chamando a função criada para cadastrar os valores conforme o jogo
    printf("--- Cadastrando Carta 1 ---\n");
    cadastrarCarta(&carta1);
    
    // Continua com o cadastro da segunda carta
    printf("--- Cadastrando Carta 2 ---\n");
    cadastrarCarta(&carta2);
    
    printf("\n--- Cartas jogadas ---\n");
    printf("\n--- Carta 1 ---\n");
    mostrarCarta(carta1);
    printf("\n--- Carta 2 ---\n");
    mostrarCarta(carta2);
    
    printf("\n--- Comparando as Cartas ---\n");
    compararCartas("População", carta1.cidade, carta2.cidade, carta1.populacao, carta2.populacao, 1);
    compararCartas("Area", carta1.cidade, carta2.cidade, carta1.area, carta2.area, 1);
    compararCartas("PIB", carta1.cidade, carta2.cidade, carta1.pib, carta2.pib, 1);
    compararCartas("Pontos Turísticos", carta1.cidade, carta2.cidade, carta1.pontosTuristicos, carta2.pontosTuristicos, 1);
    compararCartas("PIB per Capita", carta1.cidade, carta2.cidade, carta1.pibPerCapita, carta2.pibPerCapita, 1);
    compararCartas("Densidade Populacional", carta1.cidade, carta2.cidade, carta1.densidade, carta2.densidade, 0);
    compararCartas("Super Poder", carta1.cidade, carta2.cidade, carta1.superPoder, carta2.superPoder, 1);
    
    return 0;
}
