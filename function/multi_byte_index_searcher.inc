<?
$IS_MULTI_BYTE_INDEX_SEARCHER = 1;	define("IS_MULTI_BYTE_INDEX_SEARCHER", 1);

$GB_TB_RATIO_NUM = 166;

function get_arr_s_word($s_word)
{
	global $is_yes_print;
	
	$arr_s_word = array();
	$search_str = @trim($s_word);
	$search_str = preg_replace("/\s+/"," ",$search_str);
	if($search_str)
	{
		$mb_len = mb_strlen($search_str, "UTF-8");
		$arr_return_s_word = return_arr_s_word($search_str);
		if($is_yes_print>0)
		{
			echo "mb_len-1={$mb_len}<br />";
			echo "arr_return_s_word=";
			echo("<pre>");print_r($arr_return_s_word);echo("</pre>");
		}
		$h_s_word = $arr_return_s_word['h_s_word'];
		$mb_len = mb_strlen($h_s_word, "UTF-8");
		if($is_yes_print>0)
		{
			echo "mb_len-2={$mb_len}<br />";
		}
		if($mb_len>1 && $mb_len<61)
		{
			$arr_q_value = return_loop_select_query($arr_return_s_word['GB_ARR_S_WORD']);
			$arr_s_word = $arr_q_value['sword'];
			if($is_yes_print>0)
			{
				echo "arr_s_word=";
				echo("<pre>");print_r($arr_s_word);echo("</pre>");
			}
			unset($arr_q_value);
		}
		unset($arr_return_s_word);
	}
	
	return $arr_s_word;
}

function searched_str_color_replace($arr_vars)
{
	global $is_yes_print, $ARR_B_REPLACE_STR;
	
	foreach($arr_vars AS $ss_key=>$ss_value)
	{
		$$ss_key = $ss_value;//$keyword_str, $s_word, $arr_s_word, $color_css, $is_need_sub_str
	}
	if(!$color_css) $color_css="s-keyword";
	if(!$is_need_sub_str) $is_need_sub_str=0;
	
	$is_already_replace = 0;
	$txt_str_max_num = 150;
	if($keyword_str)
	{
		foreach($ARR_B_REPLACE_STR AS $replace_f=>$replace_t)//$ARR_B_REPLACE_STR assign verym_187_config.inc
		{
			$keyword_str = str_ireplace($replace_f,$replace_t,$keyword_str);
		}
		if($is_need_sub_str < 1)
		{
			$preg_str = func_preg_match_replace_str($s_word);//func_preg_match_replace_str assign func_core.inc
			if(preg_match("/{$preg_str}/i", $keyword_str))
			{
				$keyword_str = str_ireplace($s_word,"<span class=\"{$color_css}\">{$s_word}</span>",$keyword_str);
			}
			else if(count($arr_s_word) > 0)
			{
				foreach($arr_s_word AS $searched_word)
				{
					$loop_mb_len = mb_strlen($searched_word, "UTF-8");
					if($loop_mb_len<2) continue;
					$keyword_str = str_ireplace($searched_word,"<span class=\"{$color_css}\">{$searched_word}</span>",$keyword_str);
				}
			}
			unset($preg_str);
		}
		else
		{
			if($s_word)
			{
				$arr_temp = explode($s_word, $keyword_str);
				if(count($arr_temp) > 1)
				{
					$is_already_replace = 1;
					$keyword_str = $s_word.$arr_temp['1'];
					for($i=2; $i<6; $i++)
					{
						$is_break = 0;
						if($arr_temp[$i])
						{
							$add_str = $arr_temp[$i];
							$strip_tag_str_1 = strip_tags($keyword_str);
							$mb_len_1 = mb_strlen($strip_tag_str.$s_word.$add_str, "UTF-8");
							if($mb_len_1 > $txt_str_max_num)
							{
								$mb_len_2 = mb_strlen($strip_tag_str.$s_word, "UTF-8");
								$substr_num = $txt_str_max_num-$mb_len_2;
								if($substr_num > 0)
								{
									$add_str = mb_substr($add_str, 0, $substr_num, "UTF-8");
								}
								else
								{
									$add_str = "";
								}
								$is_break = 1;
							}
							$keyword_str = $keyword_str.$s_word.$add_str;
						}
						if($is_break > 0)
						{
							break;
						}
					}
					$keyword_str = str_ireplace($s_word,"<span class=\"{$color_css}\">{$s_word}</span>",$keyword_str);
				}
				unset($arr_temp);
			}
			if($is_already_replace<1 && count($arr_s_word)>0)
			{
				$arr_temp = explode($arr_s_word['0'], $keyword_str);
				if(count($arr_temp) > 1)
				{
					$keyword_str = $arr_s_word['0'].$arr_temp['1'];
					for($i=2; $i<6; $i++)
					{
						$is_break = 0;
						if($arr_temp[$i])
						{
							$add_str = $arr_temp[$i];
							$strip_tag_str_1 = strip_tags($keyword_str);
							$mb_len_1 = mb_strlen($strip_tag_str.$arr_s_word['0'].$add_str, "UTF-8");
							if($mb_len_1 > $txt_str_max_num)
							{
								$mb_len_2 = mb_strlen($strip_tag_str.$arr_s_word['0'], "UTF-8");
								$substr_num = $txt_str_max_num-$mb_len_2;
								if($substr_num > 0)
								{
									$add_str = mb_substr($add_str, 0, $substr_num, "UTF-8");
								}
								else
								{
									$add_str = "";
								}
								$is_break = 1;
							}
							$keyword_str = $keyword_str.$arr_s_word['0'].$add_str;
						}
						if($is_break > 0)
						{
							break;
						}
					}
				}
				unset($arr_temp);
				foreach($arr_s_word AS $searched_word)
				{
					$loop_mb_len = mb_strlen($searched_word, "UTF-8");
					if($loop_mb_len<2) continue;
					$keyword_str = str_ireplace($searched_word,"<span class=\"{$color_css}\">{$searched_word}</span>",$keyword_str);
				}
			}
		}
	}
	
	return $keyword_str;
}

