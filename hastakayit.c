#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hasta yapýsý tanýmý (HL7 formatýna uygun temel bilgiler)
typedef struct Patient {
    char id[10];
    char name[50];
    char birthDate[11]; // YYYY-MM-DD formatýnda
    char gender[2]; // M veya F
    int priority; // Öncelik (1 - Yüksek, 5 - Düþük)
    char triageCode[10]; // Triage kodu (Kýrmýzý, Turuncu, Sarý, Yeþil, Siyah)
    char prescription[100]; // Reçete bilgisi
    struct Patient* next;
} Patient;

// Baðlý liste için baþ ve son pointerlar
Patient* head = NULL;

// Yeni hasta ekle
void addPatient(char* id, char* name, char* birthDate, char* gender, int priority, char* triageCode) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    strcpy(newPatient->id, id);
    strcpy(newPatient->name, name);
    strcpy(newPatient->birthDate, birthDate);
    strcpy(newPatient->gender, gender);
    newPatient->priority = priority;
    strcpy(newPatient->triageCode, triageCode);
    strcpy(newPatient->prescription, ""); // Baþlangýçta reçete yok
    newPatient->next = NULL;

    // Önceliðe göre listeye ekleme (öncelik sýralý baðlý liste)
    if (head == NULL || head->priority > priority) {
        newPatient->next = head;
        head = newPatient;
    } else {
        Patient* current = head;
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }
        newPatient->next = current->next;
        current->next = newPatient;
    }
}

// Reçete oluþtur
void createPrescription(char* id, char* prescription) {
    Patient* current = head;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            strcpy(current->prescription, prescription);
            printf("Reçete oluþturuldu: %s\n", prescription);
            break;
        }
        current = current->next;
    }
}

// Hasta listesini yazdýr
void printPatients() {
    Patient* current = head;
    printf("\n--- Hasta Listesi ---\n");
    while (current != NULL) {
        printf("ID: %s, Ad: %s, Dogum Tarihi: %s, Cinsiyet: %s, Öncelik: %d, Triage Kodu: %s, Recete: %s\n",
               current->id, current->name, current->birthDate, current->gender, current->priority, current->triageCode, current->prescription);
        current = current->next;
    }
}

// Hafýzayý temizle
void freePatients() {
    Patient* current = head;
    while (current != NULL) {
        Patient* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    addPatient("P001", "Yakisikli Guvenlik", "1990-05-12", "M", 2, "Kirmizi");
    addPatient("P002", "Hurrem Sultan", "1985-09-23", "F", 1, "Turuncu");
    addPatient("P003", "Walter White", "2000-11-05", "M", 3, "Sari");
    addPatient("P004", "Kralice Elizabeth", "1995-04-15", "M", 4, "Yesil");
    addPatient("P005", "Kanye West", "1980-08-30", "M", 5, "Siyah");

    printPatients();

    // Reçete oluþturma
    createPrescription("P002", "Parol 500mg, gunde 2 kez");

    printPatients();

    freePatients();
    return 0;
}

