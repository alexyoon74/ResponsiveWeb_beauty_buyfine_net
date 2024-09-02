<div class="popup-layer" style="display: none;">
	
	<div class="popup-box" id="csPopup" style="display: none;">
		<div class="popup-title">
			<p class="p-title-back-bt a-href-link" link="mback"><span class="title-back-box">X</span></p>
			<p class="p-title-str">客服中心</p>
			<p class="p-close-bt a-href-link" link="mback">关闭</p>
		</div>
		<!--
<div class="popup-cont">
			<p>请添加<span class="wPink b">VIP</span>客服微信<span class="wPink b">wendy_wxy2014</span> 进行1对1咨询。</p>
		</div>
-->
		<div class="popup-cont">
			<p>请添加<span class="wPink b">VIP</span>客服微信<span class="wPink b">wendy_wxy2014</span> 进行1对1咨询。</p>
			<!--
<p>或，</p>
			<p>详细咨询，请在下方输入您的联系方式事情。</p>
			<p><textarea class="con-info" id="csInfo" name="con_info" placeholder="例)&#13;&#10;姓名:美女美男&#13;&#10;电话:12300000000"></textarea></p>
-->
		</div>
		<!--
<div class="popup-title act">
			<p class="p-submit-bt">确认</p>
			<p class="p-close-bt a-href-link" link="mback">关闭</p>
		</div>
-->
	</div>
	
	<div class="search-box" id="searchPopup" style="display: none;">
		<div class="popup-title">
			<p class="p-title-back-bt a-href-link" link="mback"><span class="title-back-box">X</span></p>
			<p class="p-title-str">搜索</p>
			<p class="p-close-bt a-href-link" link="mback">关闭</p>
		</div>
		<div class="popup-form">
			<form id="searchForm" class="search-form" name="search_f" method="get" target="_self" action="/search.html">
				<p class="input"><input type="text" class="search-input" name="s_word" /></p>
				<p class="search-submit">搜索</p>
			</form>
		</div>
		<div id="searchHistory" class="popup-cont flex">
<?
$footer_now_page_uri = "{$_SERVER['REQUEST_SCHEME']}://{$_SERVER['HTTP_HOST']}{$_SERVER['REQUEST_URI']}"; 
$SHARE_LINK = $footer_now_page_uri; 
if($SHARE_IMG)
{
	if(!preg_match("/{$_SERVER['REQUEST_SCHEME']}:\/\//i", $SHARE_IMG))
	{
		$SHARE_IMG = $_SERVER['REQUEST_SCHEME'].":".$SHARE_IMG;
	}
	$in_wx_app_share_img = $SHARE_IMG;
}
if(!$SHARE_IMG) 
{
	$SHARE_IMG = "{$_SERVER['REQUEST_SCHEME']}://image.buyfine.net/images/m/appicon.png";
	$in_wx_app_share_img = $SHARE_IMG;
	//$in_wx_app_share_img = "https://img10.360buyimg.com/imgzone/jfs/t1/18484/12/4849/262904/5c36afcbE14e7fb26/15c9396eabcdfb01.jpg";//main capture image
}
$footer_en_now_page_uri = urlencode($footer_now_page_uri); 
$SHARE_EN_LINK = urlencode($SHARE_LINK); 
$is_search_history = 0;
if($result_search_str)
{
	$is_search_history = 1;
}
else if($_COOKIE['B_S_H'])
{
	$is_search_history = 1;
}
if($is_search_history > 0)
{
	$search_historty_html = "";
	$arr_new_s_h_l = array();
	if($result_search_str)
	{
		$arr_new_s_h_l[] = $result_search_str;
	}
	if($_COOKIE['B_S_H'])
	{
		$arr_s_h_l = explode("^|",$_COOKIE['B_S_H']);
		$arr_new_s_h_l = array_merge($arr_new_s_h_l, $arr_s_h_l);
		$arr_new_s_h_l = array_unique($arr_new_s_h_l);
		unset($arr_s_h_l);
	}
	if(count($arr_new_s_h_l) > 0)
	{
		foreach($arr_new_s_h_l AS $s_h_l)
		{
			$s_h_l = @trim($s_h_l);
			if(!$s_h_l) continue;
			$search_historty_html .= "<p class=\"a-href-link\" link=\"/search.html?s_word=".urlencode($s_h_l)."\">{$s_h_l}</p>";
		}
		if($search_historty_html)
		{
			$search_historty_html .= "<p class=\"a-href-link\" link=\"clear_all_s_cookie\" style=\"border: none;color:#000;background:#f1f1f1\">清除 x</p>";
		}
	}
	unset($arr_new_s_h_l);
	echo $search_historty_html;
	unset($search_historty_html);
}
?>		
		</div>
	</div>
	
