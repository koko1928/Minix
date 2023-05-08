#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

int main(void) {
    char input[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int status;

    while (1) {
        printf("$ ");
        fgets(input, MAX_CMD_LEN, stdin);

        // 改行文字をヌル文字に変換する
        input[strlen(input) - 1] = '\0';

        // ユーザーの入力をスペースで分割して、args配列に格納する
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0) {
            // exitコマンドが入力されたら、プログラムを終了する
            break;
        }

        // 子プロセスを生成して、ユーザーの入力を実行する
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            execvp(args[0], args);
            perror(args[0]);
            exit(EXIT_FAILURE);
        } else {
            // 親プロセスは子プロセスの終了を待つ
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
