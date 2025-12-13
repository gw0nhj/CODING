/*
p113
아래와 같은 문자열 클래스를 완성해보세요 (난이도 : 中)
*/

#include <iostream>

class string {
    public:

    char *str;
    int len;

    public:

    string(char c, int n); // 문자 c 가 n 개 있는 문자열로 정의
    string(const char *s);
    string(const string &s);
    ~string() {
        if(str) delete[] str;
    };
    void add_string(const string &s); // str 뒤에 s 를 붙인다.
    void copy_string(const string &s); // str 에 s 를 복사한다.
    int strlen(); // 문자열 길이 리턴
};

int main() {
    string s1('a', 4);
    printf("%s\n", s1.str);
    string s2(s1);
    s1.add_string(s2);
    string s3("asdsa");
    s1.add_string(s3);
    printf("%s\n", s1.str);

    string s4('b', 5);
    s4.copy_string(s1);
    printf("%s\n", s4.str);
    printf("%d\n", s4.strlen());
    printf("sex");
    return 0;
}

string::string(char c, int n) {
    str = new char[n+1];
    len = n;

    for(int i = 0; i < n; i++) {
        *(str + i) = c;
    }
    *(str + n) = 0;
}

string::string(const char *s) {
    int str_size = 0;
    while(*(s + str_size) != 0) {
        str_size++;
    }
    str = new char[str_size + 1];
    for(int i = 0; i < str_size; i++) {
        *(str + i) = *(s + i);
    }
    *(str + str_size) = 0;
    len = str_size;
    
}

string::string(const string &s) {
    int str_size = 0;
    while(*(s.str + str_size) != 0) {
        str_size++;
    }

    str = new char[str_size + 1];
    for(int i = 0; i < str_size; i++) {
        *(str + i) = *(s.str + i);
    }

    *(str + str_size) = 0;
    len = str_size;
    
}

void string::add_string(const string &s) {
    int str_size2 = s.len;
    int str_size1 = 0;

    while(*(str + str_size1) != 0) {
        str_size1++;
    }

    char *temp = new char[str_size1 + str_size2 + 1];

    for(int i = 0; i < str_size1; i++) {
        temp[i] = str[i];
    }

    for(int i = str_size1; i < str_size1 + str_size2; i++) {
        temp[i] = s.str[i - str_size1];
    }

    temp[str_size1 + str_size2] = 0;
    delete[] str;
    str = nullptr;
    str = new char[str_size1 + str_size2 + 1];

    for(int i = 0; i < str_size1 + str_size2 + 1; i++) {
        str[i] = temp[i];
    }
    
    len = str_size1 + str_size2;
} // str 뒤에 s 를 붙인다.

void string::copy_string(const string &s) {
    len = s.len;
    delete[] str;
    str = nullptr;
    str = new char[len + 1];

    for(int i = 0; i < len; i++) {
        str[i] = s.str[i];
    }
    
    str[len] = 0;
} // str 에 s 를 복사한다.
int string::strlen() {
    return len;
}