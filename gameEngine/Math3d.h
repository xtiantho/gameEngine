

#ifndef __GameEngine__Math3d__
#define __GameEngine__Math3d__

#include <stdio.h>
#include <math.h>
#define MATH_PI 3.1415926535897932384626433832795
#define ToRadians(x) (float)(((x) * MATH_PI / 180.0f))
#define ToDegrees(x) (float)(((x) * 180.0f / MATH_PI))

template <typename T, unsigned int D>
class Vector
{
public:
    Vector () {}
    
    T& operator [] (unsigned int i) { return m_values[i]; }
    T operator [] (unsigned int i) const { return m_values[i]; }
    
    inline T dot(const Vector<T,D>& r) const
    {
        T result = T(0);
        unsigned int i = 0;
        for(i = 0; i < D; i++)
        {
            result += (*this)[i] * r[i];
        }
        return result;
    }
    
    //Length function
    inline T lengthSq() const { return this->dot(*this); }
    
    inline T length() const { return sqrt(lengthSq()); }
    
    inline Vector<T,D> normalized() const { return (*this) / length(); }
    
    inline Vector<T,D> operator / (const T& r) const
    {
        Vector<T,D> result;
        for(int i = 0; i < D; i++)
        {
            result[i] = (*this)[i] / r;
        }
        return result;
    }
    
    inline Vector<T,D> operator + (const Vector<T,D>& r) const
    {
        Vector<T,D> result;
        for(int i = 0; i < D; i++)
        {
            result[i] = (*this)[i] + r[i];
        }
        return result;
    }
    
    inline Vector<T,D> operator - (const Vector<T,D>& r) const
    {
        Vector<T,D> result;
        for(int i = 0; i < D; i++)
        {
            result[i] = (*this)[i] - r[i];
        }
        return result;
    }
    
    inline Vector<T,D> operator * (const T& r) const
    {
        Vector<T,D> result;
        for(int i = 0; i < D; i++)
        {
            result[i] = (*this)[i] * r;
        }
        return result;
    }
    
    inline Vector<T, D>& operator+=(const Vector<T,D>& r)
    {
        for(unsigned int i = 0; i < D; i++)
            (*this)[i] = m_values[i] + r[i];
        
        return *this;
    }
    
    inline Vector<T, D>& operator-=(const Vector<T,D>& r)
    {
        for(unsigned int i = 0; i < D; i++)
            (*this)[i] = m_values[i] - r[i];
        
        return *this;
    }
    
    inline Vector<T, D>& operator*=(const T& r)
    {
        for(unsigned int i = 0; i < D; i++)
            (*this)[i] = m_values[i] * r;
        
        return *this;
    }
    
    inline Vector<T, D>& operator/=(const T& r)
    {
        for(unsigned int i = 0; i < D; i++)
            (*this)[i] = m_values[i] / r;
        
        return *this;
    }
    
    inline bool operator == (const Vector<T,D>& r) const
    {
        for(int i = 0; i < D; i++)
        {
            if((*this)[i] != r[i])
                return false;
        }
        return true;
    }

    
private:
    T m_values[D];
};

template <typename T>
class Vector2 : public Vector <T, 2>
{
public:
    Vector2 () {}
    
    Vector2 (const Vector<T, 2>& r) //const to prevent unnecessary changes to r
    {
        (*this)[0] = r[0];
        (*this)[1] = r[1];
    }
    
    Vector2 (T x, T y)
    {
        (*this)[0] = x;
        (*this)[1] = y;
    }
    
    //cross product
    
    inline Vector2<T> rotate(float angle)
    {
        float rad = ToRadians(angle);
        float c = cos(rad);
        float s = sin(rad);
        
        return Vector2<T>((*this)[0] * c - (*this)[1] * s, (*this)[0] * s + (*this)[1] * c);
    }
    
    inline T getX() { return (*this)[0]; } //cannot access m_value since it's a private member of the parent
    inline T getY() { return (*this)[1]; }
    
    inline void setX(T x) { (*this)[0] = x; }
    inline void setY(T y) { (*this)[1] = y; }
};

class Quaternion;

template <typename T>
class Vector3 : public Vector <T, 3>
{
public:
    Vector3 () {}
    
