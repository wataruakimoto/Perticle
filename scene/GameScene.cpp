#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクション初期化
	viewProjection_.Initialize();
	// ワールド変換初期化
	worldTransform_.Initialize();

	// パーティクルモデル
	modelperticle_.reset(Model::CreateFromOBJ("perticle", false));
	// パーティクルを発生させる
	PerticlePop();
}

void GameScene::Update() {

	// パーティクル更新
	for (std::unique_ptr<Perticle>& perticle : perticles_) {
		perticle->Update();
	}

	// ビュープロジェクション更新
	viewProjection_.UpdateMatrix();
	// ワールド変換更新
	worldTransform_.UpdateMatrix();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// パーティクル描画
	for (std::unique_ptr<Perticle>& perticle : perticles_) {
		perticle->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::PerticlePop() {

	for (int i = 0; i < 12; i++) {
		// パーティクル生成
		std::unique_ptr<Perticle> newPerticle = std::make_unique<Perticle>();
		// パーティクル初期化
		newPerticle->Initialize(modelperticle_.get(), { 20.0f,20.0f,20.0f });
		// パーティクルを登録する
		perticles_.push_back(std::move(newPerticle));
	}
}
