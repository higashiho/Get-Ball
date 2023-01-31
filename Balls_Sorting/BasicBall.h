#pragma once
#include "DxLib.h"
#include "Actor.h"
#include <math.h>
#include <vector>

const extern int SIZE_X, SIZE_Y;		// �E�B���h�E�̂������A�������̑傫��
const extern int BORDER_Y;				// ���\���̈��Y���W(��ʍŉ�������

// �A�j���[�V�����̑��x
#define ANIM_SPEED 5

// �{�[���̎��
struct  BallPattern{
	const int YELLOW_BALL = 0x00;
	const int RED_BALL = 0x01;
	const int ENEMY_BALL = 0x02;
};

// �{�[���p�萔
struct ConstBall{
	// vx vy�ő�l
	const int MAX_VX = 200, MAX_VY = 200;		
	// �{�[���T�C�Y�����p
	const float SCALING = 40.0f;	
	// ��ʒ[�����p
	const int OUT_LINE = 5;	
	// ���x���]�p
	const int RETURN_SPEED = 1;		
	// ���a�����p
	const int RADIUS_ADJUSMENT = 2;
	// ���a�ŏ��l
	const int MIN_RADIUS = 10;			
	// �����蔻��̔��a
	const float COL_RADIUS = 50.f;				
};

class BasicBall :public Actor {
public:
	//������
	BasicBall(class Game* game);

	virtual ~BasicBall();

	//�Փˊ֐�(���͂̋��E�ɏՓ˂������̏���)
	virtual void Collision() = 0;
	//Ball�̈ʒu���X�V����֐��@deltaTime:���[�v���P���鎞��
	virtual void Update(float deltatime) = 0;
	//���x�̐ݒ�֐�
	void SetV(int vx1, int vy1);
	// �ēx�����������p
	virtual void Reset() = 0;
	// radius��ݒ肷�郁�\�b�h
	void RadiusRand();
	// �ړ������֐�
	virtual Vector2 Movement(Vector2, float) = 0;


	// �ȉ��擾�p===========================

	inline int Getx() { return x; }
	inline int Gety() { return y; }
	inline int GetRadius() { return radius; }
	inline int GetThisBallPattern() { return ballPattern; }
	//��ʂɕ\������Ă���̂�
	inline bool GetDispflag();
	inline class CircleComponent* GetCircle() { return circleCol; }
	inline bool GetOnDrag() { return onDrag; }
	inline bool GetOnMouse() { return onMouse; }
	inline bool GetBallDrop() { return ballDrop; }

	// �ȏ�擾�p===========================


	/// �ȉ�����p==========================

	void SetRadius(float r) { radius = r; };
	//�ʒu��ݒ肷��֐��i�����͍��W�l�j�@�߂�l�̓E�B���h�E�͈͓̔�
	bool SetyBall(int x1, int y1);
	void SetOnDrag(bool flag) { onDrag = flag; }
	void SetOnMouse(bool flag) {onMouse = flag;}
	void SetBallDrop(bool flag) { ballDrop = flag; }

	/// �ȏ����p==========================

protected:
	// ball�̍��W
	int x, y;	
	// ball�̑��x
	int vx, vy;				
	// �{�[���̔��a
	int radius;				
	// �E�����̃X�s�[�h
	float rightSpeed;		
	// �������̃X�s�[�h
	float downSpeed;		
	//�f�B�X�v���C�̒��ɂ��邩
	bool dispFlag;			
	//�}�E�X�̃h���b�O�X�C�b�`
	bool onDrag;				
	//�}�E�X�̃|�C���^�[�I���X�C�b�`	
	bool onMouse;	
	// �}�E�X���h���b�O����ė����ꂽ�t���O
	bool ballDrop;
	//�Փˉ~�ւ̃|�C���^�[
	class CircleComponent* circleCol;		
	// ���g�̃{�[���p�^�[��
	int ballPattern;
	// �萔�g�p�p
	ConstBall cBall;
	BallPattern pBalls;
	// ���������Ώۊi�[�p�|�C���^
	class BallDistinction* sBalls;

	// �A�j���[�V�����N���X�|�C���^
	
	class AnimSpriteComponent* asc;

};
