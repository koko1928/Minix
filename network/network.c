#include <stdint.h>
#include <stddef.h>
#include "network.h"

static uint8_t tx_buffer[NETWORK_BUFFER_SIZE];
static uint8_t rx_buffer[NETWORK_BUFFER_SIZE];

void network_init() {
    // ネットワークデバイスの初期化
}

void network_send_packet(uint8_t *packet, size_t size, uint32_t dest_ip) {
    // パケットを送信する
}

void network_handle_packet(uint8_t *packet, size_t size) {
    // パケットを受信してハンドルする
}

void network_poll() {
    // ネットワークドライバのポーリング処理
}

