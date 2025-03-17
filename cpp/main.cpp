/*
    C++ mqtt data feeder - by Benjamin Uzunovic
*/
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "json.hpp"
#include "mosquitto.h"

using json = nlohmann::json;

void cleanMqttResources(mosquitto *client){
    mosquitto_disconnect(client);
    mosquitto_destroy(client);
    mosquitto_lib_cleanup();
}

int main(){
    mosquitto_lib_init(); //Library initialization
    mosquitto *client = mosquitto_new("Client", true, nullptr); //Creating a client
    //Here you can change the hostname from "localhost" into something like "broker.hivemq.com"...
    int ret = mosquitto_connect(client, "localhost", 1883, 60);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error connecting to the broker: " << mosquitto_strerror(ret) << std::endl;
        cleanMqttResources(client);
        return -1;
    }
    std::cout << "Connected to MQTT broker!" << std::endl;
    //Source file
    std::string fileName = "./data/HAM_2020R_Italy.json"; //After changing the source file name, you have to compile the program again!
    std::ifstream jsonFile(fileName);
    if(!jsonFile){
        std::cerr << "Error: Could not open " << fileName << "!" << std::endl;
        cleanMqttResources(client);
        return -1;
    }
    std::cout << "File " << fileName << " is open!"<< std::endl;

    json jsonData;
    jsonFile >> jsonData; //How to parse everything using 2 symbols...
    
    int period = 50; //Frequency period in milliseconds (20Hz = 50ms)
    for(const auto &x : jsonData){
        std::string str = x.dump();
        // You can change topic by changing "FS/data" into something else
        mosquitto_publish(client, nullptr, "FS/data", str.length(), str.c_str(), 0, false); 
        std::this_thread::sleep_for(std::chrono::milliseconds(period));
    }

    cleanMqttResources(client);
    return 0;
}