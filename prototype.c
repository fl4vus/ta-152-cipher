#include <stdio.h>
#include <string.h>

void copyArray(int source[], int destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int findCharPosition(char arr[], int size, char element) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            return i; // Return the index if the element is found
        }
    }

    return -1; // Return -1 if the element is not found
}

int findMapPosition(int arr[], int size, int element) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            return i; // Return the index if the element is found
        }
    }

    return -1; // Return -1 if the element is not found
}

void reverseArray(int arr[], int starter, int size) 
{
    int start = 0;
    int end = size - 1;

    while (start < end) {
        // Swap elements at start and end indices
        swap(&arr[starter+start], &arr[starter+end]);

        // Move the indices towards the center
        start++;
        end--;
    }
}

void superShuffle(int arr[], int n, int size)
{
    if (n <= 0)
    {
        n = 2;
    }
    int new_size = size - (size % n);
    int crapSize = size / n;
    int starter, ender;
    starter = 0;
    //ender = crapSize - 1;
    for (int i = 0; i < n; i++)
    {
        starter = (i  * crapSize);
        reverseArray(arr, starter, crapSize);
    }
    
    
}

int main()
{
    
    char newline = '\n';
    char space = ' ';

    char allCharacters[] = 
    {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K','L', 'M','N', 'O', 'P', 'Q', 'R', 'S','T', 'U', 'V', 'W', 'X', 'Y', 'Z','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm','n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','0', '1', '2', '3', '4', '5', '6', '7', '8', '9','!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '+', '=','[', ']', '{', '}', ';', ':', ',', '.', '/', '<', '>', '?', ' ', '\\', newline, space
    };
    int siz;
    siz = sizeof(allCharacters)/sizeof(allCharacters[0]);
    int num_array[siz];
    int new_map[siz];
    for (int i = 0; i < siz; i++)
    {
        num_array[i] = i;
        new_map[i] = i;
    }

keyInput:
    int key;
    printf("\nMake Encryption PIN (4 Digits):    ");
    scanf("%d", &key);
    
    if ((key < 1000)||(key > 9999))
    {
        printf("\nINVALID PIN. RE-ENTER");
        goto keyInput;
    }

    int trueKey = key % 10;

    superShuffle(new_map, trueKey, siz);

    
    printf("----------------\n");
    for(int j = 0; j < siz; j++)
    {
        printf("%d ", num_array[j]);
    }
    printf("\n----------------\n");
    for(int j = 0; j < siz; j++)
    {
        printf("%d ", new_map[j]);
    }
    printf("\n----------------\n");
    
    char filepath[100];
    printf("\nEnter the filename/filepath of the file to be encrypted:   ");
    scanf("%s", &filepath);    

    // Open the file
    FILE *read = fopen(filepath, "r");
    FILE *write = fopen("output.txt", "w");

    // Check if the file was opened successfully
    if (read == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read and print characters from the file
    int character;
    while ((character = fgetc(read)) != EOF) 
    {
        char char_ch;
        char_ch = character;
        int pos = findCharPosition(allCharacters, siz, char_ch);
        int map_pos = findMapPosition(new_map, siz, pos);

        printf("\n %c", char_ch);
        printf("--> %d", pos);
        
        printf("--> %d", map_pos);
        char writer = allCharacters[map_pos];
        printf("--> %c", writer);
        if ((pos == -1) || (map_pos == -1))
        {
            fputc(char_ch, write);
        }
        else
        {
            fputc(writer, write);
        }
    }

    // Close the file
    fclose(read);
    fclose(write);

    // Decrypter
enterPass:   
    int passw;
    printf("\nEnter PIN:     ");
    scanf("%d", &passw);

    const char *filePath2 = "output.txt";

    // Open the file
    FILE *read2 = fopen(filePath2, "r");
    FILE *write2 = fopen("decrypt.txt", "w");

    if (passw == key)
    {
        char newChararr[siz];
        printf("\n");
        for (int i = 0; i < siz; i++)
        {
            int charPos = findMapPosition(new_map, siz, i);
            //printf("%d ", charPos);
            newChararr[charPos] = allCharacters[i];
        }
        
        for (int i = 0; i < siz; i++)
        {
            printf("%c ", newChararr[i]);
        }
        
        superShuffle(new_map, trueKey, siz);
        //superShuffle(new_map, 1, siz);
        //superShuffle(new_map, 2, siz);

        

        // Check if the file was opened successfully
        if (read2 == NULL) {
            perror("Error opening file");
            return 1;
        }

        // Read and print characters from the file
        int character2;
        while ((character2 = fgetc(read2)) != EOF) 
        {
            char char_ch;
            char_ch = character2;
            int pos = findCharPosition(newChararr, siz, char_ch);
            int map_pos = findMapPosition(new_map, siz, pos);

            printf("\n %c", char_ch);
            printf("--> %d", pos);
            
            printf("--> %d", map_pos);
            char writer = allCharacters[map_pos];
            printf("--> %c", writer);
            if ((pos == -1) || (map_pos == -1))
            {
                fputc(char_ch, write2);
            }
            else
            {
                fputc(writer, write2);
            }
        }
    }
    else
    {
        char message[16] = "INVALID PASSWORD";
        for (int i = 0; i < 16; i++)
        {
            fputc(message[i], write2);
        }
        printf("%s", message);
    }

    

    // Close the file
    fclose(read);
    fclose(write);
    printf("\n");
    return 0;
}