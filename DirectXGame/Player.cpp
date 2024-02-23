#include "Player.h"
#include "MyMath.h"
#include <cassert>
#include <GameScene.h>
#include "ViewProjection.h"


void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);
	// 代入文の左側がメンバ変数。右側引数
	model_ = model;

	//頭
	modelHead_ = model;

	//左手
	modelLeftHand_ = model; 
	
	//右手
	modelRightHand_ = model;

	//左足
	modelLeftLeg_ = model;

	//右足
	modelRightLeg_ = model;

	textureHandle_ = textureHandle;
	worldTransform_.Initialize();

	//頭のワールドトランスフォーム
	worldTransformHead_.Initialize();

	//左手のワールドトランスフォーム
	worldTransformLeftHand_.Initialize();

	//右手のワールドトランスフォーム
	worldTransformRightHand_.Initialize();

	//左足のワールドトランスフォーム
	worldTransformLeftLeg_.Initialize();

	//右足のワールドトランスフォーム	
	worldTransformRightLeg_.Initialize();




	/********************
         　　位置	
	*********************/
	//体
	worldTransform_.translation_.z = 50.0f;

	//頭
	worldTransformHead_.translation_.x = 0.0f;
	worldTransformHead_.translation_.y = 3.0f;

	//左手
	worldTransformLeftHand_.translation_.x = -2.0f;
	worldTransformLeftHand_.translation_.y = 2.0f;

	//右手
	worldTransformRightHand_.translation_.x = 2.0f;
	worldTransformRightHand_.translation_.y = 2.0f;

	//左足
	worldTransformLeftLeg_.translation_.x = 0.0f;
	worldTransformLeftLeg_.translation_.y = -4.0f;

	// 左足
	worldTransformRightLeg_.translation_.x = 0.0f;
	worldTransformRightLeg_.translation_.y = -4.0f;

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
		Matrix4x4 matCameraRotate = MakeRotateYMatrix(viewProjection_->rotation_.y);
		move = TransformNormal(move, matCameraRotate);


		//
		if (move.x != 0 || move.z != 0) {
			worldTransform_.rotation_.y = std::atan2f(move.x, move.z);

			worldTransformHead_.rotation_.y = std::atan2f(move.x, move.z);

			worldTransformLeftHand_.rotation_.y = std::atan2f(move.x, move.z);

			worldTransformRightHand_.rotation_.y = std::atan2f(move.x, move.z);

			worldTransformLeftLeg_.rotation_.y = std::atan2f(move.x, move.z);

			worldTransformRightLeg_.rotation_.y = std::atan2f(move.x, move.z);
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
