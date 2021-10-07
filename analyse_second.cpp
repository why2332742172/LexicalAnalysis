//
// Created by Strawberry on 2021/10/6.
//

//分析2 即逐行分析 buffers里面已经存了读取的一行的代码 现在则逐个字符的去分析 辨别出每一种字符并输出、统计等

//特殊情况分析
/*
 * 1、读取的第一个字符是 # 则代表是预处理 则将该行语句加入到 pretreatments 中 代表预处理语句 <行号 , 预处理语句>
 * 2、当读取到字符 / 时 则得往后再读取一个 判断其是: a、运算符除号 b、单行注释号// c、多行注释号/*
 *
 */
#include "Utils.h"

enum Type {
    keyword, operation, demarcation, comment, var, val, pretreatment, error
};

int begin_comment2 = 0;
int end_comment2 = 0;

//存储全部分割开的字符串(按照空格、换行符、结束符分割的;按照前后不同种类字符分割的;)
vector<string> split_strings;

//存储第二次分割的字符串 完全分割版
vector<string> split_strings_second;

bool is_pre(int line, string content) {

    //首先去除前空格
    content.erase(0, content.find_first_not_of(' '));
    content.erase(0, content.find_first_not_of('\t'));

    if (content[0] == '#') {
        pretreatments[line] = content;
        return true;
    } else {
        return false;
    }
}

bool is_comment1(int line, string content) {

    //首先去除前空格
    content.erase(0, content.find_first_not_of(' '));
    content.erase(0, content.find_first_not_of('\t'));

    if (content[0] == '/' && content[1] == '/') {
        //该行以 // 开头
        comments[line] = content;
        return true;
    } else if (content[0] == '/' && content[1] == '*' && content.find("*/") != string::npos) {
        //该行以/*开头且包含*/ 也算作单行注释
        comments[line] = content;
        return true;
    } else {
        return false;
    }
}

bool is_comment2(int line, string content) {

    //首先去除前空格
    content.erase(0, content.find_first_not_of(' '));
    content.erase(0, content.find_first_not_of('\t'));

    begin_comment2 = line;

    if (content[0] == '/' && content[1] == '*') {
        //该行以 /* 开头
        //则从该行开始一直往下读 知道读取到某一行含有 */ 表示多行注释结束
        for (int i = line + 1; i < buffers.size(); i++) {
            if (buffers[i].find("*/") != string::npos) {
                //如果找到了 则表示该行是注释结束
                end_comment2 = i;
                return true;
            }
        }
    } else {
        return false;
    }
}

bool is_val(string str) {
    if(str[0] == ' ' || str[0] == '\n' || str[0] == '\t'){
        return false;
    }
    if (str[0] == '"' && str[str.length() - 1] == '"') {
        return true;
    }
    for (char ch: str) {
        if (isdigit(ch) == 0) {
            //有一个字符不是数字 则不是常数字
            return false;
        }
    }
    return true;
}

bool is_right_var(string str) {
    //首先去掉行首的空格
    str.erase(0, str.find_first_not_of(' '));
    str.erase(0, str.find_first_not_of('\t'));

    if (isdigit(str[0]) != 0) {
        //如果第一个字符就是数字 不符合规则
        return false;
    }
    if (isalpha(str[0]) == 0 && str[0] != '_') {
        //如果第一个字符不是字母 且也不是下划线_ 不符合规则
        return false;
    }
    return true;
}

Type judgeType(string toBeJudgeStr) {

    if (toBeJudgeStr != " " && toBeJudgeStr != "\n" && toBeJudgeStr != "\t") {
        //首先判断是否是 关键字
        if (find(keywords.begin(), keywords.end(), toBeJudgeStr) != keywords.end()) {
            finded_keywords.emplace_back(toBeJudgeStr);
            cout << "<KEYWORD ~ " << toBeJudgeStr << " >" << endl;
            keyword_num++;
            return keyword;
        }
            //然后判断是否是 运算符
        else if (find(operations.begin(), operations.end(), toBeJudgeStr) != operations.end()) {
            finded_operations.emplace_back(toBeJudgeStr);
            cout << "<OPERATION ~ " << toBeJudgeStr << " >" << endl;
            op_num++;
            return operation;
        }
            //然后判断是否是 分界符
        else if (find(demarcations.begin(), demarcations.end(), toBeJudgeStr) != demarcations.end()) {
            finded_demarcations.emplace_back(toBeJudgeStr);
            cout << "<DEMARCATION ~ " << toBeJudgeStr << " >" << endl;
            de_num++;
            return demarcation;
        }
            //然后判断是否是 常量(纯数字和双引号括起来的字符串)
        else if (is_val(toBeJudgeStr)) {
            vals.emplace_back(toBeJudgeStr);
            cout << "<VAL ~ " << toBeJudgeStr << " >" << endl;
            val_num++;
            return val;
        }
            //如果都不是 则是标识符(自变量)了 首先判断其是否符合构词规则(只能以字母or下划线_开头 不能以数字开头 且有字母、数字、下划线组成)
        else if (!is_right_var(toBeJudgeStr)) {
            //不符合构词规则
            cout << "<ERROR ~ " << toBeJudgeStr << " >" << endl;
            return error;
        }
            //是标识符且符合构词规则
        else {
            vars.emplace_back(toBeJudgeStr);
            cout << "<VAR ~ " << toBeJudgeStr << " >" << endl;
            var_num++;
            return var;
        }
    }
    return error;
}

