#include <stdio.h>
#include "boyer_moore.h"
#include "rabin_karp.h"
#include <stdbool.h>
#include <stdlib.h>

static char* TEXT = "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.";

struct MenuItem {
    char* name;

    void (* fct)();
};

bool running = true;

void initMenuItem(struct MenuItem* menuItem, char* name, void(* fct)()) {
    menuItem->name = name;
    menuItem->fct = fct;
}

void printMenu(struct MenuItem menu[3]) {
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, menu[i].name);
    }
    printf("Bitte geben Sie die Ziffer der gewuenschten Funktion ein:\n");
}

void close() {
    running = false;
}

void boyerMooreMenu() {
    printf("Bitte geben Sie die zu suchende Folge ein:\n");
    char keyString[256];
    scanf("%s", keyString);
    int counter = searchBoyerMoore(TEXT, keyString);
    printf("Durchläufe: %d\n", counter);
}

void rabinKarp() {
    printf("Bitte geben Sie die zu suchende Folge ein:\n");
    char keyString[256];
    scanf("%s", keyString);
    int q = 101; // A prime number
    int counter = searchRabinKarp(keyString, TEXT, q);
    printf("Durchläufe: %d\n", counter);
}

int main() {
    struct MenuItem menuItemBoyerMoore;
    initMenuItem(&menuItemBoyerMoore, "Boyer Moor", &boyerMooreMenu);

    struct MenuItem menuItemRabinKarp;
    initMenuItem(&menuItemRabinKarp, "Rabin Karp", &rabinKarp);

    struct MenuItem menuItemExit;
    initMenuItem(&menuItemExit, "Beenden des Programms", &close);

    struct MenuItem menuItems[3] = {menuItemBoyerMoore, menuItemRabinKarp, menuItemExit};

    long menuIndex;
    char menuIndexString[256];
    char* endP;
    int base = 10;
    while (running) {
        printMenu(menuItems);
        scanf("%s", menuIndexString);
        menuIndex = strtol(menuIndexString, &endP, base);
        if (menuIndex > 3 || menuIndex < 1) {
            printf("Bitte geben Sie eine Zahl zwischen 1 und 3 ein.\n");
            continue;
        }
        menuItems[--menuIndex].fct();
    }

    return 0;
}