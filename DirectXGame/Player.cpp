#include "Player.h"
#include "MyMath.h"
#include <cassert>


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

		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move);

		// 行列を更新
		worldTransform_.UpdateMatrix();
	}
}

void Player::Draw() {}
