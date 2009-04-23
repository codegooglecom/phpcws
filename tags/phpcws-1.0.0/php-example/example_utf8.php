<?php
@header('Content-Type: text/html; charset=utf-8');
$text = "2009年2月13日，我编写了一款PHP中文分词扩展：PHPCWS 1.0.0。";
$text = iconv("UTF-8", "GBK//IGNORE", $text);

echo "分词结果为：<BR>";
$result = phpcws_split($text);
$result = iconv("GBK", "UTF-8//IGNORE", $result);
echo $result . "<BR><BR>";

echo "过滤掉默认标点符号的分词结果为：<BR>";
$result = phpcws_split($text, "default");
$result = iconv("GBK", "UTF-8//IGNORE", $result);
echo $result . "<BR><BR>";

echo "过滤掉全角逗号与冒号的分词结果为：<BR>";
$result = phpcws_split($text, "，：");
$result = iconv("GBK", "UTF-8//IGNORE", $result);
echo $result . "<BR><BR>";
?>
