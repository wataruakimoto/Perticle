#include "Perticle.h"
#include <imgui.h>
#include "MathVector.h"
#include <random>

void Perticle::Initialize(Model* model,Vector3 position) {

	// 引数をメンバ変数に代入
	model_ = model;
	worldTransform_.translation_ = position;

	speed_ = SetDirection(min_, max_);

	// ワールド変換初期化
	worldTransform_.Initialize();
}

void Perticle::Update() {

	Move();

	FadeOut();

	// ワールド変換更新
	worldTransform_.UpdateMatrix();

	ImGui::Begin("Perticle");
	ImGui::DragFloat3("Scale", &worldTransform_.scale_.x, 0.01f);
	ImGui::DragFloat3("Translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("Speed", &speed_.x, 0.01f);
	ImGui::DragFloat3("Min", &min_.x, 0.01f);
	ImGui::DragFloat3("Max", &max_.x, 0.01f);
	ImGui::End();
}

void Perticle::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}

void Perticle::FadeOut() {

	// 1フレームでどのくらい小さくするか
	Vector3 kSubScale = {0.01f, 0.01f, 0.01f};
	
	// 潰れていなかったら
	if (worldTransform_.scale_.x > 0.0f) {

		// スケールを小さくする
		worldTransform_.scale_ -= kSubScale;

	} else {

		// 死亡フラグを立てる
		isDead_ = true;
	}
}

void Perticle::Move() {

	worldTransform_.rotation_ += speed_;
	worldTransform_.translation_ += speed_;
}

Vector3 Perticle::SetDirection(const Vector3& min, const Vector3& max) {

	std::random_device rd;
	std::mt19937 gen(rd());

	// float型の数字をランダムに生成
	std::uniform_real_distribution<float> distX(min.x, max.x);
	std::uniform_real_distribution<float> distY(min.y, max.y);
	std::uniform_real_distribution<float> distZ(min.z, max.z);

	return Vector3(distX(gen), distY(gen), distZ(gen));
}