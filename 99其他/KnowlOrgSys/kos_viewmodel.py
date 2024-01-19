# -*- coding: UTF-8 -*-

import os
import kos_treemodel


class ViewModel:
    def __init__(self, model):
        self.model = model
        self.tree_model = kos_treemodel.TreeModel()
        self.standard_model = None

    def create_standard_model(self, src_path=""):
        if src_path!="":
            self.model.set_md_file_path(src_path)
        self.model.remove_unused_attachment()
        multi_tree = self.model.get_multi_tree()
        self.standard_model = self.tree_model.create_standard_item_model(multi_tree)

    def move_node(self, qs_item, src_path, dist_path):
        self.model.on_files_moved(src_path, dist_path)
        key_pair = ( os.path.dirname(src_path), dist_path )
        self.tree_model.recurse_replace_item_path(qs_item, key_pair)

    def rename_node(self, node_full_name, newChildName):
        parent_node_full_name = os.path.dirname(node_full_name)
        newItemName = self.model.get_available_name(parent_node_full_name, newChildName)
        self.model.on_selected_filename_changed(newItemName)
        key_pair = ( node_full_name, os.path.join(parent_node_full_name, newChildName) )
        self.tree_model.replace_tree_item_path(self.standard_model, key_pair)

        return newItemName