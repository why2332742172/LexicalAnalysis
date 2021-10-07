//
// Created by Strawberry on 2021/10/6.
//

//第一遍分析 读入源程序 一行一行的读入 然后存入缓冲区 然后分析这一行

#include "Utils.h"
void analyse_first(){
    cout << "Starting Analyse First" << endl;
    int current_line = 1; //当前所在行数
    char temp_char; //暂存从文件读取的字符
    string temp_string; //连接字符串

    //逐行读取 碰到'\n' 结束一行的读取
    target_file.seekg(0); //让文件指针回到文件头部
    if(!target_file.eof()){
        line_num++;
    }
    while(target_file.peek() != EOF){
        //一直循环读取文件
        target_file.get(temp_char);
        if(temp_char != '\n' && temp_char != ' ' && temp_char != '\t'){
            char_num++;
        }
        temp_string += temp_char;
        if('\n' == temp_char){
            //如果读到了换行符 代表已经读取了一行

            //首先先给总行数加一
            line_num++;

            //然后将此行放入map中 并当前行号加一
            buffers[current_line] = temp_string;
            //cout << "line:" << current_line << "-->:" << buffers[current_line] << endl;

            //然后清空当前temp_string
            temp_string = "";

            //然后更新当前行号
            current_line++;
        }
        if(target_file.peek() == EOF){
            //最后一行的文字没有换行符 给他加上结束符 '\0'
            temp_string += '\0';
            buffers[current_line] = temp_string;
            //cout << "line:" << current_line << "-->:" << buffers[current_line] << endl;
        }
    }

}
