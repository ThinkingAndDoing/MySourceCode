# coding:utf-8
import os
import time
from selenium import webdriver
from selenium.webdriver.support.wait import WebDriverWait
import sendvirtualkey as keyboard
import threading

"""
chromedriver: https://sites.google.com/a/chromium.org/chromedriver/downloads
selenium 3.4.3: https://pypi.python.org/pypi/selenium/
selenium之操作ChromeDriver: https://www.testwo.com/blog/6931
ChromeDriver executable needs to be available in the path: http://blog.csdn.net/lcm_up/article/details/38302143


# 新开一个窗口，通过执行js来新开一个窗口
js='window.open("https://www.sogou.com");'
browser.execute_script(js)
"""

global _username
global _pwd

_username = "账号"
_pwd = "密码"
base_url = "https://passport.jd.com/new/login.aspx?ReturnUrl=https%3A%2F%2Fwww.jd.com%2F%3Fcu%3Dtrue%26utm_source%3Dbaidu-pinzhuan%26utm_medium%3Dcpc%26utm_campaign%3Dt_288551095_baidupinzhuan%26utm_term%3D0f3d30c8dba7459bb52f2eb5eba8ac7d_0_b31b8d6d73084beaa72e322277acf04e"


def str_send(str):
    keyboard.str_send(str)


def printCurTime():
    print(time.asctime(time.localtime(time.time())))
    # print(time.time())


def waitfortheElement(browser, strtext):
    WebDriverWait(browser, 10).until(
        lambda the_driver: the_driver.find_element_by_link_text(strtext).is_displayed()
    )
    # WebDriverWait(ff, 10).until(EC.presence_of_element_located((By.ID, "myDynamicElement")))


def initDriver():
    chromedriver = "C:\Program Files (x86)\Google\Chrome\Application\chromedriver.exe"
    os.environ["webdriver.chrome.driver"] = chromedriver
    driver = webdriver.Chrome(chromedriver)
    return driver


def rushOrder(tname):
    if tname == "t1":
        time.sleep(1)
    if tname == "t2":
        time.sleep(2)

    browser = initDriver()
    # print(dir(browser))
    """ """
    # step1
    browser.get(base_url)
    browser.maximize_window()
    # browser.implicitly_wait(1) #隐形等待是设置了一个最长等待时间，如果在规定时间内网页加载完成，则执行下一步，否则一直等到时间截止，然后执行下一步。
    waitfortheElement(browser, "账户登录")
    browser.find_element_by_link_text("账户登录").click()
    browser.find_element_by_id("loginname").send_keys(_username)
    browser.find_element_by_id("nloginpwd").send_keys(_pwd)
    browser.find_element_by_id("loginsubmit").click()
    # step2
    waitfortheElement(browser, "我的购物车")
    browser.find_element_by_link_text("我的购物车").click()
    # step3
    # 定位到新的页面
    while len(browser.window_handles) <= 1:
        print("I am waiting for the response from browser!")
    print(browser.current_window_handle)
    browser.switch_to_window(browser.window_handles[1])
    print(browser.current_window_handle)

    # step4
    waitfortheElement(browser, "去结算")
    while True:
        try:
            browser.find_element_by_link_text("去结算").click()
            print("click 去结算")
            time.sleep(0.01)
        except:
            break
    # step5
    WebDriverWait(browser, 10).until(
        lambda the_driver: the_driver.find_element_by_id("order-submit").is_displayed()
    )
    # print(browser.window_handles)
    prePrice = browser.find_element_by_id("warePriceId").get_attribute("v")
    while True:
        curPrice = browser.find_element_by_id("warePriceId").get_attribute("v")
        if curPrice != prePrice and int(float(curPrice)) < 10:
            break
        else:
            printCurTime()
            print(curPrice)
            print(tname)
            browser.refresh()
            # browser.execute_script("location.reload()")
    browser.find_element_by_id("order-submit").click()

    waitfortheElement(browser, "立即支付")
    time.sleep(0.1)
    str_send("密码")
    # time.sleep(1)
    browser.find_element_by_link_text("立即支付").click()
    # browser.find_element_by_tag_name("xmp").send_keys("2345")


if __name__ == "__main__":
    # rushOrder()

    threads = []
    threads.append(threading.Thread(target=rushOrder, args=("t1",)))
    threads.append(threading.Thread(target=rushOrder, args=("t2",)))

    for t in threads:
        t.setDaemon(True)
        t.start()
    t.join()  # 等待其他线程结束
