#include <WiFi101.h>

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):

void retrieve_time(WiFiClient &client, char* Cdate, char* Ctime);

void retrieve_temp(WiFiClient &client, int &temp);

void retrieve_standing(WiFiSSLClient client, bool &standing, int &standing_time);

void time_to_hm(char* Ctime, int &hr, int &mn);

void hm_to_time(char* Ctime, int hr, int mn);
