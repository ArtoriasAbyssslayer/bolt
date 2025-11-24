#include "math/Matrix.hpp"

#include <cmath>

namespace bolt {
namespace math {

void Matrix33f::setRotation(const Quatf& q) {
    float yy = 2.0f * q.y * q.y;
    float zz = 2.0f * q.z * q.z;
    float xx = 2.0f * q.x * q.x;
    float xy = 2.0f * q.x * q.y;
    float xz = 2.0f * q.x * q.z;
    float yz = 2.0f * q.y * q.z;
    float wz = 2.0f * q.w * q.z;
    float wx = 2.0f * q.w * q.x;
    float wy = 2.0f * q.w * q.y;

    data[0][0] = 1.0f - yy - zz;
    data[0][1] = xy - wz;
    data[0][2] = xz + wy;

    data[1][0] = xy + wz;
    data[1][1] = 1.0f - xx - zz;
    data[1][2] = yz - wx;

    data[2][0] = xz - wy;
    data[2][1] = yz + wx;
    data[2][2] = 1.0f - xx - yy;

    data[0][3] = 0.0f;
    data[1][3] = 0.0f;
    data[2][3] = 0.0f;
}

void Matrix33f::setRotation(float r, float p, float y) {
    float cr = std::cos(r);
    float sr = std::sin(r);
    float cp = std::cos(p);
    float sp = std::sin(p);
    float cy = std::cos(y);
    float sy = std::sin(y);

    data[0][0] = cy * cp;
    data[0][1] = cy * sp * sr - sy * cr;
    data[0][2] = cy * sp * cr + sy * sr;

    data[1][0] = sy * cp;
    data[1][1] = sy * sp * sr + cy * cr;
    data[1][2] = sy * sp * cr - cy * sr;

    data[2][0] = -sp;
    data[2][1] = cp * sr;
    data[2][2] = cp * cr;
}

void Matrix33f::setRotation(const Vector3f& axis, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    float C = 1-c;
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    data[0][0] = c+x*x*C;
    data[0][1] = x*y*C - z*s;
    data[0][2] = x*z*C + y*s;

    data[1][0] = x*y*C + z*s;
    data[1][1] = c+y*y*C;
    data[1][2] = y*z*C - x*s;

    data[2][0] = x*z*C - y*s;
    data[2][1] = y*z*C + x*s;
    data[2][2] = c+z*z*C;
}

Vector3f Matrix33f::operator*(const Vector3f& other) const {
    Vector3f ret;
    ret.x = this->data[0][0] * other.x + this->data[0][1] * other.y + this->data[0][2] * other.z;
    ret.y = this->data[1][0] * other.x + this->data[1][1] * other.y + this->data[1][2] * other.z;
    ret.z = this->data[2][0] * other.x + this->data[2][1] * other.y + this->data[2][2] * other.z;
    return ret;
}

void Matrix34f::setRotation(const Quatf& q) {
    float yy = 2.0f * q.y * q.y;
    float zz = 2.0f * q.z * q.z;
    float xx = 2.0f * q.x * q.x;
    float xy = 2.0f * q.x * q.y;
    float xz = 2.0f * q.x * q.z;
    float yz = 2.0f * q.y * q.z;
    float wz = 2.0f * q.w * q.z;
    float wx = 2.0f * q.w * q.x;
    float wy = 2.0f * q.w * q.y;

    data[0][0] = 1.0f - yy - zz;
    data[0][1] = xy - wz;
    data[0][2] = xz + wy;

    data[1][0] = xy + wz;
    data[1][1] = 1.0f - xx - zz;
    data[1][2] = yz - wx;

    data[2][0] = xz - wy;
    data[2][1] = yz + wx;
    data[2][2] = 1.0f - xx - yy;

    data[0][3] = 0.0f;
    data[1][3] = 0.0f;
    data[2][3] = 0.0f;
}

void Matrix34f::setRotation(float r, float p, float y) {
    float cr = std::cos(r);
    float sr = std::sin(r);
    float cp = std::cos(p);
    float sp = std::sin(p);
    float cy = std::cos(y);
    float sy = std::sin(y);

    data[0][0] = cy * cp;
    data[0][1] = cy * sp * sr - sy * cr;
    data[0][2] = cy * sp * cr + sy * sr;

    data[1][0] = sy * cp;
    data[1][1] = sy * sp * sr + cy * cr;
    data[1][2] = sy * sp * cr - cy * sr;

    data[2][0] = -sp;
    data[2][1] = cp * sr;
    data[2][2] = cp * cr;
}

void Matrix34f::setRotation(const Vector3f& axis, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    float C = 1-c;
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    data[0][0] = c+x*x*C;
    data[0][1] = x*y*C - z*s;
    data[0][2] = x*z*C + y*s;

    data[1][0] = x*y*C + z*s;
    data[1][1] = c+y*y*C;
    data[1][2] = y*z*C - x*s;

    data[2][0] = x*z*C - y*s;
    data[2][1] = y*z*C + x*s;
    data[2][2] = c+z*z*C;
}

Vector3f Matrix34f::operator*(const Vector3f& other) const {
    Vector3f ret;
    ret.x = this->data[0][0] * other.x + this->data[0][1] * other.y + this->data[0][2] * other.z + this->data[0][3];
    ret.y = this->data[1][0] * other.x + this->data[1][1] * other.y + this->data[1][2] * other.z + this->data[1][3];
    ret.z = this->data[2][0] * other.x + this->data[2][1] * other.y + this->data[2][2] * other.z + this->data[2][3];
    return ret;
}

void Matrix44f::setRotation(const Quatf& q) {
    float yy = 2.0f * q.y * q.y;
    float zz = 2.0f * q.z * q.z;
    float xx = 2.0f * q.x * q.x;
    float xy = 2.0f * q.x * q.y;
    float xz = 2.0f * q.x * q.z;
    float yz = 2.0f * q.y * q.z;
    float wz = 2.0f * q.w * q.z;
    float wx = 2.0f * q.w * q.x;
    float wy = 2.0f * q.w * q.y;

    data[0][0] = 1.0f - yy - zz;
    data[0][1] = xy - wz;
    data[0][2] = xz + wy;

    data[1][0] = xy + wz;
    data[1][1] = 1.0f - xx - zz;
    data[1][2] = yz - wx;

    data[2][0] = xz - wy;
    data[2][1] = yz + wx;
    data[2][2] = 1.0f - xx - yy;
}

void Matrix44f::setRotation(float r, float p, float y) {
    float cr = std::cos(r);
    float sr = std::sin(r);
    float cp = std::cos(p);
    float sp = std::sin(p);
    float cy = std::cos(y);
    float sy = std::sin(y);

    data[0][0] = cy * cp;
    data[0][1] = cy * sp * sr - sy * cr;
    data[0][2] = cy * sp * cr + sy * sr;

    data[1][0] = sy * cp;
    data[1][1] = sy * sp * sr + cy * cr;
    data[1][2] = sy * sp * cr - cy * sr;

    data[2][0] = -sp;
    data[2][1] = cp * sr;
    data[2][2] = cp * cr;
}

void Matrix44f::setRotation(const Vector3f& axis, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    float C = 1-c;
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    data[0][0] = c+x*x*C;
    data[0][1] = x*y*C - z*s;
    data[0][2] = x*z*C + y*s;

    data[1][0] = x*y*C + z*s;
    data[1][1] = c+y*y*C;
    data[1][2] = y*z*C - x*s;

    data[2][0] = x*z*C - y*s;
    data[2][1] = y*z*C + x*s;
    data[2][2] = c+z*z*C;
}

void Matrix44f::setPerspective(float fovy, float aspect, float zNear, float zFar) {
    setZero();
    float tanHalfFovy = std::tan(fovy / 2);
    data[0][0] = 1 / (aspect * tanHalfFovy);
    data[1][1] = 1 / tanHalfFovy;
    data[2][2] = -(zFar + zNear) / (zFar - zNear);
    data[2][3] = -(2 * zFar * zNear) / (zFar - zNear);
    data[3][2] = -1;
}

void Matrix44f::setLookAt(const Vector3f& pos, const Vector3f& focus, const Vector3f& up) {
    Vector3f X, Y, Z;

    Z = pos - focus;
    Z.normalize();
    X = up.cross(Z);
    X.normalize();
    Y = Z.cross(X);
    Y.normalize();

    data[0][0] = X.x;
    data[1][0] = X.y;
    data[2][0] = X.z;
    data[0][1] = Y.x;
    data[1][1] = Y.y;
    data[2][1] = Y.z;
    data[0][2] = Z.x;
    data[1][2] = Z.y;
    data[2][2] = Z.z;

    data[0][3] = pos.x;
    data[1][3] = pos.y;
    data[2][3] = pos.z;

    data[3][0] = 0;
    data[3][1] = 0;
    data[3][2] = 0;
    data[3][3] = 1.0f;
}

void Matrix44f::setLookAtView(const Vector3f& pos, const Vector3f& focus, const Vector3f& up) {
    Vector3f X, Y, Z;

    Z = pos - focus;
    Z.normalize();
    X = up.cross(Z);
    X.normalize();
    Y = Z.cross(X);
    Y.normalize();

    data[0][0] = X.x;
    data[0][1] = X.y;
    data[0][2] = X.z;
    data[1][0] = Y.x;
    data[1][1] = Y.y;
    data[1][2] = Y.z;
    data[2][0] = Z.x;
    data[2][1] = Z.y;
    data[2][2] = Z.z;

    data[0][3] = -pos.dot(X);
    data[1][3] = -pos.dot(Y);
    data[2][3] = -pos.dot(Z);

    data[3][0] = 0;
    data[3][1] = 0;
    data[3][2] = 0;
    data[3][3] = 1.0f;
}

Matrix44f Matrix44f::operator*(const Matrix44f& other) const {
    Matrix44f ret;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ret.data[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                ret.data[i][j] += this->data[i][k] * other.data[k][j];
            }
        }
    }
    return ret;
}

Vector4f Matrix44f::operator*(const Vector4f& other) const {
    Vector4f ret;
    for (int i = 0; i < 4; i++) {
        ret.data[i] = 0;
        for (int j = 0; j < 4; j++) {
            ret.data[i] += this->data[i][j] * other.data[j];
        }
    }
    return ret;
}

Matrix44f Matrix44f::rigidInverse() const {
    Matrix44f ret;
    ret.makeHomogeneous();
    Matrix33f rot = getRotation();
    Matrix33f rotT = rot.transpose();
    ret.setRotation(rotT);
    ret.setTranslation(-(rotT * getTranslation()));
    return ret;
}

const Matrix44f Matrix44f::IDENTITY = {{
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
}};

} // math
} // bolt
