#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"

#pragma once
/// <summary>
/// パーティクル
/// </summary>
class Perticle {
public:
	struct Emitter {
		Vector3 position;
		Vector3 min;
		Vector3 max;
	};

private: // メンバ変数
	// ワールド変換
	WorldTransform worldTransform_;
	// モデルデータ
	Model* model_;

	// アルファ値
	float alpha_ = 1.0f;

	Emitter emitter_{
		{0.0f, 0.0f, 0.0f},
		{-10.0f, -10.0f, -10.0f},
		{10.0f, 10.0f, 10.0f},
	};

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデルデータ</param>
	void Initialize(Model* model, Vector3 position);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(ViewProjection& viewProjection);
	/// <summary>
	/// 徐々に消える
	/// </summary>
	void FadeOut();
	/// <summary>
	/// エミッターのどこに出るか
	/// </summary>
	/// <returns></returns>
	Vector3 Pop(const Vector3& min, const Vector3& max);
	/// <summary>
	/// 動き
	/// </summary>
	void Move();
};