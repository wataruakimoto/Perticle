#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "memory"
#include "Star.h"
#include "Perticle.h"
#include "Emitter.h"
#include "Stage.h"
#include "Skydome.h"
#include "Mark.h"
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
	void PerticlePop(const Vector3& position_, const std::unique_ptr<Model>& model, const int& perticleNum);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;
	// ワールド変換
	WorldTransform worldTransform_;

	// スター
	std::unique_ptr<Star> star_;
	// スター用モデルデータ
	std::unique_ptr<Model> modelStar_;
	// スターの初期位置
	Vector3 starPosition_ = {0.0f, 16.0f, 20.0f};

	// パーティクル(リスト)
	std::list<std::unique_ptr<Perticle>> perticles_;
	// パーティクル用モデルデータ
	std::unique_ptr<Model> modelPerticle_;
	// エミッターの初期位置
	Vector3 emitterPosition_ = {0.0f, 16.0f, 0.0f};

	// ステージ
	std::unique_ptr<Stage> stage_;
	// ステージ用モデル
	std::unique_ptr<Model> modelStage_;
	// ステージの初期位置
	Vector3 stagePosition_ = {0.0f, 0.0f, 0.0f};

	// 天球
	std::unique_ptr<Skydome> skydome_;
	// 天球用モデル
	std::unique_ptr<Model> modelSkydome_;
	// 天球の初期位置
	Vector3 skydomePosition_ = {0.0f, 0.0f, 0.0f};

	// マーク
	std::unique_ptr<Mark> mark_;
	// マーク用モデル
	std::unique_ptr<Model> modelMark_;
	// マークの初期位置
	Vector3 markPosition_ = {0.0f, 16.0f, 0.0f};

	// デバッグカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	// デバッグカメラのフラグ
	bool isDebugCameraActive_ = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
