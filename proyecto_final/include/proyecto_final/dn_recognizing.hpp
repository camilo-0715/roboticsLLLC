#ifndef PROYECTO_FINAL__DN_RECOGNIZING_HPP__
#define PROYECTO_FINAL__DN_RECOGNIZING_HPP__

#include "ros/ros.h"
#include <iostream>
#include <map>

namespace proyecto_final
{
    class Recognizer
    {
        public:
            Recognizer(std::string item);
            // method to check if a determinated item exists. returns bool   
        private:
            // node handler, subscriber to darknet topic...
    };
}

#endif // PROYECTO_FINAL__DN_RECOGNIZING_HPP__ 
