$(document).on('click', '.s-tab p' ,function() {
	var val = $(this).attr('val');
	//console.log("val="+val);
	if(val)
	{
		if(val==='sh' || val==='se' || val==='sc' || val==='si')
		{
			pt_type = val;
			paging_type = val;
			append_obj = ".s-list-block."+val;
			
			//tab_obj, tab_info_obj - assign inbody_default.js
			tab_obj = ".s-tab p";
			$(tab_obj).removeClass('on');
			$(this).addClass('on');
			tab_info_obj = ".s-list-block";
			$(tab_info_obj).removeClass('on');
			$(append_obj).addClass('on');
			
			var idx = pt_info_obj[pt_type]['idxArr'];
			var hash_url = "";
			var current_url = window.location.href;
			var has_sharp = current_url.indexOf('#') !== -1;
			if(has_sharp)
			{
				var parts = current_url.split("#");
				var sharp_para = '&ui-tab=stab_'+val;
				if(parts[1] != sharp_para)
				{
					hash_url = parts[0] += '#' + sharp_para;
				}
			}
			else 
			{
				hash_url = current_url += '#&' + 'ui-tab=stab_'+val;
			}
			if(hash_url)
			{
				//console.log("hash_url="+hash_url);
				window.history.pushState({}, '', hash_url);
			}
			
			//console.log("append_obj="+append_obj);
			//console.log("loading="+pt_info_obj[pt_type]['loading']);
			if(typeof searchArr!="undefined" && !pt_info_obj[pt_type]['loading'])
			{
				var len = searchArr[pt_type][idx] ? searchArr[pt_type][idx].length : 0;
				//console.log("idxArr="+pt_info_obj[pt_type]['idxArr']+" / "+paging_type+" arr len="+searchArr[pt_type][idx].length);
				if(len > 0)
	        	{
	        		pt_info_obj[pt_type]['arr_uid'] = searchArr[pt_type][idx];
	        		pt_info_obj[pt_type]['loading'] = true;
			    	next_paging();//assign ...._scroll_paging.js
	        	}
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