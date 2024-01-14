# CBC Encryption Simulation using Linked Lists

This C program demonstrates a simulation of Cipher Block Chaining (CBC) encryption using linked lists. The program uses the OpenSSL library for cryptographic operations.

## Overview

The program defines a linked list data structure, where each node represents a block of plaintext and ciphertext. The CBC encryption process is simulated by XORing plaintext blocks with the previous ciphertext block before encryption.

## Files

- **cbc_encryption_linked_lists.c**: The main C file containing the implementation of CBC encryption simulation using linked lists.

## How to Run

1. **Prerequisites:**
   - Ensure that you have OpenSSL installed on your system.
   - Compile the program using a C compiler with OpenSSL support. For example:
     ```bash
     gcc -o cbc_encryption_linked_lists cbc_encryption_linked_lists.c -lssl -lcrypto
     ```

2. **Run the Program:**
   ```bash
   ./cbc_encryption_linked_lists
