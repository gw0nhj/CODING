//p86 생성자 오버로딩 연습
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class Date {
    private:
        int year_;
        int month_;
        int day_;

    public:
        
        void ShowDate();
    
    Date() {
        year_ = 2026;
        month_ = 1;
        day_ = 1;
    }

    Date(int year, int month, int day) {
        year_ = year;
        month_ = month;
        day_ = day;
    }


};

int main() {

    Date day1;
    Date day2(2026, 12, 2);

    day1.ShowDate();
    day2.ShowDate();

    return 0;
}

void Date::ShowDate() {
    cout << year_ << endl;
    cout << month_ << endl;
    cout << day_ << endl;
}