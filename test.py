#!/usr/bin/python3
# -*- coding: UTF-8 -*-

'''
Title -> Scraping JavaScript webpages with webkit
Url -> https://webscraping.com/blog/Scraping-JavaScript-webpages-with-webkit/

Title -> PyQt Usage
Url -> http://www.cnblogs.com/skynet/p/4229556.html
'''

import sys  
from PyQt4.QtGui import *  
from PyQt4.QtCore import *  
from PyQt4.QtWebKit import *  

class Render(QWebPage):
  def __init__(self, url):
    self.app = QApplication(sys.argv)
    QWebPage.__init__(self)
    self.loadFinished.connect(self._loadFinished)
    self.mainFrame().load(QUrl(url))
    self.app.exec_()

  def _loadFinished(self, result):
    self.frame = self.mainFrame()
    self.app.quit()

url = 'http://webscraping.com'
r = Render(url)
html = r.frame.toHtml()
