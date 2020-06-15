#include "../inc/uchat.h"

static void if_registration(cJSON *root, int fd) {
    cJSON* reg = cJSON_GetObjectItemCaseSensitive(root, "REG");
    int ret;

    if (cJSON_IsTrue(reg) == 1) {
        write(1, "HERE REGISTRATION\n", 19);
        mx_creating(root, fd);
        //if (mx_creating(root, fd) == false)
        //  pthread_exit(&ret);
        pthread_exit(&ret);
    } 
    //return true;
}

static bool loging(cJSON *root) {
    cJSON* log = cJSON_GetObjectItemCaseSensitive(root, "LOGIN");
    cJSON* pass = cJSON_GetObjectItemCaseSensitive(root, "PASS");
    
    if (cJSON_IsString(log) && (log->valuestring != NULL)) { 
        write(1, "LOGIN\n" , 7);
        if(mx_pass_connect(log->valuestring, pass->valuestring) == true)
            return true;
        else  
            return false;
    }
    write(1, "ERROR NOT LOGIN\n", 17);
    return false;
}

bool mx_registr(int fd) {
    char buff[2048];
    cJSON* request_json = NULL;

    if (read(fd, buff, 2048) > 0) { //this while or if i don't know
        request_json = cJSON_Parse(buff);
        if_registration(request_json, fd);
        //if (if_registration(request_json, fd) == true) {
            // bzero(buff, 1024);
            // read(fd, buff, 2048);
            // cJSON_Delete(request_json);
            // request_json = cJSON_Parse(buff);
        //}
        if (loging(request_json) == false) {
            bzero(buff, 1024);
            cJSON_Delete(request_json);
            return false;
        } 
        else {
            bzero(buff, 1024);
            cJSON_Delete(request_json);
            return true;
        }
    }
    return false;
}