#include "FollowCamera.h"
#include "Material.h"
#include "MyMath.h"

#define ROTATE_SPEED 0.1f

void FollowCamera::Initialize() { 
	viewProjection_.Initialize(); 
	input_ = Input::GetInstance();
	rotateSpeed_ = 0.01f;
}

void FollowCamera::Update() {

	if (input_->PushKey(DIK_Q)) {
	viewProjection_.rotation_.y += rotateSpeed_;
	}

	if (input_->PushKey(DIK_E)) {
	viewProjection_.rotation_.y -= rotateSpeed_;
	}

	//ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

	//ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * ROTATE_SPEED;
	}

	//追従対象がいれば
	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -10.0f};

		//カメラの角度から回転行列を計算する
		Matrix4x4 matRotateY = MakeRotateYMatrix(viewProjection_.rotation_.y);

		//オフセットをカメラの回転に合わせて回転される
		offset = TransformNormal(offset, matRotateY);

		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_.x = target_->translation_.x + offset.x;
		viewProjection_.translation_.y = target_->translation_.y + offset.y;
		viewProjection_.translation_.z = target_->translation_.z + offset.z;
	}
	viewProjection_.UpdateMatrix();
}
