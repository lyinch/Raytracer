//
// Created by Thierry Backes on 19/04/18.
//

#ifndef SCRATCHPIXEL_VEC2_H
#define SCRATCHPIXEL_VEC2_H
template<typename T>
class Vec2 {
public:
    Vec2():x{},y{} {}
    explicit Vec2(const T &val): x(val),y(val){}
    Vec2(T xx, T yy): x(xx), y(yy){}
    T x, y;

};
typedef Vec2<float> Vec2f;

#endif //SCRATCHPIXEL_VEC2_H