</div>

<footer class="copyright-addr clearfix-both mt30">
	<p><address>BUYFINE LIMITED, FLAT/RM 1403 CAUSEWAY BAY COMMERCIAL BLDG 3 SUGAR STREET CAUSEWAY BAY HONG KONG</address></p>
	<p><address class="copyright-p">COPYRIGHT<em>©</em>2009.&nbsp;<span class="wPink">BUYFINE</span>&nbsp;ALL RIGHT RESERVED.</address></p>
	<p class="scjgj-p"><span class="icp-span"><a href="/link_gate_external.html?e_uri=<?=urlencode("http://beian.miit.gov.cn/state/outPortal/loginPortal.action");?>" target="_blank">沪ICP备08025160号</a></span><span><a href="/link_gate_external.html?e_uri=<?=urlencode("http://wap.scjgj.sh.gov.cn/businessCheck/verifKey.do?showType=extShow&serial=9031000020160909134546000001211400-SAIC_SHOW_310000-2020051615572474306&signData=MEYCIQCtvxazVJ9q0A1p13bGL/0sAacb8zDLIIu9XYxfsdDSJwIhANeeshKqxbM32Uvyen7rJzFbCcuiEI/4lhc15d1II1xA");?>" target="_blank"><img src="//image.buyfine.net/images/public3/info/scjgj3.jpg" alt="scjgj" border="0" /></a></span></p>
</footer>
<div id="goTop" class="clearfix-both"><p id="topBt" class="top-btn<?=$change_y_position_class;?> nav-icon top-icon">TOP</p></div>
<div id="bottomCSPop" class="clearfix-both a-href-link" link="cs_popup"><p class="nav-icon bottom-cs-icon">CS</p></div>
<div id="bottomViewed" class="clearfix-both a-href-link" link="/viewed.html"><p class="nav-icon viewed-icon">Viewed</p></div>
<div id="bottomRefP" class="clearfix-both a-href-link" link="/ref_price.html"><p class="right-bt">价格参考</p></div>
<?
if($imgSlideID)
{
?>
	<script type="text/javascript" src="<?=$JS_HOST_URI;?>ideal-image-slider.js?o=<?=$JS_CSS_CACHE_STR;?>" charset="utf-8"></script>
	<script>
	var slider = new IdealImageSlider.Slider('#<?=$imgSlideID;?>');
	slider.start();
	</script>
<?
}
$need_bottom_cs_bt = 1;
$need_bottom_viewed_bt = 1;
$need_bottom_ref_bt = 1;
if($no_need_bottom_ref_bt) $need_bottom_ref_bt=0;
if(!$IS_NEED_PAGING_SCROLL) $IS_NEED_PAGING_SCROLL=0;
?>
<script>
var arr_s_word, s_word, en_s_word;
<?
	if($search_js_str_1)
	{
		echo $search_js_str_1;
		unset($search_js_str_1);
	}
