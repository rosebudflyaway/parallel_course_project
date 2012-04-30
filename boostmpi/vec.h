#ifndef _VEC_H
#define _VEC_H

class Vec
{
    public:
        Vec(int a,int b)
        {
            x = a;
            y = b;
        }
        Vec(){};
        int get_x()
        {
            return x;
        }
    private:
        friend class boost::serialization::access;
        template<class Archive>
            void serialize(Archive & ar, const unsigned int version)
            {
                ar & x;
                ar & y;
            }
        int x;
        int y;
};
#endif
