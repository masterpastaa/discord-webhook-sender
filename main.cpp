#define CURL_STATICLIB

#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>
#include <regex>
#include <curl/curl.h>
#include <string>

using namespace std;
namespace fs = std::filesystem;

basic_string WEBHOOK = "NULL"; // you can directly set your default webhook here.

void sendWebhook(const char* content) 
{
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, WEBHOOK);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)

            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main()
{
    SetConsoleTitleA("simple webhook sender");

    /* ONLY THE OWNER OF THE SOURCE CODE CAN DEFINE THE DEFAULT WEBHOOK. */
    if (WEBHOOK._Starts_with("https://discord.com/api/webhooks/"))
    {
        string reply;
        std::cout << "Enter desired message: ";
        std::getline(cin, reply);

        string combine = "content=";
        combine += reply;
        const char* postContent = combine.c_str();

        sendWebhook(postContent);
        std::cout << "\n" << "{" << "\n" << "  " << "'content': '" << postContent << "'," << "\n" << "  " << "'api_response': 'successfully sent'," << "\n" << "  " << "'rate_limited': false" << "\n" << "   " << "Message sent." << "\n" << "}" << std::endl;

    }

    else
    {
        string user_reply;
        cout << "[-] No webhook found, please enter a valid webhook link: ";
        getline(cin, user_reply);
        if (user_reply._Starts_with("https://discord.com/api/webhooks/"))
        {
            WEBHOOK = user_reply;

            string str;
            std::cout << "Enter desired message: ";
            std::getline(cin, str);

            string combine = "content=";
            combine += str;
            const char* postContent = combine.c_str();

            sendWebhook(postContent);
            std::cout << "\n" << "{" << "\n" << "  " << "'content': '" << postContent << "'," << "\n" << "  " << "'api_response': 'successfully sent'," << "\n" << "  " << "'rate_limited': false" << "\n" << "   " << "Message sent." << "\n" << "}" << std::endl;
        }
        else
        {
            Sleep(1000);
            cout << "[-] Cannot find your webhook." << endl;
        }
    }
    Sleep(-1);    
}