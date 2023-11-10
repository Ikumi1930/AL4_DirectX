#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model) {
	assert(model);
	model_ = model; 
	worldTransform_.Initialize();
	viewProjrction_.Initialize();
}

void Skydome::Update() {}

void Skydome::Draw() {
	model_->Draw(worldTransform_, viewProjrction_);
}

