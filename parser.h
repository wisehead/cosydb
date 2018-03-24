/*******************************************************************************
 * Copyright 2018 no Inc. All Rights Reserved.
 * Author: Hui Chen (alex.chenhui@gmail.com)
 *
 * File Name: parser.h                                               
 * Header file.
 * Created Time: 2018/03/22-15:39                                    
 *******************************************************************************/
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <map>

using std::string;
using std::cout;
using std::endl;

namespace cosydb {
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName(const TypeName&); \
        TypeName& operator=(const TypeName&)

// Base type of data type.
// defines a virtual function parse. each succeeder needs to implements it.
class BaseType {
public:
    virtual ~BaseType(){}
    virtual int parse(string str) {
        printf("in parse() of BaseType.\n");
        return 0;
    }
};

// helper class for built-in data type int. we define this class, so that we have the same 
// parse interface as other user defined types, which is easy to manage.
class BuiltinInt:public BaseType {
public:
    BuiltinInt():_value(0){}
    virtual ~BuiltinInt(){}
    virtual int parse(string str);
private:
    int _value;
    DISALLOW_COPY_AND_ASSIGN(BuiltinInt);
};

// helper class for built-in data type float.
class BuiltinFloat:public BaseType {
public:
    BuiltinFloat():_value(0){}
    virtual ~BuiltinFloat(){}
    virtual int parse(string str);
private:
    float _value;
    DISALLOW_COPY_AND_ASSIGN(BuiltinFloat);
};

// helper class for built-in data type char*.
class BuiltinCharString:public BaseType {
public:
    BuiltinCharString():_value(0){}  
    virtual ~BuiltinCharString(){
        if (_value != NULL){
            delete [] _value;
            _value = NULL;
        }
    }
    virtual int parse(string str);
private:
    char* _value;
    DISALLOW_COPY_AND_ASSIGN(BuiltinCharString);
};

/*
   Base Class of User Defined Type, 

   if you want to add a new User Defined Type, you need to
   1.inherit from UserDefinedType;
   2.implement interface parse();
   3.add a member of the new Type to class Handler, and add 
     it to _handler_map in constuctor function;
*/
class UserDefinedType: public BaseType {
public:
    virtual ~UserDefinedType(){}
    virtual int parse(string str) {
        printf("in parse() of UserDefinedType.\n");
        return 0;
    }
};

// this user defined type just has one member, this is a simple sample.
class UdtBool:public UserDefinedType {
public:
    UdtBool():_value(false){}
    virtual ~UdtBool(){}
    virtual int parse(string str);
private:
    bool _value;
    DISALLOW_COPY_AND_ASSIGN(UdtBool); 
};

// this user defined type has 4 members, which is a complex sample.
class UdtUser:public UserDefinedType {
public:
    UdtUser():_userId(0),_name(NULL),_age(0),_money(0) {}
    virtual ~UdtUser() {
        if (_name != NULL) {
            delete [] _name;
            _name = NULL;
        }
    }
    virtual int parse(string str);
private:
    int _userId;
    char* _name;
    int _age;
    float _money;
    DISALLOW_COPY_AND_ASSIGN(UdtUser);
};

typedef std::map<string, BaseType*> MAP_STRING_BASETYPE; 

// Handler class is a tool class, which manages the all types of handlers.
// if user defines a new type, he/she needs to register here. so that it can be recognized
// and parsed.
class Handler {
public:
    static Handler * get_instance() {
        if(_p_instance==NULL)
            _p_instance=new Handler();
        return _p_instance;
    }

    bool is_this_type_supported(string type);
    BaseType* get_handler(string type);
private:
    Handler():_handler_map(),
              _handler_builtin_int(),
              _handler_builtin_float(),
              _handler_builtin_char_string(),
              _handler_udt_bool(),
              _handler_udt_user()
    {
        _handler_map.clear();
        _handler_map["int"]=&_handler_builtin_int;
        _handler_map["float"]=&_handler_builtin_float;
        _handler_map["char*"]=&_handler_builtin_char_string;
        _handler_map["UdtBool"]=&_handler_udt_bool;
        _handler_map["UdtUser"]=&_handler_udt_user;
    }
    static Handler * _p_instance;
    
    class Garbo {
        public:
            ~Garbo() {
                if (Handler::_p_instance) {
                    delete Handler::_p_instance;
                }
            }
    };
    static Garbo gb;

    MAP_STRING_BASETYPE _handler_map; 
    BuiltinInt _handler_builtin_int;
    BuiltinFloat _handler_builtin_float;
    BuiltinCharString _handler_builtin_char_string;
    UdtBool _handler_udt_bool;
    UdtUser _handler_udt_user;
};
Handler * Handler::_p_instance=NULL;

// the definition of the table.
// it stores all the data types of each columns. and provide data type checking functionality.
class TableDef {
public:
    TableDef():columns() {}
    ~TableDef() {}

    int init();
    int get_col_count();
    string get_type(int i);
    int check_and_get_array_def(string arr_str, string* ele_type, int* ele_count);
private:
    std::vector<string> columns; 
    DISALLOW_COPY_AND_ASSIGN(TableDef);
};

// the main worker class, implementing the main parsing algorithms.
class Parser {
public:
    Parser():_table_def() {}
    ~Parser() {}
    TableDef& get_table_def();
    int parse_line(string line);
    int parse_array(string def, string column);
    int parse_low(string line, char tab, int col_count, string type=string(""));
private:
    TableDef _table_def;
    DISALLOW_COPY_AND_ASSIGN(Parser);
};

}//namespace cosydb 
