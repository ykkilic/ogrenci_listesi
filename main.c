#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

typedef struct Ogrenci {
    char *isim;
    char *soyisim;
    int ogrenci_no;
    int not;
} ogrenci_t;

typedef struct Node {
    ogrenci_t *data;
    struct Node *prev;
    struct Node *next;
} node_t;

typedef struct {
    node_t *head;
    node_t *tail;
} LinkedList;

LinkedList *createLinkedList() {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void pushFront(LinkedList *list, ogrenci_t *ogrenci) {
    node_t *newNode = malloc(sizeof(node_t));
    newNode->data = ogrenci;
    newNode->prev = NULL;
    newNode->next = list->head;
    if (list->head != NULL) {
        list->head->prev = newNode;
    } else {
        list->tail = newNode;
    }

    list->head = newNode;
}

void pushBack(LinkedList *list, ogrenci_t *ogrenci) {
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    newNode->data = ogrenci;
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = newNode;
    } else {
        list->head = newNode;
    }
    list->tail = newNode;
}

void popFront(LinkedList *list) {
    if (list->head == NULL) {
        return;
    }
    node_t *temp = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    free(temp);
}

void popBack(LinkedList *list) {
    if (list->tail == NULL) {
        return;
    }
    node_t *temp = list->tail;
    list->tail = list->tail->prev;
    list->tail->next = NULL;
    free(temp);
}

void deleteNode(LinkedList *list, ogrenci_t *data) {
    if (list->head == NULL) {
        return;
    }
    if (list->head->data == data) {
        popFront(list);
    } else if (list->tail->data == data) {
        popBack(list);
    } else {
        node_t *current = list->head;

        while (current != NULL) {
            if (current->data == data) {
                // Bağlantıları güncelle
                if (current->prev != NULL)
                    current->prev->next = current->next;

                if (current->next != NULL)
                    current->next->prev = current->prev;

                // Belleği serbest bırak
                free(current->data); // ogrenci_t
                return; // silme tamamlandı
            } else {
                current = current->next;
            }
        }
    }
}

void print_list(LinkedList *list) {
    node_t *current = list->head;
    while (current != NULL) {
        printf("--------------------------------------\n");
        printf("%s\n", current->data->isim);
        printf("%s\n", current->data->soyisim);
        printf("%d\n", current->data->ogrenci_no);
        printf("%d\n", current->data->not);
        printf("--------------------------------------\n");
        current = current->next;
    }
}

float ortalama_al(LinkedList *list) {
    node_t *current = list->head;
    int toplam = 0;
    int sayi = 0;
    while (current != NULL) {
        toplam += current->data->not;
        sayi++;
        current = current->next;
    }
    float ortalama = (float)toplam/(float)sayi;
    return ortalama;
}

int main(void) {
    LinkedList *list = createLinkedList();


    struct Ogrenci *ogrenci = malloc(sizeof(ogrenci_t));
    ogrenci->isim = "Yigit Kagan";
    ogrenci->soyisim = "Kilic";
    ogrenci->ogrenci_no = 618;
    ogrenci->not = 100;

    pushBack(list, ogrenci);

    // 1. öğrenci
    ogrenci_t *ogrenci1 = malloc(sizeof(ogrenci_t));
    ogrenci1->isim = "Furkan Ali";
    ogrenci1->soyisim = "Kilic";
    ogrenci1->ogrenci_no = 610;
    ogrenci1->not = 95;

    pushBack(list, ogrenci1);

    ogrenci_t *ogrenci3 = malloc(sizeof(ogrenci_t));
    ogrenci3->isim = "Ayse";
    ogrenci3->soyisim = "Yilmaz";
    ogrenci3->ogrenci_no = 102;
    ogrenci3->not = 90;

    pushBack(list, ogrenci3);

    ogrenci_t *ogrenci4 = malloc(sizeof(ogrenci_t));
    ogrenci4->isim = "Mehmet";
    ogrenci4->soyisim = "Kaya";
    ogrenci4->ogrenci_no = 103;
    ogrenci4->not = 70;

    pushBack(list, ogrenci4);

    deleteNode(list, ogrenci3);

    print_list(list);

    float ortalama = ortalama_al(list);
    printf("%f\n", ortalama);

    free(list);
    return 0;
}