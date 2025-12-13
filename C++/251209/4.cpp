//p73 Q1
//Date 클래스 제작

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Date {
    private:
        int year_;
        int month_;
        int day_;

    public:
        void SetDate(int year, int month, int day);
        void AddDay(int inc);
        void AddMonth(int inc);
        void AddYear(int inc);

        void ShowDate();
    
};


int main () {

    Date date1;
    date1.SetDate(2025, 12, 10);
    date1.AddDay(13125);
    date1.ShowDate();
    return 0;

}


void Date::AddDay(int inc) {
    day_ += inc;
    int Calculated = 0;
    do {
        Calculated = 0;

        if(month_ > 6) {

            if((month_ == 7 || month_ == 8 || month_ == 10 || month_ == 12) && day_ > 31) {
                day_ -= 31;
                month_++;
                Calculated = 1;
            }

            else if((month_ == 9 || month_ == 11) && day_ > 30) {
                day_ -= 30;
                month_++;
                Calculated = 1;
            }

        }

        else {

            if((month_ == 1 || month_ == 3 || month_ == 5) && day_ > 31) {
                day_ -= 31;
                month_++;
                Calculated = 1;
            }

            else {

                if((month_ == 4 || month_ == 6) && day_ > 31) {
                    day_ -= 31;
                    month_++;
                    Calculated = 1;
                }
                else if(month_ == 2) {
                    if(year_ % 4 != 0 && day_ > 28) {
                        day_ -= 28;
                        month_++;
                        Calculated = 1;
                    }

                    if(year_ % 4 == 0 && year_ % 100 != 0 && day_ > 29) {
                        day_ -= 29;
                        month_++;
                        Calculated = 1;
                    }

                    if(year_ % 100 == 0 && day_ > 28) {
                        day_ -= 28;
                        month_++;
                        Calculated = 1;
                    }

                }

            }
        }
        if(month_ == 13) {
            year_++;
            month_ -= 12;
        }
    } while (Calculated == 1);

    return;
}

void Date::SetDate(int year, int month, int day) {
    year_ = year;
    month_ = month;
    day_ = day;
}

void Date::ShowDate() {
    cout << year_ << endl;
    cout << month_ << endl;
    cout << day_ << endl;
}