function special_mb_replace($str,$isNeedSpace=1,$isNoReplace=0)
{
	$str = str_ireplace("<br","",$str);
	$str = str_ireplace("<br>","",$str);
	$str = str_ireplace("</br>","",$str);
	$str = str_ireplace("<b>","",$str);
	$str = str_ireplace("<b","",$str);
	$str = str_ireplace("</b>","",$str);
	$str = str_ireplace("[br]","",$str);
	//$str = str_ireplace("&","&amp;",$str);

	if($isNoReplace)
	{
		$arr_replace_word = array("`","~","!","@","#","$","%","^","&","*","(",")","－","-","_","=","+","|","\\","[","]","{","}","\"","'",":",";",">","<",",",".","?","/","～","`","！","·","#","￥","€","＄","￡","%","……","…—","—","…","*","（","〔","〕","［","］","｛","｝","）","-","——","—…","=","+","、","|","[","]","{","}","‘","“","”","’","；","：","∶","？","/","〉","〈","《","。","，","　","☆","′","″");
	}
	else
	{
		$arr_replace_word = array("`","~","!","@","#","$","%","^","&","*","(",")","－","-","_","=","+","|","\\","[","]","{","}","\"","'",":",";",">","<",",",".","?","/","～","`","！","·","#","￥","€","＄","￡","%","……","…—","—","…","*","（","〔","〕","［","］","｛","｝","）","-","——","—…","=","+","、","|","[","]","{","}","‘","“","”","’","；","：","∶","？","/","〉","》","〈","《","。","，","　","☆","′","″","↓");
	}
	foreach($arr_replace_word AS $val)
	{
		if($isNeedSpace > 0)
		{
			$str=str_ireplace($val," ",$str);
		}
		else
		{
			$str=str_ireplace($val,"",$str);
		}
	}

	$str = str_replace("０","0",$str);
	$str = str_replace("１","1",$str);
	$str = str_replace("２","2",$str);
	$str = str_replace("３","3",$str);
	$str = str_replace("４","4",$str);
	$str = str_replace("５","5",$str);
	$str = str_replace("６","6",$str);
	$str = str_replace("７","7",$str);
	$str = str_replace("８","8",$str);
	$str = str_replace("９","9",$str);
	$str = str_replace("ａ","a",$str);
	$str = str_replace("ｂ","b",$str);
	$str = str_replace("ｃ","c",$str);
	$str = str_replace("ｄ","d",$str);
	$str = str_replace("ｅ","e",$str);
	$str = str_replace("ｆ","f",$str);
	$str = str_replace("ｇ","g",$str);
	$str = str_replace("ｈ","h",$str);
	$str = str_replace("ｉ","i",$str);
	$str = str_replace("ｊ","j",$str);
	$str = str_replace("ｋ","k",$str);
	$str = str_replace("ｌ","l",$str);
	$str = str_replace("ｍ","m",$str);
	$str = str_replace("ｎ","n",$str);
	$str = str_replace("ｏ","o",$str);
	$str = str_replace("ｐ","p",$str);
	$str = str_replace("ｑ","q",$str);
	$str = str_replace("ｒ","r",$str);
	$str = str_replace("ｓ","s",$str);
	$str = str_replace("ｔ","t",$str);
	$str = str_replace("ｕ","u",$str);
	$str = str_replace("ｖ","v",$str);
	$str = str_replace("ｗ","w",$str);
	$str = str_replace("ｘ","x",$str);
	$str = str_replace("ｙ","y",$str);
	$str = str_replace("ｚ","z",$str);
	$str = str_replace("Ａ","a",$str);
	$str = str_replace("Ｂ","b",$str);
	$str = str_replace("Ｃ","c",$str);
	$str = str_replace("Ｄ","d",$str);
	$str = str_replace("Ｅ","e",$str);
	$str = str_replace("Ｆ","f",$str);
	$str = str_replace("Ｇ","g",$str);
	$str = str_replace("Ｈ","h",$str);
	$str = str_replace("Ｉ","i",$str);
	$str = str_replace("Ｊ","j",$str);
	$str = str_replace("Ｋ","k",$str);
	$str = str_replace("Ｌ","l",$str);
	$str = str_replace("Ｍ","m",$str);
	$str = str_replace("Ｎ","n",$str);
	$str = str_replace("Ｏ","o",$str);
	$str = str_replace("Ｐ","p",$str);
	$str = str_replace("Ｑ","q",$str);
	$str = str_replace("Ｒ","r",$str);
	$str = str_replace("Ｓ","s",$str);
	$str = str_replace("Ｔ","t",$str);
	$str = str_replace("Ｕ","u",$str);
	$str = str_replace("Ｖ","v",$str);
	$str = str_replace("Ｗ","w",$str);
	$str = str_replace("Ｘ","x",$str);
	$str = str_replace("Ｙ","y",$str);
	$str = str_replace("Ｚ","z",$str);
	$str = str_replace("â","a",$str);
	$str = str_replace("ê","e",$str);
	$str = str_replace("è","e",$str);
	$str = str_replace("é","e",$str);
	$str = str_replace("ñ","n",$str);
	$str = str_replace("ü","u",$str);
	
	if($isNeedSpace > 0)
	{
		$str = preg_replace("/\s+/"," ",$str);
		$str = @trim($str);
	}
	else
	{
		$str = preg_replace("/\s+/","",$str);
	}
	
	return($str);
}

