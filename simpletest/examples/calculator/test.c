#include "../../simpletest.h"
#include "calculator.h"
// Inlcuindo pthread no Visual Studio: http://web.cs.du.edu/~sturtevant/w13-sys/InstallingpthreadsforVisualStudio.pdf
#define HAVE_STRUCT_TIMESPEC //REMOVE O ERRO --> "pthread.h(320): error C2011: 'timespec': 'struct' type redefinition"
#include <pthread.h>

#define MAX_CASES 3

int *GLOBALVAR;

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

void *incGlobal(void *arg) {
	//Função paralela que incrementa um valor na variável global
	int x = *GLOBALVAR; //Obtem o valor atual da variavel
	int y = x + 1; //Calcula a soma que deveria ser obtido

	char iftxt[255];
	char thentxt[255];

	sprintf(iftxt, "use numbers %ld and 1", x);
	sprintf(thentxt, "the result should be %ld", y);

	DESCRIBE("SOMA GLOBAL");
	WHEN("I execute sum");
	IF(iftxt);
	THEN(thentxt);
	*GLOBALVAR = *GLOBALVAR + 1; //Realiza a soma de verdade
	x = *GLOBALVAR;
	isEqual(sum(x, 1), y); //Verifica se a soma surtiu efeito 
}

void *decGlobal(void *arg) {
	//Função paralela que decrementa um valor na variável global
	int x = *GLOBALVAR; //Obtem o valor atual da variavel
	int y = x - 1; //calcula a subtração que deveria ser obtida
	char iftxt[255];
	char thentxt[255];

	sprintf(iftxt, "use numbers %ld and 1", x);
	sprintf(thentxt, "the result should be %ld", y);

	DESCRIBE("SUB GLOBAL");
	WHEN("I execute sub");
	IF(iftxt);
	THEN(thentxt);
	*GLOBALVAR = *GLOBALVAR - 1; //Realiza a subtração de verdade
	x = *GLOBALVAR;
	isEqual(sub(x, 1), y); //Verifica se a subtração surtiu efeito
}

void *contaCasos(void *arg) {
	//Função que conta a quantidade de possibilidades de resultados
}

void doTheParallel() {
	//Função que irá realizar o paralelismo
	
	pthread_t threads[MAX_CASES]; //Cria unidades de paralelismos
	for (int i = 0; i < MAX_CASES; i++) {
		//Cria threads e executa-as, foi separado em incremento e decremento para tornar "mais dinâmico"
		if(i % 2 == 0)
			pthread_create(&(threads[i]), NULL, incGlobal, NULL);
		else
			pthread_create(&(threads[i]), NULL, decGlobal, NULL);
	}
	for (int i = 0; i < MAX_CASES; i++) {
		//Aguarda o fim de cada thread
		pthread_join(threads[i], NULL);
	}
}


int main () {
	//test_sum();
	//test_sub();

	//1. Clonar o Simpletest de https://github.com/bundz/simpletest : DONE, firstCommit
	//2. Olhar o exemplo de calculadora : DONE, firstCommit
	//3. Criar uma função em C que calcule o número de combinações possíveis de resultados de n threads executando x = x + 1 numa variável x compartilhada e não protegida por exclusão mútua. 
	//4. Criar casos de teste para a função usando simpletest. 
	//5. Submeter um único arquivo de texto contendo o código com a função e os casos de teste.

	int oGlobal = 0;
	GLOBALVAR = &oGlobal; // Setando o valor inicial da variável global

	//for(int i = 0; i < MAX_CASES; i++) //Repete o teste várias vezes, [OPCIONAL]
		doTheParallel();

	printf("Global iniciou com ZERO, terminou com %i\n", *GLOBALVAR); //Mostra o valor final obtido no processo
	system("PAUSE"); //Permite que se veja a saida dos dados
}