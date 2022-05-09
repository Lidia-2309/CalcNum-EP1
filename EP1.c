/*
INTEGRANTES DA EQUIPE:

ANA LIDIA LISBOA
GABRIEL FELICIANO
LETICIA SAMPAIO
MARINA BRASIL
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.00000001 // isso é igual a 10 elevado a -8

void conversao(double num);
void sistemaLinear();
void equacaoAlgebrica();
void metodoNewton(int grauEquacao, double *coeficientes);
void trocas(double *a, double *b);

int main()
{

    char comando = 0;
    double num_conv = 0.0;

    do
    {
        printf("\n\n==== MENU ====\n");
        printf("'C' - Conversao\n'S' - Sistema Linear\n'E' - Equacao Algebrica\n'F' - Finalizar\n");
        printf("Digite a opcao desejada: ");
        scanf(" %c%*[^\n]", &comando); // recebe o comando e limpa o buffer

        switch (comando)
        {
        case 'C':
            printf("insira o numero decimal para conversao: ");
            scanf("%lf", &num_conv);
            // printf("%lf\n", num_conv);
            conversao(num_conv);

            /*
            !!!ATENCAO!!!
            PRECISA MELHORAR A PRECISAO DO SCANF
            NÃO ESTA PEGANDO CASAS DECIMAIS DEPOIS DA 6ª
            */

            break;

        case 'S':
            printf("vc escolheu sistema linear");
            sistemaLinear();
            break;

        case 'E':
            printf("vc escolheu equacao algebrica");
            equacaoAlgebrica();
            break;

        case 'F':
            printf("vc escolheu finalizar a aplicacao");
            break;

        default:
            printf("Opcao invalida, tente novamente.");
            break;
        }
    } while (comando != 'F');
}

void conversao(double num)
{

    // --------------------------- CONVERSAO BINARIA --------------------------------//

    // vetor para salvar o numero binario
    int numBinarioInt[32];  // parte inteira do numero binario
    int numBinarioFrac[32]; // parte fracionaria do numero binario

    char isSigned = 0;

    if (num < 0.0)
    {
        isSigned = 1;
        num = -num;
    }

    int n = (int)num;
    // printf("%d", n);
    double m = num - n;
    // printf("%lf", m);

    // conversao da parte inteira
    int i = 0; // armazena qtd de casas da parte inteira
    while (n > 0)
    {
        numBinarioInt[i] = n % 2; // salva resto da divisao por 2
        n = n / 2;                // salva o resultado inteiro da divisao por 2
        i++;                      // aumenta contador para impressao ao final
    };

    // imprime a parte inteira em ordem inversa
    printf("Binario: ");
    if (isSigned)
        printf("-");
    for (int j = i - 1; j >= 0; j--)
        printf("%d", numBinarioInt[j]);

    // testa se existe parte fracionaria antes de fazer a conversao
    int k = 0; // armazena qtd de casas da parte fracionaria
    if (m)
    {
        // conversao da parte fracionaria
        while (m > 0)
        {
            numBinarioFrac[k] = (int)(m *= 2); // salva a parte inteira da multiplicacao
            m = m - (int)m;                    // salva somente a parte fracionaria apos multiplicacao
            k++;                               // aumenta contador para impressao ao final
        };
        printf(".");
        // imprime a parte fracionaria em ordem direta
        for (int l = 0; l < k && l < 20; l++)
            printf("%d", numBinarioFrac[l]);
    };

    // -------------------------- CONVERSAO OCTAL -----------------------------------//

    // vetor para salvar o numero octal
    int numOctalInt[32];  // parte inteira do numero octal
    int numOctalFrac[32]; // parte fracionaria do numero octal

    double div_int = ceil(i / 3.0);  // encontra quantos conjuntos de 3 existem no inteiro
    double div_frac = ceil(k / 3.0); // encontra quantos conjuntos de 3 existem na fracao

    n = (int)num;
    m = num - n;

    int j = 0;
    while (n)
    {
        numOctalInt[j++] = (n & 0b111);
        n >>= 3;
    }
    printf("\nOctal: ");
    if (isSigned)
        printf("-");
    for (j = div_int - 1; j >= 0; j--)
        printf("%d", numOctalInt[j]);

    j = 0;
    while (m && j < 20)
    {
        m *= 8;
        numOctalFrac[j++] = (int)m;
        m = m - (int)m;
    }
    printf(".");

    for (j = 0; j < div_frac; j++)
        printf("%d", numOctalFrac[j]);

    // ----------------------- CONVERSAO HEXADECIMAL --------------------------------//

    // vetor para salvar o numero octal
    int numHexaInt[32];  // parte inteira do numero hexadecimal
    int numHexaFrac[32]; // parte fracionaria do numero hexadecimal

    div_int = ceil(i / 4.0);  // encontra quantos conjuntos de 4 existem no inteiro
    div_frac = ceil(k / 4.0); // encontra quantos conjuntos de 4 existem na fracao

    n = (int)num;
    m = num - n;

    int q = 0;
    while (n)
    {
        numHexaInt[q++] = (n & 0b1111);
        n >>= 4;
    }
    printf("\nHexadecimal: ");
    if (isSigned)
        printf("-");
    for (q = div_int - 1; q >= 0; q--)
        printf("%X", numHexaInt[q]);

    q = 0;
    while (m && q < 20)
    {
        m *= 16;
        numHexaFrac[q++] = (int)m;
        m = m - (int)m;
    }
    printf(".");

    for (q = 0; q < div_frac; q++)
        printf("%X", numHexaFrac[q]);
};

