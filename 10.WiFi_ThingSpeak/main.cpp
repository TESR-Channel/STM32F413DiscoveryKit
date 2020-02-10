#include "mbed.h"
#include "TCPSocket.h"
#include <string>

WiFiInterface *wifi;

const char *sec2str(nsapi_security_t sec)
{
    switch (sec) {
        case NSAPI_SECURITY_NONE:
            return "None";
        case NSAPI_SECURITY_WEP:
            return "WEP";
        case NSAPI_SECURITY_WPA:
            return "WPA";
        case NSAPI_SECURITY_WPA2:
            return "WPA2";
        case NSAPI_SECURITY_WPA_WPA2:
            return "WPA/WPA2";
        case NSAPI_SECURITY_UNKNOWN:
        default:
            return "Unknown";
    }
}

int scan_demo(WiFiInterface *wifi)
{
    WiFiAccessPoint *ap;

    printf("Scan:\n");

    int count = wifi->scan(NULL,0);

    if (count <= 0) {
        printf("scan() failed with return value: %d\n", count);
        return 0;
    }

    /* Limit number of network arbitrary to 15 */
    count = count < 15 ? count : 15;

    ap = new WiFiAccessPoint[count];
    count = wifi->scan(ap, count);

    if (count <= 0) {
        printf("scan() failed with return value: %d\n", count);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        printf("Network: %s secured: %s BSSID: %hhX:%hhX:%hhX:%hhx:%hhx:%hhx RSSI: %hhd Ch: %hhd\n", ap[i].get_ssid(),
               sec2str(ap[i].get_security()), ap[i].get_bssid()[0], ap[i].get_bssid()[1], ap[i].get_bssid()[2],
               ap[i].get_bssid()[3], ap[i].get_bssid()[4], ap[i].get_bssid()[5], ap[i].get_rssi(), ap[i].get_channel());
    }
    printf("%d networks available.\n", count);

    delete[] ap;
    return count;
}

void Update_Data_to_ThingSpeak(NetworkInterface *net)
{
    TCPSocket socket;
    nsapi_error_t response;
    char server_thingSpeakAddress[] = "api.thingspeak.com";
    int server_port = 80;
    string ThingSpeak_writeAPIKey = "L4YDG032PSX1ROXX";

    printf("Sending HTTP request Write data to %s\n",server_thingSpeakAddress);

    // Open a socket on the network interface, and create a TCP connection to www.arm.com
    socket.open(net);
    response = socket.connect(server_thingSpeakAddress, server_port);
    if(0 != response) {
        printf("Error connecting: %d\n", response);
        socket.close();
        return;
    }

    // Send a simple http request
    string message;
    message += ThingSpeak_writeAPIKey;
    message += "&field1=";
    message += to_string(rand() % 100 + 1);
    message += "&field2=";
    message += to_string(rand() % 100 + 1);
    message += "\r\n\r\n";

    string req = "";
    //req = "GET https://api.thingspeak.com/update?api_key="+ThingSpeak_writeAPIKey + message + "\r\n\r\n";
    
    req += "POST /update HTTP/1.1\r\n";
    req += "Host: api.thingspeak.com\r\n";
    req += "Connection: close\r\n";
    req += "X-THINGSPEAKAPIKEY: "+ ThingSpeak_writeAPIKey +"\r\n";
    req += "Content-Type: application/x-www-form-urlencoded\r\n";
    req += "Content-Length:" + to_string(message.length()) +"\r\n";
    req += "\r\n";
    req += message;
    

    nsapi_size_t size = req.length();
  
    // declaring character array 
    char req_char_array[size + 1]; 
  
    // copying the contents of the 
    // string to char array 
    strcpy(req_char_array, req.c_str()); 
    printf("%s\r\n",req_char_array);
    response = 0;
    while(size)
    {
        response = socket.send(req_char_array, size);
        if (response < 0) 
        {
            printf("Error sending data: %d\n", response);
            socket.close();
            return;
        } 
        else 
        {
            size -= response;
            // Check if entire message was sent or not
            printf("sent %d [%.*s]\n", response, strstr(req_char_array, "\r\n")-req_char_array, req_char_array);
        }
    }

    // Recieve a simple http response and print out the response line
    char rbuffer[64];
    response = socket.recv(rbuffer, sizeof rbuffer);
    if (response < 0) 
    {
        printf("Error receiving data: %d\n", response);
    } 
    else 
    {
        printf("recv %d [%.*s]\n", response, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);
    }

    // Close the socket to return its memory and bring down the network interface
    socket.close();
}

int main()
{
    printf("WiFi ThingSpeak example\n");

    #ifdef MBED_MAJOR_VERSION
        printf("Mbed OS version %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    #endif

    wifi = WiFiInterface::get_default_instance();
    if (!wifi) 
    {
        printf("ERROR: No WiFiInterface found.\n");
        return -1;
    }

    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    int ret = wifi->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) 
    {
        printf("\nConnection error: %d\n", ret);
        return -1;
    }

    printf("Success\n\n");
    printf("MAC: %s\n", wifi->get_mac_address());
    printf("IP: %s\n", wifi->get_ip_address());
    printf("Netmask: %s\n", wifi->get_netmask());
    printf("Gateway: %s\n", wifi->get_gateway());
    printf("RSSI: %d\n\n", wifi->get_rssi());

    Update_Data_to_ThingSpeak(wifi);

    wifi->disconnect();

    printf("\nDone\n");
}
