// How to read a packet capture file.
//Group Id: 21
//Group Name: The Dexters
 

//Preprocessor Directives...
#include <string>
#include <iostream>
#include "pcap.h"
 
//using namespace std;
 
//main function... 
int main(int argc, char *argv[])
{
    
    //Get a file name...
    char file[] = "./bgp.pcap";
 

    //Create an char array to hold the error...
     char errbuff[PCAP_ERRBUF_SIZE];
 
    
    //Opening the file and store result in pointer to pcap_t
    // Use pcap_open_offline
    pcap_t * pcap = pcap_open_offline(file, errbuff);
 
    //Create a header and a data object...
    struct pcap_pkthdr *header;
 
    // Create a character array using a u_char
    // u_char is defined here:
    const u_char *data;
 
    //Loop through packets and print them to screen
    u_int packetCount = 0;
    while (int returnValue = pcap_next_ex(pcap, &header, &data) >= 0)
    {
      
        // Show the packet number
        printf("Packet # %i\n", ++packetCount);
 
        // Show the size in bytes of the packet
        printf("Packet size: %d bytes\n", header->len);
 
        // Show a warning if the length captured is different
        if (header->len != header->caplen)
            printf("Warning! Capture size different than packet size: %d bytes\n", header->len);
 
        // Show Epoch Time
        printf("Epoch Time: %ld:%ld seconds\n", header->ts.tv_sec, header->ts.tv_usec);
 
        // loop through the packet and print it as hexidecimal representations of octets
        for (u_int i=0; (i < header->caplen ) ; i++)
        {
             if ( (i % 16) == 0) printf("\n");
 
             printf("%.2x ", data[i]);
        }
 
        // Add two lines between packets
        printf("\n\n");
    }
}