void trocas(double *a, double *b)
{
    /*
    Funcao para auxiliar nas trocas de valores em diferentes posicoes de um
    ponteiro do tipo double.
    */
    double aux;

    aux = *a;
    *a = *b;
    *b = aux;
} // Acabou a função: trocas

int verificaDigitado(int n, int grauEquacao)
{
    /*
    Funcao criada para verificar se o número que foi digitado no coeficiente
    é 0 no caso de x[n] e x[0]
    */

    int digitado;
    printf("Valor invalido. Digite novamente\n");
    scanf("%d", &digitado);

    if ((digitado <= 0 && n != grauEquacao) ||
        (digitado == 0 && n == grauEquacao))
    {
        digitado = verificaDigitado(n, grauEquacao);
    }
    return digitado;
} // Acabou a função: verificaDigitado

void sistemaLinear()
{
    printf("teste2");
};

void equacaoAlgebrica()
{
    /*
    Função vai ler o grau de uma equacao algebrica, ler o coeficientes de n até
    0 Vai dar erro caso x[n] <= 0 ou x[0]
    */

    int grauEquacao, i, contLimites = 0, novoValor;
    double *coeficientes;

    printf("\nDigite o grau da equacao: ");
    scanf("%d%*c", &grauEquacao);

    coeficientes = malloc(sizeof(double) * grauEquacao + 1);

    // Caso coeficiente é nulo
    if (coeficientes == NULL)
    {
        printf("\n\nFaltou memoria.\n");
        return;
    }

    /*
    Vai receber os valores do coeficiente, verificando se o x[n] >= 0 e
    x[0] != 0 para funcionar
    */
    for (i = 0; i <= grauEquacao; i++)
    {
        printf("\nDigite x[%d]: ", grauEquacao - i);
        scanf("%lf%*c", &coeficientes[i]);
        if (((i == 0) && (coeficientes[i] <= 0)) ||
            ((i == (grauEquacao)) && (coeficientes[i] == 0)))
        {
            novoValor = verificaDigitado(i, grauEquacao);
            coeficientes[i] = novoValor;
        }
    }
    // Chamada do metodo de Newton
    metodoNewton(grauEquacao, coeficientes);

    // Desalocar memória
    free(coeficientes);

} // Acabou a função: equacaoAlgebrica

void metodoNewton(int grauEquacao, double *coeficientes)
{
    /*
    Função de metodoNewton começa recebendo o resultado do f(x) e f'(x).
    Zeramos as funções para o x[0]
    para x[0] usamos o limite superior do teorema de lagrande
    Depois imprimimos a quantidade de interação e a raiz aproximada
    */

    double aux, *dfx, x = 10, fx[2];
    // x: aproximacao resultante (limite superior)
    int contaIteracoes, i, z;
    // fx é o polinomio e a derivada

    dfx = malloc(sizeof(double) * grauEquacao);
    // Se a derivada for nula
    if (dfx == NULL)
    {
        printf("\n\nFaltou memoria.\n");
        return;
    }

    for (i = 0; i < grauEquacao; i++)
    {
        dfx[i] =
            coeficientes[i] *
            (grauEquacao - i); //	Encontramos os coeficientes da f'(x) de f(x)
    }

    for (contaIteracoes = 0; contaIteracoes < 1000; contaIteracoes++)
    {
        fx[0] = 0; //	Zerando o valor de f'(x)
        fx[1] = 0; //	Zerando o valor de f'(x)
        for (z = 0; z <= grauEquacao; z++)
        {
            // Vamos começar o metodo de Newton com a formula x[n+1] = x[n]-f(x)/f'(x)

            fx[0] += pow(x, grauEquacao - z) * coeficientes[z]; // Calcula f(x)
            if (z != grauEquacao)
                fx[1] += pow(x, grauEquacao - z - 1) * dfx[z]; // Calcula f'(x)
        }
        // metodo principal
        aux = x - fx[0] / fx[1];

        if (fabs(aux - x) < EPSILON)
        {
            printf("\n\nIteracoes: %d\n", contaIteracoes);
            printf("\nx = %lf", x);
            free(dfx);
            return;
        }
        x = aux;
    }

    printf("\n\nIteracoes: %d\n", contaIteracoes);
    printf("\nx = %lf\n", x);
    free(dfx);

} // Acabou a função: metodoNewton
