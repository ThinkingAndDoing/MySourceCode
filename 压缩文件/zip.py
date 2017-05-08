import os
import sys
import time
import zipfile

def zipAllFiles(distPath, filename):
	compression = zipfile.ZIP_DEFLATED
	try:
		import zlib
		compression = zipfile.ZIP_DEFLATED
	except:
		compression = zipfile.ZIP_STORED
	path = distPath
	start = path.rfind(os.sep) + 1
	z = zipfile.ZipFile(filename,mode = "w",compression = compression)
	try:
		for dirpath,dirs,files in os.walk(path):
			for file in files:
				if file == filename:
					continue
				print(file)
				z_path = os.path.join(dirpath,file)
				z.write(z_path,z_path[start:])
		z.close()
	except:
		if z:
			z.close()
		
distPath = os.getcwd()+"\\Allfiles"
zipAllFiles(distPath, "myZip.zip")

