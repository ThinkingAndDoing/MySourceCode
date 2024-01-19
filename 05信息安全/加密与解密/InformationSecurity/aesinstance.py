#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import os
import pbkdf2
from Crypto.Cipher import AES
from binascii import b2a_hex, a2b_hex

# required pycryptodemo

default_key = "00112233445566778899aabbccddeeff"
g_salt = [
    0x74,
    0x76,
    0x32,
    0x63,
    0x36,
    0x6D,
    0x5F,
    0x73,
    0x6E,
    0x61,
    0x6E,
    0x64,
    0x30,
    0x30,
    0x30,
    0x31,
    0x30,
    0x10,
    0x51,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0xB3,
    0x01,
    0xB0,
    0x62,
    0x00,
    0x00,
    0x00,
    0x00,
    0x24,
    0x2F,
    0x38,
    0x7B,
    0xAA,
    0x5E,
    0x6D,
    0x53,
    0xD4,
    0xFD,
    0x08,
    0xC2,
    0xB9,
    0xC5,
    0xBE,
    0x57,
]


class AEScrypt:
    def __init__(self, key=default_key):
        self.secret_key = pbkdf2.derive_pbkdf2(key.encode(), bytes(g_salt), 16)

    def generate_random_iv(self):
        return os.urandom(16)  # 16字节的随机字节字符串IV

    def pad_16(self, plain_text):
        length = 16
        pad_num = length - (len(plain_text) % length)
        padded_text = plain_text + ("\0" * pad_num)
        return padded_text

    def encrypt(self, plaintext):
        """
        AES算法需要两个不同的参数进行加密，分别是密钥和初始化向量（IV）。
        这里密钥key 长度必须为16（AES-128）、24（AES-192）、或32（AES-256）Bytes 长度。
        目前AES-128足够用
        """
        iv = self.generate_random_iv()

        cryptor = AES.new(self.secret_key, AES.MODE_CBC, IV=iv)
        padded_text = self.pad_16(plaintext)  # 加密文本text必须为16的倍数
        self.ciphertext = cryptor.encrypt(padded_text.encode())
        return b2a_hex(
            iv + self.ciphertext
        ).decode()  # AES加密后的字符不是ascii字符集的，输出到终端或者保存时候会存在问题，所以转化为16进制字符串

    def decrypt(self, ciphertext):
        cipher_data_bytes = a2b_hex(ciphertext.encode())
        iv, cipher_data = cipher_data_bytes[:16], cipher_data_bytes[16:]

        cryptor = AES.new(self.secret_key, AES.MODE_CBC, IV=iv)
        plaintext = cryptor.decrypt(cipher_data)
        return plaintext.decode().rstrip("\0")  # 解密后，去掉补足的空格用strip() 去掉


if __name__ == "__main__":
    pc = AEScrypt()
    e = pc.encrypt("00000")
    d = pc.decrypt(e)
    print("*****************")
    print(e, d)
    e = pc.encrypt("11111111")
    d = pc.decrypt(e)
    print("*****************")
    print(e, d)
