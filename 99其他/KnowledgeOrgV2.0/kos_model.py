# -*- coding: UTF-8 -*-

import os
import sys
import chardet


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
    def __init__(self):
        IoAdapter.__init__(self)
        
        self.path = ""
        self.selectFileName = ""

    def get_path(self):
        return self.path
    
    def set_path(self, src_path):
        isValidPath = False
        if os.path.exists(src_path):
            src_path_backup = self.path

            self.path = src_path
            fileNameList = self.get_all_nodepairs()
            root_key = self.get_root_key(fileNameList)
            if root_key is not None:
                isValidPath = True
            else:
                #roll back
                self.path = src_path_backup
        return isValidPath
    
    def remove_invalid_attachment(self):

        attachFiles = []
        for root, dirs, files in os.walk(os.path.join(self.path, "resources")):
            for file in files:
                attachFiles.append((root, file))

        md_content = ""
        for root, dirs, files in os.walk(self.path):
            for file in files:
                if file.endswith(".md"):
                    md_content += self.load_from_local(os.path.join(root, file))

        for f in attachFiles:
            if f[1] not in md_content:
                os.remove(os.path.join(f[0], f[1]))

    def set_sel_fn(self, fn):
        self.selectFileName = fn

    def get_sel_fn(self):
        return self.selectFileName

    def remove_local(self, fn):
        os.remove(os.path.join(self.path, fn))

    def rename_local(self, oldName, newName):
        os.rename(os.path.join(self.path, oldName), os.path.join(self.path, newName))

    def save_sel(self, data):
        if (data.count("@Facts") == 1
            and data.count("@Question") == 1
            and data.count("@Opinion") == 1
            and data.find("@Facts") == 0
            and data.find("@Question") < data.find("@Opinion")):
            self.save_to_local(os.path.join(self.path, self.selectFileName), data)
        else:
            print(f"{self.selectFileName} is not formatted and won't be changed!")

    def create_new_file(self, filename):
        template = "@Facts\n\nNA\n\n@Question\n\nNA\n\n@Opinion\n\nNA\n\n"
        self.save_to_local(os.path.join(self.path, filename), template)

    def load_sel(self):
        return self.load_from_local(os.path.join(self.path, self.selectFileName))

    def get_root_key(self, listKey):
        for item in listKey:
            if item[0].lower() == "root":
                return item
        return None

    def rename_files_on_item_changed(self, newItemName):
        itemOld = self.filename_to_nodepair(self.selectFileName)
        
        for fn in os.listdir(self.path):
            curNode = self.filename_to_nodepair(fn)
            if curNode is not None and curNode[0] == itemOld[1]:
                os.rename(os.path.join(self.path, fn), os.path.join(self.path, self.nodepair_to_filename((newItemName, curNode[1]))))

        os.rename(os.path.join(self.path, self.selectFileName),  os.path.join(self.path, self.nodepair_to_filename((itemOld[0], newItemName))))
        
        self.selectFileName = self.nodepair_to_filename((itemOld[0], newItemName))

    def get_new_item_name(self, newItem):
        nodepairs = self.get_all_nodepairs()
        childs = { x[1] for x in nodepairs }

        if newItem not in childs and newItem.lower() != "root":
            return newItem
        else:
            return self.get_new_item_name(f"{newItem}_new")

    def get_all_nodepairs(self):
        #get all node pairs from local filenames
        all_filenames = os.listdir(self.path)
        nodepairs = []
        for fn in all_filenames:
            np = self.filename_to_nodepair(fn)
            if np is not None:
                nodepairs.append(np)
        #remove invalid node pairs
        while(True):
            cleanDone = True
            childs = { x[1] for x in nodepairs }
            for item in nodepairs:
                if item[0] not in childs and item[0].lower() != "root":
                    fn_to_del = self.nodepair_to_filename(item)
                    if fn_to_del!="":
                        os.remove(os.path.join(self.path, fn_to_del))
                        nodepairs.remove(item)
                        cleanDone = False
                        break
                    
            if cleanDone:
                break
        #return all valid node pairs
        return nodepairs
    
    def filename_to_nodepair(self, filename):
        if filename.endswith(".md"):
            nodepair = filename[:-3].split("-")
            if len(nodepair)==2:
                return (nodepair[0], nodepair[1])
        return None

    def nodepair_to_filename(self, nodepair):
        if type(nodepair)==tuple and len(nodepair)==2:
            return "-".join(map(str, nodepair)) + ".md"
        return ""


if __name__ == "__main__":
    if len(sys.argv) > 1 and os.path.exists(sys.argv[1]):
        model = Model(sys.argv[1])
