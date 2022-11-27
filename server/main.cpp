#include <iostream>
#include <fstream>
#include <json/json.h>

#include "server.hpp"

using namespace std;

int main()
{
    // Load JSON config file
    Json::Value json;
    ifstream ifs;
    ifs.open("config.json");

    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;

    if (!Json::parseFromStream(builder, ifs, &json, &errs))
    {
        cout << errs << endl;
        return EXIT_FAILURE;
    }

    server::server{json};

    return 0;
}
