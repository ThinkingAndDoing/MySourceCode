import pandas as pd


def getNotifDF(df):
	indexList = []
	indexList.append("Notification ID")
	indexList.append("Priority")
	indexList.append("Usage mode value - See explanation sheet")
	indexList.append("Display Timeout [ms]")
	indexList.append("Minimum Display Time [ms]")
	indexList.append("User lock time [ms]")
	indexList.append("Draft text")
	indexList.append("Display position")
	indexList.append("Notification分类")
	indexList.append("文本更正")
	indexList.append("中文")
	return df[indexList]
	
def getWrnListDF(df):
	indexList = []
	indexList.append("PIFLName")
	indexList.append("notification ID Geely")
	return df[indexList]
	
if __name__=="__main__":

	notifDF = pd.DataFrame(pd.read_excel('Notification Database DIM-E3 Freeze.xlsx', sheet_name="Notifications_GEEA2.0"))
	notifDF = getNotifDF(notifDF)
	wrnlistDF = pd.DataFrame(pd.read_excel('TT&&WRN_List.xlsx', sheet_name="Text_Message"))
	wrnlistDF = getWrnListDF(wrnlistDF)
	wrnlistDF = wrnlistDF.rename(columns={'notification ID Geely' : 'Notification ID'})
	newDF = pd.merge(notifDF, wrnlistDF, on='Notification ID', how='outer')
	newDF = newDF.fillna("NA")
	newDF.to_excel('excel_to_python.xlsx',sheet_name='new',index=False) 

