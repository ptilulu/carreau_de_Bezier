#include <cmath>
#include "segment.h"

Segment::Segment()
{
	pointList = new Point[2];
}

Segment::~Segment()
{
	delete [] pointList;
	pointList = nullptr;
}

Segment::Segment(Point A, Point B)
{
    pointList = new Point[2];
    pointList[0]=A;
    pointList[1]=B;
}

Segment::Segment(const Segment & s)
{
	pointList = new Point[2];

	for (unsigned i=0; i<2; ++i)
		pointList[i] = s.pointList[i];

}

void Segment::setStart(const Point & p)
{
	pointList[0] = p;
}

void Segment::setEnd(const Point & p)
{
	pointList[1] = p;
}

void Segment::setN(unsigned r, const Point & p)
{
	if (r>1)
		r=1;
	pointList[r] = p;
}

Point Segment::getN(unsigned r) const
{
	if (r>1)
		r=1;

	return pointList[r];
}

Point Segment::getStart() const
{
	return getN(0);
}


Point Segment::getEnd() const
{
	return getN(1);
}

float Segment::length() const
{
	float res=0.0f;

	for (unsigned i=0; i<3; ++i)
		res += pow((pointList[1]).getN(i) - (pointList[0]).getN(i), 2.0f);

	return sqrt(res);
}

void Segment::makeObject(QVector<GLfloat> *vertData)
{
    GLfloat vertices[6];
    GLfloat colors[6];

    //VStart
    vertices[0] = getStart().getX();
    vertices[1] = getStart().getY();
    vertices[2] = getStart().getZ();

    //VEnd
    vertices[3] = getEnd().getX();
    vertices[4] = getEnd().getY();
    vertices[5] = getEnd().getZ();

    //CStart
    colors[0] = getStart().getR();
    colors[1] = getStart().getG();
    colors[2] = getStart().getB();

    //CEnd
    colors[3] = getEnd().getR();
    colors[4] = getEnd().getG();
    colors[5] = getEnd().getB();

    for (int i = 0; i < 2; ++i) { //2 sommets
        // coordonnées sommets
        for (int j = 0; j < 3; j++) //3 coords par sommet
            vertData->append(vertices[i*3+j]);
        // couleurs sommets
        for (int j = 0; j < 3; j++) //1 RGB par sommet
            vertData->append(colors[i*3+j]*10);

        for (int j = 0; j < 3; j++) //1 RGB par sommet
            vertData->append(0);
    }
}

Segment& Segment::operator= (const Segment &s)
{
	for (unsigned i=0; i<2; ++i)
		pointList[i] = s.pointList[i];

return *this;
}

std::ostream& operator<<(std::ostream& out, const Segment& s)
{
	return out << s.pointList[0] << " -- " << s.pointList[1];
}
