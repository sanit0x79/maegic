#include <stdio.h>
#include <string.h>
#include "inventory.h"

void initializeInventory(Inventory* inventory) {
    inventory->itemCount = 0;
}

void addItem(Inventory* inventory, const char* itemName, const char* asciiArt) {
    if (inventory->itemCount < MAX_ITEMS) {
        strcpy(inventory->items[inventory->itemCount].name, itemName);
        strcpy(inventory->items[inventory->itemCount].asciiArt, asciiArt);
        inventory->itemCount++;
    } else {
        printf("Inventory is full!\n");
    }
}

void removeItem(Inventory* inventory, int index) {
    if (index >= 0 && index < inventory->itemCount) {
        for (int i = index; i < inventory->itemCount - 1; i++) {
            inventory->items[i] = inventory->items[i + 1];
        }
        inventory->itemCount--;
    } else {
        printf("Invalid item index!\n");
    }
}

void displayInventory(const Inventory* inventory) {
    printf("Inventory:\n");
    for (int i = 0; i < inventory->itemCount; i++) {
        printf("%d: %s\n%s\n", i + 1, inventory->items[i].name, inventory->items[i].asciiArt);
    }
    if (inventory->itemCount == 0) {
        printf("Your inventory is empty.\n");
    }
}
