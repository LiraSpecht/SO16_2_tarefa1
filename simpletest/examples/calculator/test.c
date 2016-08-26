#include "../../simpletest.h"
#include "calculator.h"
// Inlcuindo pthread no Visual Studio: http://web.cs.du.edu/~sturtevant/w13-sys/InstallingpthreadsforVisualStudio.pdf
#define HAVE_STRUCT_TIMESPEC //REMOVE O ERRO --> "pthread.h(320): error C2011: 'timespec': 'struct' type redefinition"
#include <pthread.h>

#define NUM_THREADS 8 //Define número de threads
#define CASOSTESTES 100 //Define a quantidade de casos de testes serão executados

int GLOBALVAR = 0; //variável compartilhada

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

char* concat(char *txt, int num) {
	char buffer[255];
	sprintf(buffer, txt, num);
	return buffer;
}

void *plusOne(void *arg) {
	//Função paralela que incrementa um valor na variável global

	DESCRIBE("SOMA GLOBAL");
	WHEN("I execute sum");

	int valGlobal = GLOBALVAR;
	int result = valGlobal + 1;

	char iftxt[50];
	char thentxt[50];
	sprintf(iftxt, "use numbers %ld and 1", GLOBALVAR);
	sprintf(thentxt, "the result should be %ld", result);
	
	IF(iftxt);
	THEN(thentxt);

	isEqual(sum(GLOBALVAR, 1), result); //Verifica se a soma surtiu efeito 
	GLOBALVAR = result; //Atribui a variavel compartilhada o valor da soma no inicio do processo
}

void doTheParallel() {
	//Função que irá realizar o paralelismo
	
	pthread_t threads[NUM_THREADS]; //Cria unidades de paralelismos
	for (int i = 0; i < NUM_THREADS; i++) {
		//Cria threads e executa-as, foi separado em incremento e decremento para tornar "mais dinâmico"
		pthread_create(&(threads[i]), NULL, plusOne, NULL);
	}
	for (int i = 0; i < NUM_THREADS; i++) {
		//Aguarda o fim de cada thread
		pthread_join(threads[i], NULL);
	}
}

void contaCasos() {
	//Função que conta a quantidade de possibilidades de resultados
	int contador[NUM_THREADS + 1]; //Teoricamente, há NUM_THREADS - 1 casos de resposta, de 1 à NUM_THREAD
									//No pior caso, cada thread é executada uma após a outra, resultando em NUM_THREAD
	for (int i = 0; i < NUM_THREADS + 1; i++) {
		contador[i] = -1; //"zerando" valores
	}
	
	for (int i = 0; i < CASOSTESTES; i++) {
		// Executa o paralelismo várias vezes
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
	sprintf(iftxt, "used %ld cases of test", CASOSTESTES);
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
	//3. Criar uma função em C que calcule o número de combinações possíveis de resultados de n threads executando x = x + 1 numa variável x compartilhada e não protegida por exclusão mútua. 
	//4. Criar casos de teste para a função usando simpletest. 
	//5. Submeter um único arquivo de texto contendo o código com a função e os casos de teste.

	contaCasos();

	system("PAUSE"); //Permite que se veja a saida dos dados
}