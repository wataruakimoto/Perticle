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

	// 飛んでいく向き
	Vector3 speed_;

	Vector3 min_ = {-0.1f, -0.1f, -0.1f};
	Vector3 max_ = {0.1f, 0.1f, 0.1f};

	// 削除フラグ
	bool isDead_ = false;

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
	/// 動き
	/// </summary>
	void Move();
	/// <summary>
	/// 死亡フラグのゲッター
	/// </summary>
	/// <returns></returns>
	bool GetIsDead() { return isDead_; }
	/// <summary>
	/// 飛んでいく向きを設定する
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns></returns>
	Vector3 SetDirection(const Vector3& min, const Vector3& max);
};