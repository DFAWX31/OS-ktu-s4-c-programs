#include <stdio.h>

int isin(int*, int, int);

struct process {
	int pid, allocated[3], maximum[3], needs[3], free[3];
};

void main() {
	struct process processes[50];
	int num;
	
	int free[3];
	
	printf("Enter the number of processes: ");
	scanf("%d", &num);
	
	for (int i = 0; i < num; i++) {
		processes[i].pid = i + 1;
		printf("Enter the number of A, B, C allocated to %d process: ", i + 1);
		scanf("%d %d %d", &processes[i].allocated[0], &processes[i].allocated[1], &processes[i].allocated[2]);
		
		printf("Enter the max A, B, C resources required for %d process: ", i + 1);
		scanf("%d %d %d", &processes[i].maximum[0], &processes[i].maximum[1], &processes[i].maximum[2]);
		
		for (int j = 0; j < 3; j++) {
			processes[i].needs[j] = processes[i].maximum[j] - processes[i].allocated[j];
		}
	}
	
	printf("Enter the number of A, B, C available at the start: ");
	scanf("%d %d %d", &free[0], &free[1], &free[2]);
	
	int arr[num], top = 0, pid = 0;
	
	while (top != num ) {

		if (isin(arr, top, pid) == 1 && free[0] >= processes[pid].needs[0] && free[1] >= processes[pid].needs[1] && free[2] >= processes[pid].needs[2]) {
			arr[top++] = pid;
			
			for (int i = 0; i < 3; i++) {
				free[i] += processes[pid].allocated[i];
				processes[pid].free[i] = free[i];
			}
			
		}
		pid = ( pid + 1 ) % num;
	}
	
	printf("pid\talloc\tmax\tneeds\tfree\n");
	
	for (int i = 0; i < num; i++) {
		printf("%d\t%d%d%d\t%d%d%d\t%d%d%d\t%d%d%d\n", processes[i].pid, processes[i].allocated[0], processes[i].allocated[1], processes[i].allocated[2], processes[i].maximum[0], processes[i].maximum[1], processes[i].maximum[2], processes[i].needs[0], processes[i].needs[1], processes[i].needs[2], processes[i].free[0], processes[i].free[1], processes[i].free[2]);
	}
}

int isin(int *arr, int size, int number) {
	if (size < 1) {
		return 1;
	}

	for (int i = 0; i < size; i++) {
		if (arr[i] == number) {
			return 0;
		}
	}
	return 1;
}
