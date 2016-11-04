import os
import sys

#获取脚本文件的当前路径
def get_script_path():
    #获取脚本路径
    path = sys.path[0]
    #判断为脚本文件还是py2exe编译后的文件，如果是脚本文件，则返回的是脚本的目录，如果是py2exe编译后的文件，则返回的是编译后的文件路径
    if os.path.isdir(path):
        return path
    elif os.path.isfile(path):
        return os.path.dirname(path)
#打印结果

print("脚本所在位置：")
print(get_script_path())
print("Python执行时，搜索目录：")
print(sys.path)