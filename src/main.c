#include "../inc/uchat.h"

int main(int argc, char *argv[]) {
    t_widget_my *widge = (t_widget_my *)malloc(sizeof(t_widget_my));
    widge->message_id = 0;
    widge->id_friend = 0;
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
    widge->theme = gtk_css_provider_new ();

    gtk_css_provider_load_from_path (widge->theme, "src/themes/theme_1.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(widge->theme),
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

    mx_login_win(widge);
    

    gtk_main ();
    // free(widge->main_chat);
    // free(widge);
    // system("leaks -q uchat");
    return 0;
}
