#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct quan ly thong tin am tra
typedef struct {
    int id;
    char tenAm[40];
    double giaTien;
    int dungTichMl;
    char chatDat[20];
    char khaNangHuong[30];
    char tonTra[30];
    char kieuDang[20];
    char kichCo[20]; // Dai x Rong x Cao (cm)
} AmTra;

// Danh sach kho am tra co san
AmTra danhSachAm[] = {
    {1, "Am Tu Sa Tay Thi", 1500000, 150, "Chu Ne", "Cao (Giu huong)", "Tot (Nhanh len nuoc)", "Tay Thi", "11x7x6 cm"},
    {2, "Am Tu Sa Thach Bieu", 2200000, 200, "Tu Ne", "Trung Binh", "Rat Tot (Giu vi)", "Thach Bieu", "13x8x7 cm"},
    {3, "Am Tu Sa Thuy Binh", 1800000, 180, "Dai Hong Pao", "Rat Cao", "Trung Binh", "Thuy Binh", "12x7.5x6.5 cm"},
    {4, "Am Tu Sa Dung Thien", 2800000, 350, "Doan Ne", "Trung Binh", "Kha (Nhat vi)", "Dung Thien", "15x10x9 cm"},
    {5, "Am Tu Sa Bao Xuan", 3200000, 250, "Tu Ne Co", "Cao", "Rat Tot", "Bao Xuan", "14x9x8 cm"}
};

int soLuongAm = sizeof(danhSachAm) / sizeof(danhSachAm[0]);

// Cac ham ho tro ve giao dien (UI Components)
void veDuongKeNgang(char ch, int len) {
    for (int i = 0; i < len; i++) putchar(ch);
    putchar('\n');
}

void veTieuDeUI(const char* title) {
    printf("\n+");
    veDuongKeNgang('-', 118);
    printf("| %-116s |\n", title);
    printf("+");
    veDuongKeNgang('-', 118);
}

// 1. GIAO DIEN BANG THONG KE AM TRA
void hienThiUIBangThongKe() {
    veTieuDeUI("                       [ DANH SACH AM TRA & THONG SO KY THUAT ]");
    
    printf("| %-2s | %-20s | %-10s | %-8s | %-12s | %-20s | %-20s | %-10s |\n", 
           "ID", "Ten Am Tra", "Gia (VND)", "DungTich", "Chat Dat", "Kha Nang Huong", "Ton Tra", "Kieu Dang");
    printf("+");
    veDuongKeNgang('=', 118);

    for (int i = 0; i < soLuongAm; i++) {
        printf("| %-2d | %-20s | %-10.0f | %-6dml | %-12s | %-20s | %-20s | %-10s |\n",
               danhSachAm[i].id,
               danhSachAm[i].tenAm,
               danhSachAm[i].giaTien,
               danhSachAm[i].dungTichMl,
               danhSachAm[i].chatDat,
               danhSachAm[i].khaNangHuong,
               danhSachAm[i].tonTra,
               danhSachAm[i].kieuDang);
    }
    printf("+");
    veDuongKeNgang('-', 118);
}

// Ham goi y loai tra theo chat dat
void goiYTraUI(const char* chatDat) {
    printf("| [GOI Y TRA PHU HOP]:\n");
    if (strcmp(chatDat, "Chu Ne") == 0) {
        printf("|  -> O Long Thanh Huong, Tra Xanh, Bach Tra (Ton huong thom, giu vi mat).\n");
    } else if (strcmp(chatDat, "Tu Ne") == 0 || strcmp(chatDat, "Tu Ne Co") == 0) {
        printf("|  -> Pho Nhi Song/Chin, Hong Tra, O Long Nuong (Giu nhiet dam, nhuat tra nhuon).\n");
    } else if (strcmp(chatDat, "Dai Hong Pao") == 0) {
        printf("|  -> Nham Tra Vu Di, Dai Hong Pao, Tra San Tuyet (Kich huong cuc tot).\n");
    } else if (strcmp(chatDat, "Doan Ne") == 0) {
        printf("|  -> Tra San Tuyet Cung Dinh, Tra Thao Moc (Thoat nhiet tot, khong bi nong tra).\n");
    }
}

