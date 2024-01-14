#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

// Structure for a node in the linked list
struct Node {
    unsigned char plaintext[16];  // Block size for AES (128 bits)
    unsigned char ciphertext[16]; // Block size for AES (128 bits)
    struct Node* next;
};

// Function to add a new node to the linked list
struct Node* addNode(struct Node* head, const unsigned char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    memcpy(newNode->plaintext, data, 16);
    memset(newNode->ciphertext, 0, 16); // Initialize to 0 for simplicity
    newNode->next = head;
    return newNode;
}

// Function to display the linked list
void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%s ", current->plaintext);
        current = current->next;
    }
    printf("\n");
}

// Function to perform XOR operation on two blocks
void xorBlocks(const unsigned char* block1, const unsigned char* block2, unsigned char* result) {
    for (int i = 0; i < 16; ++i) {
        result[i] = block1[i] ^ block2[i];
    }
}

// Function to perform CBC Encryption simulation using linked lists
void performCBCSimulation(struct Node* head, const unsigned char* key, const unsigned char* iv) {
    EVP_CIPHER_CTX* ctx;
    ctx = EVP_CIPHER_CTX_new();

    struct Node* current = head;
    unsigned char previousCiphertext[16];
    memcpy(previousCiphertext, iv, 16); // Use IV as the initial previous ciphertext

    while (current != NULL) {
        // XOR the plaintext block with the previous ciphertext block
        xorBlocks(current->plaintext, previousCiphertext, current->plaintext);

        // Encrypt the XORed result and store it as the current ciphertext block
        EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
        EVP_EncryptUpdate(ctx, current->ciphertext, NULL, current->plaintext, 16);
        EVP_EncryptFinal_ex(ctx, NULL, NULL);

        // Update the previous ciphertext for the next iteration
        memcpy(previousCiphertext, current->ciphertext, 16);

        current = current->next;
    }

    EVP_CIPHER_CTX_free(ctx);
}

// Function to perform CBC Decryption simulation using linked lists
void performCBCDecryption(struct Node* head, const unsigned char* key, const unsigned char* iv) {
    EVP_CIPHER_CTX* ctx;
    ctx = EVP_CIPHER_CTX_new();

    struct Node* current = head;
    unsigned char previousCiphertext[16];
    memcpy(previousCiphertext, iv, 16); // Use IV as the initial previous ciphertext

    while (current != NULL) {
        // Decrypt the ciphertext block
        EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
        EVP_DecryptUpdate(ctx, current->plaintext, NULL, current->ciphertext, 16);
        EVP_DecryptFinal_ex(ctx, NULL, NULL);

        // XOR the decrypted result with the previous ciphertext block
        xorBlocks(current->plaintext, previousCiphertext, current->plaintext);

        // Update the previous ciphertext for the next iteration
        memcpy(previousCiphertext, current->ciphertext, 16);

        current = current->next;
    }

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    // 128-bit AES key
    const unsigned char key[16] = "0123456789ABCDEF";

    // Initialization Vector (IV) for the first block
    const unsigned char iv[16] = "0123456789ABCDEF";

    // Create a linked list with test data
    struct Node* head = NULL;
    
     head = addNode(head, (const unsigned char*)"bonjour");

    // Display the original message
    printf("Original Message: ");
    displayList(head);

    // Perform CBC Encryption simulation using linked lists
    performCBCSimulation(head, key, iv);

    // Display the encrypted message
    printf("Encrypted Message: ");
    displayList(head);

    // Perform CBC Decryption simulation using linked lists
    performCBCDecryption(head, key, iv);

    // Display the decrypted message
    printf("Decrypted Message: ");
    displayList(head);

    return 0;
}
