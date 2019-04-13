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

#include <gtk-3.0/gtk/gtk.h>

#include "rfidVisual.h"

typedef struct {
	// All the widgets on the form go into here
	GtkWidget *w_txt_tag_id_pg0;
	GtkWidget *w_txt_view_page_block_info_pg0;    
	GtkWidget *w_radbut_tag_present_pg0;
	GtkWidget *w_txt_tag_id_pg1;
	GtkWidget *w_txt_view_page_block_info_pg1;
	GtkWidget *w_radbut_tag_present_pg1;
	GtkWidget *w_but_factory_reset;
	GtkWidget *w_txt_version_info_box;
	GtkWidget *w_txt_mode_box;
} app_widgets;


// called when window is closed
void on_main_application_window_destroy()
{
    printf("In on window main destroy\n");
    gtk_main_quit();
    
    exit(0);
}



/*
 * 
 */
int main(int argc, char** argv) {
	
	GtkBuilder      *builder; 
    GtkWidget       *window;
	
	GError			*err = NULL;	// holds any error that occurs within GTK
	
    // instantiate structure, allocating memory for it
    app_widgets        *widgets = g_slice_new(app_widgets);
	
	// initialize GTK library and pass it in command line parameters
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
	
    gtk_widget_show(window);                
    gtk_main();
    // free up memory used by widget structure, probably not necessary as OS will
    // reclaim memory from application after it exits
    g_slice_free(app_widgets, widgets);
	
	return (EXIT_SUCCESS);
}

