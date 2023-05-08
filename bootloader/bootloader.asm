bits 16			;16ビットモードを使用する
org 0x7c00			;ブートセクタは0x7c00にロードされる

section bootloader		;ブートローダーセクション
start:				;開始位置
    mov ax, 0x07c0		;セグメントレジスタの初期化
    mov ds, ax
    mov ax, 0x07e0
    mov es, ax

    mov si, bootmsg		;メッセージのアドレスをレジスタに保存
    call print_string		;文字列を表示するサブルーチンの呼び出し

    jmp $			;無限ループ

bootmsg:			;メッセージのデータ
    db 'Hello, World!', 0

print_string:			;文字列を表示するサブルーチン
    pusha			;レジスタの保存
    mov ah, 0x0e		;BIOS割り込みの設定
.loop:
    lodsb			;メモリから1バイト読み込み
    cmp al, 0
    je .done
    int 0x10			;画面に表示
    jmp .loop
.done:
    popa			;レジスタの復元
    ret				;サブルーチン終了
