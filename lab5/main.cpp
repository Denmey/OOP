#include "Figures.hpp"
#include "vector.cpp"
#include "shared_ptr.cpp"
#include <iostream>
#include <ctime>

#define OBJ_N 1000 // Количество тестируемых объектов
#define X_MAX 1920 // Максимально возможное значение X положения фигуры
#define Y_MAX 1080 // Y
#define R_MAX 100 // Максимальный радиус от цента фигуры до ее вершин

using namespace std;

void generateShapes(stepik::vector<stepik::shared_ptr<Shape>>& SSPVect)
{
	srand(time(NULL));
	for (stepik::shared_ptr<Shape> &i : SSPVect)
	{
		switch (rand()%3)
		{
			case 0: // Круг
				i.reset(new Circle{});
				static_cast<Circle&>(*i).setRadius(
					static_cast<double>(rand()%R_MAX));
				break;
			case 1: // Пятиугольник
				i.reset(new Pentagon{});
				static_cast<Pentagon&>(*i).setDotsRadius({
					static_cast<double>(rand()%R_MAX),
					static_cast<double>(rand()%R_MAX),
					static_cast<double>(rand()%R_MAX),
					static_cast<double>(rand()%R_MAX),
					static_cast<double>(rand()%R_MAX)
				});
				static_cast<Pentagon&>(*i).setDotsAngle({
					static_cast<double>(rand()),
					static_cast<double>(rand()),
					static_cast<double>(rand()),
					static_cast<double>(rand()),
					static_cast<double>(rand())
				});
				break;
			case 2: // Правильный пятиугольник
				i.reset(new RegPentagon{});
				static_cast<RegPentagon&>(*i).setDotsRadius(
					static_cast<double>(rand()%R_MAX));
				break;
		}
		// Устанавливаем поля базового для всех объектов класса
		i->setPos({static_cast<double>(rand()%X_MAX),
			static_cast<double>(rand()%Y_MAX), 0});
		i->setColor({rand()%256, rand()%256, rand()%256});
		i->setAngle(rand());
	}
}

// First argument is container with shapes, second - predicate
stepik::shared_ptr<Shape> findFirstOccurence(
	stepik::vector<stepik::shared_ptr<Shape>>& SSPVect,
	bool (*predicate)(const Shape&))
{
	for (stepik::shared_ptr<Shape> &i : SSPVect)
	{
		if (predicate(*i))
			return i;
	}
	return stepik::shared_ptr<Shape>{nullptr};
}

int main()
{
	stepik::vector<stepik::shared_ptr<Shape>> SSPVect(OBJ_N);

	generateShapes(SSPVect);

	for (auto &i : SSPVect)
	{
		cout << *i << " ";
	}
	cout << endl;

	//1.  Поиск первого элемента удовлетворяющего определенному критерию.

	{
		stepik::shared_ptr<Shape> found{findFirstOccurence(SSPVect,
			[](const Shape& a)
			{
				if (a.getPos().x<100 && a.getPos().y>200) return true;
				return false;
			})};
		if (found)
			cout << "First element with x<100 and y>200 is " << found.get() << ": "
				<< endl << *found;
		else
		{
			cout << "Couldn't find element with x<100 and y>200." << endl;
		}
	}

	// 12. Отсортировать элементы диапазона так, чтобы правильный элемент находился на n-й позиции
   //  (все стоящие перед ним элементы не превосходят его, а все стоящие после - превосходят либо равны).

	

	return 0;
}
