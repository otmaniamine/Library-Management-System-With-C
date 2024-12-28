#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_BOOKS 100
#define MAX_LEN 100

// Structures for users and books
typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
    char role[MAX_LEN]; // "Admin" or "Member"
} User;

typedef struct {
    int id;
    char title[MAX_LEN];
    char author[MAX_LEN];
    float price;
    int quantity;
} Book;

// Function declarations
void registerUser();
bool loginUser(char *role);
void adminMenu();
void memberMenu();
void addBook();
void viewBooks();
void updateBook();
void deleteBook();
void borrowBook();

// Utility functions
bool isUsernameUnique(char *username);
void saveUserToFile(User user);
void saveBookToFile(Book book);
void loadBooksFromFile();
void loadUsersFromFile();
void saveAllBooksToFile();

// Global variables
User users[MAX_USERS];
int userCount = 0;
Book books[MAX_BOOKS];
int bookCount = 0;

int main() {
    loadUsersFromFile();
    loadBooksFromFile();

    char role[MAX_LEN];
    int choice;

    do {
        printf("\nLibrary Management System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser(role)) {
                    if (strcmp(role, "Admin") == 0) {
                        adminMenu();
                    } else {
                        memberMenu();
                    }
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}

void registerUser() {
    User user;
    printf("\nEnter username: ");
    scanf("%s", user.username);
    if (!isUsernameUnique(user.username)) {
        printf("Username already exists!\n");
        return;
    }

    printf("Enter password: ");
    scanf("%s", user.password);
    printf("Enter role (Admin/Member): ");
    scanf("%s", user.role);

    saveUserToFile(user);
    users[userCount++] = user;

    printf("User registered successfully!\n");
}

bool isUsernameUnique(char *username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return false;
        }
    }
    return true;
}

void saveUserToFile(User user) {
    FILE *file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s %s %s\n", user.username, user.password, user.role);
    fclose(file);
}

bool loginUser(char *role) {
    char username[MAX_LEN], password[MAX_LEN];
    printf("\nEnter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            strcpy(role, users[i].role);
            printf("Login successful!\n");
            return true;
        }
    }

    printf("Invalid credentials!\n");
    return false;
}

void adminMenu() {
    int choice;

    do {
        printf("\nAdmin Menu\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Update Book\n");
        printf("4. Delete Book\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                updateBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);
}

void memberMenu() {
    int choice;

    do {
        printf("\nMember Menu\n");
        printf("1. View Books\n");
        printf("2. Borrow Book\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewBooks();
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);
}

void addBook() {
    Book book;
    printf("\nEnter book ID: ");
    scanf("%d", &book.id);
    printf("Enter book title: ");
    scanf("%s", book.title);
    printf("Enter book author: ");
    scanf("%s", book.author);
    printf("Enter book price: ");
    scanf("%f", &book.price);
    printf("Enter book quantity: ");
    scanf("%d", &book.quantity);

    books[bookCount++] = book;
    saveBookToFile(book);

    printf("Book added successfully!\n");
}

void saveBookToFile(Book book) {
    FILE *file = fopen("books.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%d %s %s %.2f %d\n", book.id, book.title, book.author, book.price, book.quantity);
    fclose(file);
}

void loadBooksFromFile() {
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        return; // No books file yet
    }

    while (fscanf(file, "%d %s %s %f %d", &books[bookCount].id, books[bookCount].title, books[bookCount].author, &books[bookCount].price, &books[bookCount].quantity) != EOF) {
        bookCount++;
    }

    fclose(file);
}

void loadUsersFromFile() {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        return; // No users file yet
    }

    while (fscanf(file, "%s %s %s", users[userCount].username, users[userCount].password, users[userCount].role) != EOF) {
        userCount++;
    }

    fclose(file);
}

void viewBooks() {
    printf("\nAvailable Books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d, Title: %s, Author: %s, Price: %.2f, Quantity: %d\n", books[i].id, books[i].title, books[i].author, books[i].price, books[i].quantity);
    }
}

void updateBook() {
    int id, choice;
    printf("\nEnter book ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            printf("1. Update Title\n2. Update Author\n3. Update Price\n4. Update Quantity\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter new title: ");
                    scanf("%s", books[i].title);
                    break;
                case 2:
                    printf("Enter new author: ");
                    scanf("%s", books[i].author);
                    break;
                case 3:
                    printf("Enter new price: ");
                    scanf("%f", &books[i].price);
                    break;
                case 4:
                    printf("Enter new quantity: ");
                    scanf("%d", &books[i].quantity);
                    break;
                default:
                    printf("Invalid choice!\n");
                    return;
            }

            saveAllBooksToFile();
            printf("Book updated successfully!\n");
            return;
        }
    }

    printf("Book not found!\n");
}

void deleteBook() {
    int id;
    printf("\nEnter book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            saveAllBooksToFile();
            printf("Book deleted successfully!\n");
            return;
        }
    }

    printf("Book not found!\n");
}

void borrowBook() {
    int id, quantity;
    printf("\nEnter book ID to borrow: ");
    scanf("%d", &id);
    printf("Enter quantity to borrow: ");
    scanf("%d", &quantity);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            if (books[i].quantity >= quantity) {
                books[i].quantity -= quantity;
                saveAllBooksToFile();
                printf("Book borrowed successfully!\n");
            } else {
                printf("Not enough stock available!\n");
            }
            return;
        }
    }

    printf("Book not found!\n");
}

void saveAllBooksToFile() {
    FILE *file = fopen("books.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%d %s %s %.2f %d\n", books[i].id, books[i].title, books[i].author, books[i].price, books[i].quantity);
    }

    fclose(file);
}
