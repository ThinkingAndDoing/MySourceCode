# -*- coding: UTF-8 -*-

import os
import kos_treemodel


class ViewModel(object):
    def __init__(self, model):
        self.model = model
        self.tree_model = None
        self.standard_model = None

    def load_treemodel(self, src_path=""):
        if src_path!="":
            self.model.set_md_file_path(src_path)
        self.model.remove_unused_attachment()
        multiTree = self.model.get_multi_tree()
        self.tree_model = kos_treemodel.TreeModel()
        self.standard_model = self.tree_model.create_standard_item_model(multiTree)
        return self.standard_model

    def move_node(self, qs_item, src_path, dist_path):
        self.model.on_files_moved(src_path, dist_path)
        key_pair = ( os.path.dirname(src_path), dist_path )
        self.tree_model.recurse_replace_item_path(qs_item, key_pair)

    def rename_node(self, nodeFullName, newChildName):
        parentNodeFullName = os.path.dirname(nodeFullName)
        newItemName = self.model.get_available_name(parentNodeFullName, newChildName)
        self.model.on_selected_filename_changed(newItemName)
        key_pair = ( nodeFullName, os.path.join(parentNodeFullName, newChildName) )
        self.tree_model.replace_tree_item_path(self.standard_model, key_pair)

        return newItemName