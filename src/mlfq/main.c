#include <stdio.h>	// FILE, fopen, fclose, etc.
#include <stdlib.h> // malloc, calloc, free, etc
#include "../process/process.h"
#include "../queue/queue.h"
#include "../file_manager/manager.h"

int main(int argc, char const *argv[])
{
	/*Lectura del input*/
	char *file_name = (char *)argv[1];
	InputFile *input_file = read_file(file_name);

	/*Mostramos el archivo de input en consola*/
	printf("Nombre archivo: %s\n", file_name);
	printf("Cantidad de procesos: %d\n", input_file->len);
	printf("Procesos:\n");
	struct Queue *queue_a;
	struct Queue *queue_b;
	struct Queue *queue_c;
	struct Queue *processes;
	struct Queue *finished;

	queue_a = newQueue();
	queue_b = newQueue();
	queue_c = newQueue();
	processes = newQueue();
	finished = newQueue();

	int last_time = -1;
	int last_index = -1;

	for (int i = 0; i < input_file->len; ++i)
	{
		// for (int j = 0; j < 7; ++j)
		// {	
		// 	printf("%s ", input_file->lines[i][j]);
		// }
		
		Process *process;
		process = newProcess(input_file->lines[i][0], atoi(input_file->lines[i][1]), atoi(input_file->lines[i][2]), atoi(input_file->lines[i][3]), atoi(input_file->lines[i][4]), atoi(input_file->lines[i][5]), atoi(input_file->lines[i][6]));
		//agregar procesos a queue processes
		int largo = 0;
		largo = enqueue(processes, process);
		printf("\nProcesses tiene %d elementos\n", largo);
		printf("\nSe agrega el proceso pid %d \n", process->pid);
		// enqueue(a, process );
	}
	// print_list(processes);
	//code scheduler
	int cycle = 0;
	printf("Inicia ciclo 0\n");
	int largo_a;
	while (cycle <= 20){
		//comienzo ciclo
		//Añado un proceso si tiene que entrar
		Process* new_process =  startProcess(processes, cycle);
		printf("ciclo numero: %d\n", cycle);
		while (new_process != NULL){
			largo_a = enqueue(queue_a, new_process);
			// printf("Entrar lista A en el puesto %d: \n\n",largo_a);
			// printf("STATUS %d de proceso \n",new_process->status);
			new_process =  startProcess(processes, cycle);
		}
		// Process* proceso_ready;
		// proceso_ready = readyProcesses(queue_a);
		if (readyProcesses(queue_a)){
			printf("Ejecutando\n");
			actualizeCycle(queue_a);
		}
		//final ciclo
		cycle += 1;
	}
	printf("Inicia liberacion de memoria\n");

	// realese memory
	freeQueue(queue_a);
	printf("A");
	freeQueue(queue_b);
	printf("B");
	freeQueue(queue_c);
	printf("C");
	freeQueue(processes);
	printf("D");
	freeQueue(finished);
	printf("E");
	input_file_destroy(input_file);
}