?>
$(document).ready(function () {
	var need_bottom_cs_bt = <?=$need_bottom_cs_bt;?>;
	var need_bottom_viewed_bt = <?=$need_bottom_viewed_bt;?>;
	var need_bottom_ref_bt = <?=$need_bottom_ref_bt;?>;
	var is_scroll_paging = <?=$IS_NEED_PAGING_SCROLL;?>;
	
	$(window).scroll(function(){
		var scrollPosition = $(document).scrollTop();
        if (scrollPosition > 20) {
            $('#topBt').fadeIn();
        } else {
            $('#topBt').fadeOut();
        }
		if(is_scroll_paging > 0)
		{
			if($(window).scrollTop()+scroll_top_px>=$(document).height() - $(window).height())//scroll_top_px assign footer
			{
				//console.log("pt_type="+pt_type+" / scrollTop loading="+pt_info_obj[pt_type]['loading']);
				if(pt_type)
				{
					if(!pt_info_obj[pt_type]['loading'])
					{
					    pt_info_obj[pt_type]['loading'] = true;
					    //paging_loading = true;
					    next_paging(); 
					}
					else
					{
					    //console.log(pt_info_obj[pt_type]['page']+'page loading...');
					}
				}
			}
		}
	});
	
	$('#topBt').click(function () {
        $(window).scrollTop(0);
    });
<?
	echo $search_init_js_str;
	unset($search_init_js_str);
?>    
	if(need_bottom_cs_bt > 0)
    {
    	$('#bottomCSPop').css('display', 'block');
    }
    if(need_bottom_viewed_bt > 0) 
    {
    	$('#bottomViewed').css('display', 'block');
    }
    if(need_bottom_ref_bt > 0) 
    {
    	$('#bottomRefP').css('display', 'block');
    }
});
//console.log('imgSlideLayer zIndex='+$('#imgSlideLayer').zIndex());
</script>
<script>
$(function() {
<?
$is_no_need_fast_click_js = 0;
if($is_mobile_agent<1 || $is_need_fastclick_js<1)//$is_mobile_agent, $is_need_fastclick_js assign header.inc
{
	$is_no_need_fast_click_js = 1;
}
if($is_no_need_fast_click_js > 0)
{
}
else
{
?>
	//new FastClick(document.body);
	try
	{
  		FastClick.attach(document.body);
  	}
	catch(e){}
<?
}
if($is_no_need_lazy_js > 0)
{
}
else
{
	if($lazy_layer_obj)
	{
?>
		var lazy_obj = "<?=$lazy_layer_obj;?>";
<?
	}
	else
	{
?>
		var lazy_obj = "img.lazy";
<?	
	}
	if($lazy_threshold_static_num)
	{
?>	
		var lazy_threshold = <?=$lazy_threshold_static_num;?>;
<?	
	}
	else
	{
?>
		var lazy_threshold = 160;
<?	
	}
?>
	//console.log('lazy_obj='+lazy_obj);
<?
	//threshold : 300
	if($lazy_add_container)
	{
?>
		$(lazy_obj).lazyload({
			effect : "fadeIn",
			container: $("<?=$lazy_add_container;?>"),
			threshold : lazy_threshold
		});
<?	
	}
	else
	{
?>	
		$(lazy_obj).lazyload({
			effect : "fadeIn",
			threshold : lazy_threshold
		});
<?
	}
	echo $add_horizontal_lazy_img_str;
}
echo $add_in_body_footer_js_str;
unset($add_in_body_footer_js_str);
unset($add_horizontal_lazy_img_str);						
?>
});
</script>
<?
if($add_in_body_api_key_footer_js_str)
{
	echo "<script type=\"text/javascript\" charset=\"utf-8\">
	{$add_in_body_api_key_footer_js_str}
	</script>";
	unset($add_in_body_api_key_footer_js_str);
}
?>
<script type="text/javascript" src="<?=$JS_HOST_URI;?>inbody_default.js?o=<?=$JS_CSS_CACHE_STR;?>" charset="utf-8"></script>
<?
if($IS_WX_JS_SDK > 0)
{
	echo "<script type=\"text/javascript\" charset=\"utf-8\">
	var encode_url = '{$footer_en_now_page_uri}';
	";
	echo "</script>";
}
	
