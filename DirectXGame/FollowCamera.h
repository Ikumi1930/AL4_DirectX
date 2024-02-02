#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include <Input.h>

class FollowCamera {
public:

	void Initialize();

	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; }

	const ViewProjection& GetViewProjection() { return viewProjection_; }

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;

	//追従対象
	const WorldTransform* target_ = nullptr;
	Input* input_ = nullptr;
	float rotateSpeed_ = 0.01f;

};