function return_mb_cjk_search_insert_query($group_uid, $type, $str)
{
	global $GB_DB_POS,$GB_DB,$GB_FDS,$GB_VALUES;
	global $GB_ARR_QUERY,$GB_ARR_OVERLAP_STR, $GB_TB_RATIO_NUM;

	$mb_len = mb_strlen($str, "UTF-8");
	//echo $mb_len."<br>";
	if($mb_len > 0)
	{
		$check_etc_byte = 0;
		for($i=0;$i<$mb_len;$i++)
		{
			$two_str = mb_substr($str, $i, 2, "UTF-8");
			$first_str = mb_substr($two_str, 0, 1, "UTF-8");
			$ascii_num = ord($first_str);
			if(($ascii_num<=239) && ($ascii_num>=224)) //3byte
			{
				$temp_tb_num_2 = ($ascii_num & 0x0F) << 12 | (ord($first_str{0 + 1}) & 0x3F) << 6
                                                           | (ord($first_str{0 + 2}) & 0x3F);
				//echo $temp_tb_num_2."<br>";
				$tb_num_2 = $temp_tb_num_2 % $GB_TB_RATIO_NUM;
				//echo $first_str." : ".$tb_num_2."<br>";
				$tb = "index_cjk_".$tb_num_2;
				
				if(in_array($two_str, $GB_ARR_OVERLAP_STR[$type]))
				{
					//echo "{$two_str} - OVERLAP_STR 3\n";
				}
				else
				{
					$low_str = strtolower($two_str);
					$GB_ARR_QUERY[] = "INSERT INTO ".$GB_DB.".".$tb." (".$GB_FDS.") VALUES (".$GB_VALUES.",'{$type}','{$low_str}',{$GB_DB_POS},{$group_uid})";
					$GB_ARR_OVERLAP_STR[$type][] = $two_str;
					$GB_DB_POS++;
				}
			}
			else //Ex : str = 不是Love => 不是, 是L
			{
				$check_etc_byte = 1;
				$j = $mb_len - $i;
				$str2 = mb_substr($str, $i, $j, "UTF-8"); // Ex : $str2 = Love
				//echo $two_str;
				$k = $i - 1;
				$str3 = mb_substr($str, $k, 1, "UTF-8"); // Ex : $str3 = 是Love => 是
				//echo $str3."<br>";
				break;
			}
		}

		if($check_etc_byte)
		{
			if($str3)
			{
				if(in_array($two_str, $GB_ARR_OVERLAP_STR[$type]))
				{
					//echo "{$two_str} - OVERLAP_STR 4\n";
				}
				else
				{
					array_pop($GB_ARR_QUERY);
					array_pop($GB_ARR_OVERLAP_STR[$type]);
					$GB_ARR_QUERY[] = "INSERT INTO ".$GB_DB.".".$tb." (".$GB_FDS.") VALUES (".$GB_VALUES.",'{$type}','{$str3}',{$GB_DB_POS},{$group_uid})";
					$GB_ARR_OVERLAP_STR[$type][] = $str3;
					$GB_DB_POS++;	
				}
			}
			return return_mb_search_insert_query($group_uid, $type, $str2);
		}
		else
		{
			return $GB_ARR_QUERY;
		}
	}
}

function return_mb_search_insert_query($group_uid, $type, $str)
{ 
	global $GB_DB_POS,$GB_DB,$GB_FDS,$GB_VALUES;
	global $GB_ARR_QUERY,$GB_ARR_OVERLAP_STR;

	$low_str = strtolower($str);
	$check_str = mb_substr($low_str, 0, 1, "UTF-8");
	$ascii_num = ord($check_str);
	$mb_len = mb_strlen($low_str, "UTF-8");
	if($mb_len > 0)
	{
		if(($ascii_num<=239) && ($ascii_num>=224)) //3byte
		{
			return return_mb_cjk_search_insert_query($group_uid, $type, $low_str);
		}
		else
		{
			if(($ascii_num<=244) && ($ascii_num>=240)) //4byte
			{
				$tb = "index_4byte_".$ascii_num;
			}
			else
			{	
				if(($ascii_num<=57) && ($ascii_num>=48)) // 0~9
				{
					$tb = "index_num";
				}
				else if(($ascii_num<=122) && ($ascii_num>=97)) // a~z
				{
					$tb = "index_en_".$check_str;
				}
				else if(($ascii_num<=90) && ($ascii_num>=65)) // A~Z
				{
					$check_str = strtolower($check_str);
					$tb = "index_en_".$check_str;
				}
				else //Etc
				{
					$tb = "index_etc";
				}
			}
			
			if(in_array($low_str, $GB_ARR_OVERLAP_STR[$type]))
			{
				//echo "{$low_str} - OVERLAP_STR 1\n";
			}
			else
			{
				$GB_ARR_QUERY[] = "INSERT INTO ".$GB_DB.".".$tb." (".$GB_FDS.") VALUES (".$GB_VALUES.",'{$type}','{$low_str}',{$GB_DB_POS},{$group_uid})";
				$GB_ARR_OVERLAP_STR[$type][] = $low_str;
				$GB_DB_POS++;
			}

			$check_3byte = 0;
			for($i=0;$i<$mb_len;$i++)
			{
				$first_str = mb_substr($low_str, $i, 1, "UTF-8");
				$ascii_num2 = ord($first_str);
				if(($ascii_num2<=239) && ($ascii_num2>=224)) //3byte Ex : str = Love不是 => Love, 不是
				{
					$j = $mb_len - $i;
					$str2 = mb_substr($low_str, $i, $j, "UTF-8"); //  Ex : str2 = 不是
					$str3 = mb_substr($low_str, 0, $i, "UTF-8"); //  Ex : str3 = Love
					//echo $str3."<br>";
					$check_3byte = 1;
					break;
				}
			}

			if($check_3byte)
			{
				if($str3)
				{
					if(in_array($str3, $GB_ARR_OVERLAP_STR[$type]))
					{
						//echo "{$str3} - OVERLAP_STR 2\n";
					}
					else
					{
						$GB_ARR_QUERY[] = "INSERT INTO ".$GB_DB.".".$tb." (".$GB_FDS.") VALUES (".$GB_VALUES.",'{$type}','{$str3}',{$GB_DB_POS},{$group_uid})";
						$GB_ARR_OVERLAP_STR[$type][] = $str3;
						$GB_DB_POS++;
					}
				}
				return return_mb_cjk_search_insert_query($group_uid, $type, $str2);
			}
			else
			{
				return $GB_ARR_QUERY;
			}
		}
	}
}

