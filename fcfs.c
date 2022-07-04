#include <stdio.h>

struct program {
	int p_no, arrival_time, burst_time, waiting_time, turnaround_time;
};

typedef struct program program;

void sort(program*, int);

void main() {
	int num;

	printf("Enter the number of processes: ");
	scanf("%d", &num);

	program programs[num];

	for (int i = 0; i < num; i++) {
		programs[i].p_no = i + 1;

		printf("Enter the arrival time and burst time of process number %d: ", i + 1);
		scanf("%d %d", &programs[i].arrival_time, &programs[i].burst_time);
	}

	int time = 0;

	sort(programs, num);

	for (int i = 0; i < num; i++) {
		if (time < programs[i].arrival_time) {
			time = programs[i].arrival_time;
		}

		programs[i].waiting_time = time - programs[i].arrival_time;

		programs[i].turnaround_time = programs[i].waiting_time + programs[i].burst_time;

		time += programs[i].burst_time;
	}

	int total_waiting_time = 0, total_turnaround_time = 0;

	printf("pid\tat\tbt\twt\ttt\n");
	for (int i = 0; i < num; i++) {
		total_waiting_time += programs[i].waiting_time;
		total_turnaround_time += programs[i].turnaround_time;

		printf("%d\t%d\t%d\t%d\t%d\n", programs[i].p_no, programs[i].arrival_time, programs[i].burst_time, programs[i].waiting_time, programs[i].turnaround_time);
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