#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED


class Resource{
    int max;
    int current;

public:
    Resource(int _max = 0, int _current = 0): max( _max), current( _current){}
    int getMax(){ return max; }
    int getCurrent() { return current; }
    void setMax(int _max) { max = _max; }
    void setCurrent(int _current);
};

#endif // RESOURCES_H_INCLUDED
