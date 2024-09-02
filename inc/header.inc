<?
$check_pm_time = date("Y-m-d H:i");
$is_pm_time = 0;
if($check_pm_time >= "2019-06-27 10:01")
{
	$is_pm_time = 1;
}
$is_pm_time = 0;
if($is_pm_time > 0)
{
	Header("Location:/pm.html");
	exit;
}
$IS_NO_MOBILE_AGENT = 1;
$is_mobile_agent = 0;
$is_tablet_agent = 0;
$arr_mobile_agent_str = array('mobile');
$arr_tablet_agent_str = array('ipad','tablet');
foreach($arr_mobile_agent_str AS $mobile_agent)
{
	if(preg_match("/{$mobile_agent}/i", $_SERVER['HTTP_USER_AGENT']))
	{
		$IS_NO_MOBILE_AGENT = 0;
		$is_mobile_agent = 1;
		break;
	}
}
foreach($arr_tablet_agent_str AS $tablet_agent)
{
	if(preg_match("/{$tablet_agent}/i", $_SERVER['HTTP_USER_AGENT']))
	{
		$is_tablet_agent = 1;
		break;
	}
}

$IS_IMG_BLUR_FILTER = 0;
if(!$is_mobile_agent && !$is_tablet_agent)
{
	$IS_IMG_BLUR_FILTER = 1;
}

/*
if(!$isNoNeedCache)
{
	header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
	// 항상 변경됨
	header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
	// HTTP/1.1
	header("Cache-Control: no-store, no-cache, must-revalidate");
	header("Cache-Control: post-check=0, pre-check=0", false);
	// HTTP/1.0
	header("Pragma: no-cache");
}
else
{
	header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
	header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
	header("Cache-Control: no-cache, must-revalidate");
	header("Cache-Control: post-check=0, pre-check=0", false);
	header("Pragma: no-cache");
}
*/
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT");
header("Cache-Control: no-cache, must-revalidate");
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache");

if($PAGE_TITLE)
{
	$PAGE_TITLE = strip_tags($PAGE_TITLE);
	$PAGE_TITLE = preg_replace("/\s+/"," ",$PAGE_TITLE);
	$PAGE_TITLE = $PAGE_TITLE." + BEAUTY.BUYFINE.NET";  
	$SHARE_TITLE = $PAGE_TITLE; 
	$SHARE_LONG_TITLE = $PAGE_TITLE;
}
else
{
	$PAGE_TITLE = "BEAUTY.BUYFINE.NET";
	$SHARE_TITLE = $PAGE_TITLE; 
	$SHARE_LONG_TITLE = $PAGE_TITLE;
}
if(!$META_STR) $META_STR=$PAGE_TITLE;
if($META_DESCRIPTION)
{
	$META_DESCRIPTION = strip_tags($META_DESCRIPTION);
	$META_DESCRIPTION = preg_replace("/\s+/"," ",$META_DESCRIPTION);
	$SHARE_DESC = $META_DESCRIPTION;
	$META_DESCRIPTION = $META_DESCRIPTION.", BEAUTY.BUYFINE.NET"; 
}
else
{
	$META_DESCRIPTION=$PAGE_TITLE;
	$SHARE_DESC=$PAGE_TITLE;
}
$SCREEN_USER_SCALABLE = "yes";//yes or no
?>
<!doctype html>
<html lang="zh-CN">
<head>
<title><?=$PAGE_TITLE;?></title>
<link rel="icon" href="/favicon.ico" />	
<meta charset="utf-8">
<meta name="description" content="<?=$META_DESCRIPTION;?>" />
<meta name="keywords" content="<?=$META_STR;?>" />