function return_arr_s_word($temp_s_word, $get_h_s_word="")
{
	global $GB_ARR_OVERLAP_COUNT_STR, $GB_S_W_COUNT_2, $GB_T_WORD_COUNT;

	$arr_return_s_word = array();

	$temp_s_word = special_mb_replace($temp_s_word);
	$arr_s_word = explode(" ",$temp_s_word);
	$arr_s_word = array_unique($arr_s_word);
	if($get_h_s_word)
	{
		$get_h_s_word = @trim($get_h_s_word);
		$en_h_s_word = urlencode($get_h_s_word);
		$arr_h_s_word = explode("^^", $get_h_s_word);
		$arr_h_s_word = array_unique($arr_h_s_word);
		$temp_h_s_word = implode(" ", $arr_h_s_word);

		$arr_now_s_word = array();
		foreach($arr_s_word AS $now_s_word)
		{
			$now_s_word = @trim($now_s_word);
			if(!$now_s_word) continue;
			$arr_now_s_word[] = $now_s_word;
		}
		$h_s_word = implode(" ", $arr_now_s_word);
		$h_s_word = $get_h_s_word."^^".$h_s_word;
		$arr_h_s_word = explode("^^", $h_s_word);
		$arr_h_s_word = array_unique($arr_h_s_word);
		$h_s_word = implode("^^", $arr_h_s_word);

		$temp_h_s_word_2 = implode(" ", $arr_now_s_word);
		$temp_s_word = $temp_h_s_word." ".$temp_h_s_word_2;
		$arr_s_word = explode(" ",$temp_s_word);
		$arr_s_word = array_unique($arr_s_word);
		$GB_ARR_S_WORD = $arr_s_word;
	}
	else
	{
		$GB_ARR_S_WORD = $arr_s_word;
		$en_h_s_word = "";
		$h_s_word = implode(" ", $arr_s_word);
	}
	//echo("<pre>");print_r($arr_s_word);echo("</pre>");
	//$s_word_count = count($arr_s_word);
	$t_word_count = 0;
	$GB_ARR_OVERLAP_COUNT_STR = array();
	$arr_new_s_word = array();
	foreach($arr_s_word AS $s_word)
	{
		$s_word = @trim($s_word);
		if(!$s_word) continue;
		$s_word_count = search_str_count($s_word);
		$t_word_count += $s_word_count;
		$arr_new_s_word[] = $s_word;
	}
	//echo("<pre>");print_r($arr_new_s_word);echo("</pre>");
	$s_log_str = implode("-", $arr_new_s_word);
	$GB_T_WORD_COUNT = $t_word_count;
	//echo $temp_s_word."<br>";

	$arr_return_s_word['en_h_s_word'] = $en_h_s_word;
	$arr_return_s_word['h_s_word'] = $h_s_word;
	$arr_return_s_word['GB_ARR_S_WORD'] = $GB_ARR_S_WORD;
	$arr_return_s_word['t_word_count'] = $t_word_count;
	$arr_return_s_word['GB_T_WORD_COUNT'] = $GB_T_WORD_COUNT;
	$arr_return_s_word['arr_new_s_word'] = $arr_new_s_word;
	$arr_return_s_word['s_log_str'] = $s_log_str;
	$arr_return_s_word['s_w_count_1'] = 12;

	return $arr_return_s_word;
}

function search_cjk_str_count($str,$count=0)
{
	global $GB_ARR_OVERLAP_COUNT_STR;

	$mb_len = mb_strlen($str, "UTF-8");
	if($mb_len > 0)
	{
		$check_etc_byte = 0;
		for($i=0;$i<$mb_len;$i++)
		{
			$two_str = mb_substr($str, $i, 2, "UTF-8");
			$first_str = mb_substr($two_str, 0, 1, "UTF-8");
			$ascii_num = ord($first_str);
			if(($ascii_num<=239) && ($ascii_num>=224)) //3byte
			{
				if(in_array($two_str, $GB_ARR_OVERLAP_COUNT_STR))
				{
				}
				else
				{
					$count++;
					$GB_ARR_OVERLAP_COUNT_STR[] = $two_str;
				}
			}
			else //Ex : str = 不是Love => 不是, 是L
			{
				$check_etc_byte = 1;
				$j = $mb_len - $i;
				$str2 = mb_substr($str, $i, $j, "UTF-8"); // Ex : $str2 = Love
				$k = $i - 1;
				$str3 = mb_substr($str, $k, 1, "UTF-8"); // Ex : $str3 = 是L => 是
				break;
			}
		}

		if($check_etc_byte)
		{
			if($str3)
			{
				$count--;
			}
			return search_str_count($str2,$count);
		}
		else
		{
			if($i > 1)
			{
				$count--;
			}
			return $count;
		}
	}
	else
	{
		return $count;
	}
}

function search_str_count($str,$count=0)
{
	global $GB_ARR_OVERLAP_COUNT_STR;
	
	$check_str = mb_substr($str, 0, 1, "UTF-8");
	$ascii_num = ord($check_str);
	$mb_len = mb_strlen($str, "UTF-8");
	if($mb_len > 0)
	{
		if(($ascii_num<=239) && ($ascii_num>=224)) //3byte
		{
			return search_cjk_str_count($str,$count);
		}
		else
		{
			if(in_array($str, $GB_ARR_OVERLAP_COUNT_STR))
			{
			}
			else
			{
				$count++;
				$GB_ARR_OVERLAP_COUNT_STR[] = $str;
			}
			
			$check_3byte = 0;
			for($i=0;$i<$mb_len;$i++)
			{
				$first_str = mb_substr($str, $i, 1, "UTF-8");
				$ascii_num2 = ord($first_str);
				if(($ascii_num2<=239) && ($ascii_num2>=224)) //3byte Ex : str = Love不是 => Love, 不是
				{
					$j = $mb_len - $i;
					$str2 = mb_substr($str, $i, $j, "UTF-8"); //  Ex : str2 = 不是
					$str3 = mb_substr($str, 0, $i, "UTF-8"); //  Ex : str3 = Love
					//echo $str3."<br>";
					$check_3byte = 1;
					break;
				}
			}

			if($check_3byte)
			{
				if($str3)
				{
					$GB_ARR_OVERLAP_COUNT_STR[] = $str3;
				}
				return search_cjk_str_count($str2,$count);
			}
			else
			{
				return $count;
			}
		}
	}
	else
	{
		return $count;
	}
}

