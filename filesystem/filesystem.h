#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "types.h"

// ファイル属性の定義
#define FS_ATTR_DIRECTORY 0x01  // ディレクトリ
#define FS_ATTR_READ_ONLY 0x02  // 読み込み専用

// ファイルの情報を格納する構造体
struct file_info {
    uint32_t size;            // ファイルのサイズ
    uint8_t attributes;       // ファイルの属性
    char filename[256];       // ファイル名
    uint64_t created_time;    // ファイルの作成日時
    uint64_t modified_time;   // ファイルの変更日時
};

// ファイルのオープン
int32_t file_open(const char* path);

// ファイルのクローズ
void file_close(int32_t fd);

// ファイルの読み取り
int32_t file_read(int32_t fd, void* buffer, uint32_t size);

// ファイルの書き込み
int32_t file_write(int32_t fd, const void* buffer, uint32_t size);

// ファイルのサイズを取得する
uint32_t file_get_size(const char* path);

// ファイルを作成する
int32_t file_create(const char* path);

// ファイルを削除する
int32_t file_delete(const char* path);

// ディレクトリを作成する
int32_t dir_create(const char* path);

// ディレクトリを削除する
int32_t dir_delete(const char* path);

// ファイルまたはディレクトリの情報を取得する
int32_t get_file_info(const char* path, struct file_info* info);

#endif
