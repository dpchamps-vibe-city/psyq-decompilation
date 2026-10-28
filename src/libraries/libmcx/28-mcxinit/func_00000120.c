#include "common.h"
#include "libmcx_init.h"

static void func_00000120(int priority, McxInterruptRecord *record) {
    McxInterruptQueue *queue;
    McxInterruptRecord *tail;

    queue = &(*D_00000184)[priority];
    tail = queue->head;
    if (tail == NULL) {
        queue->head = record;
    } else {
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = record;
    }
    record->next = NULL;
}
