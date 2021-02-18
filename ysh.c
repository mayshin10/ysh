#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <assert.h> // for assert function

#define buf_size 128    // Max length of user input
#define max_args 8      // Max number of arguments per process

#define arg_name_size 16 // Maximum argument name size
#define max_commands 4 //Maximum number of (| or ;). So the actual max number of commands are 5.

// Read a shell input.
char* readcmd(char *buf) {
    // Read input from stdin.
    fprintf(stdout, "$ ");
    memset(buf, 0, buf_size);
    char *cmd = fgets(buf, buf_size, stdin);

    // Chop the tailing \n.
    cmd[strlen(cmd)-1] = 0;
    return cmd;
}

// Run a command.
int runcmd(char *cmd) {
    // Remove leading white space(s).
    while(*cmd == ' ') { cmd++; }

//My code starts

    // exit command: return -1 to terminate the while loop in main.
    if(!strncmp(cmd, "exit", 4)) { return -1; }
    else {
	//parsing the commands line from here to line 83.
	int num_semicolon=0, num_vertical=0; //count semicolon number and serial commands number.

	//count serial commands
	char *str_cpy1=(char*)malloc(sizeof(char)*buf_size);	//copy cmd
	strcpy(str_cpy1, cmd);
	while((str_cpy1=strchr(str_cpy1, '|')) != NULL){	//count in loop
		num_vertical++;
		str_cpy1++;		
	}

	//count pipe commands
	char *str_cpy2=(char*)malloc(sizeof(char)*buf_size);	//copy cmd
        strcpy(str_cpy2, cmd);
        while((str_cpy2=strchr(str_cpy2, ';')) != NULL){	//count in loop
                num_semicolon++;
                str_cpy2++;
        }

	//counting the each command and storing it in string array.
    	char *str_array[max_commands];
	char *ptr = strtok(cmd, "|;");	//tok by '|' or ';'
	int num_command = 0;
	while(ptr !=NULL){	//count the number of command
		str_array[num_command]=(char*)malloc(sizeof(char)*buf_size);
		strcpy(str_array[num_command],ptr);
		ptr = strtok(NULL, "|;");
		num_command++;       
	}
	
	//seperating from whole command line into a single command and arguments
	char *cmds[num_command][max_args];	//making the 2-dim string array pointer. it could be a 5 X 8 array.
	for(int j=0; j<num_command; j++){
		char *ptr = strtok(str_array[j], " ");	//tok by ' '
		int k = 0;	//number of arguments
		while(ptr !=NULL){
			cmds[j][k] = (char*)malloc(sizeof(char)*arg_name_size);	//assign the memory space to the 2D string array
			strcpy(cmds[j][k], ptr);
			ptr = strtok(NULL, " ");
			k ++;
		}
		while(k<max_args){
			cmds[j][k]=NULL;	//assign NUll point to blank space
			k++;
		}	
	}	//complete the parsing function from "cmd"


	//begin execution region
	int filedes_A[2];	//first pipeline
        int filedes_B[2];	//second pipeline
        assert(!pipe(filedes_A));	//connect first pipe
        assert(!pipe(filedes_B));	//connect second pipe

	//this loop is for serialization commands and pipe commands
	for(int x=0; x < num_command; x++){
		//'cd' command
                if(!strcmp(cmds[x][0], "cd")){
                	if(chdir(cmds[x][1]) < 0) { fprintf(stderr, "Cannot cd %s\n", cmds[x][1]); }}
		else {
			//fork the process
			int rc = fork();
			if(rc < 0) { fprintf(stderr, "fork() failed\n"); exit(1);}	//handle the fork error
        		
			//this is for parent
			else if(rc>0) {
				//handle the last loop
				if(x==num_command-1)
					close(filedes_B[1]);
				//handle the first loop
				if(x==0)
					close(filedes_A[1]);
				//wait until the child process ends	
				wait(NULL);
			}
			//this is for the child process
			else{
				//this is for the pipe commands
				if(num_vertical != 0){
					if(x==0){	// first command in pipe commands
						//Using only 'write' to first pipe and close all others
						dup2(filedes_A[1],1);
						close(filedes_A[0]);
						close(filedes_B[0]);
						close(filedes_B[1]);
					}
					else if((x!=0) && (x!=num_command-1)){	// neither the first nor the last command in pipe commands
                         			if(x%2==1){	//handling odd order one
							//Reading from fisrt pipe and Writing to second pipe.
							dup2(filedes_A[0],0);
                                			dup2(filedes_B[1],1);
							close(filedes_A[1]);
							close(filedes_B[0]);
						}
						else{		//handling even order one
							//Reading from second pipe and Writing to first pipe.
							dup2(filedes_B[0],0);
                                        		dup2(filedes_A[1],1);
                                        		close(filedes_B[1]);
                                        		close(filedes_A[0]);
				    		}
                        		}
					else if(x==num_command-1){	// last command in pipe commands
						if(x%2==0){	//handling even order one
							//Reading from second pipe and close all the others
                                        		dup2(filedes_B[0],0);
                                        		close(filedes_A[0]);
                                        		close(filedes_A[1]);
                                        		close(filedes_B[1]);
						}
                                        	else{		//handling odd order one
							//Reading from first pipe and close all the others
							dup2(filedes_A[0],0);
                                        		close(filedes_B[0]);
                                        		close(filedes_B[1]);
                                        		close(filedes_A[1]);
				       		}                                      
					}
				}
				//execution the single command with arguments
				if(execvp(cmds[x][0], cmds[x])==-1){
					fprintf(stdout, "command not found: %s\n", cmds[x][0]);	//error handling
				exit(0);	//if error occurs, exit the process
				}
			}
		}
	}
    }    
    return 0;
}

// My code ends

int main(void) {
    int fd = 0;
    char *cmd = 0;
    char buf[buf_size];

    // Ensure three file descriptors are open. Failure will hang the shell.
    while((fd = open("console", O_RDWR)) >= 0) {
        if(fd >= 3) { close(fd); break; }
    }

    fprintf(stdout, "EEE3535 Operating Systems: starting ysh\n");

    // Read and run input commands.
    while((cmd = readcmd(buf))) {
        // Run the input commands.
        if(*cmd && runcmd(cmd)) { break; }
    }
    return 0;
}

