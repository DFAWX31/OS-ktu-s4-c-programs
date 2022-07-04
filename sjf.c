#include <stdio.h>

typedef struct {
	int process_id, arrival_time, burst_time, waiting_time, turnaround_time;
} program;

void sort(program*, int);
void insert_into_ready_queue(int*, int*, int, program*);
int remove_front_from_ready_queue(int*, int*);
int isin(int*, int, int);

void main() {
	int num;

	printf("Enter the number of processes: ");
	scanf("%d", &num);

	program programs[num];

	for (int i = 0; i < num; i++) {
		programs[i].process_id = i + 1;

		printf("Enter the arrival time and burst time of process number %d: ", i + 1);
		scanf("%d %d", &programs[i].arrival_time, &programs[i].burst_time);
	}
	
	sort(programs, num);

	int ready_queue[num], ready_queue_size = -1;

	int done_stack[num], done_stack_top = -1;

	int pid = 0;

	insert_into_ready_queue(ready_queue, &ready_queue_size, pid, programs);

	pid = remove_front_from_ready_queue(ready_queue, &ready_queue_size);

	int time = programs[0].arrival_time;

	while (done_stack_top < num - 1) {
		programs[pid].waiting_time = time - programs[pid].arrival_time;

		programs[pid].turnaround_time = programs[pid].waiting_time + programs[pid].burst_time;

		time += programs[pid].burst_time;

		done_stack[++done_stack_top] = pid;

		if (done_stack_top < num - 1) {
			for (int i = 0; i < num; i++) {
				if (isin(done_stack, done_stack_top, i) == 0 && isin(ready_queue, ready_queue_size, i) == 0) {
					if (programs[i].arrival_time <= time) {
						insert_into_ready_queue(ready_queue, &ready_queue_size, i, programs);
					}
				}
			}
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


void insert_into_ready_queue(int *array, int *size, int element_number, program *programs) {
	if (*size < 0) {
		array[++*size] = element_number;
		return;
	}

	for (int i = 0; i <= *size; i++) {
		if (programs[array[i]].burst_time > programs[element_number].burst_time) {
			for (int j = *size; j >= i; j--) {
				array[j + 1] = array[j];
			}

			++*size;

			array[i] = element_number;
			
			return;
		}
	}

	array[++*size] = element_number;
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