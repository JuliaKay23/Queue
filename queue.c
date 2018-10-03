#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "cda.h"

struct queue {
    CDA *ds;
    int debug;
    void (*display)(void *, FILE *);
    int size;
};

QUEUE *newQUEUE(void) {
    QUEUE *items = malloc(sizeof(QUEUE));
    items->ds = newCDA();
    items->debug = 0;
    items->display = NULL;
    items->size = 0;
    assert(items != 0);
    return items;
}

void  setQUEUEdisplay(QUEUE *items,void (*display)(void *,FILE *)){
    items->display = display;
    setCDAdisplay(items->ds,display);
}

void  setQUEUEfree(QUEUE *items,void (*free)(void *)){
    setCDAfree(items->ds,free);
}

void  enqueue(QUEUE *items,void *value){
    insertCDA(items->ds,sizeCDA(items->ds),value);
    items->size += 1;
}

void *dequeue(QUEUE *items){
    assert(sizeCDA(items->ds) > 0);
    items->size -= 1;
    return removeCDA(items->ds,0);
}

void *peekQUEUE(QUEUE *items){
    assert(sizeCDA(items->ds) > 0);
    return getCDA(items->ds,0);
}

void  displayQUEUE(QUEUE *items,FILE *fp){
    if (items->debug == 0) {
        if (sizeCDA(items->ds) == 0) {
            fprintf(fp, "<>");
        }
        else if (sizeCDA(items->ds) > 0) {
            fprintf(fp, "<");
            if (items->display == NULL) {
                for (int i = 0; i < sizeCDA(items->ds) - 1; i++) {
                    fprintf(fp, "@%p,", getCDA(items->ds, i));
                }
                fprintf(fp, "@%p", getCDA(items->ds, sizeCDA(items->ds) - 1));
            }
            else if (items->display != NULL) {
                for (int i = 0; i < sizeCDA(items->ds) - 1; i++) {
                    items->display(getCDA(items->ds, i), fp);
                    fprintf(fp, ",");
                }
                items->display(getCDA(items->ds, sizeCDA(items->ds) - 1), fp);
            }
            fprintf(fp, ">");
        }
    }
    else if (items->debug == 1 || items->debug == 2) {
        displayCDA(items->ds, fp);
    }
}

int   debugQUEUE(QUEUE *items,int level){
    int old = items->debug;

    if (level == 1) {
        debugCDA(items->ds,0);
    }

    else if (level == 2) {
        debugCDA(items->ds, 1);
    }
    items->debug = level;
    return old;
}

void  freeQUEUE(QUEUE *items) {
    freeCDA(items->ds);
    free(items);
}

int   sizeQUEUE(QUEUE *items){
    return sizeCDA(items->ds);
}