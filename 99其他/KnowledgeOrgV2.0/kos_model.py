# -*- coding: UTF-8 -*-

import os
import sys
import chardet


class Model:
    def __init__(self, src_path):
        self.path = src_path
        self.tree = None
        self.selectFileName = ""

    def set_sel_fn(self, fn):
        self.selectFileName = fn

    def get_sel_fn(self):
        return self.selectFileName

    def rename_local(self, src, dst):
        os.rename(self.path + "\\" + src, self.path + "\\" + dst)

    def remove_local(self, fn):
        os.remove(self.path + "\\" + fn)

    def save_to_local(self, fn, data):
        f = open(self.path + "\\" + fn, "w", encoding="utf8")
        f.write(data)
        f.close()

    def is_content_formatted(self, data):
        if (
            data.count("@Facts") == 1
            and data.count("@Question") == 1
            and data.count("@Opinion") == 1
        ):
            if data.find("@Facts") == 0 and data.find("@Question") < data.find(
                "@Opinion"
            ):
                return True
        return False

    def save_to_local_sel(self, data):
        if self.is_content_formatted(data):
            self.save_to_local(self.selectFileName, data)

    def get_char_encode(self, filename):
        file = open(filename, "rb")
        buf = file.read()
        file.close()
        result = chardet.detect(buf)
        return result["encoding"]

    def load_from_local(self):
        fn = self.path + "\\" + self.selectFileName
        f = open(fn, "r", encoding=self.get_char_encode(fn), errors="ignore")
        data = f.read()
        f.close()
        return data

    def get_root_key(self, listKey):
        for item in listKey:
            if item[0].lower() == "root":
                return item

    def rename_files_by_item(self, itemNew):
        itemOld = self.selectFileName[:-4].split("-")[1]
        l_fn = os.listdir(self.path)
        for fn in l_fn:
            if fn.split("-")[0] == itemOld:
                self.rename_local(fn, itemNew + "-" + fn.split("-")[1])
        self.rename_local(
            self.selectFileName,
            self.selectFileName.split("-")[0] + "-" + itemNew + ".txt",
        )
        self.set_sel_fn(self.selectFileName.split("-")[0] + "-" + itemNew + ".txt")

    def get_new_item_name(self, newItem):
        l_fn = os.listdir(self.path)
        l_fn = self.get_pair_list_by_txt_name(l_fn)
        s_key = {x[1] for x in l_fn}

        if newItem not in s_key and newItem.lower() != "root":
            return newItem
        else:
            return self.get_new_item_name(newItem + "_new")

    def clear_invalid_file_list(self):
        l_fn = os.listdir(self.path)
        l_fn = self.get_pair_list_by_txt_name(l_fn)
        s_key = {x[1] for x in l_fn}

        for item in l_fn:
            if item[0] not in s_key and item[0].lower() != "root":
                self.remove_local(item[0] + "-" + item[1] + ".txt")
                self.clear_invalid_file_list()
                break

    def get_pair_list_by_txt_name(self, l_fn):
        l_pairs = [x[:-4].split("-") for x in l_fn if x.endswith(".txt")]
        l_pairs = [x for x in l_pairs if len(x) == 2]
        return l_pairs

    def get_invalid_file_list(self):
        self.clear_invalid_file_list()

        l_fn = os.listdir(self.path)
        l_fn = self.get_pair_list_by_txt_name(l_fn)

        return l_fn


if __name__ == "__main__":
    if len(sys.argv) > 1 and os.path.exists(sys.argv[1]):
        model = Model(sys.argv[1])
