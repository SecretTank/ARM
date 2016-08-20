#ifndef DEFINE
#define DEFINE

#include <QVector>

#define sceen_size 173

typedef struct oscope_data_t {
    QVector<int> data;
    int buffer; //number of unproccessed data
} oscope_data;

void *serial_main(void *arg);

#endif // DEFINE

