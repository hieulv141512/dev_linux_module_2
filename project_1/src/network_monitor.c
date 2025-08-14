#include "../inc/network_monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/net.h>


void get_ip_address(char *ip_address, size_t len) {
    FILE *fp = popen("hostname -I", "r");
    if (fp) {
        if (fgets(ip_address, len, fp) != NULL) {
            ip_address[strcspn(ip_address, "\n")] = 0;
        }
        pclose(fp);
    } else {
        strcpy(ip_address, "N/A");
    }
}

uint64_t get_num_connections() {
    FILE *fp = popen("netstat -nt | grep -c ESTABLISHED", "r");
    if (!fp) return 0;
    
    uint64_t count = 0;
    fscanf(fp, "%lu", &count);
    pclose(fp);
    return count;
}

void get_network_speed(float *download_kbps, float *upload_kbps) {
    FILE *fp = fopen("/proc/net/dev", "r");
    if (!fp) {
        *download_kbps = 0.0;
        *upload_kbps = 0.0;
        return;
    }
    
    char line[256];
    unsigned long long rx_bytes1 = 0, tx_bytes1 = 0;
    unsigned long long rx_bytes2 = 0, tx_bytes2 = 0;

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);
    
    while (fgets(line, sizeof(line), fp)) {
        unsigned long long rx_temp, tx_temp;
        char iface[32];
        sscanf(line, " %s %llu %*u %*u %*u %*u %*u %*u %*u %llu",
               iface, &rx_temp, &tx_temp);
        if (strcmp(iface, "lo:") != 0) {
            rx_bytes1 += rx_temp;
            tx_bytes1 += tx_temp;
        }
    }
    fclose(fp);
    
    sleep(1);
    
    fp = fopen("/proc/net/dev", "r");
    if (!fp) return;
    
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);
    
    while (fgets(line, sizeof(line), fp)) {
        unsigned long long rx_temp, tx_temp;
        char iface[32];
        sscanf(line, " %s %llu %*u %*u %*u %*u %*u %*u %*u %llu",
               iface, &rx_temp, &tx_temp);
        if (strcmp(iface, "lo:") != 0) {
            rx_bytes2 += rx_temp;
            tx_bytes2 += tx_temp;
        }
    }
    fclose(fp);
    
    *download_kbps = (float)((rx_bytes2 - rx_bytes1) * 8 / 1024.0);
    *upload_kbps = (float)((tx_bytes2 - tx_bytes1) * 8 / 1024.0);
}

NetworkStats* get_network_stats() {
    NetworkStats *stats = (NetworkStats*)malloc(sizeof(NetworkStats));
    if (stats == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for stats instance.\n");
        return NULL;
    }
    
    get_ip_address(stats->ip_address, IP_ADDRESS_LEN);
    stats->num_connection = get_num_connections();
    get_network_speed(&stats->current_download_speed_kbps, &stats->current_upload_speed_kbps);
    
    return stats;
}

void free_network_stats(NetworkStats *stats) {
    if (stats) {
        free(stats);
    }
}