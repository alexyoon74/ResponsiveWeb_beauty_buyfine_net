<?
$IS_API_PUBLIC_VARS = 1;
define("IS_API_PUBLIC_VARS", 1);
$arr_req_data = array();
if ($is_no_err > 0) {
	if ($is_yes_print > 1) {
		echo "ARR GET = ";
		echo ("<pre>");
		print_r($_GET);
		echo ("</pre>");
		echo "ARR POST = ";
		echo ("<pre>");
		print_r($_POST);
		echo ("</pre>");
		echo "arr_skip_replace_para = ";
		echo ("<pre>");
		print_r($arr_skip_replace_para);
		echo ("</pre>");
	}
	if (count($_GET) > 0) {
		foreach ($_GET as $key => $value) {
			if ($key == 'arr_uid') continue;
			if ($key == 'arr_s_word') continue;
			if ($key == 'sign_key') continue;
			if (count($arr_skip_replace_para) > 0) {
				if (in_array($key, $arr_skip_replace_para)) {
					continue;
				}
			}
			$value = @trim($value);
			if ($value || $value == '0') {
				$arr_req_data[$key] = $value;
			}
		}
		$arr_req_data = array_map('str_filter', $arr_req_data); //str_replace
		$arr_req_data = array_map('db_escape_string', $arr_req_data); //mysql_escape_string
		$arr_req_data['arr_uid'] = $_GET['arr_uid'];
		$arr_req_data['arr_s_word'] = $_GET['arr_s_word'];
		$arr_req_data['sign_key'] = $_GET['sign_key'];
		if (count($arr_skip_replace_para) > 0) {
			foreach ($arr_skip_replace_para as $key) {
				if ($_GET[$key]) {
					$arr_req_data[$key] = @trim($_GET[$key]);
				}
			}
		}
	}
	unset($_GET);
	if (count($_POST) > 0) {
		foreach ($_POST as $key => $value) {
			if ($key == 'arr_uid') continue;
			if ($key == 'arr_s_word') continue;
			if ($key == 'sign_key') continue;
			if (count($arr_skip_replace_para) > 0) {
				if (in_array($key, $arr_skip_replace_para)) {
					continue;
				}
			}
			$value = @trim($value);
			if ($value || $value == '0') {
				$arr_req_data[$key] = $value;
			}
		}
		$arr_req_data = array_map('str_filter', $arr_req_data); //str_replace
		$arr_req_data = array_map('db_escape_string', $arr_req_data); //mysql_escape_string
		$arr_req_data['arr_uid'] = $_POST['arr_uid'];
		$arr_req_data['arr_s_word'] = $_POST['arr_s_word'];
		$arr_req_data['sign_key'] = $_POST['sign_key'];
		if (count($arr_skip_replace_para) > 0) {
			foreach ($arr_skip_replace_para as $key) {
				if ($_POST[$key]) {
					$arr_req_data[$key] = @trim($_POST[$key]);
				}
			}
		}
	}
	if ($is_arr_post_var > 0) {
	} else {
		unset($_POST);
	}
}
if ($is_yes_print > 0) {
	echo "arr_req_data = ";
	echo ("<pre>");
	print_r($arr_req_data);
	echo ("</pre>");
}
if ($is_no_err > 0 && !$is_no_need_compare_sign_key) {
	if (!$arr_req_data['app_key'] || !$arr_req_data['sign_key']) {
		$is_no_err = 0;
		$result_num = -1;
	}
}
if ($is_no_err > 0 && !$is_no_need_compare_sign_key) {
	$api_md5_key = $ARR_API_V2_MD5_KEY_STR[$arr_req_data['app_key']]; //$ARR_API_V2_MD5_KEY_STR assign api/config.inc
	$explode_str = $ARR_API_V2_EXPLODE_STR[$arr_req_data['app_key']]; //$ARR_API_V2_EXPLODE_STR assign api/config.inc
	$compare_str = $ARR_API_V2_PLAIN_STR[$arr_req_data['app_key']]; //$ARR_API_V2_PLAIN_STR assign api/config.inc
	$max_timesec_gap = $ARR_API_V2_MAX_TIMESEC_GAP[$arr_req_data['app_key']]; //$ARR_API_V2_MAX_TIMESEC_GAP assign api/config.inc
	//$max_timesec_gap = 0;//0이면 시간값 체크 안함
	if ($arr_req_data['sign_type'] == 'app') {
		$arr_vars = array('keyCode' => $api_md5_key, 'encryptedText' => $arr_req_data['sign_key'], 'max_timesec_gap' => $max_timesec_gap, 'explode_str' => $explode_str, 'echo_print' => $is_yes_print);
		if ($is_yes_print > 2) {
			echo "arr_vars=";
			print_r($arr_vars);
		}
		$arr_sign_key_result = decryptText($arr_vars); //decryptText assign BUYFINE/api/config.inc
		unset($arr_vars);
		if ($is_yes_print > 1) {
			echo "arr_sign_key_result=";
			print_r($arr_sign_key_result);
		}
		if ($arr_sign_key_result['result'] == 1) {
		} else {
			$is_no_err = 0;
			$result_num = -4;
		}
		unset($arr_sign_key_result);
	} else {
		$arr_vars = array('api_md5_key' => $api_md5_key, 'sign_key' => $arr_req_data['sign_key'], 'compare_str' => $compare_str, 'max_timesec_gap' => $max_timesec_gap, 'explode_str' => $explode_str, 'echo_print' => $is_yes_print);
		if ($is_yes_print > 2) {
			echo "arr_vars=";
			print_r($arr_vars);
		}
		$arr_sign_key_result = func_check_api_sign_key($arr_vars); //func_check_api_sign_key assign func_extra.inc
		unset($arr_vars);
		if ($is_yes_print > 1) {
			echo "arr_sign_key_result=";
			print_r($arr_sign_key_result);
		}
		if ($arr_sign_key_result['result'] == 1) {
		} else {
			$is_no_err = 0;
			$result_num = -4;
		}
		unset($arr_sign_key_result);
	}
}
if ($is_arr_post_var > 0) {
	$arr_post = $arr_req_data;
	unset($arr_req_data);
}
