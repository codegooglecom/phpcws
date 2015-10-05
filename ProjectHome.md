# 注：最新的分词系统 HTTPCWS 已经发布，用来取代 PHPCWS。 #

# 请点击以下网址下载 HTTPCWS： #
# http://code.google.com/p/httpcws #

# 原来的 PHPCWS 停止更新。 #


---


## Introduction in English ##

> PHPCWS is a open-source PHP Extension for Chinese Word Segmentation, using ICTCLAS Chinese word segmentation algorithms and Reverse maximal matching algorithms.

> ICTCLAS is a Chinese lexical analysis system, which is able to make Chinese word segmentation, Part-Of-Speech tagging, word sense disambiguation and named entity recognition. The detailed linguistic information provided by ICTCLAS increases the accuracy and depth of any application related to Chinese language, such as machine translation, retrieval, filtering, text mining and many others.

## 发布版本： ##
**PHPCWS 1.0.1** （最新版本：2009-07-06发布）

> 安装使用手册：http://blog.s135.com/phpcws_v100/

> 下载地址（PHP扩展）：http://phpcws.googlecode.com/files/phpcws-1.0.1.tar.gz

> 下载地址（词库）：http://phpcws.googlecode.com/files/phpcws-dict-1.0.0.tar.gz

> 中文分词在线演示：http://blog.s135.com/demo/phpcws/

> PHP实例程序下载：http://blog.s135.com/demo/phpcws/phpcws-php-demo.zip

**PHPCWS 1.0.0** （历史版本）


---


## PHPCWS 中文简介 ##
#### 1、什么是 PHPCWS ？ ####
> PHPCWS 是一款开源的PHP中文分词扩展，目前仅支持Linux/Unix系统。

> PHPCWS 先使用“ICTCLAS 3.0 共享版中文分词算法”的API进行初次分词处理，再使用自行编写的“逆向最大匹配算法”对分词和进行词语合并处理，并增加标点符号过滤功能，得出分词结果。

> [ICTCLAS](http://ictclas.org/sub_1_2.html)（Institute of Computing Technology, Chinese Lexical Analysis System）是中国科学院计算技术研究所在多年研究工作积累的基础上，基于多层隐马模型研制出的汉语词法分析系统，主要功能包括中文分词；词性标注；命名实体识别；新词识别；同时支持用户词典。ICTCLAS经过五年精心打造，内核升级6次，目前已经升级到了ICTCLAS3.0，分词精度98.45%，各种词典数据压缩后不到3M。ICTCLAS在国内973专家组组织的评测中活动获得了第一名，在第一届国际中文处理研究机构SigHan组织的评测中都获得了多项第一名，是当前世界上最好的汉语词法分析器。

> ICTCLAS 3.0 商业版是收费的，而免费提供的 ICTCLAS 3.0 共享版不开源，词库是根据人民日报一个月的语料得出的，很多词语不存在。所以本人对ICTCLAS分词后的结果，再采用逆向最大匹配算法，根据自己补充的一个9万条词语的自定义词库（与ICTCLAS词库中的词语不重复），对ICTCLAS分词结果进行合并处理，输出最终分词结果。

> 由于 ICTCLAS 3.0 共享版只支持GBK编码，因此，如果是UTF-8编码的字符串，可以先用PHP的iconv函数转换成GBK编码，再用phpcws\_split函数进行分词处理，最后转换回UTF-8编码。

#### 2、PHPCWS 中文分词在线演示 ####
> 演示网址：http://blog.s135.com/demo/phpcws/

#### 3、PHPCWS 分词速度及用途 ####

> 初次使用时，Apache 或 php-cgi(FastCGI) 进程，需要加载一次词库到内存中，需要0.0X秒。58字节的一句话——“2009年2月13日，我编写了一款PHP中文分词扩展：PHPCWS 1.0.0。”，分词速度只需为0.0003秒。

> PHPCWS 属于《[亿级数据的高并发通用搜索引擎架构设计](http://blog.s135.com/post/385.htm)》的一部分，用作“搜索查询接口”的关键字分词处理。在此架构中，Sphinx索引引擎对于CJK（中日韩）语言支持一元切分，假设【反恐行动是国产主视角射击网络游戏】这段文字，Sphinx会将其切成【反 恐 行 动 是 国 产 主 视 角 射 击 网 络 游 戏】，然后对每个字建立反向索引。如果用这句话中包含的字组成一个不存在的词语，例如【恐动】，也会被搜索到，所以搜索时，需要加引号，例如搜索【"反恐行动"】，就能完全匹配连在一起的四个字，不连续的【"恐动"】就不会被搜索到。但是，这样还有一个问题，搜索【"反恐行动游戏"】或【"国产网络游戏"】就会搜索不到。所以，我在搜索层写了个PHP中文分词扩展，搜索“反恐行动游戏”、“国产网络游戏”，会被PHPCWS中文分词函数分别切分为“反恐行动 游戏”、“国产 网络游戏”，这时候，用PHP函数给以空格分隔的词语加上引号，去搜索【"反恐行动" "游戏"】或【"国产" "网络游戏"】，就能搜索到这条记录了。由于PHPCWS位于搜索层，中文分词词库发生增、删、改，只需平滑重启一次Web服务器或php-cgi进程即可，无需重建搜索索引。

> 根据上述情况，对于那些采用二元交叉切分的搜索引擎，PHPCWS用在前端搜索层对用户输入的搜索关键字、短语进行分词处理，同样适合。PHPCWS开发的目的正在于此，对于短句、小文本中文分词切分，速度非常之快。

#### 4、自定义词库 ####
> 自定义词库名称为[userdict.tch](http://code.google.com/p/phpcws/source/browse/trunk/phpcws-dict/userdict.tch)，格式为 Tokyo Cabinet DBM 的 Abstract key-value 内存哈希数据库（key为GBK编码的词语名词，value为词频。目前词频均填1，暂时用不上）。
