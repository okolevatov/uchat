#include "../inc/uchat.h"

int main(int argc, char *argv[]) {
    t_widget_my *widge = (t_widget_my *)malloc(sizeof(t_widget_my));
    widge->message_id = 0;
    widge->from_id = 0;
    widge->id_friend = 0;
    widge->color_mode = 0;
    widge->on_profile = 0;

    widge->message_send = (GtkWidget **)malloc(sizeof(GtkWidget *));
    // widge->mess_arr = g_array_new(TRUE, TRUE, sizeof widge->message_send);

    GError *error = NULL;

    if (argc == 3) {               //dodat check na pravelnist vvoda
        widge->ip = argv[1];
        widge->port = atoi(argv[2]);
    }
    else {
        printf("usage : ./uchat [ip] [port]\n");
        exit(1);
    }

    gtk_init (&argc, &argv);
    
    //css
    widge->dark = gtk_css_provider_new ();

    gtk_css_provider_load_from_path (widge->dark, "src/themes/theme_1.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(widge->dark),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
    //

    widge->builder = gtk_builder_new ();

    if (gtk_builder_add_from_file (widge->builder, "src/login_new.glade", &error) == 0)
    {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error (&error);
        return 1;
    }

    mx_create_widge(widge);

    // widge->sw = gtk_scrolled_window_new (NULL, NULL);
    // gtk_widget_set_hexpand (widge->sw, TRUE);
    // gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (widge->sw), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    // gtk_container_add(GTK_CONTAINER (widge->list_box), widge->sw);

    mx_login_win(widge);
    

    gtk_main ();
    // free(widge->main_chat);
    // free(widge);
    // system("leaks -q uchat");
    return 0;
}
