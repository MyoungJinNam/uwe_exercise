#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAX_PACKET_SIZE 64

/*  return values of instrLoad  */
#define INVALID 0
#define VALID 1

bool authenticate(char * str);
extern void PacketRead(char * dest);
extern void ProcessPacket(char * pckt);

const char *legalport = "55000";

/*  malware corrupts local variables through a stack pointer. */
void malware()
{
    register void *sp asm ("sp");
    memset((char*)(sp+16), 1, 32);
    /*  If necessary, feel free to adjust arguments of memset 
        (the address and length) to overwrite 'authenticated'. */
}

/*  instrStore is instrumented right before memory write to ptr */
void instrStore (void* ptr, void* chkpoint)
{
    /*  TODO: Fill the function.  */
}

/*  instrLoad is instrumented right before memory read to ptr */
int instrLoad (void* ptr, void* chkpoint)
{
    int status = INVALID;
    /*  TODO: Fill the function: 
        if the result is valid, return 1; otherwise 0. */
    return status;
}

int main(int argc, char const *argv[])
{
    /*  TODO: create an argument of instrStore: 
              e.g. create a structure and pass a pointer to it,
              or pass NULL.  */
    int authenticated;
    instrStore(&authenticated, /* TODO: a pointer argument */);    
    authenticated = 0;   
    
    char packet[MAX_PACKET_SIZE]; 

    /*  TODO: Create an argument in the same way as instrStore above */ 
    printf ("0: %d\n", instrLoad(&authenticated, /* TODO */));
    
    while (1) {
        
        /*  Unsafe PacketRead function may overwrite return address 
            or local variables such as authenticated. 
            NOTE: the order of local variables on the stack is unspecified. */
        printf ("1: %d\n", instrLoad(&authenticated, /* TODO */)); 
        if (authenticated) {
            break;
        }

        instrStore(packet, /* TODO */); 
        PacketRead(packet); 
        
        /*  malware corrupts local variables. */
        malware();  
        
        printf("2: %d\n", instrLoad(packet, /* TODO */)); 
        /*  authenticated variable must be assigned 1, 
            only if authenticate(packet) returns 1,
            i.e. srcport equals to legalport. 
        */
        if (authenticate(packet)) {
            printf("3: %d\n", instrLoad(packet, /* TODO */)); 
            authenticated = 1;
        }
    }
    
    /*  A corrupted authenticated value can be used here 
        and changes control flow illegally. 
        In this example, although authenticated variable 
        has not been written non-zero legally, ProcessPacket is called. */
    printf("4: %d\n", instrLoad(&authenticated, /* TODO */)); 
    if (authenticated) {
        printf ("5: %d\n", instrLoad(packet, /* TODO */)); 
        ProcessPacket(packet);
    }

    return 0;
}

/*  if "Src port: 55000" is found, returns 1; otherwise returns 0.
    NOTE: DO NOT modify this function. */ 
bool authenticate(char * str)
{
    if (!strlen(str))   return 0;
    
    int status = 0;

    char * substr= "Src port: "; 
    char * ptr= strstr(str, substr);
    // pos is an index of substr in str 
    int pos = ptr - str;    
    pos = pos + strlen(substr); 

#define FIXED_LEN 5
    char srcport[FIXED_LEN];
    strncpy(srcport, &str[pos], FIXED_LEN); 
   
    if (!strcmp(srcport, legalport)) {
        status= 1;
    }
    else {
        // printf("! error: srcport is illegal.\n");
    }

    return status;
}

