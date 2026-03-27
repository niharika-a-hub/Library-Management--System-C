#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold book data
struct Book {
    int id;
    char title[100];
    char author[50];
    int isIssued;    // 0 = Available, 1 = Issued
    int issueCount;  // Tracks popularity
};

const char* DB = "library.dat";

// Function Prototypes
void login();
void addBook();
void displayBooks();
void searchBook();
void issueReturnBook(int mode);
void deleteBook();
void clearBuffer();

int main() {
    login(); // Secure the system
    int choice;

    while(1) {
        printf("\n====================================");
        printf("\n   ULTIMATE LIBRARY SYSTEM (C)");
        printf("\n====================================");
        printf("\n1. Add New Book");
        printf("\n2. View All Books");
        printf("\n3. Search by Title");
        printf("\n4. Issue a Book");
        printf("\n5. Return a Book");
        printf("\n6. Delete a Record");
        printf("\n7. Exit");
        printf("\n------------------------------------");
        printf("\nSelect Option: ");
        
        if (scanf("%d", &choice) != 1) {
            clearBuffer();
            continue;
        }

        switch(choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueReturnBook(1); break;
            case 5: issueReturnBook(0); break;
            case 6: deleteBook(); break;
            case 7: exit(0);
            default: printf("\n[!] Invalid Choice.");
        }
    }
    return 0;
}

void login() {
    char pass[20];
    printf("Enter Admin Password: ");
    scanf("%s", pass);
    if (strcmp(pass, "admin123") != 0) {
        printf("Incorrect password. Access Denied.\n");
        exit(0);
    }
}

void clearBuffer() {
    while (getchar() != '\n');
}

void addBook() {
    FILE *fp = fopen(DB, "ab");
    struct Book b;

    printf("\nEnter Book ID (Numeric): ");
    scanf("%d", &b.id);
    clearBuffer();

    printf("Enter Title: ");
    fgets(b.title, 100, stdin);
    b.title[strcspn(b.title, "\n")] = 0;

    printf("Enter Author: ");
    fgets(b.author, 50, stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    b.isIssued = 0;
    b.issueCount = 0;

    fwrite(&b, sizeof(struct Book), 1, fp);
    fclose(fp);
    printf("\n[+] Book added to record successfully!");
}

void displayBooks() {
    FILE *fp = fopen(DB, "rb");
    struct Book b;

    if (!fp) {
        printf("\n[!] No records found. Add a book first.");
        return;
    }

    printf("\n%-5s %-25s %-20s %-10s %-5s", "ID", "Title", "Author", "Status", "Reads");
    printf("\n----------------------------------------------------------------------");
    
    while(fread(&b, sizeof(struct Book), 1, fp)) {
        printf("\n%-5d %-25s %-20s %-10s %-5d", 
               b.id, b.title, b.author, 
               b.isIssued ? "OUT" : "IN", b.issueCount);
    }
    fclose(fp);
    printf("\n");
}

void searchBook() {
    FILE *fp = fopen(DB, "rb");
    struct Book b;
    char query[100];
    int found = 0;

    printf("\nEnter Title or Keyword: ");
    clearBuffer();
    fgets(query, 100, stdin);
    query[strcspn(query, "\n")] = 0;

    while(fread(&b, sizeof(b), 1, fp)) {
        if(strstr(strlwr(b.title), strlwr(query))) { // Case-insensitive partial match
            printf("\nFOUND: ID %d | %s by %s [%s]", 
                   b.id, b.title, b.author, b.isIssued ? "Borrowed" : "Available");
            found = 1;
        }
    }
    if(!found) printf("\n[!] No matches found.");
    fclose(fp);
}

void issueReturnBook(int mode) {
    FILE *fp = fopen(DB, "rb+");
    struct Book b;
    int id, found = 0;

    printf("\nEnter Book ID: ");
    scanf("%d", &id);

    while(fread(&b, sizeof(b), 1, fp)) {
        if(b.id == id) {
            found = 1;
            b.isIssued = mode;
            if(mode == 1) b.issueCount++; // Increment popularity on issue
            
            fseek(fp, -sizeof(struct Book), SEEK_CUR);
            fwrite(&b, sizeof(struct Book), 1, fp);
            break;
        }
    }
    fclose(fp);
    if(found) printf("\n[+] Record updated successfully!");
    else printf("\n[!] Book ID not found.");
}

void deleteBook() {
    FILE *fp = fopen(DB, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Book b;
    int id, found = 0;

    printf("\nEnter Book ID to DELETE: ");
    scanf("%d", &id);

    while(fread(&b, sizeof(b), 1, fp)) {
        if(b.id == id) {
            found = 1;
        } else {
            fwrite(&b, sizeof(b), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);

    remove(DB);
    rename("temp.dat", DB);

    if(found) printf("\n[+] Record deleted permanently.");
    else printf("\n[!] ID not found.");
}
