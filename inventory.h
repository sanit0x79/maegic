#ifndef INVENTORY_H
#define INVENTORY_H
#define MAX_ITEMS 20

typedef struct {
    char name[50];
    char asciiArt[100];
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int itemCount;
} Inventory;

void initializeInventory(Inventory* inventory);
void addItem(Inventory* inventory, const char* itemName, const char* asciiArt);
void removeItem(Inventory* inventory, int index);
void displayInventory(const Inventory* inventory);

#endif