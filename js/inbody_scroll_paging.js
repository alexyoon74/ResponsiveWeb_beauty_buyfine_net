/*
pt_info_obj assign footer
var paging_loading = false;
var page = 1;
var t_err_num = 0;
*/
var append_obj = "#listContent";

function next_paging()
{
	if(navigator.onLine)
	{
		$.ajax({
			type:"POST",
			url: paging_uri,
			data : {'type':paging_type,'ca':paging_ca,'cursor':pt_info_obj[pt_type]['cursor'],'s_cur':pt_info_obj[pt_type]['s_cur'],'limit':paging_rows,'p_uid':paging_uid,'e_uid':paging_e_uid,'arr_uid[]':pt_info_obj[pt_type]['arr_uid'],'s_word':s_word,'arr_s_word[]':arr_s_word,'app_key':app_key,'sign_key':api_sign_key},
			dataType : "json",
			success: function(data)
			{
	    		pt_info_obj[pt_type]['t_err_num'] = 0;
	    		if(data['count'] > 0)
	    		{
			        //console.log(pt_info_obj[pt_type]['page']+' page load');
			        var content_1 = "";
			        var sub_content_1 = "";
			        var last_idx = 0;
			        var num = 0;
			        var idxArr = 0;
			        var uid_len = 0;
			        var list_id_str = "";
			        var l_type;
			        var add_css_1 = '';
			        if(paging_type==='sh' || paging_type==='se' || paging_type==='sc' || paging_type==='si')
			        {
			        	//l_type = paging_type.charAt(1);
			        	var uri_str="";
			        	if(paging_type==='sh') {
			        		uri_str="/detail.html?l=h";
			        	} else if(paging_type==='se') {
			        		uri_str="/detail_expert.html?l=e";
			        	} else if(paging_type==='sc') {
			        		uri_str="/detail_case.html?l=c";
			        	} else {
			        		uri_str="/detail_info.html?l=i";
			        	}
			        	$.each(data['rows'], function(idx, arr_temp_value) {
							content_1 += '<div class="list-e-row">'+
							'<div class="list-item more info search a-href-link" link="'+uri_str+'&uid='+arr_temp_value['uid']+'&s_word='+en_s_word+'">'+
							'<div class="div-img">';
							if(typeof arr_temp_value['imgs'] != "undefined")
							{
								$.each(arr_temp_value['imgs'], function(i_idx, img_value) {
									content_1 += '<p><img class="lazy'+img_blur_css+'" src="'+lazy_d_uri+'" data-original="'+img_value+'" alt="s_'+arr_temp_value['uid']+'_'+i_idx+'" /></p>';
								});
							}
							content_1 += '</div><div class="div-txt">'+
							'<p class="p-tit">'+arr_temp_value['tit']+'</p>'+
							'<p class="p-txt">'+arr_temp_value['txt']+'</p>'+
							'</div></div></div>';
							num++;
						});
			        }
					else if(paging_type === 'h')
					{
						$.each(data['rows'], function(idx, arr_temp_value) {
							content_1 += '<div class="list-title a-href-link" link="/detail.html?l=h&uid='+arr_temp_value['uid']+'"><p class="name">'+arr_temp_value['cn']+'</p><p class="m-items">'+arr_temp_value['items']+'</p></div>'+
							'<div id="addRow_'+arr_temp_value['uid']+'" class="list-row"><div class="list-item hos a-href-link" link="/detail.html?l=h&uid='+arr_temp_value['uid']+'"><img class="lazy'+img_blur_css+'" src="'+lazy_d_uri+'" data-original="'+arr_temp_value['img']+'" alt="mi_'+arr_temp_value['uid']+'" /><p class="hos-t">'+arr_temp_value['kr']+'</p></div>'+
							'<div class="list-item doc"><div class="list-image-group">';
							if(typeof arr_temp_value['ex'] != "undefined")
							{
								$.each(arr_temp_value['ex'], function(e_idx, arr_e_value) {
									content_1 += '<div class="list-item-inner a-href-link" link="/detail_expert.html?l=h&uid='+e_idx+'"><img class="lazy'+img_blur_css+'" src="'+lazy_d_uri+'" data-original="'+arr_e_value['img']+'" alt="di_'+e_idx+'" /><p>'+arr_e_value['name']+'</p></div>';
								});
							}
							//console.log('case = ' + typeof arr_temp_value['case']);
							content_1 += '</div></div>';
							last_idx = 0;
							sub_content_1 = "";
							if(typeof arr_temp_value['case'] != "undefined")
							{
								$.each(arr_temp_value['case'], function(c_idx, arr_c_value) {
									sub_content_1 += '<div class="list-image-group">';
									if(typeof arr_c_value['imgs'] != "undefined")
									{
										$.each(arr_c_value['imgs'], function(i_idx, img_value) {
											sub_content_1 += '<img class="lazy'+img_blur_css+'" src="'+lazy_d_uri+'" data-original="'+img_value+'" alt="ci_'+c_idx+'_'+i_idx+'" />';
										});
									}
									sub_content_1 += '</div><p>'+arr_c_value['title']+'</p>';
									last_idx = c_idx;
								});
							}
							if(last_idx > 0)
							{
								content_1 += '<div class="list-item case a-href-link" link="/detail_case.html?l=h&uid='+last_idx+'">'+sub_content_1+'</div>';
							}
							else
							{
								content_1 += '<div class="list-item case">&nbsp;</div>';
							}
							content_1 += '</div>';
							num++;
						});
					}
					else if(paging_type==='e' || paging_type==='de')
					{
						l_type = paging_type;
						if(paging_type === 'de')
						{
							l_type = 'h';
							add_css_1 = ' detail';
						}
						$.each(data['rows'], function(idx, arr_temp_value) {
							content_1 += '<div id="addRow_'+arr_temp_value['uid']+'" class="list-e-row'+add_css_1+'">';
							content_1 += '<div class="list-item a-href-link" link="/detail_expert.html?l='+l_type+'&uid='+arr_temp_value['uid']+'">'+
							'<div class="div-img">'+
							'<img class="lazy'+img_blur_css+'" src="'+lazy_d_uri+'" data-original="'+arr_temp_value['img']+'" alt="di_'+arr_temp_value['uid']+'" />'+
							'</div><div class="div-txt">';
							if(paging_type === 'de')
							{
								content_1 += '<p class="p-tit"><span class="s-tit">'+arr_temp_value['name']+'</span> '+arr_temp_value['pos']+'</p>';
							}
							else
							{
								content_1 += '<p class="p-tit"><span class="s-tit">'+arr_temp_value['name']+'</span> '+arr_temp_value['cn']+' '+arr_temp_value['pos']+'</p>';
							}
							content_1 += '<p class="p-txt">'+arr_temp_value['items']+'</p>'+
							'</div></div>';
							if(paging_type === 'e')
							{
								if(typeof arr_temp_value['case'] != "undefined")
								{
									$.each(arr_temp_value['case'], function(c_idx, arr_c_value) {
										content_1 += '<div class="list-item add a-href-link" link="/detail_case.html?l=e&uid='+c_idx+'">'+
										'<div class="div-txt">'+
										'<p class="p-tit">'+arr_c_value['title']+'</p>'+
										'<p class="p-txt">'+arr_c_value['txt']+'</p>'+
										'</div><div class="div-img">';
										if(typeof arr_c_value['imgs'] != "undefined")
										{
											$.each(arr_c_value['imgs'], function(i_idx, img_value) {
												content_1 += '<p><img class="lazy'+img_blur_css+'" src="'+lazy_d_uri+'" data-original="'+img_value+'" alt="ci_'+c_idx+'_'+i_idx+'" /></p>';
											});
										}
										content_1 += '</div></div>';
									});
								}
								if(typeof arr_temp_value['info'] != "undefined")
								{
									$.each(arr_temp_value['info'], function(c_idx, arr_c_value) {
										content_1 += '<div class="list-item more a-href-link" link="/detail_info.html?l=e&uid='+c_idx+'">'+
										'<div class="div-img">'+
										'<img class="lazy'+img_blur_css+'" src="'+lazy_d_uri+'" data-original="'+arr_c_value['img']+'" alt="fi_'+c_idx+'" />'+
										'</div><div class="div-txt">'+
										'<p class="p-tit">'+arr_c_value['title']+'</p>';
										if(arr_c_value['items'])
										{
											content_1 += '<p class="p-txt">'+arr_c_value['items']+'</p>';
										}
										if(arr_c_value['summ'])
										{
											content_1 += '<p class="p-txt">'+arr_c_value['summ']+'</p>';
										}
										content_1 += '</div></div>';
									});
								}
							}
							content_1 += '</div>';
							num++;
						});	
					}
					else if(paging_type==='c' || paging_type==='dc')
					{
						l_type = paging_type;
						if(paging_type === 'dc')
						{
							l_type = 'h';
							add_css_1 = ' detail';
						}
						$.each(data['rows'], function(idx, arr_temp_value) {
							content_1 += '<div class="list-title case'+add_css_1+' a-href-link" link="/detail_case.html?l='+l_type+'&uid='+arr_temp_value['uid']+'"><p class="title">'+arr_temp_value['title']+'</p></div>';
							if(arr_temp_value['txt'])
							{
								content_1 += '<div class="list-txt a-href-link" link="/detail_case.html?l='+l_type+'&uid='+arr_temp_value['uid']+'">'+
								'<p>'+arr_temp_value['txt']+'</p></div>';
							}
							content_1 += '<div class="list-row case a-href-link" link="/detail_case.html?l='+l_type+'&uid='+arr_temp_value['uid']+'">'+
							'<div class="list-item case">'+
								'<div class="list-image-group">';
							if(typeof arr_temp_value['imgs'] != "undefined")
							{
								$.each(arr_temp_value['imgs'], function(i_idx, img_value) {
									content_1 += '<img class="lazy'+img_blur_css+'" src="'+lazy_d_uri+'" data-original="'+img_value+'" alt="ci_'+arr_temp_value['uid']+'_'+i_idx+'" />';
								});
							}
							content_1 += '</div></div></div>';
							num++;
						});
					}
					else if(paging_type==='i' || paging_type==='di')
					{
						l_type = paging_type;
						if(paging_type === 'di')
						{
							l_type = 'h';
							add_css_1 = ' detail';
						}
						$.each(data['rows'], function(idx, arr_temp_value) {
							content_1 += '<div class="list-e-row'+add_css_1+'">'+
							'<div class="list-item more info a-href-link" link="/detail_info.html?l='+l_type+'&uid='+arr_temp_value['uid']+'">'+
							'<div class="div-img">'+
							'<img class="lazy'+img_blur_css+'" src="'+lazy_d_uri+'" data-original="'+arr_temp_value['img']+'" alt="fi_'+arr_temp_value['uid']+'" />'+
							'</div><div class="div-txt">'+
							'<p class="p-tit">'+arr_temp_value['title']+'</p>';
							if(arr_temp_value['items'])
							{
								content_1 += '<p class="p-txt">'+arr_temp_value['items']+'</p>';
							}
							if(arr_temp_value['summ'])
							{
								content_1 += '<p class="p-txt">'+arr_temp_value['summ']+'</p>';
							}
							content_1 += '</div></div></div>';
							num++;
						});
					}
					if(num > 0)
					{
						list_id_str = "listBlock_"+pt_type+"_"+pt_info_obj[pt_type]['page'];
						content_1 = '<div id="'+list_id_str+'" class="list-block">'+content_1+'</div>';
						//console.log("append_obj="+append_obj+" / "+list_id_str+" content_1="+content_1);
						$(append_obj).append(content_1);
						$("#"+list_id_str+" img.lazy").lazyload({ effect : "fadeIn", threshold: 300});
					}
					pt_info_obj[pt_type]['idxArr'] = pt_info_obj[pt_type]['page'];
					idxArr = pt_info_obj[pt_type]['idxArr'];
			        pt_info_obj[pt_type]['page']++;
			        if(typeof searchArr!="undefined" && (paging_type==='sh' || paging_type==='se' || paging_type==='sc' || paging_type==='si'))
			        {
			        	uid_len = searchArr[pt_type][idxArr] ? searchArr[pt_type][idxArr].length : 0;
						//console.log("idxArr="+pt_info_obj[pt_type]['idxArr']+" / "+paging_type+" arr len="+uid_len);
			        	if(uid_len > 0)// check next page
			        	{
			        		pt_info_obj[pt_type]['arr_uid'] = searchArr[pt_type][idxArr];
			        	}
			        	else //last page
			        	{
			        		pt_info_obj[pt_type]['loading'] = true;
				        	pt_info_obj[pt_type]['is_last'] = true;
			        	}
			        }
			        else
			        {
				        if(data['count'] < paging_rows)
				        {
				        	pt_info_obj[pt_type]['loading'] = true;
				        	pt_info_obj[pt_type]['is_last'] = true;
				        	//paging_loading = true;
				        	//console.log('last paging');
				        }
				        else
				        {
				        	pt_info_obj[pt_type]['cursor'] = data['lastID'];
				        	pt_info_obj[pt_type]['s_cur'] = data['lastS'];
				        	//pt_info_obj[pt_type]['loading'] = false;
				        	//paging_loading = false;
				        }
				    }
			    }
			    else
			    {
			        pt_info_obj[pt_type]['loading'] = true;
			        pt_info_obj[pt_type]['is_last'] = true;
			        //console.log('null resutl');
			    }
			},
			error: function(xhr, status, error) 
			{
				if(pt_info_obj[pt_type]['t_err_num'] < 4)
				{
					pt_info_obj[pt_type]['loading'] = false;
					//paging_loading = false;
				}
				else
				{
					pt_info_obj[pt_type]['loading'] = true;
				}
				pt_info_obj[pt_type]['t_err_num']++;
			    //console.log('error='+error);
			},
			complete: function ()
			{
				if(!pt_info_obj[pt_type]['is_last'])
				{
					pt_info_obj[pt_type]['loading'] = false;
					//paging_loading = false;
				}
			},
			timeout:10000//10000=10sec
		});
	}
	else
	{
		alert('网络连接错误，请确认网络状态');//Network err
	}
}