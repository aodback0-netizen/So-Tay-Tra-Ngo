#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_FILES 200

typedef struct {
    char category[50];
    char filename[100];
    char filepath[300];
    char markdown_link[400];
} TeaFile;

// Hàm chuyển đổi khoảng trắng thành %20 cho đường dẫn URL Markdown
void encodeURL(const char* input, char* output, size_t max_len) {
    size_t j = 0;
    for (size_t i = 0; input[i] != '\0' && j < max_len - 4; i++) {
        if (input[i] == ' ') {
            output[j++] = '%';
            output[j++] = '2';
            output[j++] = '0';
        } else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

// Quét lùi lại 1 cấp thư mục (../) để tìm đúng vị trí các folder chứa tệp
void scanDirectoryForFiles(const char* dir_name, const char* category, TeaFile files[], int* count) {
    DIR *dir = opendir(dir_name);
    if (dir == NULL) return;

    struct dirent *ent;
    struct stat path_stat;
    char full_path[300];
    char encoded_path[350];

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_name[0] == '.') continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", dir_name, ent->d_name);
        
        if (stat(full_path, &path_stat) == 0) {
            if (S_ISREG(path_stat.st_mode)) {
                strncpy(files[*count].category, category, sizeof(files[*count].category) - 1);
                strncpy(files[*count].filename, ent->d_name, sizeof(files[*count].filename) - 1);
                strncpy(files[*count].filepath, full_path, sizeof(files[*count].filepath) - 1);
                
                // Mã hóa đường dẫn và tạo cú pháp Markdown chuẩn
                encodeURL(full_path, encoded_path, sizeof(encoded_path));
                snprintf(files[*count].markdown_link, sizeof(files[*count].markdown_link), 
                         "[%s](%s)", ent->d_name, encoded_path);

                (*count)++;
                if (*count >= MAX_FILES) {
                    closedir(dir);
                    return;
                }
            }
        }
    }
    closedir(dir);
}

void renderTable(TeaFile files[], int count) {
    printf("+----------------------+------------------------------------------+------------------------------------------------------+\n");
    printf("| Danh Mục             | Tên Tệp                                  | Đường Dẫn Markdown Chuẩn                             |\n");
    printf("+----------------------+------------------------------------------+------------------------------------------------------+\n");
    
    for (int i = 0; i < count; i++) {
        printf("| %-20s | %-40s | %-52s |\n", files[i].category, files[i].filename, files[i].markdown_link);
    }
    
    printf("+----------------------+------------------------------------------+------------------------------------------------------+\n");
}

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    TeaFile files[MAX_FILES];
    int count = 0;

    // Trỏ ra ngoài thư mục gốc từ vị trí Source code/
    scanDirectoryForFiles("../Trà", "Trà", files, &count);
    scanDirectoryForFiles("../Ấm trà", "Ấm Trà", files, &count);
    scanDirectoryForFiles("../Chén trà", "Chén Trà", files, &count);
    scanDirectoryForFiles("../Trà cụ", "Trà Cụ", files, &count);

    printf("\n=== KẾT QUẢ TRÍCH XUẤT ĐƯỜNG DẪN TỰ ĐỘNG ===\n");
    if (count > 0) {
        renderTable(files, count);
    } else {
        printf("Lỗi: Không tìm thấy tệp tin. Vui lòng kiểm tra lại cấu trúc thư mục.\n");
    }

    return 0;
}
