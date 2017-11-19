#ifndef COEFICIENT_H
#define COEFICIENT_H


class coeficient
{
public:
    coeficient();

    void setTime(unsigned int);

    unsigned int getTime() const {
        return time;
    }

private:
    unsigned int time;
};

#endif // COEFICIENT_H
