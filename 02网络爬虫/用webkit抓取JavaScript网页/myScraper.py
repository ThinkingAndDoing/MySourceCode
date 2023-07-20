#!/usr/bin/python3
# -*- coding: UTF-8 -*-

"""
Title -> Scraping JavaScript webpages with webkit
PyQt5 Components: http://pyqt.sourceforge.net/Docs/PyQt5/introduction.html#module-PyQt5.QtWebEngineWidgets
Porting from Qt WebKit to Qt WebEngine: http://doc.qt.io/qt-5/qtwebenginewidgets-qtwebkitportingguide.html
pyqt5_scraper.py: https://gist.github.com/brbsix/e5d633077025f14892e5075e1fd46bc5
PyQt5应用与实践: http://www.cnblogs.com/skynet/p/4229556.html
"""
# standard imports
import sys

# third-party imports
import requests
from PyQt5.QtCore import QEventLoop
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtWidgets import QApplication


class Render(QWebEngineView):
    """Render HTML with PyQt5 WebEngine."""

    def __init__(self, html):
        self.html = None
        self.app = QApplication(sys.argv)
        QWebEngineView.__init__(self)
        self.loadFinished.connect(self._loadFinished)
        self.setHtml(html)
        while self.html is None:
            self.app.processEvents(
                QEventLoop.ExcludeUserInputEvents
                | QEventLoop.ExcludeSocketNotifiers
                | QEventLoop.WaitForMoreEvents
            )
            self.app.quit()

    def _callable(self, data):
        self.html = data

    def _loadFinished(self, result):
        self.page().toHtml(self._callable)


url = "http://192.168.1.1/"

# get the raw HTML
source_html = requests.get(url).text

# return the JavaScript rendered HTML
file = open("foo.txt", "w", encoding="utf-8")
try:
    data = Render(source_html).html
    file.write(data)
finally:
    file.close()
