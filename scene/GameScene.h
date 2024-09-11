#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "memory"
#include "Perticle.h"
#include "Emitter.h"
#include "DebugCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// パーティクル発生
	/// </summary>
	void PerticlePop(const Vector3& position_);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;
	// ワールド変換
	WorldTransform worldTransform_;

	// パーティクル(リスト)
	std::list<std::unique_ptr<Perticle>> perticles_;
	// パーティクル用モデルデータ
	std::unique_ptr<Model> modelperticle_;

	Vector3 position = {0.0f, 0.0f, 0.0f};

	// デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	// デバッグカメラのフラグ
	bool isDebugCameraActive_ = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
