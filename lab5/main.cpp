#include "Figures.hpp"
#include "vector.cpp"
#include "shared_ptr.cpp"
#include <iostream>
#include <ctime>

#define OBJ_N 5 // Количество тестируемых объектов
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

// First argument is container with shapes, second - predicate function
// Returns a shared pointer to a found element
// 	Or empty shared pointer if all elements not matching a predicate
stepik::shared_ptr<Shape> findFirstOccurence(
	const stepik::vector<stepik::shared_ptr<Shape>>& SSPVect,
	bool (*predicate)(const Shape&))
{
	for (const stepik::shared_ptr<Shape> &i : SSPVect)
	{
		if (predicate(*i))
			return i;
	}
	return stepik::shared_ptr<Shape>{nullptr};
}

// Function that sorts container(First elements are not matching predicate)
// First argument is container with shapes, second - predicate function
// Returns first element that matching a predicate.
// If there is no such elements then returns -1
int sort(stepik::vector<stepik::shared_ptr<Shape>>& SSPVect,
	bool (*predicate)(const Shape&))
{
	// Sorting
	std::sort(SSPVect.begin(), SSPVect.end(),
		[predicate](const stepik::shared_ptr<Shape>& lhs,
			const stepik::shared_ptr<Shape>& rhs) -> bool
		{
			return predicate(*lhs)<predicate(*rhs);
		});
	// Searching first matching element and returning it's index if found
	for (unsigned i = 0, size = SSPVect.size(); i < size; ++i)
		if (predicate(*SSPVect[i]))
			return i;
	// No matching element
	return -1;
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
	cout << endl;

	// 12. Отсортировать элементы диапазона так, чтобы правильный элемент находился на n-й позиции
   //  (все стоящие перед ним элементы не превосходят его, а все стоящие после - превосходят либо равны).
	// 'True' - figure is in right bottom quarter
	{
		int index = sort(SSPVect,
			[](const Shape& a)
			{
				if (a.getPos().x>(X_MAX/2) && a.getPos().y>(Y_MAX/2)) return true;
				return false;
			});
		cout << "Sorting container: predicate - figure's position in the left bottom quarter." << endl;
		cout << "Sorted container: " << endl;
		for (auto &i : SSPVect)
		{
			cout << *i << " ";
		}
		cout << endl;
		if (index>=0)
			cout << "Index of first element matching predicate: " << index
				<< endl << *(SSPVect[index]);
		else
			cout << "No elements matching a predicate." << endl;
	}

	return 0;
}
