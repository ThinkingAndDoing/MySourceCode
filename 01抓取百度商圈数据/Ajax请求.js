//����HTTP���󣬻�ȡJson���ݣ�������ʡ�
$.ajax({
    type: "GET",
    //url: "http://api.map.baidu.com/shangquan/forward/?qt=sub_area_list&ext=1&level=1&areacode=1550&business_flag=1&callback=BMap._rd._cbk44348",
    url: "http://api.map.baidu.com/shangquan/forward/?qt=sub_area_list&ext=1&level=1&areacode=1960&business_flag=1&callback=BMap._rd._cbk24526",
    error: function (XMLHttpRequest, textStatus, errorThrown) {
        alert(textStatus);
        alert(errorThrown);
        this; // ���ñ���AJAX����ʱ���ݵ�options����
    },
    dataType: "jsonp",
    success: function (msg, textStatus) {
        console.log('-------------��Ȧ�б�-------------');
        for(var i=0; i<msg.content.sub.length; i++)
        {
            console.log(msg.content.sub[i].area_name);
        }
//        console.log(msg.content.sub);
    }
})