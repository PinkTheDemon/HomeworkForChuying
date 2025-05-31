#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <string.h>
#include "logger.h"

#define ADDLOG 1
#define SHOWALLLOG 2
#define SORTLOG 3
#define SEARCHBYKEYWORD 4
#define EXIT 0

int main() {
#ifdef _WIN32
    // 设置控制台输出和输入编码为 UTF-8
    SetConsoleOutputCP(CP_UTF8);  // 影响 printf 输出
#endif
    int choice;
    wchar_t winput[256];
    char input[256], utf8_input[256], keyword[64];
    log_entry_t logs[MAX_LOGS];
    int count;

    while (1) {
        printf("\nMiniLog 日志系统\n");
        printf("1. 添加日志\n");
        printf("2. 显示所有日志\n");
        printf("3. 按字母排序日志\n");
        printf("4. 按关键词搜索日志\n");
        printf("0. 退出程序\n");
        printf("请输入操作编号: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("输入错误，请输入数字。\n");
            while (getchar() != '\n'); // 清空错误输入
            continue;
        }
        (void)getchar(); // 吸收回车

        switch (choice) {
            case ADDLOG:
#ifdef _WIN32
                printf("请输入日志内容: ");

                DWORD read = 0;
                HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
                if (!ReadConsoleW(hInput, winput, 255, &read, NULL)) {
                    printf("读取失败。\n");
                    break;
                }
                winput[read] = L'\0';

                // 去掉末尾换行
                if (read > 0 && winput[read - 1] == L'\n') {
                    winput[read - 1] = L'\0';
                }

                // UTF-16 → UTF-8
                int utf8_len = WideCharToMultiByte(CP_UTF8, 0, winput, -1, utf8_input, sizeof(utf8_input), NULL, NULL);
                if (utf8_len == 0) {
                    printf("转换失败。\n");
                    break;
                }

                add_log_entry(utf8_input);
#else
                printf("请输入日志内容: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                add_log_entry(input);
#endif
                break;
            case SHOWALLLOG:
                load_logs(logs, &count);
                for (int i = 0; i < count; ++i) {
                    if (should_print_log(logs[i].message)) {
                        printf("[%s] %s\n", logs[i].timestamp, logs[i].message);
                    }
                }
                break;
            case SORTLOG:
                load_logs(logs, &count);
                sort_logs(logs, count);
                save_logs(logs, count);
                break;
            case SEARCHBYKEYWORD:
                printf("请输入关键词: ");
                fgets(keyword, sizeof(keyword), stdin);
                keyword[strcspn(keyword, "\n")] = '\0';
                load_logs(logs, &count);
                search_logs(logs, count, keyword);
                break;
            case EXIT:
                printf("程序退出。\n");
                return 0;
            default:
                printf("无效选项，请重试。\n");
        }
    }
}
