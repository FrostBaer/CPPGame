#include "resource.h"

void Resource::setCurrent(int _current) {
        if (_current > max){
            current = max;
            //throw "Current > max! Current set to max.";
        }
        else if(_current < 0){
            current = 0;
            //throw "Current < 0! Current set to 0.";
        }
        else
            current = _current;
    }
