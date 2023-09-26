#ifndef __JSON_BUILDER_H__
#define __JSON_BUILDER_H__

#include "Data.hpp"

class JsonBuilder
{
    public:
        void addStringToObject(int parentId, std::string key, std::string value);
        void addIntegerToObject(int parentId, std::string key, int value);
        int addContainerToObject(int parentId, std::string key, std::string type);

        Data* addObjectToObject(int parentId, std::string key);
        Data* addArrayToObject(int parentId, std::string key);        

        void addStringToArray(int parentId, std::string value);
        void addIntegerToArray(int parentId, int value);
        int addContainerToArray(int parentId, std::string type);

        Data* addObjectToArray(int parentId);
        Data* addArrayToArray(int parentId);
        
        void print(int id);
        
    private:
        void check_parentId_object(int parentId);
        void check_parentId_array(int parentId);
        void check_type(std::string type);
        void check_key(int parentId, std::string key);

        bool check_if_empty(int id);
        void print_inside(int id);

        data_2D datas_info  {{0}};
        std::string jasonFormat;
};

#endif
