

1，HTTP状态码详解
http://tool.oschina.net/commons?type=5


如果要抓取完整的页面，只能用PhantomJS，并且要留一定时间给PhantomJS执行。urllib.request.urlopen是无法获取JavaScript和Ajax的内容。
PhantomJS is the right direction if you need the complete page source with all the JavaScript executed and async requests made. You are just missing one thing - you need to give PhantomJS time to load the page before reading the source (pun intentional).

