#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[100]) {
    if (argc <= 1) {			 
        fprintf(stderr, "%s debe digitar un texto. \n", argv[0]);
        exit(1);
    }
	int cantidadHijos = atoi(argv[1]);

    int fd[2];
    pid_t pidC;
    char buffer[100];
    int numB;
    
    pipe(fd);
    pidC = fork();
    
    switch(pidC){
    	
    	case 0:
    		close(fd[0]);
    		write(fd[1], argv, 100);
    		close(fd[1]);
    		exit(0);
    		break;
    		
    	case -1:
    		break;
    		
    	default:
    		close(fd[1]);
    		numB = read(fd[0], buffer, sizeof(buffer));
    		printf("El texto a compartir es: %s", buffer);
    		close(fd[0]);
    		break;
    		
	}


    return 0;
}
