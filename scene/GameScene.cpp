#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <imgui.h>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection_.translation_ = {0.0f, 19.0f, -30.0f};

	// ビュープロジェクション初期化
	viewProjection_.Initialize();
	// ワールド変換初期化
	worldTransform_.Initialize();

	// スターモデル
	modelStar_.reset(Model::CreateFromOBJ("MyResources/star1", false));
	// スター生成
	star_ = std::make_unique<Star>();
	// スター初期化
	star_->Initialize(modelStar_.get(), starPosition_);

	// パーティクルモデル
	modelPerticle_.reset(Model::CreateFromOBJ("MyResources/piece1", false));

	// ステージモデル
	modelStage_.reset(Model::CreateFromOBJ("MyResources/mars", true));
	// ステージ生成
	stage_ = std::make_unique<Stage>();
	// ステージ初期化
	stage_->Initialize(modelStage_.get(), stagePosition_);

	// 天球モデル
	modelSkydome_.reset(Model::CreateFromOBJ("MyResources/skydome", true));
	// 天球生成
	skydome_ = std::make_unique<Skydome>();
	// 天球初期化
	skydome_->Initialize(modelSkydome_.get(), skydomePosition_);

	// マークモデル
	modelMark_.reset(Model::CreateFromOBJ("MyResources/mark", false));
	// マーク生成
	mark_ = std::make_unique<Mark>();
	// マーク初期化
	mark_->Initialize(modelMark_.get(), markPosition_);

	// デバッグカメラの生成と初期化
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);
}

void GameScene::Update() {

	// スター更新
	star_->Update();

	// キー入力によってエミッターの位置を更新
	if (input_->PushKey(DIK_UP)) {
		emitterPosition_.y += 0.1f; // 上に移動
	}
	if (input_->PushKey(DIK_DOWN)) {
		emitterPosition_.y += -0.1f; // 下に移動
	}

	if (input_->TriggerKey(DIK_SPACE)) {
		// パーティクルを発生させる
		PerticlePop(emitterPosition_, modelPerticle_, 24);
	}

	// パーティクル更新
	//for (std::unique_ptr<Perticle>& perticle : perticles_) {
	//	perticle->Update();
	//}
	for (auto it = perticles_.begin(); it != perticles_.end();) {
		(*it)->Update(); // パーティクルを更新

		// パーティクルが死んでいたらリストから削除
		if ((*it)->GetIsDead()) {
			it = perticles_.erase(it); // 削除し、イテレータを更新
		} else {
			++it; // 削除しない場合は次のパーティクルへ
		}
	}

	// ステージ更新
	stage_->Update();

	// 天球更新
	skydome_->Update();

	// マーク更新
	mark_->Update();

	// ビュープロジェクション更新
	viewProjection_.UpdateMatrix();
	// ワールド変換更新
	worldTransform_.UpdateMatrix();

	// ビュープロジェクション行列の転送
	viewProjection_.TransferMatrix();

#ifdef _DEBUG

	if (input_->TriggerKey(DIK_C)) {
		isDebugCameraActive_ = true;
	}

#endif

	// デバッグカメラの処理
	if (isDebugCameraActive_) {

		// デバッグカメラの更新
		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetView();
		viewProjection_.matProjection = debugCamera_->GetProjection();
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();

	} else {

		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

	ImGui::Begin("ViewProjection");
	ImGui::DragFloat3("pos", &viewProjection_.translation_.x, 0.01f);
	ImGui::End();
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

	// スター更新
	star_->Draw(viewProjection_);

	// パーティクル描画
	for (std::unique_ptr<Perticle>& perticle : perticles_) {
		perticle->Draw(viewProjection_);
	}

	// ステージ描画
	stage_->Draw(viewProjection_);

	// 天球描画
	skydome_->Draw(viewProjection_);

	// マーク描画
	mark_->Draw(viewProjection_);

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

void GameScene::PerticlePop(const Vector3& position_, const std::unique_ptr<Model>& model, const int& perticleNum) {

	// エミッターを作成
	std::unique_ptr<Emitter> newEmitter = std::make_unique<Emitter>();
	// エミッター初期化
	newEmitter->SetPosition(position_);
	// エミッターからパーティクルを作成
	newEmitter->Emit(perticles_, model.get(), perticleNum);
}
