/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 18:13:13
 * @Last Modified by: Nihil Eon
 * @Last Modified time: 2019-05-01 18:37:21
 */
#include "user.h"
User* User::_instance = nullptr; /// 创建用户单实例

User& User::instance(){
    if(_instance == nullptr){
        _instance = new User();
    }
    return *_instance;
}

void User::destroy(){
    if(_instance != nullptr){
        delete _instance;
    }
    return;
}
