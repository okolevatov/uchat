#include "../inc/uchat.h"

static void design_css(t_widget_my *widge) {
    gtk_widget_set_name(widge->send_button, "send_button");
    gtk_widget_set_name(widge->list_box, "list_box");
    gtk_widget_set_name(widge->return_sign_in, "return_sign_in");
    gtk_widget_set_name(widge->command_line, "command_line");
    gtk_widget_set_name(widge->who_writing, "who_writing");
    gtk_widget_set_name(widge->theme_1, "theme_1");
    gtk_widget_set_name(widge->theme_2, "theme_2");
    gtk_widget_set_name(widge->theme_3, "theme_3");
    gtk_widget_set_name(widge->theme_4, "theme_4");
    gtk_widget_set_name(widge->theme_5, "theme_5");
    gtk_widget_set_name(widge->theme_6, "theme_6");
    gtk_widget_set_name(widge->win_sett, "win_sett");
    gtk_widget_set_name(widge->scrolled, "scrolled");
    gtk_widget_set_name(widge->choose_user, "choose_user");
    gtk_widget_set_name(widge->friends, "friends_listbox");
}

void relieff_set(t_widget_my *widge) {
    gtk_button_set_relief(GTK_BUTTON(widge->who_writing), GTK_RELIEF_NONE);
}

void mx_create_widge(t_widget_my *widge) {
    widge->window = GTK_WIDGET(gtk_builder_get_object (widge->builder, "window"));

    widge->win_sign = GTK_WIDGET(gtk_builder_get_object (widge->builder, "win_sign"));
    widge->win_reg = GTK_WIDGET(gtk_builder_get_object (widge->builder, "win_reg"));
    widge->win_sett = GTK_WIDGET(gtk_builder_get_object (widge->builder, "win_sett"));

    widge->sign_in = GTK_WIDGET(gtk_builder_get_object (widge->builder, "sign_in"));
    widge->sign_up = GTK_WIDGET(gtk_builder_get_object (widge->builder, "sign_up"));

    widge->user_name = GTK_WIDGET(gtk_builder_get_object (widge->builder, "user_name"));
    widge->user_password = GTK_WIDGET(gtk_builder_get_object (widge->builder, "user_password"));

    widge->create_user_name = GTK_WIDGET(gtk_builder_get_object (widge->builder, "create_user_name"));
    widge->create_user_password = GTK_WIDGET(gtk_builder_get_object (widge->builder, "create_user_password"));
    widge->repeat_user_password = GTK_WIDGET(gtk_builder_get_object (widge->builder, "repeat_user_password"));
    widge->registration = GTK_WIDGET(gtk_builder_get_object (widge->builder, "registration"));
    widge->return_sign_in = GTK_WIDGET(gtk_builder_get_object (widge->builder, "return_sign_in"));

    widge->command_line = GTK_WIDGET(gtk_builder_get_object (widge->builder, "command_line"));
    widge->com_event_box = GTK_WIDGET(gtk_builder_get_object (widge->builder, "com_event_box"));
    widge->setting = GTK_WIDGET(gtk_builder_get_object (widge->builder, "setting"));

    widge->name_exists = GTK_LABEL(gtk_builder_get_object (widge->builder, "name_exists"));//nd
    widge->wrong_login = GTK_LABEL(gtk_builder_get_object (widge->builder, "wrong_login"));//nd

    widge->message_win = GTK_FIXED(gtk_builder_get_object (widge->builder, "message_win"));

    widge->list_box = GTK_WIDGET(gtk_builder_get_object(widge->builder, "list_box"));
    widge->profile_button = GTK_WIDGET(gtk_builder_get_object(widge->builder, "profile_button"));
    widge->send_button = GTK_WIDGET(gtk_builder_get_object(widge->builder, "send_button"));

    widge->friends = GTK_WIDGET(gtk_builder_get_object(widge->builder, "friends"));

    widge->who_writing = GTK_WIDGET(gtk_builder_get_object(widge->builder, "who_writing"));

    widge->sticker_pack = GTK_WIDGET(gtk_builder_get_object(widge->builder, "sticker_pack"));
    widge->file_button = GTK_WIDGET(gtk_builder_get_object(widge->builder, "file_button"));
    widge->achiev = GTK_WIDGET(gtk_builder_get_object(widge->builder, "achiev"));
    widge->setting = GTK_WIDGET(gtk_builder_get_object(widge->builder, "setting"));

    widge->theme_1 = GTK_WIDGET(gtk_builder_get_object(widge->builder, "theme_1"));
    widge->theme_2 = GTK_WIDGET(gtk_builder_get_object(widge->builder, "theme_2"));
    widge->theme_3 = GTK_WIDGET(gtk_builder_get_object(widge->builder, "theme_3"));
    widge->theme_4 = GTK_WIDGET(gtk_builder_get_object(widge->builder, "theme_4"));
    widge->theme_5 = GTK_WIDGET(gtk_builder_get_object(widge->builder, "theme_5"));
    widge->theme_6 = GTK_WIDGET(gtk_builder_get_object(widge->builder, "theme_6"));

    widge->back = GTK_WIDGET(gtk_builder_get_object(widge->builder, "back"));

    widge->main_chat = GTK_WIDGET(gtk_builder_get_object(widge->builder, "main_chat"));

    widge->scrolled = GTK_WIDGET(gtk_builder_get_object(widge->builder, "scrolled"));

    widge->slider_adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(widge->scrolled));

    widge->choose_user = GTK_WIDGET(gtk_builder_get_object(widge->builder, "choose_user"));

    widge->papa_bot = GTK_WIDGET(gtk_builder_get_object (widge->builder, "papa_bot"));

    widge->search_entry = GTK_WIDGET(gtk_builder_get_object (widge->builder, "search_entry"));
    // gtk_list_box_unselect_all (GTK_LIST_BOX(widge->list_box));

    mx_set_images(widge);
    // relieff_set(widge);
    design_css(widge);
}