function return_loop_select_query($arr_str)
{
	global $GB_DB,$GB_TB_NUM,$GB_JOIN_UID,$GB_ONLY_SEARCH_TB,$GB_T_WORD_COUNT,$GB_S_W_COUNT_2,$GB_STOP_COUNT;
	global $GB_ARR_TB,$GB_ARR_JOIN_UID,$GB_ARR_WHERE_STR,$GB_ARR_LIKE_STR,$GB_ARR_OVERLAP_STR,$GB_ARR_OVERLAP_STR_2,$GB_ARR_SORT,$GB_ARR_STOP_WORD_1_2,$GB_ARR_STOP_WORD_1_1,$GB_ARR_STOP_WORD_2_2,$GB_ARR_STOP_WORD_2_1;

	$GB_TB_NUM = 0;
	$GB_ARR_TB = array();
	$GB_ARR_WHERE_STR = array();
	$GB_ARR_LIKE_STR = array();
	$GB_ARR_OVERLAP_STR = array();
	$GB_ARR_OVERLAP_STR_2 = array();
	$GB_ARR_JOIN_UID = array();
	$GB_ARR_SORT = array();
	/*
$GB_ARR_STOP_WORD_1_2 = array("你们","我们","他们","她们","由于","立刻","以为","比较","除了","此外","以外","连忙","对于","关于","至于","根据","为了","历来","因为","所以","因此","依次","不然","总共","不管","既然","假如","并且","通过","一律","即使","它们","按照","多少","别人","总是","自从","虽然","但是","或者","一般","不曾","人家","那样","这些","哪儿","多么","不能","仍然","那里","哪里","这边","这样","屡次","非常","特别","十分","相当","更加","公斤","稍微","还要","尤其","局部","可以","正在","逐步","逐渐","到底","何必","何等","赶快","只好","难道","难怪","究竟","的确","偶然","过于","尤其","未必","不免","居然","全是","当然","幸好","幸亏","毕竟","怎么","统统","怎样","那些","哪些","刚刚","刚才","没能","几乎","不仅","不禁","简直","索性","愿意","反正","何苦","必然","莫非","反倒","不要","未免","一样","老是","恰恰","不妨","继续","已经","何尝","何曾","大概","大约","帮助","其实","明明","必定","忽然","时常","从来","从此","常常","往往","一直","一向","赶紧","渐渐","处处","到处","只是","果然","偶尔","永远","一定","一致","以至","不只","全都","终于","始终","不断","立即","将要","单单","厘米","而且","反复","甚至","原来","没有","公里","再次","成天","向来","仍旧","不敢","天天","根据","千克","仅仅","大都","不会","每天","小时","分钟","一概","一起","重新","季节","季度","年代","世纪","一再","帮忙","星期","稍稍","忽略","莫非","无论","奇怪","曾经","暂且","偏偏","格外","极其","及其","况且","不止","否则","宁肯","要是","尽管","竟然","不是","好象","可能","就是");
	$GB_ARR_STOP_WORD_1_1 = array("的","地","得","着","了","过","吧","吗","啊","哦","呢","么","你","从","您","我","总","他","都","它","常","她","刚","啦","可","把","被","将","集","到","在","却","自","以","还","叫","让","给","和","与","同","比","为","对","或","跟","就","又","并","哪","当","于","多","哟","这","那","谁","几","很","最","大","更","较","小","少","人","更","极","顶","光","靠","全","共","不","便","别","再","也","只","本","位","间","条","根","双","群","堆","队","排","帮","棵","匹","片","台","辆","首","部","分","年","章","册","节","段","副","颗","粒","件","朵","时","秒","刻","元","角","吨","尺","点","日","左","右","东","南","西","北","中","次","回","寸","米","两","里","上","下","趟","遍","声","天","周");
	$arr_stop_en_word_1 = array("is","the","you","of","i","a","to","me","in","my","on","it","and","for","your","be","with","what","this","that","so","from","its","if","at","by","as","or","oh","into","these","but","mine","an","they","other","his","him","any","while","them","yet","those","which","their","wow","ah","am","aint","all","are","been","dont","de","el","get","go","her","im","let","no","u","we","were","will","youre");
	$GB_ARR_STOP_WORD_2_2 = array("希望","凭着","为着","呵呵","哈哈","凭借","横竖","嘻嘻","哎呀","权且","咕咚","假若","马上","扑通","喀嚓","轰隆","也好","姑且","赶忙","来着","趁着","着呢","哗哗","继而","终究","沿着","顺着","遵照","打从","毫米","毫秒","越发","一齐","顿时","径直","径自","有点","咚咚","呼啦","进而","本着","略微","嚣张","夸张","比如","好听","没准","愤怒","努力","将来");
	$GB_ARR_STOP_WORD_2_1 = array("归","凭","哎","呗","嗨","嘿","遭","盏","哼","替","捆","番","阵","串","勿","朝","越","架","嚯","呕","咦","喽");
	$arr_stop_en_word_2 = array("up","do","down","have","when","who","after","some","nobody","along","now","one","out","over","who","since","till","because","below","none","though","ill");
*/
	$GB_ARR_STOP_WORD_1_2 = array('nownonowno');
	$GB_ARR_STOP_WORD_1_1 = array("的","了");
	//$arr_stop_en_word_1 = array('nownonowno');
	$arr_stop_en_word_1 = array("is","the","you","of","i","a","to","me","in","my","on","it","and","for","your","be","with","what","this","that","so","from","its","if","at","by","as","or","oh","into","these","but","mine","an","they","other","his","him","any","while","them","yet","those","which","their","wow","ah","am","aint","all","are","been","dont","de","el","get","go","her","im","let","no","u","we","were","will","youre");
	$GB_ARR_STOP_WORD_2_2 = array('nownonowno');
	$GB_ARR_STOP_WORD_2_1 = array('nownonowno');
	//$arr_stop_en_word_2 = array('nownonowno');
	$arr_stop_en_word_2 = array("up","do","down","have","when","who","after","some","nobody","along","now","one","out","over","who","since","till","because","below","none","though","ill");
	
	$result = 0;
	$GB_STOP_COUNT = 0;
	$stop_en_count = 0;
	foreach($arr_str AS $str)
	{
		$str = @trim($str);
		if(!$str) continue;
		//echo $str."<br>";
		$mb_len = (mb_strlen($str, "UTF-8"));
		
		if($mb_len > 0)
		{
			$check_str = mb_substr($str, 0, 1, "UTF-8");
			$ascii_num = ord($check_str);
			
			if((($ascii_num<=122) && ($ascii_num>=97)) || (($ascii_num<=90) && ($ascii_num>=65)))
			{
				if($stop_en_count > 0)
				{
					if($GB_T_WORD_COUNT < $GB_S_W_COUNT_2)
					{
					}
					else
					{
						if(@in_array ($str, $arr_stop_en_word_1)) 
						{
							//echo "$stop_en_count : <font color=green>1 : $str</font><br>";
							$GB_T_WORD_COUNT--;
							$GB_ARR_OVERLAP_STR_2[] = $str;
							continue;
						}
						
						if($GB_T_WORD_COUNT > $GB_S_W_COUNT_2)
						{
							if(@in_array ($str, $arr_stop_en_word_2)) 
							{
								//echo "$stop_en_count : <font color=green>2 : $str</font><br>";
								$GB_T_WORD_COUNT--;
								$GB_ARR_OVERLAP_STR_2[] = $str;
								continue;
							}
						}
					}
				}
			}
			$stop_en_count++;

			$result = return_mb_select_query($str);
		}
	}
	
	/*
echo "<font color=darkred>2 - $GB_T_WORD_COUNT</font><br>";
	echo("<pre>");print_r($GB_ARR_TB);echo("</pre>");
	echo("<pre>");print_r($GB_ARR_JOIN_UID);echo("</pre>");
	echo("<pre>");print_r($GB_ARR_WHERE_STR);echo("</pre>");
	echo("<pre>");print_r($GB_ARR_LIKE_STR);echo("</pre>");
	echo("<pre>");print_r($GB_ARR_SORT);echo("</pre>");
*/

	$tb = implode(",",$GB_ARR_TB);
	$join_str = implode(" ",$GB_ARR_JOIN_UID);
	$and_str = implode(" ",$GB_ARR_WHERE_STR);
	$like_and_str = implode(" ",$GB_ARR_LIKE_STR);
	$sort_str = implode(",",$GB_ARR_SORT);
	if($result)
	{
		$arr_q_value = array();
		$arr_q_value['tb'] = $tb;
		$arr_q_value['join'] = $join_str;
		$arr_q_value['and'] = $and_str;
		$arr_q_value['like_and'] = $like_and_str;
		$arr_q_value['sort'] = $sort_str;
		$arr_overlap_strs = array_merge($GB_ARR_OVERLAP_STR, $GB_ARR_OVERLAP_STR_2);
		$arr_overlap_strs = array_unique($arr_overlap_strs);
		$arr_q_value['sword'] = $arr_overlap_strs;
		return($arr_q_value);
	}
}

