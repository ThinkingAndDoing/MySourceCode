# -*- coding: UTF-8 -*-

import rsa


class RsaKeyGen(object):
    def __init__(self):
        self.RSA_KEY_LEN = 2048
        self.PUBLIC_KEY_PATH = "publicKey.pem"
        self.PRIVATE_KEY_PATH = "privateKey.pem"

    def set_RSA_key_length(self, length):
        self.RSA_KEY_LEN = length

    def set_public_key_path(self, keyPath):
        self.PUBLIC_KEY_PATH = keyPath

    def set_private_key_path(self, keyPath):
        self.PRIVATE_KEY_PATH = keyPath

    def generate_RSA_pkcs1(self):
        publicKey, privateKey = rsa.newkeys(self.RSA_KEY_LEN)

        privateKey = privateKey.save_pkcs1()
        with open(self.PRIVATE_KEY_PATH, "wb") as f:
            f.write(privateKey)

        publicKey = publicKey.save_pkcs1()
        with open(self.PUBLIC_KEY_PATH, "wb") as f:
            f.write(publicKey)

        print("RSA pkcs1 generate successfully!")

    def generate_RSA_pkcs8(self):
        from Crypto.PublicKey import RSA

        key = RSA.generate(self.RSA_KEY_LEN)

        privateKey = key.export_key("PEM", pkcs=8)
        publicKey = key.publickey().export_key()

        with open(self.PRIVATE_KEY_PATH, "wb") as f:
            f.write(privateKey)

        with open(self.PUBLIC_KEY_PATH, "wb") as f:
            f.write(publicKey)

        print("RSA pkcs8 generate successfully!")


if __name__ == "__main__":
    RsaKeyGenerator = RsaKeyGen()

    RsaKeyGenerator.generate_RSA_pkcs1()