    Vector3 (const Vector<T, 3>& r) //const to prevent unnecessary changes to r
    {
        (*this)[0] = r[0];
        (*this)[1] = r[1];
        (*this)[2] = r[2];
    }
    
    Vector3 (T x, T y, T z)
    {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
    }
    
    //cross product
    inline Vector3<T> cross(Vector3<T>& r) const
    {
        float x_ = (*this)[1] * r[2] - (*this)[2] * r[1];
        float y_ = (*this)[2] * r[0] - (*this)[0] * r[2];
        float z_ = (*this)[0] * r[1] - (*this)[1] * r[0];
        
        return Vector3<T>(x_, y_, z_);
    }
    
    inline Vector3<T> rotate(float angle)
    {
        
    }
    
    inline Vector3<T> rotate(const float& angle, const Vector3<T>& axis)
    {
        /*float sinHalfAngle = (float) sin(ToRadians(angle / 2));
        float cosHalfAngle = (float) cos(ToRadians(angle / 2));
        
        float rx = axis.getX() * sinHalfAngle;
        float ry = axis.getY() * sinHalfAngle;
        float rz = axis.getZ() * sinHalfAngle;
        float rw = 1.0f * cosHalfAngle;
        
        Quaternion rotation(rx, ry, rz, rw);*/
        
        const float sin = sinf(-ToRadians(angle));
        const float cos = cosf(-ToRadians(angle));
        
        Vector3<T> v = axis * sin;
        //Vector3<T> v1 = this->cross(v);
        
        return this->cross(v) +        //Rotation on local X
        (*this * cos) +                     //Rotation on local Z
        axis * this->dot(axis * (1 - cos)); //Rotation on local Y
    }
    
    inline T getX() const { return (*this)[0]; } //cannot access m_value since it's a private member of the parent
    inline T getY() const { return (*this)[1]; }
    inline T getZ() const { return (*this)[2]; }
    
    inline void setX(const T& x) { (*this)[0] = x; }
    inline void setY(const T& y) { (*this)[1] = y; }
    inline void setZ(const T& z) { (*this)[2] = z; }
};

template <typename T>
class Vector4 : public Vector<T, 4>
{
public:
    Vector4() { }
    
    Vector4(const Vector<T, 4>& r)
    {
        (*this)[0] = r[0];
        (*this)[1] = r[1];
        (*this)[2] = r[2];
        (*this)[3] = r[3];
    }
    
    Vector4(T x, T y, T z, T w)
    {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
        (*this)[3] = w;
    }
    
    inline T getX() const { return (*this)[0]; }
    inline T getY() const { return (*this)[1]; }
    inline T getZ() const { return (*this)[2]; }
    inline T getW() const { return (*this)[3]; }
    
    inline void setX(const T& x) { (*this)[0] = x; }
    inline void setY(const T& y) { (*this)[1] = y; }
    inline void setZ(const T& z) { (*this)[2] = z; }
    inline void setW(const T& w) { (*this)[3] = w; }
    
    inline void set(const T& x, const T& y, const T& z, const T& w) { setX(x); setY(y); setZ(z); setW(w); }
protected:
private:
};

template <typename T, unsigned int D>
class Matrix
{
public:
    
    inline Matrix<T,D> initIdentity()
    {
        for(int i = 0; i < D; i++)
        {
            for(int j = 0; j < D; j++)
            {
                if (i == j)
                    M[i][j] = T(1);
                else
                    M[i][j] = T(0);
            }
        }
        return *this;
    }
    
    inline Matrix<T,D> Transpose() const
    {
        Matrix<T,D> result;
        for(int i = 0; i < D; i++)
            for(int j = 0; j < D; j++)
                result[i][j] = M[j][i];
        return result;
    }
    
    inline Matrix<T,D> operator*(Matrix<T,D>& r) const
    {
        Matrix<T,D> result;
        
        for(int i = 0; i < D; i++)
        {
            for(int j = 0; j < D; j++)
            {
                result.M[i][j] = T(0);
                for(int k = 0; k < D; k++)
                {
                    result.M[i][j] += M[k][j] * r.M[i][k];
                }
            }
        }
        
        return result;
    }
    
