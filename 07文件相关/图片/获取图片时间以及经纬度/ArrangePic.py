import os
import exifread


lImgDictList = []
#dImgDic={"ctime":"", "latitude":"", "longitude":"", "hash":"", "filename":""}
# os.rename(old_full_file_name, new_full_file_name)


def getExif(imgpath, filename):
    dImgDic = {}
    old_full_file_name = os.path.join(imgpath, filename)
    fd = open(old_full_file_name, 'rb')
    tags = exifread.process_file(fd)
    fd.close()
    
    dImgDic["filename"] = old_full_file_name
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
    
    if "EXIF DateTimeOriginal" in tags:
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
    
    print(dImgDic)
        
def reOrderImgs(strSrcImg):
    imgpath = strSrcImg
    for filename in os.listdir(imgpath):
        full_file_name = os.path.join(imgpath, filename)
        if os.path.isfile(full_file_name):
           getExif(imgpath, filename)
           #break

if __name__=="__main__":

    reOrderImgs("C:\\Users\\Administrator\\Desktop\\test\\2016")

