#include <stdio.h>

#define MAX_LENGTH 100

int main() {
    char message[MAX_LENGTH];
    int key;
    
    // Get the message from the user
    printf("Enter the message to be encrypted: ");
    fgets(message, MAX_LENGTH, stdin);
    
    // Get the encryption key from the user
    printf("Enter the encryption key: ");
    scanf("%d", &key);
    
    // Loop through each character in the message
    for (int i = 0; message[i] != '\0'; i++) {
        char c = message[i];
        
        // Encrypt uppercase letters
        if (c >= 'A' && c <= 'Z') {
            c = (c - 'A' + key) % 26 + 'A';
        }
        // Encrypt lowercase letters
        else if (c >= 'a' && c <= 'z') {
            c = (c - 'a' + key) % 26 + 'a';
        }
        
        // Print the encrypted character
        printf("%c", c);
    }
    
    printf("\n");
    
    return 0;
}
