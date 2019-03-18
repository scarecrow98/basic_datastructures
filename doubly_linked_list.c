#include "stdio.h"
#include "stdlib.h"

typedef struct date {
    int year;
    int month;
    int day;
    struct date *prev;
    struct date *next;
} Date;

typedef struct DateList {
    struct date *head;
    int size;
} DateList;

DateList *create_list() {
    DateList *list = (DateList *) malloc(sizeof(DateList));
    list->head = NULL;
    list->size = 0;

    return list;
}

Date *create_date(int year, int month, int day) {
    Date *date = (Date *) malloc(sizeof(Date));
    date->year = year;
    date->month = month;
    date->day = day;
    date->next = NULL;
    date->prev = NULL;

    return date;
}

void insert(DateList *list, int year, int month, int day) {
    if (!list->head) {
        list->head = create_date(year, month, day);
    } else {
        Date *act = list->head;
        while (act->next != NULL) {
            act = act->next;
        }

        act->next = create_date(year, month, day);
        act->next->prev = act;
    }
    
    list->size++;
    printf("Date %d.%d.%d added.\n", year, month, day);
}

void insert_front(DateList *list, int year, int month, int day) {
    if (!list->head) {
        list->head = create_date(year, month, day);
    } else {
        Date *new_date = create_date(year, month, day);
        new_date->next = list->head;
        list->head = new_date;
    }

    list->size++;
    printf("Date %d.%d.%d added.\n", year, month, day);
}

void print_list(DateList *list) {
    Date *act = list->head;

    while (act != NULL) {
        printf("\t%d.%d.%d\n", act->year, act->month, act->day);
        act = act->next;
    }
}

Date *get(DateList *list, int index) {
    int i = 0;
    Date *act = list->head;

    while (act != NULL && i < index) {
        act = act->next;
        i++;
    }

    return i == index ? act : NULL;
}

void delete(DateList *list, int year, int month, int day) {
    Date *act = list->head;

    while (act != NULL && !(act->year == year && act->month == month && act->day == day)) {
        act = act->next;
    }

    if (act) {
        if (act == list->head) {
            list->head = act->next;
        } else {
            act->prev->next = act->next;
        }
        printf("Date %d.%d.%d deleted.\n", act->year, act->month, act->day);
        free(act);
    } else {
        printf("Date you want to delete is not found.\n");
    }
}

void list_delete(DateList *list) {
    Date *act = list->head;
    Date *next = act;

    while (act != NULL) {
        next = act->next;
        free(act);
        act = next;
    }
}

int main() {
    DateList *list = create_list();

    insert(list, 2019, 8, 21);
    insert(list, 2019, 9, 21);
    insert_front(list, 2019, 7, 21);
    insert_front(list, 2019, 6, 21);

    printf("Elements of the lists:\n");
    print_list(list);

    printf("Element at index %d:\n", 1);
    Date *d = get(list, 1);
    if (!d) printf("Index is out of bounds.\n");
    else printf("Selected date is: %d.%d.%d\n", d->year, d->month, d->day);

    delete(list, 2019, 6, 21);
    delete(list, 2019, 11, 21);
    print_list(list);

    printf("Size of the list:%d\n", list->size);

    list_delete(list);
    return 0;
}