<?php
@header('Content-Type: text/html; charset=gb2312');
$text = "2009年2月13日，我编写了一款PHP中文分词扩展：PHPCWS 1.0.0。";

echo "分词结果为：<BR>";
$result = phpcws_split($text);
echo $result . "<BR><BR>";

echo "过滤掉默认标点符号的分词结果为：<BR>";
$result = phpcws_split($text, "default");
echo $result . "<BR><BR>";

echo "过滤掉全角逗号与冒号的分词结果为：<BR>";
$result = phpcws_split($text, "，：");
echo $result . "<BR><BR>";
?>
