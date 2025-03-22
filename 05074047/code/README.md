# File Encryption and Decryption in C

## Overview
This repository contains a simple C program to encrypt and decrypt files using the XOR bitwise operation. It demonstrates basic file handling operations and encryption techniques using an XOR key.

## Features
- Encrypts a text file using XOR encryption.
- Decrypts an encrypted file using the same XOR key.
- Uses a temporary file for intermediate storage.
- Simple and efficient encryption method.

## Prerequisites
- A C compiler (GCC, Clang, MSVC, etc.)

## Compilation
Use the following command to compile the encryption and decryption programs:
```sh
gcc encrypt.c -o encrypt.exe
gcc decrypt.c -o decrypt.exe
```

## Usage
### Encryption
1. Run the encryption program:
   ```sh
   ./encrypt.exe
   ```
2. Enter the filename to encrypt.
3. The file contents will be modified with XOR-encrypted text.
4. The encrypted file replaces the original file.

### Decryption
1. Run the decryption program:
   ```sh
   ./decrypt.exe
   ```
2. Enter the filename to decrypt.
3. The program restores the original text using the XOR key.

## How It Works
- XOR encryption is performed by applying the XOR operation on each character with a fixed key.
- The same key is used for both encryption and decryption.
- The encrypted content is temporarily stored in a separate file before being copied back to the original file.

## Limitations
- Uses a fixed XOR key (5), making it vulnerable to attacks.
- Modifies the original file after encryption.
- No password-based encryption.



