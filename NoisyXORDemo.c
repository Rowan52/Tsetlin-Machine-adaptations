#include "MultiClassTsetlinMachine.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUMBER_OF_TRAINING_EXAMPLES 60000
#define NUMBER_OF_TEST_EXAMPLES 10000
int epoch = 1 ;
int X_train[NUMBER_OF_TRAINING_EXAMPLES][FEATURES];
int y_train[NUMBER_OF_TRAINING_EXAMPLES];

int X_test[NUMBER_OF_TEST_EXAMPLES][FEATURES];
int y_test[NUMBER_OF_TEST_EXAMPLES];

void read_file(void)
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	const char *s = " ";
	char *token = NULL;

	fp = fopen("MNISTTraining.txt", "r");
	if (fp == NULL) {
		printf("Error opening\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < NUMBER_OF_TRAINING_EXAMPLES; i++) {
		getline(&line, &len, fp);

		token = strtok(line, s);
		for (int j = 0; j < FEATURES; j++) {
			X_train[i][j] = atoi(token);
			token=strtok(NULL,s);
		}
		y_train[i] = atoi(token);
	}

	fp = fopen("MNISTTest.txt", "r");
	if (fp == NULL) {
		printf("Error opening\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < NUMBER_OF_TEST_EXAMPLES; i++) {
		getline(&line, &len, fp);

		token = strtok(line, s);
		for (int j = 0; j < FEATURES; j++) {
			X_test[i][j] = atoi(token);
			token=strtok(NULL,s);
		}
		y_test[i] = atoi(token);
	}
}


int main(void)
{	
	srand(time(NULL));

	read_file();

	struct MultiClassTsetlinMachine *mc_tsetlin_machine = CreateMultiClassTsetlinMachine();

	float average = 0.0;
	for (int i = 0; i < 25; i++) {
		mc_tm_initialize(mc_tsetlin_machine);
		clock_t start_total = clock();
		mc_tm_fit(mc_tsetlin_machine, X_train, y_train, NUMBER_OF_TRAINING_EXAMPLES, epoch , 3.9);
		
		clock_t end_total = clock();
		double time_used = ((double) (end_total - start_total)) / CLOCKS_PER_SEC;

		printf("EPOCH %d TIME: %f\n", i+1, time_used);
		average += mc_tm_evaluate(mc_tsetlin_machine, X_test, y_test, NUMBER_OF_TEST_EXAMPLES);

		printf("Average accuracy: %f\n", average/(i+1));
		tm_feedback_print(i , average/(i+1) , epoch );
	}
	
	
	return 0;
}
