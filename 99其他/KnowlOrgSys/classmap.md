@startuml


class QMainWindow{
    
}

class MarkdownView{
+model
}

class Model{
+md_path
+file_path
+file_selected
}

class MultiTree{
+root
}

class ViewModel{
+model
+tree_model
+standard_model
}

class KosTextBrowser{
+file_to_be_copied
}

class View{
+view_model
}

class TreeModel{
    
}

MarkdownView <|-- View
QMainWindow <|-- MarkdownView
QTextBrowser <|-- KosTextBrowser
MarkdownView *-- KosTextBrowser
View *-- ViewModel
ViewModel *-- Model
Model *-- MultiTree
ViewModel *-- TreeModel

@enduml