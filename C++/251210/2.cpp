//p88 Q2
/* 
수학 관련 소프트웨어를 만드는 회사에서 의뢰가 들어왔습니다. 중학생용 기하학 소프트웨워를
만드는 것인데요, 클래스는 총 두 개로 하나는 Point 로 점에 관한 정보를 담는 것이고 다른 하나는
Geometry 로 점들을 가지고 연산을 하는 클래스 입니다. 즉 아래와 같은 두 클래스의 함수들을
모두 정의하세요 (난이도 : 上)
*/

#include <iostream>
#include <cmath>
#define Want_size 100

using namespace std;

class Point {
    int x, y;
    public:
        Point(int pos_x, int pos_y) {
            x = pos_x;
            y = pos_y;
        };

        void SetPoint(int x_, int y_) {
            x = x_;
            y = y_;
        };

        int returnX() {
            return x;
        }

        int returnY() {
            return y;
        }
};

class Geometry {
    // 점 100 개를 보관하는 배열.
    Point* point_array[Want_size];
    public:
        Geometry(Point **point_list) {
            for(int i = 0; i < Want_size; i++) {
                point_array[i] = point_list[i];
            }
            
        };
        Geometry() {
            point_array[0] = new Point(0, 0);
            for(int i = 1; i < Want_size; i++) {
                point_array[i] = 0;
            }
        };
        
        void AddPoint(const Point &point) {
            int i = 0;
            while(*(point_array + i) != NULL) {
                i++;
            }

            if(i > Want_size - 1) {
                printf("CANNOT add the point.\n");
                return;
            }

            else {
                point_array[i] = new Point(point);
            }
            
        };
        
        // 모든 점들 간의 거리를 출력하는 함수 입니다.
        void PrintDistance() {
            int arr_size = 0;
            while(*(point_array + arr_size) != NULL) {
                arr_size++;
            }

            for(int i = 0; i < arr_size; i++) {
                for(int j = i + 1; j < arr_size; j++) {
                    float Distance = sqrtf(pow(point_array[i]->returnX() - point_array[j]->returnX(), 2) + pow(point_array[i]->returnY() - point_array[j]->returnY() , 2));
                    printf("%05.2f", Distance);
                    cout << "가 점 " << i << "와 " << j << " 사이의 거리다 이새기야" << endl;
                }
            }
        };

        // 모든 점들을 잇는 직선들 간의 교점의 수를 출력해주는 함수 입니다.
        // 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
        // 이라고 할 때 임의의 다른 두 점 (x1, y1) 과 (x2, y2) 가 f(x,y)=0 을 기준으로
        // 서로 다른 부분에 있을 조건은 f(x1, y1) * f(x2, y2) <= 0 이면 됩니다.
        void PrintNumMeets() {
            int arr_size = 0;
            int cross_point = 0;
            while(*(point_array + arr_size) != NULL) {
                arr_size++;
            }
            int *Calculated = (int *)malloc(sizeof(int) * arr_size);
            for(int i = 0; i < arr_size - 2; i++) {
                for(int j = i + 1; j < arr_size - 1; j++) {
                    for(int k = j + 1; k < arr_size; k++) {
                        int x1 = point_array[i]->returnX();
                        int x2 = point_array[j]->returnX();
                        int y1 = point_array[i]->returnY();
                        int y2 = point_array[j]->returnY();
                        int a = y1 - y2;
                        int b = x2 - x1;
                        int c = (-1) * (a * x1 + b * y1);
                        
                        if(a * point_array[k]->returnX() + b * point_array[k]->returnY() == (-1) * c) {
                            cout << "InF" << endl;
                            return;
                        }

                        else {
                            if(Calculated[i] == 0) {
                                Calculated[i] = 1;
                                cross_point++;
                            }
                            if(Calculated[j] == 0) {
                                Calculated[j] = 1;
                                cross_point++;
                            }
                            cross_point++;
                        }
                    }
                }
            }

            printf("%d", cross_point + 1);
        };
};

int main() {
    Point *P1 = new Point(0, 0);
    Point *P2 = new Point(10, 0);
    Point *P3 = new Point(0, 10);
    Point *P4 = new Point(10, 10);

    Point *PArr[100] = {P1, P2, P3, P4};

    Geometry G1(PArr);
    Point P5(4, 5);
    G1.AddPoint(P5);
    
    G1.PrintDistance();
    G1.PrintNumMeets();
    
    delete P1;
    delete P2;
    delete P3;
    delete P4;

    return 0;
}

