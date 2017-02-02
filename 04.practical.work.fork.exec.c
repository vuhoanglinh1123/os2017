//Vu Hoang Linh
//BI6-086

#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Main before fork()\n");
	
	int pid_1 = fork();											//First fork()

	printf("\npid = %d\n", pid_1);

	if (pid_1 == 0) {											//Child no.1
																
		int pid_2 = fork();										//Second fork() inside Child no.1

		printf("\npid = %d\n", pid_2);

		if (pid_2 == 0) {										//Child no.2

			printf("\nLaunching free -h\n");					//Executing the second command
			char *args[] = {"/usr/bin/free","-h",NULL};
			execvp("/usr/bin/free",args);
		}
		else {													//Parent no.2 inside Child no.1	
			printf("Parent of Child with PID = %d\n",pid_2);
		}

		printf("\nLaunching ps -ef\n");							//Executing the first command
		char *args[] = {"/bin/ps","-ef",NULL};
		execvp("/bin/ps",args);
	}
	else {														//Parent no.1
		printf("Parent of Child with PID = %d\n", pid_1);
	}

	return 0;
}
//ps -ef
//free -h