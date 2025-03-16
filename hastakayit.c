#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hasta yap�s� tan�m� (HL7 format�na uygun temel bilgiler)
typedef struct Patient {
    char id[10];
    char name[50];
    char birthDate[11]; // YYYY-MM-DD format�nda
    char gender[2]; // M veya F
    int priority; // �ncelik (1 - Y�ksek, 5 - D���k)
    char triageCode[10]; // Triage kodu (K�rm�z�, Turuncu, Sar�, Ye�il, Siyah)
    char prescription[100]; // Re�ete bilgisi
    struct Patient* next;
} Patient;

// Ba�l� liste i�in ba� ve son pointerlar
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
    strcpy(newPatient->prescription, ""); // Ba�lang��ta re�ete yok
    newPatient->next = NULL;

    // �nceli�e g�re listeye ekleme (�ncelik s�ral� ba�l� liste)
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

// Re�ete olu�tur
void createPrescription(char* id, char* prescription) {
    Patient* current = head;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            strcpy(current->prescription, prescription);
            printf("Re�ete olu�turuldu: %s\n", prescription);
            break;
        }
        current = current->next;
    }
}

// Hasta listesini yazd�r
void printPatients() {
    Patient* current = head;
    printf("\n--- Hasta Listesi ---\n");
    while (current != NULL) {
        printf("ID: %s, Ad: %s, Dogum Tarihi: %s, Cinsiyet: %s, �ncelik: %d, Triage Kodu: %s, Recete: %s\n",
               current->id, current->name, current->birthDate, current->gender, current->priority, current->triageCode, current->prescription);
        current = current->next;
    }
}

// Haf�zay� temizle
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

    // Re�ete olu�turma
    createPrescription("P002", "Parol 500mg, gunde 2 kez");

    printPatients();

    freePatients();
    return 0;
}

