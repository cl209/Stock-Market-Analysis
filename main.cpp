// Include necessary headers
#include <iostream>
#include <string>
#include "curl/curl.h"
#include "json.hpp"
using namespace std;

//Renaming the nlohmann namespace to json
using json = nlohmann::json;

//Used to process data by chunks
size_t WriteCallback(void* data, size_t byte, size_t length, void* storeDataPtr) {
    //Size of line, byte * length of line 
    size_t totalSize = byte * length;
    //Treat data as strings
    string* str = static_cast<string*>(storeDataPtr);
    //Append data as char by char
    str->append(static_cast<char*>(data), totalSize);
    
    return totalSize;
}

int main() {
    //API key
    const string apiKey = "4UU7A7KYJGKYT726";
    //Stock symbol
    const string symbol = "NVDA"; 

    //Alpha Vantage API URL
    string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY"
                "&symbol=" + symbol + "&apikey=" + apiKey + "&datatype=json";

    
    CURL* curl = curl_easy_init(); //Initialized curl object as curl
    CURLcode result; //CURLcode object to store result
    string dataString; //Data string to store data

    if (curl) {
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());//Set URL to what curl can read
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);//Call WriteCallback function after every chunk of data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &dataString);//Store data in dataString
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);//Verify the peer

        //Perform the request and store the result
        result = curl_easy_perform(curl);
        
        //If result is not CURLE_OK, print error message and cleanup
        if (result != CURLE_OK) {
            cerr << "CURL error: " << curl_easy_strerror(result) << endl;
            curl_easy_cleanup(curl);
            return 1;
        }

        //Cleanup curl
        curl_easy_cleanup(curl);
    } else {
        cerr << "Failed to initialize CURL." << endl;
        return 1;
    }

   
    try {
        //JsonData = parsed dataString
        auto jsonData = json::parse(dataString);

        //If jsonData contains "Error Message", print error message and return 1
        if (jsonData.contains("Error Message")) {
            cerr << "API Error: " << jsonData["Error Message"] << endl;
            return 1;
        }

        //TimeSeries = Time Series (Daily) data) in jsonData
        auto timeSeries = jsonData["Time Series (Daily)"];

        for (auto& [date, values] : timeSeries.items()){
            
            //Format date
            string year = date.substr(0, 4);
            string month = date.substr(5, 2);
            string day = date.substr(8, 2);
            string formattedDate = month + "/" + day + "/" + year;

            //Get values as strings and convert to double
            double openPrice = stod(values["1. open"].get<string>());
            double highPrice = stod(values["2. high"].get<string>());
            double lowPrice = stod(values["3. low"].get<string>());
            double closePrice = stod(values["4. close"].get<string>());

            //Format volume
            string volume = values["5. volume"];
            int volLength = volume.length();
            for (int i = volLength - 3; i > 0; i -= 3) {
                volume.insert(i, ",");
            }
            
            //Print data
            cout << "Ticker: " << symbol << endl;
            cout << "Date: " << formattedDate << endl;
            cout << "Open: $" << openPrice << endl;
            cout << "High: $" << highPrice << endl;
            cout << "Low: $" << lowPrice << endl;
            cout << "Close: $" << closePrice << endl;
            cout << "Volume: " << volume << endl;
            cout << "-------------------------" << endl;
        }
    //Error handling
    } catch (json::parse_error& e) {
        cerr << "JSON parse error: " << e.what() << endl;
        return 1;
    } catch (json::type_error& e) {
        cerr << "JSON type error: " << e.what() << endl;
        return 1;
    } catch (std::exception& e) {
        cerr << "Standard exception: " << e.what() << endl;
        return 1;
    }

    return 0;
}
