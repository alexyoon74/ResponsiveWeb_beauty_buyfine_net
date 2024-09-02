wx.config({
	debug: wx_debug,
	appId: wx_appId,
	timestamp: wx_timestamp,
	nonceStr: wx_nonceStr,
	signature: wx_signature,
	jsApiList: [
		'checkJsApi',
		'onMenuShareTimeline',
		'onMenuShareAppMessage',
		'onMenuShareQQ',
		'onMenuShareWeibo',
		'onMenuShareQZone',
		'hideOptionMenu',
		'showOptionMenu',
		'showMenuItems',
		'sendEmail',
		'refresh',
		'copyUrl',
		'openWithSafari',
		'openUrlByExtBrowser',
		'getBrandWCPayRequest'
		/*
		'hideMenuItems',
		'showMenuItems',
		'hideAllNonBaseMenuItem',
		'showAllNonBaseMenuItem',
		'previewImage',
		'getNetworkType',
		'openWXDeviceLib',
		'closeWXDeviceLib',
		'closeWindow',
		'scanQRCode',
		*/
	]
});
wx.ready(function () {
	wx.checkJsApi({
	    jsApiList: [
		'checkJsApi',
		'onMenuShareTimeline',
		'onMenuShareAppMessage',
		'onMenuShareQQ',
		'onMenuShareWeibo',
		'onMenuShareQZone',
		'hideOptionMenu',
		'showOptionMenu',
		'showMenuItems',
		'sendEmail',
		'refresh',
		'copyUrl',
		'openWithSafari',
		'openUrlByExtBrowser',
		'getBrandWCPayRequest'
		/*
		'hideMenuItems',
		'showMenuItems',
		'hideAllNonBaseMenuItem',
		'showAllNonBaseMenuItem',
		'previewImage',
		'getNetworkType',
		'openWXDeviceLib',
		'closeWXDeviceLib',
		'closeWindow',
		'scanQRCode',
		
		*/
	    ], // 需要检测的JS接口列表，所有JS接口列表见附录2,
	    success: function(res) {
	       if(wx_console_print > 0)
	       {
				console.log("WX checkJsApi obj errMsg ="+JSONtoString(res));
				console.log("WX checkJsApi obj checkResult ="+JSONtoString(res['checkResult']));
			}
	    }
	});
	wx.onMenuShareTimeline({
		title: wx_long_title, // 分享标题
	    link: wx_link, // 分享链接
	    imgUrl: wx_imgUrl, // 分享图标
	    type : 'link',
	    dataUrl : '',
	    success: function () { 
	        if(wx_console_print>0) console.log("WX onMenuShareTimeline success");
	    },
	    cancel: function () { 
	       // 用户取消分享后执行的回调函数
	       if(wx_console_print>0) console.log("WX onMenuShareTimeline cancel");
	    }
	});
	wx.onMenuShareAppMessage({
	    title: wx_title, // 分享标题
	    desc: wx_desc, // 分享描述
	    link: wx_link, // 分享链接
	    imgUrl: wx_imgUrl, // 分享图标
	    type : 'link',
	    dataUrl : '',
	    success: function () { 
	        if(wx_console_print>0) console.log("WX onMenuShareAppMessage success");
	    },
	    cancel: function () { 
	       // 用户取消分享后执行的回调函数
	       if(wx_console_print>0) console.log("WX onMenuShareAppMessage cancel");
	    }
	});
	wx.onMenuShareQQ({
	    title: wx_title, // 分享标题
	    desc: wx_desc, // 分享描述
	    link: wx_link, // 分享链接
	    imgUrl: wx_imgUrl, // 分享图标
	    success: function () { 
	        if(wx_console_print>0) console.log("WX onMenuShareQQ success");
	    },
	    cancel: function () { 
	       // 用户取消分享后执行的回调函数
	       if(wx_console_print>0) console.log("WX onMenuShareQQ cancel");
	    }
	});
	wx.onMenuShareQZone({
    	title: wx_title, // 分享标题
	    desc: wx_desc, // 分享描述
	    link: wx_link, // 分享链接
	    imgUrl: wx_imgUrl, // 分享图标
	    success: function () { 
	        if(wx_console_print>0) console.log("WX onMenuShareQZone success");
	    },
	    cancel: function () { 
	       // 用户取消分享后执行的回调函数
	       if(wx_console_print>0) console.log("WX onMenuShareQZone cancel");
	    }
	});
	wx.onMenuShareWeibo({
	    title: wx_title, // 分享标题
	    desc: wx_desc, // 分享描述
	    link: wx_link, // 分享链接
	    imgUrl: wx_imgUrl, // 分享图标
	    success: function () { 
	        if(wx_console_print>0) console.log("WX onMenuShareWeibo success");
	    },
	    cancel: function () { 
	       // 用户取消分享后执行的回调函数
	       if(wx_console_print>0) console.log("WX onMenuShareWeibo cancel");
	    }
	});
	wx.showMenuItems({
		menuList: ["menuItem:refresh","menuItem:openWithSafari","menuItem:openUrlByExtBrowser","menuItem:copyUrl"] // Menu items to be displayed. See Appendix 3 for a list of all menu items.
	});
	//wx.hideOptionMenu();
	wx.showOptionMenu();
	
});
wx.error(function (res) {
	if(wx_console_print>0) console.log("WX res.errMsg ="+res.errMsg);
});