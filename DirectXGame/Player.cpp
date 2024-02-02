﻿#include "Player.h"
#include "MyMath.h"
#include <cassert>
#include <GameScene.h>


void Player::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);
	// 代入文の左側がメンバ変数。右側引数
	model_ = model;
	texturHandle_ = textureHandle;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}

void Player::Update() {

	
	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	//ゲームパッドの状態取得、ゲームパッドが有効の場合if文が通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float speed = 0.3f;

		// 移動量
		Vector3 move = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed};

		Vector3 normalizeMove = Normalize(move);

		// 移動量に速さを反映
		move.x = normalizeMove.x * speed;
		move.y = normalizeMove.y * speed;
		move.z = normalizeMove.z * speed;


		//新規追加
		Matrix4x4 matCamerRotate = MakeRotateYMatrix(viewProjection_->rotation_.y);
		move = TransformNormal(move, matCamerRotate);


		//
		if (move.x != 0 || move.z != 0) {
			worldTransform_[(size_t)ModelParts::kBase].rotation_.y = std::atan2f(move.x, move.z);
		}

		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);

		// 行列を更新
		worldTransform_.UpdateMatrix();
	}
}

void Player::Draw(const ViewProjection& viewProjection, uint32_t textureHandle_) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
