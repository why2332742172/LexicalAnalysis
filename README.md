# LexicalAnalysis
bupt-LexicalAnalysis

##任务信息

编写C语言的词法分析程序
1、可以识别出用C语言编写的源程序中的每一个单词符号、并以记号的形式输出每个单词符号 (输出形式暂定为<当前符号类型 : 符号内容>)
2、可以识别并跳过源程序中的注释 (注释类型有 // /**/ )
3、可以统计源程序中的行数(每读到一个'\n'就加一)、各类单词的个数(每种类型的单词有一个全局变量来计数)、字符总数(每从文件中读取一个字符就加一)，并输出统计结果
4、检查源程序中存在的词法错误(词法错误主要是标识符命名错误?[暂定])、并报告错误所在位置(报告行数和错误内容)
5、对源程序中出现的错误进行适当的恢复，使词法分析可以继续进行，对源程序进行一次扫描，即可检查并报告源程序中存在的所有词法错误

##设计大纲

1、源程序中的全部字符大体分为:
    关键字(C语言的关键字)keyword
    标识符(自变量)var
    常量(字符串、常数)val
    运算符(+,-,*,/,>,<,>=,<=等等全部的C语言运算符)operation
    分界符('',"",逗号,括号,[],{})demarcation
2、注释在词法分析中被忽略 最后在输出注释内容
3、预处理部分在词法分析中被忽略(以#开头的,例如#include <stdio.h>) 最后再输出
4、标识符词法规则为: 只能以字母or下划线_开头 不能以数字开头 且有字母、数字、下划线组成

##模块划分

GlobalVar.h GlobalVar.cpp 定义各种全局变量的文件
Utils.h Utils.cpp 定义各种工具函数的文件
