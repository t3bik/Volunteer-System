#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 1000
#define MAX_EVENTS 1000
#define MAX_TASKS 1000

// Input validation function
void getInput(char *prompt, char *input, int maxLength) {
    while (1) {
        printf("%s", prompt);
        fgets(input, maxLength, stdin);
        if (strlen(input) > 1) { // Ensure input is not just a newline
            input[strcspn(input, "\n")] = 0; // Remove trailing newline
            break;
        } else {
            printf("Bu alan boş bırakılamaz. Lütfen geçerli bir giriş yapın.\n");
        }
    }
}

typedef struct {
    char username[50];
    char password[50];
    char role[10]; // "volunteer" or "organizer"
    char name[50];
    int age;
    char contact[50];
    char interests[100];
} User;

typedef struct {
    char eventName[50];
    char date[20];
    char location[50];
    char tasks[MAX_TASKS][50];
    int taskAvailability[MAX_TASKS];
    int taskCount;
} Event;

User users[MAX_USERS];
Event events[MAX_EVENTS];
int userCount = 0;
int eventCount = 0;

void saveUsersToFile() {
    FILE *file = fopen("users.txt", "w");
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s %s %s %d %s %s\n", users[i].username, users[i].password, users[i].role, users[i].name, users[i].age, users[i].contact, users[i].interests);
    }
    fclose(file);
}

void loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file) {
        while (fscanf(file, "%s %s %s %s %d %s %s\n", users[userCount].username, users[userCount].password, users[userCount].role, users[userCount].name, &users[userCount].age, users[userCount].contact, users[userCount].interests) != EOF) {
            userCount++;
        }
        fclose(file);
    }
}

void saveEventsToFile() {
    FILE *file = fopen("events.txt", "w");
    for (int i = 0; i < eventCount; i++) {
        fprintf(file, "%s %s %s %d\n", events[i].eventName, events[i].date, events[i].location, events[i].taskCount);
        for (int j = 0; j < events[i].taskCount; j++) {
            fprintf(file, "%s %d\n", events[i].tasks[j], events[i].taskAvailability[j]);
        }
    }
    fclose(file);
}

int isEventDuplicate(Event newEvent) {
    for (int i = 0; i < eventCount; i++) {
        if (strcmp(events[i].eventName, newEvent.eventName) == 0 && strcmp(events[i].date, newEvent.date) == 0 && strcmp(events[i].location, newEvent.location) == 0) {
            return 1;
        }
    }
    return 0;
}

void loadEventsFromFile() {
    FILE *file = fopen("events.txt", "r");
    if (file) {
        while (1) {
            Event tempEvent;
            if (fscanf(file, "%s %s %s %d\n", tempEvent.eventName, tempEvent.date, tempEvent.location, &tempEvent.taskCount) == EOF) {
                break;
            }

            for (int j = 0; j < tempEvent.taskCount; j++) {
                fscanf(file, "%s %d\n", tempEvent.tasks[j], &tempEvent.taskAvailability[j]);
            }

            if (!isEventDuplicate(tempEvent)) {
                events[eventCount++] = tempEvent;
            }
        }
        fclose(file);
    }
}

int loginUser(char role[]) {
    char username[50], password[50];
    getInput("\nKullanıcı adı: ", username, 50);
    getInput("Şifre: ", password, 50);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0 && strcmp(users[i].role, role) == 0) {
            printf("\nBaşarıyla giriş yapıldı. Hoş geldiniz, %s!\n", users[i].name);
            return 1;
        }
    }
    printf("\nGiriş başarısız! Lütfen bilgilerinizi kontrol edin.\n");
    return 0;
}

void registerUser() {
    char ageStr[10];
    printf("\nYeni bir kullanıcı kaydediliyor...\n");
    getInput("Kullanıcı adı: ", users[userCount].username, 50);
    getInput("Şifre: ", users[userCount].password, 50);
    getInput("Rol (volunteer/organizer): ", users[userCount].role, 10);
    getInput("Ad: ", users[userCount].name, 50);
    getInput("Yaş: ", ageStr, 10);
    users[userCount].age = atoi(ageStr);
    getInput("İletişim: ", users[userCount].contact, 50);
    getInput("İlgi alanları: ", users[userCount].interests, 100);
    userCount++;
    saveUsersToFile();
    printf("Kullanıcı başarıyla kaydedildi!\n");
}

