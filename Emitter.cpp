#include "Emitter.h"
#include <random>
#include "Perticle.h"
#include "MathVector.h"

void Emitter::Emit(std::list<std::unique_ptr<Perticle>>& perticles, Model* model, int numParticles) { 

	min_ += position_;
	max_ += position_;
	
	for (int i = 0; i < numParticles; i++) {

		std::unique_ptr<Perticle> newPerticle = std::make_unique<Perticle>();
		Vector3 particlePosition = Pop(min_, max_);
		newPerticle->Initialize(model, particlePosition);
		perticles.push_back(std::move(newPerticle));
	}
}

Vector3 Emitter::Pop(const Vector3& min, const Vector3& max) {

	std::random_device rd;
	std::mt19937 gen(rd());

	// float型の数字をランダムに生成
	std::uniform_real_distribution<float> distX(min.x, max.x);
	std::uniform_real_distribution<float> distY(min.y, max.y);
	std::uniform_real_distribution<float> distZ(min.z, max.z);

	return Vector3(distX(gen), distY(gen), distZ(gen));
}

void Emitter::SetPosition(const Vector3& newPosition) { position_ = newPosition; }