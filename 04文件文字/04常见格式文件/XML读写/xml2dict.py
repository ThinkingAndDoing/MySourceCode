import xmltodict
import json
import re


# xml to json
def xmlToJson(xml_str):
    try:
        json_dict = xmltodict.parse(xml_str, encoding="utf-8")
        json_str = json.dumps(json_dict, indent=2)
        return json_str
    except:
        pass


# json to xml
def jsonToXml(json_str):
    try:
        json_dict = json.loads(json_str)
        xml_str = xmltodict.unparse(json_dict, encoding="utf-8")
    except:
        xml_str = xmltodict.umparse({"request": json_dict}, encoding="utf-8")
    finally:
        return xml_str


# load xml file
def load_json(xml_path):
    # 获取xml文件
    xml_file = open(xml_path, "r", encoding="utf-8")
    xml_str = xml_file.read()
    # 将读取的xml字符串转换为字典
    json_dict = xmltodict.parse(xml_str)
    # 将字典转换为json格式的字符串
    json_str = json.dumps(json_dict, indent=2)
    return json_str


def loadFromLocal(fn):
    file = open(fn, "r")
    return file.read()


if __name__ == "__main__":
    js = load_json("strings.xml")
    print(js)
