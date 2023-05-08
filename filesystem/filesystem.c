#include "filesystem.h"

/* ファイルを開く関数 */
int open_file(char* path, int flags)
{
    /* ファイルの存在を確認する */
    if (check_file_exists(path)) {
        /* ファイルが存在する場合、指定されたフラグに応じた処理を行う */
        if (flags == READ_ONLY) {
            /* 読み取り専用で開く場合は、ファイルを開いてファイルディスクリプタを返す */
            int fd = open(path, O_RDONLY);
            return fd;
        } else if (flags == WRITE_ONLY) {
            /* 書き込み専用で開く場合は、ファイルを作成して開き、ファイルディスクリプタを返す */
            int fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
            return fd;
        } else {
            /* その他のフラグが指定された場合はエラーを返す */
            return -1;
        }
    } else {
        /* ファイルが存在しない場合はエラーを返す */
        return -1;
    }
}

/* ファイルを閉じる関数 */
void close_file(int fd)
{
    close(fd);
}

/* ファイルにデータを書き込む関数 */
int write_file(int fd, char* data, size_t size)
{
    int ret = write(fd, data, size);
    if (ret < 0) {
        return -1;
    }
    return ret;
}

/* ファイルからデータを読み込む関数 */
int read_file(int fd, char* buf, size_t size)
{
    int ret = read(fd, buf, size);
    if (ret < 0) {
        return -1;
    }
    return ret;
}

/* ファイルが存在するかどうかを確認する関数 */
int check_file_exists(char* path)
{
    struct stat st;
    if (stat(path, &st) == 0) {
        return S_ISREG(st.st_mode);
    } else {
        return 0;
    }
}
