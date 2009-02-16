<?php
@header('Content-Type: text/html; charset=gb2312');
?>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title>开源PHP中文分词扩展：PHPCWS中文分词演示</title>
<!--css--><style type='text/css'>
body {font-family: Verdana;FONT-SIZE: 12px;MARGIN: 0;color: #000000;background: #ffffff;}
td {FONT-SIZE: 12px;}
textarea,input,select{
	font-family: Verdana;
	font-size: 12px;
	background-color: #ffffff;
}
div.quote{
margin:5px 20px;border:1px solid #000000;padding:5px;background:#e3f2fd ;line-height : normal;
}
a { TEXT-DECORATION: none;}
a:hover{ text-decoration: underline;}
img {border:0;}
.head { color: #000000;padding: 5px;}
.head a { color: #0000BB;}
.f_one {background: #eff8fe;}
.f_two {background: #e3f2fd;}
.hr  {border-top: 1px solid #b6d6f3; border-bottom: 0; border-left: 0; border-right: 0; }
.t_one {background: #e3f2fd;}
.t_two {background: #eff8fe;}
.r_one {background: #FFFFFF;}
.r_two {background: #FFFFFF;}
.cbg { color:#000000;background: #eff8fe;}
.cbg a{ color:#000000;}
.smalltxt {font-family: Tahoma, Verdana; font-size: 12px;}
.cfont { color:#000000; }
.fnamecolor { color:#003366;}
.index_font{color: #3A4F6C;background-color:#eff8fe;font-weight:bold;padding: 5px;}
.tpc_title { font-size: 12px;font-weight:bold;}
.tpc_content { font-size: 9pt;line-height: 20px;}
.i_table {BORDER: #b6d6f3 1px solid;background:#D6E3EF;}
.STYLE1 {background: #eff8fe; font-weight: bold; }
.STYLE2 {background: #e3f2fd; font-weight: bold; }
</style><!--css-->
</head>
<body vlink='#333333' link='#333333'>
<FORM ENCTYPE = "multipart/form-data" NAME = "SubmitForm"
ACTION = "" METHOD = "POST">
<table><tr><td height="5"></td></tr></table>
<table width='99%' cellspacing=1 cellpadding=3 align=center bgcolor=#b6d6f3>
    <tr>
        <td colspan=5 class=head height=25>开源PHP中文分词扩展：PHPCWS在线演示，更多内容请访问：<a href="http://code.google.com/p/phpcws" target="_blank">http://code.google.com/p/phpcws</a> (本演示程序开源，<a href="phpcws-php-demo.zip">点此下载</a>)</td>
    </tr>
    <tr>
        <td width="12%" align="right" valign=middle  class='f_two'>文字内容<BR>
        GBK编码</td>
        <td width="88%" colspan="4" class='f_one'><label>
          <textarea name="text" cols="100" rows="3" id="name"></textarea>
      </label></td>
    </tr>
    <tr>
      <td align="right" valign=middle  class='f_two'>去除标点</td>
      <td colspan="4" class='f_one'><label>
        <input name="checkbox" type="checkbox" id="checkbox" value="1">
      </label></td>
    </tr>
    <tr>
        <td align="right" valign=middle  class='f_two'>&nbsp;</td>
        <td colspan="4" class='f_one'><input type='submit' name='submit' value='          显示分词结果          '></td>
    </tr>
</table>	
<table><tr><td height="20"></td></tr></table>
<?php
$text = $_POST["text"];
$checkbox = $_POST["checkbox"];
if ($text != ""){
?>
<table width='99%' cellspacing=1 cellpadding=3 align=center bgcolor=#b6d6f3>	
    <tr>
        <td width="100%" height="25" valign=middle  class='head'>分词结果：<?=strlen($text)?>字节。（初次使用时，Apache 或 php-cgi(FastCGI) 进程，需要加载一次词库到内存中，需要0.0X秒。）</td>
    </tr>
    <tr>
        <td height="60" valign=top  class='f_one'>
		<?php
		$stime=microtime(true);
		if (strlen($text) <= 20480){
			if ($checkbox == 1){
			    echo phpcws_split($text, "default");
			} else {
                echo phpcws_split($text);
			}
		} else {
		    echo "为防止恶意攻击，文字内容大小限制在了20KB以内。";
		}
		$etime=microtime(true);
		$total=$etime-$stime;
		?>
        </td>
    </tr>
    <tr>
        <td width="100%" height="25" valign=middle  class='head'>分词耗时：<?=$total?>秒</td>
    </tr>    
</table>
<?php
}
?>
</form>
</body>
</html>
