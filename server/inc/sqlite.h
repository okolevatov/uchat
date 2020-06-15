#ifndef SQLITE_H
#define SQLITE_H

#include "uchat.h"
#include <sqlite3.h>

typedef struct s_login_pass {
    char *login;
    char *pass;
    // int socket;
} t_login_pass;

void mx_sqlite(char *sql, int (*callback)(void *, int, char **, char **), void *data);
void mx_create_table(char *name_table, char *values_table);
void mx_tables();
void mx_add_to_table(char *name_table, char *values_table, char *values);
void mx_set_value(char *name_table, char *str_change, char *search_condition);
void mx_select(char *search, char *tables, int (*callback)(void *, int, char **, char **), void *data);
bool mx_path_connect(char *login, char *pass);

#endif