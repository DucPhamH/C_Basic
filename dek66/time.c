#include <stdio.h>
#include <time.h>

int main() {
    // Khai báo biến thời gian
    time_t rawtime;
    struct tm * timeinfo;

    // Lấy thời gian hiện tại
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // Lưu các giá trị ngày, tháng, năm, giờ, phút, giây vào các biến
    int day = timeinfo->tm_mday;
    int month = timeinfo->tm_mon + 1; // Tháng bắt đầu từ 0, cộng thêm 1 để đưa về đúng tháng
    int year = timeinfo->tm_year + 1900; // Năm bắt đầu từ 1900
    int hour = timeinfo->tm_hour;
    int minute = timeinfo->tm_min;
    int second = timeinfo->tm_sec;

    // In ra các giá trị của các biến
    printf("Ngay: %d\n", day);
    printf("Thang: %d\n", month);
    printf("Nam: %d\n", year);
    printf("Gio: %d\n", hour);
    printf("Phut: %d\n", minute);
    printf("Giay: %d\n", second);

    return 0;
}
