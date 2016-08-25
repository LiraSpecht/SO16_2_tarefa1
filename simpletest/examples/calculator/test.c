#include "../../simpletest.h"
#include "calculator.h"
// Inlcuindo pthread no Visual Studio: https://linqtolinq.wordpress.com/2012/04/24/setting-up-pthreads-in-windows-under-visual-studio/
#include "../trab1SO/pthread-win32/pthread.h"

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

void *etapa3(void *arg) {
	int x = 0;
	DESCRIBE("SOMA X");
	WHEN("I execute sum");
	IF("use numbers 0 and 1");
	THEN("the result should be 1");
	isEqual(sum(x, 1), 1);
	return NULL;
}

/*void doTheParallel() {
	pthread_t threads;
	pthread_create(&(threads), NULL, etapa3, NULL);
	pthread_join(threads, NULL);
}*/

void *thread_func(void *arg) {
	return 0;
}



int main () {
	//test_sum();
	//test_sub();

	//1. Clonar o Simpletest de https://github.com/bundz/simpletest : DONE, firstCommit
	//2. Olhar o exemplo de calculadora : DONE, firstCommit
	//3. Criar uma fun��o em C que calcule o n�mero de combina��es poss�veis de resultados de n threads executando x = x + 1 numa vari�vel x compartilhada e n�o protegida por exclus�o m�tua. 
	//4. Criar casos de teste para a fun��o usando simpletest. 
	//5. Submeter um �nico arquivo de texto contendo o c�digo com a fun��o e os casos de teste.

	//paralelismo();

	pthread_t threads;
	pthread_create(&threads, NULL, thread_func, NULL);
	pthread_join(threads, NULL);

	system("PAUSE");
}
