
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//Leslie McCarthy DNET 3
#define DEBUG 0

int MAXFUEL = 100;
int fuelLevel = 100;

void handler(int sig){
    
    
    if (sig == SIGUSR2){       
        
    #ifdef DEBUG 
        printf("Message: From SIGUSR2 Max fuel is set to full Process ID: %d\n", getpid());
    #endif
        
    }
    
    else if (sig == SIGALRM){
      
    #ifdef DEBUG
        printf("\nMessage: From SIGALRM Fuel is dropping: Process ID: %d\n", getpid());
    #endif
        
        if (fuelLevel == 0){
    #ifdef DEBUG
           printf("PLANE:Child %d\n exiting shortly \n", getpid());
    #endif
            sleep(1);
            exit(0);
        }       
        else{
            
            if(fuelLevel < 30){            
             kill(getppid(),SIGUSR1);//Low fuel signal to parent.
             
            #ifdef DEBUG
                printf("Message: to Parent fuel level below 30 gallons. Parent ID: %d\n\n", getppid());
            #endif       
        
            } 
            
            fuelLevel -= 10;
            #ifdef DEBUG
                printf("Message: Fuel Remaining %d Gallons Parent ID: %d\n",fuelLevel, getppid());
            #endif
        }  
    
    
    }
alarm(3);
    
}

int main(){
    signal(SIGUSR2, handler);// refuel signal
    
    signal(SIGALRM, handler);// update fuel
    
#ifdef DEBUG
    printf("Plane: Started %d\n", getpid());
#endif
    
    alarm(3);
    
    while(1){        
        sleep(10);
        
    }
    
    return 0;
    
}
