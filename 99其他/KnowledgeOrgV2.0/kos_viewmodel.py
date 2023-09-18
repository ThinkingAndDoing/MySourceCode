# -*- coding: UTF-8 -*-


import kos_multitree
import kos_treemodel


class ViewModel(object):
    def __init__(self, model):
        self.model = model
        self.treeModel = kos_treemodel.TreeModel()

    def get_multitree(self):
        fileNameList = self.model.get_all_nodepairs()
        root_key = self.model.get_root_key(fileNameList)        
        fileNameList.remove(root_key)
        multiTree = kos_multitree.MultiTree(root_key[1])

        while fileNameList != []:
            for line in fileNameList:
                isAdded = multiTree.add(line[0], line[1])
                if isAdded:
                    fileNameList.remove(line)
        return multiTree

    def get_treemodel(self, src_path=""):
        rst = True
        if src_path=="":
            rst = self.model.set_path(self.model.get_path())
        else:
            rst = self.model.set_path(src_path)
        
        if rst==False:
                return None
        else:
            self.model.remove_invalid_attachment()
            multiTree = self.get_multitree()
            return self.treeModel.get_treemodel(multiTree)

    def add_child_node(self, currentNodeName):
        childNodeName = self.model.get_new_item_name("New Item")
        childnode = (currentNodeName, childNodeName)
        self.model.create_new_file(self.model.nodepair_to_filename(childnode))

        return childNodeName

    def del_current_node(self, currentNode):
        self.model.remove_local(self.model.nodepair_to_filename(currentNode))

    def rename_leaf_node(self, oldname, newname):
        self.model.rename_local(
            self.model.nodepair_to_filename(oldname),
            self.model.nodepair_to_filename(newname),
        )

    def rename_non_leaf_node(self, itemName):
        newItemName = self.model.get_new_item_name(itemName)
        self.model.rename_files_on_item_changed(newItemName)

        return newItemName

    def set_active_node(self, activenode):
        self.model.set_sel_fn(self.model.nodepair_to_filename(activenode))

    def load_active_node(self):
        return self.model.load_sel()

    def update_active_node(self, newContent):
        self.model.save_sel(newContent)

    def get_active_node(self):
        return self.model.filename_to_nodepair(self.model.get_sel_fn())

    def get_info_base_path(self):
        return self.model.get_path()