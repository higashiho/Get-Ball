#include"BoxComponent.h"
#include"Actor.h"

//BoxComponent�̃R���X�g���N�^�[
BoxComponent::BoxComponent(class Actor* owner)
    :Component(owner)
{

}

//�Փˋ�`�̒��S��Ԃ����\�b�h
const Vector2 BoxComponent::GetCenter() const
{
    return owner->GetPosition();
}

float MinDistSq(const Vector2 point, BoxComponent& box)
{
    const Vector2 min = box.GetminPoint();
    const Vector2 max = box.GetmaxPoint();

    float dx = Math::Max(min.x - point.x, 0.0f);    //Math.Max()�̂Q�̈����̒l�̑傫���ق���Ԃ��֐�
    dx = Math::Max(dx, point.x - max.x);            //dx�ɂ͂R�̒l�̍ő�l���c��

    float dy = Math::Max(min.y - point.y, 0.0f);
    dy = Math::Max(dy, point.y - max.y);

    return dx * dx + dy * dy;                       //�����̂Q���Ԃ�
}

// ��`�Ɖ~�̏Փ˔���
bool Intersect(const CircleComponent& a, BoxComponent& b)
{
    //�~�ƒ����`�̋�����Ԃ��֐�
    float distSq = MinDistSq(a.GetCenter(), b);

    //�~�̔��a
    float radiiSq = a.GetRadius();
    radiiSq *= radiiSq;

    //�~�̂Q��̔��a�Ƌ����̂Q��̔��a���ׂ�
    return distSq <= radiiSq;
}

// ��`�Ƌ�`�̏Փ˔���
bool Intersect(BoxComponent& a, BoxComponent& b)
{
    Vector2 max_a, max_b;
    Vector2 min_a, min_b;
    max_a = a.GetmaxPoint();
    max_b = b.GetmaxPoint();
    min_a = a.GetminPoint();
    min_b = b.GetminPoint();

    // �ǂꂩ�����藧�ꍇtrue��Ԃ�
    bool flag = (max_a.x < min_b.x) ||
        (max_a.y < min_b.y) ||
        (max_b.x < min_a.x) ||
        (max_b.y < min_a.y);

    // ���ۂɌ��������ꍇ�̍����v�Z
    float dx1 = min_b.x - max_a.x;
    float dx2 = max_b.x - min_a.x;
    float dy1 = min_b.y - max_a.y;
    float dy2 = max_b.y - min_a.y;

    // �Փˋ�`�̍l���̈�̂��A������������ݒ肷��
    // x�����̍��̐�Βl�𒲂ׂ�
    if (Math::Abs(dx1) < Math::Abs(dx2))
        a.dd.x = dx1;
    else
        a.dd.x = dx2;
    // y�����̍��̐�Βl�𒲂ׂ�
    if (Math::Abs(dy1) < Math::Abs(dy2))
        a.dd.y = dy1;
    else
        a.dd.y = dy2;
    // x����,y�����̍��𒲂ׂ�
    if (Math::Abs(a.dd.x) < Math::Abs(a.dd.y))
        a.dd.y = 0.0f;
    else
        a.dd.x = 0.0f;

    // �������Ȃ�����̋t��true�̎���������
    return !flag;
}
