#include "../inc/uchat.h"

static void mylvl(use_mutex_t *mutex) {
    //iz bd dostaem vse chto nado to est po loginu uroven
    cJSON *root = cJSON_CreateObject();
    cJSON *level = cJSON_CreateNumber(mutex->lvl);
    char *str = NULL;

    cJSON_AddItemToObject(root, "Level: ", level);
    str = cJSON_Print(root);
    write(mutex->cli_fd, str, strlen(str));
    free(str);
    cJSON_Delete(root);
}

static void start(use_mutex_t *mutex) {
    // nachinaem cacueto zagadku proveriaya na raiting i v zavisimosti ot raitinga vivodim zagadku
    // pervaya zagadka shifr cezara

}

static void command_false(use_mutex_t *mutex) {
    // commanda ne izvestna
    write(mutex->cli_fd, "Chto eto za slovo?", 18);
}

void mx_papa_bot(cJSON *MESS, use_mutex_t *mutex) { //vsegda nado budet otpravliat chto oni v etom chate ili tipa togo chtobi pisat im commands
    char *mess = strdup(MESS->valuestring);

    if (strcmp(mess, "./mylvl") == 0)
        mylvl(mutex);
    else if (strcmp(mess, "./start") == 0)
        start(mutex);
    else if (strncmp(mess, "./answer:", 10) == 0) 
        mx_answers_papa(mutex);
    else 
        command_false(mutex);
}


