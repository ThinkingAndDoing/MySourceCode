from PyQt5 import QtGui, QtWidgets
import markdown
import re

def get_html_text(plain_text):
    html_text = markdown.markdown(plain_text)
    #replace \n as <br/> between <p> and </p>
    html_text = re.sub(r'<p>.*?</p>', lambda x: x.group().replace('\n', '<br/>'), html_text, flags=re.DOTALL)
    #keep all space
    html_text = "<pre>" + html_text + "</pre>"
    return html_text

if __name__ == '__main__':
    import sys

    text = "hello.你好"*200
    app = QtWidgets.QApplication(sys.argv)
    w = QtWidgets.QTextBrowser()
    w.setStyleSheet('color: blue') 
    w.setFont(QtGui.QFont("Monospace"))
    w.setWordWrapMode(QtGui.QTextOption.WordWrap)
    w.setText(get_html_text(text))
    w.showMaximized()
    sys.exit(app.exec_())