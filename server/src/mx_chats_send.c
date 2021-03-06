#include "../inc/uchat.h"

static void adding(t_messeges *chat, cJSON *who_in_chat) {
    t_list *users = chat->who_is_here;
    cJSON *user_id = NULL;

    while (users) {
        user_id = cJSON_CreateString((char *) users->data);
        cJSON_AddItemToObject(who_in_chat, "user_in_chat", user_id);
        users = users->next;
    }
}

static void creating_cJSON(cJSON *users, t_messeges *chat) { // надо знать кто последний отправил сообщение и кто учавствует в этом чате
    cJSON *id = cJSON_CreateString(mx_itoa(chat->chats_id));
    cJSON *last_mess = cJSON_CreateString(chat->text);
    cJSON *who_in_chat = cJSON_CreateArray();
    char *str = mx_itoa(chat->who_write);
    cJSON *who_write = cJSON_CreateString(str);

    cJSON_AddItemToObject(users, "id", id);
    cJSON_AddItemToObject(users, "last_mess", last_mess);
    cJSON_AddItemToObject(users, "who_write", who_write);
    cJSON_AddItemToObject(users, "who_in_chat", who_in_chat);
    adding(chat, who_in_chat);
    free(str);
}

void mx_chats_send(use_mutex_t *mutex) {
    t_list *chats = mx_list_last_users_messeges(mutex);
    cJSON *root = cJSON_CreateObject();
    cJSON *users = NULL;
    cJSON *info = NULL;
    char *str = NULL;

    write(1, "\n\n", 2);

    if (chats != NULL) {
        users = cJSON_CreateArray();
        cJSON_AddItemToObject(root, "chats", users);
    }
    else {
        users = cJSON_CreateFalse();
        cJSON_AddItemToObject(root, "chats", users);
        write(1, "DELETING", 8);
    }
    while(chats) {
        info = cJSON_CreateObject();
        cJSON_AddItemToArray(users, info);
        creating_cJSON(info, (t_messeges *) chats->data);
        chats = chats->next;
    }
    str = cJSON_Print(root);
    write(mutex->cli_fd, str, strlen(str));
    write(1, str, strlen(str));
    cJSON_Delete(users);
    free(str);
    write(1, "\n\n", 2);
}
