#ifndef HTTP_H
#define HTTP_H

#endif // HTTP_H

namespace
{
    std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            char* out)
    {
        std::string data(in, (std::size_t) size * num);
        *((std::stringstream*) out) << data;
        return size * num;
    }
}

Json::Value simpleCurl(string apiUrl, string queryStr) {
    //return commandToString("curl -s "+apiUrl+queryStr);
    string url=apiUrl+queryStr;
    Json::Value root;
    Json::CharReaderBuilder jsonReader;
    std::string errs;
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    long httpCode(0);
    std::stringstream json;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    try {
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &json);
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);
    } catch (...) {
        PLOGE << "simpleCurl exception! httpCode:"+to_string(httpCode)+" - URL: " << url;
    }

    if (httpCode == 200) {
        if (Json::parseFromStream(jsonReader, json, &root, &errs)) {
            return root;
        } else {
            PLOGE << "simpleCurl ERROR! Could not parse HTTP data as JSON";
            return 1;
        }
    } else {
        PLOGE << "simpleCurl ERROR! HTTP "+to_string(httpCode)+" - URL: " << url;
        return 1;
    }

}
