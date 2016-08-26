#include "../../simpletest.h"
#include "calculator.h"
// Inlcuindo pthread no Visual Studio: http://web.cs.du.edu/~sturtevant/w13-sys/InstallingpthreadsforVisualStudio.pdf
#define HAVE_STRUCT_TIMESPEC //REMOVE O ERRO --> "pthread.h(320): error C2011: 'timespec': 'struct' type redefinition"
#include <pthread.h>

#define MAX_CASES 10

int GLOBALVAR;

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

void *incGlobal(void *arg) {
	GLOBALVAR = GLOBALVAR + 1;
}

void *etapa3(void *arg) {
	DESCRIBE("SOMA X");
	WHEN("I execute sum");
	IF("use numbers 0 and 1");
	THEN("the result should be 1");
	isEqual(sum(GLOBALVAR, 1), 1);
	return NULL;
}

void doTheParallel() {
	//Cria unidades de paralelismos
	pthread_t threads[MAX_CASES];
	for (int i = 0; i < MAX_CASES; i++) {
		//Cria threads e executa-as
		pthread_create(&(threads[i]), NULL, incGlobal, NULL);
	}
	for (int i = 0; i < MAX_CASES; i++) {
		//Aguarda o fim de cada thread
		pthread_join(threads[i], NULL);
	}
	printf("NO FINAL SAIU %i\n", GLOBALVAR);
}


int main () {
	//test_sum();
	//test_sub();

	//1. Clonar o Simpletest de https://github.com/bundz/simpletest : DONE, firstCommit
	//2. Olhar o exemplo de calculadora : DONE, firstCommit
	//3. Criar uma função em C que calcule o número de combinações possíveis de resultados de n threads executando x = x + 1 numa variável x compartilhada e não protegida por exclusão mútua. 
	//4. Criar casos de teste para a função usando simpletest. 
	//5. Submeter um único arquivo de texto contendo o código com a função e os casos de teste.

	GLOBALVAR = 0; // Setando o valor inicial da variável global

	for(int i = 0; i < MAX_CASES; i++)
		doTheParallel();

	system("PAUSE");
}