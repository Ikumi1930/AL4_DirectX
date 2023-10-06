#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);
	// 代入文の左側がメンバ変数。右側引数
	model_ = model;
	texturHandle_ = textureHandle;
	worldTransform_.Initialize();
}

void Player::Update() {}

void Player::Draw() {}
