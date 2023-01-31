#pragma once
#include "BallDistinction.h"
#include "BasicBall.h"
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include "InstanceBall.h"
#include "Input.h"
#include "SelectScene.h"

// �^�C�}�[�����炷�Ԋu
#define TIMER_COUNT 1
// �^�C�}�[�̏����l
#define MAX_SPONE_TIMER 100
#define MAX_COL_TIMER 10
// �S�[����pos.x�����p
#define ADJUSMENT_POS_X 100
// �S�[���̎��ʗp
#define YELLOW_BALL_GOAL 0
#define RED_BALL_GOAL 1
// �J�E���g�����n
#define START_COUNT 100
// ���a���_�ω��p(���a�ő�l+5)
#define COUNT_CHANGE_RATIOS 35
// ���[�v�x������
#define WAIT_TIME 16
// deltaTime�ő�l
#define MAX_DELTA_TIME 0.05f
// �^�C�}�[�����p
#define ADJUST_TIMER 1000
// �w�i�X�N���[���X�s�[�h
#define SCROLL_LOW_SPEED 100
#define SCROLL_HIGH_SPEED 200

// �|�C���^Delete�p
#define SAFE_DELETE(o)  if (o){ delete (o); o = NULL; }

// �摜�t�@�C�����Ƃ��̃n���h�������\����
struct Dx_Texture {
	// �摜�̃t�@�C����
	std::string filename;	
	// �摜�̃n���h���iDxlib�Ŏg�p�������)
	int handle;					
};
class Game {
public:
	bool Initialize();
	void DisplayTime();
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void UpdateGame();
	void UnloadData();
	int GetTexture(const std::string& fileName);
	void Shutdown();
	void RunLoop();		
	void JudgCount();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	void AddSortingBowls(class BallDistinction* ast);
	void RemoveSortingBowls(class BallDistinction* ast);
	void GenerateOutput();
	// �V�[���摜�f�[�^��ǂݍ��ރ��\�b�h�̒�`
	void LoadData(const int);
	void BackgroundLoading(std::string str, std::string str2, float speed);

	Game();
	~Game();

	// �ȉ�����p======================================

	void SetStartTime(int value) { startTime = value; }
	void SetGameOverFlag(bool flag) { gameOver = flag; }
	void SetCount(float value) { count = value; }
	// �d�����������ɃJ�E���g�𑝂₷
	void CountUp(UINT radius) { count += ~radius + COUNT_CHANGE_RATIOS; }
	// �G�l�~�[�{�[���ɓ������������a���J�E���g�����炷
	void CountDown(float radius) { count -= radius; }

	// �ȏ����p======================================

	// �ȉ��擾�p======================================

	inline std::vector<class BallDistinction*>& GetSortingBowls() { return ballDistinctions; }
	inline std::vector<class Actor*>& GetActors() { return actors; }
	inline class Input* GetInput() { return input; }
	inline class SelectScene* GetSelectScene() { return selectScene; }

	// �ȏ�擾�p======================================

private:
	//��ʂ̒��S
	int centerX, centerY;
	//�Q�[������
	int startTime;
	//�v���C����
	int playTime;
	//�Q�[���X�^�[�g����̎��Ԃ�ێ�����ϐ�
	int time;
	// Actor���𒼂��ɍX�V���邩�ǂ����̃t���O
	bool updatingActors;
	// �Q�[���J�n����̌o�ߎ���
	float  ticksCount;
	// �����t���O
	bool instansFlag;
	// �����Ԋu
	int instansTimer;
	// �d���������J�E���g
	int count;
	// �Q�[���I�[�o�[�t���O
	bool gameOver;

	// �摜�f�[�^(�t�@�C�����Ƃ��̃n���h�����Z�b�g)�ɂ������I�z��
	std::unordered_map<std::string, int> textures;

	// �ȉ��z��|�C���^================================

	// �{�[���i�[�p�z��|�C���^
	std::vector<class BallDistinction*>ballDistinctions;
	// �V�[���ɓo�^����Actor�N���X�̓��I�z��̃|�C���^
	std::vector<class Actor*> actors;
	// �o�^����\���Actor�N���X�̓��I�z��̃|�C���^
	std::vector<class Actor*> pendingActors;
	// �V�[���ɓo�^����X�v���C�g�̃|�C���^
	std::vector<class SpriteComponent*> sprites;

	// �ȏ�z��|�C���^================================

	// �ȉ��N���X�|�C���^===============================

	class Input* input;
	class InstanceBall* instance;
	class SelectScene* selectScene;

	// �ȏ�N���X�|�C���^===============================

	// ���͂̃��\�b�h
	void processInput();
	// �������ł���܂ł̃J�E���^�[
	bool waitInstans(bool*, int*);

};

