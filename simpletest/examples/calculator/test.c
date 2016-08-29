/****************************************************/
/****************************************************/
/*        Trabalho 1 de Sistemas Operacionais       */
/*              Autoria de Lira Specht              */
/*                 Semestre 2016-2                  */
/****************************************************/
/****************************************************/


#include "../../simpletest.h"
#include "calculator.h"

// Incluindo pthread no Visual Studio: http://web.cs.du.edu/~sturtevant/w13-sys/InstallingpthreadsforVisualStudio.pdf
#define HAVE_STRUCT_TIMESPEC //REMOVE O ERRO --> "pthread.h(320): error C2011: 'timespec': 'struct' type redefinition"
#include <pthread.h>

#define TESTE_NUMERO 7 //H� tr�s testes, que varia o n�mero de Threads e de Casos de Teste para apurar as respostas [teste: threads x casos de teste]
						// 1: 4  x  50
						// 2: 4  x 100
						// 3: 8  x 100
						// 4: 8  x 150
						// 5: 16 x 150
						// 6: 16 x 200
						// ?: 32 x 200

#if TESTE_NUMERO == 1
	#define NUM_THREADS 4 //Define n�mero de threads
	#define CASOSTESTES 50 //Define a quantidade de casos de testes ser�o executados
#elif TESTE_NUMERO == 2
	#define NUM_THREADS 4 //Define n�mero de threads
	#define CASOSTESTES 100 //Define a quantidade de casos de testes ser�o executados
#elif TESTE_NUMERO == 3
	#define NUM_THREADS 8 //Define n�mero de threads
	#define CASOSTESTES 100 //Define a quantidade de casos de testes ser�o executados
#elif TESTE_NUMERO == 4
	#define NUM_THREADS 8 //Define n�mero de threads
	#define CASOSTESTES 150 //Define a quantidade de casos de testes ser�o executados
#elif TESTE_NUMERO == 5
	#define NUM_THREADS 16 //Define n�mero de threads
	#define CASOSTESTES 150 //Define a quantidade de casos de testes ser�o executados
#elif TESTE_NUMERO == 6
	#define NUM_THREADS 16 //Define n�mero de threads
	#define CASOSTESTES 200 //Define a quantidade de casos de testes ser�o executados
#else
	#define NUM_THREADS 32 //Define n�mero de threads
	#define CASOSTESTES 200 //Define a quantidade de casos de testes ser�o executados
#endif // TESTE_NUMERO == 1


int GLOBALVAR = 0; //vari�vel compartilhada


void test_sum(){
	DESCRIBE("SUM");
	WHEN("I execute sum");
	IF("use numbers 3 and 5");
	THEN("the result should be 8");
	isEqual(sum(3,5), 8);

	IF("use numbers 0 and 0");
	THEN("the result should be 0");
	isEqual(sum(0, 0), 0);

	IF("use numbers 7 and 1");
	THEN("the result should be greater than 7");
	isGreaterThan(sum(7, 1), 7);
}

void test_sub() {
	DESCRIBE("SUB");
	WHEN("I execute sub");
	IF("use numbers 3 and 5");
	THEN("the result should be -2");
	isEqual(sub(1,5), -2);

	IF("use numbers 0 and 0");
	THEN("the result should be 0");
	isEqual(sum(0, 0), 0);
}

void *plusOne(void *arg) {
	//Fun��o paralela que incrementa um valor na vari�vel global

	int valGlobal = GLOBALVAR;
	int result = valGlobal + 1;

	char iftxt[50];
	char thentxt[50];
	sprintf(iftxt, "use numbers %ld and 1", GLOBALVAR);
	sprintf(thentxt, "the result should be %ld", result);

//	DESCRIBE("SOMA THREAD");
//	WHEN("I execute sum using threads");
//	IF(iftxt);
//	THEN(thentxt);
//	isEqual(sum(GLOBALVAR, 1), result); //Verifica se a soma surtiu efeito 

	GLOBALVAR = result; //Atribui a variavel compartilhada o valor da soma no inicio do processo
}

void doTheParallel() {
	//Fun��o que ir� realizar o paralelismo
	
	pthread_t threads[NUM_THREADS]; //Cria unidades de paralelismos
	for (int i = 0; i < NUM_THREADS; i++) {
		//Cria threads e executa-as, foi separado em incremento e decremento para tornar "mais din�mico"
		pthread_create(&(threads[i]), NULL, plusOne, NULL);
	}
	for (int i = 0; i < NUM_THREADS; i++) {
		//Aguarda o fim de cada thread
		pthread_join(threads[i], NULL);
	}
}

void contaCasos() {
	//Fun��o que conta a quantidade de possibilidades de resultados
	
	int contador[NUM_THREADS + 1]; //Teoricamente, h� NUM_THREADS - 1 casos de resposta, de 1 � NUM_THREAD
									//No pior caso, cada thread � executada uma ap�s a outra, resultando em NUM_THREAD
	for (int i = 0; i < NUM_THREADS + 1; i++) {
		contador[i] = -1; //"zerando" valores
	}
	
	for (int i = 0; i < CASOSTESTES; i++) {
		// Executa o paralelismo v�rias vezes
		GLOBALVAR = 0;
		doTheParallel();
		contador[GLOBALVAR]++;
	}
	
	int totalRespostasDiferentes = 0;
	for (int i = 0; i < NUM_THREADS + 1; i++) {
		if (contador[i] != -1) {
			totalRespostasDiferentes++; // para cada valor diferente encontrado
		}
	}

	char iftxt[255];
	char thentxt[255];
	sprintf(iftxt, "used %ld cases of test and %ld threads", CASOSTESTES, NUM_THREADS);
	sprintf(thentxt, "it was possible obtained a tottal of %ld different answer", totalRespostasDiferentes);

	DESCRIBE("COUNTER");
	WHEN("I execute counter");
	IF(iftxt);
	THEN(thentxt);
}

int main () {
	
	//test_sum();
	//test_sub();

	//1. Clonar o Simpletest de https://github.com/bundz/simpletest : DONE, firstCommit
	//2. Olhar o exemplo de calculadora : DONE, firstCommit
	//3. Criar uma fun��o em C que calcule o n�mero de combina��es poss�veis de resultados de n threads executando x = x + 1 numa vari�vel x compartilhada e n�o protegida por exclus�o m�tua. 
	//4. Criar casos de teste para a fun��o usando simpletest. 
	//5. Submeter um �nico arquivo de texto contendo o c�digo com a fun��o e os casos de teste.

	contaCasos(); // Inicia o Teste, conforme as configura��es feitas no #define TESTE_NUMERO
	system("PAUSE"); //Permite que se veja a saida dos dados
}