function return_mb_select_query($str)
{ 
	global $GB_DB,$GB_TB_NUM,$GB_JOIN_UID,$GB_ONLY_SEARCH_TB,$GB_T_WORD_COUNT,$GB_S_W_COUNT_2;
	global $GB_ARR_TB,$GB_ARR_JOIN_UID,$GB_ARR_WHERE_STR,$GB_ARR_LIKE_STR,$GB_ARR_OVERLAP_STR_2,$GB_ARR_OVERLAP_STR,$GB_ARR_SORT;
	
	//$low_str = strtolower($str);
	$low_str = mb_strtolower($str,"UTF-8");
	$check_str = mb_substr($low_str, 0, 1, "UTF-8");
	$ascii_num = ord($check_str);
	$mb_len = mb_strlen($low_str, "UTF-8");
	if($mb_len > 0)
	{
		if(($ascii_num<=239) && ($ascii_num>=224)) //3byte
		{
			return return_mb_cjk_select_query($low_str);
		}
		else
		{
			if(($ascii_num<=244) && ($ascii_num>=240)) //4byte
			{
				$tb = "index_4byte_".$ascii_num;
			}
			else
			{	
				if(($ascii_num<=57) && ($ascii_num>=48)) // 0~9
				{
					$tb = "index_num";
				}
				else if(($ascii_num<=122) && ($ascii_num>=97)) // a~z
				{
					$tb = "index_en_".$check_str;
				}
				else if(($ascii_num<=90) && ($ascii_num>=65)) // A~Z
				{
					//$check_str = strtolower($check_str);
					$check_str = mb_strtolower($check_str,"UTF-8");
					$tb = "index_en_".$check_str;
				}
				else //Etc
				{
					$tb = "index_etc";
				}
			}	

			if(in_array($low_str, $GB_ARR_OVERLAP_STR))
			{
			}
			else
			{				
				$GB_ARR_TB[] = $GB_DB.".".$tb." S".$GB_TB_NUM;
				if($GB_ONLY_SEARCH_TB > 0)
				{
					if($GB_TB_NUM > 0)
					{
						$GB_ARR_JOIN_UID[] = "AND S0.t_str=S{$GB_TB_NUM}.t_str AND S0.".$GB_JOIN_UID."=S".$GB_TB_NUM.".".$GB_JOIN_UID;
					}
				}
				else
				{
					//$GB_ARR_JOIN_UID[] = "AND S.".$GB_JOIN_UID."=S".$GB_TB_NUM.".".$GB_JOIN_UID;
					$GB_ARR_JOIN_UID[] = "AND S.t_str=S{$GB_TB_NUM}.t_str AND S.".$GB_JOIN_UID."=S".$GB_TB_NUM.".".$GB_JOIN_UID;
				}
				$GB_ARR_WHERE_STR[] = "AND S".$GB_TB_NUM.".idx_str='".$low_str."'";
				//$GB_ARR_LIKE_STR[] = "AND T".$GB_TB_NUM.".idx_str LIKE '".$low_str."%'";
				$GB_ARR_LIKE_STR[] = "S".$GB_TB_NUM.".idx_str^".$low_str;
				$GB_ARR_OVERLAP_STR[] = $low_str;
				$GB_ARR_SORT[] = "S".$GB_TB_NUM.".pos";
				$GB_TB_NUM++;
			}
			//echo "GB_TB_NUM-1={$GB_TB_NUM}<br />";
			/*
echo("Table : ".print_r($GB_ARR_TB)."<br>");
			echo("Join Uid : ".print_r($GB_ARR_JOIN_UID)."<br>");
			echo("Where_str : ".print_r($GB_ARR_WHERE_STR)."<br>");
			echo("Where_str : ".print_r($GB_ARR_LIKE_STR)."<br>");
			echo("overlap_str : ".print_r($GB_ARR_OVERLAP_STR)."<br>");
			echo("sort : ".print_r($GB_ARR_SORT)."<br>");
*/
			//exit;
			
			$check_3byte = 0;
			for($i=0;$i<$mb_len;$i++)
			{
				$first_str = mb_substr($low_str, $i, 1, "UTF-8");
				$ascii_num2 = ord($first_str);
				if(($ascii_num2<=239) && ($ascii_num2>=224)) //3byte Ex : str = Love不是 => Love, 不是
				{
					$j = $mb_len - $i;
					$str2 = mb_substr($low_str, $i, $j, "UTF-8"); //  Ex : str2 = 不是
					//echo "str2=".$str2."<br>";
					$str3 = mb_substr($low_str, 0, $i, "UTF-8"); //  Ex : str3 = Love
					//echo "str3=".$str3."<br>";
					$check_3byte = 1;
					break;
				}
			}

			if($check_3byte)
			{
				if($str3) //and idx_str='love不是' =>  and idx_str='love' and idx_str='不是'
				{
					//Delete love不是
					array_pop($GB_ARR_TB);
					array_pop($GB_ARR_JOIN_UID);
					array_pop($GB_ARR_WHERE_STR);
					array_pop($GB_ARR_LIKE_STR);
					array_pop($GB_ARR_SORT);
					if($GB_TB_NUM>0) $GB_TB_NUM--;
					if(in_array($str3, $GB_ARR_OVERLAP_STR))
					{
					}
					else
					{
						//and idx_str='love'
						$GB_ARR_TB[] = $GB_DB.".".$tb." S".$GB_TB_NUM;;
						if($GB_ONLY_SEARCH_TB > 0)
						{
							if($GB_TB_NUM > 0)
							{
								$GB_ARR_JOIN_UID[] = "AND S0.t_str=S{$GB_TB_NUM}.t_str AND S0.".$GB_JOIN_UID."=S".$GB_TB_NUM.".".$GB_JOIN_UID;
							}
						}
						else
						{
							//$GB_ARR_JOIN_UID[] = "AND S.".$GB_JOIN_UID."=S".$GB_TB_NUM.".".$GB_JOIN_UID;
							$GB_ARR_JOIN_UID[] = "AND S.t_str=S{$GB_TB_NUM}.t_str AND S.".$GB_JOIN_UID."=S".$GB_TB_NUM.".".$GB_JOIN_UID;
						}
						$GB_ARR_WHERE_STR[] = "AND S".$GB_TB_NUM.".idx_str='".$str3."'";
						//$GB_ARR_LIKE_STR[] = "AND T".$GB_TB_NUM.".idx_str LIKE '".$str3."%'";
						$GB_ARR_LIKE_STR[] = "S".$GB_TB_NUM.".idx_str^".$str3;
						$GB_ARR_OVERLAP_STR[] = $str3;
						$GB_ARR_SORT[] = "S".$GB_TB_NUM.".pos";
						$GB_TB_NUM++;
					}
				}
				//echo "GB_TB_NUM-2={$GB_TB_NUM}<br />";
				//and idx_str='不是'
				return return_mb_cjk_select_query($str2);
			}
			else
			{
				return 1;
			}
		}
	}
}

