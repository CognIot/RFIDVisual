/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rfidVisual.c
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


//ToDo: Mode in the Mode Box needs to be centralised and smaller, allowing version to be wider.
//ToDo: Mode selection pictures needs to include words, and have only 1 selected, not all 3!
//ToDo: How do I all the user to set the value for polling delay?

/*
 * function to open and configure the serial port
 */

int open_serial_port( struct app_widgets *widget) {
    
	int		status = 1;
    // Open the serial port
    
    status = setupComms(&widget->conn);
	printf("Opened the serial port:%d\n", widget->conn);
    
    return status;
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

void on_menu_file_connect(struct app_widgets *widget) {
    printf("In On Menu File connect\n");
    
	open_serial_port(widget);
    get_version_info(widget);
	get_mode_info(widget);
}

void on_btn_reset_clicked(GtkButton *button, struct app_widgets *widget) {
	
	int			status;
    printf("Reset button has been clicked\n");
	
	status = resetReader(widget->conn);
	
	if (status ==0 ) {
		printf("Factory Reset Complete\n");
	}
	else {
		printf("Factory Reset failed\n");
	}
	
	return;
}

void on_radiobutton_toggled(GtkButton *button, struct app_widgets *widget) {
	
	char			mode;
	mode = '\0';
    printf("Radiobuttons for mode has changed\n");
	
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_mode_a_pg2))) {
        printf("Mode a selected\n");
		mode = 'A';
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_mode_b_pg2))) {
        printf("Mode b selected\n");
		mode = 'B';
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_mode_c_pg2))) {
        printf("Mode C selected\n");
		mode = 'C';
    }
	
	setReaderMode(widget->conn, mode);
	return;
}

void get_version_info(struct app_widgets *widget) {

    char            version[101];
    int				count = 0;
	int				response = 1;
	GtkTextBuffer	*buffer;
	
	version[0] = '\0';
    
    do {
		response = readVersion(widget->conn, version, MAX_FIRMWARE_LENGTH);
        
        printf("size of Version: %d\n", sizeof(version)/sizeof(version[0]));        // returns 100
        count ++;

    } while  ((count < 5) && (response != EXIT_SUCCESS));
    
    if (response == EXIT_SUCCESS) {
        printf("status is zero\n");
		// Get and then set the buffer
		buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (widget->w_txt_version_info_box));
		printf("Got the buffer\n");
		gtk_text_buffer_set_text(buffer, version, -1);
        printf("set the text\n");

    }
    
    return;
}

void get_mode_info(struct app_widgets *widget) {

    char            mode[1];
    int				count = 0;
    int             connection;
	int				response = EXIT_FAILURE;
	
	mode[0] = '\0';
    
    connection = widget->conn;
    do {
        response = readMode(connection, mode);
        
        printf("Mode Information: >>%s<<\n", mode);
        count ++;

    } while  ((count < 5) && (response != EXIT_SUCCESS));
    
    if (response == EXIT_SUCCESS) {
        gtk_entry_set_text(GTK_ENTRY(widget->w_txt_mode_box), mode);
                            
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
	
	//Bug: If the application is run from the build directory, it doesn't find the glade file.
	//		 Does this mean that the XML file is not incorporated into the executable??
    
    // check if the GUI has opened.
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
	widgets->w_radbut_mode_a_pg2 = GTK_WIDGET(gtk_builder_get_object(builder, "radbut_mode_a_pg2"));
	widgets->w_radbut_mode_b_pg2 = GTK_WIDGET(gtk_builder_get_object(builder, "radbut_mode_b_pg2"));
	widgets->w_radbut_mode_c_pg2 = GTK_WIDGET(gtk_builder_get_object(builder, "radbut_mode_c_pg2"));
    widgets->w_but_factory_reset  = GTK_WIDGET(gtk_builder_get_object(builder, "but_factory_reset"));
    widgets->w_txt_version_info_box  = GTK_WIDGET(gtk_builder_get_object(builder, "txt_version_info_box"));
    widgets->w_txt_mode_box  = GTK_WIDGET(gtk_builder_get_object(builder, "txt_mode_box"));
    
    // connect the widgets to the signal handler
    gtk_builder_connect_signals(builder, widgets);    // note: second parameter points to widgets
    g_object_unref(builder);
    
    // Set the status of the various boxes etc.
	//ToDo: need to set the txt_version_info box to not editable.
    //gtk_text_view_set_editable(GtkTextView (widgets->w_txt_version_info_box), FALSE);
    
	// ToDo: need to get this to try and if fail, report to the user. Maybe have it only run by the menu item rather than automatic.
    on_menu_file_connect(widgets);

    
    gtk_widget_show(window);                
    gtk_main();
    // free up memory used by widget structure, probably not necessary as OS will
    // reclaim memory from application after it exits
    g_slice_free(struct app_widgets, widgets);
    
    return (EXIT_SUCCESS);
}
