/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rfidVisual.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 13 April 2019, 16:14
 */

#ifndef RFIDVISUAL_H
#define RFIDVISUAL_H

struct app_widgets {
    // All the widgets on the form go into here
    GtkWidget *w_txt_tag_id_pg0;
    GtkWidget *w_txt_view_page_block_info_pg0;    
    GtkWidget *w_radbut_tag_present_pg0;
    GtkWidget *w_txt_tag_id_pg1;
    GtkWidget *w_txt_view_page_block_info_pg1;
    GtkWidget *w_radbut_tag_present_pg1;
    GtkWidget *w_but_factory_reset;
    GtkWidget *w_txt_version_info_box;
    GtkTextBuffer *w_txt_version_info_box_tree_view;
    //GtkWidget *w_txt_version_info_box_tree_view;
    GtkWidget *w_txt_mode_box;
    // also the serial connection
    int        conn;
} ;



void open_serial_port(struct app_widgets *widget);

// calls the library and gets the version info
void get_version_info(struct app_widgets *widget) ;
void on_main_application_window_destroy() ;

// calls the library and gets the mode info
void get_mode_info(struct app_widgets *widget);

// called when the reset button is clicked
void on_btn_reset_clicked(GtkButton *button, struct app_widgets *widget);

#endif /* RFIDVISUAL_H */

