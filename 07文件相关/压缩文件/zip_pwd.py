# -*- coding: utf-8 -*- 
#https://blog.csdn.net/embedded_sky/article/details/45201181
import os
import time


loc_7z = r"D:\01MyProgram\7-zip\7z.exe"
zip_file_name = time.strftime("%Y_%m_%d", time.localtime())

def zip_file(f, pwd):
    os.system( loc_7z + " a -tzip "+zip_file_name+" "+f+" -p" + pwd)

def zip_folder(f, pwd):
    os.system( loc_7z + " a -tzip "+zip_file_name+" "+f+"\\ -p" + pwd)
    
def unzip_file(f, pwd):
    os.system(loc_7z + " x " + f + " -p" + pwd )

if __name__ == "__main__":

    password = input("请输入加密密码:")
    zip_file("D:\\03SourceCode\\07文件相关\\压缩文件\\Allfiles", password)
    
    #zip_file("args.png", password)
    #unzip_file("archive.zip", password)
    
    