#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"

#pragma once
/// <summary>
/// パーティクル
/// </summary>
class Perticle {
private: // メンバ変数
	// ワールド変換
	WorldTransform worldTransform_;
	// モデルデータ
	Model* model_;

	// アルファ値
	float alpha_ = 1.0f;

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
};