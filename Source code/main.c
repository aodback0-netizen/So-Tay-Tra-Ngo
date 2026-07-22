#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Thư viện hỗ trợ tạo thư mục tùy theo hệ điều hành
#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#define MKDIR(path) mkdir(path, 0777)
#endif

// Hàm thay thế chuỗi để xử lý tiếng Việt UTF-8
void replace_string(char *target, const char *needle, const char *replacement) {
    char buffer[1024] = {0};
    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t needle_len = strlen(needle);
    size_t repl_len = strlen(replacement);

    while (1) {
        const char *p = strstr(tmp, needle);
        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;
        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;
        tmp = p + needle_len;
    }
    strcpy(target, buffer);
}

// Hàm chuyển Tiếng Việt có dấu thành không dấu và khoảng trắng thành dấu gạch ngang
void remove_diacritics(const char *input, char *output) {
    strcpy(output, input);
    
    // Xử lý các ký tự có dấu cho: trà, chén, ấm, cụ
    replace_string(output, "à", "a");
    replace_string(output, "é", "e");
    replace_string(output, "ấ", "a");
    replace_string(output, "ụ", "u");
    
    // Thay thế khoảng trắng thành dấu gạch ngang cho chuẩn URL
    replace_string(output, " ", "-");
}

int main() {
    // Đặt hệ thống hiển thị UTF-8 trên CMD Windows để không bị lỗi font
    system("chcp 65001 > nul");

    // TÊN REPO LẤY TỪ ẢNH CỦA BẠN: So-Tay-Tra-Ngo
    // HÃY THAY THẾ "[TEN_TAI_KHOAN_CUA_BAN]" bằng username thật của bạn
    const char *base_url = "https://github.com/[]/So-Tay-Tra-Ngo/tree/main/";
    
    // 4 thư mục gốc
    const char *folders[] = {"trà", "chén trà", "ấm trà", "trà cụ"};
    int num_folders = sizeof(folders) / sizeof(folders[0]);

    printf("\n");
    printf("====================================================================================================\n");
    printf("| %-12s | %-12s | %-65s |\n", "Thu muc goc", "Ten URL", "Duong dan GitHub (Giu Ctrl + Click chuot trai de mo)");
    printf("====================================================================================================\n");

    for (int i = 0; i < num_folders; i++) {
        char url_name[256];
        remove_diacritics(folders[i], url_name);
        
        // Tạo đường dẫn hoàn chỉnh
        char full_url[512];
        sprintf(full_url, "%s%s", base_url, url_name);

        // In ra dạng bảng trên CMD
        printf("| %-12s | %-12s | %-65s |\n", folders[i], url_name, full_url);

        // Tự động tạo thư mục vật lý trên máy tính (nếu chưa có)
        if (MKDIR(url_name) == 0) {
            // Tạo thành công sẽ không báo gì để tránh rối bảng
        }
    }
    printf("====================================================================================================\n");
    printf(">> Da tu dong tao 4 thu muc tren may tinh tai noi chay file nay.\n\n");

    return 0;
}