    //inline const T* operator[](int index) { return M[index]; }
    
    inline void set(unsigned int x, unsigned int y, T val) { M[x][y] = val; }

    inline const T* operator[](int index) const { return M[index]; }
    inline T* operator[]  (int index) { return M[index]; }
    
private:
    T M[D][D];
};

typedef Vector2<float> vec2f;
typedef Vector3<float> vec3f;

template <typename T>
class Matrix4 : public Matrix<T, 4>
{
public:
    
    Matrix4() {}
    
    template<unsigned int D>
    Matrix4(const Matrix<T, D>& r)
    {
        if(D < 4)
        {
            this->initIdentity();
            
            for(unsigned int i = 0; i < D; i++)
                for(unsigned int j = 0; j < D; j++)
                    (*this)[i][j] = r[i][j];
        }
        else
        {
            for(unsigned int i = 0; i < 4; i++)
                for(unsigned int j = 0; j < 4; j++)
                    (*this)[i][j] = r[i][j];
        }
    }
    
    inline Matrix4<T> initTranslation(T x, T y, T z)
    {
        (*this)[0][0] = T(1); (*this)[1][0] = T(0); (*this)[2][0] = T(0); (*this)[3][0] = x;
        (*this)[0][1] = T(0); (*this)[1][1] = T(1); (*this)[2][1] = T(0); (*this)[3][1] = y;
        (*this)[0][2] = T(0); (*this)[1][2] = T(0); (*this)[2][2] = T(1); (*this)[3][2] = z;
        (*this)[0][3] = T(0); (*this)[1][3] = T(0); (*this)[2][3] = T(0); (*this)[3][3] = T(1);
        
        return *this;
    }
    
    inline Matrix4<T> initScale(T x, T y, T z)
    {
        (*this)[0][0] = x; (*this)[1][0] = T(0); (*this)[2][0] = T(0); (*this)[3][0] = T(0);
        (*this)[0][1] = T(0); (*this)[1][1] = y; (*this)[2][1] = T(0); (*this)[3][1] = T(0);
        (*this)[0][2] = T(0); (*this)[1][2] = T(0); (*this)[2][2] = z; (*this)[3][2] = T(0);
        (*this)[0][3] = T(0); (*this)[1][3] = T(0); (*this)[2][3] = T(0); (*this)[3][3] = T(1);
        
        return *this;
    }
    
    inline Matrix4<T> initRotationEuler(T x, T y, T z)
    {
        Matrix4<T> rx;
        Matrix4<T> ry;
        Matrix4<T> rz;
        
        Matrix4<T> r;
        
        x = (T) ToRadians(x);
        y = (T) ToRadians(y);
        z = (T) ToRadians(z);
        
        rx[0][0] = T(1);   rx[1][0] = T(0)  ;  rx[2][0] = T(0)   ; rx[3][0] = T(0);
        rx[0][1] = T(0);   rx[1][1] = cos(x);  rx[2][1] = -sin(x); rx[3][1] = T(0);
        rx[0][2] = T(0);   rx[1][2] = sin(x);  rx[2][2] = cos(x) ; rx[3][2] = T(0);
        rx[0][3] = T(0);   rx[1][3] = T(0)  ;  rx[2][3] = T(0)   ; rx[3][3] = T(1);
        
        ry[0][0] = cos(y); ry[1][0] = T(0);    ry[2][0] = -sin(y); ry[3][0] = T(0);
        ry[0][1] = T(0)  ; ry[1][1] = T(1);    ry[2][1] = T(0)   ; ry[3][1] = T(0);
        ry[0][2] = sin(y); ry[1][2] = T(0);    ry[2][2] = cos(y) ; ry[3][2] = T(0);
        ry[0][3] = T(0)  ; ry[1][3] = T(0);    ry[2][3] = T(0)   ; ry[3][3] = T(1);
        
        rz[0][0] = cos(z); rz[1][0] = -sin(z); rz[2][0] = T(0);    rz[3][0] = T(0);
        rz[0][1] = sin(z); rz[1][1] = cos(z) ; rz[2][1] = T(0);    rz[3][1] = T(0);
        rz[0][2] = T(0)  ; rz[1][2] = T(0)   ; rz[2][2] = T(1);    rz[3][2] = T(0);
        rz[0][3] = T(0)  ; rz[1][3] = T(0)   ; rz[2][3] = T(0);    rz[3][3] = T(1);
        
        *this = rz * ry * rx;
        //r = rz * ry * rx;
        
        return *this;
    }
    
