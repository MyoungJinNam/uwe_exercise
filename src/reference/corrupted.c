#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>

bool authenticate(char * str);
extern void PacketRead(char * dest);
extern void ProcessPacket(char * pckt);

const char *legalport = "55000";

/* 
    malware corrupts local variables through a stack pointer.  
*/
void malware()
{
    register void *sp asm ("sp");
    memset((char*)(sp+16), 1, 32);
    /*  If necessary, feel free to adjust arguments of memset 
        (the address and length) to overwrite 'authenticated'. */
}

int main(int argc, char const *argv[])
{
    int authenticated = 0;   
#define MAX_PACKET_SIZE 64 
    char packet[MAX_PACKET_SIZE]; 
    
    //while (!authenticated) {
    while (1) {
        if (authenticated) {
            break;
        }
        /*  Unsafe PacketRead function may overwrite return address 
            or local variables such as authenticated. 
            NOTE: the order of local variables on the stack is unspecified. */
        PacketRead(packet); 
        
        /*  malware corrupts local variables. */
        malware();  
        
        /*  authenticated variable must be assigned 1, 
            only if authenticate(packet) returns 1,
            i.e. srcport equals to legalport. 
        */
        if (authenticate(packet)) {
            authenticated = 1;
        }
    }
    
    /*  A corrupted authenticated value can be used here 
        and changes control flow illegally. 
        In this example, although authenticated variable 
        has not been written non-zero legally, ProcessPacket is called. */
    if (authenticated) {
        ProcessPacket(packet);
    }

    return 0;

}

/*  if "Src port: 55000" is found, returns 1; otherwise returns 0 */ 
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

