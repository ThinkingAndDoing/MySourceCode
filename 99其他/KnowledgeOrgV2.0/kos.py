# -*- coding: UTF-8 -*-

# KOS: knowledge organization system, MVVM mode
# Version 2.0

import os
import sys
from PyQt5.QtWidgets import QApplication
from ui import *
import kos_model
import kos_viewmodel
import kos_view


if __name__ == "__main__":
    app = QApplication(sys.argv)

    src_path = "D:\\03SourceCode\\yy_Doc\\InformationManagement\\AMP4"

    if len(sys.argv) > 1 and os.path.exists(sys.argv[1]):
        src_path = sys.argv[1]

    model = kos_model.Model(src_path)
    viewmodel = kos_viewmodel.ViewModel(model)
    myWin = kos_view.View()
    myWin.set_view_model(viewmodel)

    myWin.show()
    sys.exit(app.exec_())