<?
echo "<meta id=\"mViewport\" name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable={$SCREEN_USER_SCALABLE}\">";
//echo "<meta id=\"mViewport\" name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1, user-scalable={$SCREEN_USER_SCALABLE}\">";
if(!$isNoNeedDCss) 
{
	echo("<link rel=\"stylesheet\" href=\"{$CSS_HOST_URI}default.css?o={$JS_CSS_CACHE_STR}\" type=\"text/css\" />\n");
}
if($CSS_FILES)
{
	foreach($CSS_FILES as $css_temp)
	{
		echo("<link rel=\"stylesheet\" href=\"{$css_temp}\" type=\"text/css\" />\n");    
	}
}
$is_need_fastclick_js = 0;
if(!$isNoNeedDJs && $is_mobile_agent>0 && $is_need_fastclick_js>0) 
{
	echo("<script type=\"text/javascript\" src=\"{$JS_HOST_URI}fastclick.js?o={$JS_CSS_CACHE_STR}\" charset=\"utf-8\"></script>\n");
}
if($JS_FILES)
{
	foreach($JS_FILES as $js_temp)
    {
        echo("<script type=\"text/javascript\" src=\"{$js_temp}\" charset=\"utf-8\"></script>\n");
    }
}
?>
</head>
<body>
<?
if($is_need_api_js_str>0 && $APP_KEY && count($ARR_API_V2_MD5_KEY_STR)>0)
{
	$api_md5_key = $ARR_API_V2_MD5_KEY_STR[$APP_KEY];//$APP_KEY assign verym_187_config.inc, $ARR_API_V2_MD5_KEY_STR assign api/config.inc
	$api_sessin_key = $ARR_API_V2_SESSION_KEY[$APP_KEY];//$ARR_API_V2_SESSION_KEY assign api/config.inc
	//$en_api_sign_key = urlencode(api_md5_enc($api_sessin_key, $api_md5_key));//api_md5_enc, $API_M_V2_SESSION_KEY assign api/config.inc
	$en_api_sign_key = api_md5_enc($api_sessin_key, $api_md5_key);//api_md5_enc, $API_M_V2_SESSION_KEY assign api/config.inc
	$add_in_body_api_key_footer_js_str = "var api_sign_key = \"{$en_api_sign_key}\";
	var app_key = \"{$APP_KEY}\";";
	unset($api_md5_key);
	unset($api_sessin_key);
	unset($en_api_sign_key);
}

if(!$arr_get['l']) $arr_get['l']='h';
$page_t = $arr_get['l'];
if($search_str) $page_t="s";
$arr_title_link = array(
	'h'=>array('t'=>'找医院','link'=>'/list.html'),
	'e'=>array('t'=>'找医生','link'=>'/list_expert.html'),
	'c'=>array('t'=>'整容案例','link'=>'/list_case.html'),
	'i'=>array('t'=>'整容攻略','link'=>'/list_info.html')
);
$top_m_on_h = "";
$top_m_on_e = "";
$top_m_on_c = "";
$top_m_on_f = "";
$top_m_on_s = "";
if(!$arr_get['vd'])
{
	if($page_t=='h') $top_m_on_h=" on";
	else if($page_t=='e') $top_m_on_e=" on";
	else if($page_t=='c') $top_m_on_c=" on";
	else if($page_t=='i') $top_m_on_f=" on";
	else if($page_t=='s') $top_m_on_s=" on";
}
?>
<header class="top-menu">
	<nav>
		<ul>
			<li class="a-href-link<?=$top_m_on_c;?>" link="<?=$arr_title_link['c']['link'];?>"><a href="<?=$arr_title_link['c']['link'];?>" target="_self"><?=$arr_title_link['c']['t'];?></a></li>
			<li class="a-href-link<?=$top_m_on_h;?>" link="<?=$arr_title_link['h']['link'];?>"><a href="<?=$arr_title_link['h']['link'];?>" target="_self"><?=$arr_title_link['h']['t'];?></a></li>
			<li class="a-href-link<?=$top_m_on_e;?>" link="<?=$arr_title_link['e']['link'];?>"><a href="<?=$arr_title_link['e']['link'];?>" target="_self"><?=$arr_title_link['e']['t'];?></a></li>
			<li class="a-href-link<?=$top_m_on_f;?>" link="<?=$arr_title_link['i']['link'];?>"><a href="<?=$arr_title_link['i']['link'];?>" target="_self"><?=$arr_title_link['i']['t'];?></a></li>
			<!-- <li class="a-href-link cs-open" link="cs_popup"><span class="nav-icon cs-icon">提问</span></li> -->
			<li class="a-href-link search-open<?=$top_m_on_s;?>" link="search_popup"><span class="nav-icon search-icon">搜索</span></li>
		</ul>
	</nav>
