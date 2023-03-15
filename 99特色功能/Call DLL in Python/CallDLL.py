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
	
def on_warning_changed(curWrnID):
	'''
	This functiion will be called in DLL
	'''
	print("curWrnID is "+str(curWrnID))

def register_callback_func(myDll):

	callbackFunc = ctypes.CFUNCTYPE(ctypes.c_bool, ctypes.c_int)(on_warning_changed)
	gCallbackFuncList.append(callbackFunc) #There is an error if this line is missing. OSError: exception: access violation writing 0x00000000
	myDll.dllRegisterPythonFunc(callbackFunc)
	
def verify_immediate():
	'''
	NotiID = 98, priority = 4, Immediate = false
	NotiID = 99, priority = 6, Immediate = true
	NotiID = 241, priority = 8, Immediate = false
	'''
	wm = get_warning_manager_dll(False)
	register_callback_func(wm)
	wm.init()
	wm.RequestWarning(98)
	time.sleep(0.5)
	wm.RequestWarning(99)
	time.sleep(0.5)
	wm.RequestWarning(241)

if __name__ == "__main__":  
	
	verify_immediate()
	while(True):
		pass
		
		
		