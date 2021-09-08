#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import win32evtlog

class EventLog:
	def __init__(self, s, l):
		self.server = s
		self.logtype = l
		self.flags = win32evtlog.EVENTLOG_BACKWARDS_READ|win32evtlog.EVENTLOG_SEQUENTIAL_READ
		
	def get_events_by_SourceName(self, srcName):
	
		listEventRec = []
		readNum = 0
		hand= win32evtlog.OpenEventLog(self.server, self.logtype)
		total = win32evtlog.GetNumberOfEventLogRecords(hand)
		
		while total>readNum:
			events = win32evtlog.ReadEventLog(hand, self.flags,0)
			readNum += len(events)
			for event in events:
				if event.SourceName == srcName:
					#self.print_event_info(event)
					listEventRec.append(event)
		win32evtlog.CloseEventLog(hand)
		return listEventRec
		
	def print_event_info(self, event):
		print( 'Event Category:', event.EventCategory )
		print( 'Time Generated:', event.TimeGenerated )
		print( 'Source Name:', event.SourceName )
		print( 'Event ID:', event.EventID )
		print( 'Event Type:', event.EventType )
 
def print_daily_poweron_shutdown_time():

	eLog = EventLog("localhost", "System")
	listBoot = eLog.get_events_by_SourceName("Microsoft-Windows-Kernel-Boot")
	listPower = eLog.get_events_by_SourceName("Microsoft-Windows-Kernel-Power")
	dictPowerOnTime = {}
	dictPowerOffTime = {}

	for e in listBoot:
		dictPowerOnTime[ str(e.TimeGenerated.date()) ] = str(e.TimeGenerated.time())
		
	for e in listPower:
		if str(e.TimeGenerated.date()) not in dictPowerOffTime.keys():
			dictPowerOffTime[ str(e.TimeGenerated.date()) ] = str(e.TimeGenerated.time())
	
	listSystemWorkTime = []
	allKeys = set(dictPowerOnTime.keys()) | set(dictPowerOffTime.keys())
	
	for k in sorted( list(allKeys) ):
		if k in dictPowerOnTime.keys():
			startTime = dictPowerOnTime[k]
		else:
			startTime = "Null"
		if k in dictPowerOffTime.keys():
			endTime = dictPowerOffTime[k]
		else:
			endTime = "Null"
		listSystemWorkTime.append("date:"+k+", start:"+startTime+", end:"+endTime)
		
	for t in listSystemWorkTime:
		print(t)

		
if __name__=="__main__":
	
	print_daily_poweron_shutdown_time()


	