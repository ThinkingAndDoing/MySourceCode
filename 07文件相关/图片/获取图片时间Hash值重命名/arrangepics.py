import os
import exifread
import hashlib
import time

lImgDictList = []
#dImgDic={"ctime":"", "latitude":"", "longitude":"", "hash":"", "oldfilename":"", "newfilename":""}
# os.rename(old_full_file_name, new_full_file_name)

def md5sum(filename):
	f=open(filename, 'rb')
	md5=hashlib.md5()
	while True:
		fb = f.read(8096)
		if not fb:
			break
		md5.update(fb)
	f.close()
	return (md5.hexdigest())

def getExif(imgpath, filename):
    print(filename)
    dImgDic = {}
    old_full_file_name = os.path.join(imgpath, filename)
    fd = open(old_full_file_name, 'rb')
    tags = exifread.process_file(fd)
    fd.close()
    
    dImgDic["oldfilename"] = old_full_file_name
    if "EXIF DateTimeOriginal" in tags:
        dImgDic["ctime"] = tags["EXIF DateTimeOriginal"].printable
    else:
        dImgDic["ctime"] = ""
    
    if "GPS GPSLatitudeRef" in tags:
        LatRef=tags["GPS GPSLatitudeRef"].printable
        Lat=tags["GPS GPSLatitude"].printable[1:-1].replace(" ","").replace("/",",").split(",")
        if len(Lat)==3:
            Lat.append("1")
        Lat=float(Lat[0])+float(Lat[1])/60+float(Lat[2])/float(Lat[3])/3600
        if LatRef != "N":
            Lat=Lat*(-1)
        dImgDic["latitude"] = str(Lat)
    else:
        dImgDic["latitude"] = ""
    
    if "EXIF GPSLongitudeRef" in tags:
        LonRef=tags["GPS GPSLongitudeRef"].printable
        Lon=tags["GPS GPSLongitude"].printable[1:-1].replace(" ","").replace("/",",").split(",")
        if len(Lon)==3:
            Lon.append("1")
        Lon=float(Lon[0])+float(Lon[1])/60+float(Lon[2])/float(Lon[3])/3600
        if LonRef!="E":
            Lon=Lon*(-1)
        dImgDic["longitude"] = str(Lon)
    else:
        dImgDic["longitude"] = ""
    
    dImgDic["hash"] = md5sum(old_full_file_name)
    
    if dImgDic["ctime"]!="":
        tmCtime = time.strptime(dImgDic["ctime"], '%Y:%m:%d %H:%M:%S')
        strNewFileName = "["+str(tmCtime.tm_year) + "年" +str(tmCtime.tm_mon)+"月"+str(tmCtime.tm_mday)+"日]"+ dImgDic["hash"][:6]+os.path.splitext(filename)[1]
    else:
        strNewFileName = dImgDic["hash"]+os.path.splitext(filename)[1]
    dImgDic["newfilename"] = os.path.join(imgpath, strNewFileName)
    os.rename(dImgDic["oldfilename"], dImgDic["newfilename"])
    print(dImgDic)
        
def reOrderImgs(strSrcImg):
    imgpath = strSrcImg
    for filename in os.listdir(imgpath):
        full_file_name = os.path.join(imgpath, filename)
        if os.path.isfile(full_file_name):
           getExif(imgpath, filename)
           #break

if __name__=="__main__":

    reOrderImgs("E:\\娱乐\\图片\\我的照片\\2018")

