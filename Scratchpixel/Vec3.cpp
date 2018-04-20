//
// Created by Thierry Backes on 22/03/18.
//



/*



template<typename T>
Vec3<T> &Vec3<T>::normalize() {
    {
        T len = length();
        if (len > 0) {
            T invLen = 1 / len;
            x *= invLen, y *= invLen, z *= invLen;
        }
        return *this;
    }
}

template<typename T>
T length(const Vec3<T> &v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

template<typename T>
T dot(const Vec3<T> &a, const Vec3<T> &b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}



template<typename T>
void normalize(Vec3<T> &v)
{
    T len = v.length();
    if (len > 0) {
        T invLen = 1 / len;
        v.x *= invLen, v.y *= invLen, v.z *= invLen;
    }
}

template<typename T>
Vec3<T> cross(const Vec3<T>  &a, const Vec3<T> &b)
{
    return Vec3<T>(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
}

 */
