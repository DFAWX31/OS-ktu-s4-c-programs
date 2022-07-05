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
		/*printf("Enter the number of B allocated to %d process: ", i + 1);
		scanf("%d", &processes[i].allocated[1]);
		printf("Enter the number of C allocated to %d process: ", i + 1);
		scanf("%d", &processes[i].allocated[2]);*/
		
		printf("Enter the max A, B, C resources required for %d process: ", i + 1);
		scanf("%d %d %d", &processes[i].maximum[0], &processes[i].maximum[1], &processes[i].maximum[2]);
		/*printf("Enter the max B resources required for %d process: ", i + 1);
		scanf("%d", &processes[i].maximum[1]);
		printf("Enter the max C resources required for %d process: ", i + 1);
		scanf("%d", &processes[i].maximum[2]);*/
		
		for (int j = 0; j < 3; j++) {
			processes[i].needs[j] = processes[i].maximum[j] - processes[i].allocated[j];
		}
	}
	
	/*processes[0].pid = 1;processes[1].pid = 2;processes[2].pid = 3;
	processes[0].allocated[0] = 1;processes[0].allocated[1] = 2;processes[0].allocated[2] = 1;
	processes[1].allocated[0] = 2;processes[1].allocated[1] = 0;processes[1].allocated[2] = 1;
	processes[2].allocated[0] = 2;processes[2].allocated[1] = 2;processes[2].allocated[2] = 1;
	processes[0].maximum[0] = 2;processes[0].maximum[1] = 2;processes[0].maximum[2] = 4;
	processes[1].maximum[0] = 2;processes[1].maximum[1] = 1;processes[1].maximum[2] = 3;
	processes[2].maximum[0] = 3;processes[2].maximum[1] = 4;processes[2].maximum[2] = 1;
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			processes[i].needs[j] = processes[i].maximum[j] - processes[i].allocated[j];
		}
	}*/
	
	/*char letters[3] = {'A', 'B', 'C'};
	
	for (int i = 0; i < 3; i++) {
		printf("Enter the number %c available at the start: ", letters[i]);
		scanf("%d", &free[i]);
	}*/
	
	printf("Enter the number of A, B, C available at the start: ");
	scanf("%d %d %d", &free[0], &free[1], &free[2]);
	
	int arr[num], top = 0, pid = 0;
	
	while (top != num ) {
	
		/*printf("%d\n", pid);
		printf("%d\t%d\t%d\n", processes[pid].needs[0], processes[pid].needs[1], processes[pid].needs[2]);
		printf("%d\t%d\t%d\n", free[0], free[1], free[2]);
		printf("%d\n", isin(arr, top, pid));
		printf("%d\n", top);*/
		
		if (isin(arr, top, pid) == 1 && free[0] >= processes[pid].needs[0] && free[1] >= processes[pid].needs[1] && free[2] >= processes[pid].needs[2]) {
			//printf("wiow");
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
