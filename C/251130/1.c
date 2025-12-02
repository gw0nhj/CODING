// 337p Q4

#include <stdio.h>

#define MAXBOOKNAME 50
#define MAXNAME 25
#define BOOKAMOUNT 3000

int SameString(char *String1, char *String2);
int SearchBookNum(char String[], char Data[][MAXBOOKNAME + 1]);
void AddBook(char Bookname[], char AuthorName[], char CompanyName[], char BookData[][MAXBOOKNAME + 1], char AuthorData[][MAXNAME + 1], char CompanyData[][MAXNAME + 1]);
int SearchElseNum(char String[], char Data[][MAXNAME + 1]);

void AddSmallData(char String[], char Data[][MAXNAME + 1]);
void AddBigData(char String[], char Data[][MAXBOOKNAME + 1]);
void ScanfString(char String[]);
int HaveString(char *String1, char *String2);

void ClearInputBuffer();
void LoadBooksFromFile(char BookData[][MAXBOOKNAME + 1], char AuthorData[][MAXNAME + 1], char CompanyData[][MAXNAME + 1], const char *filename);

// BOOKAMOUNT권. 책 제목. 저자의 이름. 출판사.
// SearchBookNum - 1 : 책의 인덱스
void main() {
    char BookName[BOOKAMOUNT + 1][MAXBOOKNAME + 1] = {0};
    char Author[BOOKAMOUNT + 1][MAXNAME + 1] = {0};
    char Company[BOOKAMOUNT + 1][MAXNAME + 1] = {0};
    short BORROW[BOOKAMOUNT] = {0};

    char String[MAXBOOKNAME + 1];
    char InputAuthor[MAXNAME + 1];
    char InputCompany[MAXNAME + 1];

    short Command = 1;
    short Index = 0;
    short Num = 0;
    
    LoadBooksFromFile(BookName, Author, Company, "BookList.txt");

    while(Command) {

        printf("\n=============================================\n");
        printf("        L I B R A R Y  C O M M A N D         \n");
        printf("=============================================\n\n");

        printf("1. 책 추가 / 2. 책 검색(이름) / 3. 책 검색(저자) / 4. 책 검색(출판사)\n5. 대출 / 6. 반납 / 7. 대출도서 목록 / 8. 전체도서 목록 / 9. 종료\n\n");
        scanf("%d", &Command);
        
        
        switch (Command)
        {
        case 1:
            /* code */

            ClearInputBuffer();
            printf("Add Name of Book: ");
            ScanfString(String);

            printf("Add Name of Author: ");
            ScanfString(InputAuthor);

            printf("Add Name of Company: ");
            ScanfString(InputCompany);

            AddBook(String, InputAuthor, InputCompany, BookName, Author, Company);

            break;
        
        case 2:
            
            printf("Search Name of Book: ");
            ClearInputBuffer();
            scanf("%[^\n]s", String);
            ClearInputBuffer();
            
            printf("\n");

            if(SearchBookNum(String, BookName)) {

                for(int i = 0; i < BOOKAMOUNT + 1 && BookName[i][0] != 0; i++) {

                    if(HaveString(String, BookName[i])) {
                        printf("In index %d, ", i);
                        printf("BookName: %s, Author: %s, Company: %s\n", BookName[i], Author[i], Company[i]);
                    }

                }

            }

            break;
        
        case 3:
            
            printf("Search Author of Book: ");
            ClearInputBuffer();
            scanf("%[^\n]s", String);
            ClearInputBuffer();

            printf("\n");

            if(SearchElseNum(String, Author)) {

                for(int i = 0; i < BOOKAMOUNT + 1 && BookName[i][0] != 0; i++) {

                    if(SameString(String, Author[i])) {
                        printf("In index %d, ", i);
                        printf("BookName: %s, Author: %s, Company: %s\n", BookName[i], Author[i], Company[i]);
                    }

                }

            }

            break;

        case 4:
            
            printf("Search Company of Book: ");
            ClearInputBuffer();
            scanf("%[^\n]s", String);
            ClearInputBuffer();

            printf("\n");
            
            if(SearchElseNum(String, Company)) {
                for(int i = 0; i < BOOKAMOUNT + 1 && BookName[i][0] != 0; i++) {

                    if(SameString(String, Company[i])) {
                        printf("In index %d, ", i);
                        printf("BookName: %s, Author: %s, Company: %s\n", BookName[i], Author[i], Company[i]);
                    }

                }
            }

            break;

        case 5:

            printf("Enter the index the book you wish to borrow.\n: ");
            scanf("%d", &Index);

            if(BookName[Index][0] != 0) {
                if(BORROW[Index] == 0) {
                    BORROW[Index] = 1;
                    printf("\"%s\" BORROW SUCCESS\n", BookName[Index]);
                }

                else if(BORROW[Index] == 1) {
                    printf("\"%s\" already has been borrowed\n", BookName[Index]);
                }
            }
            else {
                printf("Unknown Index\n");
            }

            Command = 1;
            break;

        case 6:

            printf("Enter the index the book you wish to return.\n: ");
            scanf("%d", &Index);

            if(BookName[Index][0] != 0) {
                if(BORROW[Index] == 1) {
                    BORROW[Index] = 0;
                    printf("\"%s\" RETURN SUCCESS\n", BookName[Index]);
                }

                else if(BORROW[Index] == 0) {
                    printf("\"%s\" already returned\n", BookName[Index]);
                }
            }
            else {
                printf("Unknown Index\n");
            }

            Command = 1;
            break;

        case 7:
            printf("\n");

            for(int i = 0; i < BOOKAMOUNT; i++) {
                if(BORROW[i] == 1) {
                    Num++;
                    printf("In index %d, ", i);
                    printf("BookName: %s, Author: %s, Company: %s\n", BookName[i], Author[i], Company[i]);
                }
            }

            if(Num == 0) {
                printf("\nNOT HAS BEEN BORROWED\n");
            }

            Num = 0;
            Command = 1;
            break;

        case 8:
            printf("\n");
            for(int i = 0; i < BOOKAMOUNT; i++) {
                if(BookName[i][0] != 0) {
                    printf("In index %d, ", i);
                    printf("BookName: %s, Author: %s, Company: %s\n", BookName[i], Author[i], Company[i]);
                }
            }

            Command = 1;
            break;

        case 9:
            Command = 0;
            break;

        default:
            Command = 1;
            break;
        }


    }

    
}

