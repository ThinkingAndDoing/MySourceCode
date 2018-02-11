#!/usr/bin/python3
# -*- coding: UTF-8 -*-
#coding=utf-8  
 
import unittest  
from des import DES  
       
    class KnownValues(unittest.TestCase):  
        """""" 
        __known_values = (('12345678','ABC我们大家','388a9c61849462e20af277ffe6891072'),  
                )  
       
        def test_encode(self):  
            des = DES()  
            for key, before, after in self.__known_values:  
                des.input_key(key)  
                result = des.encode(before)  
                self.assertEqual(after, result)  
       
        def test_decode(self):  
            des = DES()  
            for key, after, before in self.__known_values:  
                des.input_key(key)  
                result = des.decode(before)  
                self.assertEqual(after, result)  
       
    class BadInput(unittest.TestCase):  
        """""" 
        __key_inputs = (  
                )  
        def test_input_key(self):  
            des = DES()  
            self.assertRaises(IndexError, des.input_key, '1234567', 10)  
            self.assertRaises(IndexError, des.input_key, '123我阿, 4567', 2)  
            self.assertRaises(KeyError, des.input_key, '123我哦哦哦, 4567', 16)  
       
        def test_encode(self):  
            pass 
       
        def test_decode(self):  
            des = DES()  
            self.assertRaises(KeyError, des.decode, '123我哦哦哦, 4567')  
       
    class SanityCheck(unittest.TestCase):  
        """""" 
        """""" 
        __encode_inputs = (('asfd我 ','的萨sa1'),  
                )  
        __decode_inputs = (('12345678','388a9c61849462e20af277ffe6891072'),  
                )  
       
        def test_encode(self):  
            des = DES()  
            for key, before in self.__encode_inputs:  
                des.input_key(key)  
                after = des.encode(before)  
                result = des.decode(after)  
                self.assertEqual(before, result)  
       
        def test_decode(self):  
            des = DES()  
            for key, before in self.__decode_inputs:  
                des.input_key(key)  
                after = des.decode(before)  
                result = des.encode(after)  
                self.assertEqual(before, result)  
       
    if __name__ == '__main__':  
        unittest.main()  
