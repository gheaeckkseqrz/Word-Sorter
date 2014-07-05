


// regex_match example
#include <iostream>
#include <string>
#include <regex>
#include <curl/curl.h>


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

std::string             getWiki()
{
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl = curl_easy_init();
  if(curl)
    {
      curl_easy_setopt(curl, CURLOPT_URL, "http://en.m.wikipedia.org/wiki/Special:Random");
      /* example.com is redirected, so we tell libcurl to follow redirection */ 
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
 
      /* Perform the request, res will get the return code */ 
      res = curl_easy_perform(curl);
      /* Check for errors */ 
      if(res != CURLE_OK)
      {
          fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
          return std::string("");
      }
        
      /* always cleanup */ 
      curl_easy_cleanup(curl);
    }

  std::regex text ("<p>.*</p>");
  std::cmatch sm;    // same as std::match_results<const char*> cm;
  std::regex_search(readBuffer.c_str(), sm, text);

    std::string result;
  for (auto p : sm)
    {
      std::string sp = p;
      std::regex balise ("(<.*?>)");  
      result += " " + std::regex_replace (sp, balise, "");
    }

  return result;
}