void second_separate(){
    //第二次处理 处理
    //遍历第一次分割开的字符串vector
    //对每一个字符串进行分析
    bool multiple_comments = false;

    for(string str : split_strings){
        bool flag = false;
        bool forward_flag = false;
        int forward_index = 0;
        bool after_flag = false;
        int after_index = 0;
        int begin_index = 0;
        int end_index = 0;
        //cout << "str: " << str << endl;
        if(multiple_comments){
            //当前处于多行注释阶段
            cout << "str:" << str << endl;
            comments_in_line_mul.push_back(str);
            if(str.find_first_of("*/") < str.length()){
                //找到了结束符号
                multiple_comments = false;
            }
        }else{
            for (int i = 0; i < str.length(); i++) {

                char ch = str[i];
                string ch_str = string(1,ch);
                if(ch_str != "\n" && ch_str != "\t" && ch_str != " "){
//                    if(ch == '/' && str[i+1] == '*'){
//                        cout << "-->" << str[str.length() - 3] << endl;
//                        cout << "-->" << str[str.length() - 2] << endl;
//                    }
                    //处理语句中的注释
                    // 单行注释
                    if(ch == '/' && str[i+1] == '/'){

                        string comment_in_line = str.substr(i,str.length());
                        //cout << "COMMENT:" << comment_in_line << endl;
                        comments_in_line.push_back(comment_in_line);
                        break;
                    }
                    //单行注释 /**/类型
                    else if(ch == '/' && str[i+1] == '*' && str[str.length() - 3] == '*' && str[str.length() - 2] ==  '/'){
                        string comment_in_line = str.substr(i,str.length());
                        comments_in_line.push_back(comment_in_line);
                        break;
                    }
                        //多行注释
//                    else if(ch == '/' && str[i+1] == '*'){
//                        //一直往下走找到 */为止 把多行注释加入到 comments_in_line
//                        string comment_in_line1 = str.substr(i,str.length());
//                        cout << "comment_in_line1:" << comment_in_line1 << endl;
//                        comments_in_line_mul.push_back(comment_in_line1);
//                        multiple_comments = true;
//                        break;
//                    }

                    //如果当前字符是 " 则说明是字符串常量 则一直往后读直到找到下一个 " 为止
                    if(!forward_flag && ch_str == "\""){
                        forward_flag = true;
                        forward_index = i;
                    }else if(forward_flag && !after_flag && ch_str == "\""){
                        after_flag = true;
                        after_index = i;
                    }
                    if(forward_flag && after_flag){
                        flag = true;
                        after_flag = false;
                        forward_flag = false;
                        string val_string = "\"" + str.substr(forward_index + 1,(after_index - forward_index - 1)) + "\"" ;

                        split_strings_second.push_back(val_string);
                        begin_index = after_index;
                    }

                    if(!forward_flag && ch_str != "\""){
                        //如果当前的字符是分界符or运算符 则说明与前面的不同 需要分隔开
                        if(find(operations.begin(),operations.end(),ch_str) != operations.end()){
                            flag = true;

                            end_index = i;
                            if(end_index != begin_index && end_index != 0){
                                if(find(operations.begin(),operations.end(),string(1,str[i-1])) == operations.end()){
                                    string split_string = str.substr(begin_index , (end_index - begin_index));
                                    split_strings_second.push_back(split_string);
                                    //cout << "split_string1: " << split_string << endl;
                                }
                            }
                            begin_index = end_index + 1;
                            split_strings_second.push_back(ch_str);
                        }

                        if(find(demarcations.begin(),demarcations.end(),ch_str) != demarcations.end()){
                            flag = true;
                            //cout << begin_index << ":" << end_index << endl;
                            end_index = i;
                            //end_index - begin_index > 1
                            if(end_index != begin_index && end_index != 0){
                                if(find(demarcations.begin(),demarcations.end(),string(1,str[i-1])) == demarcations.end()){
                                    //cout << begin_index << ":" << end_index << endl;
                                    string split_string = str.substr(begin_index , (end_index - begin_index));
                                    split_strings_second.push_back(split_string);
                                    //cout << "split_string2: " << split_string << endl;

                                }
                            }

                            begin_index = end_index + 1;
                            split_strings_second.push_back(ch_str);
                        }
                    }


                }
            }
            if(!flag){
                //cout << "!flag" << endl;
                split_strings_second.push_back(str);
            }
        }

    }

}

