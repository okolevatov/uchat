#include "../inc/uchat.h"

static int callback_persons_id(void *data, int argc, char **argv, char **ColName) {
    char **new = (char **)data;

    *new = strdup(argv[0]);
    return 0;
}

static void send_mess(int socket, cJSON* CHAT_ID, use_mutex_t *mutex, cJSON* MESS) {
    char *str = NULL;

    asprintf(&str, "{\"FROM\":%d,\"MESS\":%s,\"CHAT_ID\":%d}\n", 
            mutex->user_id, MESS->valuestring, atoi(CHAT_ID->valuestring));
    write(socket, str, strlen(str));
    free(str);
}

void mx_send_group(cJSON* MESS, cJSON* USERS_GRP, cJSON* CHAT_ID, use_mutex_t *mutex) {
    cJSON *USER = NULL;
    cJSON *USER_ID = NULL;
    char *str = NULL;
    char *data = NULL;

    cJSON_ArrayForEach(USER, USERS_GRP) {
        USER_ID = cJSON_GetObjectItemCaseSensitive(USER, "USER_ID");
        asprintf(&str, "sockets WHERE users_id = %d", atoi(USER_ID->valuestring));
        mx_select("socket", str, callback_persons_id, &data, mutex);
        if (data != NULL) {
            send_mess(atoi(data), CHAT_ID, mutex, MESS);
            free(data);
        }
        free(str);
    }
    mx_add_message(atoi(CHAT_ID->valuestring), MESS->valuestring, 0, mutex);
}
