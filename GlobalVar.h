//
// Created by Strawberry on 2021/10/6.
//

#ifndef LEXICALANALYSIS_GLOBALVAR_H
#define LEXICALANALYSIS_GLOBALVAR_H

#endif //LEXICALANALYSIS_GLOBALVAR_H



#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <cctype>
#include <map>
#include <algorithm>
using namespace std;

extern ifstream target_file; //将要打开并进行词法分析的目标.c文件

extern map<int , string> buffers;//读入缓冲区 每次读一行就存到这个里面 <行号 , 该行内容>

extern vector<string> keywords; //预先记录关键字
extern vector<string> operations; //预先记录全部的运算符
extern vector<string> demarcations; //预先记录全部的分界符

extern map<int , string> comments; //存储分析得到的全部的注释内容(单行)
extern map<int , string> comments_mul; //存储分析得到的全部的注释内容(多行)
extern vector<string> comments_in_line; //存储在分析过程中 跟代码放在一起的 预处理未处理到的注释(单行)
extern vector<string> comments_in_line_mul; //存储在分析过程中 跟代码放在一起的 预处理未处理到的注释(多行)
extern vector<string> vars; //存储分析得到的全部的标识符(自变量)
extern vector<string> vals; //存储分析得到的全部的常量
extern map<int , string> pretreatments; //存储分析得到得全部预处理语句
extern vector<string> finded_operations; //存储分析得到的全部运算符
extern vector<string> finded_keywords; //存储分析得到的全部关键字
extern vector<string> finded_demarcations; //存储分析得到的全部分界符

extern int line_num; //源程序总行数
extern int keyword_num; //源程序中关键字的数目
extern int var_num; //源程序中标识符(自变量)的数目
extern int val_num; //源程序中常量(字符串、常数)的数目
extern int op_num; //源程序中运算符(+,-,*,/,>,<,>=,<=)的数目
extern int de_num; //源程序中分界符的数目
extern int char_num;