//
// Created by Strawberry on 2021/10/6.
//

//init模块 完成全局变量的初始化
#include "Utils.h"

void keywords_init(){
    keywords.emplace_back("printf");
    keywords.emplace_back("auto");
    keywords.emplace_back("short");
    keywords.emplace_back("int");
    keywords.emplace_back("long");
    keywords.emplace_back("float");
    keywords.emplace_back("double");
    keywords.emplace_back("char");
    keywords.emplace_back("struct");
    keywords.emplace_back("union");
    keywords.emplace_back("enum");
    keywords.emplace_back("typedef");
    keywords.emplace_back("const");
    keywords.emplace_back("unsigned");
    keywords.emplace_back("signed");
    keywords.emplace_back("extern");
    keywords.emplace_back("register");
    keywords.emplace_back("static");
    keywords.emplace_back("volatile");
    keywords.emplace_back("void");
    keywords.emplace_back("if");
    keywords.emplace_back("else");
    keywords.emplace_back("switch");
    keywords.emplace_back("case");
    keywords.emplace_back("for");
    keywords.emplace_back("do");
    keywords.emplace_back("while");
    keywords.emplace_back("goto");
    keywords.emplace_back("continue");
    keywords.emplace_back("break");
    keywords.emplace_back("default");
    keywords.emplace_back("sizeof");
    keywords.emplace_back("return");
}

void operations_init(){
    operations.emplace_back("+");
    operations.emplace_back("-");
    operations.emplace_back("*");
    operations.emplace_back("/");
    operations.emplace_back("%");
    operations.emplace_back("=");
    operations.emplace_back("++");
    operations.emplace_back("--");
    operations.emplace_back("==");
    operations.emplace_back("!=");
    operations.emplace_back(">");
    operations.emplace_back("<");
    operations.emplace_back(">=");
    operations.emplace_back("<=");
    operations.emplace_back("&&");
    operations.emplace_back("&");
    operations.emplace_back("||");
    operations.emplace_back("|");
    operations.emplace_back("!");
}

void demarcations_init(){
    demarcations.emplace_back("(");
    demarcations.emplace_back(")");
    demarcations.emplace_back("[");
    demarcations.emplace_back("]");
    demarcations.emplace_back("{");
    demarcations.emplace_back("}");
    demarcations.emplace_back("'");
    demarcations.emplace_back("\"");
    demarcations.emplace_back(",");
    demarcations.emplace_back(";");
}

void init(){

    keywords_init();
    cout << "Loading Keywords:" << endl;
    for(string str : keywords){
        cout << str << endl;
    }

    operations_init();
    cout << "\nLoading operations:" << endl;
    for(string str2 : operations){
        cout << str2 << endl;
    }
    demarcations_init();
    cout << "\nLoading demarcations:" << endl;
    for(string str3 : demarcations){
        cout << str3 << endl;
    }
}