    inline Matrix4<T> initProjection(const T& fov, const T& width, const T& height, const T& zNear, const T& zFar)
    {
        T tanHalfFOV = tanf(ToRadians(fov / T(2)));
        T ar = width / height;
        T zRange = zNear - zFar;
        
        
        (*this)[0][0] = T(1)/(tanHalfFOV*ar);(*this)[1][0] = T(0); (*this)[2][0] = T(0); (*this)[3][0] = T(0);
        (*this)[0][1] = T(0); (*this)[1][1] = T(1) / tanHalfFOV; (*this)[2][1] = T(0); (*this)[3][1] = T(0);
        (*this)[0][2] = T(0); (*this)[1][2] = T(0); (*this)[2][2] = (-zNear - zFar)/zRange; (*this)[3][2] = (T(2) * zFar * zNear) / zRange;
        (*this)[0][3] = T(0); (*this)[1][3] = T(0); (*this)[2][3] = T(1); (*this)[3][3] = T(0);
        
        return *this;
    }
    
    inline Matrix4<T> initCamera(const vec3f& forward, const vec3f& up)
    {
        vec3f f = forward;
        f = f.normalized();
        
        vec3f r = up;
        r = r.normalized();
        
        r = r.cross(f);
        
        vec3f u = f.cross(r);
        
        (*this)[0][0] = r.getX();   (*this)[1][0] = r.getY();   (*this)[2][0] = r.getZ();   (*this)[3][0] = T(0);
        (*this)[0][1] = u.getX();   (*this)[1][1] = u.getY();   (*this)[2][1] = u.getZ();   (*this)[3][1] = T(0);
        (*this)[0][2] = f.getX();   (*this)[1][2] = f.getY();   (*this)[2][2] = f.getZ();   (*this)[3][2] = T(0);
        (*this)[0][3] = T(0);       (*this)[1][3] = T(0);       (*this)[2][3] = T(0);       (*this)[3][3] = T(1);
        
        return *this;
    }
    
private:
};


typedef Matrix4<float> Matrix4f;

class Quaternion : public Vector4<float>
{
public:
    Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f)
    {
        (*this)[0] = x;
        (*this)[1] = y;
        (*this)[2] = z;
        (*this)[3] = w;
    }
    
    Quaternion(const Vector4<float>& r)
    {
        (*this)[0] = r.getX();
        (*this)[1] = r.getY();
        (*this)[2] = r.getZ();
        (*this)[3] = r.getW();
    }
    
    inline Quaternion conjugate() const
    {
        return Quaternion(-getX(), -getY(), -getZ(), getW());
    }
    
    inline Quaternion operator*(const Quaternion& r) const
    {
        const float w_ = getW() * r.getW() - getX() * r.getX() - getY() * r.getY() - getZ() * r.getZ();
        const float x_ = getX() * r.getW() + getW() * r.getX() + getY() * r.getZ() - getZ() * r.getY();
        const float y_ = getY() * r.getW() + getW() * r.getY() + getZ() * r.getX() - getX() * r.getZ();
        const float z_ = getZ() * r.getW() + getW() * r.getZ() + getX() * r.getY() - getY() * r.getX();
        
        return Quaternion(x_, y_, z_, w_);
    }
    
    inline Quaternion operator*(const Vector3<float>& v) const
    {
        const float _w = - (getX() * v.getX()) - (getY() * v.getY()) - (getZ() * v.getZ());
        const float _x =   (getW() * v.getX()) + (getY() * v.getZ()) - (getZ() * v.getY());
        const float _y =   (getW() * v.getY()) + (getZ() * v.getX()) - (getX() * v.getZ());
        const float _z =   (getW() * v.getZ()) + (getX() * v.getY()) - (getY() * v.getX());
        
        return Quaternion(_x, _y, _z, _w);
    }
    
private:
};


#endif
