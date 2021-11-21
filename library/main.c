#include <stdio.h>
#include <string.h>

#define SIZE 25
#define BOOKS 15

void readFile();

void menu();

void insertBook();

void deleteBook();

void searchId();

void searchName();

void sortName();

void unsorted();

int linerSearch(int key);

void sortedArr();

struct book {
    int id;
    char name[SIZE];
    unsigned int quantity;
} bookArr[BOOKS], bookCopy[BOOKS];

int bookCounter = 0;

int main() {
    puts("Welcome to our Library!");

    readFile();
    menu();

    return 0;
}

void readFile() {
    FILE *rfPtr;
    if ((rfPtr = fopen("library.txt", "r")) == NULL)
        puts("Fill is not exist");
    else {
        bookCounter = 0;
        while (!feof(rfPtr)) {
            fscanf(rfPtr, "%10d%24s%10u", &bookArr[bookCounter].id, bookArr[bookCounter].name,
                   &bookArr[bookCounter].quantity);

            ++bookCounter;
        }
        fclose(rfPtr);
    }
}

void menu() {
    puts("");
    puts("Menu:");
    puts("     1) Insert a book.");
    puts("     2) Delete a book by id.");
    puts("     3) Search a book by id.");
    puts("     4) Search a book by name.");
    puts("     5) Display all books sorted by name.");
    puts("     6) Display all unsorted.");
    puts("");

    int choice;
    printf("Please choose what would you do: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            insertBook();
            break;

        case 2:
            deleteBook();
            break;

        case 3:
            searchId();
            break;

        case 4:
            searchName();
            break;

        case 5:
            sortName();
            break;

        case 6:
            unsorted();
            break;

        default:
            puts("Invalid number\n");
            menu();
            break;
    }

    char repeat;
    printf("\nDo you want to try another operation?\npress (Y/y) for 'yes' or (N/n) for 'no': ");
    getc(stdin);
    scanf("%c", &repeat);
    puts("");
    if (repeat == 'y' || repeat == 'Y') {
        puts("=======================================================================================\n");
        menu();
    }
}

void insertBook() {
    FILE *bfPtr;
    if ((bfPtr = fopen("library.txt", "a")) == NULL)
        puts("File is not exist");
    else {
        unsigned int number;
        printf("Enter number of books you would to input: ");
        scanf("%u", &number);
        int count = 1;
        while (count <= number) {
            printf("\nEnter id of book[%d]: ", count);
            scanf("%d", &bookArr[bookCounter].id);
            printf("\nEnter name of book[%d]: ", count);
            getc(stdin);
            gets(bookArr[bookCounter].name);
            printf("\nEnter quantity of book[%d]: ", count);
            scanf("%u", &bookArr[bookCounter].quantity);

            fprintf(bfPtr, "\n%10d %24s %10u", bookArr[bookCounter].id, bookArr[bookCounter].name,
                    bookArr[bookCounter].quantity);
            puts("Book was added");

            ++count;
            ++bookCounter;
        }
        fclose(bfPtr);
    }
}

void deleteBook() {
    int idBook;
    printf("Enter id of a book you want to delete: ");
    scanf("%d", &idBook);
    int idb = linerSearch(idBook);
    if (idb == -1)
        puts("Not found\n");
    else {
        bookArr[idb].id = 0;

        FILE *wfPtr;
        if ((wfPtr = fopen("library.txt", "w")) == NULL)
            puts("Fill is not exist");
        else {
            bookCounter = 0;
            while (bookCounter < BOOKS) {
                if (bookCounter != idb && bookArr[bookCounter].id != 0)
                    fprintf(wfPtr, "%10d%24s%10u\n", bookArr[bookCounter].id, bookArr[bookCounter].name,
                            bookArr[bookCounter].quantity);

                ++bookCounter;
            }
            fclose(wfPtr);
        }
        int i = 0, count = 0;
        while (i < BOOKS) {
            if (bookArr[i].id != 0) {
                bookArr[count] = bookArr[i];
                ++count;
            }
            ++i;
        }
        puts("Book was deleted");
    }
}

void searchId() {
    int idBook;
    printf("Enter id of book you want to search: ");
    scanf("%d", &idBook);
    int idb = linerSearch(idBook);
    if (idb == -1)
        puts("Not found\n");
    else if (bookArr[idb].id == 0)
        puts("Not found\n");
    else
        printf("ID: %10d | Name: %24s | Quantity: %10u\n", bookArr[idb].id, bookArr[idb].name, bookArr[idb].quantity);
}

void searchName() {
    sortedArr();

    char key[SIZE];
    int low = 0,
            high = BOOKS - 1,
            middle;

    printf("Enter the name of book you want to search: ");
    getc(stdin);
    gets(key);

    while (low <= high) {
        middle = (low + high) / 2;
        if (strcmp(key, bookCopy[middle].name) == 0) {
            puts("The book is:");
            printf("ID: %10d | Name: %24s | Quantity: %10u\n", bookCopy[middle].id, bookCopy[middle].name,
                   bookCopy[middle].quantity);
            break;
        } else if (strcmp(key, bookCopy[middle].name) < 0)
            high = middle - 1;
        else if (strcmp(key, bookCopy[middle].name) > 0)
            low = middle + 1;
    }
    if (strcmp(key, bookCopy[middle].name) != 0)
        puts("Not found");
}

void sortName() {
    sortedArr();
    puts("");
    printf("%10s | %24s | %10s\n", "id", "name", "quantity");
    for (int i = 0; i < BOOKS; ++i) {
        if (bookCopy[i].id == 0)
            continue;
        printf("%10d | %24s | %10u\n", bookCopy[i].id, bookCopy[i].name, bookCopy[i].quantity);
    }
    puts("");
}

void unsorted() {
    printf("\n%10s | %24s | %10s\n", "id", "name", "quantity");
    for (int i = 0; i < BOOKS; ++i)
        if (bookArr[i].id != 0)
            printf("%10d | %24s | %10u\n", bookArr[i].id, bookArr[i].name, bookArr[i].quantity);

    puts("");
}

int linerSearch(int key) {
    int i = 0;
    while (i < BOOKS) {
        if (key == bookArr[i].id)
            return i;
        ++i;
    }
    return -1;
}

void sortedArr() {
    for (int count = 0; count < BOOKS; ++count)
        bookCopy[count] = bookArr[count];

    for (int i = 1; i < BOOKS; ++i) {
        for (int j = 0; j < BOOKS - 1; ++j) {
            int x = strcmp(bookCopy[j].name, bookCopy[j + 1].name);
            if (x > 0) {
                struct book temp = bookCopy[j];
                bookCopy[j] = bookCopy[j + 1];
                bookCopy[j + 1] = temp;
            }
        }
    }
}
