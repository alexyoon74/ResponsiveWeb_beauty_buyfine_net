var request_ajax;
var ajax_success_data;
var ajax_error_data;
var ajax_complete_data;
var ajax_multi_conn = 0;
var is_popuped = false;
var pop_type, pop_box_obj;
var tab_obj, tab_info_obj;
var is_first_confirm = 0;

var jquery_ajax = function (uri,method,data_type,t_out,multi_conn,post_data)
{
	if(!data_type) data_type='json';
	if(!t_out) t_out=3000;//3 second timeout
	if(!multi_conn) multi_conn=0;
	if(uri && method)
	{
		if(multi_conn < 1)
		{
			if (typeof request_ajax != "undefined" )  {
				request_ajax.abort();
			}
		}
		if(method==='POST' && post_data)
		{
			//console.log("post_data="+post_data);      
			request_ajax = $.ajax({
				url:uri,
				data:post_data,
				type:method,
				dataType:data_type,
				success:ajax_success_data,
				error:ajax_error_data,
				complete:ajax_complete_data,
				timeout:t_out
			});
		}
		else
		{
			request_ajax = $.ajax({
				url:uri,
				type:method,
				dataType:data_type,
				success:ajax_success_data,
				error:ajax_error_data,
				complete:ajax_complete_data,
				timeout:t_out
			});
		}
	}
}
ajax_success_data = function (data)
{
	if(data['result'] == 1)
	{
		if(ajax_type === 'con_update')
		{
			alert('您的信息已登记成功，会有客服跟您联系。');
			$('#csInfo').val('');
			history.back();
		}
		else if(ajax_type === 'del_s_cookie')
		{
			$('#searchHistory').html('');
			history.back();
		}
		else if(ajax_type === 'del_v_cookie')
		{
			//$(".popup-layer").css('display', 'none');
			if(data['del_obj'])
			{
				$(data['del_obj']).css('display', 'none');
			}
			if(ajax_var_1)
			{
				var num_obj = "#"+ajax_var_1+"CTNum";
				var was_num = $(num_obj).attr('value');
				if (!isNaN(was_num)) 
				{
					was_num = parseFloat(was_num); // 숫자형으로 변환 (부동 소수점)
				}
				if(was_num > 0)
				{
					var now_num = was_num-1;
					console.log("was_num="+was_num+" / now_num="+now_num);
					$(num_obj).attr('value', now_num);
					$(num_obj).text('('+now_num+')');
				}
			}
		}
	}
	else
	{
		alert('出现错误。\n如果继续出现错误请与管理者联系。');
	}
}
ajax_error_data = function(data,status,err){ 
	//console.log("ajax_error_data - status="+status+" / ajax_type="+ajax_type);      
	if(status==='timeout') { 
    }
	if(status!='abort')
    {
		//alert('出现错误。请稍候再使用。\n如果继续出现错误请与管理者联系。');
	}
}
ajax_complete_data = function(){
	if(ajax_type === 'con_update')
	{
	}
	else if(ajax_type === 'del_v_cookie')
	{
		$(".popup-layer").css('display', 'none');
	}
}

$('#csPopup .p-submit-bt').on('click', function(e) {
	//e.preventDefault();
	var val = $('#csInfo').val();
	//console.log('val='+val);
	if(val)
	{
		if(navigator.onLine)
		{
			ajax_timeout = 5000;//5 second timeout
			ajax_uri = "/api/cs_con_update.html";
			val = sanitize_input(val);
			//console.log('val2='+val);
			var ajax_post_data = $.parseJSON('{"con_info": "'+val+'", "app_key": "'+app_key+'", "sign_key": "'+api_sign_key+'"}');
		    if(typeof ajax_uri!="undefined" && ajax_uri)
		    {
		    	ajax_type = 'con_update';
		    	ajax_var_1 ='con_update';
		    	jquery_ajax(ajax_uri,'POST','json',ajax_timeout,ajax_multi_conn,ajax_post_data);
		    }
		}
		else
		{
			alert('网络连接错误，请确认网络状态');//Network err
		}
	}
	else
	{
		alert('请输入信息');
		$('#csInfo').focus();
		return false;
	}
});

function clear_all_s_cookie() {
	if(navigator.onLine)
	{
		ajax_timeout = 5000;//5 second timeout
		ajax_uri = "/api/operation_proc.html";
		var val = "del_s_cookie";
		var ajax_post_data = $.parseJSON('{"type": "'+val+'", "app_key": "'+app_key+'", "sign_key": "'+api_sign_key+'"}');
		if(typeof ajax_uri!="undefined" && ajax_uri)
	    {
	    	ajax_type = 'del_s_cookie';
	    	ajax_var_1 ='del_s_cookie';
	    	jquery_ajax(ajax_uri,'POST','json',ajax_timeout,ajax_multi_conn,ajax_post_data);
	    }
	}
	else
	{
		alert('网络连接错误，请确认网络状态');//Network err
	}
}

