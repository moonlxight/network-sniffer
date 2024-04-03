#include <gtk/gtk.h>
#include <pcap.h> // pcap kütüphanesini içeri aktar
#include <errno.h> // errno.h başlık dosyasını ekledik
#include <string.h> // strerror fonksiyonu için
extern pcap_t *handle;
extern char errbuf[];
void toggle_sniffer(GtkWidget *widget, gpointer data) {
    pcap_dumper_t *pcap_dump_file;
    char pcap_errbuf[PCAP_ERRBUF_SIZE];
    FILE *logfile = (FILE *)data;
    
    if (handle == NULL) {
        handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);
        if (handle == NULL) {
            g_print("Couldn't open device %s: %s\n", "eth0", errbuf);
            return;
        }
        pcap_dump_file = pcap_dump_open(handle, "packet_log.pcap");
        if (pcap_dump_file == NULL) {
            g_print("Couldn't open packet log file: %s\n", strerror(errno));
            return;
        }
        g_print("Packet capturing started.\n");
    } else {
        pcap_close(handle);
        handle = NULL;
        g_print("Packet capturing stopped.\n");
    }
}

void clear_log(GtkWidget *widget, gpointer data) {
    FILE *logfile = (FILE *)data;
    fclose(logfile);
    logfile = fopen("packet_log.txt", "w");
    if (logfile == NULL) {
        g_print("Log file couldn't be cleared. The file might appear empty.\n");
        return;
    }
    fclose(logfile);
    g_print("Log file cleared.\n");
}
void start_gui(FILE *log) {
    GtkWidget *window;
    GtkWidget *start_button;
    GtkWidget *stop_button;
    GtkWidget *clear_button;
    GtkWidget *vbox;
    gtk_init(NULL, NULL);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Network Sniffer");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    start_button = gtk_button_new_with_label("Start");
    g_signal_connect(start_button, "clicked", G_CALLBACK(toggle_sniffer), (gpointer)log);
    gtk_box_pack_start(GTK_BOX(vbox), start_button, TRUE, TRUE, 0);
    stop_button = gtk_button_new_with_label("Stop");
    g_signal_connect(stop_button, "clicked", G_CALLBACK(toggle_sniffer), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), stop_button, TRUE, TRUE, 0);
    clear_button = gtk_button_new_with_label("Clear Log");
    g_signal_connect(clear_button, "clicked", G_CALLBACK(clear_log), (gpointer)log);
    gtk_box_pack_start(GTK_BOX(vbox), clear_button, TRUE, TRUE, 0);
    gtk_widget_show_all(window);
    gtk_main();
}
