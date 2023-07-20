import os
import exifread
import hashlib
import time
import argparse
import shutil


def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-src",
        "--srcpath",
        help="absolute path to copy image from.",
        default=r".\\images",
    )
    parser.add_argument(
        "-dst", "--dstpath", help="absolute path to copy image to.", default=r"."
    )
    parser.add_argument(
        "-tt",
        "--timetype",
        help="rename by create time(ctime) or modify time(mtime).",
        default=r"ctime",
    )

    args = parser.parse_args()

    return args


def md5sum(filename):
    f = open(filename, "rb")
    md5 = hashlib.md5()
    while True:
        fb = f.read(8096)
        if not fb:
            break
        md5.update(fb)
    f.close()
    return md5.hexdigest()


class CopyPic:
    def __init__(self, src, dst):
        self.srcImgPath = src
        self.dstImgPath = dst
        self.timeType = "ctime"

    def set_time_type(self, tt):
        if tt == "ctime" or tt == "mtime":
            self.timeType = tt

    def start_copy(self):
        imgpath = self.srcImgPath
        for filename in os.listdir(imgpath):
            fullPath = os.path.join(imgpath, filename)
            if os.path.isfile(fullPath):
                try:
                    dImgDic = self.get_exif_dict(fullPath)

                    if self.timeType == "ctime":
                        tmCtime = dImgDic["ctime"]
                    elif self.timeType == "mtime":
                        tmCtime = dImgDic["mtime"]
                    else:
                        tmCtime = dImgDic["ctime"]

                    strNewFileName = (
                        "["
                        + str(tmCtime.tm_year)
                        + "年"
                        + str(tmCtime.tm_mon)
                        + "月"
                        + str(tmCtime.tm_mday)
                        + "日"
                        + str(tmCtime.tm_hour)
                        + "时"
                        + str(tmCtime.tm_min)
                        + "分"
                        + str(tmCtime.tm_sec)
                        + "秒]"
                        + dImgDic["hash"][:6]
                        + os.path.splitext(filename)[1]
                    )

                    dImgDic["newfilename"] = os.path.join(
                        self.dstImgPath, strNewFileName
                    )
                    shutil.copy(dImgDic["oldfilename"], dImgDic["newfilename"])

                    print(
                        dImgDic["oldfilename"]
                        + " has been copied to "
                        + dImgDic["newfilename"]
                        + " !"
                    )

                except Exception as e:
                    print("Can't copy image " + fullPath + " !")
                    print(e)

    def get_exif_dict(self, filename):
        dImgDic = {}
        fullPath = filename
        fd = open(fullPath, "rb")
        tags = exifread.process_file(fd)
        fd.close()

        dImgDic["oldfilename"] = fullPath
        dImgDic["hash"] = md5sum(fullPath)

        if "EXIF DateTimeOriginal" in tags:
            dImgDic["ctime"] = tags["EXIF DateTimeOriginal"].printable
            dImgDic["ctime"] = time.strptime(dImgDic["ctime"], "%Y:%m:%d %H:%M:%S")
        else:
            dImgDic["ctime"] = time.localtime(os.path.getctime(fullPath))

        dImgDic["mtime"] = time.localtime(os.path.getmtime(fullPath))

        if "GPS GPSLatitudeRef" in tags:
            LatRef = tags["GPS GPSLatitudeRef"].printable
            Lat = (
                tags["GPS GPSLatitude"]
                .printable[1:-1]
                .replace(" ", "")
                .replace("/", ",")
                .split(",")
            )
            if len(Lat) == 3:
                Lat.append("1")
            Lat = (
                float(Lat[0])
                + float(Lat[1]) / 60
                + float(Lat[2]) / float(Lat[3]) / 3600
            )
            if LatRef != "N":
                Lat = Lat * (-1)
            dImgDic["latitude"] = str(Lat)
        else:
            dImgDic["latitude"] = ""

        if "EXIF GPSLongitudeRef" in tags:
            LonRef = tags["GPS GPSLongitudeRef"].printable
            Lon = (
                tags["GPS GPSLongitude"]
                .printable[1:-1]
                .replace(" ", "")
                .replace("/", ",")
                .split(",")
            )
            if len(Lon) == 3:
                Lon.append("1")
            Lon = (
                float(Lon[0])
                + float(Lon[1]) / 60
                + float(Lon[2]) / float(Lon[3]) / 3600
            )
            if LonRef != "E":
                Lon = Lon * (-1)
            dImgDic["longitude"] = str(Lon)
        else:
            dImgDic["longitude"] = ""

        return dImgDic


if __name__ == "__main__":
    args = get_args()
    c = CopyPic(args.srcpath, args.dstpath)
    c.set_time_type(args.timetype)
    c.start_copy()
