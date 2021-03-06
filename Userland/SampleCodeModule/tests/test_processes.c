// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "test_processes.h"

//TO BE INCLUDED
void endless_loop_proc(){
  while(1);
}

uint32_t my_create_process_proc(char * name){
  char * argv[] = {name};
  return sys_loadProcess(&endless_loop_proc,1, argv,0,0);
  
}

uint32_t my_kill_proc(uint32_t pid){
  return kill(pid);
  
}

uint32_t my_block_proc(uint32_t pid){
  return block(pid);
}

uint32_t my_unblock_proc(uint32_t pid){
  return unblock(pid);

}

#define PROCESSES 51//Should be around 80% of the the processes handled by the kernel  | 80% of 64 is aprox 51
#define MAX_PROCESSES 64 //only run once per shell to add Maximum amount of processes.

enum State { RUNNING, BLOCKED, KILLED};

typedef struct P_rq{
  uint32_t pid;
  enum State state;
}p_rq;

void test_processes(){
  p_rq p_rqs[MAX_PROCESSES];
  uint8_t rq;
  uint8_t alive = 0;
  uint8_t action;
  int error;
  int initialProcessCount =  syscall(PROCESS_COUNT, 0,0,0,0,0,0);
  int maxProcesses = PROCESSES + initialProcessCount;

  if(maxProcesses > MAX_PROCESSES){
    substractLine();
    addText("You can only execute this test once. Restart Qemu");
    substractLine();
    printWindow();
    return;
  }
    addText("Creating processes");
    substractLine();
    printWindow();
    // Create MAX_PROCESSES processes
    for(rq = initialProcessCount; rq < maxProcesses; rq++){
      error = my_create_process_proc("proc_loop");
      if(error == -1 ){
        addText("Error creating process");
        substractLine();
        printWindow();            
      }
      else{
        p_rqs[rq].pid = rq;
        p_rqs[rq].state = RUNNING;
        alive++;
      }
      
    }
    addText("Randomly killing, blocking and unblocking processes");
    substractLine();
    printWindow();
    // Randomly kills, blocks or unblocks processes until every one has been killed exclude shell for demonstration purposes
    while (alive > 0){

      for(rq = initialProcessCount; rq < maxProcesses; rq++){
        action = GetUniform(2) % 2; 

        switch(action){
          case 0:
            if (p_rqs[rq].state == RUNNING || p_rqs[rq].state == BLOCKED){
              if (my_kill_proc(p_rqs[rq].pid) == -1){          // TODO: Port this as required
                addText("Error killing process");  
                substractLine();
                printWindow();         // TODO: Port this as required
              }else{
                   p_rqs[rq].state = KILLED; 
                  alive--;
              }
             
            }
            break;

          case 1:
            if (p_rqs[rq].state == RUNNING){
              if(my_block_proc(p_rqs[rq].pid) == -1){          
                addText("Error blocking process");
                substractLine();
                printWindow();          
              }else{
                p_rqs[rq].state = BLOCKED; 
              }
             
            }
            break;
        }
      }

      // Randomly unblocks processes exclude shell for demonstration purposes
      for(rq = initialProcessCount; rq < maxProcesses; rq++)
        if (p_rqs[rq].state == BLOCKED && GetUniform(2) % 2){
          if(my_unblock_proc(p_rqs[rq].pid) == -1){            
            addText("Error unblocking process");  
            substractLine();
            printWindow();         
          }
          else{
            p_rqs[rq].state = RUNNING; 
          }
        }
    } 
 
  addText("ProcessTest OK");
  substractLine();
  printWindow();
}