$(document).on('click', '.page-title .d-bt' ,function() {
	var type = $(this).attr('type');
	var del = $(this).attr('del');
	var title = $(this).attr('title');
	if(type && del && title)
	{
		var confirm_obj = confirm(title+' - 确定要全部删除吗？');
		if(confirm_obj===true)
		{
			window.location = "/viewed.html?v="+type+"&d="+del;
		}
		else
		{
			return false;
		}
	}
});

$(document).on('click', '.del-layer .del-bt' ,function() {
	if(navigator.onLine)
	{
		if(is_first_confirm > 0)
		{
			var confirm_obj = true;
		}
		else
		{
			var confirm_obj = confirm('确定要从足迹中删除吗？');
		}
		if(confirm_obj===true)
		{
			is_first_confirm = 1;
			var type = $(this).attr('type');
			var value = $(this).attr('value');
			//console.log("del-bt type="+type+" / value="+value);
			if(type && value)
			{
				var del_obj = "#"+type+"_"+value;
				//console.log("del_obj="+del_obj);
				$(del_obj+' .div-img').css("visibility","hidden");
				$(del_obj).removeClass('loading-spinner').addClass('loading-spinner');
				//$(".popup-layer").css('display', 'block');
				$('.popup-layer').fadeIn('fast');
				ajax_timeout = 5000;//5 second timeout
				ajax_uri = "/api/operation_proc.html";
				var val = "del_v_cookie";
				var ajax_post_data = $.parseJSON('{"type": "'+val+'","c_type": "'+type+'","uid": '+value+', "app_key": "'+app_key+'", "sign_key": "'+api_sign_key+'"}');
				if(typeof ajax_uri!="undefined" && ajax_uri)
			    {
			    	ajax_type = 'del_v_cookie';
			    	ajax_var_1 = type;
			    	jquery_ajax(ajax_uri,'POST','json',ajax_timeout,ajax_multi_conn,ajax_post_data);
			    }
			}
			else
			{
				alert('出现错误。\n如果继续出现错误请与管理者联系。');
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		alert('网络连接错误，请确认网络状态');//Network err
	}
});

function sanitize_input(input) {
	//var sanitized = input.replace(/\n/g, '\\n');
	var sanitized = input.replace(/\n/g, ' ');
	sanitized = escape_html(sanitized);
	return sanitized;
}

function escape_html(unsafe) {
	return unsafe.replace(/[&<"']/g, function(m) {
		switch (m) {
			case '&':
			    return '&amp;';
			case '<':
			    return '&lt;';
			case '"':
			    return '&quot;';
			case "'":
			    return '&#039;';
		}
	});
}

$(document).on('click', '.a-href-link' ,function() {
	var loc = $(this).attr('link');
	//console.log("a-href-link loc="+loc);
	if(loc)
	{
		if(loc === 'cs_popup')
		{
			//$("#csPopup").css('display', 'block');
			//$('#csPopup').slideDown();
			$('.popup-layer').fadeIn('fast');
			$('#csPopup').slideDown('fast');
			//$('#csPopup').slideUp('fast');
			pop_type = loc;
			pop_box_obj = ".popup-box";
			open_layer_popup();
		}
		else if(loc === 'search_popup')
		{
			//$("#csPopup").css('display', 'block');
			//$('#csPopup').slideDown();
			$('.popup-layer').fadeIn('fast');
			$('#searchPopup').slideDown('fast');
			pop_type = loc;
			pop_box_obj = ".search-box";
			open_layer_popup();
		}
		else if(loc === 'clear_all_s_cookie')
		{
			clear_all_s_cookie();
		}
		else if(loc === 'hash_del')
		{
			var h_loc = $(this).attr('h-link');
			if(h_loc)
			{
				//location.hash = '';
				//var numberOfEntries = window.history.length;
				//console.log("history length ="+numberOfEntries+" / history.state ="+history.state+" / history.replaceState ="+history.replaceState+" / history.pushState ="+history.pushState);
				window.location.replace(h_loc);
				if(typeof (history.replaceState) != "undefined") {
					//history.pushState('', document.title, window.location.href.split('#')[0]);
					//window.location.replace(h_loc);
					//history.replaceState('', document.title, window.location.href.split('#')[0]);
				}
				//window.location = h_loc;
			}
		}
		else if(loc === 'mback')
		{
			history.back();
		}
		else
		{
			window.location = loc;
		}
	}
});

$(window).on('popstate', function(event) {
	//console.log('it has back event.');
	if(is_popuped)
	{
		$(pop_box_obj).slideToggle('fast','swing',function() {
			$(".popup-layer").css('display', 'none');
		});
		//$(pop_box_obj).css('display', 'none');
		//$(pop_box_obj).slideToggle();
		//$(pop_box_obj).css('display', 'none');
		//$(pop_box_obj).fadeOut('fast');
		is_popuped = false;
	}
	else
	{
		//console.log('tab_obj='+tab_obj+' / tab_info_obj='+tab_info_obj);
		if(tab_obj && tab_info_obj)
		{
			var current_url = window.location.href;
			var has_sharp = current_url.indexOf('#&ui-tab=') !== -1;
			var tab_on_obj = ""
			var tab_on_info_obj = "";
			if(has_sharp)
			{
				var arr_temp1, arr_temp2;
				arr_temp1 = current_url.split("#&ui-tab=");
				if(arr_temp1[1])
				{
					arr_temp2 = arr_temp1[1].split("_");
					if(arr_temp2['0'] && arr_temp2['1'])
					{
						tab_on_obj = tab_obj+"."+arr_temp2['1'];
						tab_on_info_obj = tab_on_info_obj+"."+arr_temp2['1'];
					}
				}
			}
			else
			{
				if(tab_obj === '.s-tab p')
				{
					tab_on_obj = tab_obj+".sh";
					tab_on_info_obj = tab_on_info_obj+".sh";
				}
				else if(tab_obj === '.d-tab p')
				{
					tab_on_obj = tab_obj+".dh";
					tab_on_info_obj = tab_on_info_obj+".dh";
				}
			}
			//console.log('tab_on_obj='+tab_on_obj+' / tab_on_info_obj='+tab_on_info_obj);
			if(tab_on_obj && tab_on_info_obj)
			{
				$(tab_obj).removeClass('on');
				$(tab_on_obj).addClass('on');
				$(tab_info_obj).removeClass('on');
				$(tab_on_info_obj).addClass('on');
			}
		}
	}
});

function open_layer_popup() {
	is_popuped = true;
	//var current_url = document.URL;
	var current_url = window.location.href;
	var has_sharp = current_url.indexOf('#') !== -1;
	var hash_url = "";
	if(has_sharp)
	{
		var arr_temp1 = current_url.split("#");
		if(arr_temp1[1])
		{
			hash_url = arr_temp1[0] += '#&' + 'ui-state=popup';
		}
	}
	else
	{
		hash_url = current_url += '#&' + 'ui-state=popup';
	}
	if(hash_url)
	{
		//window.location.replace(hash_url);
		window.history.pushState({}, '', hash_url);
		//window.history.replaceState({}, '', hash_url);
	}
	/* 			 
	window.history.replaceState(): 이 메서드는 현재 페이지의 히스토리 엔트리를 대체합니다. 새로운 URL로 변경되며, 브라우저의 주소 표시줄에도 새로운 URL이 나타납니다. 그러나 페이지는 새로 로드되지 않고, 현재 페이지의 JavaScript 상태나 컨텐츠 등이 변경되었음을 나타내는 데 주로 사용됩니다. 예를 들어, Ajax 요청 후 URL을 업데이트할 때 사용할 수 있습니다.
	
	window.history.pushState(): 이 메서드는 현재 페이지를 히스토리 스택에 새 엔트리로 추가합니다. 브라우저의 주소 표시줄에는 새 URL이 나타나며, 페이지는 실제로 다시 로드되지 않습니다. 주로 페이지의 상태를 변경하거나, 새로운 페이지 컨텐츠를 동적으로 로드한 후 URL을 업데이트할 때 사용됩니다.
	*/
	//console.log($('body').html());
}

function close_layer_popup() {
	$(pop_box_obj).slideToggle('fast','swing',function() {
		$(".popup-layer").css('display', 'none');
	});
	//$(pop_box_obj).css('display', 'none');
	//$(pop_box_obj).slideToggle();
	//$(pop_box_obj).css('display', 'none');
	if(is_popuped)
	{
	    history.back();
	    is_popuped = false;
	}
}

$('.popup-layer').on('click', function(e) {
	//console.log('popup-overlay='+e.target.classList.toString());
	if(e.target.classList.contains("popup-layer")) {
		close_layer_popup();       
	}
});

$('#searchForm').submit(function(){
	var input_value = $('.search-input').val();
	//console.log("input_value.length = "+input_value.length);
	if(input_value && input_value.length>1)
	{
		if(input_value == s_word)
		{
			close_layer_popup();
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		//alert('请输入搜索关键字!');
		alert('请最少输入2个字符');
		$('.search-input').focus();
		return false;
	}
});

$('.search-submit').on('click', function(e) {
	 $('#searchForm').submit();
});