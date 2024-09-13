#include "Mark.h"

void Mark::Initialize(Model* model, Vector3 position) {

	// 引数をメンバ変数に代入
	model_ = model;
	worldTransform_.translation_ = position;

	// ワールド変換初期化
	worldTransform_.Initialize();
}
void Mark::Update() {

	// ワールド変換更新
	worldTransform_.UpdateMatrix();
}

void Mark::Draw(ViewProjection& viewProjection) {

	// モデル描画
	model_->Draw(worldTransform_, viewProjection);
}