# -*- coding: UTF-8 -*-
# reference codes: https://www.jianshu.com/p/7a4645691c68
import base64
import rsa
from rsa import common


str_to_be_encrypt = "RSA stands for Rivest-Shamir-Adleman. It is a cryptosystem used for secure data transmission. In RSA algorithm, encryption key is public but decryption key is private.插入中文 This algorithm is based on mathematical fact that factoring the product of two large prime numbers is not easy. It was developed by Ron Rivest, Adi Shamir and Leonard Adleman in 1977."


class RsaUtil(object):
    PUBLIC_KEY_PATH = "rsa_keys/publicKey.pem"
    PRIVATE_KEY_PATH = "rsa_keys/privateKey.pem"

    def __init__(
        self, company_pub_file=PUBLIC_KEY_PATH, company_pri_file=PRIVATE_KEY_PATH
    ):
        if company_pub_file:
            # load_pkcs1_openssl_pem: Loads a PKCS#1.5 PEM-encoded public key file from OpenSSL.
            # load_pkcs1: Loads a key in PKCS#1 DER or PEM format.
            self.company_public_key = rsa.PublicKey.load_pkcs1(
                open(company_pub_file, "rb").read()
            )
        if company_pri_file:
            self.company_private_key = rsa.PrivateKey.load_pkcs1(
                open(company_pri_file).read()
            )

    def get_max_length(self, rsa_key, encrypt=True):
        """加密内容过长时 需要分段加密 换算每一段的长度.
        :param rsa_key: 钥匙.
        :param encrypt: 是否是加密.
        """
        blocksize = common.byte_size(rsa_key.n)
        reserve_size = 11  # 预留位为11
        if not encrypt:  # 解密时不需要考虑预留位
            reserve_size = 0
        maxlength = blocksize - reserve_size
        return maxlength

    def encrypt_by_public_key(self, message):
        """使用公钥加密.
        :param message: 需要加密的内容.
        加密之后需要对接过进行base64转码
        """
        encrypt_result = b""
        max_length = self.get_max_length(self.company_public_key)
        while message:
            input = message[:max_length]
            message = message[max_length:]
            out = rsa.encrypt(input, self.company_public_key)
            encrypt_result += out
        encrypt_result = base64.b64encode(encrypt_result)
        return encrypt_result

    def decrypt_by_private_key(self, message):
        """使用私钥解密.
        :param message: 需要加密的内容.
        解密之后的内容直接是字符串，不需要在进行转义
        """
        decrypt_result = b""

        max_length = self.get_max_length(self.company_private_key, False)
        decrypt_message = base64.b64decode(message)
        while decrypt_message:
            input = decrypt_message[:max_length]
            decrypt_message = decrypt_message[max_length:]
            out = rsa.decrypt(input, self.company_private_key)
            decrypt_result += out
        return decrypt_result

    def sign_by_private_key(self, data):
        """私钥签名.
        :param data: 需要签名的内容.
        使用SHA-1 方法进行签名（也可以使用MD5）
        签名之后，需要转义后输出
        """
        signature = rsa.sign(str(data), priv_key=self.company_private_key, hash="SHA-1")
        return base64.b64encode(signature)

    def verify_by_public_key(self, message, signature):
        """公钥验签.
        :param message: 验签的内容.
        :param signature: 对验签内容签名的值（签名之后，会进行b64encode转码，所以验签前也需转码）.
        """
        signature = base64.b64decode(signature)
        return rsa.verify(message, signature, self.company_public_key)


if __name__ == "__main__":
    RsaTool = RsaUtil()

    rst = RsaTool.encrypt_by_public_key(str_to_be_encrypt.encode("utf8"))

    print(rst.decode("utf8"))

    rst = RsaTool.decrypt_by_private_key(rst)

    print(rst.decode("utf8"))