// 2. GIAO DIEN TINH TOAN VA GOI Y MUA AM
void hienThiUITinhToanGoiY() {
    int soNguoi, gioiTinh;
    double luongTra, doNo, doHut;

    veTieuDeUI("                  [ KHUNG NHAP THONG SO CHON AM PHU HOP ]");
    
    printf("| Nhap so nguoi uong tra        : "); scanf("%d", &soNguoi);
    printf("| Nhap gioi tinh (1:Nam, 2:Nu)   : "); scanf("%d", &gioiTinh);
    printf("| Nhap luong tra kho (Gam)      : "); scanf("%lf", &luongTra);
    printf("| Nhap do no cua tra (2.5 - 5.0) : "); scanf("%lf", &doNo);
    printf("| Nhap do hut nuoc (2.0 - 3.5)  : "); scanf("%lf", &doHut);

    // Tinh toan dung tich
    double nuocNguoi = 45.0; // ml/nguoi/tuan
    double nuocThucTe = soNguoi * nuocNguoi;
    double traChiem = luongTra * doNo * 1.2;
    double nuocHut = luongTra * doHut;
    double tongDungTich = nuocThucTe + traChiem + nuocHut;

    veTieuDeUI("                   [ KET QUA PHAN TICH & DE XUAT UY TIN ]");
    printf("| - Tong nuoc ngam phuc vu (%d nguoi) : %.1f ml\n", soNguoi, nuocThucTe);
    printf("| - The tich tra no & hut nuoc        : %.1f ml\n", traChiem + nuocHut);
    printf("| => DUNG TICH AM KHUYEN NGHI          : ~%.0f ml\n", tongDungTich);
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");

    // Goi y kieu dang & kich co theo gioi tinh
    printf("| [GOI Y KIEU DANG & KICH THUOC GIOT TINH]:\n");
    if (gioiTinh == 1) {
        printf("| - NAM GIOI : Chon kieu dang vung chai, duong net manh me (Thach Bieu, Dung Thien, Han Quan).\n");
        printf("|              Quai cam rong, duong kinh am vua tay nam (12cm - 15cm).\n");
    } else {
        printf("| - NU GIOI  : Chon kieu dang mem mai, tinh te (Tay Thi, Thuy Binh, Bao Xuan).\n");
        printf("|              Kich thuoc nho gọn, trong luong nhe, quai cam thanh thoat (10cm - 13cm).\n");
    }
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");

    // Tim am phu hop
    int count = 0;
    for (int i = 0; i < soLuongAm; i++) {
        if (abs(danhSachAm[i].dungTichMl - (int)tongDungTich) <= 60) {
            count++;
            printf("| [+] AM GOI Y #%d: %s (ID: %d)\n", count, danhSachAm[i].tenAm, danhSachAm[i].id);
            printf("|     Dung tich: %dml | Gia: %.0f VND | Kieu: %s | Kich thuoc: %s\n", 
                   danhSachAm[i].dungTichMl, danhSachAm[i].giaTien, danhSachAm[i].kieuDang, danhSachAm[i].kichCo);
            goiYTraUI(danhSachAm[i].chatDat);
            printf("+----------------------------------------------------------------------------------------------------------------------+\n");
        }
    }
    if (count == 0) {
        printf("| Hien tai trong kho khong co am gan voi dung tich %.0fml. Vui long xem bang thong ke de chon!\n", tongDungTich);
        printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    }
}

