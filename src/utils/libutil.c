#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int read_line(FILE *in, char *buffer, size_t max)
{
  return fgets(buffer, max, in) == buffer;
}

void PacketRead(char * dest)
{
    FILE *filein;

    if ((filein = fopen("foo.txt", "rt")) != NULL) {
        char line[256];

        if(read_line(filein, line, sizeof line)) {
            strcpy(dest, line);
        }
        else {
           // printf("read error\n");
        }
        fclose(filein);
    }
}

void ProcessPacket(char * pckt)
{
    printf("Processsing Packet...\n");

}


