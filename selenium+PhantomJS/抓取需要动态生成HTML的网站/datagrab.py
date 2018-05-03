#coding:utf-8
import os
import time
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import Select
from selenium.webdriver.common.action_chains import ActionChains

_username = 'yb'
_pwd = 'yb'
_homepage = 'http://218.91.209.251:8087/Default.aspx'

_datatype = ["监测点分钟数据", "监测点小时数据", "监测点日数据", "监测点日报列表", "区域/组小时数据", "区域/组日数据", "区域/组日报列表"]

_datatypedict = {}
_datatypedict["监测点分钟数据"] = "javascript:__doPostBack('ctl00$ContentHolder$dataNameList$BulletedList1','0')"
_datatypedict["监测点小时数据"] = "javascript:__doPostBack('ctl00$ContentHolder$dataNameList$BulletedList1','1')"
_datatypedict["监测点日数据"] = "javascript:__doPostBack('ctl00$ContentHolder$dataNameList$BulletedList1','2')"
_datatypedict["监测点日报列表"] = "javascript:__doPostBack('ctl00$ContentHolder$dataNameList$BulletedList1','3')"
_datatypedict["区域/组小时数据"] = "javascript:__doPostBack('ctl00$ContentHolder$dataNameList$BulletedList1','4')"
_datatypedict["区域/组日数据"] = "javascript:__doPostBack('ctl00$ContentHolder$dataNameList$BulletedList1','5')"
_datatypedict["区域/组日报列表"] = "javascript:__doPostBack('ctl00$ContentHolder$dataNameList$BulletedList1','6')"

def saveToLocal(fn, str):
	f = open(fn,'w',encoding='utf-8')
	f.write(str)
	f.close()
	
def waitfortheElement(browser, str):
	WebDriverWait(browser, 10).until(lambda the_driver: the_driver.find_element_by_link_text(str).is_displayed())

def initDriver():
	chromedriver = "C:\Program Files (x86)\Google\Chrome\Application\chromedriver.exe"
	os.environ["webdriver.chrome.driver"] = chromedriver
	driver =  webdriver.Chrome(chromedriver)
	return driver

def grab():
	global _username
	global _pwd
	global _homepage

	browser = initDriver()
	#step1
	browser.get(_homepage)
	browser.maximize_window()
	browser.implicitly_wait(1) #隐形等待是设置了一个最长等待时间，如果在规定时间内网页加载完成，则执行下一步，否则一直等到时间截止，然后执行下一步。
	waitfortheElement(browser, "登录")
	browser.find_element_by_id('Login1_UserName').send_keys(_username)
	browser.find_element_by_id('Login1_Password').send_keys(_pwd)
	browser.find_element_by_id('Login1_btnLogin').click()
	#step2
	waitfortheElement(browser, "数据查询")
	browser.find_element_by_link_text("数据查询").click()
	
	#step3
	actions = ActionChains(browser)
	
	for dt in _datatype:
		print(dt)
		# 先定位到下拉菜单
		browser.find_element_by_xpath("//div[@id='ContentHolder_dataNameList_Panel1']/table/tbody/tr/td[@class='combo-ddb-cell']").click()
		# 再对下拉菜单中的选项进行选择
		#browser.find_element_by_link_text(dt).click()
		browser.execute_script("comboBoxItemClick(this, '"+dt+"', '"+dt+"')")
		browser.execute_script(_datatypedict[dt])
		#点击更新按钮
		time.sleep(0.2)
		#WebDriverWait(browser, 10).until(EC.visibility_of_element_located((By.ID, "btnUpdateX")))
		#browser.find_element_by_id('btnUpdateX').click()
		browser.execute_script("javascript:WebForm_DoPostBackWithOptions(new WebForm_PostBackOptions('ctl00$ContentHolder$btnUpdateX', '', true, '', '', false, true))")
		time.sleep(0.2)
		#--------------------------------------------------------------------------
		#gridview是动态生成的HTML Tag，需要等待此元素可见，才能保存page_source
		#WebDriverWait(browser, 10).until(EC.visibility_of_element_located((By.CLASS_NAME, "gridview")))
		html_source = browser.page_source
		
		soup = BeautifulSoup(html_source, "html.parser")
		#saveToLocal("output.txt", html_source)
		saveToLocal(dt.replace("/", "_")+".txt", html_source)
	
	browser.quit()
	
if __name__ == "__main__":
	grab()


	
	
	
'''
drop_down = browser.find_element_by_xpath("//div[@id='ContentHolder_dataNameList_Panel1']/table/tbody/tr/td[@class='combo-ddb-cell']")
actions.move_to_element(drop_down).click().perform()
'''