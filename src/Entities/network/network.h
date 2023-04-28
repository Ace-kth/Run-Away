#include <SDL_net.h>

typedef struct {
    UDPsocket sourcePort;
	IPaddress destination;
	UDPpacket *dataToSend1;
	UDPpacket *dataToSend2;
} Network;

Network setUpNetwork(char IP_address[], char port[]);