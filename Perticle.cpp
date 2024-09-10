#include "Perticle.h"
#include <imgui.h>
#include "MathVector.h"
#include <random>

void Perticle::Initialize(Model* model,Vector3 position) {

	// 引数をメンバ変数に代入
	model_ = model;
	emitter_.position = position;
	emitter_.min += emitter_.position;
	emitter_.max += emitter_.position;
	worldTransform_.translation_ = Pop(emitter_.min, emitter_.max);

	// ワールド変換初期化
	worldTransform_.Initialize();
}

void Perticle::Update() {

	FadeOut();

	// モデルの透明度を変える
	model_->SetAlpha(alpha_);

	// ワールド変換更新
	worldTransform_.UpdateMatrix();

	ImGui::Begin("emitter");
	ImGui::DragFloat3("position", &emitter_.position.x, 0.01f);
	ImGui::DragFloat3("min", &emitter_.min.x, 0.01f);
	ImGui::DragFloat3("max", &emitter_.max.x, 0.01f);
	ImGui::End();

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

Vector3 Perticle::Pop(const Vector3& min, const Vector3& max) {

	std::random_device rd;
	std::mt19937 gen(rd());

	// float型の数字をランダムに生成
	std::uniform_real_distribution<float> distX(min.x, max.x);
	std::uniform_real_distribution<float> distY(min.y, max.y);
	std::uniform_real_distribution<float> distZ(min.z, max.z);

	return Vector3(distX(gen), distY(gen), distZ(gen));
}

void Perticle::Move() {}
