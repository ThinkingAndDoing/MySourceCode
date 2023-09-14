# -*- coding: UTF-8 -*-


import multitree
import kos_treemodel


class ViewModel(object):
    def __init__(self, model):
        self.model = model

    def get_multitree(self):
        fileNameList = self.model.get_invalid_file_list()
        root_key = self.model.get_root_key(fileNameList)
        fileNameList.remove(root_key)
        multiTree = multitree.MultiTree(root_key[1])

        while fileNameList != []:
            for line in fileNameList:
                isAdded = multiTree.add(line[0], line[1])
                if isAdded:
                    fileNameList.remove(line)
        return multiTree

    def get_treemodel(self):
        multiTree = self.get_multitree()
        treeModel = kos_treemodel.TreeModel(multiTree)

        return treeModel.get_treemodel()

    def add_child_node(self, currentNodeName):
        childNodeName = self.model.get_new_item_name("New Item")
        childnode = (currentNodeName, childNodeName)
        self.model.save_to_local(
            self.convert_nodename_to_filename(childnode),
            "@Facts\n\nNA\n\n@Question\n\nNA\n\n@Opinion\n\nNA\n\n",
        )

        return childNodeName

    def del_current_node(self, currentNode):
        self.model.remove_local(self.convert_nodename_to_filename(currentNode))

    def rename_leaf_node(self, oldname, newname):
        self.model.rename_local(
            self.convert_nodename_to_filename(oldname),
            self.convert_nodename_to_filename(newname),
        )

    def rename_non_leaf_node(self, newnode):
        newItemName = self.model.get_new_item_name(newnode)
        self.model.rename_files_by_item(newItemName)

        return newItemName

    def set_active_node(self, activenode):
        self.model.set_sel_fn(self.convert_nodename_to_filename(activenode))

    def convert_nodename_to_filename(self, nodename):
        return "-".join(map(str, nodename)) + ".txt"

    def load_active_node(self):
        return self.model.load_from_local()

    def update_active_node(self, newContent):
        self.model.save_to_local_sel(newContent)

    def get_active_node(self):
        return self.convert_filename_to_nodename(self.model.get_sel_fn())

    def convert_filename_to_nodename(self, filename):
        filename = filename.split(".")[0]
        pre, sub = filename.split("-")
        return pre, sub
