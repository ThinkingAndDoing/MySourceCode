import os  
import cchardet  
  
def replace_text_in_file(file_path):  
    try:  
        # 使用cchardet检测文件编码  
        with open(file_path, 'rb') as file:  
            result = cchardet.detect(file.read())  
            encoding = result['encoding']  
  
        # 使用检测到的编码打开文件并替换文本  
        with open(file_path, 'r', encoding=encoding) as file:  
            file_content = file.read()  
            modified_content = file_content.replace('D:\\03SourceCode\\yy_Doc\\InformationManagement\\汽车行业', '__md_file_path__')  
            modified_content = file_content.replace('file:///D://.kos_file_library', '__inserted_file_path__')  

        # 将替换后的内容写回文件  
        with open(file_path, 'w', encoding=encoding) as file:  
            file.write(modified_content)  
  
        print(f' {file_path} 替换已完成！')  
    except Exception as e:  
        #print(f'处理 {file_path} 时出错: {str(e)}')  
        pass
  



if __name__ == "__main__":
    folder_path = "D:\\03SourceCode\\yy_Doc\\InformationManagement"  # 替换成你的文件夹路径
    # 遍历文件夹中的所有文件并处理  
    for root, dirs, files in os.walk(folder_path):  
        for file in files:  
            file_path = os.path.join(root, file)  
            replace_text_in_file(file_path)