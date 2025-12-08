#include <stdio.h>
#include <stdlib.h>

typedef struct SENSOR {
/* 감지 안되면 0, 감지되면 1 이다.*/
    int sensor_flag;
    int data;
} SENSOR;

int main() {
    struct SENSOR *sensor = (SENSOR *)malloc(sizeof(SENSOR));
    sensor->sensor_flag = 0;

    while (!(sensor->sensor_flag)) {
        printf("아직아니야\n");
    }

    printf("Data : %d \n", sensor->data);

}
