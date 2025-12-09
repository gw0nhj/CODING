#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* BOOK 구조체 정의 */
struct BOOK {
    char book_name[30];
    char auth_name[30];
    char publ_name[30];
    int borrowed; // 0: 대출 가능, 1: 대출 중
};

typedef struct BOOK BOOK;

// 함수 프로토타입 (유효성 검사를 위해 매개변수 수정됨)
// max_books: 용량 초과 검사를 위해 추가
int register_book(BOOK *book_list, int *nth, int max_books); 
int search_book(BOOK *book_list, int total_num_book);
// total_num_book: 인덱스 유효성 검사를 위해 추가
int borrow_book(BOOK *book_list, int total_num_book); 
// total_num_book: 인덱스 유효성 검사를 위해 추가
int return_book(BOOK *book_list, int total_num_book); 
int print_book_list(BOOK *book_list, int total_num_book); 

// 사용자 정의 문자열 비교 함수 (정확히 일치할 경우 1 반환)
// string.h의 strcmp를 사용하여 안전하게 구현
char compare(char *str1, char *str2) {
    return (strcmp(str1, str2) == 0); 
}

/*
 * main 함수: 프로그램의 핵심 로직 (메뉴 및 메모리 관리)
 */
int main() {
    int user_choice;        /* 유저가 선택한 메뉴/임시 저장 변수 */
    int num_total_book = 0; /* 현재 책의 수 (0부터 시작하는 인덱스 카운터 역할) */
    BOOK *book_list = NULL;
    int max_books;          /* 도서관의 최대 보관 장서 수 */
    
    // 1. 최대 장서 수 설정 및 메모리 할당
    printf("도서관의 최대 보관 장서 수를 설정해주세요 : ");
    // user_choice 변수를 max_books 용도로 사용하지 않고, 새로운 변수를 사용하는 것이 더 명확합니다.
    if (scanf("%d", &max_books) != 1 || max_books <= 0) {
        fprintf(stderr, "오류: 유효하지 않은 장서 수입니다. 프로그램을 종료합니다.\n");
        return 1;
    }
    
    book_list = (BOOK *)malloc(sizeof(BOOK) * max_books);
    if (book_list == NULL) {
        fprintf(stderr, "오류: 메모리 할당에 실패하였습니다. 프로그램을 종료합니다.\n");
        return 1;
    }
    printf("최대 장서 수 %d 권으로 도서 관리 프로그램을 시작합니다.\n", max_books);

    // 2. 메인 루프 (메뉴 선택)
    while (1) {
        printf("\n--- 도서 관리 프로그램 ---\n");
        printf("메뉴를 선택하세요 \n");
        printf("1. 책을 새로 추가하기 \n");
        printf("2. 책을 검색하기 \n");
        printf("3. 책을 빌리기 \n");
        printf("4. 책을 반납하기 \n");
        printf("5. 프로그램 종료 \n");
        printf("6. 책들의 내용을 book_list.txt 에 출력 \n");
        printf("당신의 선택은 : ");
        
        // 입력 오류 방지 (scanf가 숫자가 아닌 문자를 받을 경우)
        if (scanf("%d", &user_choice) != 1) {
             printf("잘못된 입력입니다. 다시 시도해 주세요.\n");
             while (getchar() != '\n'); // 입력 버퍼 비우기
             continue;
        }

        if (user_choice == 1) { 
            /* 🚨 책을 새로 추가하는 함수 호출 (용량 검사 매개변수 추가) */
            register_book(book_list, &num_total_book, max_books);
        } else if (user_choice == 2) { 
            /* 책을 검색하는 함수 호출 */
            search_book(book_list, num_total_book);
        } else if (user_choice == 3) { 
            /* 🚨 책을 빌리는 함수 호출 (인덱스 유효성 검사 매개변수 추가) */
            borrow_book(book_list, num_total_book);
        } else if (user_choice == 4) { 
            /* 🚨 책을 반납하는 함수 호출 (인덱스 유효성 검사 매개변수 추가) */
            return_book(book_list, num_total_book);
        } else if (user_choice == 5) { 
            /* 프로그램을 종료한다. */
            printf("프로그램을 종료합니다. 안녕히 계세요!\n");
            break;
        } else if (user_choice == 6) {
             /* 책들의 내용을 book_list.txt 에 출력 */
            print_book_list(book_list, num_total_book);
        } else {
             printf("경고: 유효하지 않은 메뉴 선택입니다. (1~6)\n");
        }
    }
    
    // 3. 자원 해제
    free(book_list);
    return 0;
}

// --------------------------------------------------------
// --- 함수 구현부 ---
// --------------------------------------------------------

/* 책을 추가하는 함수*/
int register_book(BOOK *book_list, int *nth, int total_max_books) {
    // 🚨 논리 오류 수정: 최대 장서 수 초과 검사
    if (*nth >= total_max_books) {
        printf("오류: 최대 장서 수 (%d권)에 도달하여 책을 추가할 수 없습니다.\n", total_max_books);
        return -1;
    }
    
    printf("책의 이름 : ");
    // 주의: scanf("%s") 대신 fgets를 쓰는 것이 더 안전합니다.
    scanf("%s", book_list[*nth].book_name);
    printf("책의 저자 : ");
    scanf("%s", book_list[*nth].auth_name);
    printf("책의 출판사 : ");
    scanf("%s", book_list[*nth].publ_name);
    
    book_list[*nth].borrowed = 0; // 초기 상태: 대출 가능
    (*nth)++; // 전체 책 수 증가
    printf("책이 성공적으로 등록되었습니다. (현재 등록된 책 수: %d)\n", *nth);
    return 0;
} 

