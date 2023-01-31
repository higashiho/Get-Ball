#include "Actor.h"
#pragma once
#include "Component.h"
#include "Math.h"
#include "CircleComponent.h"
#include"BoxComponent.h"

class BoxComponent : public Component// Component�̌p���N���X�錾
{
public:
	BoxComponent(class Actor* owner);						// �N���X�̃R���X�g���N�^�[
	void  SetPoint(Vector2 max1, Vector2 min1) { max = max1; min = min1; }
	// �Փˋ�`�̍�����W�ƉE�����W��ݒ肷�郁�\�b�h�̎���
	Vector2  GetmaxPoint() { return max; }					// �Փˋ�`�̉E�����W��Ԃ����\�b�h����
	Vector2  GetminPoint() { return min; }					// �Փˋ�`�̍�����W��Ԃ����\�b�h����

	const Vector2 GetCenter() const;						// �Փˋ�`�̒��S�̍��W��Ԃ����\�b�h

	Vector2 dd;												// �Փˋ�`�̍l���̈�̂��A����������
private:
	Vector2 max, min;// �Փˋ�`�̉E�����W�A������W
};

// �Փˉ~�ƏՓˋ�`�̌�������֐�
bool Intersect(const CircleComponent& a, BoxComponent& b);

// �Փˋ�`�ǂ����̌�������֐�
bool Intersect(BoxComponent& a, BoxComponent& b);

