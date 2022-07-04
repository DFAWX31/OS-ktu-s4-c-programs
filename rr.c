#include <stdio.h>

typedef struct {
	int process_id, arrival_time, burst_time, waiting_time, turnaround_time, remaining_time;
} program;

void sort(program*, int);
int remove_front_from_ready_queue(int*, int*);
int isin(int*, int, int);

void main() {
	int num;

	printf("Enter the number of processes: ");
	scanf("%d", &num);

	program programs[num];

	for (int i = 0; i < num; i++) {
		programs[i].process_id = i + 1;

		printf("Enter the arrival time and burst time of the process number %d: ", i + 1);
		scanf("%d %d", &programs[i].arrival_time, &programs[i].burst_time);

		programs[i].remaining_time = programs[i].burst_time;
	}

	sort(programs, num);

	int time_quantum;

	printf("Enter the time quantum: ");
	scanf("%d", &time_quantum);

	int ready_queue[num], ready_queue_size = -1;
	int in_ready_queue_stack[num], in_ready_queue_stack_top = -1;

	int pid = 0;

	int time = programs[pid].arrival_time;

	ready_queue[++ready_queue_size] = pid;
	pid = remove_front_from_ready_queue(ready_queue, &ready_queue_size);
	in_ready_queue_stack[++in_ready_queue_stack_top] = pid;

	int max_time = time;

	for (int i = 0; i < num; i++) {
		max_time += programs[i].burst_time;
	}

	while (time < max_time) {
		// printf("----------\n\ntime: %d\n", time);

		// printf("ready queue size: %d\nready queue: ", ready_queue_size + 1);

		// for (int i = 0; i <= ready_queue_size; i++) {
		// 	printf("%d\t", programs[ready_queue[i]].process_id);
		// }
		// printf("\n");

		// printf("done stack size: %d\ndone stack: ", in_ready_queue_stack_top + 1);

		// for (int i = 0; i <= in_ready_queue_stack_top; i++) {
		// 	printf("%d\t", programs[in_ready_queue_stack[i]].process_id);
		// }
		// printf("\n");

		// printf("process id: %d\n----------\n\n", programs[pid].process_id);
		
		if (programs[pid].remaining_time > time_quantum) {		
			time += time_quantum;
			programs[pid].remaining_time -= time_quantum;
		} else {
			time += programs[pid].remaining_time;
			programs[pid].remaining_time = 0;

			programs[pid].turnaround_time = time - programs[pid].arrival_time;
			programs[pid].waiting_time = programs[pid].turnaround_time - programs[pid].burst_time;
		}

		if (in_ready_queue_stack_top < num - 1) {
			for (int i = 0; i < num; i++) {
				if (isin(in_ready_queue_stack, in_ready_queue_stack_top, i) == 0) {
					if (programs[i].arrival_time <= time) {
						ready_queue[++ready_queue_size] = i;
						in_ready_queue_stack[++in_ready_queue_stack_top] = i;
					} else {
						break;
					}
				}
			}
		}
		
		if (programs[pid].remaining_time != 0) {
			ready_queue[++ready_queue_size] = pid;
		}

		pid = remove_front_from_ready_queue(ready_queue, &ready_queue_size);
	}

	int total_waiting_time = 0, total_turnaround_time = 0;

	printf("pid\tat\tbt\twt\ttt\n");
	for (int i = 0; i < num; i++) {
		total_waiting_time += programs[i].waiting_time;
		total_turnaround_time += programs[i].turnaround_time;

		printf("%d\t%d\t%d\t%d\t%d\n", programs[i].process_id, programs[i].arrival_time, programs[i].burst_time, programs[i].waiting_time, programs[i].turnaround_time);
	}

	float average_turnaround_time = (float)total_turnaround_time / (float)num;
	float average_waiting_time = (float)total_waiting_time / (float)num;

	printf("Average waiting time = %f\n", average_waiting_time);
	printf("Average turnaround time = %f\n", average_turnaround_time);
}

void sort(program *array, int num) {
	for (int i = 0; i < num - 1; i++) {
		for (int j = 0; j < num - i - 1; j++) {
			if (array[j].arrival_time > array[j + 1].arrival_time) {
				program temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

int remove_front_from_ready_queue(int *array, int *size) {
	int return_value = array[0];

	if (*size == 0) {
		*size = 0;
	}

	for (int i = 0; i < *size; i++) {
		array[i] = array[i + 1];
	}

	--*size;

	return return_value;
}

int isin(int *array, int size, int element) {
	for (int i =0; i <= size; i++) {
		if (array[i] == element) {
			return 1;
		}
	}

	return 0;
}