import my_debugger
from win32com.client import GetObject
import sys
import os

def testSoftBreakpoint():
	debugger = my_debugger.debugger()
	pid = input("Enter the PID of the process to attach to: ")
	debugger.attach(int(pid))
	printf_address = debugger.func_resolve("msvcrt.dll","printf")
	print("[*] Address of printf: 0x%08x" % printf_address)
	debugger.bp_set(printf_address)
	debugger.run()

def attachProcessToDebug():
	debugger = my_debugger.debugger()
	pid = input("Enter the PID of the process to attach to: ")
	debugger.attach(int(pid))
	debugger.run()
	debugger.detach()

def createProcessToDebug():
	debugger = my_debugger.debugger()
	debugger.load("C:\\WINDOWS\\system32\\calc.exe")

def printRegister():
	debugger = my_debugger.debugger()
	pid = input('Enter the pid: ')
	debugger.attach(int(pid))
	list_threads = debugger.enumerate_threads()
	for thread in list_threads:
		thread_context = debugger.get_thread_context(thread)
		print(thread)
		print('eax: 0x%08x' %  thread_context.Eax)
		print('ebx: 0x%08x' %  thread_context.Ebx)
		print('ecx: 0x%08x' %  thread_context.Ecx)
		print('edx: 0x%08x' % thread_context.Edx)
		print('esp: 0x%08x' %  thread_context.Esp)
	debugger.detach()
	
def attachProcessToDebug2():
	debugger = my_debugger.debugger()
	Wmi = GetObject('winmgmts:')
	processes = Wmi.InstancesOf('Win32_Process')
	# Get process
	calculator = Wmi.ExecQuery('select * from Win32_Process where Name="calc.exe"')
	# Grab its PID
	pid =calculator[0].Properties_('ProcessId').Value
	debugger.attach(int(pid))
	debugger.detach()

#printRegister()
testSoftBreakpoint()
#attachProcessToDebug()
#attachProcessToDebug2()
#createProcessToDebug()