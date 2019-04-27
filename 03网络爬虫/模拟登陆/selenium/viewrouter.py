#coding:utf-8
import os
import urllib.request as res
import requests
import time
import datetime
import sendvirtualkey as keyboard
from selenium import webdriver
from selenium.webdriver.common.action_chains import ActionChains 
from selenium.webdriver.common.keys import Keys


'''
chromedriver: https://sites.google.com/a/chromium.org/chromedriver/downloads
selenium 3.4.3: https://pypi.python.org/pypi/selenium/
selenium之操作ChromeDriver: https://www.testwo.com/blog/6931
ChromeDriver executable needs to be available in the path: http://blog.csdn.net/lcm_up/article/details/38302143
'''

global _delay

_delay = 0.01

keylist = ['tab', 'tab', 'tab', 'tab', 'tab', 'tab', 'enter', 'tab', 'tab', 'tab', 'tab', 'tab', 'enter']

def key_send(str):
	keyboard.key_send(str)
	#time.sleep(_delay)

if __name__ == "__main__":
	PWD = '554637you'

	ss = str(int(time.time()//1))+'012'
	print(ss)

	chromedriver = "C:\Program Files (x86)\Google\Chrome\Application\chromedriver.exe"
	os.environ["webdriver.chrome.driver"] = chromedriver
	browser =  webdriver.Chrome(chromedriver)
	browser.get('http://192.168.1.1/')
	browser.implicitly_wait(30) #隐形等待是设置了一个最长等待时间，如果在规定时间内网页加载完成，则执行下一步，否则一直等到时间截止，然后执行下一步。
	browser.find_element_by_id('pcPassword').send_keys(PWD)
	browser.find_element_by_id('loginBtn').click()
	#time.sleep(1)
	for key in keylist:
		key_send(key)
	
	#print(browser.find_element_by_name('mainFrame').get_attribute("src"))
	print(browser.find_element_by_name('mainFrame').get_attribute("src"))
	print(browser.find_element_by_name('mainFrame').__dict__.items())
	#print(browser.find_element_by_tag_name('TITLE').__dict__.items())





'''
wanmac = browser.find_element_by_id('wanmac')
print('wan MAC:')
str_wanmac = wanmac.text
print(wanmac.text)
wanip = browser.find_element_by_id('wanip')
print('wan IP:')
str_wanip = wanip.text
print(wanip.text)
browser.find_element_by_id('menu_dhcp').click()
browser.find_element_by_id('menu_clientlist').click()
#browser.get(dhtp+ss)
hostTbl = browser.find_element_by_id('hostTbl')
str_client = hostTbl.text
print(str_client)

now = datetime.datetime.now()
str_time = now.strftime("%Y_%m_%d_%H_%M_%S")
with open(str_time+'.txt','w') as f:
    f.write(str_time+'\n\n')
    f.write('wan MAC:'+str_wanmac+'\n')
    f.write('wan IP:'+str_wanip+'\n\n')
    f.write(str_client+'\n')
'''