void analyse_second() {
    auto it = buffers.begin();
    auto it_end = buffers.end();

    while (it != it_end) {

        //遍历每一行的内容
        int line = it->first;
        string content = it->second;

        //cout << line << ":" << content;
        //首先进行预处理检查 检查该行语句是否是预处理语句(以 # 开头)
        if (is_pre(line, content)) {
            cout << "line " << line << " doing pretreatment: " << content << endl;
            pretreatments[line] = content;
        }
            //然后进行整行单行注释检查 检查该语句是否以 // 开头 如果是则不用处理 节约时间
        else if (is_comment1(line, content)) {
            comments[line] = content;
            cout << "line " << line << " is single line comment: " << content << endl;
        }
            //然后检查是否是多行注释 即以 /* 开头 如果是则也加入注释中 不做处理 节约时间
        else if (is_comment2(line, content)) {

            cout << "from line " << line << " to line " << end_comment2 << " is multiple line comment" << endl;
            for(int i = line;i <= end_comment2;i++){
                comments_mul[i] = buffers[i];
            }
        }
            //如果当前行数大于多行注释的末尾行or小于多行注释的起始行 则说明不是多行注释 再加上前面的特殊情况都不是 则进入正常分析
        else if (line > end_comment2 || line < begin_comment2) {
//            cout << line << ":" << content;
//            if (content.find('\n') == string::npos) {
//                cout << "\n";
//            }
//            cout << "normal\n" << endl;

            //line 是当前待分析的一行
            //直接从左往右依次按顺序进行分析

            //首先去掉行首的空格 直到第一个不是空格的字符为止
            content.erase(0, content.find_first_not_of(' '));
            content.erase(0, content.find_first_not_of('\t'));

            if(content != "\n" && content != " " && content != "\t"){
                int forward_index = 0;
                int after_index = 0;

                int nums = count(content.begin(), content.end(), '"');
                if ( nums != 0 && nums % 2 == 0) {

                    //如果双引号数量为偶数 则说明该行包含字符串 则直接加入到split_strings 下一步再进行分析
                    //去掉换行符

                    split_strings.push_back(content);

                }
                //对于每一行的内容 逐个字符的分析
                for (int i = 0; i < content.length(); i++) {
                    if (nums == 0 || nums % 2 != 0) {
                        //如果双引号的数量是奇数or0 则说明该行不包含包含字符串
                        //对于情况 int num = 0 类型的 有空格隔开的一行代码
                        if ((content[i] == ' ' || content[i] == '\n' || content[i] == '\0') && content[0] != '\0') {
                            //找到了空格or换行符or行尾结束符 说明前面的从 forward_index 到 after_index 前一个都是一个独立的字符串
                            after_index = i;
                            int sub_length = after_index - forward_index;
                            string split_str = content.substr(forward_index, sub_length);

                            split_strings.push_back(split_str);
                            forward_index = after_index + 1;
                        }
                    }
                }
            }


        }
        it++;
    }
//    cout << "---------------------" << endl;
//    for (string strssss: split_strings) {
//        cout << strssss << endl;
//        //judgeType(strssss);
//    }
//    cout << "---------------------" << endl;

    //经过大致分了一次之后 再分第二次 此次是判断前一个字符和后一个字符的种类是否相同 如果不同则说明他们是两个东西
    second_separate();
//    cout << "````````````````````````````===============````````````````````````````" << endl;
//    for (string strssss2: split_strings_second) {
//        cout << strssss2 << endl;
//        //judgeType(strssss2);
//    }
//    cout << "````````````````````````````===============````````````````````````````" << endl;
    cout << "===============" << endl;
    for (string strssss2: split_strings_second) {
        //cout << strssss2 << endl;
        judgeType(strssss2);
    }
    cout << "================" << endl;


}

