#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "inventory.h"
#include <string.h>

void startGame();
void playMusic(const char *file);
void displayIntro();
void displayInventoryMenu(Inventory* inventory);
char* loadAsciiArt(const char *filename);

int main(int argc, char* argv[])
{

    while (1)
    {
        displayIntro();
        startGame();
    }

    return 0;
}

void startGame()
{
    Inventory inventory;
    initializeInventory(&inventory);

    playMusic("/home/sanity/CLionProjects/TextBasedRPG/content/audio/adventure.mp3");
    char characterName[50];
    printf("What is your character's name? ");
    fgets(characterName, sizeof(characterName), stdin);
    characterName[strcspn(characterName, "\n")] = '\0';
    printf("Welcome, %s!\n", characterName);

    char choice;
    while (1)
    {
        printf("Choose an action: (e)xplore, (b)attle, (i)nventory, (q)uit: ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
        switch (choice)
        {
            case 'e':
                printf("You explore the area... \n");
                break;
            case 'b':
                printf("A wild monster appears!\n");
                playMusic("/home/sanity/CLionProjects/TextBasedRPG/content/audio/battle.mp3");
                break;
            case 'i':
                printf("You open your inventory...\n");
                displayInventoryMenu(&inventory);
                break;
            case 'q':
                printf("Returning to Main Menu \n");
                return;
            default:
                printf("You did not make a choice!");
        }
    }
}

void displayIntro()
{
    printf("Welcome to Maegic!\n");
    printf("Press S to start the game or Q to quit\n");
    playMusic("/home/sanity/CLionProjects/TextBasedRPG/content/audio/introScreen.mp3");
    char choice;
    while (1) {
        choice = getchar();
        while (getchar() != '\n');

        if (choice == 's' || choice == 'S') {
            return;
        } else if (choice == 'q' || choice == 'Q') {
            printf("Quitting...\n");
            exit(0);
        } else {
            printf("Invalid input. Press S to start the game or Q to quit.\n");
        }
    }
}

void playMusic(const char *file)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    Mix_Music *music = Mix_LoadMUS(file);
    if (!music)
    {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(music, -1);
    // printf("Playing music: %s\n", file);
}


void displayInventoryMenu(Inventory* inventory) {
    displayInventory(inventory);
    printf("Choose an action: (a)dd item, (r)emove item, (b)ack to game: ");

    char choice;
    scanf(" %c", &choice);
    while (getchar() != '\n');

    switch (choice) {
        case 'a': {
            char itemName[50];
            char asciiArt[500];
            printf("Enter item name to add: ");
            fgets(itemName, sizeof(itemName), stdin);
            itemName[strcspn(itemName, "\n")] = '\0';

            char filename[60];
            snprintf(filename, sizeof(filename), "%s.txt", itemName);
            char *art = NULL;

            if (strcmp(itemName, "Sword") == 0)
            {
                art = loadAsciiArt("/home/sanity/CLionProjects/TextBasedRPG/content/weapons/sword.txt");
            } else if (strcmp(itemName, "Dagger") == 0)
            {
                art = loadAsciiArt("/home/sanity/CLionProjects/TextBasedRPG/content/weapons/dagger.txt");
            }
            if (art) {
                addItem(inventory, itemName, art);
                free(art);
            } else {
                printf("Enter ASCII art for the item (end with a single '.' on a new line):\n");
                int i = 0;
                char line[100];
                while (1) {
                    fgets(line, sizeof(line), stdin);
                    if (strcmp(line, ".\n") == 0) {
                        asciiArt[i] = '\0';
                        break;
                    }
                    strcpy(&asciiArt[i], line);
                    i += strlen(line);
                }
                addItem(inventory, itemName, asciiArt);
            }
            break;
        }
        case 'r':
            {
            int itemIndex;
            printf("Enter item index to remove: ");
            scanf("%d", &itemIndex);
            while (getchar() != '\n');
            removeItem(inventory, itemIndex - 1);
            break;
        }
        case 'b':
            return;
        default:
            printf("Invalid choice!\n");
    }
}

char* loadAsciiArt(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char*)malloc(fileSize + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    fclose(file);
    return buffer;
}