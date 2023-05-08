#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

typedef struct {
    uint8_t address[4];
} ip_address_t;

typedef struct {
    uint8_t mac_address[6];
} mac_address_t;

typedef struct {
    ip_address_t source_ip;
    ip_address_t dest_ip;
    uint16_t source_port;
    uint16_t dest_port;
} network_packet_t;

void send_packet(network_packet_t* packet);
void receive_packet(network_packet_t* packet);

#endif /* NETWORK_H */
