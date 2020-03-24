#include<iostream>
#include<queue>
using namespace std;

struct node // структура для представления узлов дерева
{
	int key;//значение узла
	unsigned char height;//высота поддерева с корнем в данном узле
	node* left;//указатель на девое поддерево
	node* right;//указатель на правое поддерево
	node(int k) { key = k; left = right = 0; height = 1; }//конструктор новго узла с высотой 1
};

unsigned char height(node* p)//функция вычисления высоты
{
	if (!p)//если пустое
		return 0;//вернуть 0
	else//иначе
		return p->height;//вернуть высоту
	//return p ? p->height : 0;
}

int bfactor(node* p)//вычисляем баланс фактор узла
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)//востанавливает корректное значение высоты
{
	unsigned char hl = height(p->left);//высота левого
	unsigned char hr = height(p->right);//высота правого
	p->height = (hl > hr ? hl : hr) + 1;//если h1 > hr то h1 + 1 иначе hr + 1
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;//вершину перемешаем на левое поддерево
	p->left = q->right;//левому приравниваем правому
	q->right = p;//правому пиравнием p
	fixheight(p);//вызываем функцию востановления корректно вытосоты для вершины p
	fixheight(q);//вызываем функцию востановления корректно вытосоты для вершины q
	return q;//вохвращаем q
}

//реализуется аналогично right (зеркально)
node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;//вершину перемешаем на правое поддерево
	q->right = p->left;//правому присваиваем левое
	p->left = q;//левому q
	fixheight(q);//вызываем функцию востановления корректно вытосоты для вершины q
	fixheight(p);//вызываем функцию востановления корректно вытосоты для вершины p
	return p;//возвращаем p
}

//для ситуаций дисбаланса

node* balance(node* p) // балансировка узла p
{
	fixheight(p);//фунция выравнивания по выоте
	if (bfactor(p) == 2)//если равно 2 то(когда высота правого поддерева на 2 больше левого)
	{
		if (bfactor(p->right) < 0)//реалтзуем так называемый большой поворот
			p->right = rotateright(p->right);//для правой вершины правый поворот
		return rotateleft(p);//левый поворот
	}
	if (bfactor(p) == -2)//если равно -2 то(когда высота левого поддерева на 2 больше правого)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);//левое поддерево левый поврот
		return rotateright(p);//правый поворот
	}
	return p; // балансировка не нужна
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new node(k);//пока не пустое создаем новую вершину к
	if (k < p->key)//если наша вершина менньше значния
		p->left = insert(p->left, k);//уходим влево проверяем дальше
	else//иначе
		p->right = insert(p->right, k);//уходим в право и проверяем дальше
	return balance(p);//вызываем банансирвку дерева
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;// если p->left вызываем p->left иначе возвращаем p(пока есть левое идем по нему)
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)//если левое равно 0
		return p->right;//переходим к правомсу
	p->left = removemin(p->left);//ищем минимальное
	return balance(p);//вызываем балансировку дерева
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;//если пустое возвращаем 0
	if (k < p->key)//если меньше вершины
		p->left = remove(p->left, k);//уходим налево
	else if (k > p->key)//если больше 
		p->right = remove(p->right, k);//уходим направо
	else //  k == p->key 
	{
		node* q = p->left;//создаем правую
		node* r = p->right;//сохдаем левую
		delete p;//удаляем вершину
		if (!r) return q;//если r не пусто возврашаем q
		node* min = findmin(r);// ищем min в r
		min->right = removemin(r);//вызываем вспомагателтную функцию
		min->left = q;//присваиваем q
		return balance(min);//вызывваем ба
	}
	return balance(p);//вызываем балансировку дерева
}



void levelOrder(node* x) {
	if (x == NULL)
		// возвращаем, если узел нулевой
		return;

	// queue 
	queue<node*> q;
	node* curr;

	// push x 
	q.push(x);

	while (!q.empty()) {
		// пока q не пусто
		// удаление очереди 
		curr = q.front();
		q.pop();

		// выводим значение узла
		cout << curr->key << " ";

		// добавдяем ребенка в очередь
		if (curr->left != NULL)
			q.push(curr->left);
		if (curr->right != NULL)
			q.push(curr->right);
	}
}

bool search(const int x, node* p)//функция проверки существования вершины
{
	if (!p)//если пустое
	{
		return false;// если пустое вызываем false
	}
	else if (x < p->key)//если меньше значения
	{
		return search(x, p->left);//идём по левому поддереву
	}
	else if (p->key < x)//если больше
	{
		return search(x, p->right);//идём по правому
	}
	//else{;}//пустой оператор
}


void preOrder(node* p) {
	
	if (p)
	{
		cout << p->key << " ";
		preOrder(p->left);
		preOrder(p->right);
	}
	
	
}
int main() {
	setlocale(LC_ALL, "rus");//подлючение русской раскладки
	int ch, y = 0;//вспомогаельные переменные для реализации меню
	int x;//переменная для вставки и удаления
	node* p = NULL;//создаем пустое дерево
	do
	{
		cout << "\n\t Красно черное дерево";
		cout << "\n 1. Вставка вершины ";
		cout << "\n 2. Удаление вершины";
		cout << "\n 3. Выбор вывода ";
		cout << "\n 4. Выход ";
		cout << "\nВыбор действия: "; cin >> ch;
		switch (ch)
		{
		case 1://вставка вершины
			cout << "Введите значение: ";
			cin >> x;
			p = insert(p, x);//вызываем функцию вставки
			cout << "\nВершина вставленна.\n";
			break;
		case 2://удаление вершины
			cout << "Введите значение: ";
			cin >> x;
			if (search(x, p))//проверяем существует ли данная вершина
				p = remove(p, x);//если да то вызываем функцию удаления
			else
				cout << "вершина не найдена";//иначе выводим
			break;

		case 3://выбор обхода дерева
			cout << "Выберите вывод " << endl;
			cout << "1)InOrder" << endl << "2)levelOrder" << endl ;
			cin >> x;
			cout << "------"<<endl;
			if (x == 1) {
				preOrder(p);//вызываем прямой обход
				break;
			}
			else levelOrder(p);//вызываем обход по уровням
			break;
		case 4: y = 1;//выход из программы
			break;
		default: cout << "\nВыбор действия.";
		}
		cout << endl;

	} while (y != 1);
	return 1;
	
	
}