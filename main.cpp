#include <iostream>
#include "Utils.h"
/*
 * 程序的主体流程
 * 首先读入.c文件
 * 然后一行一行的存入缓冲区
 * 每存一行就分析一次，输出相应的信息，对各类单词数、字符总数、语句行数进行统计累加
 *
 */
int main() {
    target_file.open("test.c");
    if(!target_file){
        cout << "ERROR: can't find target file!" << endl;
        return 0;
    }else{
        cout << "Loading target file: test.c" << endl;
    }

    //初始化各种全局变量
    init();

    //首先读取文件然后将每行与其对应的内容都放到buffers这个map里面
    analyse_first();


    //然后对整个程序进行分析 每行与其对应的内容都存在了buffers里面
    cout << "\nStarting analyse row by row:\n" << endl;
    analyse_second();

    //然后输出统计信息
    cout << "-----" << endl;
    cout << "char_num: " << char_num << endl;
    cout << "-----" << endl;
    cout << "The total line num of the target file is:" << line_num << endl;
    cout << "-----" << endl;
    cout << "The keywords num:" << keyword_num << endl;
    cout << "-----" << endl;
    cout << "The op_num:" << op_num << endl;
    cout << "-----" << endl;
    cout << "The de_num:" << de_num << endl;
    cout << "-----" << endl;
    cout << "The val_num:" << val_num << endl;
    cout << "-----" << endl;
    cout << "The var_num:" << var_num << endl;
    cout << "-----" << endl;
    cout << "The pretreatment is:" << endl;
    for (auto it = pretreatments.begin(); it != pretreatments.end(); ++it)
    {
        cout << "line" << it->first << "->" << it->second << endl;
    }
    cout << "-----" << endl;
    cout << "Single line of comment during pretreatment is:" << endl;
    for (auto it = comments.begin(); it != comments.end(); ++it)
    {
        cout << "line" << it->first << "->" << it->second << endl;
    }
    cout << "-----" << endl;
    cout << "Multiple line of comment during pretreatment is:" << endl;
    for (auto it = comments_mul.begin(); it != comments_mul.end(); ++it)
    {
        cout << "line" << it->first << "->" << it->second << endl;
    }
    cout << "-----" << endl;
    cout << "Single line of comment during second analyse is:" << endl;
    for(string s : comments_in_line){
        cout << s << endl;
    }
    cout << "-----" << endl;
//    cout << "Multiple line of comment during second analyse is:" << endl;
//    for(string s : comments_in_line_mul){
//        cout << s << endl;
//    }
//    cout << "-----" << endl;

    return 0;
}
