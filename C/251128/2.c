#include <stdio.h>
#include <string.h>

typedef struct {
    char word[50];
    char meaning[200];
    char example[200];
} DictEntry;

int main() {
    // Sample dictionary data
    DictEntry dict[] = {
        {"사랑", "누군가를 좋아하고 소중히 여기는 감정", "나는 너를 사랑한다."},
        {"희망", "좋은 일이 일어날 것으로 기대함", "희망을 가지고 열심히 공부했다."},
        {"용기", "두려움을 이기고 앞으로 나아가는 힘", "용기를 내어 새로운 도전을 시작했다."}
    };
    
    int dict_size = sizeof(dict) / sizeof(dict[0]);
    char search_word[50];
    
    printf("단어를 입력하세요: ");
    scanf("%s", search_word);
    
    for (int i = 0; i < dict_size; i++) {
        if (strcmp(dict[i].word, search_word) == 0) {
            printf("\n[%s]\n", dict[i].word);
            printf("뜻: %s\n", dict[i].meaning);
            printf("예문: %s\n", dict[i].example);
            return 0;
        }
    }
    
    printf("찾는 단어가 없습니다.\n");
    return 0;
}