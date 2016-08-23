#ifndef DEFINE
#define DEFINE

#include <QVector>

#define screen_res 300
#define screen_size 1020

typedef struct oscope_data_t {
    QVector<int> data;
    int buffer; //number of unproccessed data
} oscope_data;

void *serial_main(void *arg);

#endif // DEFINE

