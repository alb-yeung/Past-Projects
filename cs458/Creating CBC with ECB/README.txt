This is using OpenSSL's blowfish implementation to recreate a CBC encryption algorithm using only ECB calls.

This uses a blocksize of 8 and a keysize of 16, both in bytes. Each byte of padding is the number of pad bytes there are.
For example, "Hello world" would be stored as {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', 5, 5, 5, 5, 5}.