if($IS_NEED_PAGING_SCROLL)
{	
	if(!$last_cursor_id) $last_cursor_id=0;
	if(!$last_s_cur_id) $last_s_cur_id=0;
	if(!$lazy_placeholder_img) $lazy_placeholder_img="//image.buyfine.net/images/public3/etc/blank.jpg?o=1";
	
	$arr_p_scroll = array();
	if($IS_DETAIL_PAGING_SCROLL > 0)
	{
		//detail list page
		$arr_p_scroll['dh']['loading'] = true;//스크롤페이징이 필요없기 때문
		$arr_p_scroll['dh']['is_last'] = true;
		$arr_p_scroll['dh']['page'] = 1;
		$arr_p_scroll['dh']['idxArr'] = 0;
		$arr_p_scroll['dh']['t_err_num'] = 0;
		$arr_p_scroll['dh']['cursor'] = 0;
		$arr_p_scroll['dh']['s_cur'] = 0;
		$arr_p_scroll['dc']['loading'] = false;
		$arr_p_scroll['dc']['is_last'] = false;
		$arr_p_scroll['dc']['page'] = 1;
		$arr_p_scroll['dc']['idxArr'] = 0;
		$arr_p_scroll['dc']['t_err_num'] = 0;
		$arr_p_scroll['dc']['cursor'] = 0;
		$arr_p_scroll['dc']['s_cur'] = 0;
		$arr_p_scroll['de']['loading'] = false;
		$arr_p_scroll['de']['is_last'] = false;
		$arr_p_scroll['de']['page'] = 1;
		$arr_p_scroll['de']['idxArr'] = 0;
		$arr_p_scroll['de']['t_err_num'] = 0;
		$arr_p_scroll['de']['cursor'] = 0;
		$arr_p_scroll['de']['s_cur'] = 0;
		$arr_p_scroll['di']['loading'] = false;
		$arr_p_scroll['di']['is_last'] = false;
		$arr_p_scroll['di']['page'] = 1;
		$arr_p_scroll['di']['idxArr'] = 0;
		$arr_p_scroll['di']['t_err_num'] = 0;
		$arr_p_scroll['di']['cursor'] = 0;
		$arr_p_scroll['di']['s_cur'] = 0;
		$scroll_top_px = 400;
		$pt_type = "dh";
	}
	else if($IS_SEARCH_PAGING_SCROLL > 0)
	{
		$arr_p_scroll['sh']['loading'] = false;
		$arr_p_scroll['sh']['is_last'] = false;
		$arr_p_scroll['sh']['page'] = 1;
		$arr_p_scroll['sh']['idxArr'] = 0;
		$arr_p_scroll['sh']['t_err_num'] = 0;
		$arr_p_scroll['sc']['loading'] = false;
		$arr_p_scroll['sc']['is_last'] = false;
		$arr_p_scroll['sc']['page'] = 1;
		$arr_p_scroll['sc']['idxArr'] = 0;
		$arr_p_scroll['sc']['t_err_num'] = 0;
		$arr_p_scroll['sc']['cursor'] = 0;
		$arr_p_scroll['sc']['s_cur'] = 0;
		$arr_p_scroll['se']['loading'] = false;
		$arr_p_scroll['se']['is_last'] = false;
		$arr_p_scroll['se']['page'] = 1;
		$arr_p_scroll['se']['idxArr'] = 0;
		$arr_p_scroll['se']['t_err_num'] = 0;
		$arr_p_scroll['se']['cursor'] = 0;
		$arr_p_scroll['se']['s_cur'] = 0;
		$arr_p_scroll['si']['loading'] = false;
		$arr_p_scroll['si']['is_last'] = false;
		$arr_p_scroll['si']['page'] = 1;
		$arr_p_scroll['si']['idxArr'] = 0;
		$arr_p_scroll['si']['t_err_num'] = 0;
		$arr_p_scroll['si']['cursor'] = 0;
		$arr_p_scroll['si']['s_cur'] = 0;
		$scroll_top_px = 400;
		if(!$js_init_scroll_type) $js_init_scroll_type="sh";
		$pt_type = $js_init_scroll_type;
	}
	else
	{
		//default list page
		$arr_p_scroll['d']['loading'] = false;
		$arr_p_scroll['d']['is_last'] = false;
		$arr_p_scroll['d']['page'] = 1;
		$arr_p_scroll['d']['idxArr'] = 0;
		$arr_p_scroll['d']['t_err_num'] = 0;
		$arr_p_scroll['d']['cursor'] = $last_cursor_id;
		$arr_p_scroll['d']['s_cur'] = $last_s_cur_id;
		$scroll_top_px = 400;
		$pt_type = "d";
	}
	if(!$paging_uid) $paging_uid=0;
	if(!$paging_e_uid) $paging_e_uid=0;
	$json_p_scroll = json_encode($arr_p_scroll);
?>
	<script>
	var scroll_top_px = <?=$scroll_top_px;?>;
	var paging_uid = <?=$paging_uid;?>; 
	var paging_e_uid = <?=$paging_e_uid;?>; 
	var paging_type = "<?=$paging_type;?>"; 
	var paging_ca = "<?=$paging_sub_ca;?>"; 
	var paging_uri = "<?=$paging_uri;?>";
	var paging_rows = <?=$paging_rows;?>;
	var img_blur_css = "<?=$paging_img_blur;?>";
	var lazy_d_uri = "<?=$lazy_placeholder_img;?>";
	var pt_type = '<?=$pt_type;?>';
	var json_pt_info = '<?=$json_p_scroll;?>';
	var pt_info_obj;
	pt_info_obj = $.parseJSON(json_pt_info);
<?
	if($search_js_str_2)
	{
		echo $search_js_str_2;
		unset($search_js_str_2);
	}
?>	
	</script>
	<script type="text/javascript" src="<?=$JS_HOST_URI;?>inbody_scroll_paging.js?o=<?=$JS_CSS_CACHE_STR;?>" charset="utf-8"></script>
<?
}
if($add_jquery_no_ready_footer_files)
{
	echo $add_jquery_no_ready_footer_files;
	unset($add_jquery_no_ready_footer_vars);
}
?>
</body>
<?
$wx_jssdk_link_var_2 = "";
if($IS_WX_JS_SDK > 0)
{
	$wx_jssdk_js = "<script type=\"text/javascript\" src=\"{$JS_HOST_URI}wx_jssdk.js?o={$JS_CSS_CACHE_STR}\" charset=\"utf-8\"></script>";
	$wx_jssdk_link_var_1 = "var wx_link =\"{$SHARE_LINK}\";";
?>
	<script src="<?=$_SERVER['REQUEST_SCHEME'];?>://res.wx.qq.com/open/js/jweixin-1.3.2.js"></script>
	<script>
	var is_need_wx_share = true;
	var wx_title = "<?=$SHARE_TITLE;?>";
	var wx_long_title = "<?=$SHARE_LONG_TITLE;?>";
	var wx_desc = "<?=$SHARE_DESC;?>";
	var wx_imgUrl = "<?=$SHARE_IMG;?>";
	<?=$wx_jssdk_link_var_1;?>
	<?=$wx_jssdk_link_var_2;?>
	var wx_console_print = 0;
	var wx_debug = false;
	var wx_appId = '<?=$arr_wx_jssdk_key["appId"];?>';
	var wx_timestamp = '<?=$arr_wx_jssdk_key["timestamp"];?>';
	var wx_nonceStr = '<?=$arr_wx_jssdk_key["nonceStr"];?>';
	var wx_signature = '<?=$arr_wx_jssdk_key["signature"];?>';
	</script>
<?
	echo $wx_jssdk_js;
	unset($wx_jssdk_js);
	unset($arr_wx_jssdk_key);
}
unset($SHARE_TITLE);
unset($SHARE_LONG_TITLE);
unset($SHARE_DESC);
unset($SHARE_LINK);
unset($SHARE_IMG);
?>	
</html>