#include "Perticle.h"
#include <imgui.h>
#include "MathVector.h"

void Perticle::Initialize(Model* model,Vector3 position) {

	// 引数をメンバ変数に代入
	model_ = model;
	worldTransform_.translation_ = position;

	// ワールド変換初期化
	worldTransform_.Initialize();

}

void Perticle::Update() {

	FadeOut();

	// モデルの透明度を変える
	model_->SetAlpha(alpha_);

	// ワールド変換更新
	worldTransform_.UpdateMatrix();

	ImGui::Begin("Perticle");
	ImGui::DragFloat3("Scale", &worldTransform_.scale_.x, 0.01f);
	ImGui::DragFloat3("Translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat("Alpha", &alpha_, 0.01f);
	ImGui::End();
}

void Perticle::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection); }

void Perticle::FadeOut() {

	// 1フレームでどのくらい小さくするか
	Vector3 kSubScale = {0.01f, 0.01f, 0.01f};
	// 1フレームでどのくらい薄くするか
	float kSubAlpha = 0.01f;

	// 透明になっていなければ
	if (alpha_ > 0.0f) {

		// アルファ値を減らして薄くする
		alpha_ -= kSubAlpha;

	// 透明ならば
	} else {

		// 透明度をを元に戻す
		alpha_ = 1.0f;
	}

	// 潰れていなかったら
	if (worldTransform_.scale_.x > 0.0f) {

		// スケールを小さくする
		worldTransform_.scale_ -= kSubScale;

	// 潰れたら
	} else {

		// スケールを元のサイズに戻す
		worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	}

}
