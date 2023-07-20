# -*- coding: UTF-8 -*-
import albumdownloader
import albumset
import os


def loadPicSetFromLocal(albumdir):
    dictAlbumset = []

    for root, dirs, files in os.walk(albumdir, topdown=False):
        for name in files:
            try:
                filename = os.path.join(root, name)
                data = readJson(filename)
                data["title"] = name[:-5]
                dictAlbumset.append(data)
            except Exception as e:
                continue
                # print(e)
    return dictAlbumset


if __name__ == "__main__":
    listSource = []

    # _listSource.append("http://xxx/thread.php?fid=26&page=1")
    for i in range(1, 2):
        listSource.append(
            "http://xxx/thread.php?fid-26-orderway-favors-asc-DESC-page-"
            + str(i)
            + ".html"
        )

    theAlbumset = albumset.Albumset(listSource)
    theAlbumset.createAlbumset()

    # dictAlbumset = loadPicSetFromLocal("albumset")

    """
    #start download album
    for ps in dictAlbumset:
        theDownloader = albumdownloader.ListOfPhotos()
        theDownloader.setUrlListAndPath(ps["urllist"],ps["title"])
        theDownloader.startDownload()
	"""
