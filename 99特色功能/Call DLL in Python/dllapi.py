import ctypes
import os
import time


gCallbackFuncList = []

def get_warning_manager_dll(winDll=False):
	
	dllDir = r".\ConsoleApplication2\Release\ConsoleApplication2.dll"
	if os.path.exists(dllDir):
		if winDll:
			WrnManageDll = ctypes.WinDLL(dllDir)
		else:
			WrnManageDll = ctypes.CDLL(dllDir)
		return WrnManageDll
	else:
		print("Can't find dll.")
	
	
def verify_immediate(vm):
	'''
	NotiID = 98, priority = 4, Immediate = false
	NotiID = 99, priority = 6, Immediate = true
	NotiID = 241, priority = 8, Immediate = false
	'''
	wm.RequestWarning(98)
	time.sleep(0.5)
	wm.RequestWarning(99)
	time.sleep(0.5)
	wm.RequestWarning(241)
	
def verify_userlocktime(vm):
	'''
	NotiID = 98, userlocktime = 2000, minidisplaytime = 4000, 
	'''
	wm.RequestWarning(98)
	time.sleep(0.5)
	wm.ProcessVirtualKey(4)
	time.sleep(1)
	wm.ProcessVirtualKey(4)
	time.sleep(2)
	wm.ProcessVirtualKey(4)
	
def verify_telltale(vm):
	'''
	{ AutoHoldTT, 4 },
	{ TurnLeftTT, 8 },
	{ TurnRightTT, 5 },
	'''
	wm.RequestTelltale(0)
	time.sleep(0.5)
	wm.RequestTelltale(1)
	time.sleep(0.5)
	wm.RequestTelltale(2)
	time.sleep(0.5)
	wm.ReleaseTelltale(1)
	time.sleep(0.5)
	wm.ReleaseTelltale(2)	
	time.sleep(0.5)
	wm.ReleaseTelltale(0)
	
def print_warninglist(vm):
	
	print("+"*10)
	i = 0
	while wm.GetWarningIDFromStack(i) != 245:
		print("WarningItem = "+str(wm.GetWarningIDFromStack(i)))
		i = i+1
	print("-"*10)
	
def verify_warninglist(vm):
	'''
	NotiID = 98, userlocktime = 2000, minidisplaytime = 4000, 
	'''
	wm.RequestWarning(98)
	time.sleep(0.5)
	wm.ProcessVirtualKey(4)
	time.sleep(1)
	wm.ProcessVirtualKey(4)
	time.sleep(2)
	wm.ProcessVirtualKey(4)
	print_warninglist(vm)
	time.sleep(1)
	wm.RequestWarning(192)
	time.sleep(7)
	print_warninglist(vm)
	
	
def verify_warningmode(vm):
	'''
	NotiID = 98, priority = 4, Immediate = false
	NotiID = 99, priority = 6, Immediate = true
	NotiID = 241, priority = 8, Immediate = false
	'''
	wm.SetWarningMode(3)
	wm.RequestWarning(98)
	time.sleep(0.5)
	wm.RequestWarning(99)
	time.sleep(0.5)
	wm.RequestWarning(241)
	wm.SetWarningMode(4)
	
if __name__ == "__main__":  
	
	wm = get_warning_manager_dll(False)
	register_callback_func(wm)
	wm.init()
	#verify_telltale(wm)
	#verify_immediate(wm)
	#verify_userlocktime(wm)
	#verify_warninglist(wm)
	verify_warningmode(wm)
	while(True):
		pass
		
		
		