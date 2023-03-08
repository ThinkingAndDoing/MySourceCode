import ctypes
import os

def get_warning_manager():

	dll_path = r".\ConsoleApplication2\Release\ConsoleApplication2.dll"

	if os.path.exists(dll_path):
		lib = ctypes.cdll.LoadLibrary(dll_path)
		print( lib.add(1, 2) )
	else:
		print("Can't find dll.")
	
	return lib
		
if __name__ == "__main__":  
	
	wm = get_warning_manager()
	wm.RequestWarning(10)
	wm.ReleaseWarning(11)
	print(wm.GetActiveWarningID())