// 3. GIAO DIEN TINH TONG TIEN DON HANG
void hienThiUITinhTien() {
    int idAm = 0, slTra = 0, slChen = 0, slTraCu = 0;
    double giaTraKg = 0, giaChen = 0, giaTraCu = 0;
    double tienAm = 0, tienTra = 0, tienChen = 0, tienTraCu = 0;

    veTieuDeUI("                  [ NHAP THONG TIN DON HANG TRA CU ]");
    printf("| Nhap ID Am Tra ban chon (0 neu khong mua) : "); scanf("%d", &idAm);
    if (idAm > 0 && idAm <= soLuongAm) {
        tienAm = danhSachAm[idAm - 1].giaTien;
        printf("|   -> Da chon am: %s (%.0f VND)\n", danhSachAm[idAm - 1].tenAm, tienAm);
    }

    printf("| Nhap gia 1kg Tra (VND, 0 neu khong mua)   : "); scanf("%lf", &giaTraKg);
    if (giaTraKg > 0) {
        printf("| Nhap so Lang Tra mua (1 Lang = 100g)      : "); scanf("%d", &slTra);
        tienTra = (giaTraKg / 10.0) * slTra;
    }

    printf("| Nhap gia 1 Chen Tra (VND, 0 neu khong mua): "); scanf("%lf", &giaChen);
    if (giaChen > 0) {
        printf("| Nhap so luong Chen Tra mua                : "); scanf("%d", &slChen);
        tienChen = giaChen * slChen;
    }

    printf("| Nhap gia 1 Bo Tra Cu (VND, 0 neu khong)   : "); scanf("%lf", &giaTraCu);
    if (giaTraCu > 0) {
        printf("| Nhap so luong Bo Tra Cu mua               : "); scanf("%d", &slTraCu);
        tienTraCu = giaTraCu * slTraCu;
    }

    // In hoa don UI
    double tongTien = tienAm + tienTra + tienChen + tienTraCu;
    
    printf("\n");
    printf("========================================================================================================================\n");
    printf("|                                           HOA DON THANH TOAN CHI TIET                                                |\n");
    printf("========================================================================================================================\n");
    printf("| 1. Tien Am Tra                             : %20.0f VND                                              |\n", tienAm);
    printf("| 2. Tien Tra                                : %20.0f VND                                              |\n", tienTra);
    printf("| 3. Tien Chen Tra                           : %20.0f VND                                              |\n", tienChen);
    printf("| 4. Tien Bo Tra Cu (Tong, Khay, Thuyen...)  : %20.0f VND                                              |\n", tienTraCu);
    printf("+----------------------------------------------------------------------------------------------------------------------+\n");
    printf("| TONG CONG THANH TOAN                       : %20.0f VND                                              |\n", tongTien);
    printf("========================================================================================================================\n");
}

// 4. MAIN MENU UI
int main() {
    int choice;
    do {
        printf("\n");
        printf("========================================================================================================================\n");
        printf("|                                   HE THONG QUAN LY SO TAY TRA NGO                                         |\n");
        printf("========================================================================================================================\n");
        printf("|  1. Xem bang thong ke tat ca am tra (Gia, Dung tich, Chat dat, Huong, Ton tra)                                       |\n");
        printf("|  2. Tinh toan dung tich, kieu dang, kich thuoc & Goi y am tra phu hop                                                  |\n");
        printf("|  3. Lap hoa don & Tinh tong tien don hang (Am, Tra, Chen, Tra cu)                                                    |\n");
        printf("|  0. Thoat chuong trinh                                                                                                |\n");
        printf("========================================================================================================================\n");
        printf(">>> Nhap lua chon cua ban [0-3]: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                hienThiUIBangThongKe();
                break;
            case 2:
                hienThiUITinhToanGoiY();
                break;
            case 3:
                hienThiUITinhTien();
                break;
            case 0:
                printf("\n[!] Cam on ban da su dung chuong trinh Quan Ly Tra Dao!\n\n");
                break;
            default:
                printf("\n[X] Lua chon khong hop le. Vui long thu lai!\n");
        }
    } while (choice != 0);

    return 0;
}