/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 30 March 2019, 09:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk-3.0/gtk/gtk.h>

#include "rfidVisual.h"
#include "lib_rfid/inc/rfid.h"

/*
 * function to open and configure the serial port
 */

void open_serial_port( struct app_widgets *widget) {
    
    // Open the serial port
    printf("opened a serial port\n");
    
    widget->conn = 1;               // set the serial port
    return;
}

/*
 * Functions called by GUI
 */

// called when window is closed
void on_main_application_window_destroy() {
    printf("In on window main destroy\n");
    gtk_main_quit();
    
    exit(0);
}

void on_menu_file_connect() {
    printf("In On Menu File connect");
    
}

/*
 * functions called locally
 */

// calls the library and gets the version info
void get_version_info(struct app_widgets *widget) {

    int             *version;
    int                     status = 1;
    int                     count = 0;
    int             connection;
    
    connection = widget->conn;
    do {
        status = readVersion(connection, version);
        printf("Status: %d\n", status);
        //printf("Version: %d\n", *version);
        count ++;
    } while  ((count < 5) & (status != 0));
    
    //sprintf(widget->w_txt_version_info_box, "%s", version);               //this line causes a segmentation fault
    
    // widget->w_txt_version_info_box = "done";             //this line causes a segmentation fault
    if (status == 0) {
        printf("status is zero\n");
        gtk_entry_set_text(GTK_ENTRY(widget->w_txt_version_info_box), "hello box"); //*version);
                            
        printf("set the text\n");

    }
    
    return;
}


/*
 * 
 */
int main(int argc, char** argv) {
    
    GtkBuilder      *builder; 
    GtkWidget       *window;
    
    GError                  *err = NULL;    // holds any error that occurs within GTK
    
    // instantiate structure, allocating memory for it
    struct app_widgets	*widgets = g_slice_new(struct app_widgets);
    
    // initialise GTK library and pass it in command line parameters
    gtk_init(&argc, &argv);

    // build the gui
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "gui/main_window.glade", &err);
    
    // check if the gui has opened.
    if (err != NULL) {
	fprintf (stderr, "Unable to read file: %s\n", err->message);
	g_error_free(err);
	return 1;
    }
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_application_window"));
    
    // build the structure of widget pointers
    widgets->w_txt_tag_id_pg0  = GTK_WIDGET(gtk_builder_get_object(builder, "txt_tag_id_pg0"));
    widgets->w_txt_view_page_block_info_pg0  = GTK_WIDGET(gtk_builder_get_object(builder, "txt_view_page_block_info_pg01"));
    widgets->w_radbut_tag_present_pg0  = GTK_WIDGET(gtk_builder_get_object(builder, "radbut_tag_present_pg0"));
    widgets->w_txt_tag_id_pg1  = GTK_WIDGET(gtk_builder_get_object(builder, "txt_tag_id_pg1"));
    widgets->w_txt_view_page_block_info_pg1  = GTK_WIDGET(gtk_builder_get_object(builder, "txt_view_page_block_info_pg1"));
    widgets->w_radbut_tag_present_pg1  = GTK_WIDGET(gtk_builder_get_object(builder, "radbut_tag_present_pg1"));
    widgets->w_but_factory_reset  = GTK_WIDGET(gtk_builder_get_object(builder, "but_factory_reset"));
    widgets->w_txt_version_info_box  = GTK_WIDGET(gtk_builder_get_object(builder, "txt_version_info_box"));
    widgets->w_txt_mode_box  = GTK_WIDGET(gtk_builder_get_object(builder, "txt_mode_box"));
    
    // connect the widgets to the signal handler
    gtk_builder_connect_signals(builder, widgets);    // note: second parameter points to widgets
    g_object_unref(builder);
    
    // Set the status of the various boxes etc.
    gtk_editable_set_editable(GTK_ENTRY (widgets->w_txt_version_info_box), FALSE);
    
    open_serial_port(widgets);
    printf("port opened\n");
    get_version_info(widgets);
    
    gtk_widget_show(window);                
    gtk_main();
    // free up memory used by widget structure, probably not necessary as OS will
    // reclaim memory from application after it exits
    g_slice_free(struct app_widgets, widgets);
    
    return (EXIT_SUCCESS);
}
