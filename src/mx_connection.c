#include "../inc/uchat.h"

void mx_create_chat(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    gtk_widget_grab_focus (widge->command_line);
    gtk_entry_set_text(GTK_ENTRY(widget), "");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widget), "No such user");
}

void mx_pop_front(t_list **head) {
    t_list *first = *head;
    *head = (*head)->next;
    free(first->login);
    free(first->id);
    first->login = NULL;
    first->id = NULL;
}

void free_list(t_list **head) {
    while(*head)
        mx_pop_front(head);
}

t_list *mx_create_node(char *login, char *id, int online) {
    t_list *node = (t_list *) malloc(sizeof(t_list));

    node->login = strdup(login);
    node->id = strdup(id);
    node->online = online;
    node->next = NULL;  
    return node;
}

void mx_push_back(t_list **list, char *login, char *id, int online){
    if(*list == NULL) {
        *list = mx_create_node(login, id, online);
        return;
    }
    t_list *copy = *list;

    while(copy->next != NULL) {
        copy = copy->next;
    }
    copy->next = mx_create_node(login, id, online);
    copy = copy->next;
}

void mx_parse_whoonline(t_widget_my *widge, cJSON *json) {
    cJSON *user = NULL;
    cJSON *peoples = NULL;
    cJSON *user_id;
    cJSON *login;
    cJSON *online;
    user = cJSON_GetObjectItemCaseSensitive(json, "user");
    cJSON_ArrayForEach(peoples, user) { 
        login = cJSON_GetObjectItemCaseSensitive(peoples, "login");
        user_id = cJSON_GetObjectItemCaseSensitive(peoples, "user_id");
        online = cJSON_GetObjectItemCaseSensitive(peoples, "online");

        write(1, login->valuestring, strlen(login->valuestring));
        write(1, "\n", 1);
        write(1, user_id->valuestring, strlen(user_id->valuestring));
        write(1, "\n", 1);
        printf("%d\n",online->valueint);
        write(1, "===================\n", strlen("===================\n"));
        mx_push_back(&widge->login_id, login->valuestring, user_id->valuestring, online->valueint);
        //if (online->valueint == 1)
        mx_create_friend(widge, login->valuestring, online->valueint);
    }   
}

static void change_pos(GtkWidget *widget, void *data) {
    static gdouble uper = 0;

    if (uper != gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget))) {
        gtk_adjustment_set_value(GTK_ADJUSTMENT(widget), gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget)));
        uper = gtk_adjustment_get_upper(GTK_ADJUSTMENT(widget));
    }
}

void mx_papa_bot(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;
    char *login = (char *) gtk_button_get_label(GTK_BUTTON(widget));
    
    gtk_button_set_label (GTK_BUTTON(widge->who_writing), login);
    mx_remove_mess(widge);
    widge->to = login;
}

void hazker_mode(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_css_provider_load_from_path (widge->theme, "src/hacker.css", NULL);
}

void send_file(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    mx_dialog_open(widge);
}

void theme_1(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_css_provider_load_from_path (widge->theme, "src/hacker.css", NULL);
}

void theme_2(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_css_provider_load_from_path (widge->theme, "src/default.css", NULL);
}

void theme_3(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    gtk_widget_hide(widge->win_sett);
    gtk_widget_show_all(widge->main_chat);
}


void setting_win(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;

    g_signal_connect (widge->theme_1, "clicked", G_CALLBACK(theme_1), widge);
    g_signal_connect (widge->theme_2, "clicked", G_CALLBACK(theme_2), widge);
    g_signal_connect (widge->theme_3, "clicked", G_CALLBACK(theme_3), widge);
    gtk_widget_hide(widge->main_chat);
    gtk_widget_show_all(widge->win_sett);
}

static void send_message(GtkWidget* widget, void *dat) {
    t_widget_my *widge = (t_widget_my *)dat;
    char *str; //строка которую отправляем Лехе
    char *message = (char *)gtk_entry_get_text(GTK_ENTRY(widget)); //считываем данные с ввода

    if (strlen(message) == 0) { //если пустая строка, ничего не делать
        printf("Are you kidding me?\n");
    }
    else {
        mx_message_to(widge, message);
        // mx_remove_friend_list(widge);
        asprintf(&str, "{\"TO\":\"%s\",\"MESS\":\"%s\",\"TYPE\":\"text\",\"CHAT_ID\":\"0\"}\n", widge->to, message);
        //write(1, str, strlen(str));
        write(widge->sockfd, str, strlen(str)); //отпрвляем Лехе данные
        gtk_entry_set_text(GTK_ENTRY(widge->command_line), ""); //обнуляем вводимую строку, следовательно обнуляеться message
        free(str);
    }
}

