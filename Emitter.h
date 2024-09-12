#include "WorldTransform.h"
#include <list>
#include <memory>
#include "Model.h"
#pragma once

/// <summary>
/// パーティクル前方宣言
/// </summary>
class Perticle;

class Emitter {
private: // メンバ変数
	Vector3 position_;
	Vector3 min_ = {-2.0f, -2.0f, -2.0f};
	Vector3 max_ = {2.0f, 2.0f, 2.0f};

public: // メンバ関数
	
	/// <summary>
	/// エミッターからパーティクルを発生
	/// </summary>
	/// <param name="perticles">パーティクル</param>
	/// <param name="model">モデル</param>
	/// <param name="numParticles">パーティクルの個数</param>
	void Emit(std::list<std::unique_ptr<Perticle>>& perticles, Model* model, int numParticles);

	/// <summary>
	/// エミッターのどこに出るか
	/// </summary>
	/// <returns></returns>
	Vector3 Pop(const Vector3& min, const Vector3& max);

	/// <summary>
	/// 位置の設定
	/// </summary>
	/// <param name="newPosition"></param>
	void SetPosition(const Vector3& newPosition);
};
