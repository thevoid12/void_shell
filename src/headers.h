#ifndef HEADERS_H
#define HEADERS_H

void execute_ls(char *flags);
void execute_pwd();
void execute_cd(char *dir);
void execute_touch(char *dir);
void execute_cat(char *dir);
void execute_echo(char *args);
void execute_psinfo(); 
void execute_remindme(int time, const char *message);
void execute_exit();


#endif // HEADERS_H
