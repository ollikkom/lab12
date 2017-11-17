#include <iostream>
#include <curl/curl.h>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2){
        cout << "Error" << endl;
        return 0;
    }

    char* name = argv[1];
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, name);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_NOBODY, true);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK){
            cout << "ERROR: " << curl_easy_strerror(res) << endl;
        }
        else {
            char *url = NULL;
            curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
            if(url){
                cout << "Redirect to: " << url << endl;
            }

            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            cout << "Response code: " << response_code << endl;
        }

        curl_easy_cleanup(curl);
    }
    return 0;
}