void listEvents() {
    printf("\nMevcut etkinlikler:\n");
    for (int i = 0; i < eventCount; i++) {
        printf("%d. %s (%s, %s)\n", i + 1, events[i].eventName, events[i].date, events[i].location);
        for (int j = 0; j < events[i].taskCount; j++) {
            printf("  Görev: %s - Durum: %s\n", events[i].tasks[j], events[i].taskAvailability[j] ? "Müsait" : "Dolu");
        }
    }
}

void assignTaskToVolunteer() {
    int eventIndex, taskIndex;
    char eventStr[10], taskStr[10];
    printf("\nGörev atama için etkinlik seçin: \n");
    listEvents();
    getInput("Etkinlik numarası: ", eventStr, 10);
    eventIndex = atoi(eventStr) - 1;

    printf("Görev seçin: \n");
    for (int i = 0; i < events[eventIndex].taskCount; i++) {
        printf("%d. %s - Durum: %s\n", i + 1, events[eventIndex].tasks[i], events[eventIndex].taskAvailability[i] ? "Müsait" : "Dolu");
    }
    getInput("Görev numarası: ", taskStr, 10);
    taskIndex = atoi(taskStr) - 1;

    if (events[eventIndex].taskAvailability[taskIndex]) {
        events[eventIndex].taskAvailability[taskIndex] = 0;
        printf("Görev başarıyla atandı!\n");
        saveEventsToFile();
    } else {
        printf("Bu görev zaten dolu!\n");
    }
}

void organizerActions() {
    int choice;
    char choiceStr[10];
    while (1) {
        printf("\n1. Etkinlik Oluştur\n2. Görev Ata\n3. Çıkış\nSeçiminizi yapın: ");
        getInput("", choiceStr, 10);
        choice = atoi(choiceStr);

        switch (choice) {
            case 1:
                printf("\nYeni bir etkinlik oluşturuluyor...\n");
                getInput("Etkinlik adı: ", events[eventCount].eventName, 50);
                getInput("Tarih (gg/aa/yyyy): ", events[eventCount].date, 20);
                getInput("Konum: ", events[eventCount].location, 50);
                char taskCountStr[10];
                getInput("Kaç görev eklemek istiyorsunuz? ", taskCountStr, 10);
                events[eventCount].taskCount = atoi(taskCountStr);

                for (int i = 0; i < events[eventCount].taskCount; i++) {
                    printf("Görev %d: ", i + 1);
                    getInput("", events[eventCount].tasks[i], 50);
                    events[eventCount].taskAvailability[i] = 1;
                }

                eventCount++;
                saveEventsToFile();
                printf("Etkinlik başarıyla oluşturuldu!\n");
                break;
            case 2:
                assignTaskToVolunteer();
                break;
            case 3:
                printf("Çıkış yapılıyor...\n");
                return;
            default:
                printf("Geçersiz seçim!\n");
        }
    }
}

void volunteerActions() {
    int choice;
    char choiceStr[10];
    while (1) {
        printf("\n1. Müsait Görevlere Kendini Ata\n2. Çıkış\nSeçiminizi yapın: ");
        getInput("", choiceStr, 10);
        choice = atoi(choiceStr);

        switch (choice) {
            case 1:
                listEvents();
                assignTaskToVolunteer();
                break;
            case 2:
                printf("Çıkış yapılıyor...\n");
                return;
            default:
                printf("Geçersiz seçim!\n");
        }
    }
}

int main() {
    loadUsersFromFile();
    loadEventsFromFile();

    int userType;
    char userTypeStr[10];
    printf("\nGönüllü Randevu Sistemi\n");
    printf("1. Kayıt Ol\n2. Giriş Yap\n3. Çıkış\nSeçiminizi yapın: ");
    getInput("", userTypeStr, 10);
    userType = atoi(userTypeStr);

    if (userType == 1) {
        registerUser();
        return main();
    } else if (userType == 2) {
        printf("Rol seçin: \n1. Gönüllü\n2. Organizatör\nSeçiminizi yapın: ");
        getInput("", userTypeStr, 10);
        userType = atoi(userTypeStr);

        if (userType == 1 && loginUser("volunteer")) {
            volunteerActions();
        } else if (userType == 2 && loginUser("organizer")) {
            organizerActions();
        } else {
            printf("Giriş başarısız veya geçersiz seçim!\n");
        }
    } else {
        printf("Sistemden çıkılıyor...\n");
    }

    saveUsersToFile();
    saveEventsToFile();
    return 0;
}