function return_mb_cjk_select_query($str)
{
	global $goods_db,$GB_DB,$GB_TB_NUM,$GB_JOIN_UID,$GB_ONLY_SEARCH_TB,$GB_T_WORD_COUNT,$GB_S_W_COUNT_2,$GB_STOP_COUNT;
	global $GB_ARR_TB,$GB_ARR_JOIN_UID,$GB_ARR_WHERE_STR,$GB_ARR_LIKE_STR,$GB_ARR_OVERLAP_STR,$GB_ARR_OVERLAP_STR_2,$GB_ARR_SORT,$GB_ARR_STOP_WORD_1_2,$GB_ARR_STOP_WORD_1_1,$GB_ARR_STOP_WORD_2_2,$GB_ARR_STOP_WORD_2_1,$GB_TB_RATIO_NUM;

	$is_strict_search = 0;
	if($str)
	{
		$arr_strict_s_word = array("首尔大学医学院","首尔大学医院","首尔大学校","首尔大学","首尔大");
		if(@in_array ($str, $arr_strict_s_word))
		{
			$is_strict_search = 1;
		}
	}
	$mb_len = mb_strlen($str, "UTF-8");
	//echo $mb_len."<br>";
	if($mb_len > 0)
	{
		$check_etc_byte = 0;
		$check_array_pop = array();
		for($i=0;$i<$mb_len;$i++)
		{
			$check_i_odd_even = $i%2;
			//echo "{$i}/{$mb_len}=check_i_odd_even={$check_i_odd_even}<br />";
			if($check_i_odd_even > 0)//2글자씩 검색하기 때문에 $i가 0부터 시작하니 홀수인 경우는 스킵하고 짝수일때에만 2글자씩 가져온다.
			{
				if($is_strict_search < 1)
				{
					continue;
				}
			}
			$two_str = mb_substr($str, $i, 2, "UTF-8");
			
			$GB_STOP_COUNT++;
			if($GB_STOP_COUNT > 6)
			{
				if($GB_T_WORD_COUNT < $GB_S_W_COUNT_2)
				{
				}
				else
				{
					if(@in_array ($two_str, $GB_ARR_STOP_WORD_1_2)) 
					{
						//echo "$GB_STOP_COUNT : <font color=blue>2 : $two_str</font><br>";
						$GB_T_WORD_COUNT--;
						$GB_ARR_OVERLAP_STR_2[] = $two_str;
						continue;
					}
					else
					{
						$t_check_stop_word_1 = mb_substr($two_str, 0, 1, "UTF-8");
						if(@in_array ($t_check_stop_word_1, $GB_ARR_STOP_WORD_1_1))
						{
							//echo "$GB_STOP_COUNT : <font color=blue>1-1 : $two_str - $t_check_stop_word_1</font><br>";
							$GB_T_WORD_COUNT--;
							$GB_ARR_OVERLAP_STR_2[] = $t_check_stop_word_1;
							continue;
						}
						else
						{
							$t_check_stop_word_2 = mb_substr($two_str, 1, 1, "UTF-8");
							if(@in_array ($t_check_stop_word_2, $GB_ARR_STOP_WORD_1_1))
							{
								//echo "$GB_STOP_COUNT : <font color=blue>1-2 : $two_str - $t_check_stop_word_2</font><br>";
								$GB_T_WORD_COUNT--;
								$GB_ARR_OVERLAP_STR_2[] = $t_check_stop_word_2;
								continue;
							}
						}
					}
					
					if($GB_T_WORD_COUNT > $GB_S_W_COUNT_2)
					{
						if(@in_array ($two_str, $GB_ARR_STOP_WORD_2_2)) 
						{
							//echo "$GB_STOP_COUNT : <font color=green>2 : $two_str</font><br>";
							$GB_T_WORD_COUNT--;
							$GB_ARR_OVERLAP_STR_2[] = $two_str;
							continue;
						}
						else
						{
							$t_check_stop_word_1 = mb_substr($two_str, 0, 1, "UTF-8");
							if(@in_array ($t_check_stop_word_1, $GB_ARR_STOP_WORD_2_2))
							{
								//echo "$GB_STOP_COUNT : <font color=green>1-1 : $two_str - $t_check_stop_word_1</font><br>";
								$GB_T_WORD_COUNT--;
								$GB_ARR_OVERLAP_STR_2[] = $t_check_stop_word_1;
								continue;
							}
							else
							{
								$t_check_stop_word_2 = mb_substr($two_str, 1, 1, "UTF-8");
								if(@in_array ($t_check_stop_word_2, $GB_ARR_STOP_WORD_2_2))
								{
									//echo "$GB_STOP_COUNT : <font color=green>1-2 : $two_str - $t_check_stop_word_2</font><br>";
									$GB_T_WORD_COUNT--;
									$GB_ARR_OVERLAP_STR_2[] = $t_check_stop_word_2;
									continue;
								}
							}
						}
					}
				}
			}
			
			$first_str = mb_substr($two_str, 0, 1, "UTF-8");
			$ascii_num = ord($first_str);
			if(($ascii_num<=239) && ($ascii_num>=224)) //3byte
			{
				$temp_tb_num_2 = ($ascii_num & 0x0F) << 12 | (ord($first_str{0 + 1}) & 0x3F) << 6
                                                           | (ord($first_str{0 + 2}) & 0x3F);
				$tb_num_2 = $temp_tb_num_2 % $GB_TB_RATIO_NUM;
				$tb = "index_cjk_".$tb_num_2;
				//echo "GB_TB_NUM={$GB_TB_NUM}<br />";
				//echo "two_str={$two_str}<br />";
				//echo("<pre>");print_r($GB_ARR_OVERLAP_STR);echo("</pre>");
				if(in_array($two_str, $GB_ARR_OVERLAP_STR))
				{
				}
				else
				{
					$GB_ARR_TB[] = $GB_DB.".".$tb." S".$GB_TB_NUM;
					if($GB_ONLY_SEARCH_TB > 0)
					{
						if($GB_TB_NUM > 0)
						{
							$GB_ARR_JOIN_UID[] = "AND S0.t_str=S{$GB_TB_NUM}.t_str AND S0.".$GB_JOIN_UID."=S".$GB_TB_NUM.".".$GB_JOIN_UID;
						}
					}
					else
					{
						//$GB_ARR_JOIN_UID[] = "AND S.".$GB_JOIN_UID."=S".$GB_TB_NUM.".".$GB_JOIN_UID;
						$GB_ARR_JOIN_UID[] = "AND S.t_str=S{$GB_TB_NUM}.t_str AND S.".$GB_JOIN_UID."=S".$GB_TB_NUM.".".$GB_JOIN_UID;
					}
					$GB_ARR_WHERE_STR[] = "AND S".$GB_TB_NUM.".idx_str='".$two_str."'";
					//$GB_ARR_LIKE_STR[] = "AND T".$GB_TB_NUM.".idx_str LIKE '".$two_str."%'";
					$GB_ARR_LIKE_STR[] = "S".$GB_TB_NUM.".idx_str^".$two_str;
					$GB_ARR_OVERLAP_STR[] = $two_str;
					$GB_ARR_SORT[] = "S".$GB_TB_NUM.".pos";
					$check_array_pop[] = $two_str;
					$GB_TB_NUM++;
				}
			}
			else //Ex : str = 不是Love => 不是, 是L
			{
				$check_etc_byte = 1;
				$j = $mb_len - $i;
				$str2 = mb_substr($str, $i, $j, "UTF-8"); // Ex : $str2 = Love
				//echo "str2=".$str2."<br>";
				$k = $i - 1;
				$str3 = mb_substr($str, $k, 1, "UTF-8"); // Ex : $str3 = 是L => 是
				//echo "str3=".$str3."<br>";
				break;
			}
		}

		if($check_etc_byte)
		{
			/*
if($str3)
			{
				array_pop($GB_ARR_TB);
				array_pop($GB_ARR_JOIN_UID);
				array_pop($GB_ARR_WHERE_STR);
				array_pop($GB_ARR_LIKE_STR);
				array_pop($GB_ARR_SORT);
			}
			$GB_STOP_COUNT--;
*/
			return return_mb_select_query($str2);
		}
		else
		{
			$check_array_pop_c = count($check_array_pop);
			$check_array_pop_key =  $check_array_pop_c-1;
			$array_pop_len = mb_strlen($check_array_pop[$check_array_pop_key], "UTF-8");
			//echo "$check_array_pop[$check_array_pop_key] : $array_pop_len <br>";

			/*
if($i>1 && $array_pop_len==1)
			{
				array_pop($GB_ARR_TB);
				array_pop($GB_ARR_JOIN_UID);
				array_pop($GB_ARR_WHERE_STR);
				array_pop($GB_ARR_LIKE_STR);
				array_pop($GB_ARR_SORT);
			}
*/
			return 1;
		}
	}
}
?>