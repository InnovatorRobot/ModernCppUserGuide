#ifndef RAPIDJSON_HPP
#define RAPIDJSON_HPP
#include <iostream>
#include <fstream> // to open/read the file
#include <sstream>
#include <exception>
#include <memory>
#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>

class JsonParser
{
public:
    explicit JsonParser(const std::string& filename) : filename_{filename} {}

    rapidjson::Document getJsonDocument()
    {
        // open the JSON file
        std::ifstream jFile(filename_);
        if (!jFile.is_open())
        {
            throw std::invalid_argument("Error");
        }

        std::stringstream content;
        content << jFile.rdbuf();
        rapidjson::Document document;
        document.Parse(content.str().c_str());
        return document;
    }

private:
    std::string filename_;
};

#endif // RAPIDJSON_HPP
