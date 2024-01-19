# -*- coding: UTF-8 -*-

# KOS: knowledge organization system, MVVM mode
# Version 3.0
"""
Todo:
NA

History:
1, support for inserting pictures, links and files.
2, the file is often very large, it is not appropriate to add the system to manage, therefore, to change to support only the file path can be. 
   It is recommended that all files are placed in a fixed location such as D:\.kos_file_library
3, md files are placed in a folder, is not very wise way, when the md file is very much, parallel editing renaming problem is not good to solve, 
   so it is necessary to change the file naming.
4, Generating mind maps

"""

import os
import sys
from PyQt5.QtWidgets import QApplication
import kos_model
import kos_viewmodel
import kos_view
import argparse


def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-mp",
        "--md_path",
        help="Specify the path where all md files are stored.",
        default=r".",
    )
    parser.add_argument(
        "-fp",
        "--file_path",
        help="Specify the path where all inserted files are stored.",
        default="D:\\.kos_file_library",
    )
    args = parser.parse_args()

    return args


if __name__ == "__main__":
    app = QApplication(sys.argv)
    input_args = get_args()
    md_path, file_path = input_args.md_path, input_args.file_path

    if os.path.exists(md_path) and os.path.exists(file_path):
        model = kos_model.Model(md_path, file_path)
        view_model = kos_viewmodel.ViewModel(model)
        view = kos_view.View(view_model)
        view.update_tree_view()
        view.show()
        sys.exit(app.exec_())
    else:
        print(
            f"Can't find the md file or inserted file.\nPlease check path: {md_path}, {file_path}"
        )
        app.quit()
