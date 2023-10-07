import os

def rename_md_files(folder):
    for root, dirs, files in os.walk(folder):
        for file in files:
            if file.endswith(".md") and "-" in file:
                parts = file.split("-")
                if len(parts) == 2:
                    new_name = parts[1].strip()
                    old_path = os.path.join(root, file)
                    new_path = os.path.join(root, new_name)
                   
                    try:
                        os.rename(old_path, new_path)
                        print(f"Renamed: {old_path} -> {new_path}")
                    except Exception as e:
                        print(f"Error renaming {old_path}: {str(e)}")

if __name__ == "__main__":
    folder_path = "D:\\03SourceCode\\yy_Doc\\InformationManagement"  # 替换成你的文件夹路径
    rename_md_files(folder_path)