static bool if_online(cJSON *js) {
    cJSON *online = cJSON_GetObjectItemCaseSensitive(js, "USERS");

    if(cJSON_IsTrue(online) == 1)
        return true;
    return false;
}

static bool if_chats(cJSON *js) {
    cJSON *chats = cJSON_GetObjectItemCaseSensitive(js, "chats");

    if(cJSON_IsTrue(chats) == 1)
        return true;
    return false;
}

static void parse_mess(cJSON *js, t_widget_my *widge) {
    cJSON *mess = cJSON_GetObjectItemCaseSensitive(js, "MESS");
    cJSON *to = cJSON_GetObjectItemCaseSensitive(js, "TO");

    printf("ТИ - %s\n", to->valuestring);
    mx_message_from(widge, mess->valuestring);
    write(1, mess->valuestring, strlen(mess->valuestring));
}

static void *Read(void *dat) {
    t_widget_my *widge = (t_widget_my *) dat;
    char buff[2048];
    int len;
    cJSON *json;
    t_list *p = widge->login_id;

    while(1) {
        
        len = read(widge->sockfd, buff, 2048);
        json = cJSON_Parse(buff);
        //if (!if_chats(json)) {
            //write(1, buff, strlen(buff));
            mx_message_from(widge, buff);
            //parse_mess(json, widge);
        //}
        if (if_online(json)) {
            free_list(&widge->login_id);
            mx_parse_whoonline(widge, json);
        }
        bzero(buff, 2048);
        cJSON_Delete(json);
    }
    int exit;
    pthread_exit(&exit);
    return (void*)0;
}

void profile(GtkWidget* widget, void *data) {
    t_widget_my *widge = (t_widget_my *)data;

    if (widge->on_profile == 0) {
        t_list *p = widge->login_id;

        widge->on_profile = 1;
        mx_profile_gtk(widge);
    }
}

void mx_connection(t_widget_my *widge) {
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    pthread_t preg;
    char *str;
    char buff[2048];
    cJSON *json;
    portno = widge->port;
    widge->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (widge->sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(widge->ip);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(widge->sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
    asprintf(&str, "{\"LOGIN\":\"%s\",\"PASS\":\"%s\"}\n", widge->login, widge->pass); //записываем в строку логин и пароль для Лехи
    write(widge->sockfd, str, strlen(str)); //отпраявляем логин и пароль Лехе
    free(str);


    read(widge->sockfd, buff, 2048);
    json = cJSON_Parse(buff);
    if (if_online(json))
        mx_parse_whoonline(widge, json);
    cJSON_Delete(json);
    gtk_widget_hide(GTK_WIDGET(widge->wrong_login));
    if (atoi(buff) != -1) {
        mx_chat_win(widge);
        g_signal_connect (widge->profile_button, "clicked", G_CALLBACK(profile), widge);
        g_signal_connect (widge->send_button, "clicked", G_CALLBACK(send_message), widge);
        g_signal_connect (widge->command_line, "activate", G_CALLBACK(send_message), widge);
        g_signal_connect (widge->achiev, "clicked", G_CALLBACK(hazker_mode), widge);
        g_signal_connect (widge->setting, "clicked", G_CALLBACK(mx_setting_win), widge);
        g_signal_connect (widge->file_button, "clicked", G_CALLBACK(send_file), widge);
        g_signal_connect(widge->slider_adj, "changed", G_CALLBACK(change_pos), NULL);
        g_signal_connect(widge->papa_bot, "clicked", G_CALLBACK(mx_papa_bot), widge);
        g_signal_connect (widge->search_entry, "activate", G_CALLBACK(mx_create_chat), widge);
        pthread_create(&preg, 0, Read, widge);
    }
    else {
        gtk_widget_show(GTK_WIDGET(widge->wrong_login));
        gtk_label_set_text(widge->wrong_login, "WRONG LOGIN OR PASSWORD");
    }
}
