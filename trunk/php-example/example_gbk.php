<?php
@header('Content-Type: text/html; charset=gb2312');
$text = "2009��2��13�գ��ұ�д��һ��PHP���ķִ���չ��PHPCWS 1.0.0��";

echo "�ִʽ��Ϊ��<BR>";
$result = phpcws_split($text);
echo $result . "<BR><BR>";

echo "���˵�Ĭ�ϱ����ŵķִʽ��Ϊ��<BR>";
$result = phpcws_split($text, "default");
echo $result . "<BR><BR>";

echo "���˵�ȫ�Ƕ�����ð�ŵķִʽ��Ϊ��<BR>";
$result = phpcws_split($text, "����");
echo $result . "<BR><BR>";
?>
