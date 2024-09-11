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
	modelperticle_.reset(Model::CreateFromOBJ("piece2", false));
}

void GameScene::Update() {

	// キー入力によってエミッターの位置を更新
	if (input_->PushKey(DIK_UP)) {
		position.y += 0.1f; // 上に移動
	}
	if (input_->PushKey(DIK_DOWN)) {
		position.y += -0.1f; // 下に移動
	}

	if (input_->TriggerKey(DIK_SPACE)) {
		// パーティクルを発生させる
		PerticlePop(position);
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

	// ビュープロジェクション更新
	viewProjection_.UpdateMatrix();
	// ワールド変換更新
	worldTransform_.UpdateMatrix();

	// デバッグカメラの生成と初期化
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);

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
	}
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

void GameScene::PerticlePop(const Vector3& position_) {

	// エミッターを作成
	std::unique_ptr<Emitter> newEmitter = std::make_unique<Emitter>();
	// エミッター初期化
	newEmitter->SetPosition(position_);
	// エミッターからパーティクルを作成
	newEmitter->Emit(perticles_, modelperticle_.get(), 24);
}
