#include <iostream>
#include <curl/curl.h>
#include <thread>
#include <future>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2){
        cout << "Error" << endl;
        return 0;
    }

    char* name = argv[1];
    CURL *curl;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, name);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_NOBODY, true);

std::promise<long> promise;
            auto resp = promise.get_future();

            std::thread req([curl, &promise]() {
              auto res = curl_easy_perform(curl);
              long check_code;


            if(res == CURLE_OK) {

              curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &check_code);
              promise.set_value(check_code);

            }
          });

            req.detach();

            auto response_code = resp.get();

            std::cout << "Response code: " << response_code << std::endl;

            curl_easy_cleanup(curl);
    }
    return 0;
}
