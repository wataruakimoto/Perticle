#include "Model.h"
#include "WorldTransform.h"

#pragma once
/// <summary>
/// 天球
/// </summary>
class Skydome {
private: // メンバ変数
	// ワールド変換
	WorldTransform worldTransform_;
	// モデルデータ
	Model* model_;

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
};