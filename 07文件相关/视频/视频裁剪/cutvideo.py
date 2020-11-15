# -*- coding: utf-8 -*- 

import subprocess
import os
from lib.jsonio import Jsoner

import platform
print (platform.python_version())
import pandas as pd
str_ffmpegPath = "C:\\Users\\Administrator\\Downloads\\ffmpeg-20200713-7772666-win64-static\\bin\\ffmpeg.exe"
#str_ffmpegPath = "D:\\01Myprogram\\ffmpeg-20200713-7772666-win64-static\\bin\\ffmpeg.exe"
#dict_video = {"file_name":"乌里：外科手术式打击BD中字.mkv", "start_time":"00:02:23", "end_time":"00:13:13"}
'''
subprocess.call('C:\\Users\\Administrator\\Downloads\\ffmpeg-20200713-7772666-win64-static\\bin\\ffmpeg.exe -y -i test.mp4 -ss 00:00:0.0 -t 00:00:40.0 -acodec copy -vcodec copy -async 1 test2.mp4')
subprocess.call('C:\\Users\\Administrator\\Downloads\\ffmpeg-20200713-7772666-win64-static\\bin\\ffmpeg.exe -y -i test.mp4 -ss 00:00:0.0 -to 00:01:40.0 -acodec copy -vcodec copy -async 1 test2.mp4')
从00:00:0.0起截取40秒ffmpeg -y -i test.mp4 -ss 00:00:0.0 -t 00:00:40.0 -acodec copy -vcodec copy -async 1 test2.mp4
从00:00:0.0起截到1分40秒ffmpeg -y -i test.mp4 -ss 00:00:0.0 -to 00:01:40.0 -acodec copy -vcodec copy -async 1 test2.mp4
顺时针旋转画面90度ffmpeg -i test.mp4 -vf "transpose=1" out.mp4
逆时针旋转画面90度ffmpeg -i test.mp4 -vf "transpose=2" out.mp4
顺时针旋转画面90度再水平翻转ffmpeg -i test.mp4 -vf "transpose=3" out.mp4
逆时针旋转画面90度水平翻转ffmpeg -i test.mp4 -vf "transpose=0" out.mp4
水平翻转视频画面ffmpeg -i test.mp4 -vf hflip out.mp4
垂直翻转视频画面ffmpeg -i test.mp4 -vf vflip out.mp4
// 去掉视频中的音频
ffmpeg -i input.mp4 -vcodec copy -an output.mp4
// -an: 去掉音频；-vcodec:视频选项，一般后面加copy表示拷贝

// 提取视频中的音频
ffmpeg -i input.mp4 -acodec copy -vn output.mp3
// -vn: 去掉视频；-acodec: 音频选项， 一般后面加copy表示拷贝

// 音视频合成
ffmpeg -y –i input.mp4 –i input.mp3 –vcodec copy –acodec copy output.mp4
// -y 覆盖输出文件

//剪切视频
ffmpeg -ss 0:1:30 -t 0:0:20 -i input.mp4 -vcodec copy -acodec copy output.mp4
// -ss 开始时间; -t 持续时间

// 视频截图
ffmpeg –i test.mp4 –f image2 -t 0.001 -s 320x240 image-%3d.jpg
// -s 设置分辨率; -f 强迫采用格式fmt;

// 视频分解为图片
ffmpeg –i test.mp4 –r 1 –f image2 image-%3d.jpg
// -r 指定截屏频率

// 将图片合成视频
ffmpeg -f image2 -i image%d.jpg output.mp4

//视频拼接
ffmpeg -f concat -i filelist.txt -c copy output.mp4

// 将视频转为gif
ffmpeg -i input.mp4 -ss 0:0:30 -t 10 -s 320x240 -pix_fmt rgb24 output.gif
// -pix_fmt 指定编码

// 将视频前30帧转为gif
ffmpeg -i input.mp4 -vframes 30 -f gif output.gif

// 旋转视频
ffmpeg -i input.mp4 -vf rotate=PI/2 output.mp4

// 缩放视频
ffmpeg -i input.mp4 -vf scale=iw/2:-1 output.mp4
// iw 是输入的宽度， iw/2就是一半;-1 为保持宽高比

//视频变速
ffmpeg -i input.mp4 -filter:v setpts=0.5*PTS output.mp4

//音频变速
ffmpeg -i input.mp3 -filter:a atempo=2.0 output.mp3

//音视频同时变速，但是音视频为互倒关系
ffmpeg -i input.mp4 -filter_complex "[0:v]setpts=0.5*PTS[v];[0:a]atempo=2.0[a]" -map "[v]" -map "[a]" output.mp4


// 视频添加水印
ffmpeg -i input.mp4 -i logo.jpg -filter_complex [0:v][1:v]overlay=main_w-overlay_w-10:main_h-overlay_h-10[out] -map [out] -map 0:a -codec:a copy output.mp4
// main_w-overlay_w-10 视频的宽度-水印的宽度-水印边距；
// 截取视频局部
ffmpeg -i in.mp4 -filter:v "crop=out_w:out_h:x:y" out.mp4
// 截取部分视频，从[80,60]的位置开始，截取宽200，高100的视频
ffmpeg -i in.mp4 -filter:v "crop=80:60:200:100" -c:a copy out.mp4
// 截取右下角的四分之一
ffmpeg -i in.mp4 -filter:v "crop=in_w/2:in_h/2:in_w/2:in_h/2" -c:a copy out.mp4
// 截去底部40像素高度
ffmpeg -i in.mp4 -filter:v "crop=in_w:in_h-40" -c:a copy out.mp4
-vcodec xvid 使用xvid压缩
-s 320x240 指定分辨率
-r fps 设置帧频 缺省25
-b <比特率> 指定压缩比特

-acodec aac 设定声音编码
-ac <数值> 设定声道数，1就是单声道，2就是立体声
-ar <采样率> 设定声音采样率，PSP只认24000
-ab <比特率> 设定声音比特率
-vol <百分比> 设定音量

-y（覆盖输出文件

-t duration 设置纪录时间 hh:mm:ss[.xxx]格式的记录时间也支持
-ss position 搜索到指定的时间 [-]hh:mm:ss[.xxx]的格式也支持
-title string 设置标题
-author string 设置作者

'''
def cutVideo(dict_v):

    save_name = "Fragment_"+dict_v["file_name"]
    
    cmd = str_ffmpegPath + ' -y -i ' +  dict_v["file_name"] + ' -ss ' + dict_v["start_time"] + ' -to '+ dict_v["end_time"] + ' -acodec copy -vcodec copy -async 1 ' + save_name
    subprocess.call(cmd)

def cutVideos(df):
	
	rows = df.shape[0]
	for i in range(0, rows):
		dict = {}
		dict["file_name"] = df.loc[i,"file_name"]
		dict["start_time"] = df.loc[i,"start_time"]
		dict["end_time"] = df.loc[i,"end_time"]
		try:
			cutVideo(dict)
		except:
			pass

if __name__ == '__main__':
    #js = Jsoner.readJson("C:\\Users\\uidp8103\\Desktop\\1.json")
    #cutVideo(js)
	data = pd.read_csv("fileName.csv")
	cutVideos(data)
