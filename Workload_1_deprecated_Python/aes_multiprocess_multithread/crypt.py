import click
import aes
import time
import os
import multiprocessing
import concurrent.futures

@click.command()
@click.option(
    '--encrypt/--decrypt',
    '-e/-d',
    default=True,
)
@click.option(
    '--input_file',
    '-i',
    required=True,
)
@click.option(
    '--output_file',
    '-o',
    required=True,
)
@click.option(
    '--block-cipher-mode',
    '-m',
    type=click.Choice(["ECB", "CBC", "CTR"]),
    default="CTR",
)
@click.option(
    '--key-length',
    '-l',
    type=click.Choice(["128", "192", "256"]),
    default="128",
)
def main(encrypt, input_file, output_file, block_cipher_mode, key_length):
    if encrypt:
        key = aes.random_key_generator(int(key_length))
        if key_length == "128":
            AES = aes.AES(key, 128)
        elif key_length == "192":
            AES = aes.AES(key, 192)
        elif key_length == "256":
            AES = aes.AES(key, 256)
        if block_cipher_mode == "ECB":
            bcm = aes.ECB(AES)
        elif block_cipher_mode == "CBC":
            bcm = aes.CBC(AES, 16)
        elif block_cipher_mode == "CTR":
            bcm = aes.CTR(AES)
        with multiprocessing.Pool() as process_pool:
            with concurrent.futures.ThreadPoolExecutor() as thread_executor:
                process_pool.apply_async(bcm.cipher, (input_file, output_file))
                thread_executor.submit(print, "Cipher Key:", key)
                thread_executor.submit(write_key, key)
    else:
        key = read_key()
        if key == 1:
            print("File key.txt doesn't exist! Can't decrypt without key")
            exit(1)
        key_length = len(key) * 4
        if key_length == 128:
            AES = aes.AES(key, 128)
        elif key_length == 192:
            AES = aes.AES(key, 192)
        elif key_length == 256:
            AES = aes.AES(key, 256)
        else:
            print("Key length not valid!")
            exit(1)
        if block_cipher_mode == "ECB":
            bcm = aes.ECB(AES)
        elif block_cipher_mode == "CBC":
            bcm = aes.CBC(AES, 16)
        elif block_cipher_mode == "CTR":
            bcm = aes.CTR(AES)
        with multiprocessing.Pool() as process_pool:
            with concurrent.futures.ThreadPoolExecutor() as thread_executor:
                process_pool.apply_async(bcm.decipher, (input_file, output_file))
                thread_executor.submit(print, "Decryption complete.")
                thread_executor.submit(thread_executor.shutdown)

def read_key():
    try:
        with open("key.txt", "r") as f:
            key = f.read()
        return key
    except IOError:
        return 1

def write_key(key):
    with open("key.txt", "w") as f:
        f.write(key)

if __name__ == "__main__":
    
    # Write the PID to the file
    with open("process.pid", "w") as pid_file:
        pid_file.write(str(os.getpid()))

    # Sleep for 5 seconds
    time.sleep(5)

    main()
