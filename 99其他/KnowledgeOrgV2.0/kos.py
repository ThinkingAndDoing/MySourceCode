# -*- coding: UTF-8 -*-

# KOS: knowledge organization system, MVVM mode
# Version 2.0
"""
Todo:
1, the file is often very large, it is not appropriate to add the system to manage, therefore, to change to support only the file path can be. It is recommended that all files are placed in a fixed location such as D:\.kos_file_library
2, md files are placed in a folder, is not very wise way, when the md file is very much, parallel editing renaming problem is not good to solve, so it is necessary to change the file naming.

Advantages compared to 1.0:
1, support for inserting pictures, links and files.
"""
#    src_path = "D:\\03SourceCode\\yy_Doc\\InformationManagement\\CyberSecurity"

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
        "-mf",
        "--mdfile",
        help="Specify the path where all md files are stored.",
        default=r".",
    )
    parser.add_argument(
        "-if", "--insertedfile", help="Specify the path where all inserted files are stored.", default="D:\\.kos_file_library"
    )
    args = parser.parse_args()

    return args

if __name__ == "__main__":
    app = QApplication(sys.argv)

    inputArgs = get_args()

    model = kos_model.Model()
    if model.set_path(inputArgs.mdfile):
        viewmodel = kos_viewmodel.ViewModel(model)
        myWin = kos_view.View()
        myWin.set_view_model(viewmodel)
        myWin.show()
        sys.exit(app.exec_())
    else:
        print(f"Can't find the md file.\nPlease check md file path: {inputArgs.mdfile}")
        app.quit()
