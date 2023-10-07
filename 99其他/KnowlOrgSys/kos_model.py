# -*- coding: UTF-8 -*-

import os
import chardet
import kos_multitree
import shutil

class IoAdapter:
    def __init__(self):
        pass

    def get_char_encode(self, filename):
        file = open(filename, "rb")
        buf = file.read()
        file.close()
        result = chardet.detect(buf)
        return result["encoding"]

    def load_from_local(self, filename):
        with open(filename, "r", encoding=self.get_char_encode(filename), errors="ignore") as f:
            data = f.read()
        return data

    def save_to_local(self, fn, data):
        with open(fn, "w", encoding="utf8") as f:
            f.write(data)

class Model(IoAdapter):
    def __init__(self, path):
        IoAdapter.__init__(self)
        
        self.md_file_path = path
        self.file_selected = "" # file full path

    def get_multi_tree(self):
        multiTree = kos_multitree.MultiTree(self.md_file_path)
        for root, dirs, files in os.walk(self.md_file_path):
            for file in files:
                if file.endswith(".md"):
                    multiTree.add(os.path.join(root, file)[:-3])

        return multiTree
                    
    def get_md_file_path(self):
        return self.md_file_path
    
    def set_md_file_path(self, src_path):
        isValidPath = False

        if os.path.exists(src_path):
            self.md_file_path = src_path
            isValidPath = True

        return isValidPath
    
    def remove_unused_attachment(self):

        attachFiles = []
        for root, dirs, files in os.walk(os.path.join(self.md_file_path, "resources")):
            for file in files:
                attachFiles.append((root, file))

        md_content = ""
        for root, dirs, files in os.walk(self.md_file_path):
            for file in files:
                if file.endswith(".md"):
                    md_content += self.load_from_local(os.path.join(root, file))

        for f in attachFiles:
            if f[1] not in md_content:
                os.remove(os.path.join(f[0], f[1]))

    def set_name_of_file_selected(self, fn):
        self.file_selected = fn

    def get_name_of_file_selected(self):
        return self.file_selected

    def remove_md_file(self, fn):
        os.remove(fn)

    def set_content_of_file_selected(self, data):
        if (data.count("@Facts") == 1
            and data.count("@Question") == 1
            and data.count("@Opinion") == 1
            and data.find("@Facts") == 0
            and data.find("@Question") < data.find("@Opinion")):
            self.save_to_local(self.file_selected, data)
        else:
            print(f"{self.file_selected} is not formatted and won't be changed!")

    def create_md_file(self, parentNodeFullName):
        if not os.path.exists(parentNodeFullName):
            os.makedirs(parentNodeFullName)

        template = "@Facts\n\nNA\n\n@Question\n\nNA\n\n@Opinion\n\nNA\n\n"
        availiableName = self.get_available_name(parentNodeFullName, "New Item")
        self.save_to_local(os.path.join(parentNodeFullName, f"{availiableName}.md"), template)
        return availiableName
    
    def get_content_of_file_selected(self):
        return self.load_from_local(self.file_selected)

    def on_files_moved(self, src_path, dist_path):
        if not os.path.exists(dist_path):
            os.makedirs(dist_path)

        if os.path.exists(src_path):
            shutil.move(src_path, dist_path)

        if os.path.exists(f"{src_path}.md"):
            shutil.move(f"{src_path}.md", f"{os.path.join(dist_path, os.path.basename(src_path))}.md")

    def on_selected_filename_changed(self, newItemName):
        parentNodeFullName = os.path.dirname(self.file_selected)
        oldItemName = os.path.basename(self.file_selected)
        newFileName = os.path.join(parentNodeFullName, f"{newItemName}.md")

        if self.file_selected.endswith(".md") and os.path.exists(self.file_selected[:-3]):
            os.rename(self.file_selected[:-3], os.path.join(parentNodeFullName, newItemName))

        os.rename(self.file_selected,  newFileName)
        self.file_selected = newFileName

    def get_available_name(self, parentNodeFullName, newChildName):
        availiableName = newChildName
        serialNum = 2
        while os.path.exists(os.path.join(parentNodeFullName, f"{availiableName}.md")):
            availiableName = f"{newChildName} ({serialNum})"
            serialNum += 1
        return availiableName

if __name__ == "__main__":

    file_path = "D:\\08doc\\精益求精"
    print( os.path.basename(os.path.dirname(file_path)) )