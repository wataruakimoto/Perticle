#pragma once

#include "Vector3.h"
#include "Matrix4x4.h"

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

// 3次元回転行列
Matrix4x4 MakeRotateMatrix(const Vector3& radian);

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);

// 座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);