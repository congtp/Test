#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#define MAX_CENCORS 10
#define MAX_CENCOR_VALUE  10

int cencorCount = 1;  // Khởi tạo bắt đầu từ 1
struct Cencor {
    std::string cencorName;
    int cencorValue;


    Cencor(int cencorValue = 0) : cencorValue{cencorValue} {
        this->cencorName = "cencor_monitor" + std::to_string(cencorCount);
        cencorCount++;
    }

    ~Cencor() { cencorCount--; }
};


void InitCencor(std::vector<Cencor> &cencors) {
    for (int i = 0; i < MAX_CENCORS; i++) {
        int temp = rand() % MAX_CENCOR_VALUE + 1;
        cencors.push_back(Cencor(temp));  // Không cần std::move ở đây
    }
}

int main() {
    std::vector<Cencor> cencors;
    InitCencor(cencors);

    // Để kiểm tra
    std::cout << "Number of Cencor objects: " << cencorCount << std::endl;
    return 0;
}