int SearchBookNum(char String[], char Data[][MAXBOOKNAME + 1]) {
    
    int i = 0;

    for(i = 0; i < BOOKAMOUNT; i++) {

        if(Data[i][0] == 0) {
            return 0;
        }

        if(HaveString(String, Data[i])) {
            return i + 1;
        }

    }

    return 0;

}

int SearchElseNum(char String[], char Data[][MAXNAME + 1]) {
    
    int i = 0;

    for(i = 0; i < BOOKAMOUNT; i++) {

        if(Data[i][0] == 0) {
            return 0;
        }

        if(SameString(String, Data[i])) {
            return i + 1;
        }

    }

    return 0;

}

int SameString(char *String1, char *String2) {
    
    while(*String1) {
        if(*String1 != *String2) {
            return 0;
        }

        String1++;
        String2++;
    }

    if(*String2 == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int HaveString(char *String1, char *String2) {
    
    int Num = 0;

    while(*String2) {
        if (*String1 == *String2) {

            Num++;
            String1++;
            String2++;

            if(*String1 == 0) {
                return 1;
            }

        }
        else {
            String1 -= Num;
            Num = 0;
            String2++;
        }
    }

    if(*String2 == 0) {
        return 0;
    }
}

//책 추가
void AddBook(char Bookname[], char AuthorName[], char CompanyName[], char BookData[][MAXBOOKNAME + 1], char AuthorData[][MAXNAME + 1], char CompanyData[][MAXNAME + 1]) {

    AddSmallData(AuthorName, AuthorData);
    AddSmallData(CompanyName, CompanyData);

    AddBigData(Bookname, BookData);

}

void AddSmallData(char String[], char Data[][MAXNAME + 1]) {
    int i = 0;
    int j = 0;

    while(Data[i][0] != 0) {
        i++;
    }

    for(j = 0; String[j]; j++) {
        Data[i][j] = String[j];
    }

    Data[i][j] = '\0';

}

void AddBigData(char String[], char Data[][MAXBOOKNAME + 1]) {
    int i = 0;
    while(Data[i][0] != 0) {
        i++;
    }

    int j = 0;
    for(j = 0; String[j]; j++) {
        Data[i][j] = String[j];
    }

    Data[i][j] = '\0';

}

void ScanfString(char String[]) {
    scanf("%[^\n]s", String);
    ClearInputBuffer();
}

void LoadBooksFromFile(char BookData[][MAXBOOKNAME + 1], char AuthorData[][MAXNAME + 1], char CompanyData[][MAXNAME + 1], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Warning: Could not open file %s. Starting with an empty library.\n", filename);
        return;
    }

    char book_name[MAXBOOKNAME + 1];
    char author_name[MAXNAME + 1];
    char company_name[MAXNAME + 1];
    
    // 쉼표와 공백을 구분자로 사용하며, 최대 버퍼 크기를 초과하지 않도록 지정
    // %[^,]는 쉼표를 만나기 전까지 모든 문자를 읽습니다.
    // %*c는 쉼표(,) 또는 공백을 소비합니다.
    while (fscanf(file, " %[^,], %[^,], %[^\n]", book_name, author_name, company_name) == 3) {
        // 읽은 데이터를 AddBook 함수를 통해 배열에 저장합니다.
        AddBook(book_name, author_name, company_name, BookData, AuthorData, CompanyData);
    }

    fclose(file);
    printf("Successfully loaded books from %s.\n", filename);
}

void ClearInputBuffer() {
    int c;
    // 💡 getchar()의 반환 값을 c에 저장하고, c가 \n이나 EOF인지 확인합니다.
    while ((c = getchar()) != '\n' && c != EOF);
}