#include "../inc/uchat.h"

int callback_list_history(void *data, int argc, char **argv, char **ColName) {
    t_history *send = malloc(sizeof(t_history));

    send->text = strdup(argv[0]);
    send->text_id = atoi(argv[1]);
    mx_push_front((t_list **)data, send);
    return 0;
}

t_list *mx_history_chat(int text_id, int chats_id, use_mutex_t *mutex) {
    t_list *list = 0;
    t_sqlite *lite = malloc(sizeof(t_sqlite));
    char *sql = 0;

    asprintf(&sql, "select text, chats_id from messeges where chats_id = %i "
    "and text_id > %i order by text_id desc limit 10;", chats_id, text_id);
    lite->data = &list;
    lite->callback = callback_list_history;
    lite->sql = sql;
    mx_sqlite(lite, mutex);
    free(sql);
    free(lite);
    return list;
}

void mx_free_history(t_list *list) {
    t_list *new;
    t_history *send = NULL;

    for (t_list *old = list; old != 0; old = new) {
        new = old->next;
        send = old->data;
        free(send->text);
        free(send);
        mx_pop_front(&old);
    }
}