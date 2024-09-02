$(document).on('click', '.d-tab p' ,function() {
	var val = $(this).attr('val');
	//console.log("val="+val);
	if(val)
	{
		//tab_obj, tab_info_obj - assign inbody_default.js
		tab_obj = ".d-tab p";
		$(tab_obj).removeClass('on');
		$(this).addClass('on');
		tab_info_obj = ".d-content";
		$(tab_info_obj).removeClass('on');
		var on_obj = ".d-content."+val;
		$(on_obj).addClass('on');
		var hash_url = "";
		var current_url = window.location.href;
		var has_sharp = current_url.indexOf('#') !== -1;
		if(has_sharp)
		{
			var parts = current_url.split("#");
			var sharp_para = '&ui-tab=dtab_'+val;
			if(parts[1] != sharp_para)
			{
				hash_url = parts[0] += '#' + sharp_para;
			}
		}
		else 
		{
			hash_url = current_url += '#&' + 'ui-tab=dtab_'+val;
		}
		if(hash_url)
		{
			//console.log("hash_url="+hash_url);
			window.history.pushState({}, '', hash_url);
		}
		if(val==='de' || val==='dc' || val==='di')
		{
			pt_type = val;
			paging_type = val;
			append_obj = on_obj;
			//console.log("append_obj="+append_obj);
			//console.log("loading="+pt_info_obj[pt_type]['loading']);
			if(!pt_info_obj[pt_type]['loading'])
			{
				pt_info_obj[pt_type]['loading'] = true;
			    next_paging();//assign ...._scroll_paging.js
			}
			else
			{
				//console.log(pt_info_obj[pt_type]['page']+'page loading...');
			}
			//pt_info_obj[val]['cursor'] = 10;
			//console.log(val+"-cursor="+pt_info_obj[val]['cursor']);
		}
	}
});