# vernam-encryption

A small C project I made to learn the Vernam cipher. It encrypts and decrypts
files, including text saved in a file, using XOR with a key of the same size.

## How it works

```text
encrypted = original XOR key
original  = encrypted XOR key
```

The same operation encrypts and decrypts. A new key is filled with random bytes
from the operating system: `BCryptGenRandom` on Windows and `/dev/urandom` on Linux.
Files are processed in chunks of 64 KiB.

## Build

You need GCC and GNU Make. On Windows, use MinGW-w64 with an MSYS2 shell.
On Linux, use your usual terminal.

```sh
make
```

Run on Windows:

```sh
./build/vernam.exe
```

Run on Linux:

```sh
./build/vernam
```

## Use

To encrypt a file:

1. Enter the path of the original file, for example `message.txt`.
2. Answer `n` to create a key.
3. Enter an existing folder, for example `.` for the current folder.
4. Choose a key name, for example `message` (the program adds `.key`).

The program saves the key and an encrypted file named `output.<number>`.
It prints both paths. Existing files are kept.

To decrypt, run the program again, enter the encrypted file path, answer `Y`
(or press Enter), and select the same key. The output is identical to the
original file. Rename it to the original name or extension if needed.

You can also supply an existing key. It must have exactly the same size as the
input file. Output files are saved next to the key. Enter paths without quotes;
spaces are supported. Paths, including the generated filename, must fit in
255 characters.

## Notes

A one-time pad requires a random key as long as the message, kept secret and
used to encrypt only one message. Keep the key to decrypt that message; do not
reuse it to encrypt another one.

This is a learning project. It does not authenticate files or detect changes
to encrypted data.

## Structure

- `src/main.c`: interactive program.
- `src/input.c`: input and paths.
- `src/files.c`: file checks and sizes.
- `src/vernam.c`: random key generation and XOR.
- `include/`: headers.
