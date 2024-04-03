#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <time.h>
#include <glib.h>
#include "gui.h"

pcap_t *handle;
char errbuf[PCAP_ERRBUF_SIZE];
FILE *logfile;
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data) {
    FILE *logfile = (FILE *)param;
    int i;

    logfile = fopen("packet_log.txt", "a");

    if (logfile == NULL) {
        fprintf(stderr, "Failed to create log file.\n");
        return;
    }

    fprintf(logfile, "Packet Captured! Size: %d bytes\n", header->len);
    fprintf(logfile, "Arrival Time: %s", ctime((const time_t *)&header->ts.tv_sec));

    for (i = 0; i < header->len; i++) {
        fprintf(logfile, " %02x ", pkt_data[i]);
        if ((i + 1) % 16 == 0) fprintf(logfile, "\n");
    }
    fprintf(logfile, "\n\n");

    fclose(logfile);
}

int main() {
    logfile = fopen("packet_log.txt", "w");
    if (logfile == NULL) {
        fprintf(stderr, "Failed to create log file.\n");
        exit(1);
    }
    start_gui(logfile);
    handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Failed to capture network interface: %s\n", errbuf);
        exit(1);
    }
    pcap_loop(handle, 0, packet_handler, (u_char *)logfile);
    fclose(logfile);
    pcap_close(handle);
    return 0;
}