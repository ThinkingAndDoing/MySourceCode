import ctypes
import os

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
	
def on_warning_changed(intParam):
	'''
	This functiion will be called in DLL
	'''
	print(intParam)

def register_callback_func(myDll):

	callbackFunc = ctypes.CFUNCTYPE(ctypes.c_bool, ctypes.c_int)(on_warning_changed)
	gCallbackFuncList.append(callbackFunc) #There is an error if this line is missing. OSError: exception: access violation writing 0x00000000
	myDll.dllRegisterPythonFunc(callbackFunc)
	
if __name__ == "__main__":  
	
	wm = get_warning_manager_dll(False)
	register_callback_func(wm)
	wm.init()
	wm.RequestWarning(98)
	wm.ReleaseWarning(98)
	
	while(True):
		pass