/* 책을 검색하는 함수 */
int search_book(BOOK *book_list, int total_num_book) {
    int user_input;
    int i;
    char user_search[30];
    int found_count = 0;

    if (total_num_book == 0) {
        printf("현재 등록된 책이 없습니다.\n");
        return 0;
    }

    printf("어느 것으로 검색 할 것인가요? \n");
    printf("1. 책 제목 검색 \n");
    printf("2. 지은이 검색 \n");
    printf("3. 출판사 검색 \n");
    scanf("%d", &user_input);
    
    printf("검색할 단어를 입력해주세요 : ");
    scanf("%s", user_search);
    printf("\n--- 검색 결과 ---\n");

    for (i = 0; i < total_num_book; i++) {
        char *target_str;
        if (user_input == 1) {
            target_str = book_list[i].book_name;
        } else if (user_input == 2) {
            target_str = book_list[i].auth_name;
        } else if (user_input == 3) {
            target_str = book_list[i].publ_name;
        } else {
            // 잘못된 검색 옵션 입력 시 반복문이 불필요하게 돌지 않도록 처리
            printf("오류: 잘못된 검색 메뉴 선택입니다.\n"); 
            return -1;
        }

        // compare 함수를 사용하여 정확히 일치하는 문자열을 검색
        if (compare(target_str, user_search)) {
            printf("번호 : %d // 책 이름 : %s // 지은이 : %s // 출판사 : %s // 대출 상태: %s\n", 
                   i, book_list[i].book_name, book_list[i].auth_name,
                   book_list[i].publ_name, book_list[i].borrowed == 1 ? "대출 중" : "대출 가능");
            found_count++;
        }
    }
    
    if (found_count == 0) {
        printf("검색 결과가 없습니다.\n");
    } else {
        printf("총 %d 권이 검색되었습니다.\n", found_count);
    }
    
    return 0;
}

/* 책을 빌리는 함수*/
int borrow_book(BOOK *book_list, int total_num_book) { 
    int book_num;

    if (total_num_book == 0) {
        printf("현재 등록된 책이 없어 대출할 수 없습니다.\n");
        return 0;
    }
    
    printf("빌릴 책의 번호를 말해주세요 (0 ~ %d) \n", total_num_book - 1);
    printf("책 번호 : ");
    scanf("%d", &book_num);

    // 🚨 치명적인 버그 수정: 배열 범위 초과 검사
    if (book_num < 0 || book_num >= total_num_book) {
        printf("오류: 유효하지 않은 책 번호입니다. 등록된 책 번호 범위 (0 ~ %d)를 확인해주세요.\n", total_num_book - 1);
        return -1;
    }

    if (book_list[book_num].borrowed == 1) {
        printf("이미 대출된 책입니다! \n");
    } else {
        printf("책이 성공적으로 대출되었습니다. \n");
        book_list[book_num].borrowed = 1;
    }

    return 0;
}

/* 책을 반납하는 함수 */
int return_book(BOOK *book_list, int total_num_book) {
    int book_num;

    if (total_num_book == 0) {
        printf("현재 등록된 책이 없습니다.\n");
        return 0;
    }
    
    printf("반납할 책의 번호를 써주세요 (0 ~ %d) \n", total_num_book - 1);
    printf("책 번호 : ");
    scanf("%d", &book_num);

    // 🚨 치명적인 버그 수정: 배열 범위 초과 검사
    if (book_num < 0 || book_num >= total_num_book) {
        printf("오류: 유효하지 않은 책 번호입니다. 등록된 책 번호 범위 (0 ~ %d)를 확인해주세요.\n", total_num_book - 1);
        return -1;
    }
    
    if (book_list[book_num].borrowed == 0) {
        printf("이미 반납되어 있는 상태입니다\n");
    } else {
        book_list[book_num].borrowed = 0;
        printf("성공적으로 반납되었습니다\n");
    }
    
    return 0;
}

/* 책들의 내용을 book_list.txt 에 출력하는 함수 */
int print_book_list(BOOK *book_list, int total_num_book) {
    FILE *fp = fopen("book_list.txt", "w");
    int i;

    if (fp == NULL) {
        // 🚨 오류 출력 개선: 표준 에러 출력으로 변경
        fprintf(stderr, "출력 오류: 'book_list.txt' 파일을 열 수 없습니다! \n"); 
        return -1;
    }
    
    fprintf(fp, "=== 도서 목록 (%d 권) ===\n", total_num_book);
    fprintf(fp, " 책 이름/저자 이름/출판사/대출 유무\n");
    fprintf(fp, "-----------------------------------\n");

    for (i = 0; i < total_num_book; i++) {
        fprintf(fp, "%s / %s / %s", book_list[i].book_name, book_list[i].auth_name,
                book_list[i].publ_name);
        
        // borrowed == 0: 대출 가능 (NO), borrowed == 1: 대출 중 (YES)
        if (book_list[i].borrowed == 0) {
            fprintf(fp, " /NO \n"); 
        } else {
            fprintf(fp, " /YES \n");
        }
    }
    
    fclose(fp);
    printf("'book_list.txt' 파일에 %d 권의 책 목록이 성공적으로 출력되었습니다.\n", total_num_book);
    
    // 🚨 반환값 누락 수정: int 함수이므로 0 반환
    return 0; 
}