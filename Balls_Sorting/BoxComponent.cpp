#include"BoxComponent.h"
#include"Actor.h"

//BoxComponentのコンストラクター
BoxComponent::BoxComponent(class Actor* owner)
    :Component(owner)
{

}

//衝突矩形の中心を返すメソッド
const Vector2 BoxComponent::GetCenter() const
{
    return owner->GetPosition();
}

float MinDistSq(const Vector2 point, BoxComponent& box)
{
    const Vector2 min = box.GetminPoint();
    const Vector2 max = box.GetmaxPoint();

    float dx = Math::Max(min.x - point.x, 0.0f);    //Math.Max()の２つの引数の値の大きいほうを返す関数
    dx = Math::Max(dx, point.x - max.x);            //dxには３つの値の最大値が残る

    float dy = Math::Max(min.y - point.y, 0.0f);
    dy = Math::Max(dy, point.y - max.y);

    return dx * dx + dy * dy;                       //距離の２乗を返す
}

// 矩形と円の衝突判定
bool Intersect(const CircleComponent& a, BoxComponent& b)
{
    //円と長方形の距離を返す関数
    float distSq = MinDistSq(a.GetCenter(), b);

    //円の半径
    float radiiSq = a.GetRadius();
    radiiSq *= radiiSq;

    //円の２乗の半径と距離の２乗の半径を比べる
    return distSq <= radiiSq;
}

// 矩形と矩形の衝突判定
bool Intersect(BoxComponent& a, BoxComponent& b)
{
    Vector2 max_a, max_b;
    Vector2 min_a, min_b;
    max_a = a.GetmaxPoint();
    max_b = b.GetmaxPoint();
    min_a = a.GetminPoint();
    min_b = b.GetminPoint();

    // どれかが成り立つ場合trueを返す
    bool flag = (max_a.x < min_b.x) ||
        (max_a.y < min_b.y) ||
        (max_b.x < min_a.x) ||
        (max_b.y < min_a.y);

    // 実際に交差した場合の差を計算
    float dx1 = min_b.x - max_a.x;
    float dx2 = max_b.x - min_a.x;
    float dy1 = min_b.y - max_a.y;
    float dy2 = max_b.y - min_a.y;

    // 衝突矩形の考査領域のｘ、ｙ方向成分を設定する
    // x方向の差の絶対値を調べる
    if (Math::Abs(dx1) < Math::Abs(dx2))
        a.dd.x = dx1;
    else
        a.dd.x = dx2;
    // y方向の差の絶対値を調べる
    if (Math::Abs(dy1) < Math::Abs(dy2))
        a.dd.y = dy1;
    else
        a.dd.y = dy2;
    // x方向,y方向の差を調べる
    if (Math::Abs(a.dd.x) < Math::Abs(a.dd.y))
        a.dd.y = 0.0f;
    else
        a.dd.x = 0.0f;

    // 交差しない判定の逆がtrueの時交差する
    return !flag;
}