</header>
<?
//echo "<br /><div class=\"a-href-link\" style=\"height:30px;line-height:30px\" link=\"search_popup\">Search</div>";
if($is_need_sub_menu)
{
	$sub_m_all_on = " on";
	$sub_menu_html = "";
	foreach($ARR_B_CA_1_STR AS $key=>$value)
	{
		$on_css = "";
		if($is_yes_print>1)
		{
			echo "{$key} == {$arr_get['c']}<br />";
		}
		if($key == $arr_get['c'])
		{
			$on_css = " on";
			$sub_m_all_on = "";
		}
		$sub_menu_html .= "<li class=\"a-href-link{$on_css}\" link=\"{$_SERVER['PHP_SELF']}?c={$key}\">{$value}</li>";
	}
?>
<div class="top-sub-menu">
	<ul>
		<li class="a-href-link<?=$sub_m_all_on;?>" link="<?=$_SERVER['PHP_SELF'];?>">全部</li>
<?
	echo $sub_menu_html;
	unset($sub_menu_html);
?>		
	</ul>
</div>
<?
}
else
{
	echo "<div style=\"height:40px\"></div>";
}

if($_COOKIE['BFUSERID']=='july21c@gmail.com')
{
	//echo "<br /><div class=\"a-href-link\" style=\"height:30px;line-height:30px\" link=\"search_popup\">Search</div>";
}

if($is_need_title_bar)
{
	if($search_str)
	{
		echo "<div class=\"page-title\"><p class=\"title-back-bt a-href-link\" link=\"mback\"><span class=\"title-back-box\">&lt;</span></p><p class=\"title a-href-link\" link=\"mback\">搜索(<span class=\"s-word\">{$search_str}</span>)</p><p class=\"title-nav-sym\">&gt;</p><p class=\"title a-href-link\" link=\"{$_SERVER['PHP_SELF']}?l={$page_t}&uid={$uid_t}&s_word=".urlencode($search_str)."\">正文</p></div>";
	}
	else if($arr_get['vd'])
	{
		echo "<div class=\"page-title\"><p class=\"title-back-bt a-href-link\" link=\"mback\"><span class=\"title-back-box\">&lt;</span></p><p class=\"title a-href-link\" link=\"mback\">足迹</p><p class=\"title-nav-sym\">&gt;</p><p class=\"title a-href-link\" link=\"{$_SERVER['PHP_SELF']}?vd=1&l={$page_t}&uid={$uid_t}\">正文</p></div>";
	}
	else if($arr_get['rp'])
	{
		echo "<div class=\"page-title\"><p class=\"title-back-bt a-href-link\" link=\"mback\"><span class=\"title-back-box\">&lt;</span></p><p class=\"title a-href-link\" link=\"mback\">价格参考</p><p class=\"title-nav-sym\">&gt;</p><p class=\"title a-href-link\" link=\"{$_SERVER['PHP_SELF']}?rp=1&l={$page_t}&uid={$uid_t}\">正文</p></div>";
	}
	else
	{
?>
	<div class="page-title"><p class="title-back-bt a-href-link" link="mback"><span class="title-back-box">&lt;</span></p><p class="title a-href-link" link="<?=$arr_title_link[$page_t]['link'];?>"><?=$arr_title_link[$page_t]['t'];?></p><p class="title-nav-sym">&gt;</p><p class="title a-href-link" link="<?=$_SERVER['PHP_SELF'];?>?l=<?=$page_t;?>&uid=<?=$uid_t;?>">正文</p></div>
<?
	}
}
?>