#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 　描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection, uint32_t textureHandle_);
	WorldTransform& GetWorldTransform() { return worldTransform_; }


private:
	//ワールド変換データ
	WorldTransform worldTransform_;

	//頭のワールド変換データ
	WorldTransform worldTransformHead_;

	//左手のワールド変換データ
	WorldTransform worldTransformLeftHand_;

	//右手のワールド変換データ
	WorldTransform worldTransformRightHand_;

	//左足のワールド変換データ
	WorldTransform worldTransformLeftLeg_;

	//右足のワールド変換データ
	WorldTransform worldTransformRightLeg_;


	ViewProjection* viewProjection_;

	//モデル
	Model* model_ = nullptr;

	//頭
	Model* modelHead_ = nullptr;

	//左手
	Model* modelLeftHand_ = nullptr;

	//右手
	Model* modelRightHand_ = nullptr;

	//左足
	Model* modelLeftLeg_ = nullptr;

	//右足
	Model* modelRightLeg_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//キーボード入力
	Input* input_ = nullptr;
	
	



};
