
#define eps 1e-8
int dcmp(double x){
	if (fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
struct Point{
	double x, y;
	Point(double p = 0, double q = 0){
		x = p;
		y = q;
	}
};
struct Node{
	int p;
	Point a, b;
	Node(Point a1, Point a2, int t){
		a = a1;
		b = a2;
		p = t;
	}
};

typedef Point Vector;

Vector operator + (Vector A, Vector B){
	return Vector(A.x + B.x, A.y + B.y);
}
Vector operator - (Vector A, Vector B){
	return Vector(A.x - B.x, A.y - B.y);
}
Vector operator * (Vector A, double p){
	return Vector(A.x * p, A.y * p);
}
Vector operator / (Vector A, double p){
	return Vector(A.x / p, A.y / p);
}
bool operator == (Vector A, Vector B){
	return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0;
}
bool operator > (Vector A, Vector B){
	return A.x > B.x && A.y > B.y;
}
bool operator <(Vector A, Vector B){
	return A.x < B.x && A.y < B.y;
}
//���
double  Dot(Vector A, Vector B){
	return A.x * B.x + A.y * B.y;
}
//ģ
double Length(Vector A){
	return sqrt(Dot(A, A));
}
//�н�
double Angle(Vector A, Vector B){
	return acos(Dot(A, B) / Length(A) / Length(B));
}
//���
double Cross(Vector A, Vector B){
	return A.x * B.y - A.y*B.x;
}
//���������
double Area2(Point A, Point B, Point C){
	return Cross(B - A, C - A);
}
//����ֱ����ͶӰ
Point GetLineProjection(Point P, Point A, Point B){
	Vector v = B - A;
	return A + v * (Dot(v, P - A) / Dot(v, v));
}
//�߶��ཻ(�����˵�)
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2){
	double c1 = Cross(a2 - a1, b1 - a1);
	double c2 = Cross(a2 - a1, b2 - a1);
	double c3 = Cross(b2 - b1, a1 - b1);
	double c4 = Cross(b2 - b1, a2 - b1);
	return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
//����ֱ����(�����˵�)
bool OnSegment(Point p, Point a1, Point a2){
	return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}